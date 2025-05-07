
// !!attention!!
// pragma once etc. is intentionally not used here, multiple inclusions of this file shall cause compile errors

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//   (c) Copyright Siemens AG. 2001, All rights reserved.
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file   sltrc.h
 *  \author Hubmann Hans
 *  \date   30.7.2003
 *  \brief  SolutionLine Trace Support Header File.
 *
 *  Mit diesem File wird der SolutionLine Trace Support importiert. Der SolutionLine Trace Support ist über eine
 *  MAKRO-Schnittstelle einfach zu programmieren und kann Traces aus unterschiedlichen Prozessen und Threads
 *  in der Reihenfolge ihrer Entstehung in einen Trace-Datemstrom einfügen der z.B. auf der Platte abgelegt wird.
 *  Der SolutionLine Trace Support ist bezüglich Speicherplatz, Durchsatz, Traceablageort, Anreicherung der Traceausgaben
 *  mit Standardinformation, etc. vielfach konfigurierbar (Programm sltrc.exe).
 *
 *  Im SolutionLine Trace Support laufen die Traces aus unterschiedlichen Modulen zusammen. Jedem Modul sind 28 Tracebits
 *  zugeordnetet, mit denen themenspezifische Traces an- oder abgeschaltet werden können. Darüberhinaus kann über einen
 *  TraceLevel der Detaillierungsgrad von Traceausgaben gesteuert werden. Es gibt die Möglichkeit Traceausgaben zu
 *  programmieren, die in den Release-Varianten der Programme nicht vorhanden sind (DebugTrace). Der Modulname MUSS vor
 *  dem Inkludieren dieser Datei in der Manifestationskonstant SL_TRC_MODULE definiert sein (z.B. #define SL_TRC_MODULE SlTrc).
 *
 *  In sltrc.h sind die Makros definiert, mit denen der Trace programmiert abgesondert wird. Die Tracemakros enthalten
 *  die die Modalitäten der Traceausgabe im Namen (z.B. SL_TRCD_L2_BIT0, Ausgabe erfolgt wenn TraceBit 0 gesetzt ist
 *  und mindestens TraceLevel 2 vorliegt, Debugtrace). Weitere Makros geben programmierten Zugriff auf die TraceBits
 *  und den TraceLevel. Darüber hinaus manifestiert sltrc.h einige Konfigurationskonstanten des SolutionLine Trace Suport
 *  (z.B. SL_TRC_MAX_TRACE, die Maximallänge einer Traceausgabe). Die in dieser Datei spezifizierte Klasse SlTrc
 *  implementiert die Trace Funktionalität und ist nicht für die direkte Benutzung durch Anwender vorgesehen.
 *
 *  sltrc.h unterscheidet sich von anderen Inkludefiles dadurch, daß er nicht mehrfach inkludierbar ist. Dadurch meldet
 *  der Kompiler, wenn Unklarheiten bezüglich der Modulzuordnung bestehen. Deshalb darf diese Datei nie in Inkudefiles
 *  inkludiert sein (auch nicht indirekt!), die von einem Modul an andere Moduln exportiert werden. Weiterhin besteht eine
 *  Besonderheit darin, daß der Inkludefile (optional) Manifestationen erwartet, die ein Modulspezifisches Userinterface
 *  beschreiben (z.B. Text als TraceBit Bezeichner).
 *
 *  Wenn Sie diese Datei inkludieren, entsteht ein modulspezifischer Abschnitt im Konfigurationsfile /tmp/sltrc.ini
 *  (unter WINDOWS Laufwerk c:) und eine Memory-Mapped-File Datei /tmp/sltrc.shm (unter WINDOWS Laufwerk c:). Die Ablageorte
 *  der Traceinformation sind über sltrcsvc.exe->settings einstellbar. Damit die Datei Kompiliert müssen sowohl dei
 *  ACE als auch die Qt Includefiles über Suchpfade erreichbar sein. Zum Programm, das diese Datei inkludiert, muß sltrc.lib
 *  ace.lib und $(QTLIB) zugebunden werden.
 *
 *  Damit alle SL_TRC??? Makros keinen Code absetzten muß das Praeprozessor - Define SL_TRC_OFF vor Einbindung dieser Datei definiert werden.
 */

#ifdef _WIN32
typedef __int64 sltrcInt64;                   /*!< 64 bit signed integer */
typedef unsigned __int64 sltrcUInt64;         /*!< 64 bit unsigned integer */
typedef void SL_TRC_PRINT(const char* fmt, ...); /*!< No argcheck during compilation. */
#define SL_TRC_DIRSEP         "\\"            /*!< Directory separator (under windows). */
#define SL_TRC_SERVNAME       "sltrcsvc.exe"  /*!< SlCap server executable. */
#define SL_TRC_USER           "USERNAME"
#else
typedef void SL_TRC_PRINT(const char* fmt, ...) __attribute__((format(printf, 1, 2))); /*!< Argcheck during compilation. */
typedef long long sltrcInt64;                 /*!< 64 bit signed integer */
typedef unsigned long long sltrcUInt64;       /*!< 64 bit unsigned integer */
#define SL_TRC_DIRSEP         "/"             /*!< Directory separator (under linux). */
#define SL_TRC_SERVNAME       "sltrcsvc"      /*!< SlCap server executable. */
#define SL_TRC_USER           "USER"
#endif


// if you define SL_TRC_OFF, you switch of the tracing mechanism
#if !defined(SL_TRC_OFF)

template <class Key, class T> class QHash;
class QMutex;
class QString;
class QStringList;
class SlTrc_Log_Trap;
class SlTrc;
class SlHmiSettingsQt;
class SlHmiFileAccessQt;
struct SlTrcStaticObjects_;
struct SlTrcSvcClientData_;

// Übernahme des Debug Zustandes aus der Microsoft Manifestation, wenn nicht explizit SL_TRC_DEBUG gesetzt ist
#ifndef SL_TRC_DEBUG
#ifdef _DEBUG
#define SL_TRC_DEBUG 1
#else
#define SL_TRC_DEBUG 0
#endif // _DEBUG
#endif // SL_TRC_DEBUG


/*! \enum SlTrc_TrcBitsEnum
 *  Symbolisch Namen für die TraceBits des SlTrc Moduls
 */
enum SlTrc_TrcBitsEnum
{
  SL_TRC_FILTER_OFF        = 0x000001,  /*!< Schaltet Traces übergreifend ab */
  SL_TRC_FILTER_THREAD_ID  = 0x000004,  /*!< Schaltet einzig Traces aus dem Thread ein, der über die Shared Memory Variable uProcessThreadId vorgegeben wird. */
  SL_TRC_FILTER_PROCESS_ID = 0x000008,  /*!< Schaltet einzig Traces aus dem Prozess ein, der über die Shared Memory Variable uProcessThreadId vorgegeben wird. */
  SL_TRC_TAO_LOGGING       = 0x000010,  /*!< Setzt beim nächste Trace Event den TAO_debug_level auf 100 */
  SL_TRC_PICK_ACE          = 0x000020,  /*!< Nimmt ACE Logging Messages in den Trace auf. */
  SL_TRC_PICK_QT           = 0x000040,  /*!< Nimmt QT Messages  in den Trace auf. */
  SL_TRC_BREAK_QT          = 0x000080,  /*!< Bei QT Messages erfolgt Einsprung in den Debugger. */
  SL_TRC_ADD_FILE_LINE     = 0x000100,  /*!< Fügt an die Traceausgabe die Zeilennummer und den Filenamen des korrespondierenden Trace Makros an. */
  SL_TRC_ADD_TIMESTAMP     = 0x000200,  /*!< Fügt vor der Tracegabe einen Zeitstempel ein. */
  SL_TRC_ADD_THREAD_ID     = 0x000400,  /*!< Fügt vor der Tracegabe den ThreadId (ACE_Thread::self()) ein. */
  SL_TRC_ADD_PROCESS_ID    = 0x000800,  /*!< Fügt vor der Tracegabe den ProzessId (ACE_OS::getpid()) ein. */
  SL_TRC_ADD_MODULENAME    = 0x001000,  /*!< Fügt vor der Tracegabe den Modulnamen ein. */
  SL_TRC_ADD_BITS_LEVEL    = 0x002000,  /*!< Fügt vor der Tracegabe das TraceBit und den minimalen TraceLevel der Traceausgabe ein. */
  SL_TRC_ADD_HOSTNAME      = 0x004000,  /*!< Fügt vor der Tracegabe den Hostnamen ein, der für "localhost" geliefert wird. */
  SL_TRC_ADD_STACKP        = 0x008000,  /*!< Fügt vor der Tracegabe den Stack Zeiger ein. */
  SL_TRC_SINK_FILE         = 0x040000,  /*!< Sorgt für Traceausgabe auf die in den Settings hinterlegte Datei (wird verzögert wirksam) */
  SL_TRC_SINK_TAILVIEW     = 0x080000,  /*!< Startet/Beendet die TraceView */
  SL_TRC_SINK_IDE          = 0x100000,  /*!< Leitet die Traceausgaben an einen Debugger weiter, der ein Programm gestartet hat, das potentiell Traceausgaben tätigt (noch nicht implementiert!) */
  SL_TRC_SINK_STDOUT       = 0x200000,  /*!< Gibt die Traces am stdout des sltrcsvc Prozesses aus. */
  SL_TRC_FILE_REMOVE       = 0x2000000, /*!< Remove filesink file. */
  SL_TRC_SVC_TERMINATE     = 0x4000000   /*!< Beendet den SlTrcSvc Prozess. */
};

enum SlTrc_TrcExtendedBitsEnum
{
  S_TRC_EX_ADD_DATE        = 0x00000001, /*!< Add date to time stamp */
  S_TRC_EX_ADD_PROC_NAME   = 0x00000002  /*!< shows process name instead if pid */
};

/*! \enum SlTrc_ServerBitsEnum
 *  Shared Memory Residente Server Kommando Bits zur Steuerung des SlTrc.exe Servers. Zugriff über SlTrc::serverBits().
 */
enum SlTrc_ServerBitsEnum
{
  SL_TRC_SHOW_DIALOG       = 0x0001,    /*!< Veranlaßt den Server, die BitView anzuzeigen */
  SL_TRC_SETTINGS_CHANGED  = 0x0100     /*!< Signalisiert dem Server, daß er z.B. den Trace Ausgabe Dateinamen erneut aus der Konfigurationsdatei lesen soll. */
};

// SlTrc Value Manifestations
#define SL_TRC_MAX_TRACE                253     // Maximale Zeichenzahl einer Traceausgabe (inklusive Standardinformation)
#define SL_TRC_REGEXP_SLICE             1000    // Anzahl nicht unterbrechbarer Auswertungen Regulärer Ausdrücke
#define SL_TRC_REGEXP_WORKING_COLOR     QColor(255, 205, 205) // Hintergrundfarbe eines Regulären Ausdrucks , solange er nicht für alle Zeilen ausgewertet wurde
#define SL_TRC_ACTIVE_LINE_BACKCOLOR    QColor(200, 200, 200) // Hintergrundfarbe der aktuellen Zeile
#define SL_TRC_CONFIG_FILE              "sltrccfg" // name of the sltrc config file
#define SL_TRC_KEYBITSET_FILE           "sltrc_keybitset.ini" // name of the sltrc KeyBitSet file file
#define SL_TRC_OUTFILE                  "sltrc.out"   /*!< Default tracefile name. */
#define SL_TRC_OUTDIR                   "log" SL_TRC_DIRSEP "sltrc" /*!< Default tracefile directory. */
#define SL_TRC_TRCPREFERRED_BITS        0x31041662  /*!< Preferred Developper bit setting of module SlTrc. */
#define SL_TRC_TRCINTERFACE_BITS        0x31041662  /*!< Preferred Interface bit setting of module SlTrc. */

// SlTrc Timeout Manifestations
#define SL_TRC_SERIALIZATION_TIMEOUT_MS (SL_TRC_SERVERDETECT_TIMEOUT_MS + SL_TRC_SERVERSTART_TIMEOUT_MS + 2000)   // Maximalzeit (ms), die ein Prozess an der Aktivitäts Serialisierung wartet
#define SL_TRC_SERVERDETECT_TIMEOUT_MS  4000    // Nach Ablauf dieser Zeit (ms) wird angenommen, daß kein sltrc.exe abläuft
#define SL_TRC_SERVERSTART_TIMEOUT_MS   5500    // Solange wird maximal auf den Start von sltrc.exe gewartet
#define SL_TRC_COMMIT_CYCLE_MS          5000    // In diesem Intervall (ms) wird die Tracedatei geschlossen um die Daten auf der Platte konsistent zu machen
#define SL_TRC_SERVER_FLAG_SLEEP_MS     600     // Zyklus (ms), in dem die ServerBits ausgewertet werden
#define SL_TRC_SERVER_POLL_SLEEP_MS     100     // Pollzyklus (ms) des Shared Memory Threads
#define SL_TRC_COORD_POLL_MS            10      // Pollzyklus für Koordinierungszwecke.
#define SL_TRC_FILLED_FLAG_TIMEOUT_MS   1000    // Limit the time a entry can be between allocation and being filled

// Konfiguration beim ersten Start des SolutionLine Trace Support
const int SL_TRC_SHM_BUFFER_SIZE_DEFAULT = 4000; /*!< Default number of tracelines in shm buffer. */
const int SL_TRC_SHM_BUFFER_SIZE = 15;          /*!< Minimum number of tracelines within a shared memory trace buffer. */
const int SL_TRC_SHM_ADMIN_PAGECOUNT = 2;       /*!< Number of memory pages reserved for SlTrc administration. Increase this value if you need more tracing modules. */
const unsigned SL_TRC_DEFAULT_FILESIZE = 10000; /*!< Default size of sink file in kilobytes. */
const unsigned SL_TRC_DEFAULT_NUM_TRACE_FILES = 1; /*!< Default num trace files */
const unsigned SL_TRC_MAGIC = 0xbeeffeed;       /*!< SlTrc mark. */
const unsigned SL_TRC_VERSION = 4;              /*!< Version of Shm layout. (Also used to trigger the allocation of a new shared memory centrally) */
#define SL_TRC_FILE_QUEUE_SIZE              15  // Länge des FIFO Puffers zwischen Shared Memory und File Thread
#define SL_TRC_TRACE_VIEW_QUEUE_SIZE    200000  // Länge des FIFO Puffers zwischen Shared Memory und TraceView
#define SL_TRC_STDOUT_QUEUE_SIZE        200000  // Länge des FIFO Puffers zwischen Shared Memory und stdout Ausgabe
#define SL_TRC_TRACE_VIEW_HISTORY_SIZE   10000  // Anzahl der Zeilen, die die TraceView speichert

// other constants
const unsigned SL_TRC_TIME_NOT_SET = 0xffffffff;// indicates, that a time value is not set.

// Import/Export control
#ifndef SL_TRC_EXPORT
#define SL_TRC_EXPORT
#endif

// ======================================================================================================
// Vervollständigung der Manifestationen
// ======================================================================================================

// assure a module name being existing and derive the module name string
#ifndef SL_TRC_MODULE
#define SL_TRC_MODULE ANONYM
#endif

#define SL_TRC_ALL_BITS 0xfffffff
#define SL_TRC_DEFAULT_ANYBITS SL_TRC_ALL_BITS
#if !defined(SL_TRC_ANY) && defined(_DEBUG) && defined(SL_TRCD_ANYBITS)
#define SL_TRC_ANY (SL_TRCD_ANYBITS & SL_TRC_ALL_BITS)
#endif
#if !defined(SL_TRC_ANY) && defined(SL_TRC_ANYBITS)
#define SL_TRC_ANY (SL_TRC_ANYBITS & SL_TRC_ALL_BITS)
#endif
#if !defined(SL_TRC_ANY)
#define SL_TRC_ANY SL_TRC_DEFAULT_ANYBITS
#endif

#define SL_TRC_PREFERRED_BITSETTING 0x3fffffff
#if !defined(SL_TRC_PREFERRED) && defined(_DEBUG) && defined(SL_TRCD_PREFERRED_BITS)
#define SL_TRC_PREFERRED SL_TRCD_PREFERRED_BITS
#endif
#if !defined(SL_TRC_PREFERRED) && defined(SL_TRC_PREFERRED_BITS)
#define SL_TRC_PREFERRED SL_TRC_PREFERRED_BITS
#endif
#if !defined(SL_TRC_PREFERRED)
#define SL_TRC_PREFERRED SL_TRC_PREFERRED_BITSETTING
#endif

#define SL_TRC_INTERFACE_BITSETTING 0x3fffffff
#if !defined(SL_TRC_INTERFACE) && defined(_DEBUG) && defined(SL_TRCD_INTERFACE_BITS)
#define SL_TRC_INTERFACE SL_TRCD_INTERFACE_BITS
#endif
#if !defined(SL_TRC_INTERFACE) && defined(SL_TRC_INTERFACE_BITS)
#define SL_TRC_INTERFACE SL_TRC_INTERFACE_BITS
#endif
#if !defined(SL_TRC_INTERFACE)
#define SL_TRC_INTERFACE SL_TRC_INTERFACE_BITSETTING
#endif

#ifndef SL_TRC_BIT0_TEXT
#   ifdef _DEBUG
#       ifdef SL_TRCD_BIT0_TEXT
#           define SL_TRC_BIT0_TEXT SL_TRCD_BIT0_TEXT
#       else
#           define SL_TRC_BIT0_TEXT "Bit 0"
#       endif
#   else
#       define SL_TRC_BIT0_TEXT "?"
#   endif
#endif
#ifndef SL_TRC_BIT1_TEXT
#   ifdef _DEBUG
#       ifdef SL_TRCD_BIT1_TEXT
#           define SL_TRC_BIT1_TEXT SL_TRCD_BIT1_TEXT
#       else
#           define SL_TRC_BIT1_TEXT "Bit 1"
#       endif
#   else
#       define SL_TRC_BIT1_TEXT "?"
#   endif
#endif
#ifndef SL_TRC_BIT2_TEXT
#   ifdef _DEBUG
#       ifdef SL_TRCD_BIT2_TEXT
#           define SL_TRC_BIT2_TEXT SL_TRCD_BIT2_TEXT
#       else
#           define SL_TRC_BIT2_TEXT "Bit 2"
#       endif
#   else
#       define SL_TRC_BIT2_TEXT "?"
#   endif
#endif
#ifndef SL_TRC_BIT3_TEXT
#   ifdef _DEBUG
#       ifdef SL_TRCD_BIT3_TEXT
#           define SL_TRC_BIT3_TEXT SL_TRCD_BIT3_TEXT
#       else
#           define SL_TRC_BIT3_TEXT "Bit 3"
#       endif
#   else
#       define SL_TRC_BIT3_TEXT "?"
#   endif
#endif
#ifndef SL_TRC_BIT4_TEXT
#   ifdef _DEBUG
#       ifdef SL_TRCD_BIT4_TEXT
#           define SL_TRC_BIT4_TEXT SL_TRCD_BIT4_TEXT
#       else
#           define SL_TRC_BIT4_TEXT "Bit 4"
#       endif
#   else
#       define SL_TRC_BIT4_TEXT "?"
#   endif
#endif
#ifndef SL_TRC_BIT5_TEXT
#   ifdef _DEBUG
#       ifdef SL_TRCD_BIT5_TEXT
#           define SL_TRC_BIT5_TEXT SL_TRCD_BIT5_TEXT
#       else
#           define SL_TRC_BIT5_TEXT "Bit 5"
#       endif
#   else
#       define SL_TRC_BIT5_TEXT "?"
#   endif
#endif
#ifndef SL_TRC_BIT6_TEXT
#   ifdef _DEBUG
#       ifdef SL_TRCD_BIT6_TEXT
#           define SL_TRC_BIT6_TEXT SL_TRCD_BIT6_TEXT
#       else
#           define SL_TRC_BIT6_TEXT "Bit 6"
#       endif
#   else
#       define SL_TRC_BIT6_TEXT "?"
#   endif
#endif
#ifndef SL_TRC_BIT7_TEXT
#   ifdef _DEBUG
#       ifdef SL_TRCD_BIT7_TEXT
#           define SL_TRC_BIT7_TEXT SL_TRCD_BIT7_TEXT
#       else
#           define SL_TRC_BIT7_TEXT "Bit 7"
#       endif
#   else
#       define SL_TRC_BIT7_TEXT "?"
#   endif
#endif
#ifndef SL_TRC_BIT8_TEXT
#   ifdef _DEBUG
#       ifdef SL_TRCD_BIT8_TEXT
#           define SL_TRC_BIT8_TEXT SL_TRCD_BIT8_TEXT
#       else
#           define SL_TRC_BIT8_TEXT "Bit 8"
#       endif
#   else
#       define SL_TRC_BIT8_TEXT "?"
#   endif
#endif
#ifndef SL_TRC_BIT9_TEXT
#   ifdef _DEBUG
#       ifdef SL_TRCD_BIT9_TEXT
#           define SL_TRC_BIT9_TEXT SL_TRCD_BIT9_TEXT
#       else
#           define SL_TRC_BIT9_TEXT "Bit 9"
#       endif
#   else
#       define SL_TRC_BIT9_TEXT "?"
#   endif
#endif
#ifndef SL_TRC_BIT10_TEXT
#   ifdef _DEBUG
#       ifdef SL_TRCD_BIT10_TEXT
#           define SL_TRC_BIT10_TEXT SL_TRCD_BIT10_TEXT
#       else
#           define SL_TRC_BIT10_TEXT "Bit 10"
#       endif
#   else
#       define SL_TRC_BIT10_TEXT "?"
#   endif
#endif
#ifndef SL_TRC_BIT11_TEXT
#   ifdef _DEBUG
#       ifdef SL_TRCD_BIT11_TEXT
#           define SL_TRC_BIT11_TEXT SL_TRCD_BIT11_TEXT
#       else
#           define SL_TRC_BIT11_TEXT "Bit 11"
#       endif
#   else
#       define SL_TRC_BIT11_TEXT "?"
#   endif
#endif
#ifndef SL_TRC_BIT12_TEXT
#   ifdef _DEBUG
#       ifdef SL_TRCD_BIT12_TEXT
#           define SL_TRC_BIT12_TEXT SL_TRCD_BIT12_TEXT
#       else
#           define SL_TRC_BIT12_TEXT "Bit 12"
#       endif
#   else
#       define SL_TRC_BIT12_TEXT "?"
#   endif
#endif
#ifndef SL_TRC_BIT13_TEXT
#   ifdef _DEBUG
#       ifdef SL_TRCD_BIT13_TEXT
#           define SL_TRC_BIT13_TEXT SL_TRCD_BIT13_TEXT
#       else
#           define SL_TRC_BIT13_TEXT "Bit 13"
#       endif
#   else
#       define SL_TRC_BIT13_TEXT "?"
#   endif
#endif
#ifndef SL_TRC_BIT14_TEXT
#   ifdef _DEBUG
#       ifdef SL_TRCD_BIT14_TEXT
#           define SL_TRC_BIT14_TEXT SL_TRCD_BIT14_TEXT
#       else
#           define SL_TRC_BIT14_TEXT "Bit 14"
#       endif
#   else
#       define SL_TRC_BIT14_TEXT "?"
#   endif
#endif
#ifndef SL_TRC_BIT15_TEXT
#   ifdef _DEBUG
#       ifdef SL_TRCD_BIT15_TEXT
#           define SL_TRC_BIT15_TEXT SL_TRCD_BIT15_TEXT
#       else
#           define SL_TRC_BIT15_TEXT "Bit 15"
#       endif
#   else
#       define SL_TRC_BIT15_TEXT "?"
#   endif
#endif
#ifndef SL_TRC_BIT16_TEXT
#   ifdef _DEBUG
#       ifdef SL_TRCD_BIT16_TEXT
#           define SL_TRC_BIT16_TEXT SL_TRCD_BIT16_TEXT
#       else
#           define SL_TRC_BIT16_TEXT "Bit 16"
#       endif
#   else
#       define SL_TRC_BIT16_TEXT "?"
#   endif
#endif
#ifndef SL_TRC_BIT17_TEXT
#   ifdef _DEBUG
#       ifdef SL_TRCD_BIT17_TEXT
#           define SL_TRC_BIT17_TEXT SL_TRCD_BIT17_TEXT
#       else
#           define SL_TRC_BIT17_TEXT "Bit 17"
#       endif
#   else
#       define SL_TRC_BIT17_TEXT "?"
#   endif
#endif
#ifndef SL_TRC_BIT18_TEXT
#   ifdef _DEBUG
#       ifdef SL_TRCD_BIT18_TEXT
#           define SL_TRC_BIT18_TEXT SL_TRCD_BIT18_TEXT
#       else
#           define SL_TRC_BIT18_TEXT "Bit 18"
#       endif
#   else
#       define SL_TRC_BIT18_TEXT "?"
#   endif
#endif
#ifndef SL_TRC_BIT19_TEXT
#   ifdef _DEBUG
#       ifdef SL_TRCD_BIT19_TEXT
#           define SL_TRC_BIT19_TEXT SL_TRCD_BIT19_TEXT
#       else
#           define SL_TRC_BIT19_TEXT "Bit 19"
#       endif
#   else
#       define SL_TRC_BIT19_TEXT "?"
#   endif
#endif
#ifndef SL_TRC_BIT20_TEXT
#   ifdef _DEBUG
#       ifdef SL_TRCD_BIT20_TEXT
#           define SL_TRC_BIT20_TEXT SL_TRCD_BIT20_TEXT
#       else
#           define SL_TRC_BIT20_TEXT "Bit 20"
#       endif
#   else
#       define SL_TRC_BIT20_TEXT "?"
#   endif
#endif
#ifndef SL_TRC_BIT21_TEXT
#   ifdef _DEBUG
#       ifdef SL_TRCD_BIT21_TEXT
#           define SL_TRC_BIT21_TEXT SL_TRCD_BIT21_TEXT
#       else
#           define SL_TRC_BIT21_TEXT "Bit 21"
#       endif
#   else
#       define SL_TRC_BIT21_TEXT "?"
#   endif
#endif
#ifndef SL_TRC_BIT22_TEXT
#   ifdef _DEBUG
#       ifdef SL_TRCD_BIT22_TEXT
#           define SL_TRC_BIT22_TEXT SL_TRCD_BIT22_TEXT
#       else
#           define SL_TRC_BIT22_TEXT "Bit 22"
#       endif
#   else
#       define SL_TRC_BIT22_TEXT "?"
#   endif
#endif
#ifndef SL_TRC_BIT23_TEXT
#   ifdef _DEBUG
#       ifdef SL_TRCD_BIT23_TEXT
#           define SL_TRC_BIT23_TEXT SL_TRCD_BIT23_TEXT
#       else
#           define SL_TRC_BIT23_TEXT "Bit 23"
#       endif
#   else
#       define SL_TRC_BIT23_TEXT "?"
#   endif
#endif
#ifndef SL_TRC_BIT24_TEXT
#   ifdef _DEBUG
#       ifdef SL_TRCD_BIT24_TEXT
#           define SL_TRC_BIT24_TEXT SL_TRCD_BIT24_TEXT
#       else
#           define SL_TRC_BIT24_TEXT "Bit 24"
#       endif
#   else
#       define SL_TRC_BIT24_TEXT "?"
#   endif
#endif
#ifndef SL_TRC_BIT25_TEXT
#   ifdef _DEBUG
#       ifdef SL_TRCD_BIT25_TEXT
#           define SL_TRC_BIT25_TEXT SL_TRCD_BIT25_TEXT
#       else
#           define SL_TRC_BIT25_TEXT "Bit 25"
#       endif
#   else
#       define SL_TRC_BIT25_TEXT "?"
#   endif
#endif
#ifndef SL_TRC_BIT26_TEXT
#   ifdef _DEBUG
#       ifdef SL_TRCD_BIT26_TEXT
#           define SL_TRC_BIT26_TEXT SL_TRCD_BIT26_TEXT
#       else
#           define SL_TRC_BIT26_TEXT "Bit 26"
#       endif
#   else
#       define SL_TRC_BIT26_TEXT "?"
#   endif
#endif
#ifndef SL_TRC_BIT27_TEXT
#   ifdef _DEBUG
#       ifdef SL_TRCD_BIT27_TEXT
#           define SL_TRC_BIT27_TEXT SL_TRCD_BIT27_TEXT
#       else
#           define SL_TRC_BIT27_TEXT "Bit 27"
#       endif
#   else
#       define SL_TRC_BIT27_TEXT "?"
#   endif
#endif

#ifndef SL_TRC_BIT0_TOOLTIP
#   if defined(_DEBUG) && defined(SL_TRCD_BIT0_TOOLTIP)
#       define SL_TRC_BIT0_TOOLTIP SL_TRCD_BIT0_TOOLTIP
#   else
#       define SL_TRC_BIT0_TOOLTIP ""
#   endif
#endif
#ifndef SL_TRC_BIT1_TOOLTIP
#   if defined(_DEBUG) && defined(SL_TRCD_BIT1_TOOLTIP)
#       define SL_TRC_BIT1_TOOLTIP SL_TRCD_BIT1_TOOLTIP
#   else
#       define SL_TRC_BIT1_TOOLTIP ""
#   endif
#endif
#ifndef SL_TRC_BIT2_TOOLTIP
#   if defined(_DEBUG) && defined(SL_TRCD_BIT2_TOOLTIP)
#       define SL_TRC_BIT2_TOOLTIP SL_TRCD_BIT2_TOOLTIP
#   else
#       define SL_TRC_BIT2_TOOLTIP ""
#   endif
#endif
#ifndef SL_TRC_BIT3_TOOLTIP
#   if defined(_DEBUG) && defined(SL_TRCD_BIT3_TOOLTIP)
#       define SL_TRC_BIT3_TOOLTIP SL_TRCD_BIT3_TOOLTIP
#   else
#       define SL_TRC_BIT3_TOOLTIP ""
#   endif
#endif
#ifndef SL_TRC_BIT4_TOOLTIP
#   if defined(_DEBUG) && defined(SL_TRCD_BIT4_TOOLTIP)
#       define SL_TRC_BIT4_TOOLTIP SL_TRCD_BIT4_TOOLTIP
#   else
#       define SL_TRC_BIT4_TOOLTIP ""
#   endif
#endif
#ifndef SL_TRC_BIT5_TOOLTIP
#   if defined(_DEBUG) && defined(SL_TRCD_BIT5_TOOLTIP)
#       define SL_TRC_BIT5_TOOLTIP SL_TRCD_BIT5_TOOLTIP
#   else
#       define SL_TRC_BIT5_TOOLTIP ""
#   endif
#endif
#ifndef SL_TRC_BIT6_TOOLTIP
#   if defined(_DEBUG) && defined(SL_TRCD_BIT6_TOOLTIP)
#       define SL_TRC_BIT6_TOOLTIP SL_TRCD_BIT6_TOOLTIP
#   else
#       define SL_TRC_BIT6_TOOLTIP ""
#   endif
#endif
#ifndef SL_TRC_BIT7_TOOLTIP
#   if defined(_DEBUG) && defined(SL_TRCD_BIT7_TOOLTIP)
#       define SL_TRC_BIT7_TOOLTIP SL_TRCD_BIT7_TOOLTIP
#   else
#       define SL_TRC_BIT7_TOOLTIP ""
#   endif
#endif
#ifndef SL_TRC_BIT8_TOOLTIP
#   if defined(_DEBUG) && defined(SL_TRCD_BIT8_TOOLTIP)
#       define SL_TRC_BIT8_TOOLTIP SL_TRCD_BIT8_TOOLTIP
#   else
#       define SL_TRC_BIT8_TOOLTIP ""
#   endif
#endif
#ifndef SL_TRC_BIT9_TOOLTIP
#   if defined(_DEBUG) && defined(SL_TRCD_BIT9_TOOLTIP)
#       define SL_TRC_BIT9_TOOLTIP SL_TRCD_BIT9_TOOLTIP
#   else
#       define SL_TRC_BIT9_TOOLTIP ""
#   endif
#endif
#ifndef SL_TRC_BIT10_TOOLTIP
#   if defined(_DEBUG) && defined(SL_TRCD_BIT10_TOOLTIP)
#       define SL_TRC_BIT10_TOOLTIP SL_TRCD_BIT10_TOOLTIP
#   else
#       define SL_TRC_BIT10_TOOLTIP ""
#   endif
#endif
#ifndef SL_TRC_BIT11_TOOLTIP
#   if defined(_DEBUG) && defined(SL_TRCD_BIT11_TOOLTIP)
#       define SL_TRC_BIT11_TOOLTIP SL_TRCD_BIT11_TOOLTIP
#   else
#       define SL_TRC_BIT11_TOOLTIP ""
#   endif
#endif
#ifndef SL_TRC_BIT12_TOOLTIP
#   if defined(_DEBUG) && defined(SL_TRCD_BIT12_TOOLTIP)
#       define SL_TRC_BIT12_TOOLTIP SL_TRCD_BIT12_TOOLTIP
#   else
#       define SL_TRC_BIT12_TOOLTIP ""
#   endif
#endif
#ifndef SL_TRC_BIT13_TOOLTIP
#   if defined(_DEBUG) && defined(SL_TRCD_BIT13_TOOLTIP)
#       define SL_TRC_BIT13_TOOLTIP SL_TRCD_BIT13_TOOLTIP
#   else
#       define SL_TRC_BIT13_TOOLTIP ""
#   endif
#endif
#ifndef SL_TRC_BIT14_TOOLTIP
#   if defined(_DEBUG) && defined(SL_TRCD_BIT14_TOOLTIP)
#       define SL_TRC_BIT14_TOOLTIP SL_TRCD_BIT14_TOOLTIP
#   else
#       define SL_TRC_BIT14_TOOLTIP ""
#   endif
#endif
#ifndef SL_TRC_BIT15_TOOLTIP
#   if defined(_DEBUG) && defined(SL_TRCD_BIT15_TOOLTIP)
#       define SL_TRC_BIT15_TOOLTIP SL_TRCD_BIT15_TOOLTIP
#   else
#       define SL_TRC_BIT15_TOOLTIP ""
#   endif
#endif
#ifndef SL_TRC_BIT16_TOOLTIP
#   if defined(_DEBUG) && defined(SL_TRCD_BIT16_TOOLTIP)
#       define SL_TRC_BIT16_TOOLTIP SL_TRCD_BIT16_TOOLTIP
#   else
#       define SL_TRC_BIT16_TOOLTIP ""
#   endif
#endif
#ifndef SL_TRC_BIT17_TOOLTIP
#   if defined(_DEBUG) && defined(SL_TRCD_BIT17_TOOLTIP)
#       define SL_TRC_BIT17_TOOLTIP SL_TRCD_BIT17_TOOLTIP
#   else
#       define SL_TRC_BIT17_TOOLTIP ""
#   endif
#endif
#ifndef SL_TRC_BIT18_TOOLTIP
#   if defined(_DEBUG) && defined(SL_TRCD_BIT18_TOOLTIP)
#       define SL_TRC_BIT18_TOOLTIP SL_TRCD_BIT18_TOOLTIP
#   else
#       define SL_TRC_BIT18_TOOLTIP ""
#   endif
#endif
#ifndef SL_TRC_BIT19_TOOLTIP
#   if defined(_DEBUG) && defined(SL_TRCD_BIT19_TOOLTIP)
#       define SL_TRC_BIT19_TOOLTIP SL_TRCD_BIT19_TOOLTIP
#   else
#       define SL_TRC_BIT19_TOOLTIP ""
#   endif
#endif
#ifndef SL_TRC_BIT20_TOOLTIP
#   if defined(_DEBUG) && defined(SL_TRCD_BIT20_TOOLTIP)
#       define SL_TRC_BIT20_TOOLTIP SL_TRCD_BIT20_TOOLTIP
#   else
#       define SL_TRC_BIT20_TOOLTIP ""
#   endif
#endif
#ifndef SL_TRC_BIT21_TOOLTIP
#   if defined(_DEBUG) && defined(SL_TRCD_BIT21_TOOLTIP)
#       define SL_TRC_BIT21_TOOLTIP SL_TRCD_BIT21_TOOLTIP
#   else
#       define SL_TRC_BIT21_TOOLTIP ""
#   endif
#endif
#ifndef SL_TRC_BIT22_TOOLTIP
#   if defined(_DEBUG) && defined(SL_TRCD_BIT22_TOOLTIP)
#       define SL_TRC_BIT22_TOOLTIP SL_TRCD_BIT22_TOOLTIP
#   else
#       define SL_TRC_BIT22_TOOLTIP ""
#   endif
#endif
#ifndef SL_TRC_BIT23_TOOLTIP
#   if defined(_DEBUG) && defined(SL_TRCD_BIT23_TOOLTIP)
#       define SL_TRC_BIT23_TOOLTIP SL_TRCD_BIT23_TOOLTIP
#   else
#       define SL_TRC_BIT23_TOOLTIP ""
#   endif
#endif
#ifndef SL_TRC_BIT24_TOOLTIP
#   if defined(_DEBUG) && defined(SL_TRCD_BIT24_TOOLTIP)
#       define SL_TRC_BIT24_TOOLTIP SL_TRCD_BIT24_TOOLTIP
#   else
#       define SL_TRC_BIT24_TOOLTIP ""
#   endif
#endif
#ifndef SL_TRC_BIT25_TOOLTIP
#   if defined(_DEBUG) && defined(SL_TRCD_BIT25_TOOLTIP)
#       define SL_TRC_BIT25_TOOLTIP SL_TRCD_BIT25_TOOLTIP
#   else
#       define SL_TRC_BIT25_TOOLTIP ""
#   endif
#endif
#ifndef SL_TRC_BIT26_TOOLTIP
#   if defined(_DEBUG) && defined(SL_TRCD_BIT26_TOOLTIP)
#       define SL_TRC_BIT26_TOOLTIP SL_TRCD_BIT26_TOOLTIP
#   else
#       define SL_TRC_BIT26_TOOLTIP ""
#   endif
#endif
#ifndef SL_TRC_BIT27_TOOLTIP
#   if defined(_DEBUG) && defined(SL_TRCD_BIT27_TOOLTIP)
#       define SL_TRC_BIT27_TOOLTIP SL_TRCD_BIT27_TOOLTIP
#   else
#       define SL_TRC_BIT27_TOOLTIP ""
#   endif
#endif



// ======================================================================================================
// Wird intern genutzt
// ======================================================================================================

// helper
#undef SL_TRC_STRINGIZED_MODULE                       // note: String may be predefined in slcapdata.h
#define SL_TRC_STRINGIZE_(X) #X
#define SL_TRC_STRINGIZE(X) SL_TRC_STRINGIZE_(X)
#define SL_TRC_STRINGIZED_MODULE SL_TRC_STRINGIZE(SL_TRC_MODULE)

#define SL_TRC_NAMESPACE_(X) X ## SlTrcNamespace
#define SL_TRC_NAMESPACE__(X) SL_TRC_NAMESPACE_(X)
#define SL_TRC_NAMESPACE SL_TRC_NAMESPACE__(SL_TRC_MODULE)

#ifdef WIN32
#  define SL_TRC_ALWAYS_INLINE    __forceinline
#else
#  define SL_TRC_ALWAYS_INLINE    inline __attribute__((always_inline))
#endif

// forwärts Deklarationen
class SlTrc;
namespace SL_TRC_NAMESPACE
{
  SlTrc* TrcObj();
  bool ifTrace(unsigned uLevel, unsigned uBits);
  bool ifTraceAny(unsigned uLevel, unsigned uBits);
}

namespace SLTrcSlTrcNamespace
{
  SlTrc* TrcObj();
  bool ifTrace(unsigned uLevel, unsigned uBits);
  bool ifTraceAny(unsigned uLevel, unsigned uBits);
}





/*! \struct SlTrcCachedInfo
 *  Globaldaten-Cache zur Beschleunigung der Trace-Bedingungsauswertung in Function ifTrace.
 */
typedef struct SlTrcCachedInfo_
{
  unsigned *m_puFlags;        /*!< Zeiger auf die modulspezifischen TraceBits. */
  unsigned *m_puCommonFlags;  /*!< Zeiger auf die TraceBits des Moduls SlTrc. */
  unsigned *m_puFilterId;     /*!< Zeiger auf den Prozess- oder Thread-ID */
} SlTrcCachedInfo;




/*! \struct SlTrcShmAdmin
 *  Für alle Prozesse sichtbare Verwaltungsinformation im Shared Memory.
 */
typedef struct SlTrcShmAdmin_
{
  volatile unsigned int iLineAdmin;    /*!< Hält die Einfügeposition (obere 16 Bit) und die Entnahmeposition (untere 16 Bit) für den
                               *   Shared für das Zeilenarray im Shared Memory (SlTrc_::g_pLines). Die Indizes werden aus diesen
                               *   Positionen durch eine Modulobildung zur allozierten Zeilenzahl (iLineAlloc) gebildet. Die
                               *   koordiniert den Zugriff aus unterschiedlichen Prozessen und muß stets mit der atomicAdd
                               *   Funktion verändert werden. Einfügeposition und Entnahmeposition wurden in einer Variablen
                               *   untergebracht, damit sie beide gleichzeitig atomar verändert werden können.
                               */

  int iLineAlloc;             /*!< Anzahl der Zeilen Puffer im Shared Memory. Achtung, solange die Shared Memory Datei nicht gelöscht wurde
                               *   stimmt die allozierte Anzahl möglicherweise nicht mit dem in der Konfigurationsdatei abgelegten
                               *   Wert überein.
                               */

  unsigned uProcessThreadId;  /*!< Prozess- oder Thread-ID zur Selektion/Filterung von Trace Ausgaben. */
  int iShmSize;               /*!< Bytesize of the shm file. */
  int iAppendingThreads;      /*!< Anzahl der Threads, die sich in der _append Prozedur befinden. */
  unsigned uServerBits;       /*!< Bits for SlTrc server interaction. */
  int iLineCountRequired;     /*!< Number of tracelines wished by user. */
  unsigned uFileSize;         /*!< Required file sink size. */
  unsigned uMagic;            /*!< SlTrc marker. */
  unsigned uVersion;          /*!< Shm Layout version. */
  unsigned uNumTraceFiles;    /*!< Number of trace files for swapping */
  unsigned uExtendedBits;     /*!< Extended bits for trace control */
  unsigned uReserved[6];      /*!< Reserved space for future versions. */
  bool bClientBlocked;        /*!< Signalisiert dem Server, daß ein Client wartet, weil das Shared Memory voll war. */
  bool bServerWaiting;        /*!< Signalisiert den Clients, daß der Server datrauf wartet, bei Traceeintrag aufgeweckt zu werden. */

  // Add new members here, in front of the next 4 variables, because below this line, with czFirstModuleName a data array beginns

  // start of module administation
  char czFirstModuleName[6];  /*!< Name of the first module (= always "SLTrc") */
  unsigned iFirstModuleBits;  /*!< Tracebits of SlTrc. */
  unsigned iFirstModuleHash;  /*!< Text Hashkey of SlTrc. */
  unsigned iFirstModuleBitMask; /*!< Tracebits of SlTrc. */

  // Zugriffe auf die Zeilen-Verwaltungsinformation (iLineAdmin) =================================================================
  //! Addiert einen Wert atomar auf Zeilen-Einfügezeiger des Shared Memory
  /*! \param Der addierte Wert. */
  int addLineCount(int cnt);

  /*! Zugriff auf den Einfügezeiger bei vorgegebener Verwaltungsinformation. Hinweis: wenn die Verwaltungsinformation ausgelesen
   *  wird und anschließend nach Einfügepososition und Entnahmeposition aufgesplittet wird, so sind Einfügepososition und Entnahmeposition
   *  kohärent. Man kann dann zum Beispiel die Anzahl der im Shared Memory befindlichen Zeilen berechnen.

   *  \param Eine vorher ausgelesene Verwaltungsinformation (iLineAdmin).
   */
  static int lineCount(int iLineAdmin);

  //! Addiert einen Wert atomar auf Zeilen-Entnahmezeiger des Shared Memory
  /*! \param Der addierte Wert. */
  int addLineOutput(int cnt);

  /*! Zugriff auf den Entnahmezeiger bei vorgegebener Verwaltungsinformation. Hinweis: wenn die Verwaltungsinformation ausgelesen
   *  wird und anschließend nach Einfügepososition und Entnahmeposition aufgesplittet wird, so sind Einfügepososition und Entnahmeposition
   *  kohärent. Man kann dann zum Beispiel die Anzahl der im Shared Memory befindlichen Zeilen berechnen.

   *  \param Eine vorher ausgelesene Verwaltungsinformation (iLineAdmin).
   */
  static int lineOutput(int iLineAdmin);

  //! Subtrahiert einen Wert atomar vom Zeilen-Einfügezeiger und vom Zeilen-Entnahmezeiger des Shared Memory.
  /*! \param Der subtrahierte Wert. */
  void subBoth(int cnt);

  //! Ermittelt die Anzahl unbelegter Zeilen im Shared Memory
  int freeCount();

  //! Ermittelt ob der Tracepuffer leer ist
  bool empty();
} SlTrcShmAdmin;

//SlTrcShmAdmin* const SL_TRC_SHM_NOTUSABLE = reinterpret_cast<SlTrcShmAdmin*>(1);



/*! \struct SlTrcShmLine
 *  Information je Trace Zeile im Shared Memory.
 */
typedef struct SlTrcShmLine_
{
    volatile unsigned char bFilled;     /*!< Zeigt an ob der ZeilenPuffer belegt ist. Wird vom Trace-eintragenden Clienten auf 1
                                         *   gesetzt, sobald der Text Puffer und die Zeichenanzahl belegt sind. Wird vom TrcServer
                                         *   auf 0 gesetzt, sobald er die Zeileninformation übernommen hat.
                                         */

    unsigned char bLost;                /*!< Clients vermerken hier (Wert:1), daß sie eine Trace Ausgabe nicht im Shared Memory
                                         *   unterbringen konnten. Der TrcServer erzeugt den Tracetext "...TRACES LOST...", wenn er
                                         *   den Verlust bemerkt und setzt die Verlustanzeige wieder zurück. Der Zugriff auf dieses Flag
                                         *   ist zwischen Client und TrcServer nicht koordiniert, deshalb kann (in seltenen Fällen)
                                         *   der "...TRACES LOST..." Text an einer falschen Stelle erscheinen.
                                         */

    unsigned char bFillCount;           /*!< Anzahl der Textzeichen im Zeilen Puffer. */
    char buf[SL_TRC_MAX_TRACE];         /*!< Zeilen Puffer, hält den Trace Text ohne abschließende. 0 */

} SlTrcShmLine;




/*! \struct SlTrcTracePointEnv
 *  Transportstruktur für Standardinformationen. Standardinformationen werden vom Applikationsprogrammierer nicht an die Trace
 *  erzeugende Funktion übergeben. Deshalb läuft der Transport nach folgendem Muster. Nachdem die Tracebedingungen ausgewertet
 *  sind, und damit feststeht, daß eine Traceausgabe stattfindet, wird vor dem eigentlichen Ausgabeaufruf die Methode
 *  SlTrc::setLineFile aufgerufen. Diese Funktion belegt eine der existierenden Instanzen von SlTrcTracePointEnv mit den
 *  Standardinformationen und liefert den dieser Instanz zugeordneten Prozedur Zeiger zurück, mit dem hinterher die Traceausgabe
 *  vorgenommen wird. Die Funktion kennt ihren Puffer und kann nun zur Ausgabe die arbeitende Tracefunktion aufrufen, wobei dieser
 *  Funktion zusätzlich ein Zeiger auf die Standardinformationen übergebbar ist. Die arbeitende Tracefunktion übernimmt die
 *  Standardinformation und gibt die SlTrcTracePointEnv_ sofort wieder für die nächste Benutzung frei. Mehrere Sätze von
 *  Standardinformation und Traceausgabe Funktion sind erforderlich, da mehrere Threads gleichzeitig und unkoordiniert ausgaben
 *  vornehmen können sollen.
 */
typedef struct SlTrcTracePointEnv_
{
  const char* czFile4NextTrace;   /*!< Zeiger auf den null terminierten Namen der Quelldatei, die den Trace Ausgabeaufruf enthält. */
  int iLine4NextTrace;            /*!< Zeilennummer des Trace Ausgabeaufrufs in der Quelldatei. */
  int iBitLevel4NextTrace;        /*!< TraceBit und TraceLevel des Trace Ausgabeaufrufes. */
  unsigned uStackP4NextTrace;     /*!< Stack Zeiger während der Traceausgabe. */
  bool bDebug;                    /*!< Announces debug traces. */
  int iAllocator;                 /*!< Atomar zu verändendes Allokierungs Flag (0:frei, 1:belegt) für die vorliegende Instanz. */
  SlTrc* pSlTrc;                  /*!< Zeiger auf die SlTc Instanz. */
  const char* pczModuleName;      /*!< Changes the name of the Module if set. */

} SlTrcTracePointEnv;





//! Daten der SolutionLine Trace Support Implementierungs Klasse.
/*! Die Klasse SlTrc_ hält die Daten der Klasse SlTrc und verbirgt sie somit vor dem TrcServer. Die Daten sind ausschließlich
 *  Skalare oder Zeiger.
 */
class SL_TRC_EXPORT SlTrc_
{
protected:
  // per process data
  static struct SlTrcStaticObjects_* g_pObjects;  /*!< Zeiger auf das Objekt mit nichtskalaren globalen Objekten. */
  static SlTrcTracePointEnv g_tracePointEnv[4];   /*!< Puffer zum Transport von Standardinformation. */
  static SlTrcShmAdmin* g_pTrace;                 /*!< Zeiger auf die Verwaltungsinformation des Shared Mememory Bereiches. */
  static SlTrcShmLine*  g_pLines;                 /*!< Zeiger auf das Zeilen Array (Trace Puffer). */
  static unsigned*      g_puTrcFlags;             /*!< Zeiger auf die TraceBits des Moduls SlTrc. */
  static int            g_iInitCounter;           /*!< Anzahl der init Aufrufe auf dem Stack. */
  static unsigned       g_uNull;                  /*!< Eine allgemein einsetzbare 0 (z.B. für Referenzen). */
  static unsigned       g_uPid;                   /*!< Der Process ID des Prozesses. */
  static bool           g_bUnsuccessfullWait;     /*!< Markiert, daß dieser Prozess bereits einmal ohne Erfolg auf eine freie Shared
                                           *   Memory Zeile gewartet hat. Bei nachfolgenden Zeilen wird nicht mehr gewartet
                                           *   bis wieder Platz im Shared Memory entdeckt wird. Dieser Mechanismus
                                           *   soll die Programme lauffähig halten, wenn der Solution Line Trace Support
                                           *   falsch installiert ist und nicht gestartet werden kann.
                                           */
  static bool g_bIsServer;                /*!< true for SlTrcServer, used to limit recursions. */

  // time statics
  static char g_pcTimeBuffer[30];         /*!< Globaler Puffer, in dem die Rückgabe Strings von Zeitfunktionen abgelegt werden. */
  static unsigned g_uTaoLastFlags;        /*!< Last SlTrc tracebit state needed for detecting changes of the Tao-Enable-Bit. */

  // per instance data
  const char* m_pczModuleName;            /*!< Modulname für Tracezwecke. */
  unsigned *m_puModuleBits;               /*!< Zeiger auf die modulspezifischen TraceBits. */

  static QHash<unsigned, unsigned>* g_pQString2czEnabledHash;  /*!< pointer to hash table with info for use of QString2cz() per thread */
  static QMutex* g_pQString2czEnabledHashMtx;              /*!< pointer to mutex to protect access to g_pQString2czEnabledLst from multiple threads */
  static struct SlTrcSvcClientData_ *g_pSvcClientData;
};

class SL_TRC_EXPORT SlTrc;
/*! Prozedurpointer für die SlTrc-Objektzugriffsfunktion. */
typedef SlTrc* (*SlTrcObjectAccess)(void);

//! Die SolutionLine Trace Support Implementierungs Klasse.
/*! Die Klasse SlTrc implementiert die Zugriffe auf das Shared Memory. Das Shared Memory umfaßt einen allgemeinen Verwaltungsbereich
 *  (SlTrcShmAdmin), den Trace Puffer Bereich (Array of SlTrcShmLine) und den TraceBit Bereich, in dem die TraceBits der Module hinterlegt
 *  sind. In den Statischen Daten sind Informationen hinterlegt, die für alle Module gemeinsam verwendet werden. Im den Instanzdaten
 *  befinden sich modulspezifische Daten.
 *
 *  Die modulspezifische Instanz entsteht beim ersten Zugriff auf den SolutionLine Trace Support eines Muduls. Deshalb kann auch bereits
 *  während der Instantiierung von Globalvariablen Trace abgesondert werden. Die SlTrc Instanz und alle ihre statischen Daten
 *  werden nicht mehr freigegeben. Deshalb kann auch das Verschwinden von statischen Daten im Trace verfolgt werden.
 *
 *  Die Klasse SlTrc ist logisch gesehen eine Hilfsklasse des TrcServers und gibt diesem freinen Zugriff auf interne Funtionen. Um
 *  die den direkten Datenzugriff des TrcServer aber trotzdem zu unterbinden,
 *  sind die Daten in der Superklasse SlTrc_ deklariert. Die Klienten und der Server sehen damit unterschiedliche wohldefinierte
 *  Interfaces.
 */
class SL_TRC_EXPORT SlTrc : protected SlTrc_
{
  friend class SlTrc_Log_Trap;
  friend class SlTrcFormsLogic;      // HMI business logic for trace forms
  friend class SLTrcTraceOn;         // sltrctraceon tool
  friend class SlTrcServer;         // The TrcServer gets access to private functions, but not access to data representation.
  friend struct SlTrcStaticObjects_;// These are static data of SlTrc and are logically belonging to SlTrc.
  friend SlTrc* SL_TRC_NAMESPACE::TrcObj(); // logically a module specific member of class SlTrc
  friend bool SL_TRC_NAMESPACE::ifTrace(unsigned uLevel, unsigned uBits); // logically a module specific member of class SlTrc
  friend bool SL_TRC_NAMESPACE::ifTraceAny(unsigned uLevel, unsigned uBits); // logically a module specific member of class SlTrc
  #ifndef SL_TRC_TRC
  friend bool SLTrcSlTrcNamespace::ifTrace(unsigned uLevel, unsigned uBits); // logically a module specific member of class SlTrc
  friend bool SLTrcSlTrcNamespace::ifTraceAny(unsigned uLevel, unsigned uBits); // logically a module specific member of class SlTrc
  #endif // SL_TRC_TRC

  /*! Ein Zeiger auf Trace Prozeduren */
  typedef SL_TRC_PRINT* SL_TRC_PP;

private:
  //! Entnimmt eine Zeile aus dem Shared Memory.
  /*! \param  Puffer in dem der Text der Zeile abgelegt wird.
   *  \retval Wenn >=0: Länge des im Puffer abgelgten Strings, wenn <0: Shared Memory leer oder Fehlerzustand.
   */
  int get(char* buf);

  //! Läßt einen am Shared Memory wartenden Client weiterlaufen.
  static void releaseClient();

public:
  /*! Transport Container für Traceaufruf Argumente */
  typedef struct _MANYARGS { char * any[20]; } MANYARGS;

  // client side (enter a trace into the ouputbuffer)
  //! Formatiert ein eine Tracezeile und gibt sie aus.
  /*! Das Hinzufügen von ortspezifischer Standardinformation wird unterdrückt.
   *  \param Formatangabe entsprechend dem printf Aufruf der C++ Standardbibliothek. Auch die weiteren Parameter
   *  des Aufrufs entsprechen den Parametern eines printf Aufrufs. Es muß strend darauf geachtet werden, daß die
   *  maximale Zeichenzahl (SL_TRC_MAX_TRACE) nicht überschritten wird. Deshalb sollte bei Textausgaben grundsätzlich
   *  eine längenbegrenzende Formatspezifikation verwendet werden (z.B. "%.100s").
   */
  void trace(const char* fmt, ...);

  //! Formatiert ein eine Tracezeile und verwendet bei der Ausgabe einen geänderten Modulnamen.
  /*! Das Hinzufügen von ortspezifischer Standardinformation wird unterdrückt.
   *  \param Formatangabe entsprechend dem printf Aufruf der C++ Standardbibliothek. Auch die weiteren Parameter
   *  des Aufrufs entsprechen den Parametern eines printf Aufrufs. Es muß strend darauf geachtet werden, daß die
   *  maximale Zeichenzahl (SL_TRC_MAX_TRACE) nicht überschritten wird. Deshalb sollte bei Textausgaben grundsätzlich
   *  eine längenbegrenzende Formatspezifikation verwendet werden (z.B. "%.100s").
   */
  void traceModule(const char* czModule, const char* fmt, ...);

  //! Transportiert die Standardinformation in den Trace Aufruf.
  /*! \param Zeilennummer des Trace Statements.
   *  \param Filename der Quelldatei.
   *  \param TraceBit- und TraceLevel-Spezifikation des Trace Aufrufs.
   *  \retval Prozedurzeiger auf die Trace Funktion, die unmittelbar anschließend zwingend aufgerufen werden muß.
   */
  SL_TRC_PP setLineFile(int iLin ,const char* czFil, int iBitLevel, bool bDebug);

  //! Prozeduraufruf ohne Wirkung
  static void nop();

  //! Always true
  static bool always();

  //! Always false
  static bool never();

  //! Trace eines Binär Puffers.
  /*! Die Bytes des Puffers werden hexadezimal und ASCII ausgegeben. Jeder Zeile wird ein Text vorangestellt.
   *  \param Der jeder Zeile vorangestellte Text.
   *  \param Zeiger auf den Datenpuffer.
   *  \param Anzahl der Bytes im Daten Puffer.
   */
  void trcHex(const char* szModule, const char* szLead, const void* pvData, int len);

  //! Zugriff auf den Modulnamen, der bei der Trace Ausgabe verwendet wird
  const char* moduleName();

  //! Zugriff auf den Hostnamen, der bei der Trace Ausgabe verwendet wird
  static const char* hostName();

  //! Zugriff auf den kompletten Hostnamen
  static const QString& fullHostName();

  //! Zugriff auf den kompletten Hostnamen
  static const QString& shortHostName();

  //! Zugriff auf den Hostnamen, der bei der Trace Ausgabe verwendet wird
  static unsigned ipAddr();

  // Zugriff auf TraceBits
  //! Zugriff auf die modulspezifischen TraceBits.
  /*! \retval Referenz auf die modulspezifischen TraceBits und den modulspezifischen TraceLevel. Der TraceLevel liegt
   * in den obersten 4 Bit.
   */
  unsigned& bits();

  //! Zugriff auf ServerBits im Shared Memory.
  /*! \retval Referenz auf die ServerBits.
   */
  unsigned& serverBits();

  //! Zugriff auf den Filter Prozess- oder Thread-ID im Shared Memory.
  /*! \retval Referenz auf den Prozess- oder Thread-ID.
   */
  unsigned& filterId();

  //! Zugriff auf die TraceBits des Moduls SlTrc.
  /*! \retval Referenz auf die TraceBits des Moduls SlTrc.
   */
  unsigned& commonBits();

  //! Schnellzugriff auf den gerade gültigen Prozess ID.
  /*! \retval Prozess ID.
   */
  static unsigned pid();

  //! Größe des Shared Memory in Bytes.
  /*! \retval Minmalgröße des Shared Memory in Bytes.
   */
  int shmSize();

  //! Check if working.
  bool ok() const;

  //! Wandlung von QString nach "const char*"
  static const char* QString2cz(
    const QString& str);                /*!< Qstring to be converted. */

  // time routines
  //! Millisekunden genaue Uhr.
  /*! Millisekunden genaue Zeitmessungen innerhalb von SolutionLine sollten einheitlich mit dieser Uhr vorgenommen werden.
   *  \retval Uhrzeit in Millisekunden.
   */
  static unsigned ms();

  //! Millisekunden genauer Zeittext.
  /*! Alle im Trace vorkommende Zeitstempel sollten mit dieser Prozedur erzeugt werden (Einheitliches Zeit Pattern und
   *  vergleichbare Zeiten).
   *  \param Rückgabe der Uhrzeit in Millisekunden, die dem gelieferten Text entspricht. Gleiche Zeitkodierung wie beim
   *  Aufruf von ms().
   *  \retval Zeitstring
   */
  static const char* at(unsigned *_time = 0);
  static const char* atDate(unsigned *_time = 0);

  //! Millisekunden genauer Zeittext mit zusätzlicher Zeitdauer Angabe.
  /*! Berechnet aus der übergebenen Startzeit und augenblicklichen Zeit eine Zeitdauer. Liefert einen String, der sowohl
   *  Zeit als auch Zeitdauer im Klartext enthält. Alle im Trace vorkommende Zeitstempel mit Zeitdauer Angabe sollten
   *  mit dieser Prozedur erzeugt werden (Einheitliches Pattern und vergleichbare Zeiten).
   *  \param Uhrzeit in Millisekunden wie sie von ms() oder at() geliefert wird.
   *  \retval String mit Zeitpunkt und Zeitdauer.
   */
  static const char* ativ(unsigned time);

  //! Millisekunden genauer Zeittext mit zusätzlicher Zeitdauer Angabe.
  /*! Berechnet aus der übergebenen Startzeit und augenblicklichen Zeit eine Zeitdauer. Liefert einen String, der sowohl
   *  Zeit als auch Zeitdauer im Klartext enthält. Alle im Trace vorkommende Zeitstempel mit Zeitdauer Angabe sollten
   *  mit dieser Prozedur erzeugt werden (Einheitliches Pattern und vergleichbare Zeiten). Im Unterschied zu
   *  const char* ativ(unsigned time) wird die übergebene Zeit auf den augenblicklichen Zeitpunkt gestellt (Kettenmaß).
   *  \param Uhrzeit in Millisekunden wie sie von ms() oder at() geliefert wird.
   *  \retval String mit Zeitpunkt und Zeitdauer.
   */
  static const char* ativ(unsigned* time);

  // other support
  //! Starten eines Prozesses.
  /*! \param Kommandozeile.
   *  \retval Bei Fehler -1 (errno liefert Details)
   */
  static int spawnProcess(const char* cmdLine);

  //! Hilfs Trace Funktion für Tests innerhalb des SlTrc Moduls und des TrcServers.
  /*! \param Die Parameter entsprechen den printf Parametern der C++ Standard Library.
   */
  static void ods(const char* fmt, ...);

  //! Atomares Addieren eines Wertes.
  /*! Die hauptsächliche Prozessübergreifende Koordinierungsfunktion im Modul SlTrc wird hier für den Einsatz an anderer
   *  Stelle allgemein zugreifbar gemacht. Die Funktion addiert atomar einen Wert auf eine Variable und liefert den Ergebniswert
   *  der atomaren Addition.
   *  \param Zeiger auf die Variable, deren Wert verändert wird.
   *  \param Wert der auf die Variable addiert wird.
   *  \param Ergebniswert zum Zeitpunkt der atomaren Addition.
   */
  static int atomicAdd(volatile int* iCommon, int iValue);

  static unsigned int atomicAdd(volatile unsigned int * iCommon, int iVal);

  //! Thread Suspend für eine wählbare Zeit.
  /*! \param Zeitdauer der Suspendierung.
   */
  static void sleep(int iMilliSecs);

  //! Prüft, ob Threadfilter durchlässig ist.
  static bool threadMatch(unsigned uFilter);

  //! Indicates if initialization is running
  static bool isInitializing();

  //! Access directory used for sltrc persistant files.
  static QString getDirectory();

  //! Markiert den Prozess als SlTrcServer
  static void setServer();

  //! Return SlTrc creator of module SlTrc
  static SlTrcObjectAccess slTrcObj();

  //! Start of module/bit enumeration
  static char* getFirstModule(
    unsigned** ppuBits);            /*!< Pointer to bits is stored here. */

  //! Position to next entry of module/bit enumeration.
  static char* getNextModule(
    char* p,                        /*!< Returnvalue of a previous getFirstModuleBits or getNextModuleBits call. */
    unsigned** ppuBits);            /*!< Pointer to bits is stored here. */

  //! Find modulebits in module admin area.
  static char* findModule(
    const char* czModule,           /*!< Module searched for. */
    unsigned** ppuBits);            /*!< Pointer to module bits is stored here. */

  //! Find modulebits in module admin area.
  static char* findModule(
    const QString& strModule,       /*!< Module searched for. */
    unsigned** ppuBits);            /*!< Pointer to module bits is stored here. */

  //! Acquire file sink size in kilobytes.
  static unsigned fileSize();

  //! Set file sink size in kilobytes.
  static void setFileSize(
    unsigned uNewSize);             /*!< New file size. */

  static unsigned numTraceFiles(void);

  static void setNumTraceFiles(unsigned uNewNumTraceFiles);

  static unsigned extendedBits(void);

  static void setExtendedBits(unsigned uNewExtendedBits);

  //! Set linecount within shm for next reboot.
  static void setRequiredLineCount(
    int iNewLineCount);             /*!< Number of lines in shm after next reboot. */

  // compact settings access ========================================================================
  // changed interface flavor

  //! Read a settings string.
  static QString getSettingsString(
    SlHmiSettingsQt& settings,      /*!< Settings object to be used for access of the settings entry. */
    const QString& strKey,          /*!< Name of the settings key. */
    const QString& strEntry,        /*!< Name of the settings entry. */
    const QString& strDefault);     /*!< Value to be returned if any access problem occurs. */

  //! Read settings fixed number.
  static sltrcInt64 getSettingsInt(
    SlHmiSettingsQt& settings,      /*!< Settings object to be used for access of the settings entry. */
    const QString& strKey,          /*!< Name of the settings key. */
    const QString& strEntry,        /*!< Name of the settings entry. */
    sltrcInt64 iDefault);           /*!< Value to be returned if any access problem occurs. */

  //! Access key entries.
  static QStringList getSettingsEntries(
    SlHmiSettingsQt& settings,      /*!< Settings object to be used for access of the settings entry. */
    const QString& strKey);         /*!< Name of the settings key. */

  //! Write change settings integer.
  /*! Note: Checks settings contents and writes only if modification needed.
   */
  static bool writeSettingsInt(
    SlHmiSettingsQt& settings,      /*!< Settings object to be used for access of the settings entry. */
    const QString& strKey,          /*!< Name of the settings key. */
    const QString& strEntry,        /*!< Name of the settings entry. */
    sltrcInt64 iValue,              /*!< Value to be assured in entry. */
    const QString& strComment = SlTrc::emptyQString());  /*!< Some kind of commentary. */

  //! Write settings string.
  /*! Note: Checks settings contents and writes only if modification needed.
   */
  static bool writeSettingsString(
    SlHmiSettingsQt& settings,      /*!< Settings object to be used for access of the settings entry. */
    const QString& strKey,          /*!< Name of the settings key. */
    const QString& strEntry,        /*!< Name of the settings entry. */
    const QString& strValue,        /*!< Value to be assured in entry. */
    const QString& strComment = SlTrc::emptyQString());  /*!< Some kind of commentary. */

  //! Forced write settings string
  /*! Note: Writes setting even if modification not needed.
   */
  static bool writeSettingsStringForced(
    SlHmiSettingsQt& settings,      /*!< Settings object to be used for access of the settings entry. */
    const QString& strKey,          /*!< Name of the settings key. */
    const QString& strEntry,        /*!< Name of the settings entry. */
    const QString& strValue,        /*!< Value to be written to entry. */
    const QString& strComment = SlTrc::emptyQString(), /*!< Some kind of commentary. */
    int iDontCare = 0);             /*!< Trace control. */

  //! Delete settings entry.
  static bool deleteSettingsEntry(
    SlHmiSettingsQt& settings,      /*!< Settings object to be used for access of the settings entry. */
    const QString& strKey,          /*!< Name of the settings key. */
    const QString& strEntry);       /*!< Name of the settings entry. */

  //! Delete settings section.
  static bool deleteSettingsSection(
    SlHmiSettingsQt& settings,      /*!< Settings object to be used for access of the settings entry. */
    const QString& strKey);         /*!< Name of the settings key. */

  //! Search for the highest priority file.
  static QString searchFile(
    SlHmiFileAccessQt& fileAccess,  /*!< File access object to be used. */
    const QString& strFileName,     /*!< Filename. */
    const QString& strSubPath,      /*!< Subdirectory. */
    const QString& strDefault = SlTrc::emptyQString()); /*!< Result on errors. */

  //! Writable file within HMI-paths.
  static QString hmiSaveFileName(
    SlHmiFileAccessQt& fileAccess,  /*!< File access object to be used. */
    const QString& strFileName,     /*!< Filename. */
    const QString& strSubPath);     /*!< Subdirectory. */

  //! An empty QString ref.
  /*! Needed to prevent include of Qt-files.
   */
  static const QString& emptyQString();

  // key bitset interface =============================================================================

  //! KeyBitSet activation called when the corresponding key arrives.
  static void activateKeyBitSet(const bool bReadDefaultKeyBitSetFile = true);

  //! KeyBitSet deactivation called when the corresponding key arrives.
  static void deactivateKeyBitSet();

  //! reads the trace configuration from sltrc_keybitset.ini file
  static int  readTraceConfigFromFile(const QString& rszFilePath = SlTrc::emptyQString());

  //! Ask if not protected bits set.
  static bool active();

  //! obsolete, will be removed when next binary incompatibility is allowed
  static void enableQString2cz();

protected:
  friend class SlTrcFriend;

  // internal interfaces of this class
  //! Konstruktor
  /*! Die Existenz dieses (protected) Konstuktors verhindert, daß die Klasse SlTrc allgemein instantiierbar ist.
   */
  SlTrc(
    const char* pczModuleName,            /*!< Modulname für Tracezwecke. */
    unsigned *puModuleBits);              /*!< Zeiger auf die modulspezifischen TraceBits. */

  //! Destructor.
  ~SlTrc();

  //! Initialisierung
  /*! Wird beim ersten Aufruf einer (public) TraceFunktion je Modul aufgerufen. Übernimmt die Manifestierungskonstanten
   *  in die Konfigurationsdatei, allokiert bei Bedarf einen TraceBit Index, allokiert, öffnet und intialisiert bei Bedarf
   *  den Shared Memory Bereich, Startet bei Bedarf einen Server und sorgt dafür, daß alle Global- und Instanzvariablen
   *  initialisiert sind.
   *  \param Modulname.
   *  \param Array von 28 Checkbox Bezeichnern.
   *  \param Array von 28 Tooltip Texten für die Checkboxen.
   *  \param Zeiger auf den globalen Instanz Zeiger.
   *  \param Preferred bit setting of this module.
   *  \param Interface bit setting of this module.
   *  \retval Zeiger auf die neu eingerichtete SlTrc Instanz.
   */
  static void init(const char* czClassName, const char** szCheckBoxText, const char** szCheckBoxTextExtended, SlTrc** ppTrc
    , unsigned uPreferredBits, unsigned uInterfaceBits);

  /*! Starten des Traceservers
  *   Wird von sltrcforms verwendet um den Traceservers zu starten.
  */
  static void startTraceServer();

  /*! turn on/off tracing
  *   \param bool bSwitch
  *   true turns tracing on, false deactivates the trace
  */
  static void tracingOnOff(bool bSwitch);


  //! Initialisierung der Caches in der Funktion ifTrace.
  /*! Wird von der Funktion ifTrace zur Vorbesetzung seiner gecachten Information aufgerufen.
   *  \param Referenz für die Cache Information.
   *  \param Zeiger auf die Instanzfunktion.
   */
  static void initCachedInfo(SlTrcCachedInfo &cachedInfo, SlTrcObjectAccess acc);

  //! Detail evaluation of the trace condition and cache initialization.
  static bool accurateIf(
    unsigned uLevel,                    /*!< Required Trace Level. */
    unsigned uBits,                     /*!< Tracebits required. */
    SlTrcCachedInfo &cachedInfo,        /*!< Cached info (potentially uninitialized!). */
    SlTrcObjectAccess acc);             /*!< Access to the related SlTrc object. */

  //! Detail evaluation of the trace condition and cache initialization.
  static bool accurateIfAny(
    unsigned uLevel,                    /*!< Required Trace Level. */
    unsigned uBits,                     /*!< Tracebits required. */
    SlTrcCachedInfo &cachedInfo,        /*!< Cached info (potentially uninitialized!). */
    SlTrcObjectAccess acc);             /*!< Access to the related SlTrc object. */

  //! Interne Tracefunktion.
  /*! Implementierung von Formatierung und Anreicherung mit Standardinformation. Alle formatierenden Trace Aufrufe landen zur Ausführung hier.
   *  \param Zeiger auf den Transportpuffer für die Standardinformation.
   *  \param Zeiger auf den FormatString Zeiger des ursprünglichen Trace Aufrufes.
   */
  void _trace(SlTrcTracePointEnv* pEnv, const char** fmt);

  //! Erzeugt TraceZeile im Shared Memory .
  /*! Splittet die TraceZeile in Teile der Größe SL_TRC_MAX_TRACE und ruft _append auf.
   *  \param Zeiger auf den Tracetext.
   *  \param Länge des TraceTextes.
   *  \retval True, wenn erfolgreich
   */
  bool append(char* buf, int l);    // entering a buffer

  //! Prozess Koordinierung des Einhängens einer Zeile im Shared Memory.
  /*! Allokiert eine Zeile, falls Platz im Shared Memory ist, und kopiert den Zeilentext. Falls kein Platz ist, werden die Prozesse/Threads
   *  über einen Mutex sequentialisiert und an einer Semaphore blockiert. Hinweis: Wenn ein Prozess in dieser Prozedur beendet wird
   *  (z.B. über Debugger), so kann u.U. prozessübergreifend die Traceausgabe blockieren. In diesem Fall müssen alle tracenden
   *  Applikationen und SlTrc.exe beendet werden. Anschließend ist /tmp/sltrc.shm zu löschen.
   *  \param Zeiger auf den Tracetext.
   *  \param Länge des TraceTextes.
   *  \retval True, wenn erfolgreich
   */
  bool _append(char* buf, int l);   // entering core

  //! Eine der Tracefunktionen auf Anwenderbene.
  /*! Die Tracefunktionen trace0, trace1, trace2, trace3 werden auf Anwenderebene aufgerufen und transportieren die Formatspezifikation,
   *  die Anwender Parameter und einen Zeiger auf die Standardinformation in die eigentliche Trace Prozedur _trace.
   *  \param Aufrufparameter wie printf der Standard Library.
   */
  static void trace0(const char* fmt, ...);

  //! Eine der Tracefunktionen auf Anwenderbene.
  /*! @see trace0(). */
  static void trace1(const char* fmt, ...);

  //! Eine der Tracefunktionen auf Anwenderbene.
  /*! @see trace0(). */
  static void trace2(const char* fmt, ...);

  //! Eine der Tracefunktionen auf Anwenderbene.
  /*! @see trace0(). */
  static void trace3(const char* fmt, ...);

  //! Trägt 16 Bit in einen Char Puffer ein.
  /*! \param Zeiger auf den Start des binären Puffers.
   *  \param Länge der Daten im binären Puffer.
   *  \param Offset der einzutagenden Bytes im binären Puffer
   *  \param Zeiger auf die Stelle im Ascii-Puffer, an der die Hexadarstellun einzutragen ist.
   *  \param Zeiger auf die Stelle im Ascii-Puffer, an der eine ascii-Darstellung einzutragen ist.
   */
  static void trcHexWord(const unsigned char* pBin, int iBinLen, int iBinOffset, unsigned char* ascOut, unsigned char* charOut);

  //! prüft, ob ein File anlegbar ist.
  /*! \param Pfadname des Files.
   */
  static bool assureCreateFile(const char* fil);

  //! Erzeugen eines Directory Pfades.
  /*! Stellt sicher, daß nach dem Aufruf die gewünschte Directory existiert und daß in dieser
   *  Directory Dateien erzeugt werden können.
   *  \param Pfadname der Directory.
   *  \param Name der PrüfDatei.
   *  \retval Erfolg des Aufrufs.
   */
  static bool assureDir(const char* dir);

  //! Zeitbegrenztes Warten auf Ausgabe auf das Shared Memory.
  /*! \param Zeitobergrenze für den Wartevorgang.
   */
  bool waitContinue(unsigned uMilliSecs);

  //! Zeitgegrenztes Warten des Servers auf Traceausgabe in das Shared Memory
  /*! \param Zeitobergrenze für den Wartevorgang.
   */
  static void waitTrace(unsigned uMilliSecs);

  //! Regelmäßige Aktivitäten bei ProgrammStart und TraceAusgabe.
  void eventActivities();

  //! Compute hashkey signature over module texts.
  static unsigned hashKey(
    const char** szCheckBoxText,    /*!< Checkbox label texts. */
    const char** szCheckBoxTextExtended, /*!< Tooltip texts. */
    unsigned uPreferredBits,        /*!< Proposed standard bitsetting for clients. */
    unsigned uInterfaceBits);       /*!< Standard bitsetting for tracing module interfaces. */

  //! Add string to hashkey
  static unsigned hashKey(
    const char* pcz,                /*!< String to be added to hashkey. */
    unsigned uHashKey);             /*!< Hashkey input. */

  //! Add unsigned to hashkey
  static unsigned hashKey(
    unsigned uValue,                /*!< Unsigned to be added to hashkey. */
    unsigned uHashKey);             /*!< Hashkey input. */

  //! Create tracebits/module admin info and deliver trace bits.
  static unsigned* allocateModule(
    char* pStart,                   /*!< Start of a module's admin area. */
    const char* czClassName);       /*!< Module name. */

  //! Asyncronously flush module admin area of shm to disk.
  static void flushShm();

  //! Adjust linecount for filling up the last page
  static void shmAdjust(
    int iLineCount,                 /*!< Line count to be adjusted. */
    int& iAdjustedLineCount,        /*!< Adjusted line count. */
    int& iAdjustedShmSize);         /*!< Shm size related to the adjusted line count. */

  //! Determine the user requested number of tracelines in shm.
  static int getConfigShmSize(
    int& iLineCount,                /*!< User requested number of tracelines in the shm. */
    unsigned& uFileSize);           /*!< Actual file sink size. */

  //! Read the shm size of an existing shm and deliver the user requested size.
  /*! \retval Actual shm size.
   */
  static int getExistingShmSize(
    int& iLineCount,                /*!< Actual number of tracelines in the shm. */
    int& iShmSizeRequired,          /*!< User requested size of shm. */
    int& iLineCountRequired,        /*!< User requested number of tracelines in the shm. */
    unsigned& uFileSize);           /*!< Actual file sink size. */

  //! Combine settings value with settings comment
  static QString settingsCombine(
    const QString& strValue,          /*!< Value string. */
    const QString& strEntry,          /*!< Entry string. */
    const QString& strComment);       /*!< Comment string. */

  //! Conditioning of a settings string.
  static QString settingsStringConditioning(
    const QString& str);              /*!< Value string to be conditioned. */
};

#define SL_TRC_SET_PTR_NOTUSABLE(XXP) (reinterpret_cast<void*&>(XXP) = reinterpret_cast<void*>(1))
#define SL_TRC_IS_NOTUSABLE(XXP) (reinterpret_cast<sltrcUInt64>(XXP) <= 1)
#define SL_TRC_IS_EXACTLY_NOTUSABLE(XXP) (reinterpret_cast<sltrcUInt64>(XXP) == 1)

// these logical members of SlTrc are intentionally not in the sltrc.i file, because they are not intended
// to be translated in a .cpp context (which sltrc.i is!)
namespace SL_TRC_NAMESPACE
{
  //! Zugriff auf die SlTrc Instanz.
  /*! Ruft beim ersten Aufruf die initialisierungsroutine auf. Die Prozedur liegt in einem modulspezifischen Namespace.
   *  \retval Zeiger auf die modulspezifische SlTrc Instanz.
   */
  inline SlTrc* TrcObj()
  {
    static SlTrc* g_pTrc = 0;

    if(SL_TRC_IS_NOTUSABLE(g_pTrc))
    {
      if(SL_TRC_IS_EXACTLY_NOTUSABLE(g_pTrc))
      {
        // trc initialization failed
        return 0;
      }

      // initialize trace
      const char* szCheckBoxText[28] =
      {
        SL_TRC_BIT0_TEXT,     SL_TRC_BIT1_TEXT,     SL_TRC_BIT2_TEXT,     SL_TRC_BIT3_TEXT,
        SL_TRC_BIT4_TEXT,     SL_TRC_BIT5_TEXT,     SL_TRC_BIT6_TEXT,     SL_TRC_BIT7_TEXT,
        SL_TRC_BIT8_TEXT,     SL_TRC_BIT9_TEXT,     SL_TRC_BIT10_TEXT,    SL_TRC_BIT11_TEXT,
        SL_TRC_BIT12_TEXT,    SL_TRC_BIT13_TEXT,    SL_TRC_BIT14_TEXT,    SL_TRC_BIT15_TEXT,
        SL_TRC_BIT16_TEXT,    SL_TRC_BIT17_TEXT,    SL_TRC_BIT18_TEXT,    SL_TRC_BIT19_TEXT,
        SL_TRC_BIT20_TEXT,    SL_TRC_BIT21_TEXT,    SL_TRC_BIT22_TEXT,    SL_TRC_BIT23_TEXT,
        SL_TRC_BIT24_TEXT,    SL_TRC_BIT25_TEXT,    SL_TRC_BIT26_TEXT,    SL_TRC_BIT27_TEXT
      };
      const char* szCheckBoxTextExtended[28] =
      {
        SL_TRC_BIT0_TOOLTIP,  SL_TRC_BIT1_TOOLTIP,  SL_TRC_BIT2_TOOLTIP,  SL_TRC_BIT3_TOOLTIP,
        SL_TRC_BIT4_TOOLTIP,  SL_TRC_BIT5_TOOLTIP,  SL_TRC_BIT6_TOOLTIP,  SL_TRC_BIT7_TOOLTIP,
        SL_TRC_BIT8_TOOLTIP,  SL_TRC_BIT9_TOOLTIP,  SL_TRC_BIT10_TOOLTIP, SL_TRC_BIT11_TOOLTIP,
        SL_TRC_BIT12_TOOLTIP, SL_TRC_BIT13_TOOLTIP, SL_TRC_BIT14_TOOLTIP, SL_TRC_BIT15_TOOLTIP,
        SL_TRC_BIT16_TOOLTIP, SL_TRC_BIT17_TOOLTIP, SL_TRC_BIT18_TOOLTIP, SL_TRC_BIT19_TOOLTIP,
        SL_TRC_BIT20_TOOLTIP, SL_TRC_BIT21_TOOLTIP, SL_TRC_BIT22_TOOLTIP, SL_TRC_BIT23_TOOLTIP,
        SL_TRC_BIT24_TOOLTIP, SL_TRC_BIT25_TOOLTIP, SL_TRC_BIT26_TOOLTIP, SL_TRC_BIT27_TOOLTIP
      };

      SlTrc::init(SL_TRC_STRINGIZED_MODULE, szCheckBoxText, szCheckBoxTextExtended, &g_pTrc
        , SL_TRC_PREFERRED, SL_TRC_INTERFACE);
    }

    return g_pTrc;
  }


  //! Schnellprüfung, ob die Traceausgabe ein- oder ausgeschaltet ist..
  /*! Die Prozedur liegt in einem modulspezifischen Namespace.
   *  \retval Zeiger auf die modulspezifische SlTrc Instanz.
   */
  SL_TRC_ALWAYS_INLINE  bool ifTrace(unsigned uLevel, unsigned uBits)
  {
    // here we get direct (not throu pointer) access to all data needed during check.
    // further we have no initialization which is called each time we enter this routine.
    // we cant put this static data outside a routine, because namespace globals are not supported by c++.
    static unsigned g_uAll = 0x7fffffff;
    static unsigned g_uNull = 0;
    static SlTrcCachedInfo g_cachedInfo = { &g_uAll, &g_uNull, 0 };

    return
      // first we take a rough check of bit coincidence (detail check of bits is done in accurateIf)
      // in 99% of calls the processor leaves here correctly at the first check and we need not do more costly checks.
      (uBits == (uBits & *g_cachedInfo.m_puFlags))                  // most filtering test
      // check general trace on/off
      && (0 == (*g_cachedInfo.m_puCommonFlags & SL_TRC_FILTER_OFF)) // second most filtering test
      // an early levelcheck follows here
      && (*g_cachedInfo.m_puFlags >= uLevel)                        // third most filtering test
      // accurate check follows here in a procedure
      && SlTrc::accurateIf(uLevel, uBits, g_cachedInfo, &TrcObj);
  }

  //! Schnellprüfung, ob die Traceausgabe ein- oder ausgeschaltet ist (Anybit Variante).
  /*! Die Prozedur liegt in einem modulspezifischen Namespace.
   *  \retval Zeiger auf die modulspezifische SlTrc Instanz.
   */
  SL_TRC_ALWAYS_INLINE  bool ifTraceAny(unsigned uLevel, unsigned uBits)
  {
    // here we get direct (not throu pointer) access to all data needed during check.
    // further we have no initialization which is called each time we enter this routine.
    // we cant put this static data outside a routine, because namespace globals are not supported by c++.
    static unsigned g_uAll = 0x7fffffff;
    static unsigned g_uNull = 0;
    static SlTrcCachedInfo g_cachedInfo = { &g_uAll, &g_uNull, 0 };

    return
      // first we take a rough check of bit coincidence (detail check of bits is done in accurateIf)
      // in 99% of calls the processor leaves here correctly at the first check and we need not do more costly checks.
      (0 != (uBits & *g_cachedInfo.m_puFlags))                      // most filtering test
      // check general trace on/off
      && (0 == (*g_cachedInfo.m_puCommonFlags & SL_TRC_FILTER_OFF)) // second most filtering test
      // an early levelcheck follows here
      && (*g_cachedInfo.m_puFlags >= uLevel)                        // third most filtering test
      // accurate check follows here in a procedure
      && SlTrc::accurateIfAny(uLevel, uBits, g_cachedInfo, &TrcObj);
  }
}


#ifndef SL_TRC_TRC
namespace SLTrcSlTrcNamespace
{
  SL_TRC_ALWAYS_INLINE  bool ifTrace(unsigned uLevel, unsigned uBits)
  {
    // here we get direct (not throu pointer) access to all data needed during check.
    // further we have no initialization which is called each time we enter this routine.
    // we cant put this static data outside a routine, because namespace globals are not supported by c++.
    static unsigned g_uAll = 0x7fffffff;
    static unsigned g_uNull = 0;
    static SlTrcCachedInfo g_cachedInfo = { &g_uAll, &g_uNull, 0 };   // Preset TraceLevel=8, all bits set (enable all traces)

    return
      // first we take a rough check of bit coincidence (detail check of bits is done in accurateIf)
      // in 99% of calls the processor leaves here correctly at the first check and we can do more costly checks later.
      (uBits == (uBits & *g_cachedInfo.m_puFlags))                      // most filtering test
      // check general trace on/off
      && (0 == (*g_cachedInfo.m_puCommonFlags & SL_TRC_FILTER_OFF)) // second most filtering test
      // an early levelcheck follows here
      && (*g_cachedInfo.m_puFlags >= uLevel)                        // third most filtering test
      // accurate check follows here in a procedure
      && SlTrc::accurateIf(uLevel, uBits, g_cachedInfo, SlTrc::slTrcObj());
  }

  SL_TRC_ALWAYS_INLINE  bool ifTraceAny(unsigned uLevel, unsigned uBits)
  {
    // here we get direct (not throu pointer) access to all data needed during check.
    // further we have no initialization which is called each time we enter this routine.
    // we cant put this static data outside a routine, because namespace globals are not supported by c++.
    static unsigned g_uAll = 0x7fffffff;
    static unsigned g_uNull = 0;
    static SlTrcCachedInfo g_cachedInfo = { &g_uAll, &g_uNull, 0 };   // Preset TraceLevel=8, all bits set (enable all traces)

    return
      // first we take a rough check of bit coincidence (detail check of bits is done in accurateIf)
      // in 99% of calls the processor leaves here correctly at the first check and we can do more costly checks later.
      (0 != (uBits & *g_cachedInfo.m_puFlags))                      // most filtering test
      // check general trace on/off
      && (0 == (*g_cachedInfo.m_puCommonFlags & SL_TRC_FILTER_OFF)) // second most filtering test
      // an early levelcheck follows here
      && (*g_cachedInfo.m_puFlags >= uLevel)                        // third most filtering test
      // accurate check follows here in a procedure
      && SlTrc::accurateIfAny(uLevel, uBits, g_cachedInfo, SlTrc::slTrcObj());
  }
}
#endif // SL_TRC_TRC


#include "sltrc.i"

/*! \def SL_TRC_OBJ
 *  \brief Zeiger auf das modulspezifische SlTrc Objekt.
 */
#define SL_TRC_OBJ                    SL_TRC_NAMESPACE::TrcObj()

#endif // SL_TRC_OFF



#ifndef SL_TRC_NO_MACROS

// switch traceing off ??
#if !defined(SL_TRC_OFF)
  // macros ending with '_' expect a bitmask not a bit value
  // levels(1..8) are changed to numeric representation immediately before a call of a procedure

  // intern genutzte Makros
  #define SL_TRC_BITS                 SL_TRC_OBJ->bits()
  #define SL_TRC_TRCBITS              SL_TRC_OBJ->commonBits()
  #define SL_TRC_LEVEL                (((SL_TRC_BITS >> 28) & 7) + 1)
  #define SL_TRC_SERVERBITS           SL_TRC_OBJ->serverBits()
  #define SL_TRC_PID                  SL_TRC_OBJ->pid()
  #define SL_TRC_MODULE_NAME          SL_TRC_OBJ->moduleName()
  #define SL_TRC_IPADDR               SlTrc::ipAddr()
  #define SL_TRC_HOSTNAME             SlTrc::hostName()

  // trace calls
  #define SL_TRC_CALL_(L, B, D)       (*(SL_TRC_OBJ->setLineFile(__LINE__, __FILE__, ((((L) - 1) << 28) | (B)), D)))
  #define SL_TRC_CALL_EXT_(L, B, D)   (*(SL_TRC_OBJ->setLineFile(__LINE__, __FILE__, ((((L) - 1) << 28) | (B)), D)))
  #define SL_TRC_CALL_WOQSTR2CZ_(L, B, D)                             (*(SL_TRC_OBJ->setLineFile(__LINE__, __FILE__, ((((L) - 1) << 28) | (B)), D)))
  #define SL_TRC_OUT                  SL_TRC_OBJ->trace
  #define SL_TRC_HEX(LEAD, BUF, LEN)  SL_TRC_OBJ->trcHex(SL_TRC_STRINGIZED_MODULE, LEAD, BUF, LEN)

  // condition evaluation
  #define SL_TRC_CON_(L, B)           if (!SL_TRC_NAMESPACE::ifTrace((((L) - 1) << 28), (B))) { SlTrc::nop(); } else SL_TRC_MARK
  #define SL_TRC_CON_ANY_(L)          if (!SL_TRC_NAMESPACE::ifTraceAny((((L) - 1) << 28), (SL_TRC_ANY))) { SlTrc::nop(); } else SL_TRC_MARK
  #define SL_TRC_CON_GUARD(L, B)      if (!SL_TRC_NAMESPACE::ifTrace((((L) - 1) << 28), (B))) { SlTrc::nop(); } else
  #define SL_TRC_CONCALL_(L, B, D)    SL_TRC_CON_(L, B) SL_TRC_CALL_((L), (B), D)
  #define SL_TRC_CONCALL_ARGS_(L, B, D)    SL_TRC_CON_(L, B) SL_TRC_CALL_EXT_((L), (B), D)
  #define SL_TRC_CONCALL_ANY_(L, D)   SL_TRC_CON_ANY_(L) SL_TRC_CALL_((L), (SL_TRC_ANY | 0x80000000), D)
  #define SL_TRC_TRC_CON_(L, B)       (!SLTrcSlTrcNamespace::ifTrace((((L) - 1) << 28), (B))) ? SlTrc::nop() : SL_TRC_MARK
  #define SL_TRC_TRC_CONCALL_(L, B, D) SL_TRC_TRC_CON_(L, B) SL_TRC_CALL_((L), (B), D)
  #if SL_TRC_DEBUG == 1
    // tracing is by default compiled into debug builds
    #define SL_TRC_COND_(L, B)        SL_TRC_CON_(L, B)
    #define SL_TRC_CONDCALL_(L, B)    SL_TRC_CONCALL_(L, B, true)
    #define SL_TRC_CONDCALL_ARGS_(L, B)    SL_TRC_CONCALL_ARGS_(L, B, true)
    #define SL_TRC_CONDCALL_ANY_(L)   SL_TRC_CONCALL_ANY_(L, true)
    #define SL_TRC_COND_GUARD(L, B)   SL_TRC_CON_GUARD(L, B)
  #else
    // tracing removed by optimization
    #define SL_TRC_COND_(L, B)        while(SlTrc::never())
    #define SL_TRC_CONDCALL_(L, B)    while(SlTrc::never()) SL_TRC_OUT
    #define SL_TRC_CONDCALL_ARGS_(L, B)    while(SlTrc::never()) SL_TRC_OUT
    #define SL_TRC_CONDCALL_ANY_(L)   while(SlTrc::never()) SL_TRC_OUT
    #define SL_TRC_COND_GUARD(L, B)   while(SlTrc::never())
  #endif // SL_TRC_DEBUG == 1

  /*! \def SL_TRC_WILL_TRACE(LEVEL, BITNUM)
   *  \brief Das Nachfolgende Statement wird ausgeführt, wenn die korrespondierende Trace-Ausgabe
   *  ausgeführt würde.
   */
  #define SL_TRC_WILL_TRACE(L, B)     SL_TRC_CON_GUARD((unsigned int)L, (unsigned int)(1 << (B)))
  #define SL_TRC_GUARD(L, B)          SL_TRC_CON_GUARD((unsigned int)L, (unsigned int)(B))

  /*! \def SL_TRCD_WILL_TRACE(LEVEL, BITNUM)
   *  \brief Das Nachfolgende Statement wird ausgeführt, wenn die korrespondierende Trace-Ausgabe
   *  ausgeführt würde. Falls das Define SL_TRC_DEBUG den Wert 1 hat (z.B. wenn das Define _DEBUG
   *  gesetzt ist und der Compiler beim Übersetzen optimiert, ist der Kode des Statements nicht
   *  im Objekt präsent.
   */
  #define SL_TRCD_WILL_TRACE(L, B)    SL_TRC_COND_GUARD((unsigned int)L, (unsigned int)(1 << (B)))
  #define SL_TRCD_GUARD(L, B)         SL_TRC_COND_GUARD((unsigned int)L, (unsigned int)(B))

  // traceBit access
  /*! \def SL_TRC_SET_BIT(BITNR)
   *  \brief Setzen des Bits \a BITNR in den modulspezifischen TraceBits.
   */
  #define SL_TRC_SET_BIT(X)           (SL_TRC_OBJ->bits() |= (1 << (X)))

  /*! \def SL_TRC_CLR_BIT(BITNR)
   *  \brief Rücksetzen des Bits \a BITNR in den modulspezifischen TraceBits.
   */
  #define SL_TRC_CLR_BIT(X)           (SL_TRC_OBJ->bits() &= ~(1 << (X)))

  /*! \def SL_TRC_CHK_BIT(BITNR)
   *  \brief Testen des Bits \a BITNR in den modulspezifischen TraceBits.
   */
  #define SL_TRC_CHK_BIT(X)           ((SL_TRC_OBJ->bits() & (1 << (X))) != 0)

  /*! \def SL_TRC_SET_COMMON_BIT(BITNR)
   *  \brief Setzen des Bits \a BITNR in den TraceBits des Moduls SlTrc.
   */
  #define SL_TRC_SET_COMMON_BIT(X)    (SL_TRC_OBJ->commonBits() |= (1 << (X)))

  /*! \def SL_TRC_CLR_COMMON_BIT(BITNR)
   *  \brief Rücksetzen des Bits \a BITNR in den TraceBits des Moduls SlTrc.
   */
  #define SL_TRC_CLR_COMMON_BIT(X)    (SL_TRC_OBJ->commonBits() &= ~(1 << (X)))

  /*! \def SL_TRC_CHK_COMMON_BIT(BITNR)
   *  \brief Testen des Bits \a BITNR in den TraceBits des Moduls SlTrc.
   */
  #define SL_TRC_CHK_COMMON_BIT(X)    ((SL_TRC_OBJ->commonBits() & (1 << (X))) != 0)

#else
  // switch traceing off
  inline void sltrcnotrace(const char* /*fmt*/, ...)  {}
  inline bool sltrcnever(){return false;}

  // trace calls
  #define SL_TRC_CALL_(L, B, D)     sltrcnotrace
  #define SL_TRC_OUT                sltrcnotrace
  #define SL_TRC_HEX(LEAD, BUF, LEN)

  // condition evaluation
  #define SL_TRC_CON_(L, B)         while(sltrcnever())
  #define SL_TRC_CON_GUARD(L, B)    while(sltrcnever())
  #define SL_TRC_CONCALL_(L, B, D)  while(sltrcnever()) SL_TRC_OUT
  #define SL_TRC_TRC_CONCALL_(L, B, D) while(sltrcnever()) SL_TRC_OUT

    // tracing removed by optimization
  #define SL_TRC_COND_(L, B)        while(sltrcnever())
  #define SL_TRC_CONDCALL_(L, B)    while(sltrcnever()) SL_TRC_OUT
  #define SL_TRC_COND_GUARD(L, B)   while(sltrcnever())

  /*! \def SL_TRC_WILL_TRACE(LEVEL, BITNUM)
   *  \brief Das Nachfolgende Statement wird ausgeführt, wenn die korrespondierende Trace-Ausgabe
   *  ausgeführt würde.
   */
  #define SL_TRC_WILL_TRACE(L, B)     SL_TRC_CON_GUARD((unsigned int)L, (unsigned int)(1 << (B)))
  #define SL_TRC_GUARD(L, B)          SL_TRC_CON_GUARD((unsigned int)L, (unsigned int)(B))

  /*! \def SL_TRCD_WILL_TRACE(LEVEL, BITNUM)
   *  \brief Das Nachfolgende Statement wird ausgeführt, wenn die korrespondierende Trace-Ausgabe
   *  ausgeführt würde. Falls das Define SL_TRC_DEBUG den Wert 1 hat (z.B. wenn das Define _DEBUG
   *  gesetzt ist und der Compiler beim Übersetzen optimiert, ist der Kode des Statements nicht
   *  im Objekt präsent.
   */
  #define SL_TRCD_WILL_TRACE(L, B)    SL_TRC_COND_GUARD((unsigned int)L, (unsigned int)(1 << (B)))
  #define SL_TRCD_GUARD(L, B)         SL_TRC_COND_GUARD((unsigned int)L, (unsigned int)(B))

  // traceBit access
  /*! \def SL_TRC_SET_BIT(BITNR)
   *  \brief Setzen des Bits \a BITNR in den modulspezifischen TraceBits.
   */
  #define SL_TRC_SET_BIT(X)

  /*! \def SL_TRC_CLR_BIT(BITNR)
   *  \brief Rücksetzen des Bits \a BITNR in den modulspezifischen TraceBits.
   */
  #define SL_TRC_CLR_BIT(X)

  /*! \def SL_TRC_CHK_BIT(BITNR)
   *  \brief Testen des Bits \a BITNR in den modulspezifischen TraceBits.
   */
  #define SL_TRC_CHK_BIT(X)           false

  /*! \def SL_TRC_SET_COMMON_BIT(BITNR)
   *  \brief Setzen des Bits \a BITNR in den TraceBits des Moduls SlTrc.
   */
  #define SL_TRC_SET_COMMON_BIT(X)

  /*! \def SL_TRC_CLR_COMMON_BIT(BITNR)
   *  \brief Rücksetzen des Bits \a BITNR in den TraceBits des Moduls SlTrc.
   */
  #define SL_TRC_CLR_COMMON_BIT(X)

  /*! \def SL_TRC_CHK_COMMON_BIT(BITNR)
   *  \brief Testen des Bits \a BITNR in den TraceBits des Moduls SlTrc.
   */
  #define SL_TRC_CHK_COMMON_BIT(X)    false
#endif // SL_TRC_OFF

  #define SL_TRC_BIT0     0x00000001
  #define SL_TRC_BIT1     0x00000002
  #define SL_TRC_BIT2     0x00000004
  #define SL_TRC_BIT3     0x00000008
  #define SL_TRC_BIT4     0x00000010
  #define SL_TRC_BIT5     0x00000020
  #define SL_TRC_BIT6     0x00000040
  #define SL_TRC_BIT7     0x00000080
  #define SL_TRC_BIT8     0x00000100
  #define SL_TRC_BIT9     0x00000200
  #define SL_TRC_BIT10    0x00000400
  #define SL_TRC_BIT11    0x00000800
  #define SL_TRC_BIT12    0x00001000
  #define SL_TRC_BIT13    0x00002000
  #define SL_TRC_BIT14    0x00004000
  #define SL_TRC_BIT15    0x00008000
  #define SL_TRC_BIT16    0x00010000
  #define SL_TRC_BIT17    0x00020000
  #define SL_TRC_BIT18    0x00040000
  #define SL_TRC_BIT19    0x00080000
  #define SL_TRC_BIT20    0x00100000
  #define SL_TRC_BIT21    0x00200000
  #define SL_TRC_BIT22    0x00400000
  #define SL_TRC_BIT23    0x00800000
  #define SL_TRC_BIT24    0x01000000
  #define SL_TRC_BIT25    0x02000000
  #define SL_TRC_BIT26    0x04000000
  #define SL_TRC_BIT27    0x08000000

  #define SL_TRC_LEVEL1   1
  #define SL_TRC_LEVEL2   2
  #define SL_TRC_LEVEL3   3
  #define SL_TRC_LEVEL4   4
  #define SL_TRC_LEVEL5   5
  #define SL_TRC_LEVEL6   6
  #define SL_TRC_LEVEL7   7
  #define SL_TRC_LEVEL8   8

  // debug traces
  /*! \def SL_TRCD_Lx_BITy(const char* fmt, ...)
   *  \brief Debugtrace, Traceausgabe wenn das Programm eine Debugversion ist, der DebugLevel >= x ist und das TraceBit y gesetzt ist.
   */
  #define SL_TRCD(level,bits,args)    SL_TRC_CONDCALL_ARGS_((unsigned int)level, (unsigned int)bits)args

  #define SL_TRCD_L1_BIT0             SL_TRC_CONDCALL_(1, 0x00000001)
  #define SL_TRCD_L1_BIT1             SL_TRC_CONDCALL_(1, 0x00000002)
  #define SL_TRCD_L1_BIT2             SL_TRC_CONDCALL_(1, 0x00000004)
  #define SL_TRCD_L1_BIT3             SL_TRC_CONDCALL_(1, 0x00000008)
  #define SL_TRCD_L1_BIT4             SL_TRC_CONDCALL_(1, 0x00000010)
  #define SL_TRCD_L1_BIT5             SL_TRC_CONDCALL_(1, 0x00000020)
  #define SL_TRCD_L1_BIT6             SL_TRC_CONDCALL_(1, 0x00000040)
  #define SL_TRCD_L1_BIT7             SL_TRC_CONDCALL_(1, 0x00000080)
  #define SL_TRCD_L1_BIT8             SL_TRC_CONDCALL_(1, 0x00000100)
  #define SL_TRCD_L1_BIT9             SL_TRC_CONDCALL_(1, 0x00000200)
  #define SL_TRCD_L1_BIT10            SL_TRC_CONDCALL_(1, 0x00000400)
  #define SL_TRCD_L1_BIT11            SL_TRC_CONDCALL_(1, 0x00000800)
  #define SL_TRCD_L1_BIT12            SL_TRC_CONDCALL_(1, 0x00001000)
  #define SL_TRCD_L1_BIT13            SL_TRC_CONDCALL_(1, 0x00002000)
  #define SL_TRCD_L1_BIT14            SL_TRC_CONDCALL_(1, 0x00004000)
  #define SL_TRCD_L1_BIT15            SL_TRC_CONDCALL_(1, 0x00008000)
  #define SL_TRCD_L1_BIT16            SL_TRC_CONDCALL_(1, 0x00010000)
  #define SL_TRCD_L1_BIT17            SL_TRC_CONDCALL_(1, 0x00020000)
  #define SL_TRCD_L1_BIT18            SL_TRC_CONDCALL_(1, 0x00040000)
  #define SL_TRCD_L1_BIT19            SL_TRC_CONDCALL_(1, 0x00080000)
  #define SL_TRCD_L1_BIT20            SL_TRC_CONDCALL_(1, 0x00100000)
  #define SL_TRCD_L1_BIT21            SL_TRC_CONDCALL_(1, 0x00200000)
  #define SL_TRCD_L1_BIT22            SL_TRC_CONDCALL_(1, 0x00400000)
  #define SL_TRCD_L1_BIT23            SL_TRC_CONDCALL_(1, 0x00800000)
  #define SL_TRCD_L1_BIT24            SL_TRC_CONDCALL_(1, 0x01000000)
  #define SL_TRCD_L1_BIT25            SL_TRC_CONDCALL_(1, 0x02000000)
  #define SL_TRCD_L1_BIT26            SL_TRC_CONDCALL_(1, 0x04000000)
  #define SL_TRCD_L1_BIT27            SL_TRC_CONDCALL_(1, 0x08000000)
  #define SL_TRCD_L1_ANYBIT           SL_TRC_CONDCALL_ANY_(1)

  #define SL_TRCD_L2_BIT0             SL_TRC_CONDCALL_(2, 0x00000001)
  #define SL_TRCD_L2_BIT1             SL_TRC_CONDCALL_(2, 0x00000002)
  #define SL_TRCD_L2_BIT2             SL_TRC_CONDCALL_(2, 0x00000004)
  #define SL_TRCD_L2_BIT3             SL_TRC_CONDCALL_(2, 0x00000008)
  #define SL_TRCD_L2_BIT4             SL_TRC_CONDCALL_(2, 0x00000010)
  #define SL_TRCD_L2_BIT5             SL_TRC_CONDCALL_(2, 0x00000020)
  #define SL_TRCD_L2_BIT6             SL_TRC_CONDCALL_(2, 0x00000040)
  #define SL_TRCD_L2_BIT7             SL_TRC_CONDCALL_(2, 0x00000080)
  #define SL_TRCD_L2_BIT8             SL_TRC_CONDCALL_(2, 0x00000100)
  #define SL_TRCD_L2_BIT9             SL_TRC_CONDCALL_(2, 0x00000200)
  #define SL_TRCD_L2_BIT10            SL_TRC_CONDCALL_(2, 0x00000400)
  #define SL_TRCD_L2_BIT11            SL_TRC_CONDCALL_(2, 0x00000800)
  #define SL_TRCD_L2_BIT12            SL_TRC_CONDCALL_(2, 0x00001000)
  #define SL_TRCD_L2_BIT13            SL_TRC_CONDCALL_(2, 0x00002000)
  #define SL_TRCD_L2_BIT14            SL_TRC_CONDCALL_(2, 0x00004000)
  #define SL_TRCD_L2_BIT15            SL_TRC_CONDCALL_(2, 0x00008000)
  #define SL_TRCD_L2_BIT16            SL_TRC_CONDCALL_(2, 0x00010000)
  #define SL_TRCD_L2_BIT17            SL_TRC_CONDCALL_(2, 0x00020000)
  #define SL_TRCD_L2_BIT18            SL_TRC_CONDCALL_(2, 0x00040000)
  #define SL_TRCD_L2_BIT19            SL_TRC_CONDCALL_(2, 0x00080000)
  #define SL_TRCD_L2_BIT20            SL_TRC_CONDCALL_(2, 0x00100000)
  #define SL_TRCD_L2_BIT21            SL_TRC_CONDCALL_(2, 0x00200000)
  #define SL_TRCD_L2_BIT22            SL_TRC_CONDCALL_(2, 0x00400000)
  #define SL_TRCD_L2_BIT23            SL_TRC_CONDCALL_(2, 0x00800000)
  #define SL_TRCD_L2_BIT24            SL_TRC_CONDCALL_(2, 0x01000000)
  #define SL_TRCD_L2_BIT25            SL_TRC_CONDCALL_(2, 0x02000000)
  #define SL_TRCD_L2_BIT26            SL_TRC_CONDCALL_(2, 0x04000000)
  #define SL_TRCD_L2_BIT27            SL_TRC_CONDCALL_(2, 0x08000000)
  #define SL_TRCD_L2_ANYBIT           SL_TRC_CONDCALL_ANY_(2)

  #define SL_TRCD_L3_BIT0             SL_TRC_CONDCALL_(3, 0x00000001)
  #define SL_TRCD_L3_BIT1             SL_TRC_CONDCALL_(3, 0x00000002)
  #define SL_TRCD_L3_BIT2             SL_TRC_CONDCALL_(3, 0x00000004)
  #define SL_TRCD_L3_BIT3             SL_TRC_CONDCALL_(3, 0x00000008)
  #define SL_TRCD_L3_BIT4             SL_TRC_CONDCALL_(3, 0x00000010)
  #define SL_TRCD_L3_BIT5             SL_TRC_CONDCALL_(3, 0x00000020)
  #define SL_TRCD_L3_BIT6             SL_TRC_CONDCALL_(3, 0x00000040)
  #define SL_TRCD_L3_BIT7             SL_TRC_CONDCALL_(3, 0x00000080)
  #define SL_TRCD_L3_BIT8             SL_TRC_CONDCALL_(3, 0x00000100)
  #define SL_TRCD_L3_BIT9             SL_TRC_CONDCALL_(3, 0x00000200)
  #define SL_TRCD_L3_BIT10            SL_TRC_CONDCALL_(3, 0x00000400)
  #define SL_TRCD_L3_BIT11            SL_TRC_CONDCALL_(3, 0x00000800)
  #define SL_TRCD_L3_BIT12            SL_TRC_CONDCALL_(3, 0x00001000)
  #define SL_TRCD_L3_BIT13            SL_TRC_CONDCALL_(3, 0x00002000)
  #define SL_TRCD_L3_BIT14            SL_TRC_CONDCALL_(3, 0x00004000)
  #define SL_TRCD_L3_BIT15            SL_TRC_CONDCALL_(3, 0x00008000)
  #define SL_TRCD_L3_BIT16            SL_TRC_CONDCALL_(3, 0x00010000)
  #define SL_TRCD_L3_BIT17            SL_TRC_CONDCALL_(3, 0x00020000)
  #define SL_TRCD_L3_BIT18            SL_TRC_CONDCALL_(3, 0x00040000)
  #define SL_TRCD_L3_BIT19            SL_TRC_CONDCALL_(3, 0x00080000)
  #define SL_TRCD_L3_BIT20            SL_TRC_CONDCALL_(3, 0x00100000)
  #define SL_TRCD_L3_BIT21            SL_TRC_CONDCALL_(3, 0x00200000)
  #define SL_TRCD_L3_BIT22            SL_TRC_CONDCALL_(3, 0x00400000)
  #define SL_TRCD_L3_BIT23            SL_TRC_CONDCALL_(3, 0x00800000)
  #define SL_TRCD_L3_BIT24            SL_TRC_CONDCALL_(3, 0x01000000)
  #define SL_TRCD_L3_BIT25            SL_TRC_CONDCALL_(3, 0x02000000)
  #define SL_TRCD_L3_BIT26            SL_TRC_CONDCALL_(3, 0x04000000)
  #define SL_TRCD_L3_BIT27            SL_TRC_CONDCALL_(3, 0x08000000)
  #define SL_TRCD_L3_ANYBIT           SL_TRC_CONDCALL_ANY_(3)

  #define SL_TRCD_L4_BIT0             SL_TRC_CONDCALL_(4, 0x00000001)
  #define SL_TRCD_L4_BIT1             SL_TRC_CONDCALL_(4, 0x00000002)
  #define SL_TRCD_L4_BIT2             SL_TRC_CONDCALL_(4, 0x00000004)
  #define SL_TRCD_L4_BIT3             SL_TRC_CONDCALL_(4, 0x00000008)
  #define SL_TRCD_L4_BIT4             SL_TRC_CONDCALL_(4, 0x00000010)
  #define SL_TRCD_L4_BIT5             SL_TRC_CONDCALL_(4, 0x00000020)
  #define SL_TRCD_L4_BIT6             SL_TRC_CONDCALL_(4, 0x00000040)
  #define SL_TRCD_L4_BIT7             SL_TRC_CONDCALL_(4, 0x00000080)
  #define SL_TRCD_L4_BIT8             SL_TRC_CONDCALL_(4, 0x00000100)
  #define SL_TRCD_L4_BIT9             SL_TRC_CONDCALL_(4, 0x00000200)
  #define SL_TRCD_L4_BIT10            SL_TRC_CONDCALL_(4, 0x00000400)
  #define SL_TRCD_L4_BIT11            SL_TRC_CONDCALL_(4, 0x00000800)
  #define SL_TRCD_L4_BIT12            SL_TRC_CONDCALL_(4, 0x00001000)
  #define SL_TRCD_L4_BIT13            SL_TRC_CONDCALL_(4, 0x00002000)
  #define SL_TRCD_L4_BIT14            SL_TRC_CONDCALL_(4, 0x00004000)
  #define SL_TRCD_L4_BIT15            SL_TRC_CONDCALL_(4, 0x00008000)
  #define SL_TRCD_L4_BIT16            SL_TRC_CONDCALL_(4, 0x00010000)
  #define SL_TRCD_L4_BIT17            SL_TRC_CONDCALL_(4, 0x00020000)
  #define SL_TRCD_L4_BIT18            SL_TRC_CONDCALL_(4, 0x00040000)
  #define SL_TRCD_L4_BIT19            SL_TRC_CONDCALL_(4, 0x00080000)
  #define SL_TRCD_L4_BIT20            SL_TRC_CONDCALL_(4, 0x00100000)
  #define SL_TRCD_L4_BIT21            SL_TRC_CONDCALL_(4, 0x00200000)
  #define SL_TRCD_L4_BIT22            SL_TRC_CONDCALL_(4, 0x00400000)
  #define SL_TRCD_L4_BIT23            SL_TRC_CONDCALL_(4, 0x00800000)
  #define SL_TRCD_L4_BIT24            SL_TRC_CONDCALL_(4, 0x01000000)
  #define SL_TRCD_L4_BIT25            SL_TRC_CONDCALL_(4, 0x02000000)
  #define SL_TRCD_L4_BIT26            SL_TRC_CONDCALL_(4, 0x04000000)
  #define SL_TRCD_L4_BIT27            SL_TRC_CONDCALL_(4, 0x08000000)
  #define SL_TRCD_L4_ANYBIT           SL_TRC_CONDCALL_ANY_(4)

  #define SL_TRCD_L5_BIT0             SL_TRC_CONDCALL_(5, 0x00000001)
  #define SL_TRCD_L5_BIT1             SL_TRC_CONDCALL_(5, 0x00000002)
  #define SL_TRCD_L5_BIT2             SL_TRC_CONDCALL_(5, 0x00000004)
  #define SL_TRCD_L5_BIT3             SL_TRC_CONDCALL_(5, 0x00000008)
  #define SL_TRCD_L5_BIT4             SL_TRC_CONDCALL_(5, 0x00000010)
  #define SL_TRCD_L5_BIT5             SL_TRC_CONDCALL_(5, 0x00000020)
  #define SL_TRCD_L5_BIT6             SL_TRC_CONDCALL_(5, 0x00000040)
  #define SL_TRCD_L5_BIT7             SL_TRC_CONDCALL_(5, 0x00000080)
  #define SL_TRCD_L5_BIT8             SL_TRC_CONDCALL_(5, 0x00000100)
  #define SL_TRCD_L5_BIT9             SL_TRC_CONDCALL_(5, 0x00000200)
  #define SL_TRCD_L5_BIT10            SL_TRC_CONDCALL_(5, 0x00000400)
  #define SL_TRCD_L5_BIT11            SL_TRC_CONDCALL_(5, 0x00000800)
  #define SL_TRCD_L5_BIT12            SL_TRC_CONDCALL_(5, 0x00001000)
  #define SL_TRCD_L5_BIT13            SL_TRC_CONDCALL_(5, 0x00002000)
  #define SL_TRCD_L5_BIT14            SL_TRC_CONDCALL_(5, 0x00004000)
  #define SL_TRCD_L5_BIT15            SL_TRC_CONDCALL_(5, 0x00008000)
  #define SL_TRCD_L5_BIT16            SL_TRC_CONDCALL_(5, 0x00010000)
  #define SL_TRCD_L5_BIT17            SL_TRC_CONDCALL_(5, 0x00020000)
  #define SL_TRCD_L5_BIT18            SL_TRC_CONDCALL_(5, 0x00040000)
  #define SL_TRCD_L5_BIT19            SL_TRC_CONDCALL_(5, 0x00080000)
  #define SL_TRCD_L5_BIT20            SL_TRC_CONDCALL_(5, 0x00100000)
  #define SL_TRCD_L5_BIT21            SL_TRC_CONDCALL_(5, 0x00200000)
  #define SL_TRCD_L5_BIT22            SL_TRC_CONDCALL_(5, 0x00400000)
  #define SL_TRCD_L5_BIT23            SL_TRC_CONDCALL_(5, 0x00800000)
  #define SL_TRCD_L5_BIT24            SL_TRC_CONDCALL_(5, 0x01000000)
  #define SL_TRCD_L5_BIT25            SL_TRC_CONDCALL_(5, 0x02000000)
  #define SL_TRCD_L5_BIT26            SL_TRC_CONDCALL_(5, 0x04000000)
  #define SL_TRCD_L5_BIT27            SL_TRC_CONDCALL_(5, 0x08000000)
  #define SL_TRCD_L5_ANYBIT           SL_TRC_CONDCALL_ANY_(5)

  #define SL_TRCD_L6_BIT0             SL_TRC_CONDCALL_(6, 0x00000001)
  #define SL_TRCD_L6_BIT1             SL_TRC_CONDCALL_(6, 0x00000002)
  #define SL_TRCD_L6_BIT2             SL_TRC_CONDCALL_(6, 0x00000004)
  #define SL_TRCD_L6_BIT3             SL_TRC_CONDCALL_(6, 0x00000008)
  #define SL_TRCD_L6_BIT4             SL_TRC_CONDCALL_(6, 0x00000010)
  #define SL_TRCD_L6_BIT5             SL_TRC_CONDCALL_(6, 0x00000020)
  #define SL_TRCD_L6_BIT6             SL_TRC_CONDCALL_(6, 0x00000040)
  #define SL_TRCD_L6_BIT7             SL_TRC_CONDCALL_(6, 0x00000080)
  #define SL_TRCD_L6_BIT8             SL_TRC_CONDCALL_(6, 0x00000100)
  #define SL_TRCD_L6_BIT9             SL_TRC_CONDCALL_(6, 0x00000200)
  #define SL_TRCD_L6_BIT10            SL_TRC_CONDCALL_(6, 0x00000400)
  #define SL_TRCD_L6_BIT11            SL_TRC_CONDCALL_(6, 0x00000800)
  #define SL_TRCD_L6_BIT12            SL_TRC_CONDCALL_(6, 0x00001000)
  #define SL_TRCD_L6_BIT13            SL_TRC_CONDCALL_(6, 0x00002000)
  #define SL_TRCD_L6_BIT14            SL_TRC_CONDCALL_(6, 0x00004000)
  #define SL_TRCD_L6_BIT15            SL_TRC_CONDCALL_(6, 0x00008000)
  #define SL_TRCD_L6_BIT16            SL_TRC_CONDCALL_(6, 0x00010000)
  #define SL_TRCD_L6_BIT17            SL_TRC_CONDCALL_(6, 0x00020000)
  #define SL_TRCD_L6_BIT18            SL_TRC_CONDCALL_(6, 0x00040000)
  #define SL_TRCD_L6_BIT19            SL_TRC_CONDCALL_(6, 0x00080000)
  #define SL_TRCD_L6_BIT20            SL_TRC_CONDCALL_(6, 0x00100000)
  #define SL_TRCD_L6_BIT21            SL_TRC_CONDCALL_(6, 0x00200000)
  #define SL_TRCD_L6_BIT22            SL_TRC_CONDCALL_(6, 0x00400000)
  #define SL_TRCD_L6_BIT23            SL_TRC_CONDCALL_(6, 0x00800000)
  #define SL_TRCD_L6_BIT24            SL_TRC_CONDCALL_(6, 0x01000000)
  #define SL_TRCD_L6_BIT25            SL_TRC_CONDCALL_(6, 0x02000000)
  #define SL_TRCD_L6_BIT26            SL_TRC_CONDCALL_(6, 0x04000000)
  #define SL_TRCD_L6_BIT27            SL_TRC_CONDCALL_(6, 0x08000000)
  #define SL_TRCD_L6_ANYBIT           SL_TRC_CONDCALL_ANY_(6)

  #define SL_TRCD_L7_BIT0             SL_TRC_CONDCALL_(7, 0x00000001)
  #define SL_TRCD_L7_BIT1             SL_TRC_CONDCALL_(7, 0x00000002)
  #define SL_TRCD_L7_BIT2             SL_TRC_CONDCALL_(7, 0x00000004)
  #define SL_TRCD_L7_BIT3             SL_TRC_CONDCALL_(7, 0x00000008)
  #define SL_TRCD_L7_BIT4             SL_TRC_CONDCALL_(7, 0x00000010)
  #define SL_TRCD_L7_BIT5             SL_TRC_CONDCALL_(7, 0x00000020)
  #define SL_TRCD_L7_BIT6             SL_TRC_CONDCALL_(7, 0x00000040)
  #define SL_TRCD_L7_BIT7             SL_TRC_CONDCALL_(7, 0x00000080)
  #define SL_TRCD_L7_BIT8             SL_TRC_CONDCALL_(7, 0x00000100)
  #define SL_TRCD_L7_BIT9             SL_TRC_CONDCALL_(7, 0x00000200)
  #define SL_TRCD_L7_BIT10            SL_TRC_CONDCALL_(7, 0x00000400)
  #define SL_TRCD_L7_BIT11            SL_TRC_CONDCALL_(7, 0x00000800)
  #define SL_TRCD_L7_BIT12            SL_TRC_CONDCALL_(7, 0x00001000)
  #define SL_TRCD_L7_BIT13            SL_TRC_CONDCALL_(7, 0x00002000)
  #define SL_TRCD_L7_BIT14            SL_TRC_CONDCALL_(7, 0x00004000)
  #define SL_TRCD_L7_BIT15            SL_TRC_CONDCALL_(7, 0x00008000)
  #define SL_TRCD_L7_BIT16            SL_TRC_CONDCALL_(7, 0x00010000)
  #define SL_TRCD_L7_BIT17            SL_TRC_CONDCALL_(7, 0x00020000)
  #define SL_TRCD_L7_BIT18            SL_TRC_CONDCALL_(7, 0x00040000)
  #define SL_TRCD_L7_BIT19            SL_TRC_CONDCALL_(7, 0x00080000)
  #define SL_TRCD_L7_BIT20            SL_TRC_CONDCALL_(7, 0x00100000)
  #define SL_TRCD_L7_BIT21            SL_TRC_CONDCALL_(7, 0x00200000)
  #define SL_TRCD_L7_BIT22            SL_TRC_CONDCALL_(7, 0x00400000)
  #define SL_TRCD_L7_BIT23            SL_TRC_CONDCALL_(7, 0x00800000)
  #define SL_TRCD_L7_BIT24            SL_TRC_CONDCALL_(7, 0x01000000)
  #define SL_TRCD_L7_BIT25            SL_TRC_CONDCALL_(7, 0x02000000)
  #define SL_TRCD_L7_BIT26            SL_TRC_CONDCALL_(7, 0x04000000)
  #define SL_TRCD_L7_BIT27            SL_TRC_CONDCALL_(7, 0x08000000)
  #define SL_TRCD_L7_ANYBIT           SL_TRC_CONDCALL_ANY_(7)

  #define SL_TRCD_L8_BIT0             SL_TRC_CONDCALL_(8, 0x00000001)
  #define SL_TRCD_L8_BIT1             SL_TRC_CONDCALL_(8, 0x00000002)
  #define SL_TRCD_L8_BIT2             SL_TRC_CONDCALL_(8, 0x00000004)
  #define SL_TRCD_L8_BIT3             SL_TRC_CONDCALL_(8, 0x00000008)
  #define SL_TRCD_L8_BIT4             SL_TRC_CONDCALL_(8, 0x00000010)
  #define SL_TRCD_L8_BIT5             SL_TRC_CONDCALL_(8, 0x00000020)
  #define SL_TRCD_L8_BIT6             SL_TRC_CONDCALL_(8, 0x00000040)
  #define SL_TRCD_L8_BIT7             SL_TRC_CONDCALL_(8, 0x00000080)
  #define SL_TRCD_L8_BIT8             SL_TRC_CONDCALL_(8, 0x00000100)
  #define SL_TRCD_L8_BIT9             SL_TRC_CONDCALL_(8, 0x00000200)
  #define SL_TRCD_L8_BIT10            SL_TRC_CONDCALL_(8, 0x00000400)
  #define SL_TRCD_L8_BIT11            SL_TRC_CONDCALL_(8, 0x00000800)
  #define SL_TRCD_L8_BIT12            SL_TRC_CONDCALL_(8, 0x00001000)
  #define SL_TRCD_L8_BIT13            SL_TRC_CONDCALL_(8, 0x00002000)
  #define SL_TRCD_L8_BIT14            SL_TRC_CONDCALL_(8, 0x00004000)
  #define SL_TRCD_L8_BIT15            SL_TRC_CONDCALL_(8, 0x00008000)
  #define SL_TRCD_L8_BIT16            SL_TRC_CONDCALL_(8, 0x00010000)
  #define SL_TRCD_L8_BIT17            SL_TRC_CONDCALL_(8, 0x00020000)
  #define SL_TRCD_L8_BIT18            SL_TRC_CONDCALL_(8, 0x00040000)
  #define SL_TRCD_L8_BIT19            SL_TRC_CONDCALL_(8, 0x00080000)
  #define SL_TRCD_L8_BIT20            SL_TRC_CONDCALL_(8, 0x00100000)
  #define SL_TRCD_L8_BIT21            SL_TRC_CONDCALL_(8, 0x00200000)
  #define SL_TRCD_L8_BIT22            SL_TRC_CONDCALL_(8, 0x00400000)
  #define SL_TRCD_L8_BIT23            SL_TRC_CONDCALL_(8, 0x00800000)
  #define SL_TRCD_L8_BIT24            SL_TRC_CONDCALL_(8, 0x01000000)
  #define SL_TRCD_L8_BIT25            SL_TRC_CONDCALL_(8, 0x02000000)
  #define SL_TRCD_L8_BIT26            SL_TRC_CONDCALL_(8, 0x04000000)
  #define SL_TRCD_L8_BIT27            SL_TRC_CONDCALL_(8, 0x08000000)
  #define SL_TRCD_L8_ANYBIT           SL_TRC_CONDCALL_ANY_(8)


  // Release traces
  /*! \def SL_TRC_Lx_BITy(const char* fmt, ...)
   *  \brief Releasetrace, Traceausgabe wenn der DebugLevel >= x ist und das TraceBit y gesetzt ist.
   */
  #define SL_TRC(level,bits,args)     SL_TRC_CONCALL_ARGS_((unsigned int)level, (unsigned int)bits, false)args

  #define SL_TRC_ERROR               SL_TRC_TRC_CONCALL_(1, 0x00000002, false)

  #define SL_TRC_L1_BIT0             SL_TRC_CONCALL_(1, 0x00000001, false)
  #define SL_TRC_L1_BIT1             SL_TRC_CONCALL_(1, 0x00000002, false)
  #define SL_TRC_L1_BIT2             SL_TRC_CONCALL_(1, 0x00000004, false)
  #define SL_TRC_L1_BIT3             SL_TRC_CONCALL_(1, 0x00000008, false)
  #define SL_TRC_L1_BIT4             SL_TRC_CONCALL_(1, 0x00000010, false)
  #define SL_TRC_L1_BIT5             SL_TRC_CONCALL_(1, 0x00000020, false)
  #define SL_TRC_L1_BIT6             SL_TRC_CONCALL_(1, 0x00000040, false)
  #define SL_TRC_L1_BIT7             SL_TRC_CONCALL_(1, 0x00000080, false)
  #define SL_TRC_L1_BIT8             SL_TRC_CONCALL_(1, 0x00000100, false)
  #define SL_TRC_L1_BIT9             SL_TRC_CONCALL_(1, 0x00000200, false)
  #define SL_TRC_L1_BIT10            SL_TRC_CONCALL_(1, 0x00000400, false)
  #define SL_TRC_L1_BIT11            SL_TRC_CONCALL_(1, 0x00000800, false)
  #define SL_TRC_L1_BIT12            SL_TRC_CONCALL_(1, 0x00001000, false)
  #define SL_TRC_L1_BIT13            SL_TRC_CONCALL_(1, 0x00002000, false)
  #define SL_TRC_L1_BIT14            SL_TRC_CONCALL_(1, 0x00004000, false)
  #define SL_TRC_L1_BIT15            SL_TRC_CONCALL_(1, 0x00008000, false)
  #define SL_TRC_L1_BIT16            SL_TRC_CONCALL_(1, 0x00010000, false)
  #define SL_TRC_L1_BIT17            SL_TRC_CONCALL_(1, 0x00020000, false)
  #define SL_TRC_L1_BIT18            SL_TRC_CONCALL_(1, 0x00040000, false)
  #define SL_TRC_L1_BIT19            SL_TRC_CONCALL_(1, 0x00080000, false)
  #define SL_TRC_L1_BIT20            SL_TRC_CONCALL_(1, 0x00100000, false)
  #define SL_TRC_L1_BIT21            SL_TRC_CONCALL_(1, 0x00200000, false)
  #define SL_TRC_L1_BIT22            SL_TRC_CONCALL_(1, 0x00400000, false)
  #define SL_TRC_L1_BIT23            SL_TRC_CONCALL_(1, 0x00800000, false)
  #define SL_TRC_L1_BIT24            SL_TRC_CONCALL_(1, 0x01000000, false)
  #define SL_TRC_L1_BIT25            SL_TRC_CONCALL_(1, 0x02000000, false)
  #define SL_TRC_L1_BIT26            SL_TRC_CONCALL_(1, 0x04000000, false)
  #define SL_TRC_L1_BIT27            SL_TRC_CONCALL_(1, 0x08000000, false)
  #define SL_TRC_L1_ANYBIT           SL_TRC_CONCALL_ANY_(1, false)

  #define SL_TRC_L2_BIT0             SL_TRC_CONCALL_(2, 0x00000001, false)
  #define SL_TRC_L2_BIT1             SL_TRC_CONCALL_(2, 0x00000002, false)
  #define SL_TRC_L2_BIT2             SL_TRC_CONCALL_(2, 0x00000004, false)
  #define SL_TRC_L2_BIT3             SL_TRC_CONCALL_(2, 0x00000008, false)
  #define SL_TRC_L2_BIT4             SL_TRC_CONCALL_(2, 0x00000010, false)
  #define SL_TRC_L2_BIT5             SL_TRC_CONCALL_(2, 0x00000020, false)
  #define SL_TRC_L2_BIT6             SL_TRC_CONCALL_(2, 0x00000040, false)
  #define SL_TRC_L2_BIT7             SL_TRC_CONCALL_(2, 0x00000080, false)
  #define SL_TRC_L2_BIT8             SL_TRC_CONCALL_(2, 0x00000100, false)
  #define SL_TRC_L2_BIT9             SL_TRC_CONCALL_(2, 0x00000200, false)
  #define SL_TRC_L2_BIT10            SL_TRC_CONCALL_(2, 0x00000400, false)
  #define SL_TRC_L2_BIT11            SL_TRC_CONCALL_(2, 0x00000800, false)
  #define SL_TRC_L2_BIT12            SL_TRC_CONCALL_(2, 0x00001000, false)
  #define SL_TRC_L2_BIT13            SL_TRC_CONCALL_(2, 0x00002000, false)
  #define SL_TRC_L2_BIT14            SL_TRC_CONCALL_(2, 0x00004000, false)
  #define SL_TRC_L2_BIT15            SL_TRC_CONCALL_(2, 0x00008000, false)
  #define SL_TRC_L2_BIT16            SL_TRC_CONCALL_(2, 0x00010000, false)
  #define SL_TRC_L2_BIT17            SL_TRC_CONCALL_(2, 0x00020000, false)
  #define SL_TRC_L2_BIT18            SL_TRC_CONCALL_(2, 0x00040000, false)
  #define SL_TRC_L2_BIT19            SL_TRC_CONCALL_(2, 0x00080000, false)
  #define SL_TRC_L2_BIT20            SL_TRC_CONCALL_(2, 0x00100000, false)
  #define SL_TRC_L2_BIT21            SL_TRC_CONCALL_(2, 0x00200000, false)
  #define SL_TRC_L2_BIT22            SL_TRC_CONCALL_(2, 0x00400000, false)
  #define SL_TRC_L2_BIT23            SL_TRC_CONCALL_(2, 0x00800000, false)
  #define SL_TRC_L2_BIT24            SL_TRC_CONCALL_(2, 0x01000000, false)
  #define SL_TRC_L2_BIT25            SL_TRC_CONCALL_(2, 0x02000000, false)
  #define SL_TRC_L2_BIT26            SL_TRC_CONCALL_(2, 0x04000000, false)
  #define SL_TRC_L2_BIT27            SL_TRC_CONCALL_(2, 0x08000000, false)
  #define SL_TRC_L2_ANYBIT           SL_TRC_CONCALL_ANY_(2, false)

  #define SL_TRC_L3_BIT0             SL_TRC_CONCALL_(3, 0x00000001, false)
  #define SL_TRC_L3_BIT1             SL_TRC_CONCALL_(3, 0x00000002, false)
  #define SL_TRC_L3_BIT2             SL_TRC_CONCALL_(3, 0x00000004, false)
  #define SL_TRC_L3_BIT3             SL_TRC_CONCALL_(3, 0x00000008, false)
  #define SL_TRC_L3_BIT4             SL_TRC_CONCALL_(3, 0x00000010, false)
  #define SL_TRC_L3_BIT5             SL_TRC_CONCALL_(3, 0x00000020, false)
  #define SL_TRC_L3_BIT6             SL_TRC_CONCALL_(3, 0x00000040, false)
  #define SL_TRC_L3_BIT7             SL_TRC_CONCALL_(3, 0x00000080, false)
  #define SL_TRC_L3_BIT8             SL_TRC_CONCALL_(3, 0x00000100, false)
  #define SL_TRC_L3_BIT9             SL_TRC_CONCALL_(3, 0x00000200, false)
  #define SL_TRC_L3_BIT10            SL_TRC_CONCALL_(3, 0x00000400, false)
  #define SL_TRC_L3_BIT11            SL_TRC_CONCALL_(3, 0x00000800, false)
  #define SL_TRC_L3_BIT12            SL_TRC_CONCALL_(3, 0x00001000, false)
  #define SL_TRC_L3_BIT13            SL_TRC_CONCALL_(3, 0x00002000, false)
  #define SL_TRC_L3_BIT14            SL_TRC_CONCALL_(3, 0x00004000, false)
  #define SL_TRC_L3_BIT15            SL_TRC_CONCALL_(3, 0x00008000, false)
  #define SL_TRC_L3_BIT16            SL_TRC_CONCALL_(3, 0x00010000, false)
  #define SL_TRC_L3_BIT17            SL_TRC_CONCALL_(3, 0x00020000, false)
  #define SL_TRC_L3_BIT18            SL_TRC_CONCALL_(3, 0x00040000, false)
  #define SL_TRC_L3_BIT19            SL_TRC_CONCALL_(3, 0x00080000, false)
  #define SL_TRC_L3_BIT20            SL_TRC_CONCALL_(3, 0x00100000, false)
  #define SL_TRC_L3_BIT21            SL_TRC_CONCALL_(3, 0x00200000, false)
  #define SL_TRC_L3_BIT22            SL_TRC_CONCALL_(3, 0x00400000, false)
  #define SL_TRC_L3_BIT23            SL_TRC_CONCALL_(3, 0x00800000, false)
  #define SL_TRC_L3_BIT24            SL_TRC_CONCALL_(3, 0x01000000, false)
  #define SL_TRC_L3_BIT25            SL_TRC_CONCALL_(3, 0x02000000, false)
  #define SL_TRC_L3_BIT26            SL_TRC_CONCALL_(3, 0x04000000, false)
  #define SL_TRC_L3_BIT27            SL_TRC_CONCALL_(3, 0x08000000, false)
  #define SL_TRC_L3_ANYBIT           SL_TRC_CONCALL_ANY_(3, false)

  #define SL_TRC_L4_BIT0             SL_TRC_CONCALL_(4, 0x00000001, false)
  #define SL_TRC_L4_BIT1             SL_TRC_CONCALL_(4, 0x00000002, false)
  #define SL_TRC_L4_BIT2             SL_TRC_CONCALL_(4, 0x00000004, false)
  #define SL_TRC_L4_BIT3             SL_TRC_CONCALL_(4, 0x00000008, false)
  #define SL_TRC_L4_BIT4             SL_TRC_CONCALL_(4, 0x00000010, false)
  #define SL_TRC_L4_BIT5             SL_TRC_CONCALL_(4, 0x00000020, false)
  #define SL_TRC_L4_BIT6             SL_TRC_CONCALL_(4, 0x00000040, false)
  #define SL_TRC_L4_BIT7             SL_TRC_CONCALL_(4, 0x00000080, false)
  #define SL_TRC_L4_BIT8             SL_TRC_CONCALL_(4, 0x00000100, false)
  #define SL_TRC_L4_BIT9             SL_TRC_CONCALL_(4, 0x00000200, false)
  #define SL_TRC_L4_BIT10            SL_TRC_CONCALL_(4, 0x00000400, false)
  #define SL_TRC_L4_BIT11            SL_TRC_CONCALL_(4, 0x00000800, false)
  #define SL_TRC_L4_BIT12            SL_TRC_CONCALL_(4, 0x00001000, false)
  #define SL_TRC_L4_BIT13            SL_TRC_CONCALL_(4, 0x00002000, false)
  #define SL_TRC_L4_BIT14            SL_TRC_CONCALL_(4, 0x00004000, false)
  #define SL_TRC_L4_BIT15            SL_TRC_CONCALL_(4, 0x00008000, false)
  #define SL_TRC_L4_BIT16            SL_TRC_CONCALL_(4, 0x00010000, false)
  #define SL_TRC_L4_BIT17            SL_TRC_CONCALL_(4, 0x00020000, false)
  #define SL_TRC_L4_BIT18            SL_TRC_CONCALL_(4, 0x00040000, false)
  #define SL_TRC_L4_BIT19            SL_TRC_CONCALL_(4, 0x00080000, false)
  #define SL_TRC_L4_BIT20            SL_TRC_CONCALL_(4, 0x00100000, false)
  #define SL_TRC_L4_BIT21            SL_TRC_CONCALL_(4, 0x00200000, false)
  #define SL_TRC_L4_BIT22            SL_TRC_CONCALL_(4, 0x00400000, false)
  #define SL_TRC_L4_BIT23            SL_TRC_CONCALL_(4, 0x00800000, false)
  #define SL_TRC_L4_BIT24            SL_TRC_CONCALL_(4, 0x01000000, false)
  #define SL_TRC_L4_BIT25            SL_TRC_CONCALL_(4, 0x02000000, false)
  #define SL_TRC_L4_BIT26            SL_TRC_CONCALL_(4, 0x04000000, false)
  #define SL_TRC_L4_BIT27            SL_TRC_CONCALL_(4, 0x08000000, false)
  #define SL_TRC_L4_ANYBIT           SL_TRC_CONCALL_ANY_(4, false)

  #define SL_TRC_L5_BIT0             SL_TRC_CONCALL_(5, 0x00000001, false)
  #define SL_TRC_L5_BIT1             SL_TRC_CONCALL_(5, 0x00000002, false)
  #define SL_TRC_L5_BIT2             SL_TRC_CONCALL_(5, 0x00000004, false)
  #define SL_TRC_L5_BIT3             SL_TRC_CONCALL_(5, 0x00000008, false)
  #define SL_TRC_L5_BIT4             SL_TRC_CONCALL_(5, 0x00000010, false)
  #define SL_TRC_L5_BIT5             SL_TRC_CONCALL_(5, 0x00000020, false)
  #define SL_TRC_L5_BIT6             SL_TRC_CONCALL_(5, 0x00000040, false)
  #define SL_TRC_L5_BIT7             SL_TRC_CONCALL_(5, 0x00000080, false)
  #define SL_TRC_L5_BIT8             SL_TRC_CONCALL_(5, 0x00000100, false)
  #define SL_TRC_L5_BIT9             SL_TRC_CONCALL_(5, 0x00000200, false)
  #define SL_TRC_L5_BIT10            SL_TRC_CONCALL_(5, 0x00000400, false)
  #define SL_TRC_L5_BIT11            SL_TRC_CONCALL_(5, 0x00000800, false)
  #define SL_TRC_L5_BIT12            SL_TRC_CONCALL_(5, 0x00001000, false)
  #define SL_TRC_L5_BIT13            SL_TRC_CONCALL_(5, 0x00002000, false)
  #define SL_TRC_L5_BIT14            SL_TRC_CONCALL_(5, 0x00004000, false)
  #define SL_TRC_L5_BIT15            SL_TRC_CONCALL_(5, 0x00008000, false)
  #define SL_TRC_L5_BIT16            SL_TRC_CONCALL_(5, 0x00010000, false)
  #define SL_TRC_L5_BIT17            SL_TRC_CONCALL_(5, 0x00020000, false)
  #define SL_TRC_L5_BIT18            SL_TRC_CONCALL_(5, 0x00040000, false)
  #define SL_TRC_L5_BIT19            SL_TRC_CONCALL_(5, 0x00080000, false)
  #define SL_TRC_L5_BIT20            SL_TRC_CONCALL_(5, 0x00100000, false)
  #define SL_TRC_L5_BIT21            SL_TRC_CONCALL_(5, 0x00200000, false)
  #define SL_TRC_L5_BIT22            SL_TRC_CONCALL_(5, 0x00400000, false)
  #define SL_TRC_L5_BIT23            SL_TRC_CONCALL_(5, 0x00800000, false)
  #define SL_TRC_L5_BIT24            SL_TRC_CONCALL_(5, 0x01000000, false)
  #define SL_TRC_L5_BIT25            SL_TRC_CONCALL_(5, 0x02000000, false)
  #define SL_TRC_L5_BIT26            SL_TRC_CONCALL_(5, 0x04000000, false)
  #define SL_TRC_L5_BIT27            SL_TRC_CONCALL_(5, 0x08000000, false)
  #define SL_TRC_L5_ANYBIT           SL_TRC_CONCALL_ANY_(5, false)

  #define SL_TRC_L6_BIT0             SL_TRC_CONCALL_(6, 0x00000001, false)
  #define SL_TRC_L6_BIT1             SL_TRC_CONCALL_(6, 0x00000002, false)
  #define SL_TRC_L6_BIT2             SL_TRC_CONCALL_(6, 0x00000004, false)
  #define SL_TRC_L6_BIT3             SL_TRC_CONCALL_(6, 0x00000008, false)
  #define SL_TRC_L6_BIT4             SL_TRC_CONCALL_(6, 0x00000010, false)
  #define SL_TRC_L6_BIT5             SL_TRC_CONCALL_(6, 0x00000020, false)
  #define SL_TRC_L6_BIT6             SL_TRC_CONCALL_(6, 0x00000040, false)
  #define SL_TRC_L6_BIT7             SL_TRC_CONCALL_(6, 0x00000080, false)
  #define SL_TRC_L6_BIT8             SL_TRC_CONCALL_(6, 0x00000100, false)
  #define SL_TRC_L6_BIT9             SL_TRC_CONCALL_(6, 0x00000200, false)
  #define SL_TRC_L6_BIT10            SL_TRC_CONCALL_(6, 0x00000400, false)
  #define SL_TRC_L6_BIT11            SL_TRC_CONCALL_(6, 0x00000800, false)
  #define SL_TRC_L6_BIT12            SL_TRC_CONCALL_(6, 0x00001000, false)
  #define SL_TRC_L6_BIT13            SL_TRC_CONCALL_(6, 0x00002000, false)
  #define SL_TRC_L6_BIT14            SL_TRC_CONCALL_(6, 0x00004000, false)
  #define SL_TRC_L6_BIT15            SL_TRC_CONCALL_(6, 0x00008000, false)
  #define SL_TRC_L6_BIT16            SL_TRC_CONCALL_(6, 0x00010000, false)
  #define SL_TRC_L6_BIT17            SL_TRC_CONCALL_(6, 0x00020000, false)
  #define SL_TRC_L6_BIT18            SL_TRC_CONCALL_(6, 0x00040000, false)
  #define SL_TRC_L6_BIT19            SL_TRC_CONCALL_(6, 0x00080000, false)
  #define SL_TRC_L6_BIT20            SL_TRC_CONCALL_(6, 0x00100000, false)
  #define SL_TRC_L6_BIT21            SL_TRC_CONCALL_(6, 0x00200000, false)
  #define SL_TRC_L6_BIT22            SL_TRC_CONCALL_(6, 0x00400000, false)
  #define SL_TRC_L6_BIT23            SL_TRC_CONCALL_(6, 0x00800000, false)
  #define SL_TRC_L6_BIT24            SL_TRC_CONCALL_(6, 0x01000000, false)
  #define SL_TRC_L6_BIT25            SL_TRC_CONCALL_(6, 0x02000000, false)
  #define SL_TRC_L6_BIT26            SL_TRC_CONCALL_(6, 0x04000000, false)
  #define SL_TRC_L6_BIT27            SL_TRC_CONCALL_(6, 0x08000000, false)
  #define SL_TRC_L6_ANYBIT           SL_TRC_CONCALL_ANY_(6, false)

  #define SL_TRC_L7_BIT0             SL_TRC_CONCALL_(7, 0x00000001, false)
  #define SL_TRC_L7_BIT1             SL_TRC_CONCALL_(7, 0x00000002, false)
  #define SL_TRC_L7_BIT2             SL_TRC_CONCALL_(7, 0x00000004, false)
  #define SL_TRC_L7_BIT3             SL_TRC_CONCALL_(7, 0x00000008, false)
  #define SL_TRC_L7_BIT4             SL_TRC_CONCALL_(7, 0x00000010, false)
  #define SL_TRC_L7_BIT5             SL_TRC_CONCALL_(7, 0x00000020, false)
  #define SL_TRC_L7_BIT6             SL_TRC_CONCALL_(7, 0x00000040, false)
  #define SL_TRC_L7_BIT7             SL_TRC_CONCALL_(7, 0x00000080, false)
  #define SL_TRC_L7_BIT8             SL_TRC_CONCALL_(7, 0x00000100, false)
  #define SL_TRC_L7_BIT9             SL_TRC_CONCALL_(7, 0x00000200, false)
  #define SL_TRC_L7_BIT10            SL_TRC_CONCALL_(7, 0x00000400, false)
  #define SL_TRC_L7_BIT11            SL_TRC_CONCALL_(7, 0x00000800, false)
  #define SL_TRC_L7_BIT12            SL_TRC_CONCALL_(7, 0x00001000, false)
  #define SL_TRC_L7_BIT13            SL_TRC_CONCALL_(7, 0x00002000, false)
  #define SL_TRC_L7_BIT14            SL_TRC_CONCALL_(7, 0x00004000, false)
  #define SL_TRC_L7_BIT15            SL_TRC_CONCALL_(7, 0x00008000, false)
  #define SL_TRC_L7_BIT16            SL_TRC_CONCALL_(7, 0x00010000, false)
  #define SL_TRC_L7_BIT17            SL_TRC_CONCALL_(7, 0x00020000, false)
  #define SL_TRC_L7_BIT18            SL_TRC_CONCALL_(7, 0x00040000, false)
  #define SL_TRC_L7_BIT19            SL_TRC_CONCALL_(7, 0x00080000, false)
  #define SL_TRC_L7_BIT20            SL_TRC_CONCALL_(7, 0x00100000, false)
  #define SL_TRC_L7_BIT21            SL_TRC_CONCALL_(7, 0x00200000, false)
  #define SL_TRC_L7_BIT22            SL_TRC_CONCALL_(7, 0x00400000, false)
  #define SL_TRC_L7_BIT23            SL_TRC_CONCALL_(7, 0x00800000, false)
  #define SL_TRC_L7_BIT24            SL_TRC_CONCALL_(7, 0x01000000, false)
  #define SL_TRC_L7_BIT25            SL_TRC_CONCALL_(7, 0x02000000, false)
  #define SL_TRC_L7_BIT26            SL_TRC_CONCALL_(7, 0x04000000, false)
  #define SL_TRC_L7_BIT27            SL_TRC_CONCALL_(7, 0x08000000, false)
  #define SL_TRC_L7_ANYBIT           SL_TRC_CONCALL_ANY_(7, false)

  #define SL_TRC_L8_BIT0             SL_TRC_CONCALL_(8, 0x00000001, false)
  #define SL_TRC_L8_BIT1             SL_TRC_CONCALL_(8, 0x00000002, false)
  #define SL_TRC_L8_BIT2             SL_TRC_CONCALL_(8, 0x00000004, false)
  #define SL_TRC_L8_BIT3             SL_TRC_CONCALL_(8, 0x00000008, false)
  #define SL_TRC_L8_BIT4             SL_TRC_CONCALL_(8, 0x00000010, false)
  #define SL_TRC_L8_BIT5             SL_TRC_CONCALL_(8, 0x00000020, false)
  #define SL_TRC_L8_BIT6             SL_TRC_CONCALL_(8, 0x00000040, false)
  #define SL_TRC_L8_BIT7             SL_TRC_CONCALL_(8, 0x00000080, false)
  #define SL_TRC_L8_BIT8             SL_TRC_CONCALL_(8, 0x00000100, false)
  #define SL_TRC_L8_BIT9             SL_TRC_CONCALL_(8, 0x00000200, false)
  #define SL_TRC_L8_BIT10            SL_TRC_CONCALL_(8, 0x00000400, false)
  #define SL_TRC_L8_BIT11            SL_TRC_CONCALL_(8, 0x00000800, false)
  #define SL_TRC_L8_BIT12            SL_TRC_CONCALL_(8, 0x00001000, false)
  #define SL_TRC_L8_BIT13            SL_TRC_CONCALL_(8, 0x00002000, false)
  #define SL_TRC_L8_BIT14            SL_TRC_CONCALL_(8, 0x00004000, false)
  #define SL_TRC_L8_BIT15            SL_TRC_CONCALL_(8, 0x00008000, false)
  #define SL_TRC_L8_BIT16            SL_TRC_CONCALL_(8, 0x00010000, false)
  #define SL_TRC_L8_BIT17            SL_TRC_CONCALL_(8, 0x00020000, false)
  #define SL_TRC_L8_BIT18            SL_TRC_CONCALL_(8, 0x00040000, false)
  #define SL_TRC_L8_BIT19            SL_TRC_CONCALL_(8, 0x00080000, false)
  #define SL_TRC_L8_BIT20            SL_TRC_CONCALL_(8, 0x00100000, false)
  #define SL_TRC_L8_BIT21            SL_TRC_CONCALL_(8, 0x00200000, false)
  #define SL_TRC_L8_BIT22            SL_TRC_CONCALL_(8, 0x00400000, false)
  #define SL_TRC_L8_BIT23            SL_TRC_CONCALL_(8, 0x00800000, false)
  #define SL_TRC_L8_BIT24            SL_TRC_CONCALL_(8, 0x01000000, false)
  #define SL_TRC_L8_BIT25            SL_TRC_CONCALL_(8, 0x02000000, false)
  #define SL_TRC_L8_BIT26            SL_TRC_CONCALL_(8, 0x04000000, false)
  #define SL_TRC_L8_BIT27            SL_TRC_CONCALL_(8, 0x08000000, false)
  #define SL_TRC_L8_ANYBIT           SL_TRC_CONCALL_ANY_(8, false)


#define SL_TRC_MARK

class SlTrcExceptionNotification
{
  const char* m_pTraceText;
public:
  SlTrcExceptionNotification(const char* pTraceText)
    : m_pTraceText(pTraceText)
  {
  }

  ~SlTrcExceptionNotification()
  {
    if(m_pTraceText)
    {
      SL_TRC_L1_ANYBIT(m_pTraceText);
    }
  }

  void deactivate()
  {
    m_pTraceText = 0;
  }
};

#endif // SL_TRC_NO_MACROS
