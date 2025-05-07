// ////////////////////////////////////////////////////////////////////////////
/*! 
\file   sltmstore.h
  \author Reinhold Guenthner
  \date   04.2005
  \brief  Headerfile for class SlTmStore and related classes
          used to store tool and magazine data and device system data
          of OPERATEs (HMI SolutionLines) Toolmanagement Service.

  This file is part of the OPERATE (HMI Solutionline) Toolmanagement.

  These classes are also used by client software to store parts 
  of tool and magazine data and device system data.


  (C) Copyright Siemens AG A&D MC 2005-2006. All rights reserved.
*/
// ////////////////////////////////////////////////////////////////////////////


#if !defined(SL_TM_STORE_H)
#define SL_TM_STORE_H

#include "slhmitemplatesqt.h"

#include <QtCore/QTextStream>


// everybody who uses read and write lock of SlTmStore needs this:
#include <QtCore/QReadWriteLock>
#include <QtCore/QReadLocker>
#include <QtCore/QWriteLocker>

#include "sltmtomacontainer.h"
#include "sltmsys.h"
#include "sltmtomalist.h"
#include "sltmtomalistuni.h"
#include "sltmtomaexportimport.h"

// qt4: now direct by qt4 classes: #include "sltmsvcreadwritemutex.h"


#if !defined (SL_TM_UTILITIES_EXPORT)
#  if defined (WIN32) || defined (WIN64)
#     if defined (SL_TM_UTILITIES_EXPORTS)
#        define SL_TM_UTILITIES_EXPORT __declspec (dllexport)
#     else
#        define SL_TM_UTILITIES_EXPORT __declspec (dllimport)
#     endif
#  else
#      define SL_TM_UTILITIES_EXPORT
#  endif
#endif


/// \doxygen_should_skip_this
///   // @TODO
///   // Reinhold: 
///   // fuer MultiThreading spaeter einbauen:
///   // (z.B. "ClientSynch TOARead" und "Datenabgleich mit NC" und "ListenSort-TOAebergreifend")
///   // - TOA-spezifischer QMutex oder ACE-Mutex fuer getrennt read/write spaeter einbauen.
///   //   Das wird nicht zu Aenderungen der Methoden der Detail-Daten-Objekte fuehren, da es 
///   //   in den uebergeordneten Methoden aufgerufen wird. 
///   //   Dort muss man unterscheiden, 
///   //   - ob man nur in einem TOA agiert 
///   //     (einfache Strategie: man wartet einfach, bis man seinen Mutex hat)
///   //   - oder ob man mehrere TOA belegt 
///   //     (komplexere Strategie: entweder ein zusaetzlicher gemeinsamer Mutex oder
///   //     alle belegen die TOA-Mutexe in gleicher Reihenfolge; 
///   //     muss man sich noch genau ueberlegen, dass man keine DeadLocks baut.
///   //      besonders beruecksichtigen: "TOA-spezifische Aenderungen in TOA-uebergreifende Liste eintragen" und
///   //      "lese-Zugriff auf TOA-uebergreifende Liste ohne TOA-QMutex"; Listen-QMutex(e); 
///   //      kann sein, dass jede TOA-Aenderung gleichzeitig in TOA-uebergreifende Listen eingetragen
///   //      werden muss und somit immer die selben QMutexe belegt werden, was sich dann so 
///   //      verhaelt, wie wenn fuer alle TOAs und Listen nur ein einziger QMutex vorhanden waere.)
///   // - implicit Sharing der QVector, QMap usw. und Multithreading:
///   //   - Zugriffe nur koordiniert ueber QMutex, siehe oben
///   //   - deepCopy explizit durchfuehren, wenn die Daten in andere Threads uebergeben werden sollen 
///   //     und dann ohne TOA-QMutex weiterverarbeitet werden.
///   // - Randbedingung fuer schlichtes Lock/Unlock: es ist immer nur fuer kurze Dauer gelockt.
///   //   (besonders zu beruecksichtigen bei der Verarbeitung von Aenderungmitteilungen der NC.)
///   // 
///   // ---------------------------------------------------------------------------
///   // newer reflections:
///   // We use only 1 ReadWriteMutex for whole Store.
///   // 
///   //  Why not implement container specific locks now? 
///   //  They do not bring a lot of advandages: 
///   //  Changes in 1 container cause a synchronous update 
///   //  of lists, which potentially affects other containers, if a list has to join 
///   //  changes from these other containers. So we would need a mechanism, which detects 
///   //  lists affected containers and lock them all. 
///   //  We guess, there are mostly only needed data on solution line, so mostly they
///   //  will be contained in a list. And then after a complex computation the result 
///   //  mostly will be to lock all containers. So we implement now only one lock for 
///   //  all containers together.
///   //
///   //
///   //  Qt3: ReadWriteLock, ReadWriteLocker:
///   //  - 1 Mutex + 1 Semaphore
///   //  - Writer takes all Sema steps up to Limit
///   //  - Reader takes one Sema step
///   //  - Writer occupies Mutex during counting up to avoid deadlock against a further writer.
///   //    (Mutex is locked only during counting up, not all the time untill unlock is executed.)
///   //  - Reader and Writers do NOT use Mutex to count down
///   //
///   //  Qt4: QReadWriteLock, QReadLocker, QWriteLocker are new and do exactly what we need.
///   //       So we change our software to use them very directly without an addidional layer.
///   //
///   //
///   //  What to do, if we would use container locks:
///   //  (thoughts are written here, because this can be usefull for a 
///   //  other resource locks.)
///   //  How to occupy multi Containers?
///   //  If more than one locker tries to occupy more than one Container, 
///   //  they can do this in different order or with different speed.
///   //  A deadlock can occur.
///   //  To avoid this, we use a Mutex to let only one single locker 
///   //  exclusively set all of his locks.
///   //
///   //  MultiReaders and MultiWriters must use the Mutex while invoking his lock calls. 
///   //  (MultiReaders are involved, because they can wait for a 2nd readLock 
///   //  which is occupied by a writer, that is waiting for 
///   //  writeLock of readers first readLocked Container.)
///   //
///   //  SingleReaders and SingleWriters are not involved.
///   //
///   //  Better we use a master SlTmSvcReadWriteMutex which is used by its
///   //  SlTmSvcReadWriteMutexLocker.
///   //  To lock multi ordinary SlTmSvcReadWriteMutex-es:
///   //  a SlTmSvcReadWriteMutexMultiLocker is required, 
///   //  which uses master SlTmSvcReadWriteMutexLocker during lock calls to 
///   //  multi ordinary SlTmSvcReadWriteMutex-es.
///   //  SlTmSvcReadWriteMutexMultiLocker-s parameters: master SlTmSvcReadWriteMutex and 
///   //  a QMap or ValueVector of ordinary SlTmSvcReadWriteMutex, maybe for each ordinary 
///   //  a read or readwrite accessmode. Usage of QMap could give a chance for control of 
///   //  sequence of lock of ordinary SlTmSvcReadWriteMutex.
///   // 
///   // 
///   //  To delete a mutex/semaphore: if locked: behavior is undefined.
///   //  ??? is it a good idee, to get writeaccess before delete it?
/// \end_doxygen_should_skip_this






// ////////////////////////////////////////////////////////////////////////////


// ////////////////////////////////////////////////////////////////////////////
/*! 

<!-- doxygen_should_skip_this

Work around for a doxygen error:

The next conditional text is shown in page "mainpage". 
Doxygen does shift this text to the subsequent page.

If following conditional text would be written after backslash_mainpage,
an error would happen: all text behind end of conditional text would be shifted to 
subsequent page "compositionhierarchy ..." if condition is false, 
which would not be what we want.

doxygen_should_skip_this -->



\cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC 

\n
\n
<CENTER> 
<b>
This extended documentation has been made for \n
"OPERATE(HMI-SolutionLine)-core-project" internal use only. \n
\n
In addition it contains parts, which are hidden in \n
Open Architecture Programming Interface Reference Documentation. \n
\n
</b>
In general these additional parts may be changed or canceled at any time, \n
but usually this does not take place, especially if they are already in use. \n
</CENTER>
\n
\n

<!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond 



  \mainpage 

  \n
  \n
  This is the 
  public <b>Open Architecture Programming Interface Reference Documentation</b> 
  of OPERATE (HMI Solutionline) Toolmanagement.
  \n
  \n

  OPERATE (HMI Solutionline) Toolmanagement consists of 
  - a service component (sltmservice)  
  - a client side service adapter (sltmserviceadapter) 
  - two lightweight client user interfaces SlTmQCmd and SlTmCmd (which belong to sltmserviceadapter)
  - a lot of utility classes (i.e. to store and manipulate specific data) (sltmutities)
  .
  \n

  sltmserviceadapter and sltmservice are connected 
  internaly by a CORBA interface, which has not 
  been released to the public.

  To prevent client from dealing with sltmserviceadapter 
  and to make access to sltmservices easier,
  two lightweight user interfacess SlTmQCmd and SlTmCmd exist 
  as the only interfaces, to be used by Qt-GUI clients.

  SlTmQCmd offers Qt signals to integrate seamless into
  Qt clients signal and slot environment. 
  SlTmQCmd should be used by clients from within Qt main thread.

  SlTmCmd offers an interface which allows client to call it from within a free thread. 
  Client must implement its own class derived from pure virtual class SlTmCmdCallBackI
  and receives the asynchronous results by callback functions defined in class SlTmCmdCallBackI.

  Public user (open architecture) documentation consists of interface description of 
  sltmserviceadapters SlTmQCmd / SlTmCmd and sltmutilities classes, 
  whereas sltmservice and the other parts of sltmserviceadapter do their work behind the scenery.

  Even though some internal classes and methods can be discovered by reading header files, 
  these classes and methods are not released to the public user (open architecture) documentation. \n
  (These sections are marked in header files with a string like "DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC".)

  Do NOT use such classes and methods, which are not contained in public user (open architecture) documentation. \n
  (Or do not complain about changes and errors.)

  SlTmCmd and SlTmCmdCallBackI are not releases to the public user (open architecture) documentation yet. \n
  \n
  \n
  Using SlTmQCmd / SlTmCmd, client can i.e.
  - create and delete tools in NC
  - load, unload, move tool in relation to magazin places
  - find magazin places in NC
  - subscribe for notification about NC's power on reset
  - subscribe for sorted lists of tools and places inclusive notifies about changed data
  - get information about tool managment related NC data
  - get information about data in relation to access levels
  .
  \n

  SlTmQCmd / SlTmCmd interface offers some sltmutilities classes for data exchange, 
  which are also used within sltmservice, to store and to manipulate 
  system data and tool and magazine data 
  of all connected devices (i. e. NCU, Transline PCU).
  \n
  \n
  \n
    

  \section store_class_overview sltmservice Data Store / sltmutilities Data Classes Overview

  Here sltmservice data store is described. 

  It consists of sltmutilities data classes. 

  Data store itself is not accessible by SlTmQCmd / SlTmCmd directly but 
  some data classes are used in SlTmQCmd / SlTmCmd interface.

  Therefore knowledge of OPEARTEs Toolmangement Service data store
  coherences helps to understand SlTmQCmd / SlTmCmd interface.
  
  To navigate through this classes, you can start with SlTmStore, which contains all other 
  system, tool and magazine data of OPERATESs (HMI SolutionLines) Toolmanagement Service. 

  Another good starting point for navigation through data, is page \ref compositionhierarchy.

  Classes with names like \c %SlTmSys.... contains devices system data, \n
  classes with names like \c %SlTmToMa.... contains tool and magazine data, 
  inclusive magazine configuration.
  \n
  \n
  \n
  Some of common used typedefs and enums are contained in file sltmutil.h and class SlTmUtil. 
  \n
  \n
  \n
  The one and only object of class SlTmStore in toolmanagment service contains these data:
  - system data SlTmSys of connected devices (NC or Transline PLC)
  - a collection SlTmToMaContainerColl of data containers SlTmToMaContainer 
  - and a collection SlTmToMaLists of data lists SlTmToMaList
  .
  \n
  \n
  Each object of class SlTmToMaContainer contains all data of 
  - one TOA (Tool Offset Area) of a NCU 
  - or of one Automotive Transline PLC 
  - and will be extented, to contain data of one tool cabinet 
  - or one tool catalogue
  .
  \n
  \n
  Each SlTmToMaContainer consists of data of classes:
  - SlTmToMaContainerSize: number of data values in contained data classes 
  - SlTmToMaContainerData: general data values of container
  - SlTmToMaContainerTypeSpecData: container type specific data values of container
  - SlTmToMaToolColl: Collection of (e.g. a TOAs) all Tools SlTmToMaTool
  - SlTmToMaMagConf: Magazine configuration 
    - SlTmToMaMagConfData: magazine configurations general data
    - SlTmToMaMagColl: Collection of all magazines inclusive places and tNo tool numbers of loaded tools.
    - SlTmToMaDistOrdMagColl: Relations and distances from ordinary magazines 
                              to special magazine (buffer and load) places.
                              See also page \ref pageoverviewmagazineconf.
    - SlTmToMaDistSpecMagColl: Relations and distances from special magazines (buffer and load) places 
                              to ordinary magazines
                              See also page \ref pageoverviewmagazineconf.
    .
  - SlTmToMaAdaptColl: Collection of magazine location adapter data (old data type NOT for new development)
  - SlTmToMaAdaptUniColl: Collection of adapter data (new data type for new development)
  .
  
  For complete class listing see: \ref compositionhierarchy.
  \n
  \n
  Nearly all subordinate data classes of lowest level use classes SlTmToMaIntData, 
  SlTmToMaDoubleData, SlTmToMaBoolData or SlTmToMaVariantData as composition part.
  \n
  \n
  \n
  \n
  \n
  If you need knowledge about 
  - interrelationship between NC toolmanagements OPI / BTSS data module interface and sltmservices data store, 
  - interrelationship within sltmservices data store,
  - interrelationship between NC-PI-Services and SlTmQCmd methods,
  .
  see \ref crossreferenceopi. \n
  \n
  \n
  This page contains information about 
  - class names, 
  - data kind and data index enums, 
  - a short description of data, 
  - names of methods to get references to data
  - interrelationship to OPI / BTSS data
  - and SlTmQCmd methods and associated NC-PI-Services.
  .
  \n
  \n
  \n
  \n
  \n
  \n

  \section seealso See also
  - \ref compositionhierarchy 
  - \ref crossreferenceopi
  - \ref typicalmethods 
  - \ref pageoverviewmagazineconf
  - \ref exportimport 
  - \ref multithreading 
  - \ref delayedupdate 
  - \ref versionhistory 
  .
  \n
  \n
  \n


  \section copyright Copyright
  (C) Copyright Siemens AG 2005. All rights reserved.
  
*/
// ////////////////////////////////////////////////////////////////////////////


/*!
  \page versionhistory What's new or changed in software version
  \n
  \n
  \n
  <b>What's new in 04.94.00:</b> \n
  \n
  -# <b>New data added.</b> \n
     New channal state data on BTSS is added \a acIsAddChan. It describes whether channel is a handlings channel. \n
     $MCS_FUNCTION_MASK_TECH_0 is added. It is bit coded and with technology 0 every bit tells if a functionality
     has to be hiden in hmi \n
  .
  \n
  \n
  \n
  <b>What's new in 04.93.00:</b> \n
  \n
  -# <b>To support crossheads a new adapter structure is introduced which is capable of reflecting
     magazine place adapter and alternating a new multitool place adapter data.</b>\n
     Crosshead is in service a pair of a multitool with only one place and adapter with type = 2
     on this place (multitool place adapter, $TC_MTPP7=adaptNo).\n 
     For this purpose new methods in SlTmQCmd and SlTmCmd are implemented to create and to delete
     such pairs.\n
     Those functions are:\n
     -# int SlTmQCmd::createMultiToolWithAdaptersAndLoadIntoMagAsync( int containerNo, const SlTmToMaMultiTool* pMultiTool, int destMagNo, int destMagPlaceNo, bool overwriteLoadingPoint, SlTmInfo& rInfo, int scope = SlTmCmdDef::SEARCH_PLACE_SCOPE_TO_UNIT, int timeout = 100, int loadingPointNo = 0, bool deleteFragments = true, bool mTNoForced = false, const SlTmToMaAdaptUniConstPtrVecType& adapterVect = SlTmToMaAdaptUniConstPtrVecType(0), bool adaptNoForced = false, int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO)
     -# int SlTmQCmd::getAllAdapterUniNoSync(int containerNo, QVector<SlTmToMaAdaptUniNoType>& rResultAdaptNoVect, SlTmInfo& rInfo)
     -# int SlTmQCmd::createMultiToolWithAdaptersAsync( int containerNo, const SlTmToMaMultiTool* pMultiTool, SlTmInfo& rInfo, int timeout = 100, bool mTNoForced = false, const SlTmToMaAdaptUniConstPtrVecType& adapterVect = SlTmToMaAdaptUniConstPtrVecType(0), bool adaptNoForced = false, bool deleteFragments = true, int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO)
     -# int SlTmQCmd::deleteMultiToolWithAdaptersAsync(int containerNo, int mTNo, bool deleteIfNotEmpty, SlTmInfo& rInfo, bool alsoDeleteToolsInside = true, int reservedPar = 0)
     -# int SlTmQCmd::unloadMultiToolFromMagAndDeleteWithAdaptersAsync(int containerNo, int mTNo, int srcMagNo, int srcMagPlaceNo, bool deleteIfNotEmpty, SlTmInfo& rInfo, int timeout = 100, bool alsoDeleteToolsInside = true, int loadingPointNo = 0, int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO)
     -# int SlTmQCmd::readDataSync(int containerNo, const QVector<SlTmToMaAdaptUniNoType>& rReadAdapterSpecVec, QVector<SlTmToMaAdaptUniData>& rResultAdapterDataVec, QBitArray& rHasError, SlTmInfo& rInfo)
     -# int SlTmQCmd::createAdapterAsync(int containerNo, const SlTmToMaAdaptUniData* pAdapterData, SlTmInfo& rInfo, bool adaptNoForced = false, int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO)
     -# int SlTmQCmd::deleteAdapterAsync(int containerNo, int adaptNo, SlTmInfo& rInfo, int reservedPar = 0)
     \n 
     .
     \n
     Adapter for magazine location have type = 1. For creating adapter new PI calls are there _N_TMCRAD and _N_TMDLAD.\n 
     Old adapter for magazine location can be created old-fashioned too.\n New adapter data structure includes both adapter data (magazine location and
     multitool place adapter). See SlTmToMaAdaptUniColl and SlTmToMaAdaptUniData.\n
     Also SlTmMassData2ToolMagListChangedData has been extended to recive adapter data from new data structure.\n
  .
  \n
  \n
  \n
  <b>What's new in 04.90.00 (Helsinki):</b> \n
  \n
  -# <b>New, support of external containers in container collection</b> \n
     and methods in SlTmQCmd and SlTmCmd: \n
     SlTmQCmd::copyExternalContainer2ServiceSync() \n
     SlTmQCmd::deleteExternalContainerFromServiceSync() \n
     \n
     External containers must have a container id bigger than 1000. \n
     Therefore use SlTmToMaContainerColl::CONNO_FIRST_EXTERNAL_CONTAINER. \n
     Use of external containers: \n
     You create a local container in your application. \n
     Perhaps you fill the container with data from an ini file \n
     using the method SlTmToMaContainer::importToIniStyle(). \n
     Then you can copy the container to SlTmService \n
     using the method SlTmQCmd::copyExternalContainer2ServiceSync(). \n
     In many cases you can handle an external container like a normal \n
     nc container. As an exception you can not us magazine functions. \n
     \n
  .
  \n
  \n
  \n
  <b>What's new in 04.08.03 (Georgetown SP3):</b> \n
  \n
  -# <b>New, support of tool user data with type string, see MD 18095</b> \n
     and corresponding enum value in SlTmUtil::DataKindEnum: \n
     SlTmUtil::DATA_KIND_DEVICE_TOOL_USER_TYPES. \n
     \n
     These data only exist in NC, if OPI / BTSS data /Nck/Configuration/nckVersion \n
     has a value equal or greater than 128010G, see SlTmSysDeviceData::DEV_DATA_IDX_NCK_VERSION. \n
     \n
  -# <b>Fix enum values in ..._USER_30, ..._USER_40, ..._USER_50, ..._USER_60</b> \n
     there was an offset of 10 in this four items. \n
     in SlTmToMaToolUser::ToolUserIdxEnum \n
     in SlTmToMaEdgeUser::EdgeUserIdxEnum \n
     in SlTmToMaMagUser::MagUserIdxEnum \n
     in SlTmToMaPlaceUser::PlaceUserIdxEnum \n
     in SlTmToMaMultiToolUser::MultiToolUserIdxEnum \n
     in SlTmToMaMultiToolPlaceUser::MultiToolPlaceUserIdxEnum \n
     \n
  .
  \n
  \n
  \n
  <b>What's new in 04.07.01 (Frankfurt SP1):</b> \n
  \n
  -# <b>New grinding data "dressing program name" and "dressing program path"</b> \n
     and corresponding enum values in SlTmToMaToolGrind::ToolGrindIdxEnum: \n
     SlTmToMaToolGrind::TOOL_GRIND_DRSPROG and SlTmToMaToolGrind::TOOL_GRIND_DRSPATH. \n
     \n
     These data only exist in NC, if OPI / BTSS data /Nck/Configuration/nckVersion \n
     has a value equal or greater than 990600.0, see SlTmSysDeviceData::DEV_DATA_IDX_NCK_VERSION. \n
     For convenience this is also indicated by value "true" (QVariant(bool(true))) of \n
     SlTmToMaContainerData::CONTAINER_DATA_EXIST_GRINDING_DRS_DATA and \n
     SlTmSysDeviceData::DEV_DATA_IDX_EXIST_GRINDING_DRS_DATA. \n
     \n
  -# <b>Further methods</b> in class SlTmToMaToolGrind: \n
     -# int SlTmToMaToolGrind::setVal(const int idx, const QString& rSourceVal)
     -# int SlTmToMaToolGrind::setVal(const int idx, const int& rSourceVal)
     -# int SlTmToMaToolGrind::val(const int idx, QString& rTargetVal) const
     -# int SlTmToMaToolGrind::val(const int idx, int& rTargetVal) const
     .
     \n
  -# <b>New enum</b> SlTmToMaPlaceData::PlaceKindValueEnum, \n
     in particular SlTmToMaPlaceData::PLACE_KIND_VALUE_SPINDLE. \n
     \n
  -# <b>Changed list element correlation of revolver place tool when located on a non-spindle buffer place:</b>\n
     If tool (or multitool) owns a place within a revolver magazine, \n
     (when tools myMag / myPlace data points to a revolver magazin place) \n
     tool is exeptionally displayed in lists on this revolver magazine place, \n
     even if tools current location (inMag / inPlace data of tool) is \n
     a buffer magazine place (inMag = 9998) of place kind "spindle". \n
     \n
     This handling is necessary, because NC must temporary \n
     change tools current location data to a spindle place, \n
     when tool becomes the NC-program-current tool, \n
     while tool physically remains on its revolver magazine place. \n
     \n
     In the past, detection of this display exeption did not \n
     consider place kind "spindle" but only magazine kind "buffer", \n
     so tool was faultily displayed on revolver, \n
     even if its current location was a buffer place of a non-spindle place kind, \n
     like a gripper, pickup or shuttle, where tool pysically was located. \n
     \n
     Yet, tool is displayed on its non-spindle buffer place, \n
     even if owner magazine is a revolver. \n
  .
  \n
  \n
  \n
  <b>What's new in 04.07 (Frankfurt) since 04.06 (Edinburgh):</b> \n
  \n
  -# <b>Number of user ("oem") data has bee extended from 10 to 64.</b> (If nck version >= 990000) \n
    -# Tool User-Param,             $TC_TPC64,   SlTmToMaToolUser::TOOL_USER_64,                       SlTmToMaToolUser,           SlTmUtil::DATA_KIND_TOOL_USER,            BTSS / OPI "/Tool/User/data"                    
    -# Edge User-Param,             $TC_DPC64,   SlTmToMaEdgeUser::EDGE_USER_64,                       SlTmToMaEdgeUser,           SlTmUtil::DATA_KIND_EDGE_USER,            BTSS / OPI "/Tool/User/edgeData"                
    -# Edge Supervision-User-Param, $TC_MOPC64,  SlTmToMaEdgeSupUser::EDGE_SUPUSER_64,                 SlTmToMaEdgeSupUser,        SlTmUtil::DATA_KIND_EDGE_SUPUSER,         BTSS / OPI "/Tool/Supervision/userData",         
    -# Multitool User-Param,        $TC_MTPC64,  SlTmToMaMultiToolUser::MULTITOOL_USER_64,             SlTmToMaMultiToolUser,      SlTmUtil::DATA_KIND_MULTITOOL_USER,       BTSS / OPI "/Tool/MT/userData"                  
    -# Multitool Place User-Param,  $TC_MTPPC64, SlTmToMaMultiToolPlaceUser::MULTITOOL_PLACE_USER_64 , SlTmToMaMultiToolPlaceUser, SlTmUtil::DATA_KIND_MULTITOOL_PLACE_USER, BTSS / OPI "/Tool/MTPlace/userData"             
    -# Magazine User-Param,         $TC_MAPC64,  SlTmToMaMagUser::MAG_USER_64,                         SlTmToMaMagUser,            SlTmUtil::DATA_KIND_MAG_USER,             BTSS / OPI "/Tool/MagazineDescription/userData" 
    -# Place User-Param,            $TC_MPPC64,  SlTmToMaPlaceUser::PLACE_USER_64,                     SlTmToMaPlaceUser,          SlTmUtil::DATA_KIND_PLACE_USER,           BTSS / OPI "/Tool/Magazine/userPlaceData"       
    -# In case of a high number of place user data in combination with a high number of places within a magazine, \n
       a BTSS/OPI address limit can apply, which is indicated by an alarm and forces OPERATE to switch OFF handling of magazine place user data. \n
       Currently the limit of the product of both values is about 32767. \n
       For handling of BTSS/OPI address limitation of product of "number of place user data" and "number of places of a magazine" see: 
      -# SlTmToMaContainerData::CONTAINER_DATA_EXIST_PLACE_USER_DATA_NUM_LIMIT
      -# SlTmToMaContainerData::CONTAINER_DATA_IS_PLACE_USER_DATA_NUM_LIMIT_SOMEWHERE_EXCEEDED
      -# SlTmToMaContainerData::CONTAINER_DATA_IS_THIS_CONTAINER_CAUSING_PLACE_USER_DATA_NUM_LIMIT_EXCEEDANCE
      -# SlTmSysDeviceData::DEV_DATA_IDX_EXIST_PLACE_USER_DATA_NUM_LIMIT
      -# SlTmSysDeviceData::DEV_DATA_IDX_IS_PLACE_USER_DATA_NUM_LIMIT_SOMEWHERE_EXCEEDED
      -# SlTmToMaMagData::MAG_DATA_PLACE_USER_DATA_NUM_LIMIT
      .
    .
  -# <b>Magazine and place user and appl data type "double" is supported.</b> (If nck version >= 990000) \n
     New BTSS / OPI module interface is internally used to exchange data in double format between NC and OPERATE. \n
     In the past old BTSS / OPI module interface did limit exchange to integer format \n
     and therefore OPERATE could not support double format. \n
     Now data is stored in OPERATEs data store internally as QVariant and can be accessed by clients in double format. \n
     Before storage and access methods had been of type integer. \n
     Old data access as integer keeps on working, \n
     additional new data access as double is available. \n
     Old integer client code and new double client code can coexist. \n
     Change has been made in binary code compatible matter. \n
     Under rare circumstance (when client did use implicit type conversion in val() and setVal() methods), \n
     an ambiguity can be discovered by compiler during compilation of client source code. \n
     This must be resolved by changing clients source code to using exclusively the data types of methods signature.
    -# See also: \n
      -# SlTmSysDeviceData::DEV_DATA_IDX_EXIST_MAG_AND_PLACE_USER_AND_APPL_DATA_DOUBLE_OPI
      -# SlTmToMaContainerData::CONTAINER_DATA_EXIST_MAG_AND_PLACE_USER_AND_APPL_DATA_DOUBLE_OPI
      -# Method int SlTmToMaMagUser::val(const int idx, double& rTargetVal) const
      -# Method int SlTmToMaMagAppl::val(const int idx, double& rTargetVal) const
      -# Method int SlTmToMaPlaceUser::val(const int idx, double& rTargetVal) const
      -# Method int SlTmToMaPlaceAppl::val(const int idx, double& rTargetVal) const
      -# Method int SlTmToMaMagUser::setVal(const int idx, const double& rSourceVal)
      -# Method int SlTmToMaMagAppl::setVal(const int idx, const double& rSourceVal)
      -# Method int SlTmToMaPlaceUser::setVal(const int idx, const double& rSourceVal)
      -# Method int SlTmToMaPlaceAppl::setVal(const int idx, const double& rSourceVal)
      .
    .
  -# <b>Further values in enum SlTmToMaMagData::MagDataIdxEnum:</b> (If nck version >= 990000) 
    -# SlTmToMaMagData::MAG_DATA_DIM2 ($TC_MAP7)
    -# SlTmToMaMagData::MAG_DATA_PLACE_USER_DATA_NUM_LIMIT (magPlaceUserDataNumLimit, unsigned integer)
    .
  -# <b>Further value in enum SlTmToMaMachineData::MachineDataEnum:</b> (If nck version >= 970000)
    -# SlTmToMaMachineData::MACH_DATA_IDX_TOOL_LENGTH_CONST_T ($SC_TOOL_LENGTH_CONST_T (42942))
    .
  .
  \n
  \n
  \n
  \n
  \n
  <hr>
  \n
  \n
  <b>What's new in 04.06.00.00 (Edinburgh) since 04.05.00.00 (Dublin):</b>
  \n
  -# <b>Further methods</b> in existing classes \n
     <b> to read and write data values via integer data type</b>, \n
     if value is castable to integer: 
    -# Method int SlTmToMaDoubleData::setVal(const int idx, const int& rSourceVal)
    -# Method int SlTmToMaDoubleData::val(const int idx, int& rTargetVal) const
    -# Method int SlTmToMaEdgeTo::setVal(const int idx, const int& rSourceVal)
    -# Method int SlTmToMaEdgeTo::val(const int idx, int& rTargetVal) const
    -# Method int SlTmToMaEdgeToTr::setVal(const int idx, const int& rSourceVal)
    -# Method int SlTmToMaEdgeToTr::val(const int idx, int& rTargetVal) const
    -# Method int SlTmToMaEdgeUser::setVal(const int idx, const int& rSourceVal)
    -# Method int SlTmToMaEdgeUser::val(const int idx, int& rTargetVal) const
    -# Method int SlTmToMaEdgeAppl::setVal(const int idx, const int& rSourceVal)
    -# Method int SlTmToMaEdgeAppl::val(const int idx, int& rTargetVal) const
    -# Method int SlTmToMaEdgeSup::setVal(const int idx, const int& rSourceVal)
    -# Method int SlTmToMaEdgeSup::val(const int idx, int& rTargetVal) const
    -# Method int SlTmToMaEdgeSupUser::setVal(const int idx, const int& rSourceVal)
    -# Method int SlTmToMaEdgeSupUser::val(const int idx, int& rTargetVal) const
    -# Method int SlTmToMaEdgeSupAppl::setVal(const int idx, const int& rSourceVal)
    -# Method int SlTmToMaEdgeSupAppl::val(const int idx, int& rTargetVal) const
    .
  -# <b>Further values in enum</b> SlTmToMaEdgeTo::EdgeToIdxEnum:
    -# SlTmToMaEdgeTo::EDGE_TO_BASIC_ROTATION_ANGLE   ($TC_DPROT basic rotation angle)
    .
  -# <b>Further values in enum</b> SlTmToMaEdgeToTr::EdgeToIdxEnum:
    -# SlTmToMaEdgeToTr::EDGE_TO_BASIC_ROTATION_ANGLE ($TC_DPROT basic rotation angle)
    .
  -# <b>Intermediate messages for technological functions of SlTmQCmd</b>, \n
     see also parameter "int intermediateLevel" in asynchronous technological methods, \n
     source code compatible by default value. 
  -# <b>Further values in enum</b> SlTmCmdDef::SlTmCmdStateEnum:
    -# SlTmCmdDef::STATE_INTERMEDIATE
    .
  -# <b>New enum</b> SlTmCmdDef::SlTmTechnoFuncIntermediateInfo:
    -# SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO
    -# SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1
    -# SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2
    .
  -# <b>Further values in enum</b> SlTmInfo::subFunctionsEnum:
    -# SlTmInfo::SUB_FUNC_POSITION_MAG
    .
  -# <b>Improved errorhandling for technological functions of SlTmQCmd</b>
  -# <b>Changes</b> in SlTmInfo::SlTmInfo():
    -# <b>Changed (source code compatible)</b> SlTmInfo::SlTmInfo()
    -# <b>New method</b> SlTmInfo::infoVersion()
    -# <b>New method</b> SlTmInfo::setInfoVersion()
    .
  -# <b>Further values in enum</b> SlTmInfo::infoVersionEnum:
    -# SlTmInfo::INFO_VERSION_V01
    -# SlTmInfo::INFO_VERSION_V02
    .
  -# <b>Further values in enum</b> SlTmInfo::infoIdValuesEnum:
    -# SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE
    -# SlTmInfo::ID_SVC_DELAY_BY_MAGAZINE_STATE
    -# SlTmInfo::ID_SVC_SUB_FUNCTION_DONE
    -# SlTmInfo::ID_SVC_MOVE_STARTED
    -# SlTmInfo::ID_SVC_POSITIONING_STARTED
    -# SlTmInfo::ID_SVC_NO_MORE_MULTITOOLS
    -# SlTmInfo::ID_SVC_NO_MORE_MULTITOOL_LOCATIONS
    -# SlTmInfo::ID_SVC_WRONG_TOOL_NAME
    -# SlTmInfo::ID_SVC_WRONG_DUPLO_NO
    -# SlTmInfo::ID_SVC_WRONG_TOOLHOLDER_NO
    -# SlTmInfo::ID_SVC_GENERAL_PI_ERROR
    -# SlTmInfo::ID_SVC_OPTION_NOT_SET
    -# SlTmInfo::ID_SVC_TM_NOT_ACTIVE
    -# SlTmInfo::ID_SVC_FUNC_MT_NOT_ACTIVE
    -# SlTmInfo::ID_SVC_WRONG_CUTTING_EDGE_OR_D_NO
    -# SlTmInfo::ID_SVC_WRONG_TOOL_NO
    -# SlTmInfo::ID_SVC_PI_INVALID_ARGUMENT
    -# SlTmInfo::ID_SVC_NO_MORE_TOOLS
    -# SlTmInfo::ID_SVC_NO_MORE_CUTTING_EDGES
    -# SlTmInfo::ID_SVC_WRONG_MAGAZINE_NO
    -# SlTmInfo::ID_SVC_DUPLO_NO_ALREADY_EXISTING
    -# SlTmInfo::ID_SVC_MONITORING_FOR_TOOL_NOT_ACTIVE
    -# SlTmInfo::ID_SVC_WRONG_WEAR_COMPOUND_NO
    -# SlTmInfo::ID_SVC_NO_ACTIVE_WEAR_COMPOUND
    -# SlTmInfo::ID_SVC_WRONG_MULTITOOL_NAME
    -# SlTmInfo::ID_SVC_WRONG_MULTITOOL_NO
    -# SlTmInfo::ID_SVC_WRONG_MULTITOOL_LOCATION_NUMBER
    -# SlTmInfo::ID_SVC_MULTITOOL_IS_LOADED
    -# SlTmInfo::ID_SVC_MULTITOOL_CONTAINS_ACTIVE_TOOL
    -# SlTmInfo::ID_SVC_MULTITOOL_CONTAINS_TOOL_WITH_ACTIVE_CORR
    -# SlTmInfo::ID_SVC_PREVIOUS_MOVE_NOT_READY
    -# SlTmInfo::ID_SVC_NO_FITTING_MAG_LOCATION_FOUND
    -# SlTmInfo::ID_SVC_TOOL_IS_LOADED
    -# SlTmInfo::ID_SVC_MAGAZINE_STATE_NOT_OK
    -# SlTmInfo::ID_SVC_TO_UNIT_NOT_VALID
    -# SlTmInfo::ID_SVC_WRONG_INTERNAL_MAGAZINE_NO
    -# SlTmInfo::ID_SVC_WRONG_MAG_LOCATION_NUMBER
    .
  -# <b>Tool and magazine list data:</b> for optimized transport and improved access: \n
     (Use SlTmMassData2ToolMagListChangedData instead of deprecated SlTmMassDataToolMagListChangedData)
    -# <b>New classes</b>:
      -# Class SlTmMassData2ToolMagListChangedData
      -# Class SlTmMassData2ToolMagListElData
      -# Class SlTmMassDataExportImportMask
      -# Class SlTmToMaContainerNoToolNo
      -# Class SlTmToMaContainerNoMultiToolNo
      -# Class SlTmToMaContainerNoMagNoPlaceNo
      -# Class SlTmToMaContainerNoAdaptNo
      .
    -# <b>New typedefs:</b>:
      -# typedef QMap<SlTmListElNoType,                SlTmMassData2ToolMagListElData> ::SlTmMassData2ToolMagListElCollMapType
      -# typedef QMap<SlTmToMaContainerNoToolNo,       SlTmToMaTool>                   ::SlTmMassDataToolCollMapType
      -# typedef QMap<SlTmToMaContainerNoMultiToolNo,  SlTmToMaMultiTool>              ::SlTmMassDataMultiToolCollMapType
      -# typedef QMap<SlTmToMaContainerNoAdaptNo,      SlTmToMaAdaptData>              ::SlTmMassDataAdaptDataCollMapType
      -# typedef QMap<SlTmToMaContainerNoMagNoPlaceNo, SlTmToMaPlace>                  ::SlTmMassDataPlaceCollMapType
      -# typedef QMap<SlTmToMaContainerNoToolNo,       bool>                           ::SlTmToMaListConnectedToolNoCollMapType
      -# typedef QMap<SlTmToMaContainerNoMultiToolNo,  bool>                           ::SlTmToMaListConnectedMultiToolNoCollMapType
      -# typedef QMap<SlTmToMaContainerNoAdaptNo,      bool>                           ::SlTmToMaListConnectedAdaptNoCollMapType
      -# typedef QMap<SlTmToMaContainerNoMagNoPlaceNo, bool>                           ::SlTmToMaListConnectedPlaceNoCollMapType
      .
    -# <b>New methods:</b>
      -# Method int SlTmQCmd::subscribeToolMagList(const QString& rKey, const SlTmMassDataExportImportMask& parMassDataExportImportMask, const SlTmToMaExportImportMask& parToMaDataExportImportMask, SlTmMassDataImportI* pImportMassData, SlTmInfo& rInfo)
      -# Method bool SlTmToMaTool::isChanged(void)const
      -# Method void SlTmToMaTool::setChanged(const bool& isChanged)
      -# Method void SlTmToMaToolColl::setChanged(const bool& isChanged)
      -# Method bool SlTmToMaMultiTool::isChanged(void)const
      -# Method void SlTmToMaMultiTool::setChanged(const bool& isChanged)
      -# Method void SlTmToMaMultiToolColl::setChanged(const bool& isChanged)
      -# Method bool SlTmToMaPlace::isChanged(void)const
      -# Method void SlTmToMaPlace::setChanged(const bool& isChanged)
      -# Method void SlTmToMaPlaceColl::setChanged(const bool& isChanged)
      -# Method bool SlTmToMaMag::isChanged(void)const
      -# Method void SlTmToMaMag::setChanged(const bool& isChanged)
      -# Method void SlTmToMaMagColl::setChanged(const bool& isChanged)
      -# Method bool SlTmToMaAdaptData::isChanged(void)const
      -# Method void SlTmToMaAdaptColl::setChanged(const bool& isChanged)
      .
    .
  -# <b>Read and write SlCap-local variable: </b> \n
     Consider special parameter specification when using data kind enum SlTmUtil::DATA_KIND_SPECIAL_DATA_CAP_LOCAL_VARIABLE in:
    -# SlTmQCmd::readDataSync(int containerNo, SlTmSvcSpecStoreElementsVectorType& rReadSpecVec, QBitArray& rHasError, SlTmInfo& rInfo);
    -# SlTmQCmd::writeDataSync(int containerNo, const SlTmSvcSpecStoreElementsVectorType& rWriteSpecVec, QBitArray& rHasError, SlTmInfo& rInfo);
    .
  -# <b> Convert between key-value-pairs of a QMap and a QString:</b> \n
     (for coding in HMI_ADV-WIZARD-GUI-Cursor-Current-Tool-and-Magazin-NCDDE-Variable compatible style)
    -# static unsigned int SlTmQCmd::encodeKeyValuePairsString(const QMap<QString, QString>& rInputMap, QString& rEncodedString);
    -# static unsigned int SlTmQCmd::decodeKeyValuePairsString(const QString& rEncodedString, QMap<QString, QString>& rOutputMap);
    .
  -# <b>Combination of multittool and magazine place adapter is supported now:</b> \n
      AdaptNo of multitool data is supported now this way: \n
      Since NC does not deliver this data on BTSS/OPI interface nowadays, \n
      data is computed by OPERATE sltmservice meanwhile. \n
      NC's data will be considered by OPERATE in future versions, \n
      when NC is extended to deliver multitools adaptNo via BTSS/OPI interface. \n
      These OPERATE sltmservice OA interface data have been extended:
    -# SlTmToMaMultiToolData: SlTmToMaMultiToolData::MultiToolDataIdxEnum: SlTmToMaMultiToolData::MULTITOOL_DATA_ADAPTNO
    -# SlTmToMaContainerData: SlTmToMaContainerData::ContainerDataIdxEnum: SlTmToMaContainerData::CONTAINER_DATA_EXIST_ADAPTNO_IN_NC_MULTITOOL_DATA \n
       (Indicates if SlTmToMaMultiToolData::MULTITOOL_DATA_ADAPTNO is computed by OPERATE or delivered by NC)
    -# SlTmSysDeviceData: SlTmSysDeviceData::SysDeviceEnum: SlTmSysDeviceData::DEV_DATA_IDX_EXIST_ADAPTNO_IN_NC_MULTITOOL_DATA \n
       (Indicates if SlTmToMaMultiToolData::MULTITOOL_DATA_ADAPTNO is computed by OPERATE or delivered by NC)
    .
  -# <b>Binary compatibility of version 04.06.00.00 to version 04.05.00.00 is kept. </b>
  .
  \n
  \n
  \n
  <b>For internal use only:</b> \n
  Changes of these methods, classes and files have been made for internal use only and may be changed or canceled at any time. \n
  They are hidden in Open Architecture Documentation: \n
  \n
  -# <b>Improvements of methods to export and import data in ToIni format style:</b>
    -# <b>ToIni style format import</b> of tool data ("Read in tool setup data"), importToIniStyle():
      -# <b>TC_MOPCS</b> and <b>TC_ECP</b> data import is done now.
      -# Data <b>TC_DPV3, TC_DPV4, TC_DPV5</b> is no longer mistaken 
         for <b>TC_DPVN3, TC_DPVN4, TC_DPVN5</b> and vice versa.
      -# <b>Creation of tool and edges in NC</b> is done now, even if \n
         <b>DL-EC (TC_ECP) or DL_SC (TC_SCP) data exists AND ("optional") D no is different from edge no</b>.
      -# <b>Unknown data do no more overrite first known data</b>  (e.g. TC_DP36 does no more override TC_DP1).
      -# <b>TC_MOP11, TC_MOP13, TC_MOP15</b> data import is done now and does no more override TC_MOP1.
      -# <b>TC_MTPPC</b> and <b>TC_MTPPCS</b> data import is done now.
      .
    -# <b>ToIni style format export</b> of tool data ("Save tool setup data"), exportToIniStyle():
      -# <b> Optional D no value 0</b>  \n
         (which can be set in NC exclusively by PI DZERO for all edges of all tools at once) \n
         is not longer exported as 0 but as edge no, like in a newly created tool, \n
         because D no value 0 can not be writen to single edges and tools during import. \n
         Further more, D no value 0 is not conform to the rules of NC-sys-vars.
      .
    -# <b>ToIni style format export and import</b> of tool data:
      -# <b>TC_MTPC</b>, <b>TC_MTPC</b>, <b>TC_MTPPC</b> and <b>TC_MTPPCS</b> data export and import \n
         is done now as <b>data type double</b>.
      -# New <b>TC_DPROT</b> data: export and import is done as <b>data type double</b>.
      .
    .
  -# <b>Intermediate messages for technological functions of SlTmCmd</b>
  -# <b>Improved errorhandling for technological functions of SlTmCmd</b>
  -# <b>tool and magazine list data:</b> for optimized transport and improved access: \n
     Use SlTmMassData2ToolMagListChangedData instead of deprecated SlTmMassDataToolMagListChangedData.
  .
  \n
  \n
  \n
  \n
  \n
  <hr>
  \n
  \n
  <b>What's new in 04.05.04.01 (Dublin SP4 HF1):</b> \n
  \n
  -# <b>New enum</b> SlTmToMaPlaceData::PlaceKindValueEnum, \n
     in particular SlTmToMaPlaceData::PLACE_KIND_VALUE_SPINDLE. \n
     \n
  -# <b>Changed list element correlation of revolver place tool when located on a non-spindle buffer place:</b>\n
     If tool (or multitool) owns a place within a revolver magazine, \n
     (when tools myMag / myPlace data points to a revolver magazin place) \n
     tool is exeptionally displayed in lists on this revolver magazine place, \n
     even if tools current location (inMag / inPlace data of tool) is \n
     a buffer magazine place (inMag = 9998) of place kind "spindle". \n
     \n
     This handling is necessary, because NC must temporary \n
     change tools current location data to a spindle place, \n
     when tool becomes the NC-program-current tool, \n
     while tool physically remains on its revolver magazine place. \n
     \n
     In the past, detection of this display exeption did not \n
     consider place kind "spindle" but only magazine kind "buffer", \n
     so tool was faultily displayed on revolver, \n
     even if its current location was a buffer place of a non-spindle place kind, \n
     like a gripper, pickup or shuttle, where tool pysically was located. \n
     \n
     Yet, tool is displayed on its non-spindle buffer place, \n
     even if owner magazine is a revolver. \n
  .
  \n
  \n
  \n
  <b>What's new in 04.05.03 (Dublin SP3):</b>
  \n
  -# <b>Number of oem data has bee extended from 10 to 20: </b> \n
     -# Tool User-Param,             $TC_TPC20,   SlTmToMaToolUser::TOOL_USER_20,                       SlTmToMaToolUser,           SlTmUtil::DATA_KIND_TOOL_USER,            BTSS / OPI "/Tool/User/data".                    
     .
  .
  \n
  \n
  \n
  <b>What's new in 04.05 (Dublin) past 04.05.01.00.020:</b>
  \n
  -# <b>Read and write SlCap-local variable: </b> \n
     Consider special parameter specification when using data kind enum SlTmUtil::DATA_KIND_SPECIAL_DATA_CAP_LOCAL_VARIABLE in:
    -# SlTmQCmd::readDataSync(int containerNo, SlTmSvcSpecStoreElementsVectorType& rReadSpecVec, QBitArray& rHasError, SlTmInfo& rInfo);
    -# SlTmQCmd::writeDataSync(int containerNo, const SlTmSvcSpecStoreElementsVectorType& rWriteSpecVec, QBitArray& rHasError, SlTmInfo& rInfo);
    .
  -# <b> Convert between key-value-pairs of a QMap and a QString:</b> \n
     (for coding in HMI_ADV-WIZARD-GUI-Cursor-Current-Tool-and-Magazin-NCDDE-Variable compatible style)
    -# static unsigned int SlTmQCmd::encodeKeyValuePairsString(const QMap<QString, QString>& rInputMap, QString& rEncodedString);
    -# static unsigned int SlTmQCmd::decodeKeyValuePairsString(const QString& rEncodedString, QMap<QString, QString>& rOutputMap);
    .
  .
  \n
  \n
  \n
  <b>What's new in 04.05.00.00 (Dublin) since 04.04.00.00 (Berlin):</b>
  \n
  -# <b>Version history</b> "What's new in ... since ...".
  -# <b>New and extended classes and \n
     classes, which are yet updated with NCs data</b> \n
     (in older version they have been empty dummies):
    -# Class SlTmToMaEdge (extended): \n
       -# by class SlTmToMaEdgeToTr, \n
          get reference by SlTmToMaEdge::rToTr()
       .
    -# Class SlTmToMaEdgeToTr (new), \n
       contains transformed ToolOffset parameters of an edge, \n
       get reference by SlTmToMaEdge::rToTr()
    -# Class SlTmToMaDl (extended): \n
       -# by class SlTmToMaDlEcTr, \n
          get reference by SlTmToMaDl::rEcTr()
       -# by class SlTmToMaDlScTr, \n
          get reference by SlTmToMaDl::rScTr()
       .
    -# Class SlTmToMaDlEc, \n
       contains EC parameters of a DL, \n
       get reference by SlTmToMaDl::rEc()
    -# Class SlTmToMaDlEcTr (new), \n
       contains transformed EC parameters of a DL, \n
       get reference by SlTmToMaDl::rEcTr()
    -# Class SlTmToMaDlSc, \n
       contains SC parameters of a DL, \n
       get reference by SlTmToMaDl::rSc()
    -# Class SlTmToMaDlScTr (new), \n
       contains transformed SC parameters of a DL, \n
       get reference by SlTmToMaDl::rScTr()
    -# Class SlTmToMaEdgeOptDNo, \n
       contains "associated optional D number" of edge, \n
       sometimes called "unique D number" or "any D number" or "assigned D number", \n
       get reference by SlTmToMaEdge::rOptDNo() \n
       Default value in constructor has changed from 0 to -1. \n
       NCs "optional D number" function is supported now and \n
       description of values has been refined. \n
       In older code version, data did contain dummy value only. \n
       If client does explicitly set value other than default value -1, \n
       this will lead to errors during tool or edge creation in NC, \n
       when "optional D number" function is activated on NC. \n
       Usually clients did not do so in previous source code versions, \n
       because "optional D number" function has not been supported by sltmservice before.
    -# Class SlTmToMaAdaptColl, \n
       contains all magazine place (location) adapters, \n
       get reference by SlTmToMaContainer::rAdaptColl()
    -# Class SlTmToMaAdaptData, \n
       contains adapter parameters of a magazine location, \n
       get reference by SlTmToMaAdaptColl::rAdaptData()
    .
  -# <b>New</b> SlTmQCmd <b>methods</b>:
    -# SlTmQCmd::setDNosToZeroAsync()
    -# SlTmQCmd::checkDNosAsync()
    -# SlTmQCmd::activateWearGroupAsync()
    -# SlTmQCmd::setToolStateAsync()
    -# SlTmQCmd::checkDNosAndActivateAsync()
    -# SlTmQCmd::getCountOfAdaptersSync()
    -# SlTmQCmd::readDataSync(int containerNo, const QVector<SlTmToMaAdaptNoType> &rReadAdapterSpecVec, QVector<SlTmToMaAdaptData> &rResultAdapterDataVec, QBitArray &rHasError, SlTmInfo &rInfo)
    .
  -# <b>New</b> SlTmQCmd <b>signals</b>:
    -# SlTmQCmd::signalNotifySetDNosToZero()
    -# SlTmQCmd::signalNotifyCheckDNos()
    -# SlTmQCmd::signalNotifyActivateWearGroup()
    -# SlTmQCmd::signalNotifySetToolState()
    -# SlTmQCmd::signalNotifyCheckDNosAndActivate()
    .
  -# <b>Extended Methods</b> \n
     SlTmQCmd::subscribeToolMagList() and SlTmQCmd::signalNotifySubscribeToolMagList(): \n
     see SlTmMassDataToolMagListChangedData (SlTmMassDataImportI) contains: 
    -# Class SlTmMassDataToolMagListElData <b>extended by data</b>:
      -# int parAdaptNo
      -# SlTmToMaAdaptData& parAdaptData
      .
    .
  -# <b>Added an optional dummy parameter</b> \n
     to all SlTmQCmd asynchronous methods \n
     to avoid future binary incompatibility of a particular future extension.
  -# <b>Further values in enum</b> SlTmInfo::infoIdValuesEnum:
    -# SlTmInfo::ID_NO_INFO                       
    -# SlTmInfo::ID_SVC_DNOS_NOT_UNIQUE           
    -# SlTmInfo::ID_SVC_WEARGROUP_NOT_EXISTING    
    -# SlTmInfo::ID_SVC_EDGE_OR_DNO_NOT_EXISTING  
    -# SlTmInfo::ID_SVC_NO_ACTIVE_WEARGROUP       
    .
  -# <b>Further values in enum</b> SlTmInfo::subFunctionsEnum:
    -# SlTmInfo::SUB_FUNC_CHECK_DNOS          
    -# SlTmInfo::SUB_FUNC_ACTIVATE_WEARGROUP  
    -# SlTmInfo::SUB_FUNC_SET_TOOLSTATE       
    -# SlTmInfo::SUB_FUNC_SET_DNOS_TO_ZERO    
    .
  -# <b>Further values in enum</b> SlTmSysDeviceData::SysDeviceEnum:
    -# SlTmSysDeviceData::DEV_DATA_IDX_MAX_NUM_SUMCORR_PER_NC        
    -# SlTmSysDeviceData::DEV_DATA_IDX_EXIST_DL_SC_DATA              
    -# SlTmSysDeviceData::DEV_DATA_IDX_EXIST_DL_EC_DATA              
    -# SlTmSysDeviceData::DEV_DATA_IDX_EXIST_ADAPT                   
    -# SlTmSysDeviceData::DEV_DATA_IDX_MAX_NUM_SUMCORR_PER_CUTTEDGE  
    -# SlTmSysDeviceData::DEV_DATA_IDX_EXIST_EDGE_TO_TR_DATA         
    -# SlTmSysDeviceData::DEV_DATA_IDX_EXIST_DL_SC_TR_DATA           
    -# SlTmSysDeviceData::DEV_DATA_IDX_EXIST_DL_EC_TR_DATA           
    .
  -# <b>Further values in enum</b> SlTmSysDeviceSize::SysDeviceSizeIdxEnum:
    -# SlTmSysDeviceSize::SYSDEV_SIZE_IDX_NUM_EDGE_TO_TR_PARAMS  
    -# SlTmSysDeviceSize::SYSDEV_SIZE_IDX_NUM_DL_EC_TR_PARAMS    
    -# SlTmSysDeviceSize::SYSDEV_SIZE_IDX_NUM_DL_SC_TR_PARAMS    
    .
  -# <b>Further values in enum</b> SlTmToMaContainerData::ContainerDataIdxEnum:
    -# SlTmToMaContainerData::CONTAINER_DATA_EXIST_WEARGROUP          
    -# SlTmToMaContainerData::CONTAINER_DATA_EXIST_OPT_DNO            
    -# SlTmToMaContainerData::CONTAINER_DATA_EXIST_SUMCORR            
    -# SlTmToMaContainerData::CONTAINER_DATA_EXIST_DL_SC_DATA         
    -# SlTmToMaContainerData::CONTAINER_DATA_EXIST_DL_EC_DATA         
    -# SlTmToMaContainerData::CONTAINER_DATA_EXIST_ADAPT              
    -# SlTmToMaContainerData::CONTAINER_DATA_EXIST_EDGE_TO_TR_DATA    
    -# SlTmToMaContainerData::CONTAINER_DATA_EXIST_DL_SC_TR_DATA      
    -# SlTmToMaContainerData::CONTAINER_DATA_EXIST_DL_EC_TR_DATA      
    -# SlTmToMaContainerData::CONTAINER_DATA_EXIST_WEAR_SUPVIS        
    -# SlTmToMaContainerData::CONTAINER_DATA_EXIST_SUPVIS             
    -# SlTmToMaContainerData::CONTAINER_DATA_MAX_NUM_CUTT_EDGES_TOOL  
    -# SlTmToMaContainerData::CONTAINER_DATA_MAX_CUTTING_EDGE_NO      
    .
  -# <b>Further values in enum</b> SlTmSysDeviceSize::SysDeviceSizeIdxEnum:
    -# SlTmSysDeviceSize::SYSDEV_SIZE_IDX_NUM_EDGE_TO_TR_PARAMS  
    -# SlTmSysDeviceSize::SYSDEV_SIZE_IDX_NUM_DL_EC_TR_PARAMS    
    -# SlTmSysDeviceSize::SYSDEV_SIZE_IDX_NUM_DL_SC_TR_PARAMS    
    .
  -# <b>Further values in enum</b> SlTmToMaMachineData::MachineDataEnum:
    -# SlTmToMaMachineData::MACH_DATA_IDX_ACCESS_READ_TM_ALL_PARAM  
    -# SlTmToMaMachineData::MACH_DATA_IDX_WEAR_TRANSFORM    
    .
  -# <b>Further values in enum</b> SlTmToMaContainerSize::ToMaContainerSizeIdxEnum:
    -# SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_EDGE_TO_TR_PARAMS  
    -# SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_DL_EC_TR_PARAMS    
    -# SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_DL_SC_TR_PARAMS    
    .
  -# <b>Further values in enum</b> SlTmUtil::DataKindEnum:
    -# SlTmUtil::DATA_KIND_EDGE_TO_TR                            
    -# SlTmUtil::DATA_KIND_DL_EC_TR                              
    -# SlTmUtil::DATA_KIND_DL_SC_TR                              
    -# SlTmUtil::DATA_KIND_SPECIAL_FUNCTION_GET_EDGE_NO_BY_D_NO  
    .
  -# <b>Changes related to "associated optional D number" of edge</b>, \n
     sometimes called "unique D number" or "any D number" or "assigned D number":
    -# Further values / changed meaning in \n
       enum SlTmToMaCurrChanData::CurrChanDataIdxEnum:
      -# SlTmToMaCurrChanData::CURR_CHAN_DATA_ACT_D_NUMBER: \n
         If "optional D number functionality" is switched "OFF" in NC, \n
         NC delivers "current edge number" form actual NC program in this data. \n
         If "optional D number functionality" is switched "ON" in NC, \n
         NC delivers "current D number" form actual NC program in this data, \n
         in lieu of "current edge number". \n
         <b>To support "optional D number functionality in NC", \n
         client may have to change its source code:</b> \n
         BTSS/OPI and sltmutilities methods needs "edge number" to address an edge. \n
         If "edge number" is needed for further computations, \n
         use SlTmToMaCurrChanData::CURR_CHAN_DATA_ACT_EDGE_NUMBER instead \n
         of SlTmToMaCurrChanData::CURR_CHAN_DATA_ACT_D_NUMBER.
      -# SlTmToMaCurrChanData::CURR_CHAN_DATA_ACT_EDGE_NUMBER: \n
         If "optional D number functionality" is switched "ON" in NC, \n
         and "D number" in data of SlTmToMaCurrChanData::CURR_CHAN_DATA_ACT_D_NUMBER \n
         is unique within tools edge collection, \n
         then data of SlTmToMaCurrChanData::CURR_CHAN_DATA_ACT_EDGE_NUMBER \n
         contains "edge number", computed by sltmservice \n
         on base of "D number" and tools edge data. \n
         If "optional D number functionality" is switched "OFF" in NC, \n
         then data contains "current edge number" form actual NC program, \n
         which is the same value as in data \n
         SlTmToMaCurrChanData::CURR_CHAN_DATA_ACT_D_NUMBER.
      .
    -# Method SlTmToMaEdgeColl::getEdgeNoByDNo()
    -# Enum SlTmToMaEdgeColl::SpecialFunctionGetEdgeNoByDNoIdxEnum
    -# Enum value SlTmUtil::DATA_KIND_SPECIAL_FUNCTION_GET_EDGE_NO_BY_D_NO
    .
  -# <b>New sorting type "edges by (optional) D number"</b>:
    -# SlTmQCmd::createToolMagList and SlTmQCmd::setToolMagListParameters:
      -# New parameter value in SlTmToMaListUni::setParameters() parameter string: \n
         "ListSubType=4" (SlTmToMaListUni::LIST_SUB_TYPE_VALUE_OPTDNO) \n
         to switch to new sorting type "edges by d number".
      .
    -# Further values in enum SlTmToMaListUni::ListSubTypeValuesEnum:
      -# SlTmToMaListUni::LIST_SUB_TYPE_VALUE_OPTDNO  
      .
    .
  -# <b>Versions 04.05.00.00 and 04.04.00.00 are not binary compatible.</b>
  .
  \n
  \n
  \n
  <b>For internal use only:</b> \n
  Changes of these methods, classes and files have been made for internal use only and may be changed or canceled at any time. \n
  They are hidden in Open Architecture Documentation: \n
  \n
  -# <b>Docu about Classes SlTmCmd and SlTmCmdCallBackB:</b> \n
     SlTmCmd offers an interface, which allows client to use it from within a free thread. \n
     (Contrary to SlTmQCmd, which only works with QT mainthread and signal and slot.) \n
     To receive the asynchronous results by callback functions of class SlTmCmdCallBackB, \n
     client can implement its own derived class. \n
  -# <b>Extented binary stream format in class </b> SlTmMassDataToolMagListElData: \n
     see description in QDataStream& SlTmMassDataToolMagListElData::importData(QDataStream& rStream)
  -# <b>Class</b> SlTmToMaListUniElData <b>extended by data:</b>
    -# int parAdaptNo
    .
  -# <b>Class</b> SlTmToMaListUniElKey <b>extended by data / changed order of data:</b>
    -# int parOptDNo           (new)
    -# int parEdgeNoU          (new)
    -# int parMultiToolPlaceNo (changed order)
    .
  -# <b>New method</b> SlTmToMaContainer::importToIniStyle()
  .
  \n
  \n
  \n
  \n
  \n
  <hr>
  \n
  \n
  <b>What's new in 04.04 (Berlin) since 04.04.04.00.006:</b>
  \n
  -# <b>Read and write SlCap-local variable: </b> \n
     Consider special parameter specification when using data kind enum SlTmUtil::DATA_KIND_SPECIAL_DATA_CAP_LOCAL_VARIABLE in:
    -# SlTmQCmd::readDataSync(int containerNo, SlTmSvcSpecStoreElementsVectorType& rReadSpecVec, QBitArray& rHasError, SlTmInfo& rInfo);
    -# SlTmQCmd::writeDataSync(int containerNo, const SlTmSvcSpecStoreElementsVectorType& rWriteSpecVec, QBitArray& rHasError, SlTmInfo& rInfo);
    .
  -# <b> Convert between key-value-pairs of a QMap and a QString:</b> \n
     (for coding in HMI_ADV-WIZARD-GUI-Cursor-Current-Tool-and-Magazin-NCDDE-Variable compatible style)
    -# static unsigned int SlTmQCmd::encodeKeyValuePairsString(const QMap<QString, QString>& rInputMap, QString& rEncodedString);
    -# static unsigned int SlTmQCmd::decodeKeyValuePairsString(const QString& rEncodedString, QMap<QString, QString>& rOutputMap);
    .
  .
  \n
  \n
  \n
  <b>What's new in 04.04.00.00 / 02.07.00.00 (Berlin) since 02.06.01.00:</b>
  \n
  -# <b>Tool Grinding Data is now supported:</b> \n
     class SlTmToMaToolGrind, get reference by SlTmToMaTool::rGrind().
    -# enum SlTmToMaMachineData::MachineDataEnum: \n
                             additional value: SlTmToMaMachineData::MACH_DATA_IDX_ACCESS_WRITE_TM_GRIND
    .
  -# <b>Improved behaviour during "1-n machine switch"</b>
  -# <b>Improved error handling and more detailed error indication during shutdown:</b>
    -# Enum SlTmInfo::infoIdValuesEnum: \n
                           additional value: SlTmInfo::ID_ADAPTER_SHUTDOWN_IN_PROGRESS
    -# Class SlTmQCmd:     detailed text see:  "... If SlTmServiceAdapter is shutting down while ..."
    -# Method SlTmQCmd::signalNotifySubscribePOReset(): \n
                           detailed text see: \n
                               "... SlTmInfo::ID_ADAPTER_SHUTDOWN_IN_PROGRESS ..." \n
                               "... These signals are sent too, during start and shut down of SolutionLine HMI ..." \n
                               "... before SlTmService is stopped: signal with typeOfNotify = ..." 
    .
  -# <b>Class</b> SlTmQCmd: \n
                            additional method:  const QString& SlTmQCmd::listKey() const; \n
                            Returns the listKey if a list subscribe is active.
  -# <b>Struct</b> SlTmSvcSpecStoreElType: \n
                            additional method:  bool SlTmSvcSpecStoreElType::operator<(const SlTmSvcSpecStoreElType& rRight) const; 
  -# <b>Some other internal changes</b>, \n
                            i.e. in classes SlTmSysDevice and SlTmToMaContainer
  -# <b>Versions 04.04.00.00 and 02.06.01.00 are not binary compatible.</b>
  .
  \n
  \n
  \n
  \n
  \n
*/



/*!
  \page compositionhierarchy sltmutilities data classes, composition hierarchy

  This is the composition hierarchy of sltmutilities data classes:
  -# SlTmUtil: contains typedefs and enums for index access to single data in data vector classes,
     i.e. ::SlTmUtil::DataKindEnum
  -# SlTmStore
    -# SlTmSys,
       reference: SlTmStore::rSys()
      -# SlTmSysDeviceColl, ::SlTmSysDevCollMapType, key ::SlTmSysDevNoType,
         reference: SlTmSys::rDeviceColl()
        -# SlTmSysDevice,
           reference: SlTmSysDeviceColl::rDevice(const int devNo, bool* isContained)
          -# SlTmSysDeviceData (consists of class SlTmToMaVariantData), 
             reference: SlTmSysDevice::rDeviceData()
          -# SlTmSysChannelColl, ::SlTmSysChannelVVType, 
             reference: SlTmSysDevice::rChannelColl()
            -# SlTmSysChannelData (consists of class SlTmToMaVariantData),
               reference: SlTmSysChannelColl::rChannelData(const int chanNo, bool* isContained)
            .
          -# SlTmSysDeviceSize (consists of class SlTmToMaIntData),
             reference: SlTmSysDevice::rDeviceSize()
          -# SlTmSysDeviceToolUserTypes (consists of class SlTmToMaIntData),
             reference: SlTmSysDevice::rDeviceToolUserTypes()
          .
        .
      .
    -# SlTmToMaContainerColl, ::SlTmToMaContainerCollMapType, key ::SlTmToMaContainerNoType,
       reference: SlTmStore::rContainerColl()
      -# \b SlTmToMaContainer, 
         reference: SlTmToMaContainerColl::rContainer(const int containerNo, bool* isContained)
        -# SlTmToMaContainerSize (consists of class SlTmToMaIntData),
           reference: SlTmToMaContainer::rContainerSize()
        -# SlTmToMaContainerData (consists of class SlTmToMaVariantData),
           reference: SlTmToMaContainer::rData()
        -# SlTmToMaContainerTypeSpecData (consists of class SlTmToMaVariantData),
           reference: SlTmToMaContainer::rTypeSpecData()
        -# SlTmToMaMachineData (consists of class SlTmToMaVariantData),
           reference: SlTmToMaContainer::rMachineData()
        -# SlTmToMaDataProps, ::SlTmToMaDataPropsMapType, key ::SlTmToMaDataPropsKeyType,
           reference: SlTmToMaContainer::rDataProps()
          -# SlTmToMaDataPropsData, ::SlTmToMaDataPropsDataMapType, key ::SlTmToMaDataPropsDataKeyType
            -# ::SlTmToMaDataPropsDataValType (QVariant)
            .
          .
        -# SlTmToMaToolColl, ::SlTmToMaToolCollMapType, key ::SlTmToMaTNoType,
           reference: SlTmToMaContainer::rToolColl()
          -# \b SlTmToMaTool, 
            reference: SlTmToMaToolColl::rTool(const int tNo, bool* isContained)
            -# SlTmToMaToolData,
               reference: SlTmToMaTool::rData()
            -# SlTmToMaToolUser (consists of class SlTmToMaVariantData),
               reference: SlTmToMaTool::rUser()
            -# SlTmToMaToolAppl (consists of class SlTmToMaVariantData),
               reference: SlTmToMaTool::rAppl()
            -# SlTmToMaToolGrind (consists of class SlTmToMaDoubleData),
               reference: SlTmToMaTool::rGrind()
            -# SlTmToMaEdgeColl, ::SlTmToMaEdgeCollMapType, key ::SlTmToMaEdgeNoType,
               reference: SlTmToMaTool::rEdgeColl()
              -# SlTmToMaEdge , 
                reference: SlTmToMaEdgeColl::rEdge(const int edgeNo, bool* isContained)
                -# SlTmToMaEdgeTo (consists of class SlTmToMaDoubleData),
                   reference: SlTmToMaEdge::rTo()
                -# SlTmToMaEdgeToTr (consists of class SlTmToMaDoubleData),
                   reference: SlTmToMaEdge::rToTr()
                -# SlTmToMaEdgeUser (consists of class SlTmToMaDoubleData),
                   reference: SlTmToMaEdge::rUser()
                -# SlTmToMaEdgeAppl (consists of class SlTmToMaDoubleData),
                   reference: SlTmToMaEdge::rAppl()
                -# SlTmToMaEdgeSup (consists of class SlTmToMaDoubleData),
                   reference: SlTmToMaEdge::rSup()
                -# SlTmToMaEdgeSupUser (consists of class SlTmToMaDoubleData),
                   reference: SlTmToMaEdge::rSupUser()
                -# SlTmToMaEdgeSupAppl (consists of class SlTmToMaDoubleData),
                   reference: SlTmToMaEdge::rSupAppl()
                -# SlTmToMaEdgeOptDNo, 
                   reference: SlTmToMaEdge::rOptDNo()
                -# SlTmToMaDlColl, ::SlTmToMaDlCollMapType, key ::SlTmToMaDlNoType,
                   reference: SlTmToMaEdge::rDlColl()
                  -# SlTmToMaDl, 
                    reference: SlTmToMaDlColl::rDl(const int dlNo, bool* isContained)
                    -# SlTmToMaDlEc (consists of class SlTmToMaDoubleData),
                       reference: SlTmToMaDl::rEc()
                    -# SlTmToMaDlEcTr (consists of class SlTmToMaDoubleData),
                       reference: SlTmToMaDl::rEcTr()
                    -# SlTmToMaDlSc (consists of class SlTmToMaDoubleData),
                       reference: SlTmToMaDl::rSc()
                    -# SlTmToMaDlScTr (consists of class SlTmToMaDoubleData),
                       reference: SlTmToMaDl::rScTr()
                    .
                  .
                .
              .
            .
          .
        -# SlTmToMaMultiToolColl, ::SlTmToMaMultiToolCollMapType, key ::SlTmToMaMTNoType,
           reference: SlTmToMaContainer::rMultiToolColl()
          -# \b SlTmToMaMultiTool, 
            reference: SlTmToMaMultiToolColl::rMultiTool(const int mtNo, bool* isContained)
            -# SlTmToMaMultiToolData (consists of class SlTmToMaVariantData),
               reference: SlTmToMaMultiTool::rData()
            -# SlTmToMaMultiToolUser (consists of class SlTmToMaVariantData),
               reference: SlTmToMaMultiTool::rUser()
            -# SlTmToMaMultiToolAppl (consists of class SlTmToMaVariantData),
               reference: SlTmToMaMultiTool::rAppl()
            -# SlTmToMaMultiToolPlaceColl, ::SlTmToMaMultiToolPlaceCollVVType,
                reference: SlTmToMaMultiTool::rMultiToolPlaceColl()
              -# \b SlTmToMaMultiToolPlace,
                  reference: SlTmToMaMultiToolPlaceColl::rMultiToolPlace(const int multiToolPlaceNo, bool* isContained)
                -# SlTmToMaMultiToolPlaceData (consists of class SlTmToMaVariantData),
                    reference: SlTmToMaMultiToolPlace::rData()
                -# SlTmToMaMultiToolPlaceUser (consists of class SlTmToMaVariantData),
                    reference: SlTmToMaMultiToolPlace::rUser()
                -# SlTmToMaMultiToolPlaceAppl (consists of class SlTmToMaVariantData),
                    reference: SlTmToMaMultiToolPlace::rAppl()
                .
              .
            .
          .
        -# SlTmToMaMagConf, 
           reference: SlTmToMaContainer::rMagConf()
          -# SlTmToMaMagConfData (consists of class SlTmToMaVariantData), 
             reference: SlTmToMaMagConf::rData()
          -# SlTmToMaMagColl, ::SlTmToMaMagCollMapType, key ::SlTmToMaMagNoType,
             reference: SlTmToMaMagConf::rMagColl()
            -# \b SlTmToMaMag, 
               reference: SlTmToMaMagColl::rMag(const int magNo, bool* isContained)
              -# SlTmToMaMagData (consists of class SlTmToMaVariantData),
                 reference: SlTmToMaMag::rData()
              -# SlTmToMaMagUser (consists of class SlTmToMaIntData),
                 reference: SlTmToMaMag::rUser()
              -# SlTmToMaMagAppl (consists of class SlTmToMaIntData),
                 reference: SlTmToMaMag::rAppl()
              -# SlTmToMaPlaceColl, ::SlTmToMaPlaceCollVVType,
                 reference: SlTmToMaMag::rPlaceColl()
                -# \b SlTmToMaPlace,
                   reference: SlTmToMaPlaceColl::rPlace(const int placeNo, bool* isContained)
                  -# SlTmToMaPlaceData (consists of class SlTmToMaIntData),
                     reference: SlTmToMaPlace::rData()
                  -# SlTmToMaPlaceUser (consists of class SlTmToMaIntData),
                     reference: SlTmToMaPlace::rUser()
                  -# SlTmToMaPlaceAppl (consists of class SlTmToMaIntData),
                     reference: SlTmToMaPlace::rAppl()
                  .
                .
              .
            .
          -# SlTmToMaDistOrdMagColl, ::SlTmToMaDistOrdMagCollMapType, key ::SlTmToMaMagNoType, 
             references and convenience methodes see SlTmToMaMagConf, SlTmQCmd::getBufferDistsOfOrdMag(), SlTmQCmd::getLoadDistsOfOrdMag() \n
             and page \ref pageoverviewmagazineconf, \n
             reference: SlTmToMaMagConf::rDistOrdMagColl()
            -# SlTmToMaDistOrdMagSpecMagColl, ::SlTmToMaDistOrdMagSpecMagCollMapType, ::SlTmToMaMagNoType
              -# SlTmToMaDistOrdMagSpecMagSpecPlaceColl, ::SlTmToMaDistOrdMagSpecMagSpecPlaceCollMapType, key ::SlTmToMaPlaceNoType
                -# SlTmToMaDistOrdMagSpecMagSpecPlace
                  -# SlTmToMaDistance
                  .
                .
              .
            .
          -# SlTmToMaDistSpecMagColl, ::SlTmToMaDistSpecMagCollMapType, key ::SlTmToMaMagNoType
             references and convenience methodes see SlTmToMaMagConf and \n
             page \ref pageoverviewmagazineconf, \n
             reference: SlTmToMaMagConf::rDistSpecMagColl()
            -# SlTmToMaDistSpecMagSpecPlaceColl, ::SlTmToMaDistSpecMagSpecPlaceCollMapType, key ::SlTmToMaPlaceNoType
              -# SlTmToMaDistSpecMagSpecPlaceOrdMagColl, ::SlTmToMaDistSpecMagSpecPlaceOrdMagCollMapType, key ::SlTmToMaMagNoType
                -# SlTmToMaDistSpecMagSpecPlaceOrdMag
                  -# SlTmToMaDistance
                  .
                .
              .
            .
          .
        -# SlTmToMaAdaptColl, ::SlTmToMaAdaptCollVVType, 
           reference: SlTmToMaContainer::rAdaptColl()
          -# SlTmToMaAdaptData (consists of class SlTmToMaDoubleData),
             reference: SlTmToMaAdaptColl::rAdaptData(const int adaptNo, bool* isContained)
          .
        -# SlTmToMaAdaptUniColl, ::SlTmToMaAdaptUniCollMapType,
           reference: SlTmToMaContainer::rAdaptUniColl()
          -# SlTmToMaAdaptUniData (consists of class SlTmToMaDoubleData),
             reference: SlTmToMaAdaptUniColl::rAdaptData(const int adaptNo, bool* isContained)
          .
        -# SlTmToMaCurrChanColl, ::SlTmToMaCurrChanCollMapType, key ::SlTmToMaChanNoType,
           reference SlTmToMaContainer::rCurrChanColl()
          -# SlTmToMaCurrChan,
             reference: SlTmToMaCurrChanColl::rCurrChan(const int chanNo, bool* isContained)
            -# SlTmToMaCurrChanData (consists of class SlTmToMaVariantData), 
               reference: SlTmToMaCurrChan::rData()
            .
          .
        -# ::SlTmToMaCurrPlaceCollVecType, ::SlTmToMaCurrPlaceData, 
           reference SlTmToMaContainer::rCurrPlaceColl()
        -# SlTmToMaTIsoColl, ::SlTmToMaTIsoCollVVType, 
           reference SlTmToMaContainer::rTIsoColl()
          -# SlTmToMaTIsoData (consists of class SlTmToMaDoubleData), 
             reference: SlTmToMaTIsoColl::rTIsoData(const int tIsoNo, bool* isContained)
          .
        .
      .
    -# SlTmToMaLists, ::SlTmToMaListPtrCollMapType, key QString ListKey,
       reference: SlTmStore::rLists()
      -# SlTmToMaListUni (consists of class SlTmToMaList)
        -# SlTmToMaListUniElKey 
        -# SlTmToMaListUniElData 
        .
      .
    -# \link multithreading QReadWriteLock \endlink, 
       reference: SlTmStore::pReadWriteLock()
    .
  .

  To do: BTSS / OPI: 
  - Location types, location hierarchies of magazine data (like BTSS data module TT) 
    Attention: meaning of data in NC is going to be extended!
  .

*/


/*!
  \page typicalmethods Typical methods of sltmutilities data classes

  OPERATE (HMI SolutionLine) Toolmanagement tool and magazine data can be cut into these typicall data patterns and methods:
  -# <b>ordinary "vector" data</b> \n
    of type int, double or QVariant, \n
    i.e. edges tool offset data SlTmToMaEdgeTo: 
    -# \b constructor \n
       with "count of vector elements" parameter, \n
       i.e. SlTmToMaEdgeTo::SlTmToMaEdgeTo(const int numElements) 
    -# \b constructor \n
       with SlTmToMaContainerSize parameter, \n
       reads vector size from corresponding \a rContainerSize element, to size vector during construction: \n
       i.e. SlTmToMaEdgeTo::SlTmToMaEdgeTo(const SlTmToMaContainerSize& rContainerSize)
    -# <b>copy constructor</b> \n
       to make a copy of \a rSourceObj, \n
       i.e. SlTmToMaEdgeTo::SlTmToMaEdgeTo(const SlTmToMaEdgeTo& rSourceObj)
    -# <b>read count</b> \n
       of vectors \b elements, \n
       i.e. SlTmToMaEdgeTo::count() const
    -# \b resize \n
       vector to \a numElements, \n
       i.e. SlTmToMaEdgeTo::resize(const int numElements)
    -# <b>get a single value</b>, \n
       indexed by \a idx from vector data and write it to caller owned \a rTargetVal reference; \n
       \a rTargetVal can be either of type QVariant or of same type as vector data (int, double, QVariant); \n
       i.e. SlTmToMaEdgeTo::val(const int idx, double& rTargetVal) const and \n
       i.e. SlTmToMaEdgeTo::val(const int idx, QVariant& rTargetVal) const. \n
       \a idx allways is support by <b>adequate enums</b>, \n
       i.e. SlTmToMaEdgeTo::EdgeToIdxEnum, in particular i.e. SlTmToMaEdgeTo::EDGE_TO_GEO_LENGTH1. \n
\code
  // example to read geo length 1 from tool offset data of an edge:
  double dGeoLength1(0.0);
  int retVal(SlTmUtil::ERR_OK);
  const SlTmToMaEdge& aConstEdge = aConstEdgeFromSomeWhereElse; 
  const SlTmToMaEdgeTo& aConstEdgeTo = aConstEdge.rConstTo();
  retVal = aConstEdgeTo.val(SlTmToMaEdgeTo::EDGE_TO_GEO_LENGTH1, dGeoLength1);
  if (SlTmUtil::ERR_OK == retVal)
  {
    // value of dGeoLength1 is valid
  }
\endcode
    -# <b>get all values</b> \n
       from vector and write it all to caller owned \a rTargetVal QVector of QVariants, \n
       i.e. SlTmToMaEdgeTo::val(SlTmToMaVariantVVType& rTargetVal) const
    -# <b>write a single value</b> \n
       to vector element, indexed by \a idx, \n
       read single value from caller owned \a rSource reference. \n
       \a rSourceVal can be either of type QVariant or of same type as vector data (int, double, QVariant). \n
       i.e. SlTmToMaEdgeTo::setVal(const int idx, const double& rSourceVal) and \n
       i.e. SlTmToMaEdgeTo::setVal(const int idx, const QVariant& rSourceVal) 
    -# <b>write all values</b> \n
       to vectors elements and reads it from caller owned \a rSourceVal QVector of QVariants, \n
       i.e SlTmToMaEdgeTo::setVal(const SlTmToMaVariantVVType& rSourceVal)
    -# <b>=, assign a copy</b>, \n
       i.e SlTmToMaEdgeTo::operator=(const SlTmToMaEdgeTo& rSourceObj)
    -# <b>export vectors data</b> \n
       (count as int and each single data as QVariant) <b>to QDataStream</b> or <b>QTextStream</b>, \n
       i.e. ::operator<<(QTextStream& rStream, const SlTmToMaEdgeTo& rData) or \n
       i.e. ::operator<<(QDataStream& rStream, const SlTmToMaEdgeTo& rData) \n
       These methods have been made for internal use only and may be changed or canceled at any time. They are hidden in Open Architecture Documentation.
    -# <b>import data \n
       from QDataStream into vector</b>, inclusive resize of vector, \n
       i.e. ::operator>>(QDataStream& rStream, SlTmToMaEdgeTo& rData)\n
       This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
    .
  -# <b>map type collection</b>, \n
    i.e. collection of edges SlTmToMaEdgeColl: 
    -# <b>constructor</b> \n
       to make an \b empty collection, \n
       i.e. SlTmToMaEdgeColl::SlTmToMaEdgeColl()
    -# <b>copy constructor</b> \n
       to make a copy of \a rSourceObj, \n
       i.e. SlTmToMaEdgeColl::SlTmToMaEdgeColl(const SlTmToMaEdgeColl& rSourceObj)
    -# <b>read count</b> \n
       of maps \b elements, \n
       i.e. SlTmToMaEdgeColl::count() const
    -# \b insert \n
       a copy of i.e. \a rEdge with \b key i.e. \a edgeNo <b>into map collection</b>, \n
       i.e. SlTmToMaEdgeColl::insert(const SlTmToMaEdgeNoType tNo, const SlTmToMaEdge& rEdge)
    -# \b delete \n
       a element, addressed by key i.e. \a edgeNo <b>from map collection</b>. \n
       i.e. SlTmToMaEdgeColl::remove(const SlTmToMaEdgeNoType edgeNo)
    -# <b>delete all</b> \n
       elements from <b>map collection</b>, \n
       i.e. SlTmToMaEdgeColl::clear() 
    -# <b>get all</b> contained \b keys \n
       (i.e. edge number edgeNo keys) <b>of map</b> 
       as \b QVector of i.e. ::SlTmToMaEdgeNoType into caller owned \a rTargetEdgeNoVector. \n
       i.e. SlTmToMaEdgeColl::edgeNoVector(SlTmToMaEdgeNosValueVectorType& rTargetEdgeNoVector) const;
    -# \b get a <b>const reference</b> of a <b>single element</b> \n
       from <b>map collection</b>, addressed by \b key i.e. \a edgeNo; \n
       pointer \a pIsEdgeContained to a variable of type bool indicates, if element exists and reference is valid; \n
       i.e. SlTmToMaEdgeColl::rConstEdge(const SlTmToMaEdgeNoType edgeNo, bool* pIsEdgeContained) const. \n 
       Clients should prefer to use <b>const reference</b> methodes (like i.e. SlTmToMaEdgeColl::rConstEdge()), \n
       if they do \b not intend to change values. Otherwise they should use reference methodes (like SlTmToMaEdgeColl::rEdge()). \n
       To do so, makes the client source code more \b secure and \b avoids \b unnecessary (Qt-)internal \b tasks. \n
\code
  // example to get a edge from edge collection:
  int edgeNo(aEdgeNoFromSomewhereElse);
  const SlTmToMaTool& aConstTool = aToolFromSomewhereElse;
  int retVal(SlTmUtil::ERR_OK);
  bool isEdgeContained(false);
  const SlTmToMaEdge& aConstEdge = aConstTool.rConstEdgeColl().rConstEdge(edgeNo, &isEdgeContained);
  if (isEdgeContained) // Prevent use of invalid aConstEdge reference, if edge does not exist.
  {
    double dWearLength1(0.0);
    retVal = aConstEdge.rConstTo().val(SlTmToMaEdgeTo::EDGE_TO_WEAR_LENGTH1, dWearLength1); 
    if (SL_SUCCEEDED(retVal))
    {
      // value of dWearLength1 is valid
    }
  }
\endcode
    -# \b get a <b>reference</b> of a <b>single element</b> \n
       from <b>map collection</b>, addressed by \b key i.e. \a edgeNo; \n
       \a pIsEdgeContained pointer to a variable of type bool indicates, if element exists and reference is valid. \n
       Using this reference, it is possible to change elements data without notifying the collection. \n
       Caller is responsible to avoid inconsistency. \n
       i.e. SlTmToMaEdgeColl::rEdge(const SlTmToMaEdgeNoType edgeNo, bool* pIsEdgeContained) 
    -# <b>verify existence</b> \n
       of an \b element with \b key i.e. \a edgeNo \b in map \b collection, \n
       i.e. SlTmToMaEdgeColl::contains(const SlTmToMaEdgeNoType edgeNo) const
    -# <b>=, assign a copy</b>, \n
       i.e SlTmToMaEdgeColl::operator=(const SlTmToMaEdgeColl& rSourceObj)
    -# <b>export maps data</b> \n
       (count as int and key and data pairs of all data elements) <b>to QDataStream</b> or <b>QTextStream</b>, \n
       i.e. ::operator<<(QTextStream& rStream, const SlTmToMaEdgeColl& rData) or \n
       i.e. ::operator<<(QDataStream& rStream, const SlTmToMaEdgeColl& rData)\n
       These methods have been made for internal use only and may be changed or canceled at any time. They are hidden in Open Architecture Documentation.
    -# <b>import data \n
       from QDataStream into map</b>, \n
       i.e. ::operator>>(QDataStream& rStream, SlTmToMaEdgeColl& rData)\n
       This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
    .
  -# <b>vector type collection</b>, \n
    i.e. place data collection SlTmToMaPlaceColl:
    -# <b>constructor</b> \n
       with parameter \a numElements ("\b count of vector elements) and \n
       single element <b>default value</b> parameter \a rSourceVal, \n
       i.e. SlTmToMaPlaceColl::SlTmToMaPlaceColl(const int numElements, const SlTmToMaPlace& rSourceVal)
    -# <b>copy constructor</b> \n
       to make a copy of \a rSourceObj, \n
       i.e. SlTmToMaPlaceColl::SlTmToMaPlaceColl(const SlTmToMaPlaceColl& rSourceObj)
    -# <b>read count</b> \n
       of vectors \b elements, \n
       i.e. SlTmToMaPlaceColl::count() const
    -# \b resize vector \n
       to \a numElements, \n
       i.e. SlTmToMaPlaceColl::resize(const int numElements, const SlTmToMaPlace& rSourceVal)
    -# \b get a <b>const reference</b> of a <b>single element</b> \n
       from <b>vector collection</b>, addressed by \b index i.e. \a placeNo; \n
       pointer \a pIsPlaceContained to a variable of type bool indicates, if element exists and reference is valid. \n
       i.e. SlTmToMaPlaceColl::rConstPlace(const SlTmToMaPlaceNoType placeNo, bool* pIsPlaceContained) const 
    -# \b get a <b>reference</b> of a <b>single element</b> \n
       from <b>vector collection</b>, addressed by \b index i.e. \a placeNo; \n
       pointer \a pIsPlaceContained to a variable of type bool indicates, if element exists and reference is valid. \n
       i.e. SlTmToMaPlaceColl::rPlace(const SlTmToMaPlaceNoType placeNo, bool* pIsPlaceContained) 
    -# <b>verify existence</b> \n
       of an \b element with \b index i.e. \a placeNo in vector \b collection, \n
       i.e. SlTmToMaPlaceColl::contains(const SlTmToMaPlaceNoType placeNo) const
    -# <b>=, assign a copy</b>, \n
       i.e SlTmToMaPlaceColl::operator=(const SlTmToMaPlaceColl& rSourceObj)
    -# <b>export vectors data</b> \n
       (count as int and data of all data elements) <b>to QDataStream</b> or <b>QTextStream</b>, \n
       i.e. ::operator<<(QTextStream& rStream, const SlTmToMaPlaceColl& rData) or \n
       i.e. ::operator<<(QDataStream& rStream, const SlTmToMaPlaceColl& rData)\n
       These methods have been made for internal use only and may be changed or canceled at any time. They are hidden in Open Architecture Documentation.
    -# <b>import data \n
       from QDataStream into map</b> inclusive resize, \n
       i.e. ::operator>>(QDataStream& rStream, SlTmToMaPlaceColl& rData)\n
       This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
    .
  .
  \n
  \n
\code
  // Example: change edge data of all edges of a tool and append a edge to tool.
  // This is not an example from real world. Is's a code example only.
  // SlTmToMaTool and SlTmToMaEdge are necessary, when creating 
  // a tool in NC device by SlTmQCmd::createToolAsync() and accordingly SlTmCmd::createToolAsync().
  // To change tool data of an already existing tool, use SlTmQCmd::writeDataSync() and accordingly SlTmCmd::writeDataSync().
  
  int retVal(SlTmUtil::ERR_OK);
  SlTmToMaTool& aTool = aToolFromSomewhereElse;

  int toolMonitorMode(0); //tool supervision monitoring mode
  retVal = aTool.rData().val(SlTmToMaToolData::TOOL_DATA_MON, toolMonitorMode);
  if (SL_SUCCEEDED(retVal))
  { //valid toolMonitorMode
    if (SlTmToMaToolData::TOOL_MONITOR_VALUE_MASK_WEAR & toolMonitorMode)
    { //supervision of wear of tools edges is switched ON

      // read edge no list of tools edge collection
      // ("edge no" is "identification number of edge", 
      // this is in NC program languange usually i.e. "D=1") 
      SlTmToMaEdgeNosValueVectorType aEdgeNoVector;
      retVal = aTool.rConstEdgeColl().edgeNoVector(aEdgeNoVector);

      // retVal ignored, because in case of error, aEdgeNoVector.count() would be 0
      int edgeCount(aEdgeNoVector.count());
      int edgeIdx(0);

      // loop through edge no vector of existing edges
      // (may be i.e., there are edge nos 2 and 4 contained and 
      // edge no 1 and 3 do not exist (edge gaps)
      for (edgeIdx = 0; edgeIdx < edgeCount; ++edgeIdx)
      {
        // read edge no key from QVector
        int edgeNo(aEdgeNoVector.at(edgeIdx));

        // read edge by edgeNo key
        bool isEdgeContained(false);
        SlTmToMaEdge& aEdge = aTool.rEdgeColl().rEdge(edgeNo, &isEdgeContained);
        if (isEdgeContained) //check this allways, before using SlTmToMaEdge& aEdge
        {
          double dWearLength1(0.001);  // This is not an example from real world
          retVal = aEdge.rTo().setVal(SlTmToMaEdgeTo::EDGE_TO_WEAR_LENGTH1, dWearLength1); 
          if (SL_SUCCEEDED(retVal))
          { // setVal of wear length succeeded

            // we want to make a copy of last edge and insert it into edge collection of tool
            if (edgeIdx == (edgeCount - 1)) // last existing edge
            { // current last existing edge
              SlTmToMaEdge aNewEdge(aEdge); // copy constructor
              int newEdgeNo(edgeNo + 1);    // edge nos are sorted implicitly in edgeNoVector(), 
                                            // so we are sure, not to use an existing edge no
              
              aNewEdge.rTo().setVal(SlTmToMaEdgeTo::EDGE_TO_EDGE_NO, newEdgeNo); // edge no is in TO data too
              aTool.rEdgeColl().insert(newEdgeNo, aNewEdge);                     // insert into tools edge collection

            } // current last existing edge
          } // setVal of wear length succeeded
        } //if (isEdgeContained)
      } //for (edgeIdx = 0; edgeIdx < edgeCount; ++edgeIdx)
    } //if (SlTmToMaToolData::TOOL_MONITOR_VALUE_MASK_WEAR & toolMonitorMode)
  } //valid toolMonitorMode
\endcode

*/


/*!
  \page exportimport Export and import of data

 
  This is not a matter of clients, which use SlTmQCmd / SlTmCmd, \n
  because export and import of data is done \n
  by sltmservice and sltmutilities implementation code behind the scenery. \n

  Binary data export format \n
  can change between versions of software. \n
  Therefore exported binary data are not qualified to implement data persistency
  during change of software version.

  To improve compatibility, use of masked export and import must be done: \n
  For export use default mask, which reflects known data of exporting software version. \n
  For import use old mask from exported data, 
  which prevents import software from trying to read newly known data, 
  which are not existing in old exported data.

  Text data export \n
  reflects internal data storage and can change between versions of software. \n
  It is usefull for a human reader to verify data manually, but it is not qualified to be compared 
  by test automation during change of software version.

  Binary data export / import methods and Text data export methods \n
  are made for internal use only and may be changed or canceled at any time. \n
  They are hidden in Open Architecture Documentation. \n

  An export / import of (tool / multitool) data in TO-INI text format has become available \n
  (yet for internal use only), \n
  which works independently of sltmservice / sltmutilities software versions. \n
  \n
  Keep on to consider further limits of TO-INI compatibility \n
  between different NC software versions  during export and import and \n
  between different machine data settings during export and import.

  TO-INI text format is suitable for human readers as well as for data exchange to other systems \n
  (at least for those which know the TO-INI format).
  
*/

/*!
  \page multithreading Multithreading and coordinated access to toolmanagement services data

  For writing and reading stores data in our multi threaded environment, \n
  it is necessary to sequentialize access within sltmservice. 

  Therefore for every access to stores data within sltmservice, \n
  stores read write mutex QReadWriteLock* SlTmStore.pReadWriteLock() must be used \n
  by a SlTmQRWLocker, having SlTmQRWLocker::LOCK_LEVEL_READ or SlTmQRWLocker::LOCK_LEVEL_WRITE. 

  This is not a matter of clients, which use SlTmQCmd / SlTmCmd to access stores data, \n
  because locking is done by sltmservice or sltmutilites implementation code behind the scenery.
  \n

  Involved methods, classes and files have been made for internal use only and may be changed or canceled at any time. They are hidden in Open Architecture Documentation.

\cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

Examples:
  \code
  SlTmStore& rStore;
  
  // ...
  
  // read only access:
  { // begin of code that is sequentialized
    // get access or wait here:
    SlTmQRWLocker readLocker(
                           SlTmQRWLocker::LOCK_LEVEL_READ,
                           rStore.pReadWriteLock()
                                   // pointer to read write lock of store
                            );
    // read and compute stores data after this line

  } // end of code that is sequentialized

  // read write access:
  { // begin of code that is sequentialized
    // get access or wait here:
    SlTmQRWLocker writeLocker(
                             SlTmQRWLocker::LOCK_LEVEL_WRITE,
                             rStore.pReadWriteLock()
                                     // pointer to read write lock of store
                             );
    // read and write stores data after this line

  } // end of code that is sequentialized
  \endcode  

  Never try to lock a QReadWriteLock more than one times 
  within one thread.
  Either read access or write access can be acquired, not both for same time.

  Do NEVER hold a lock, while giving control away i.e. 
  SlCap call, sleep time, waiting for events, sending notify via ACE/TAO/CORBA.
  Consider ACE/TAOs thread recycling, which can lead to unexpected multiple use 
  of same thread, where developer usualy would expect different threads.
  
  
  Shallow and deep copy in Qt4:
  
  SlTmStore consists of Qt4-Data-Collections.
  Qt4-Data-Collection can be accessed concurrently by multiple threads. 
  Q3DeepCopy is no longer necessary, operator=() does work very well. 

  But since SlTmStore consists of many such Qt4-Data-Collections and we need 
  a consistent (a snapshoot) view of all of them, we further need 
  sequentialized access via QReadWriteLock. 
  
  Further more its best to sequentialize 
  access to single Qt4-Data-Collections to avoid confusion when using 
  read and write iterators.

<!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

*/


/*!
  \page crossreferenceopi Cross reference between sltmutilities <b>data classes</b> and corresponding  <b>OPI / BTSS items</b>

  This table shows interrelationship between \n
  - <b>NC's OPI / BTSS items</b> (like used via SlCap) and \n
  - <b>data classes</b> and <b>data index enums</b> of <b>sltmservice data store</b>.
  .

  SlTmService data store data reflect more or less NC's data, like read or written via OPI / BTSS interface. \n
  In some cases, there is no direct interrelationship. \n
  For detailed information about sltmservice data store, follow links. 
  
  Addressing of stores data by get-reference-methods (like i.e. ...%rEdge(...).%rTo().%val(...)) \n
  is shown in header of data module in an abbreviated manner in one line. \n
  The always necessary verification of validness of reference (like via i.e. bool* isEdgeContained) is ommited here. \n
  (See examples in \ref typicalmethods for necessary verification of validness of references.) \n
  In description, chain of get-reference-methods allways starts at root %SlTmStore. \n
  Client code usually deals with shorter part of reference chain, typically starting behind %rTool() or %rPlace(), \n
  when data-changes arrive via SlTmQCmd::signalNotifySubscribeToolMagList() and accordingly \n SlTmCmdCallBackI::onNotifySubscribeToolMagList() in a SlTmMassDataToolMagListChangedData class object, \n
  ordered by SlTmQCmd::subscribeToolMagList() and accordingly SlTmCmd::subscribeToolMagList(). \n
  \n

<b>Cross reference between sltmutilities data classes and corresponding OPI / BTSS items:</b> \n
<TABLE>
  <TR><TD><b>Tool Edge: Tool Offset Data, Part 1</b> \n
\code
SlTmStore::rContainerColl().rContainer(containerNo).rToolColl().rTool(tNo).rEdgeColl().rEdge(edgeNo).rTo().setVal(SlTmToMaEdgeTo::EdgeToIdxEnum); 
SlTmStore::rConstContainerColl().rConstContainer(containerNo).rConstToolColl().rConstTool(tNo).rConstEdgeColl().rConstEdge(edgeNo).rConstTo().val(SlTmToMaEdgeTo::EdgeToIdxEnum); 
\endcode
          OPI / BTSS data module: number 0x14 = 20,  TO, edge TO params, Tool offsets
  </TD></TR>
  <TABLE>
    <TR><TD> OPI / BTSS item              </TD><TD> data class      </TD><TD> data kind enum               </TD><TD> data index enum                                     </TD><TD> NC data                                                                                                    </TD></TR>
    <TR><TD> -                            </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_EDGE_NO                     </TD><TD> Edge number, number (not count) of edge, edgeNo                                                            </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_TOOL_TYPE                   </TD><TD> Edge TO-Param 1:  Geometry - tool type ($TC_DP1)                                                           </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_CUTT_EDGE_POS               </TD><TD> Edge TO-Param 2:  Geometry - tool point direction ($TC_DP2)                                                </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_GEO_LENGTH1                 </TD><TD> Edge TO-Param 3:  Geometry - length 1 ($TC_DP3)                                                            </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_GEO_LENGTH2                 </TD><TD> Edge TO-Param 4:  Geometry - length 2 ($TC_DP4)                                                            </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_GEO_LENGTH3                 </TD><TD> Edge TO-Param 5:  Geometry - length 3 ($TC_DP5)                                                            </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_GEO_RADIUS                  </TD><TD> Edge TO-Param 6:  Geometry - radius ($TC_DP6)                                                              </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_GEO_CORNER_RADIUS           </TD><TD> Edge TO-Param 7:  Geometry - corner radius ($TC_DP7)                                                       </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_GEO_LENGTH4                 </TD><TD> Edge TO-Param 8:  Geometry - length 4 ($TC_DP8)                                                            </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_GEO_LENGTH5                 </TD><TD> Edge TO-Param 9:  Geometry - length 5 ($TC_DP9)                                                            </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_GEO_ANGLE1                  </TD><TD> Edge TO-Param 10: Geometry - angle 1 ($TC_DP10)                                                            </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_GEO_ANGLE2                  </TD><TD> Edge TO-Param 11: Geometry - angle 2 ($TC_DP11)                                                            </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_WEAR_LENGTH1                </TD><TD> Edge TO-Param 12: Wear - length 1 ($TC_DP12)                                                               </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_WEAR_LENGTH2                </TD><TD> Edge TO-Param 13: Wear - length 2 ($TC_DP13)                                                               </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_WEAR_LENGTH3                </TD><TD> Edge TO-Param 14: Wear - length 2 ($TC_DP14)                                                               </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_WEAR_RADIUS                 </TD><TD> Edge TO-Param 15: Wear - radius ($TC_DP15)                                                                 </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_WEAR_CORNER_RADIUS          </TD><TD> Edge TO-Param 16: Wear - slot width b / rounding radius ($TC_DP16) or                                      </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_WEAR_SLOT_WIDTH_B           </TD><TD> Edge TO-Param 16: Wear - slot width b / rounding radius ($TC_DP16)                                         </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_WEAR_LENGTH4                </TD><TD> Edge TO-Param 17: Wear - proj. length k ($TC_DP17)                                                         </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_WEAR_LENGTH5                </TD><TD> Edge TO-Param 18: Wear - length 5 ($TC_DP18)                                                               </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_WEAR_ANGLE1                 </TD><TD> Edge TO-Param 19: Wear - angle 1 ($TC_DP19)                                                                </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_WEAR_ANGLE2                 </TD><TD> Edge TO-Param 20: Wear - angle 2 for tapered milling tools ($TC_DP20)                                      </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_ADPT_LENGTH1                </TD><TD> Edge TO-Param 21: Adapter - length 1 ($TC_DP21)                                                            </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_ADPT_LENGTH2                </TD><TD> Edge TO-Param 22: Adapter - length 2 ($TC_DP22)                                                            </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_ADPT_LENGTH3                </TD><TD> Edge TO-Param 23: Adapter - length 3 ($TC_DP23)                                                            </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_RELIEF_ANGLE                </TD><TD> Edge TO-Param 24: Relief angle ($TC_DP24)                                                                  </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_CUTTRATE                    </TD><TD> Edge TO-Param 25: Manual Turn: Cutting rate ($TC_DP25)                                                     </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_SMBITS                      </TD><TD> Edge TO-Param 25: Shopmill: Bit-coded value for different states of tools of type 1xx and 2xx ($TC_DP25)   </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_ISOHNO                      </TD><TD> Edge TO-Param 26: H parameter ISO-H-No ($TC_DPH) (deprecated ISO2.1, ISO3.1 )                              </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_ORIENT_NO                   </TD><TD> Edge TO-Param 27: Tool cutting edge orientation ($TC_DPV)                                                  </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_ORIENT_LENGTH1              </TD><TD> Edge TO-Param 28: L1 tool cutting edge orientation ($TC_DPV3)                                              </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_ORIENT_LENGTH2              </TD><TD> Edge TO-Param 29: L2 tool cutting edge orientation ($TC_DPV4)                                              </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_ORIENT_LENGTH3              </TD><TD> Edge TO-Param 30: L3 tool cutting edge orientation ($TC_DPV5)                                              </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_ORIENT_NORMAL_VECT_LENGTH1  </TD><TD> Edge TO-Param 31: L1 component of the tool cutting edge orientation normal vector ($TC_DPVN3)              </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_ORIENT_NORMAL_VECT_LENGTH2  </TD><TD> Edge TO-Param 32: L2 component of the tool cutting edge orientation normal vector ($TC_DPVN4)              </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_ORIENT_NORMAL_VECT_LENGTH3  </TD><TD> Edge TO-Param 33: L3 component of the tool cutting edge orientation normal vector ($TC_DPVN5)              </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_NUMBER_OF_TEETH             </TD><TD> Edge TO-Param 34: number of teeth ($TC_DPNT)                                                               </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeTo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO  </TD><TD> SlTmToMaEdgeTo::EDGE_TO_BASIC_ROTATION_ANGLE        </TD><TD> Edge TO-Param 35: Geometry - basic rotation angle ($TC_DPROT)                                              </TD></TR>
  </TABLE>
</TABLE>
\n
<TABLE>
  <TR><TD><b>Tool Edge: Tool Offset Data, Part 2</b> \n
\code
SlTmStore::rContainerColl().rContainer(containerNo).rToolColl().rTool(tNo).rEdgeColl().rEdge(edgeNo).rOptDNo().setVal(); 
SlTmStore::rConstContainerColl().rConstContainer(containerNo).rConstToolColl().rConstTool(tNo).rConstEdgeColl().rConstEdge(edgeNo).rConstOptDNo().val(); 
\endcode
          OPI / BTSS data module: number 0x14 = 20,  TO, edge TO params, Tool offsets
  </TD></TR>
  <TABLE>
    <TR><TD> OPI / BTSS item              </TD><TD> data class          </TD><TD> data kind enum                   </TD><TD> data index enum                             </TD><TD> NC data  </TD></TR>
    <TR><TD> /Tool/Compensation/edgeData  </TD><TD> SlTmToMaEdgeOptDNo  </TD><TD> SlTmUtil::DATA_KIND_EDGE_OPTDNO  </TD><TD> -                                           </TD><TD> Edge TO-Param: Additional Edge Param edgeOptDNo: associated optional D number of edge, sometimes called "unique D number" or "any D number" or "assigned D number". This is NOT $TC_DPCE. </TD></TR>
  </TABLE>
</TABLE>
\n
<TABLE>
  <TR><TD><b>Tool Edge: Tool Edge Collection, Part 3</b> \n
\code
edgeNo SlTmStore::rContainerColl().rContainer(containerNo).rToolColl().rTool(tNo).rEdgeColl().getEdgeNoByDNo(dNo); 
edgeNo SlTmStore::rConstContainerColl().rConstContainer(containerNo).rConstToolColl().rConstTool(tNo).rConstEdgeColl().getEdgeNoByDNo(dNo); 
\endcode
          OPI / BTSS data module: number 0x14 = 20,  TO, edge TO params, Tool offsets
  </TD></TR>
  <TABLE>
    <TR><TD> OPI / BTSS item                                </TD><TD> data class        </TD><TD> data kind enum                                            </TD><TD> data index enum                                                                                                              </TD><TD> NC data  </TD></TR>
    <TR><TD> there is no direct equivalent OPI / BTSS data  </TD><TD> SlTmToMaEdgeColl  </TD><TD> SlTmUtil::DATA_KIND_SPECIAL_FUNCTION_GET_EDGE_NO_BY_D_NO  </TD><TD> SlTmToMaEdgeColl::EDGE_COLL_SPECIAL_FUNCTION_GET_EDGE_NO_BY_D_NO_UNIQUE_TRUE_EDGE_NO_IF_OPTDNO_FUNCTION_IS_SWITCHED_OFF_TRUE </TD><TD> Edge TO-Param: like $TC_DPCE, edge no of edge, addressed by (sometimes optional) D no. </TD></TR>
  </TABLE>
</TABLE>
\n
<TABLE>
  <TR><TD><b>Tool Edge: transformed Tool Offset Data</b> \n
\code
SlTmStore::rContainerColl().rContainer(containerNo).rToolColl().rTool(tNo).rEdgeColl().rEdge(edgeNo).rToTr().setVal(SlTmToMaEdgeToTr::EdgeToIdxEnum); 
SlTmStore::rConstContainerColl().rConstContainer(containerNo).rConstToolColl().rConstTool(tNo).rConstEdgeColl().rConstEdge(edgeNo).rConstToTr().val(SlTmToMaEdgeToTr::EdgeToIdxEnum); 
\endcode
          OPI / BTSS data module: number 0x49 = 73,  TOT, transformed edge TO params, transformed Tool offsets
  </TD></TR>
  <TABLE>
    <TR><TD> OPI / BTSS item              </TD><TD> data class        </TD><TD> data kind enum                  </TD><TD> data index enum                                       </TD><TD> NC data                                                                                                                      </TD></TR>
    <TR><TD> -                            </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_EDGE_NO                     </TD><TD> Edge number, number (not count) of edge, edgeNo                                                                              </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeData  </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_TOOL_TYPE                   </TD><TD> transformed, like Edge TO-Param 1:  Geometry - tool type ($TC_DP1)                                                           </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeData  </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_CUTT_EDGE_POS               </TD><TD> transformed, like Edge TO-Param 2:  Geometry - tool point direction ($TC_DP2)                                                </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeData  </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_GEO_LENGTH1                 </TD><TD> transformed, like Edge TO-Param 3:  Geometry - length 1 ($TC_DP3)                                                            </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeData  </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_GEO_LENGTH2                 </TD><TD> transformed, like Edge TO-Param 4:  Geometry - length 2 ($TC_DP4)                                                            </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeData  </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_GEO_LENGTH3                 </TD><TD> transformed, like Edge TO-Param 5:  Geometry - length 3 ($TC_DP5)                                                            </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeData  </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_GEO_RADIUS                  </TD><TD> transformed, like Edge TO-Param 6:  Geometry - radius ($TC_DP6)                                                              </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeData  </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_GEO_CORNER_RADIUS           </TD><TD> transformed, like Edge TO-Param 7:  Geometry - corner radius ($TC_DP7)                                                       </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeData  </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_GEO_LENGTH4                 </TD><TD> transformed, like Edge TO-Param 8:  Geometry - length 4 ($TC_DP8)                                                            </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeData  </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_GEO_LENGTH5                 </TD><TD> transformed, like Edge TO-Param 9:  Geometry - length 5 ($TC_DP9)                                                            </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeData  </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_GEO_ANGLE1                  </TD><TD> transformed, like Edge TO-Param 10: Geometry - angle 1 ($TC_DP10)                                                            </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeData  </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_GEO_ANGLE2                  </TD><TD> transformed, like Edge TO-Param 11: Geometry - angle 2 ($TC_DP11)                                                            </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeData  </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_WEAR_LENGTH1                </TD><TD> transformed, like Edge TO-Param 12: Wear - length 1 ($TC_DP12)                                                               </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeData  </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_WEAR_LENGTH2                </TD><TD> transformed, like Edge TO-Param 13: Wear - length 2 ($TC_DP13)                                                               </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeData  </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_WEAR_LENGTH3                </TD><TD> transformed, like Edge TO-Param 14: Wear - length 2 ($TC_DP14)                                                               </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeData  </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_WEAR_RADIUS                 </TD><TD> transformed, like Edge TO-Param 15: Wear - radius ($TC_DP15)                                                                 </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeData  </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_WEAR_CORNER_RADIUS          </TD><TD> transformed, like Edge TO-Param 16: Wear - slot width b / rounding radius ($TC_DP16) or                                      </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeData  </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_WEAR_SLOT_WIDTH_B           </TD><TD> transformed, like Edge TO-Param 16: Wear - slot width b / rounding radius ($TC_DP16)                                         </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeData  </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_WEAR_LENGTH4                </TD><TD> transformed, like Edge TO-Param 17: Wear - proj. length k ($TC_DP17)                                                         </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeData  </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_WEAR_LENGTH5                </TD><TD> transformed, like Edge TO-Param 18: Wear - length 5 ($TC_DP18)                                                               </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeData  </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_WEAR_ANGLE1                 </TD><TD> transformed, like Edge TO-Param 19: Wear - angle 1 ($TC_DP19)                                                                </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeData  </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_WEAR_ANGLE2                 </TD><TD> transformed, like Edge TO-Param 20: Wear - angle 2 for tapered milling tools ($TC_DP20)                                      </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeData  </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_ADPT_LENGTH1                </TD><TD> transformed, like Edge TO-Param 21: Adapter - length 1 ($TC_DP21)                                                            </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeData  </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_ADPT_LENGTH2                </TD><TD> transformed, like Edge TO-Param 22: Adapter - length 2 ($TC_DP22)                                                            </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeData  </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_ADPT_LENGTH3                </TD><TD> transformed, like Edge TO-Param 23: Adapter - length 3 ($TC_DP23)                                                            </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeData  </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_RELIEF_ANGLE                </TD><TD> transformed, like Edge TO-Param 24: Relief angle ($TC_DP24)                                                                  </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeData  </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_CUTTRATE                    </TD><TD> transformed, like Edge TO-Param 25: Manual Turn: Cutting rate ($TC_DP25)                                                     </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeData  </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_SMBITS                      </TD><TD> transformed, like Edge TO-Param 25: Shopmill: Bit-coded value for different states of tools of type 1xx and 2xx ($TC_DP25)   </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeData  </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_ISOHNO                      </TD><TD> transformed, like Edge TO-Param 26: H parameter ISO-H-No ($TC_DPH) (deprecated ISO2.1, ISO3.1 )                              </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeData  </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_ORIENT_NO                   </TD><TD> transformed, like Edge TO-Param 27: Tool cutting edge orientation ($TC_DPV)                                                  </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeData  </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_ORIENT_LENGTH1              </TD><TD> transformed, like Edge TO-Param 28: L1 tool cutting edge orientation ($TC_DPV3)                                              </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeData  </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_ORIENT_LENGTH2              </TD><TD> transformed, like Edge TO-Param 29: L2 tool cutting edge orientation ($TC_DPV4)                                              </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeData  </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_ORIENT_LENGTH3              </TD><TD> transformed, like Edge TO-Param 30: L3 tool cutting edge orientation ($TC_DPV5)                                              </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeData  </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_ORIENT_NORMAL_VECT_LENGTH1  </TD><TD> transformed, like Edge TO-Param 31: L1 component of the tool cutting edge orientation normal vector ($TC_DPVN3)              </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeData  </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_ORIENT_NORMAL_VECT_LENGTH2  </TD><TD> transformed, like Edge TO-Param 32: L2 component of the tool cutting edge orientation normal vector ($TC_DPVN4)              </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeData  </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_ORIENT_NORMAL_VECT_LENGTH3  </TD><TD> transformed, like Edge TO-Param 33: L3 component of the tool cutting edge orientation normal vector ($TC_DPVN5)              </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeData  </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_NUMBER_OF_TEETH             </TD><TD> transformed, like Edge TO-Param 34: number of teeth ($TC_DPNT)                                                               </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeData  </TD><TD> SlTmToMaEdgeToTr  </TD><TD> SlTmUtil::DATA_KIND_EDGE_TO_TR  </TD><TD> SlTmToMaEdgeToTr::EDGE_TO_BASIC_ROTATION_ANGLE        </TD><TD> transformed, like Edge TO-Param 35: Geometry - basic rotation angle ($TC_DPROT)                                              </TD></TR>
  </TABLE>
</TABLE>
\n
<TABLE>
  <TR><TD><b>Tool Edge: Edge User Data (OEM Data)</b> \n
\code
SlTmStore::rContainerColl().rContainer(containerNo).rToolColl().rTool(tNo).rEdgeColl().rEdge(edgeNo).rUser().setVal(SlTmToMaEdgeUser::EdgeUserIdxEnum); 
SlTmStore::rConstContainerColl().rConstContainer(containerNo).rConstToolColl().rConstTool(tNo).rConstEdgeColl().rConstEdge(edgeNo).rConstUser().val(SlTmToMaEdgeUser::EdgeUserIdxEnum); 
\endcode
          OPI data module: number 0x25 = 37, TUE, edge user params, Tool edge data for OEM
  </TD></TR>
  <TABLE>
    <TR><TD> OPI / BTSS item     </TD><TD> data class        </TD><TD> data kind enum                </TD><TD> data index enum                 </TD><TD> NC data                         </TD></TR>
    <TR><TD> /Tool/User/edgeData </TD><TD> SlTmToMaEdgeUser  </TD><TD> SlTmUtil::DATA_KIND_EDGE_USER </TD><TD> SlTmToMaEdgeUser::EDGE_USER_1   </TD><TD> Edge User-Param 1,  ($TC_DPC1)  </TD></TR>
    <TR><TD> /Tool/User/edgeData </TD><TD> SlTmToMaEdgeUser  </TD><TD> SlTmUtil::DATA_KIND_EDGE_USER </TD><TD> SlTmToMaEdgeUser::EDGE_USER_2   </TD><TD> Edge User-Param 2,  ($TC_DPC2)  </TD></TR>
    <TR><TD> /Tool/User/edgeData </TD><TD> SlTmToMaEdgeUser  </TD><TD> SlTmUtil::DATA_KIND_EDGE_USER </TD><TD> SlTmToMaEdgeUser::EDGE_USER_3   </TD><TD> Edge User-Param 3,  ($TC_DPC3)  </TD></TR>
    <TR><TD> /Tool/User/edgeData </TD><TD> SlTmToMaEdgeUser  </TD><TD> SlTmUtil::DATA_KIND_EDGE_USER </TD><TD> SlTmToMaEdgeUser::EDGE_USER_4   </TD><TD> Edge User-Param 4,  ($TC_DPC4)  </TD></TR>
    <TR><TD> /Tool/User/edgeData </TD><TD> SlTmToMaEdgeUser  </TD><TD> SlTmUtil::DATA_KIND_EDGE_USER </TD><TD> SlTmToMaEdgeUser::EDGE_USER_5   </TD><TD> Edge User-Param 5,  ($TC_DPC5)  </TD></TR>
    <TR><TD> /Tool/User/edgeData </TD><TD> SlTmToMaEdgeUser  </TD><TD> SlTmUtil::DATA_KIND_EDGE_USER </TD><TD> SlTmToMaEdgeUser::EDGE_USER_6   </TD><TD> Edge User-Param 6,  ($TC_DPC6)  </TD></TR>
    <TR><TD> /Tool/User/edgeData </TD><TD> SlTmToMaEdgeUser  </TD><TD> SlTmUtil::DATA_KIND_EDGE_USER </TD><TD> SlTmToMaEdgeUser::EDGE_USER_7   </TD><TD> Edge User-Param 7,  ($TC_DPC7)  </TD></TR>
    <TR><TD> /Tool/User/edgeData </TD><TD> SlTmToMaEdgeUser  </TD><TD> SlTmUtil::DATA_KIND_EDGE_USER </TD><TD> SlTmToMaEdgeUser::EDGE_USER_8   </TD><TD> Edge User-Param 8,  ($TC_DPC8)  </TD></TR>
    <TR><TD> /Tool/User/edgeData </TD><TD> SlTmToMaEdgeUser  </TD><TD> SlTmUtil::DATA_KIND_EDGE_USER </TD><TD> SlTmToMaEdgeUser::EDGE_USER_9   </TD><TD> Edge User-Param 9,  ($TC_DPC9)  </TD></TR>
    <TR><TD> /Tool/User/edgeData </TD><TD> SlTmToMaEdgeUser  </TD><TD> SlTmUtil::DATA_KIND_EDGE_USER </TD><TD> SlTmToMaEdgeUser::EDGE_USER_10  </TD><TD> Edge User-Param 10, ($TC_DPC10) </TD></TR>
    <TR><TD> ...                 </TD><TD> ...               </TD><TD> ...                           </TD><TD> ...                             </TD><TD> ...                             </TD></TR>
    <TR><TD> /Tool/User/edgeData </TD><TD> SlTmToMaEdgeUser  </TD><TD> SlTmUtil::DATA_KIND_EDGE_USER </TD><TD> SlTmToMaEdgeUser::EDGE_USER_64  </TD><TD> Edge User-Param 64, ($TC_DPC64) </TD></TR>
  </TABLE>
</TABLE>
\n
<TABLE>
  <TR><TD><b>Tool Edge: Edge Application Specific Data (Siemens Data)</b> \n
\code
SlTmStore::rContainerColl().rContainer(containerNo).rToolColl().rTool(tNo).rEdgeColl().rEdge(edgeNo).rAppl().setVal(SlTmToMaEdgeAppl::EdgeApplIdxEnum); 
SlTmStore::rConstContainerColl().rConstContainer(containerNo).rConstToolColl().rConstTool(tNo).rConstEdgeColl().rConstEdge(edgeNo).rConstAppl().val(SlTmToMaEdgeAppl::EdgeApplIdxEnum); 
\endcode
          OPI data module: number 0x4F = 79, TAO, edge appl params, Application-specific tool edge data
  </TD></TR>
  <TABLE>
    <TR><TD> OPI / BTSS item                 </TD><TD> data class        </TD><TD> data kind enum                </TD><TD> data index enum                 </TD><TD> NC data                          </TD></TR>
    <TR><TD> /Tool/Compensation/applEdgeData </TD><TD> SlTmToMaEdgeAppl  </TD><TD> SlTmUtil::DATA_KIND_EDGE_APPL </TD><TD> SlTmToMaEdgeAppl::EDGE_APPL_1   </TD><TD> Edge Appl-Param 1,  ($TC_DPCS1)  </TD></TR>
    <TR><TD> /Tool/Compensation/applEdgeData </TD><TD> SlTmToMaEdgeAppl  </TD><TD> SlTmUtil::DATA_KIND_EDGE_APPL </TD><TD> SlTmToMaEdgeAppl::EDGE_APPL_2   </TD><TD> Edge Appl-Param 2,  ($TC_DPCS2)  </TD></TR>
    <TR><TD> /Tool/Compensation/applEdgeData </TD><TD> SlTmToMaEdgeAppl  </TD><TD> SlTmUtil::DATA_KIND_EDGE_APPL </TD><TD> SlTmToMaEdgeAppl::EDGE_APPL_3   </TD><TD> Edge Appl-Param 3,  ($TC_DPCS3)  </TD></TR>
    <TR><TD> /Tool/Compensation/applEdgeData </TD><TD> SlTmToMaEdgeAppl  </TD><TD> SlTmUtil::DATA_KIND_EDGE_APPL </TD><TD> SlTmToMaEdgeAppl::EDGE_APPL_4   </TD><TD> Edge Appl-Param 4,  ($TC_DPCS4)  </TD></TR>
    <TR><TD> /Tool/Compensation/applEdgeData </TD><TD> SlTmToMaEdgeAppl  </TD><TD> SlTmUtil::DATA_KIND_EDGE_APPL </TD><TD> SlTmToMaEdgeAppl::EDGE_APPL_5   </TD><TD> Edge Appl-Param 5,  ($TC_DPCS5)  </TD></TR>
    <TR><TD> /Tool/Compensation/applEdgeData </TD><TD> SlTmToMaEdgeAppl  </TD><TD> SlTmUtil::DATA_KIND_EDGE_APPL </TD><TD> SlTmToMaEdgeAppl::EDGE_APPL_6   </TD><TD> Edge Appl-Param 6,  ($TC_DPCS6)  </TD></TR>
    <TR><TD> /Tool/Compensation/applEdgeData </TD><TD> SlTmToMaEdgeAppl  </TD><TD> SlTmUtil::DATA_KIND_EDGE_APPL </TD><TD> SlTmToMaEdgeAppl::EDGE_APPL_7   </TD><TD> Edge Appl-Param 7,  ($TC_DPCS7)  </TD></TR>
    <TR><TD> /Tool/Compensation/applEdgeData </TD><TD> SlTmToMaEdgeAppl  </TD><TD> SlTmUtil::DATA_KIND_EDGE_APPL </TD><TD> SlTmToMaEdgeAppl::EDGE_APPL_8   </TD><TD> Edge Appl-Param 8,  ($TC_DPCS8)  </TD></TR>
    <TR><TD> /Tool/Compensation/applEdgeData </TD><TD> SlTmToMaEdgeAppl  </TD><TD> SlTmUtil::DATA_KIND_EDGE_APPL </TD><TD> SlTmToMaEdgeAppl::EDGE_APPL_9   </TD><TD> Edge Appl-Param 9,  ($TC_DPCS9)  </TD></TR>
    <TR><TD> /Tool/Compensation/applEdgeData </TD><TD> SlTmToMaEdgeAppl  </TD><TD> SlTmUtil::DATA_KIND_EDGE_APPL </TD><TD> SlTmToMaEdgeAppl::EDGE_APPL_10  </TD><TD> Edge Appl-Param 10, ($TC_DPCS10) </TD></TR>
  </TABLE>
</TABLE>
\n
<TABLE>
  <TR><TD><b>Tool Edge: Edge Supervision Data </b> \n
\code
SlTmStore::rContainerColl().rContainer(containerNo).rToolColl().rTool(tNo).rEdgeColl().rEdge(edgeNo).rSup().setVal(SlTmToMaEdgeSup::EdgeSupIdxEnum); 
SlTmStore::rConstContainerColl().rConstContainer(containerNo).rConstToolColl().rConstTool(tNo).rConstEdgeColl().rConstEdge(edgeNo).rConstSup().val(SlTmToMaEdgeSup::EdgeSupIdxEnum); 
\endcode
          OPI data module: number 0x22 = 34, TS, edge supervision params, Tool monitoring data
  </TD></TR>
  <TABLE>
    <TR><TD> OPI / BTSS item         </TD><TD> data class       </TD><TD> data kind enum                </TD><TD> data index enum                               </TD><TD> NC data                                                                                        </TD></TR>
    <TR><TD> /Tool/Supervision/data  </TD><TD> SlTmToMaEdgeSup  </TD><TD> SlTmUtil::DATA_KIND_EDGE_SUP  </TD><TD> SlTmToMaEdgeSup::EDGE_SUP_WARNING_TIME        </TD><TD> Sup-Param 1: prewarning limit service life in minutes ($TC_MOP1)                               </TD></TR>
    <TR><TD> /Tool/Supervision/data  </TD><TD> SlTmToMaEdgeSup  </TD><TD> SlTmUtil::DATA_KIND_EDGE_SUP  </TD><TD> SlTmToMaEdgeSup::EDGE_SUP_REMAINING_TIME      </TD><TD> Sup-Param 2: remaining service life in minutes ($TC_MOP2)                                      </TD></TR>
    <TR><TD> /Tool/Supervision/data  </TD><TD> SlTmToMaEdgeSup  </TD><TD> SlTmUtil::DATA_KIND_EDGE_SUP  </TD><TD> SlTmToMaEdgeSup::EDGE_SUP_WARNING_PIECES      </TD><TD> Sup-Param 3: prewarning limit workpiece number ($TC_MOP3)                                      </TD></TR>
    <TR><TD> /Tool/Supervision/data  </TD><TD> SlTmToMaEdgeSup  </TD><TD> SlTmUtil::DATA_KIND_EDGE_SUP  </TD><TD> SlTmToMaEdgeSup::EDGE_SUP_REMAINING_PIECES    </TD><TD> Sup-Param 4: remaining workpiece number ($TC_MOP4)                                             </TD></TR>
    <TR><TD> /Tool/Supervision/data  </TD><TD> SlTmToMaEdgeSup  </TD><TD> SlTmUtil::DATA_KIND_EDGE_SUP  </TD><TD> SlTmToMaEdgeSup::EDGE_SUP_DESIRED_TIME        </TD><TD> Sup-Param 5: desired service life ($TC_MOP11)                                                  </TD></TR>
    <TR><TD> /Tool/Supervision/data  </TD><TD> SlTmToMaEdgeSup  </TD><TD> SlTmUtil::DATA_KIND_EDGE_SUP  </TD><TD> SlTmToMaEdgeSup::EDGE_SUP_DESIRED_PIECES      </TD><TD> Sup-Param 6: desired workpiece number ($TC_MOP13)                                              </TD></TR>
    <TR><TD> /Tool/Supervision/data  </TD><TD> SlTmToMaEdgeSup  </TD><TD> SlTmUtil::DATA_KIND_EDGE_SUP  </TD><TD> SlTmToMaEdgeSup::EDGE_SUP_WARNING_WEAR        </TD><TD> Sup-Param 7: prewarning limit wear (NC-SW 5.1 and later) ($TC_MOP5)                            </TD></TR>
    <TR><TD> /Tool/Supervision/data  </TD><TD> SlTmToMaEdgeSup  </TD><TD> SlTmUtil::DATA_KIND_EDGE_SUP  </TD><TD> SlTmToMaEdgeSup::EDGE_SUP_REMAINING_WEAR      </TD><TD> Sup-Param 8: remaining wear (actual value) (NC-SW 5.1 and later) ($TC_MOP6) cannot be written  </TD></TR>
    <TR><TD> /Tool/Supervision/data  </TD><TD> SlTmToMaEdgeSup  </TD><TD> SlTmUtil::DATA_KIND_EDGE_SUP  </TD><TD> SlTmToMaEdgeSup::EDGE_SUP_DESIRED_WEAR        </TD><TD> Sup-Param 9: desired wear (NC-SW 5.1 and later) ($TC_MOP15)                                    </TD></TR>
    <TR><TD> /Tool/Supervision/data  </TD><TD> SlTmToMaEdgeSup  </TD><TD> SlTmUtil::DATA_KIND_EDGE_SUP  </TD><TD> SlTmToMaEdgeSup::EDGE_SUP_EXT_DESIRED_PIECES  </TD><TD> Sup-Param10: extended desired workpiece number (Automotive PLC only)                           </TD></TR>
  </TABLE>
</TABLE>
\n
<TABLE>
  <TR><TD><b>Tool Edge: Edge User Supervision Data (OEM Data)</b> \n
\code
SlTmStore::rContainerColl().rContainer(containerNo).rToolColl().rTool(tNo).rEdgeColl().rEdge(edgeNo).rSupUser().setVal(SlTmToMaEdgeSupUser::EdgeSupUserIdxEnum); 
SlTmStore::rConstContainerColl().rConstContainer(containerNo).rConstToolColl().rConstTool(tNo).rConstEdgeColl().rConstEdge(edgeNo).rConstSupUser().val(SlTmToMaEdgeSupUser::EdgeSupUserIdxEnum); 
\endcode
          OPI data module: number 0x3D = 61, TUS, edge supervision user params, User monitoring data
  </TD></TR>
  <TABLE>
    <TR><TD> OPI / BTSS item            </TD><TD> data class           </TD><TD> data kind enum                   </TD><TD> data index enum                       </TD><TD> NC data                                      </TD></TR>
    <TR><TD> /Tool/Supervision/userData </TD><TD> SlTmToMaEdgeSupUser  </TD><TD> SlTmUtil::DATA_KIND_EDGE_SUPUSER </TD><TD> SlTmToMaEdgeSupUser::EDGE_SUPUSER_1   </TD><TD> Edge Supervision-User-Param 1,  ($TC_MOPC1)  </TD></TR>
    <TR><TD> /Tool/Supervision/userData </TD><TD> SlTmToMaEdgeSupUser  </TD><TD> SlTmUtil::DATA_KIND_EDGE_SUPUSER </TD><TD> SlTmToMaEdgeSupUser::EDGE_SUPUSER_2   </TD><TD> Edge Supervision-User-Param 2,  ($TC_MOPC2)  </TD></TR>
    <TR><TD> /Tool/Supervision/userData </TD><TD> SlTmToMaEdgeSupUser  </TD><TD> SlTmUtil::DATA_KIND_EDGE_SUPUSER </TD><TD> SlTmToMaEdgeSupUser::EDGE_SUPUSER_3   </TD><TD> Edge Supervision-User-Param 3,  ($TC_MOPC3)  </TD></TR>
    <TR><TD> /Tool/Supervision/userData </TD><TD> SlTmToMaEdgeSupUser  </TD><TD> SlTmUtil::DATA_KIND_EDGE_SUPUSER </TD><TD> SlTmToMaEdgeSupUser::EDGE_SUPUSER_4   </TD><TD> Edge Supervision-User-Param 4,  ($TC_MOPC4)  </TD></TR>
    <TR><TD> /Tool/Supervision/userData </TD><TD> SlTmToMaEdgeSupUser  </TD><TD> SlTmUtil::DATA_KIND_EDGE_SUPUSER </TD><TD> SlTmToMaEdgeSupUser::EDGE_SUPUSER_5   </TD><TD> Edge Supervision-User-Param 5,  ($TC_MOPC5)  </TD></TR>
    <TR><TD> /Tool/Supervision/userData </TD><TD> SlTmToMaEdgeSupUser  </TD><TD> SlTmUtil::DATA_KIND_EDGE_SUPUSER </TD><TD> SlTmToMaEdgeSupUser::EDGE_SUPUSER_6   </TD><TD> Edge Supervision-User-Param 6,  ($TC_MOPC6)  </TD></TR>
    <TR><TD> /Tool/Supervision/userData </TD><TD> SlTmToMaEdgeSupUser  </TD><TD> SlTmUtil::DATA_KIND_EDGE_SUPUSER </TD><TD> SlTmToMaEdgeSupUser::EDGE_SUPUSER_7   </TD><TD> Edge Supervision-User-Param 7,  ($TC_MOPC7)  </TD></TR>
    <TR><TD> /Tool/Supervision/userData </TD><TD> SlTmToMaEdgeSupUser  </TD><TD> SlTmUtil::DATA_KIND_EDGE_SUPUSER </TD><TD> SlTmToMaEdgeSupUser::EDGE_SUPUSER_8   </TD><TD> Edge Supervision-User-Param 8,  ($TC_MOPC8)  </TD></TR>
    <TR><TD> /Tool/Supervision/userData </TD><TD> SlTmToMaEdgeSupUser  </TD><TD> SlTmUtil::DATA_KIND_EDGE_SUPUSER </TD><TD> SlTmToMaEdgeSupUser::EDGE_SUPUSER_9   </TD><TD> Edge Supervision-User-Param 9,  ($TC_MOPC9)  </TD></TR>
    <TR><TD> /Tool/Supervision/userData </TD><TD> SlTmToMaEdgeSupUser  </TD><TD> SlTmUtil::DATA_KIND_EDGE_SUPUSER </TD><TD> SlTmToMaEdgeSupUser::EDGE_SUPUSER_10  </TD><TD> Edge Supervision-User-Param 10, ($TC_MOPC10) </TD></TR>
    <TR><TD> ...                        </TD><TD> ...                  </TD><TD> ...                              </TD><TD> ...                                   </TD><TD> ...                                          </TD></TR>
    <TR><TD> /Tool/Supervision/userData </TD><TD> SlTmToMaEdgeSupUser  </TD><TD> SlTmUtil::DATA_KIND_EDGE_SUPUSER </TD><TD> SlTmToMaEdgeSupUser::EDGE_SUPUSER_64  </TD><TD> Edge Supervision-User-Param 64, ($TC_MOPC64) </TD></TR>
  </TABLE>
</TABLE>
\n
<TABLE>
  <TR><TD><b>Tool Edge: Edge Application Supervision Data (Siemens Data)</b> \n
\code
SlTmStore::rContainerColl().rContainer(containerNo).rToolColl().rTool(tNo).rEdgeColl().rEdge(edgeNo).rSupAppl().setVal(SlTmToMaEdgeSupAppl::EdgeSupApplIdxEnum); 
SlTmStore::rConstContainerColl().rConstContainer(containerNo).rConstToolColl().rConstTool(tNo).rConstEdgeColl().rConstEdge(edgeNo).rConstSupAppl().val(SlTmToMaEdgeSupAppl::EdgeSupApplIdxEnum); 
\endcode
          OPI data module: number 0x50 = 80, TAS, edge supervision appl params, Application-specific monitoring data
  </TD></TR>
  <TABLE>
    <TR><TD> OPI / BTSS item            </TD><TD> data class           </TD><TD> data kind enum                   </TD><TD> data index enum                       </TD><TD> NC data                                       </TD></TR>
    <TR><TD> /Tool/Supervision/applData </TD><TD> SlTmToMaEdgeSupAppl  </TD><TD> SlTmUtil::DATA_KIND_EDGE_SUPAPPL </TD><TD> SlTmToMaEdgeSupAppl::EDGE_SUPAPPL_1   </TD><TD> Edge Supervision-Appl-Param 1,  ($TC_MOPCS1)  </TD></TR>
    <TR><TD> /Tool/Supervision/applData </TD><TD> SlTmToMaEdgeSupAppl  </TD><TD> SlTmUtil::DATA_KIND_EDGE_SUPAPPL </TD><TD> SlTmToMaEdgeSupAppl::EDGE_SUPAPPL_2   </TD><TD> Edge Supervision-Appl-Param 2,  ($TC_MOPCS2)  </TD></TR>
    <TR><TD> /Tool/Supervision/applData </TD><TD> SlTmToMaEdgeSupAppl  </TD><TD> SlTmUtil::DATA_KIND_EDGE_SUPAPPL </TD><TD> SlTmToMaEdgeSupAppl::EDGE_SUPAPPL_3   </TD><TD> Edge Supervision-Appl-Param 3,  ($TC_MOPCS3)  </TD></TR>
    <TR><TD> /Tool/Supervision/applData </TD><TD> SlTmToMaEdgeSupAppl  </TD><TD> SlTmUtil::DATA_KIND_EDGE_SUPAPPL </TD><TD> SlTmToMaEdgeSupAppl::EDGE_SUPAPPL_4   </TD><TD> Edge Supervision-Appl-Param 4,  ($TC_MOPCS4)  </TD></TR>
    <TR><TD> /Tool/Supervision/applData </TD><TD> SlTmToMaEdgeSupAppl  </TD><TD> SlTmUtil::DATA_KIND_EDGE_SUPAPPL </TD><TD> SlTmToMaEdgeSupAppl::EDGE_SUPAPPL_5   </TD><TD> Edge Supervision-Appl-Param 5,  ($TC_MOPCS5)  </TD></TR>
    <TR><TD> /Tool/Supervision/applData </TD><TD> SlTmToMaEdgeSupAppl  </TD><TD> SlTmUtil::DATA_KIND_EDGE_SUPAPPL </TD><TD> SlTmToMaEdgeSupAppl::EDGE_SUPAPPL_6   </TD><TD> Edge Supervision-Appl-Param 6,  ($TC_MOPCS6)  </TD></TR>
    <TR><TD> /Tool/Supervision/applData </TD><TD> SlTmToMaEdgeSupAppl  </TD><TD> SlTmUtil::DATA_KIND_EDGE_SUPAPPL </TD><TD> SlTmToMaEdgeSupAppl::EDGE_SUPAPPL_7   </TD><TD> Edge Supervision-Appl-Param 7,  ($TC_MOPCS7)  </TD></TR>
    <TR><TD> /Tool/Supervision/applData </TD><TD> SlTmToMaEdgeSupAppl  </TD><TD> SlTmUtil::DATA_KIND_EDGE_SUPAPPL </TD><TD> SlTmToMaEdgeSupAppl::EDGE_SUPAPPL_8   </TD><TD> Edge Supervision-Appl-Param 8,  ($TC_MOPCS8)  </TD></TR>
    <TR><TD> /Tool/Supervision/applData </TD><TD> SlTmToMaEdgeSupAppl  </TD><TD> SlTmUtil::DATA_KIND_EDGE_SUPAPPL </TD><TD> SlTmToMaEdgeSupAppl::EDGE_SUPAPPL_9   </TD><TD> Edge Supervision-Appl-Param 9,  ($TC_MOPCS9)  </TD></TR>
    <TR><TD> /Tool/Supervision/applData </TD><TD> SlTmToMaEdgeSupAppl  </TD><TD> SlTmUtil::DATA_KIND_EDGE_SUPAPPL </TD><TD> SlTmToMaEdgeSupAppl::EDGE_SUPAPPL_10  </TD><TD> Edge Supervision-Appl-Param 10, ($TC_MOPCS10) </TD></TR>
  </TABLE>
</TABLE>
\n
<TABLE>
  <TR><TD><b>Tool Edge: Edge-related Location-dependent Coarse Total Offsets, Edge DL EC Parameters </b> \n
\code
SlTmStore::rContainerColl().rContainer(containerNo).rToolColl().rTool(tNo).rEdgeColl().rEdge(edgeNo).rDlColl().rDl(dlNo).rEc().setVal(SlTmToMaDlEc::DlDataIdxEnum); 
SlTmStore::rConstContainerColl().rConstContainer(containerNo).rConstToolColl().rConstTool(tNo).rConstEdgeColl().rConstEdge(edgeNo).rConstDlColl().rConstDl(dlNo).rConstEc().val(SlTmToMaDlEc::DlDataIdxEnum); 
\endcode
          OPI / BTSS data module: number 0x46 = 70, TOE, edge DL EC params, Edge-related location-dependent coarse total offsets, setup offsets
  </TD></TR>
  <TABLE>
    <TR><TD> OPI / BTSS item                </TD><TD> data class    </TD><TD> data kind enum             </TD><TD> data index enum                      </TD><TD> NC data                                                                                                                                          </TD></TR>
    <TR><TD> /Tool/Compensation/edgeECData  </TD><TD> SlTmToMaDlEc  </TD><TD> SlTmUtil::DATA_KIND_DL_EC  </TD><TD> SlTmToMaDlEc::DL_DATA_LENGTH1        </TD><TD> edge DL SC/EC param 1, ($TC_ECPx3     / $TC_SCPx3     x=DLNo), related to Edge TO-Param 12: Wear - length 1 ($TC_DP12)                           </TD></TR>
    <TR><TD> /Tool/Compensation/edgeECData  </TD><TD> SlTmToMaDlEc  </TD><TD> SlTmUtil::DATA_KIND_DL_EC  </TD><TD> SlTmToMaDlEc::DL_DATA_LENGTH2        </TD><TD> edge DL SC/EC param 2, ($TC_ECPx4     / $TC_SCPx4     x=DLNo), related to Edge TO-Param 13: Wear - length 2 ($TC_DP13)                           </TD></TR>
    <TR><TD> /Tool/Compensation/edgeECData  </TD><TD> SlTmToMaDlEc  </TD><TD> SlTmUtil::DATA_KIND_DL_EC  </TD><TD> SlTmToMaDlEc::DL_DATA_LENGTH3        </TD><TD> edge DL SC/EC param 3, ($TC_ECPx5     / $TC_SCPx5     x=DLNo), related to Edge TO-Param 14: Wear - length 2 ($TC_DP14)                           </TD></TR>
    <TR><TD> /Tool/Compensation/edgeECData  </TD><TD> SlTmToMaDlEc  </TD><TD> SlTmUtil::DATA_KIND_DL_EC  </TD><TD> SlTmToMaDlEc::DL_DATA_RADIUS         </TD><TD> edge DL SC/EC param 4, ($TC_ECPx6     / $TC_SCPx6     x=DLNo), related to Edge TO-Param 15: Wear - radius ($TC_DP15)                             </TD></TR>
    <TR><TD> /Tool/Compensation/edgeECData  </TD><TD> SlTmToMaDlEc  </TD><TD> SlTmUtil::DATA_KIND_DL_EC  </TD><TD> SlTmToMaDlEc::DL_DATA_CORNER_RADIUS  </TD><TD> edge DL SC/EC param 5, ($TC_ECPx7     / $TC_SCPx7     x=DLNo), related to Edge TO-Param 16: Wear - slot width b / rounding radius ($TC_DP16)     </TD></TR>
    <TR><TD> /Tool/Compensation/edgeECData  </TD><TD> SlTmToMaDlEc  </TD><TD> SlTmUtil::DATA_KIND_DL_EC  </TD><TD> SlTmToMaDlEc::DL_DATA_SLOT_WIDTH_B   </TD><TD> edge DL SC/EC param 5, ($TC_ECPx7     / $TC_SCPx7     x=DLNo), related to Edge TO-Param 16: Wear - slot width b / rounding radius ($TC_DP16)     </TD></TR>
    <TR><TD> /Tool/Compensation/edgeECData  </TD><TD> SlTmToMaDlEc  </TD><TD> SlTmUtil::DATA_KIND_DL_EC  </TD><TD> SlTmToMaDlEc::DL_DATA_LENGTH4        </TD><TD> edge DL SC/EC param 6, ($TC_ECPx8     / $TC_SCPx8     x=DLNo), related to Edge TO-Param 17: Wear - proj. length k ($TC_DP17)                     </TD></TR>
    <TR><TD> /Tool/Compensation/edgeECData  </TD><TD> SlTmToMaDlEc  </TD><TD> SlTmUtil::DATA_KIND_DL_EC  </TD><TD> SlTmToMaDlEc::DL_DATA_LENGTH5        </TD><TD> edge DL SC/EC param 7, ($TC_ECPx9     / $TC_SCPx9     x=DLNo), related to Edge TO-Param 18: Wear - length 5 ($TC_DP18)                           </TD></TR>
    <TR><TD> /Tool/Compensation/edgeECData  </TD><TD> SlTmToMaDlEc  </TD><TD> SlTmUtil::DATA_KIND_DL_EC  </TD><TD> SlTmToMaDlEc::DL_DATA_ANGLE1         </TD><TD> edge DL SC/EC param 8, ($TC_ECP(x+1)0 / $TC_SCP(x+1)0 x=DLNo), related to Edge TO-Param 19: Wear - angle 1 ($TC_DP19)                            </TD></TR>
    <TR><TD> /Tool/Compensation/edgeECData  </TD><TD> SlTmToMaDlEc  </TD><TD> SlTmUtil::DATA_KIND_DL_EC  </TD><TD> SlTmToMaDlEc::DL_DATA_ANGLE2         </TD><TD> edge DL SC/EC param 9, ($TC_ECP(x+1)1 / $TC_SCP(x+1)1 x=DLNo), related to Edge TO-Param 20: Wear - angle 2 for tapered milling tools ($TC_DP20)  </TD></TR>
  </TABLE>
</TABLE>
\n
<TABLE>
  <TR><TD><b>Tool Edge: Edge-related Location-dependent Fine Total Offsets, Edge DL SC Parameters </b> \n
\code
SlTmStore::rContainerColl().rContainer(containerNo).rToolColl().rTool(tNo).rEdgeColl().rEdge(edgeNo).rDlColl().rDl(dlNo).rSc().setVal(SlTmToMaDlSc::DlDataIdxEnum); 
SlTmStore::rConstContainerColl().rConstContainer(containerNo).rConstToolColl().rConstTool(tNo).rConstEdgeColl().rConstEdge(edgeNo).rConstDlColl().rConstDl(dlNo).rConstSc().val(SlTmToMaDlSc::DlDataIdxEnum); 
\endcode
          OPI / BTSS data module: number 0x44 = 68, TOS, edge DL SC params, Edge-related positional fine total offsets
  </TD></TR>
  <TABLE>
    <TR><TD> OPI / BTSS item                </TD><TD> data class    </TD><TD> data kind enum             </TD><TD> data index enum                      </TD><TD> NC data                                                                                                                                          </TD></TR>
    <TR><TD> /Tool/Compensation/edgeSCData  </TD><TD> SlTmToMaDlSc  </TD><TD> SlTmUtil::DATA_KIND_DL_SC  </TD><TD> SlTmToMaDlSc::DL_DATA_LENGTH1        </TD><TD> edge DL SC/EC param 1, ($TC_ECPx3     / $TC_SCPx3     x=DLNo), related to Edge TO-Param 12: Wear - length 1 ($TC_DP12)                           </TD></TR>
    <TR><TD> /Tool/Compensation/edgeSCData  </TD><TD> SlTmToMaDlSc  </TD><TD> SlTmUtil::DATA_KIND_DL_SC  </TD><TD> SlTmToMaDlSc::DL_DATA_LENGTH2        </TD><TD> edge DL SC/EC param 2, ($TC_ECPx4     / $TC_SCPx4     x=DLNo), related to Edge TO-Param 13: Wear - length 2 ($TC_DP13)                           </TD></TR>
    <TR><TD> /Tool/Compensation/edgeSCData  </TD><TD> SlTmToMaDlSc  </TD><TD> SlTmUtil::DATA_KIND_DL_SC  </TD><TD> SlTmToMaDlSc::DL_DATA_LENGTH3        </TD><TD> edge DL SC/EC param 3, ($TC_ECPx5     / $TC_SCPx5     x=DLNo), related to Edge TO-Param 14: Wear - length 2 ($TC_DP14)                           </TD></TR>
    <TR><TD> /Tool/Compensation/edgeSCData  </TD><TD> SlTmToMaDlSc  </TD><TD> SlTmUtil::DATA_KIND_DL_SC  </TD><TD> SlTmToMaDlSc::DL_DATA_RADIUS         </TD><TD> edge DL SC/EC param 4, ($TC_ECPx6     / $TC_SCPx6     x=DLNo), related to Edge TO-Param 15: Wear - radius ($TC_DP15)                             </TD></TR>
    <TR><TD> /Tool/Compensation/edgeSCData  </TD><TD> SlTmToMaDlSc  </TD><TD> SlTmUtil::DATA_KIND_DL_SC  </TD><TD> SlTmToMaDlSc::DL_DATA_CORNER_RADIUS  </TD><TD> edge DL SC/EC param 5, ($TC_ECPx7     / $TC_SCPx7     x=DLNo), related to Edge TO-Param 16: Wear - slot width b / rounding radius ($TC_DP16)     </TD></TR>
    <TR><TD> /Tool/Compensation/edgeSCData  </TD><TD> SlTmToMaDlSc  </TD><TD> SlTmUtil::DATA_KIND_DL_SC  </TD><TD> SlTmToMaDlSc::DL_DATA_SLOT_WIDTH_B   </TD><TD> edge DL SC/EC param 5, ($TC_ECPx7     / $TC_SCPx7     x=DLNo), related to Edge TO-Param 16: Wear - slot width b / rounding radius ($TC_DP16)     </TD></TR>
    <TR><TD> /Tool/Compensation/edgeSCData  </TD><TD> SlTmToMaDlSc  </TD><TD> SlTmUtil::DATA_KIND_DL_SC  </TD><TD> SlTmToMaDlSc::DL_DATA_LENGTH4        </TD><TD> edge DL SC/EC param 6, ($TC_ECPx8     / $TC_SCPx8     x=DLNo), related to Edge TO-Param 17: Wear - proj. length k ($TC_DP17)                     </TD></TR>
    <TR><TD> /Tool/Compensation/edgeSCData  </TD><TD> SlTmToMaDlSc  </TD><TD> SlTmUtil::DATA_KIND_DL_SC  </TD><TD> SlTmToMaDlSc::DL_DATA_LENGTH5        </TD><TD> edge DL SC/EC param 7, ($TC_ECPx9     / $TC_SCPx9     x=DLNo), related to Edge TO-Param 18: Wear - length 5 ($TC_DP18)                           </TD></TR>
    <TR><TD> /Tool/Compensation/edgeSCData  </TD><TD> SlTmToMaDlSc  </TD><TD> SlTmUtil::DATA_KIND_DL_SC  </TD><TD> SlTmToMaDlSc::DL_DATA_ANGLE1         </TD><TD> edge DL SC/EC param 8, ($TC_ECP(x+1)0 / $TC_SCP(x+1)0 x=DLNo), related to Edge TO-Param 19: Wear - angle 1 ($TC_DP19)                            </TD></TR>
    <TR><TD> /Tool/Compensation/edgeSCData  </TD><TD> SlTmToMaDlSc  </TD><TD> SlTmUtil::DATA_KIND_DL_SC  </TD><TD> SlTmToMaDlSc::DL_DATA_ANGLE2         </TD><TD> edge DL SC/EC param 9, ($TC_ECP(x+1)1 / $TC_SCP(x+1)1 x=DLNo), related to Edge TO-Param 20: Wear - angle 2 for tapered milling tools ($TC_DP20)  </TD></TR>
  </TABLE>
</TABLE>
\n
<TABLE>
  <TR><TD><b>Tool Edge: Edge-related transformed Location-dependent Coarse Total Offsets, transformed Edge DL EC Parameters </b> \n
\code
SlTmStore::rContainerColl().rContainer(containerNo).rToolColl().rTool(tNo).rEdgeColl().rEdge(edgeNo).rDlColl().rDl(dlNo).rEcTr().setVal(SlTmToMaDlEcTr::DlDataIdxEnum); 
SlTmStore::rConstContainerColl().rConstContainer(containerNo).rConstToolColl().rConstTool(tNo).rConstEdgeColl().rConstEdge(edgeNo).rConstDlColl().rConstDl(dlNo).rConstEcTr().val(SlTmToMaDlEcTr::DlDataIdxEnum); 
\endcode
          OPI / BTSS data module: number 0x47 = 71, TOET, transformed edge DL EC params, Edge-related location-dependent transformed coarse total offsets, transformed setup offsets
  </TD></TR>
  <TABLE>
    <TR><TD> OPI / BTSS item                </TD><TD> data class      </TD><TD> data kind enum                </TD><TD> data index enum                        </TD><TD> NC data                                                                                                                                                            </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeECData  </TD><TD> SlTmToMaDlEcTr  </TD><TD> SlTmUtil::DATA_KIND_DL_EC_TR  </TD><TD> SlTmToMaDlEcTr::DL_DATA_LENGTH1        </TD><TD> transformed, like edge DL SC/EC param 1, ($TC_ECPx3     / $TC_SCPx3     x=DLNo), related to Edge TO-Param 12: Wear - length 1 ($TC_DP12)                           </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeECData  </TD><TD> SlTmToMaDlEcTr  </TD><TD> SlTmUtil::DATA_KIND_DL_EC_TR  </TD><TD> SlTmToMaDlEcTr::DL_DATA_LENGTH2        </TD><TD> transformed, like edge DL SC/EC param 2, ($TC_ECPx4     / $TC_SCPx4     x=DLNo), related to Edge TO-Param 13: Wear - length 2 ($TC_DP13)                           </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeECData  </TD><TD> SlTmToMaDlEcTr  </TD><TD> SlTmUtil::DATA_KIND_DL_EC_TR  </TD><TD> SlTmToMaDlEcTr::DL_DATA_LENGTH3        </TD><TD> transformed, like edge DL SC/EC param 3, ($TC_ECPx5     / $TC_SCPx5     x=DLNo), related to Edge TO-Param 14: Wear - length 2 ($TC_DP14)                           </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeECData  </TD><TD> SlTmToMaDlEcTr  </TD><TD> SlTmUtil::DATA_KIND_DL_EC_TR  </TD><TD> SlTmToMaDlEcTr::DL_DATA_RADIUS         </TD><TD> transformed, like edge DL SC/EC param 4, ($TC_ECPx6     / $TC_SCPx6     x=DLNo), related to Edge TO-Param 15: Wear - radius ($TC_DP15)                             </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeECData  </TD><TD> SlTmToMaDlEcTr  </TD><TD> SlTmUtil::DATA_KIND_DL_EC_TR  </TD><TD> SlTmToMaDlEcTr::DL_DATA_CORNER_RADIUS  </TD><TD> transformed, like edge DL SC/EC param 5, ($TC_ECPx7     / $TC_SCPx7     x=DLNo), related to Edge TO-Param 16: Wear - slot width b / rounding radius ($TC_DP16)     </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeECData  </TD><TD> SlTmToMaDlEcTr  </TD><TD> SlTmUtil::DATA_KIND_DL_EC_TR  </TD><TD> SlTmToMaDlEcTr::DL_DATA_SLOT_WIDTH_B   </TD><TD> transformed, like edge DL SC/EC param 5, ($TC_ECPx7     / $TC_SCPx7     x=DLNo), related to Edge TO-Param 16: Wear - slot width b / rounding radius ($TC_DP16)     </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeECData  </TD><TD> SlTmToMaDlEcTr  </TD><TD> SlTmUtil::DATA_KIND_DL_EC_TR  </TD><TD> SlTmToMaDlEcTr::DL_DATA_LENGTH4        </TD><TD> transformed, like edge DL SC/EC param 6, ($TC_ECPx8     / $TC_SCPx8     x=DLNo), related to Edge TO-Param 17: Wear - proj. length k ($TC_DP17)                     </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeECData  </TD><TD> SlTmToMaDlEcTr  </TD><TD> SlTmUtil::DATA_KIND_DL_EC_TR  </TD><TD> SlTmToMaDlEcTr::DL_DATA_LENGTH5        </TD><TD> transformed, like edge DL SC/EC param 7, ($TC_ECPx9     / $TC_SCPx9     x=DLNo), related to Edge TO-Param 18: Wear - length 5 ($TC_DP18)                           </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeECData  </TD><TD> SlTmToMaDlEcTr  </TD><TD> SlTmUtil::DATA_KIND_DL_EC_TR  </TD><TD> SlTmToMaDlEcTr::DL_DATA_ANGLE1         </TD><TD> transformed, like edge DL SC/EC param 8, ($TC_ECP(x+1)0 / $TC_SCP(x+1)0 x=DLNo), related to Edge TO-Param 19: Wear - angle 1 ($TC_DP19)                            </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeECData  </TD><TD> SlTmToMaDlEcTr  </TD><TD> SlTmUtil::DATA_KIND_DL_EC_TR  </TD><TD> SlTmToMaDlEcTr::DL_DATA_ANGLE2         </TD><TD> transformed, like edge DL SC/EC param 9, ($TC_ECP(x+1)1 / $TC_SCP(x+1)1 x=DLNo), related to Edge TO-Param 20: Wear - angle 2 for tapered milling tools ($TC_DP20)  </TD></TR>
  </TABLE>
</TABLE>
\n
<TABLE>
  <TR><TD><b>Tool Edge: Edge-related transformed Location-dependent Fine Total Offsets, transformed Edge DL SC Parameters </b> \n
\code
SlTmStore::rContainerColl().rContainer(containerNo).rToolColl().rTool(tNo).rEdgeColl().rEdge(edgeNo).rDlColl().rDl(dlNo).rScTr().setVal(SlTmToMaDlScTr::DlDataIdxEnum); 
SlTmStore::rConstContainerColl().rConstContainer(containerNo).rConstToolColl().rConstTool(tNo).rConstEdgeColl().rConstEdge(edgeNo).rConstDlColl().rConstDl(dlNo).rConstScTr().val(SlTmToMaDlScTr::DlDataIdxEnum); 
\endcode
          OPI / BTSS data module: number 0x45 = 69, TOST, transformed edge DL SC params, Edge-related transformed positional fine total offsets
  </TD></TR>
  <TABLE>
    <TR><TD> OPI / BTSS item                </TD><TD> data class      </TD><TD> data kind enum                </TD><TD> data index enum                        </TD><TD> NC data                                                                                                                                                            </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeSCData  </TD><TD> SlTmToMaDlScTr  </TD><TD> SlTmUtil::DATA_KIND_DL_SC_TR  </TD><TD> SlTmToMaDlScTr::DL_DATA_LENGTH1        </TD><TD> transformed, like edge DL SC/EC param 1, ($TC_ECPx3     / $TC_SCPx3     x=DLNo), related to Edge TO-Param 12: Wear - length 1 ($TC_DP12)                           </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeSCData  </TD><TD> SlTmToMaDlScTr  </TD><TD> SlTmUtil::DATA_KIND_DL_SC_TR  </TD><TD> SlTmToMaDlScTr::DL_DATA_LENGTH2        </TD><TD> transformed, like edge DL SC/EC param 2, ($TC_ECPx4     / $TC_SCPx4     x=DLNo), related to Edge TO-Param 13: Wear - length 2 ($TC_DP13)                           </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeSCData  </TD><TD> SlTmToMaDlScTr  </TD><TD> SlTmUtil::DATA_KIND_DL_SC_TR  </TD><TD> SlTmToMaDlScTr::DL_DATA_LENGTH3        </TD><TD> transformed, like edge DL SC/EC param 3, ($TC_ECPx5     / $TC_SCPx5     x=DLNo), related to Edge TO-Param 14: Wear - length 2 ($TC_DP14)                           </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeSCData  </TD><TD> SlTmToMaDlScTr  </TD><TD> SlTmUtil::DATA_KIND_DL_SC_TR  </TD><TD> SlTmToMaDlScTr::DL_DATA_RADIUS         </TD><TD> transformed, like edge DL SC/EC param 4, ($TC_ECPx6     / $TC_SCPx6     x=DLNo), related to Edge TO-Param 15: Wear - radius ($TC_DP15)                             </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeSCData  </TD><TD> SlTmToMaDlScTr  </TD><TD> SlTmUtil::DATA_KIND_DL_SC_TR  </TD><TD> SlTmToMaDlScTr::DL_DATA_CORNER_RADIUS  </TD><TD> transformed, like edge DL SC/EC param 5, ($TC_ECPx7     / $TC_SCPx7     x=DLNo), related to Edge TO-Param 16: Wear - slot width b / rounding radius ($TC_DP16)     </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeSCData  </TD><TD> SlTmToMaDlScTr  </TD><TD> SlTmUtil::DATA_KIND_DL_SC_TR  </TD><TD> SlTmToMaDlScTr::DL_DATA_SLOT_WIDTH_B   </TD><TD> transformed, like edge DL SC/EC param 5, ($TC_ECPx7     / $TC_SCPx7     x=DLNo), related to Edge TO-Param 16: Wear - slot width b / rounding radius ($TC_DP16)     </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeSCData  </TD><TD> SlTmToMaDlScTr  </TD><TD> SlTmUtil::DATA_KIND_DL_SC_TR  </TD><TD> SlTmToMaDlScTr::DL_DATA_LENGTH4        </TD><TD> transformed, like edge DL SC/EC param 6, ($TC_ECPx8     / $TC_SCPx8     x=DLNo), related to Edge TO-Param 17: Wear - proj. length k ($TC_DP17)                     </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeSCData  </TD><TD> SlTmToMaDlScTr  </TD><TD> SlTmUtil::DATA_KIND_DL_SC_TR  </TD><TD> SlTmToMaDlScTr::DL_DATA_LENGTH5        </TD><TD> transformed, like edge DL SC/EC param 7, ($TC_ECPx9     / $TC_SCPx9     x=DLNo), related to Edge TO-Param 18: Wear - length 5 ($TC_DP18)                           </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeSCData  </TD><TD> SlTmToMaDlScTr  </TD><TD> SlTmUtil::DATA_KIND_DL_SC_TR  </TD><TD> SlTmToMaDlScTr::DL_DATA_ANGLE1         </TD><TD> transformed, like edge DL SC/EC param 8, ($TC_ECP(x+1)0 / $TC_SCP(x+1)0 x=DLNo), related to Edge TO-Param 19: Wear - angle 1 ($TC_DP19)                            </TD></TR>
    <TR><TD> /Tool/CompTransfor/edgeSCData  </TD><TD> SlTmToMaDlScTr  </TD><TD> SlTmUtil::DATA_KIND_DL_SC_TR  </TD><TD> SlTmToMaDlScTr::DL_DATA_ANGLE2         </TD><TD> transformed, like edge DL SC/EC param 9, ($TC_ECP(x+1)1 / $TC_SCP(x+1)1 x=DLNo), related to Edge TO-Param 20: Wear - angle 2 for tapered milling tools ($TC_DP20)  </TD></TR>
  </TABLE>
</TABLE>
\n
<TABLE>
  <TR><TD><b>Tool: Tool General Data</b> \n
\code
SlTmStore::rContainerColl().rContainer(containerNo).rToolColl().rTool(tNo).rData().setVal(SlTmToMaToolData::ToolDataIdxEnum); 
SlTmStore::rConstContainerColl().rConstContainer(containerNo).rConstToolColl().rConstTool(tNo).rConstData().val(SlTmToMaToolData::ToolDataIdxEnum); 
\endcode
          OPI / BTSS data module: number 0x21 = 33,  TD, tool data, Tool data, general data
  </TD></TR>
  <TABLE>
    <TR><TD> OPI / BTSS item                     </TD><TD> data class        </TD><TD> data kind enum                 </TD><TD> data index enum                                              </TD><TD> NC data                                                                  </TD></TR>
    <TR><TD> -                                   </TD><TD> SlTmToMaToolData  </TD><TD> SlTmUtil::DATA_KIND_TOOL_DATA  </TD><TD> SlTmToMaToolData::TOOL_DATA_TNO                              </TD><TD> Tool number, number (not count) of tool, tNo                             </TD></TR>
    <TR><TD> -                                   </TD><TD> SlTmToMaToolData  </TD><TD> SlTmUtil::DATA_KIND_TOOL_DATA  </TD><TD> SlTmToMaToolData::TOOL_DATA_IS_AFFECTED_BY_CURR_CHAN         </TD><TD> depends on context: Tool is affected by curr channel data                </TD></TR>
    <TR><TD> /Tool/Data/toolIdent                </TD><TD> SlTmToMaToolData  </TD><TD> SlTmUtil::DATA_KIND_TOOL_DATA  </TD><TD> SlTmToMaToolData::TOOL_DATA_IDENT                            </TD><TD> toolIdent                               ($TC_TP2)                        </TD></TR>
    <TR><TD> /Tool/Data/duploNo                  </TD><TD> SlTmToMaToolData  </TD><TD> SlTmUtil::DATA_KIND_TOOL_DATA  </TD><TD> SlTmToMaToolData::TOOL_DATA_DUPLO                            </TD><TD> duploNo                                 ($TC_TP1)                        </TD></TR>
    <TR><TD> /Tool/Data/toolsize_left            </TD><TD> SlTmToMaToolData  </TD><TD> SlTmUtil::DATA_KIND_TOOL_DATA  </TD><TD> SlTmToMaToolData::TOOL_DATA_SIZE_LEFT                        </TD><TD> toolsize_left                           ($TC_TP3)                        </TD></TR>
    <TR><TD> /Tool/Data/toolsize_right           </TD><TD> SlTmToMaToolData  </TD><TD> SlTmUtil::DATA_KIND_TOOL_DATA  </TD><TD> SlTmToMaToolData::TOOL_DATA_SIZE_RIGHT                       </TD><TD> toolsize_right                          ($TC_TP4)                        </TD></TR>
    <TR><TD> /Tool/Data/toolsize_upper           </TD><TD> SlTmToMaToolData  </TD><TD> SlTmUtil::DATA_KIND_TOOL_DATA  </TD><TD> SlTmToMaToolData::TOOL_DATA_SIZE_UPPER                       </TD><TD> toolsize_upper                          ($TC_TP5)                        </TD></TR>
    <TR><TD> /Tool/Data/toolsize_down            </TD><TD> SlTmToMaToolData  </TD><TD> SlTmUtil::DATA_KIND_TOOL_DATA  </TD><TD> SlTmToMaToolData::TOOL_DATA_SIZE_DOWN                        </TD><TD> toolsize_down                           ($TC_TP6)                        </TD></TR>
    <TR><TD> /Tool/Data/toolplace_spec           </TD><TD> SlTmToMaToolData  </TD><TD> SlTmUtil::DATA_KIND_TOOL_DATA  </TD><TD> SlTmToMaToolData::TOOL_DATA_PLACE_SPEC                       </TD><TD> toolplace_spec                          ($TC_TP7)                        </TD></TR>
    <TR><TD> /Tool/Data/toolState                </TD><TD> SlTmToMaToolData  </TD><TD> SlTmUtil::DATA_KIND_TOOL_DATA  </TD><TD> SlTmToMaToolData::TOOL_DATA_STATE                            </TD><TD> toolState 15 bit before nckVersion 780000.0   ($TC_TP8)                  </TD></TR>
    <TR><TD> /Tool/Data/toolStateL               </TD><TD> SlTmToMaToolData  </TD><TD> SlTmUtil::DATA_KIND_TOOL_DATA  </TD><TD> SlTmToMaToolData::TOOL_DATA_STATE                            </TD><TD> toolState 32 bit since  nckVersion 780000.0   ($TC_TP8)                  </TD></TR>
    <TR><TD> /Tool/Data/toolMon                  </TD><TD> SlTmToMaToolData  </TD><TD> SlTmUtil::DATA_KIND_TOOL_DATA  </TD><TD> SlTmToMaToolData::TOOL_DATA_MON                              </TD><TD> toolMon                                 ($TC_TP9)                        </TD></TR>
    <TR><TD> /Tool/Data/toolSearch               </TD><TD> SlTmToMaToolData  </TD><TD> SlTmUtil::DATA_KIND_TOOL_DATA  </TD><TD> SlTmToMaToolData::TOOL_DATA_SEARCH                           </TD><TD> toolSearch                              ($TC_TP10)                       </TD></TR>
    <TR><TD> /Tool/Data/toolInfo                 </TD><TD> SlTmToMaToolData  </TD><TD> SlTmUtil::DATA_KIND_TOOL_DATA  </TD><TD> SlTmToMaToolData::TOOL_DATA_INFO                             </TD><TD> toolInfo                                ($TC_TP11)                       </TD></TR>
    <TR><TD> /Tool/Data/toolInMag                </TD><TD> SlTmToMaToolData  </TD><TD> SlTmUtil::DATA_KIND_TOOL_DATA  </TD><TD> SlTmToMaToolData::TOOL_DATA_INMAG                            </TD><TD> toolInMag                               ($A_TOOLMN)                      </TD></TR>
    <TR><TD> /Tool/Data/toolInPlace              </TD><TD> SlTmToMaToolData  </TD><TD> SlTmUtil::DATA_KIND_TOOL_DATA  </TD><TD> SlTmToMaToolData::TOOL_DATA_INPLACE                          </TD><TD> toolInPlace                             ($A_TOOLMLN)                     </TD></TR>
    <TR><TD> /Tool/Data/numCuttEdges             </TD><TD> SlTmToMaToolData  </TD><TD> SlTmUtil::DATA_KIND_TOOL_DATA  </TD><TD> SlTmToMaToolData::TOOL_DATA_TDNUMCUTTEDGES                   </TD><TD> numCuttEdges from BTSS data module TD   ($P_TOOLND)                      </TD></TR>
    <TR><TD> /Tool/Data/adaptNo                  </TD><TD> SlTmToMaToolData  </TD><TD> SlTmUtil::DATA_KIND_TOOL_DATA  </TD><TD> SlTmToMaToolData::TOOL_DATA_ADAPTNO                          </TD><TD> adaptNo                                 (derived from $TC_MPP8)          </TD></TR>
    <TR><TD> /Tool/Data/adaptNoOnMultitool       </TD><TD> SlTmToMaToolData  </TD><TD> SlTmUtil::DATA_KIND_TOOL_DATA  </TD><TD> SlTmToMaToolData::TOOL_DATA_MT_ADAPTNO                       </TD><TD> adaptNoOnMultitool                      ($A_TOOLMTADAPT)                 </TD></TR>
    <TR><TD> /Tool/Data/toolMyMag                </TD><TD> SlTmToMaToolData  </TD><TD> SlTmUtil::DATA_KIND_TOOL_DATA  </TD><TD> SlTmToMaToolData::TOOL_DATA_MYMAG                            </TD><TD> toolMyMag                               ($A_MYMN)                        </TD></TR>
    <TR><TD> /Tool/Data/toolMyPlace              </TD><TD> SlTmToMaToolData  </TD><TD> SlTmUtil::DATA_KIND_TOOL_DATA  </TD><TD> SlTmToMaToolData::TOOL_DATA_MYPLACE                          </TD><TD> toolMyPlace                             ($A_MYMLN)                       </TD></TR>
    <TR><TD> -                                   </TD><TD> SlTmToMaToolData  </TD><TD> SlTmUtil::DATA_KIND_TOOL_DATA  </TD><TD> SlTmToMaToolData::TOOL_DATA_ALARM_IS_EXTENDED                </TD><TD> alarm is extend = true (Automotive PLC only)                             </TD></TR>
    <TR><TD> -                                   </TD><TD> SlTmToMaToolData  </TD><TD> SlTmUtil::DATA_KIND_TOOL_DATA  </TD><TD> SlTmToMaToolData::TOOL_DATA_ALARM_LIMIT                      </TD><TD> alarm limit is reached = true (Automotive PLC only)                      </TD></TR>
    <TR><TD> -                                   </TD><TD> SlTmToMaToolData  </TD><TD> SlTmUtil::DATA_KIND_TOOL_DATA  </TD><TD> SlTmToMaToolData::TOOL_DATA_EXT_ALARM_LIMIT                  </TD><TD> extended alarm limit is reached = true (Automotive PLC only)             </TD></TR>
    <TR><TD> /Tool/Data/toolProtAreaFile         </TD><TD> SlTmToMaToolData  </TD><TD> SlTmUtil::DATA_KIND_TOOL_DATA  </TD><TD> SlTmToMaToolData::TOOL_DATA_PROT_AREA_FILE                   </TD><TD> toolProtAreaFile                        ($TC_TP_PROTA)                   </TD></TR>
    <TR><TD> /Tool/Data/toolMaxVelo              </TD><TD> SlTmToMaToolData  </TD><TD> SlTmUtil::DATA_KIND_TOOL_DATA  </TD><TD> SlTmToMaToolData::TOOL_DATA_MAX_VELO                         </TD><TD> toolMaxVelo                             ($TC_TP_MAX_VELO)                </TD></TR>
    <TR><TD> /Tool/Data/toolMaxAcc               </TD><TD> SlTmToMaToolData  </TD><TD> SlTmUtil::DATA_KIND_TOOL_DATA  </TD><TD> SlTmToMaToolData::TOOL_DATA_MAX_ACC                          </TD><TD> toolMaxAcc                              ($TC_TP_MAX_ACC)                 </TD></TR>
    <TR><TD> /Tool/Data/toolInMultitool          </TD><TD> SlTmToMaToolData  </TD><TD> SlTmUtil::DATA_KIND_TOOL_DATA  </TD><TD> SlTmToMaToolData::TOOL_DATA_IN_MULTITOOL                     </TD><TD> toolInMultitool                         ($A_TOOLMTN)                     </TD></TR>
    <TR><TD> /Tool/Data/toolInMultitoolPlace     </TD><TD> SlTmToMaToolData  </TD><TD> SlTmUtil::DATA_KIND_TOOL_DATA  </TD><TD> SlTmToMaToolData::TOOL_DATA_IN_MULTITOOL_PLACE               </TD><TD> toolInMultitoolPlace                    ($A_TOOLMTLN)                    </TD></TR>
    <TR><TD> /Tool/Data/toolMyMultitool          </TD><TD> SlTmToMaToolData  </TD><TD> SlTmUtil::DATA_KIND_TOOL_DATA  </TD><TD> SlTmToMaToolData::TOOL_DATA_MY_MULTITOOL                     </TD><TD> toolMyMultitool                         ($A_MYMTN)                       </TD></TR>
    <TR><TD> /Tool/Data/toolMyMultitoolPlace     </TD><TD> SlTmToMaToolData  </TD><TD> SlTmUtil::DATA_KIND_TOOL_DATA  </TD><TD> SlTmToMaToolData::TOOL_DATA_MY_MULTITOOL_PLACE               </TD><TD> toolMyMultitoolPlace                    ($A_MYMTLN)                      </TD></TR>
    <!-- not supported yet                                                                                                                                                                  
    not supported yet -->
  </TABLE>
</TABLE>
\n
<TABLE>
  <TR><TD><b>Tool: Tool Grinding Data</b> \n
\code
SlTmStore::rContainerColl().rContainer(containerNo).rToolColl().rTool(tNo).rGrind().setVal(SlTmToMaToolGrind::ToolGrindIdxEnum); 
SlTmStore::rConstContainerColl().rConstContainer(containerNo).rConstToolColl().rConstTool(tNo).rConstGrind().val(SlTmToMaToolGrind::ToolGrindIdxEnum); 
\endcode
          OPI / BTSS data module: number 0x23 = 35, TG, tool grinding params, Tool data, grinding-specific data
  </TD></TR>
  <TABLE>
    <TR><TD> OPI / BTSS item                 </TD><TD> data class         </TD><TD> data kind enum                  </TD><TD> data index enum                            </TD><TD> NC data                                                                                    </TD></TR>
    <TR><TD> /Tool/GrindingData/spinNoDress  </TD><TD> SlTmToMaToolGrind  </TD><TD> SlTmUtil::DATA_KIND_TOOL_GRIND  </TD><TD> SlTmToMaToolGrind::TOOL_GRIND_SPINNODRESS  </TD><TD> Tool Grind-Param  1: spinNoDress spindle number                          ($TC_TPG1)        </TD></TR>
    <TR><TD> /Tool/GrindingData/conntectPar  </TD><TD> SlTmToMaToolGrind  </TD><TD> SlTmUtil::DATA_KIND_TOOL_GRIND  </TD><TD> SlTmToMaToolGrind::TOOL_GRIND_CONNECTPAR   </TD><TD> Tool Grind-Param  2: conntectPar chaining rule                           ($TC_TPG2)        </TD></TR>
    <TR><TD> /Tool/GrindingData/minToolDia   </TD><TD> SlTmToMaToolGrind  </TD><TD> SlTmUtil::DATA_KIND_TOOL_GRIND  </TD><TD> SlTmToMaToolGrind::TOOL_GRIND_MINTOOLDIA   </TD><TD> Tool Grind-Param  3: minToolDia  minimum wheel radius                    ($TC_TPG3)        </TD></TR>
    <TR><TD> /Tool/GrindingData/minToolWide  </TD><TD> SlTmToMaToolGrind  </TD><TD> SlTmUtil::DATA_KIND_TOOL_GRIND  </TD><TD> SlTmToMaToolGrind::TOOL_GRIND_MINTOOLWIDE  </TD><TD> Tool Grind-Param  4: minToolWide minimum wheel width                     ($TC_TPG4)        </TD></TR>
    <TR><TD> /Tool/GrindingData/actToolWide  </TD><TD> SlTmToMaToolGrind  </TD><TD> SlTmUtil::DATA_KIND_TOOL_GRIND  </TD><TD> SlTmToMaToolGrind::TOOL_GRIND_ACTTOOLWIDE  </TD><TD> Tool Grind-Param  5: actToolWide current wheel width                     ($TC_TPG5)        </TD></TR>
    <TR><TD> /Tool/GrindingData/maxRotSpeed  </TD><TD> SlTmToMaToolGrind  </TD><TD> SlTmUtil::DATA_KIND_TOOL_GRIND  </TD><TD> SlTmToMaToolGrind::TOOL_GRIND_MAXROTSPEED  </TD><TD> Tool Grind-Param  6: maxRotSpeed maximum speed                           ($TC_TPG6)        </TD></TR>
    <TR><TD> /Tool/GrindingData/maxTipSpeed  </TD><TD> SlTmToMaToolGrind  </TD><TD> SlTmUtil::DATA_KIND_TOOL_GRIND  </TD><TD> SlTmToMaToolGrind::TOOL_GRIND_MAXTIPSPEED  </TD><TD> Tool Grind-Param  7: maxTipSpeed maximum peripheral speed                ($TC_TPG7)        </TD></TR>
    <TR><TD> /Tool/GrindingData/inclAngle    </TD><TD> SlTmToMaToolGrind  </TD><TD> SlTmUtil::DATA_KIND_TOOL_GRIND  </TD><TD> SlTmToMaToolGrind::TOOL_GRIND_INCLANGLE    </TD><TD> Tool Grind-Param  8: inclAngle   angle of inclined wheel                 ($TC_TPG8)        </TD></TR>
    <TR><TD> /Tool/GrindingData/paramNrCCV   </TD><TD> SlTmToMaToolGrind  </TD><TD> SlTmUtil::DATA_KIND_TOOL_GRIND  </TD><TD> SlTmToMaToolGrind::TOOL_GRIND_PARAMNRCCV   </TD><TD> Tool Grind-Param  9: paramNrCCV  parameter number for radius calculation ($TC_TPG9)        </TD></TR>
    <TR><TD> /Tool/GrindingData/drsProgname  </TD><TD> SlTmToMaToolGrind  </TD><TD> SlTmUtil::DATA_KIND_TOOL_GRIND  </TD><TD> SlTmToMaToolGrind::TOOL_GRIND_DRSPROG      </TD><TD> Tool Grind-Param 10: drsProgname dressing program name                   ($TC_TPG_DRSPROG) </TD></TR>
    <TR><TD> /Tool/GrindingData/drsPath      </TD><TD> SlTmToMaToolGrind  </TD><TD> SlTmUtil::DATA_KIND_TOOL_GRIND  </TD><TD> SlTmToMaToolGrind::TOOL_GRIND_DRSPATH      </TD><TD> Tool Grind-Param 11: drsPath     dressing program path                   ($TC_TPG_DRSPATH) </TD></TR>
  </TABLE>
</TABLE>
\n
<TABLE>
  <TR><TD><b>Tool: Tool User Data (OEM Data)</b> \n
\code
SlTmStore::rContainerColl().rContainer(containerNo).rToolColl().rTool(tNo).rUser().setVal(SlTmToMaToolUser::ToolUserIdxEnum); 
SlTmStore::rConstContainerColl().rConstContainer(containerNo).rConstToolColl().rConstTool(tNo).rConstUser().val(SlTmToMaToolUser::ToolUserIdxEnum); 
\endcode
          OPI data module: number 0x24 = 36, TU, tool user params, Tool data for OEM
  </TD></TR>
  <TABLE>
    <TR><TD> OPI / BTSS item </TD><TD> data class        </TD><TD> data kind enum                </TD><TD> data index enum                </TD><TD> NC data                         </TD></TR>
    <TR><TD> /Tool/User/data </TD><TD> SlTmToMaToolUser  </TD><TD> SlTmUtil::DATA_KIND_TOOL_USER </TD><TD> SlTmToMaToolUser::TOOL_USER_1  </TD><TD> Tool User-Param 1,  ($TC_TPC1)  </TD></TR>
    <TR><TD> /Tool/User/data </TD><TD> SlTmToMaToolUser  </TD><TD> SlTmUtil::DATA_KIND_TOOL_USER </TD><TD> SlTmToMaToolUser::TOOL_USER_2  </TD><TD> Tool User-Param 2,  ($TC_TPC2)  </TD></TR>
    <TR><TD> /Tool/User/data </TD><TD> SlTmToMaToolUser  </TD><TD> SlTmUtil::DATA_KIND_TOOL_USER </TD><TD> SlTmToMaToolUser::TOOL_USER_3  </TD><TD> Tool User-Param 3,  ($TC_TPC3)  </TD></TR>
    <TR><TD> /Tool/User/data </TD><TD> SlTmToMaToolUser  </TD><TD> SlTmUtil::DATA_KIND_TOOL_USER </TD><TD> SlTmToMaToolUser::TOOL_USER_4  </TD><TD> Tool User-Param 4,  ($TC_TPC4)  </TD></TR>
    <TR><TD> /Tool/User/data </TD><TD> SlTmToMaToolUser  </TD><TD> SlTmUtil::DATA_KIND_TOOL_USER </TD><TD> SlTmToMaToolUser::TOOL_USER_5  </TD><TD> Tool User-Param 5,  ($TC_TPC5)  </TD></TR>
    <TR><TD> /Tool/User/data </TD><TD> SlTmToMaToolUser  </TD><TD> SlTmUtil::DATA_KIND_TOOL_USER </TD><TD> SlTmToMaToolUser::TOOL_USER_6  </TD><TD> Tool User-Param 6,  ($TC_TPC6)  </TD></TR>
    <TR><TD> /Tool/User/data </TD><TD> SlTmToMaToolUser  </TD><TD> SlTmUtil::DATA_KIND_TOOL_USER </TD><TD> SlTmToMaToolUser::TOOL_USER_7  </TD><TD> Tool User-Param 7,  ($TC_TPC7)  </TD></TR>
    <TR><TD> /Tool/User/data </TD><TD> SlTmToMaToolUser  </TD><TD> SlTmUtil::DATA_KIND_TOOL_USER </TD><TD> SlTmToMaToolUser::TOOL_USER_8  </TD><TD> Tool User-Param 8,  ($TC_TPC8)  </TD></TR>
    <TR><TD> /Tool/User/data </TD><TD> SlTmToMaToolUser  </TD><TD> SlTmUtil::DATA_KIND_TOOL_USER </TD><TD> SlTmToMaToolUser::TOOL_USER_9  </TD><TD> Tool User-Param 9,  ($TC_TPC9)  </TD></TR>
    <TR><TD> /Tool/User/data </TD><TD> SlTmToMaToolUser  </TD><TD> SlTmUtil::DATA_KIND_TOOL_USER </TD><TD> SlTmToMaToolUser::TOOL_USER_10 </TD><TD> Tool User-Param 10, ($TC_TPC10) </TD></TR>
    <TR><TD> /Tool/User/data </TD><TD> SlTmToMaToolUser  </TD><TD> SlTmUtil::DATA_KIND_TOOL_USER </TD><TD> SlTmToMaToolUser::TOOL_USER_11 </TD><TD> Tool User-Param 11, ($TC_TPC11) </TD></TR>
    <TR><TD> ...             </TD><TD> ...               </TD><TD> ...                           </TD><TD> ...                            </TD><TD> ...                             </TD></TR>
    <TR><TD> /Tool/User/data </TD><TD> SlTmToMaToolUser  </TD><TD> SlTmUtil::DATA_KIND_TOOL_USER </TD><TD> SlTmToMaToolUser::TOOL_USER_20 </TD><TD> Tool User-Param 20, ($TC_TPC20) </TD></TR>
    <TR><TD> ...             </TD><TD> ...               </TD><TD> ...                           </TD><TD> ...                            </TD><TD> ...                             </TD></TR>
    <TR><TD> /Tool/User/data </TD><TD> SlTmToMaToolUser  </TD><TD> SlTmUtil::DATA_KIND_TOOL_USER </TD><TD> SlTmToMaToolUser::TOOL_USER_64 </TD><TD> Tool User-Param 64, ($TC_TPC64) </TD></TR>
  </TABLE>
</TABLE>
\n
<TABLE>
  <TR><TD><b>Tool: Tool User Data Types (OEM Data Type)</b> \n
\code
SlTmStore::::rSys().rDeviceColl().rDevice(deviceNo).rDeviceToolUserTypes.setVal(SlTmSysDeviceToolUserTypes::SysDeviceToolUserTypesIdxEnum); 
SlTmStore::rConstSys().rConstDeviceColl().rConstDevice(deviceNo).rConstDeviceToolUserTypes.val(SlTmSysDeviceToolUserTypes::SysDeviceToolUserTypesIdxEnum); 
\endcode
          OPI data module: $MN_MM_TYPE_CC_TDA_PARAM[idx], type of tool user params, Types of Tool data for OEM
  </TD></TR>
  <TABLE>
    <TR><TD> OPI / BTSS item    </TD><TD> data class                  </TD><TD> data kind enum                             </TD><TD> data index enum                                      </TD><TD> NC data                                                  </TD></TR>
    <TR><TD> /Tool/User/dataStr </TD><TD> SlTmSysDeviceToolUserTypes  </TD><TD> SlTmUtil::DATA_KIND_DEVICE_TOOL_USER_TYPES </TD><TD> SlTmSysDeviceToolUserTypes::SYSDEV_TYPE_TOOL_USER_1  </TD><TD> Type of Tool User-Param 1,  $MN_MM_TYPE_CC_TDA_PARAM[0]  </TD></TR>
    <TR><TD> /Tool/User/dataStr </TD><TD> SlTmSysDeviceToolUserTypes  </TD><TD> SlTmUtil::DATA_KIND_DEVICE_TOOL_USER_TYPES </TD><TD> SlTmSysDeviceToolUserTypes::SYSDEV_TYPE_TOOL_USER_2  </TD><TD> Type of Tool User-Param 2,  $MN_MM_TYPE_CC_TDA_PARAM[1]  </TD></TR>
    <TR><TD> /Tool/User/dataStr </TD><TD> SlTmSysDeviceToolUserTypes  </TD><TD> SlTmUtil::DATA_KIND_DEVICE_TOOL_USER_TYPES </TD><TD> SlTmSysDeviceToolUserTypes::SYSDEV_TYPE_TOOL_USER_3  </TD><TD> Type of Tool User-Param 3,  $MN_MM_TYPE_CC_TDA_PARAM[2]  </TD></TR>
    <TR><TD> /Tool/User/dataStr </TD><TD> SlTmSysDeviceToolUserTypes  </TD><TD> SlTmUtil::DATA_KIND_DEVICE_TOOL_USER_TYPES </TD><TD> SlTmSysDeviceToolUserTypes::SYSDEV_TYPE_TOOL_USER_4  </TD><TD> Type of Tool User-Param 4,  $MN_MM_TYPE_CC_TDA_PARAM[3]  </TD></TR>
    <TR><TD> /Tool/User/dataStr </TD><TD> SlTmSysDeviceToolUserTypes  </TD><TD> SlTmUtil::DATA_KIND_DEVICE_TOOL_USER_TYPES </TD><TD> SlTmSysDeviceToolUserTypes::SYSDEV_TYPE_TOOL_USER_5  </TD><TD> Type of Tool User-Param 5,  $MN_MM_TYPE_CC_TDA_PARAM[4]  </TD></TR>
    <TR><TD> /Tool/User/dataStr </TD><TD> SlTmSysDeviceToolUserTypes  </TD><TD> SlTmUtil::DATA_KIND_DEVICE_TOOL_USER_TYPES </TD><TD> SlTmSysDeviceToolUserTypes::SYSDEV_TYPE_TOOL_USER_6  </TD><TD> Type of Tool User-Param 6,  $MN_MM_TYPE_CC_TDA_PARAM[5]  </TD></TR>
    <TR><TD> /Tool/User/dataStr </TD><TD> SlTmSysDeviceToolUserTypes  </TD><TD> SlTmUtil::DATA_KIND_DEVICE_TOOL_USER_TYPES </TD><TD> SlTmSysDeviceToolUserTypes::SYSDEV_TYPE_TOOL_USER_7  </TD><TD> Type of Tool User-Param 7,  $MN_MM_TYPE_CC_TDA_PARAM[6]  </TD></TR>
    <TR><TD> /Tool/User/dataStr </TD><TD> SlTmSysDeviceToolUserTypes  </TD><TD> SlTmUtil::DATA_KIND_DEVICE_TOOL_USER_TYPES </TD><TD> SlTmSysDeviceToolUserTypes::SYSDEV_TYPE_TOOL_USER_8  </TD><TD> Type of Tool User-Param 8,  $MN_MM_TYPE_CC_TDA_PARAM[7]  </TD></TR>
    <TR><TD> /Tool/User/dataStr </TD><TD> SlTmSysDeviceToolUserTypes  </TD><TD> SlTmUtil::DATA_KIND_DEVICE_TOOL_USER_TYPES </TD><TD> SlTmSysDeviceToolUserTypes::SYSDEV_TYPE_TOOL_USER_9  </TD><TD> Type of Tool User-Param 9,  $MN_MM_TYPE_CC_TDA_PARAM[8]  </TD></TR>
    <TR><TD> /Tool/User/dataStr </TD><TD> SlTmSysDeviceToolUserTypes  </TD><TD> SlTmUtil::DATA_KIND_DEVICE_TOOL_USER_TYPES </TD><TD> SlTmSysDeviceToolUserTypes::SYSDEV_TYPE_TOOL_USER_10 </TD><TD> Type of Tool User-Param 10, $MN_MM_TYPE_CC_TDA_PARAM[9]  </TD></TR>
    <TR><TD> /Tool/User/dataStr </TD><TD> SlTmSysDeviceToolUserTypes  </TD><TD> SlTmUtil::DATA_KIND_DEVICE_TOOL_USER_TYPES </TD><TD> SlTmSysDeviceToolUserTypes::SYSDEV_TYPE_TOOL_USER_11 </TD><TD> Type of Tool User-Param 11, $MN_MM_TYPE_CC_TDA_PARAM[10] </TD></TR>
    <TR><TD> ...                </TD><TD> ...                         </TD><TD> ...                                        </TD><TD> ...                                                  </TD><TD> ...                                                      </TD></TR>
    <TR><TD> /Tool/User/dataStr </TD><TD> SlTmSysDeviceToolUserTypes  </TD><TD> SlTmUtil::DATA_KIND_DEVICE_TOOL_USER_TYPES </TD><TD> SlTmSysDeviceToolUserTypes::SYSDEV_TYPE_TOOL_USER_20 </TD><TD> Type of Tool User-Param 20, $MN_MM_TYPE_CC_TDA_PARAM[19] </TD></TR>
    <TR><TD> ...                </TD><TD> ...                         </TD><TD> ...                                        </TD><TD> ...                                                  </TD><TD> ...                                                      </TD></TR>
    <TR><TD> /Tool/User/dataStr </TD><TD> SlTmSysDeviceToolUserTypes  </TD><TD> SlTmUtil::DATA_KIND_DEVICE_TOOL_USER_TYPES </TD><TD> SlTmSysDeviceToolUserTypes::SYSDEV_TYPE_TOOL_USER_64 </TD><TD> Type of Tool User-Param 64, $MN_MM_TYPE_CC_TDA_PARAM[63] </TD></TR>
  </TABLE>
</TABLE>
\n
<TABLE>
  <TR><TD><b>Tool: Tool Application Data (Siemens Data)</b> \n
\code
SlTmStore::rContainerColl().rContainer(containerNo).rToolColl().rTool(tNo).rAppl().setVal(SlTmToMaToolAppl::ToolApplIdxEnum); 
SlTmStore::rConstContainerColl().rConstContainer(containerNo).rConstToolColl().rConstTool(tNo).rConstAppl().val(SlTmToMaToolAppl::ToolApplIdxEnum); 
\endcode
          OPI data module: number 0x4E = 78, TAD, tool appl params,             Application-specific data
  </TD></TR>
  <TABLE>
    <TR><TD> OPI / BTSS item     </TD><TD> data class        </TD><TD> data kind enum                </TD><TD> data index enum                </TD><TD> NC data                          </TD></TR>
    <TR><TD> /Tool/Data/applData </TD><TD> SlTmToMaToolAppl  </TD><TD> SlTmUtil::DATA_KIND_TOOL_APPL </TD><TD> SlTmToMaToolAppl::TOOL_APPL_1  </TD><TD> Tool Appl-Param 1,  ($TC_TPCS1)  </TD></TR>
    <TR><TD> /Tool/Data/applData </TD><TD> SlTmToMaToolAppl  </TD><TD> SlTmUtil::DATA_KIND_TOOL_APPL </TD><TD> SlTmToMaToolAppl::TOOL_APPL_2  </TD><TD> Tool Appl-Param 2,  ($TC_TPCS2)  </TD></TR>
    <TR><TD> /Tool/Data/applData </TD><TD> SlTmToMaToolAppl  </TD><TD> SlTmUtil::DATA_KIND_TOOL_APPL </TD><TD> SlTmToMaToolAppl::TOOL_APPL_3  </TD><TD> Tool Appl-Param 3,  ($TC_TPCS3)  </TD></TR>
    <TR><TD> /Tool/Data/applData </TD><TD> SlTmToMaToolAppl  </TD><TD> SlTmUtil::DATA_KIND_TOOL_APPL </TD><TD> SlTmToMaToolAppl::TOOL_APPL_4  </TD><TD> Tool Appl-Param 4,  ($TC_TPCS4)  </TD></TR>
    <TR><TD> /Tool/Data/applData </TD><TD> SlTmToMaToolAppl  </TD><TD> SlTmUtil::DATA_KIND_TOOL_APPL </TD><TD> SlTmToMaToolAppl::TOOL_APPL_5  </TD><TD> Tool Appl-Param 5,  ($TC_TPCS5)  </TD></TR>
    <TR><TD> /Tool/Data/applData </TD><TD> SlTmToMaToolAppl  </TD><TD> SlTmUtil::DATA_KIND_TOOL_APPL </TD><TD> SlTmToMaToolAppl::TOOL_APPL_6  </TD><TD> Tool Appl-Param 6,  ($TC_TPCS6)  </TD></TR>
    <TR><TD> /Tool/Data/applData </TD><TD> SlTmToMaToolAppl  </TD><TD> SlTmUtil::DATA_KIND_TOOL_APPL </TD><TD> SlTmToMaToolAppl::TOOL_APPL_7  </TD><TD> Tool Appl-Param 7,  ($TC_TPCS7)  </TD></TR>
    <TR><TD> /Tool/Data/applData </TD><TD> SlTmToMaToolAppl  </TD><TD> SlTmUtil::DATA_KIND_TOOL_APPL </TD><TD> SlTmToMaToolAppl::TOOL_APPL_8  </TD><TD> Tool Appl-Param 8,  ($TC_TPCS8)  </TD></TR>
    <TR><TD> /Tool/Data/applData </TD><TD> SlTmToMaToolAppl  </TD><TD> SlTmUtil::DATA_KIND_TOOL_APPL </TD><TD> SlTmToMaToolAppl::TOOL_APPL_9  </TD><TD> Tool Appl-Param 9,  ($TC_TPCS9)  </TD></TR>
    <TR><TD> /Tool/Data/applData </TD><TD> SlTmToMaToolAppl  </TD><TD> SlTmUtil::DATA_KIND_TOOL_APPL </TD><TD> SlTmToMaToolAppl::TOOL_APPL_10 </TD><TD> Tool Appl-Param 10, ($TC_TPCS10) </TD></TR>
  </TABLE>
</TABLE>
\n
<TABLE>
  <TR><TD><b>Adapter: Magazine Place Adapter Data</b> \n
\code
SlTmStore::rContainerColl().rContainer(containerNo).rAdaptColl().rAdaptData(adaptNo).setVal(SlTmToMaAdaptData::AdaptDataIdxEnum); 
SlTmStore::rConstContainerColl().rConstContainer(containerNo).rConstAdaptColl().rConstAdaptData(adaptNo).val(SlTmToMaAdaptData::AdaptDataIdxEnum); 
\endcode
          OPI / BTSS data module: number 0x48 = 72,  AD, (magazine place) adapter params, Adapter data
  </TD></TR>
  <TABLE>
    <TR><TD> OPI / BTSS item          </TD><TD> data class         </TD><TD> data kind enum                  </TD><TD> data index enum                      </TD><TD> NC data                                     </TD></TR>
    <TR><TD> /Tool/Adapter/adaptData  </TD><TD> SlTmToMaAdaptData  </TD><TD> SlTmUtil::DATA_KIND_ADAPT_DATA  </TD><TD> SlTmToMaAdaptData::ADAPT_DATA_L1     </TD><TD> Adapter param 1: length 1, ($TC_ADPT1)      </TD></TR>
    <TR><TD> /Tool/Adapter/adaptData  </TD><TD> SlTmToMaAdaptData  </TD><TD> SlTmUtil::DATA_KIND_ADAPT_DATA  </TD><TD> SlTmToMaAdaptData::ADAPT_DATA_L2     </TD><TD> Adapter param 2: length 2, ($TC_ADPT2)      </TD></TR>
    <TR><TD> /Tool/Adapter/adaptData  </TD><TD> SlTmToMaAdaptData  </TD><TD> SlTmUtil::DATA_KIND_ADAPT_DATA  </TD><TD> SlTmToMaAdaptData::ADAPT_DATA_L3     </TD><TD> Adapter param 3: length 3, ($TC_ADPT3)      </TD></TR>
    <TR><TD> /Tool/Adapter/adaptData  </TD><TD> SlTmToMaAdaptData  </TD><TD> SlTmUtil::DATA_KIND_ADAPT_DATA  </TD><TD> SlTmToMaAdaptData::ADAPT_DATA_TRAFO  </TD><TD> Adapter param 4: trafo number, ($TC_ADPT4)  </TD></TR>
</TABLE>
  <TR><TD><b>Adapter: Adapter Data for magazine locaction and multitool place adapter, contains data of module AD</b> \n
\code
SlTmStore::rContainerColl().rContainer(containerNo).rAdaptUniColl().rAdaptData(adaptNo).setVal(SlTmToMaAdaptUniData::AdaptDataIdxEnum);
SlTmStore::rConstContainerColl().rConstContainer(containerNo).rConstAdaptUniColl().rConstAdaptData(adaptNo).val(SlTmToMaAdaptUniData::AdaptDataIdxEnum);
\endcode
          OPI / BTSS data module: number 0x81 = 129,  ADN, adapter params, Adapter data type 2
  </TD></TR>
  <TABLE>
    <TR><TD> OPI / BTSS item             </TD><TD> data class           </TD><TD> data kind enum                     </TD><TD> data index enum                          </TD><TD> NC data                                                  </TD></TR>
    <TR><TD> /Tool/AdapterNew/adaptType  </TD><TD> SlTmToMaAdaptUniData  </TD><TD> SlTmUtil::DATA_KIND_ADAPT_UNI_DATA  </TD><TD> SlTmToMaAdaptUniData::ADAPT_DATA_TYPE     </TD><TD> Adapter param 1: type of adapter (magazine location or multitool place), ($TC_ADPT_TYPE[N])      </TD></TR>
    <TR><TD> /Tool/AdapterNew/adapt1     </TD><TD> SlTmToMaAdaptUniData  </TD><TD> SlTmUtil::DATA_KIND_ADAPT_UNI_DATA  </TD><TD> SlTmToMaAdaptUniData::ADAPT_DATA_ADAPT_L1 </TD><TD> Adapter param 2: length 1, ($TC_ADPT1 for type 1, magazine location)         </TD></TR>
    <TR><TD> /Tool/AdapterNew/adapt2     </TD><TD> SlTmToMaAdaptUniData  </TD><TD> SlTmUtil::DATA_KIND_ADAPT_UNI_DATA  </TD><TD> SlTmToMaAdaptUniData::ADAPT_DATA_ADAPT_L2 </TD><TD> Adapter param 3: length 2, ($TC_ADPT2 for type 1, magazine location)         </TD></TR>
    <TR><TD> /Tool/AdapterNew/adapt3     </TD><TD> SlTmToMaAdaptUniData  </TD><TD> SlTmUtil::DATA_KIND_ADAPT_UNI_DATA  </TD><TD> SlTmToMaAdaptUniData::ADAPT_DATA_ADAPT_L3 </TD><TD> Adapter param 4: length 3, ($TC_ADPT3 for type 1, magazine location)         </TD></TR>
    <TR><TD> /Tool/AdapterNew/adaptt     </TD><TD> SlTmToMaAdaptUniData  </TD><TD> SlTmUtil::DATA_KIND_ADAPT_UNI_DATA  </TD><TD> SlTmToMaAdaptUniData::ADAPT_DATA_TRAFO    </TD><TD> Adapter param 5: trafo number, ($TC_ADPT4 for type 1, magazine location)     </TD></TR>
    <TR><TD> /Tool/AdapterNew/adaptOff00 </TD><TD> SlTmToMaAdaptUniData  </TD><TD> SlTmUtil::DATA_KIND_ADAPT_UNI_DATA  </TD><TD> SlTmToMaAdaptUniData::ADAPT_DATA_L1_1     </TD><TD> Adapter param 6: length1 1st component, ($TC_ADPT_OFF[N,0,0], type 2, multitool place) </TD></TR>
    <TR><TD> /Tool/AdapterNew/adaptOff01 </TD><TD> SlTmToMaAdaptUniData  </TD><TD> SlTmUtil::DATA_KIND_ADAPT_UNI_DATA  </TD><TD> SlTmToMaAdaptUniData::ADAPT_DATA_L1_2     </TD><TD> Adapter param 7: length1 2nd component, ($TC_ADPT_OFF[N,0,1], type 2, multitool place) </TD></TR>
    <TR><TD> /Tool/AdapterNew/adaptOff02 </TD><TD> SlTmToMaAdaptUniData  </TD><TD> SlTmUtil::DATA_KIND_ADAPT_UNI_DATA  </TD><TD> SlTmToMaAdaptUniData::ADAPT_DATA_L1_3     </TD><TD> Adapter param 8: length1 3rd component, ($TC_ADPT_OFF[N,0,2], type 2, multitool place) </TD></TR>
    <TR><TD> /Tool/AdapterNew/adaptDir00 </TD><TD> SlTmToMaAdaptUniData  </TD><TD> SlTmUtil::DATA_KIND_ADAPT_UNI_DATA  </TD><TD> SlTmToMaAdaptUniData::ADAPT_DATA_DIR1_1   </TD><TD> Adapter param 9: direction1 1st component, ($TC_ADPT_DIR[N,0,0], type 2, multitool place)  </TD></TR>
    <TR><TD> /Tool/AdapterNew/adaptDir01 </TD><TD> SlTmToMaAdaptUniData  </TD><TD> SlTmUtil::DATA_KIND_ADAPT_UNI_DATA  </TD><TD> SlTmToMaAdaptUniData::ADAPT_DATA_DIR1_2   </TD><TD> Adapter param 10: direction1 2nd component, ($TC_ADPT_DIR[N,0,1], type 2, multitool place) </TD></TR>
    <TR><TD> /Tool/AdapterNew/adaptDir02 </TD><TD> SlTmToMaAdaptUniData  </TD><TD> SlTmUtil::DATA_KIND_ADAPT_UNI_DATA  </TD><TD> SlTmToMaAdaptUniData::ADAPT_DATA_DIR1_3   </TD><TD> Adapter param 11: direction1 3rd component, ($TC_ADPT_DIR[N,0,2], type 2, multitool place) </TD></TR>
    <TR><TD> /Tool/AdapterNew/adaptAng0  </TD><TD> SlTmToMaAdaptUniData  </TD><TD> SlTmUtil::DATA_KIND_ADAPT_UNI_DATA  </TD><TD> SlTmToMaAdaptUniData::ADAPT_DATA_ANG_1    </TD><TD> Adapter param 12: angle1, ($TC_ADPT_ANG[N,0], type 2, multitool place)         </TD></TR>
    <TR><TD> /Tool/AdapterNew/adaptAngConst0</TD><TD> SlTmToMaAdaptUniData</TD><TD>SlTmUtil::DATA_KIND_ADAPT_UNI_DATA  </TD><TD> SlTmToMaAdaptUniData::ADAPT_DATA_ANG_CONST_1</TD><TD> Adapter param 13: const angle off. 1, ($TC_ADPT_ANG_CONST[N,0], type 2, multitool place) </TD></TR>
    <TR><TD> /Tool/AdapterNew/adaptOff10 </TD><TD> SlTmToMaAdaptUniData  </TD><TD> SlTmUtil::DATA_KIND_ADAPT_UNI_DATA  </TD><TD> SlTmToMaAdaptUniData::ADAPT_DATA_L2_1     </TD><TD> Adapter param 14: length2 1st component, ($TC_ADPT_OFF[N,1,0], type 2, multitool place)    </TD></TR>
    <TR><TD> /Tool/AdapterNew/adaptOff11 </TD><TD> SlTmToMaAdaptUniData  </TD><TD> SlTmUtil::DATA_KIND_ADAPT_UNI_DATA  </TD><TD> SlTmToMaAdaptUniData::ADAPT_DATA_L2_2     </TD><TD> Adapter param 15: length2 2nd component, ($TC_ADPT_OFF[N,1,1], type 2, multitool place)    </TD></TR>
    <TR><TD> /Tool/AdapterNew/adaptOff12 </TD><TD> SlTmToMaAdaptUniData  </TD><TD> SlTmUtil::DATA_KIND_ADAPT_UNI_DATA  </TD><TD> SlTmToMaAdaptUniData::ADAPT_DATA_L2_3     </TD><TD> Adapter param 16: length2 3nd component, ($TC_ADPT_OFF[N,1,2], type 2, multitool place)    </TD></TR>
    <TR><TD> /Tool/AdapterNew/adaptDir10 </TD><TD> SlTmToMaAdaptUniData  </TD><TD> SlTmUtil::DATA_KIND_ADAPT_UNI_DATA  </TD><TD> SlTmToMaAdaptUniData::ADAPT_DATA_DIR2_1   </TD><TD> Adapter param 17: direction2 1st component, ($TC_ADPT_DIR[N,1,0], type 2, multitool place) </TD></TR>
    <TR><TD> /Tool/AdapterNew/adaptDir11 </TD><TD> SlTmToMaAdaptUniData  </TD><TD> SlTmUtil::DATA_KIND_ADAPT_UNI_DATA  </TD><TD> SlTmToMaAdaptUniData::ADAPT_DATA_DIR2_2   </TD><TD> Adapter param 18: direction2 2nd component, ($TC_ADPT_DIR[N,1,1], type 2, multitool place) </TD></TR>
    <TR><TD> /Tool/AdapterNew/adaptDir12 </TD><TD> SlTmToMaAdaptUniData  </TD><TD> SlTmUtil::DATA_KIND_ADAPT_UNI_DATA  </TD><TD> SlTmToMaAdaptUniData::ADAPT_DATA_DIR2_3   </TD><TD> Adapter param 19: direction2 3rd component, ($TC_ADPT_DIR[N,1,2], type 2, multitool place) </TD></TR>
    <TR><TD> /Tool/AdapterNew/adaptAng1  </TD><TD> SlTmToMaAdaptUniData  </TD><TD> SlTmUtil::DATA_KIND_ADAPT_UNI_DATA  </TD><TD> SlTmToMaAdaptUniData::ADAPT_DATA_ANG_2    </TD><TD> Adapter param 20: angle 2, ($TC_ADPT_ANG[N,1], type 2, multitool place)        </TD></TR>
    <TR><TD> /Tool/AdapterNew/adaptAngConst1</TD><TD> SlTmToMaAdaptUniData</TD><TD>SlTmUtil::DATA_KIND_ADAPT_UNI_DATA  </TD><TD> SlTmToMaAdaptUniData::ADAPT_DATA_ANG_CONST_2</TD><TD> Adapter param 21: const angle off. 2, ($TC_ADPT_ANG_CONST[N,1], type 2, multitool place) </TD></TR>
    <TR><TD> /Tool/AdapterNew/adaptOff20 </TD><TD> SlTmToMaAdaptUniData  </TD><TD> SlTmUtil::DATA_KIND_ADAPT_UNI_DATA  </TD><TD> SlTmToMaAdaptUniData::ADAPT_DATA_L3_1     </TD><TD> Adapter param 22: length3 1st component, ($TC_ADPT_OFF[N,2,0], type 2, multitool place)    </TD></TR>
    <TR><TD> /Tool/AdapterNew/adaptOff21 </TD><TD> SlTmToMaAdaptUniData  </TD><TD> SlTmUtil::DATA_KIND_ADAPT_UNI_DATA  </TD><TD> SlTmToMaAdaptUniData::ADAPT_DATA_L3_2     </TD><TD> Adapter param 23: length3 2nd component, ($TC_ADPT_OFF[N,2,1], type 2, multitool place)    </TD></TR>
    <TR><TD> /Tool/AdapterNew/adaptOff22 </TD><TD> SlTmToMaAdaptUniData  </TD><TD> SlTmUtil::DATA_KIND_ADAPT_UNI_DATA  </TD><TD> SlTmToMaAdaptUniData::ADAPT_DATA_L3_3     </TD><TD> Adapter param 24: length3 3rd component, ($TC_ADPT_OFF[N,2,2], type 2, multitool place)    </TD></TR>
    <TR><TD> /Tool/AdapterNew/adaptDir20 </TD><TD> SlTmToMaAdaptUniData  </TD><TD> SlTmUtil::DATA_KIND_ADAPT_UNI_DATA  </TD><TD> SlTmToMaAdaptUniData::ADAPT_DATA_DIR3_1   </TD><TD> Adapter param 25: direction3 1st component, ($TC_ADPT_DIR[N,2,0], type 2, multitool place) </TD></TR>
    <TR><TD> /Tool/AdapterNew/adaptDir21 </TD><TD> SlTmToMaAdaptUniData  </TD><TD> SlTmUtil::DATA_KIND_ADAPT_UNI_DATA  </TD><TD> SlTmToMaAdaptUniData::ADAPT_DATA_DIR3_2   </TD><TD> Adapter param 26: direction3 2nd component, ($TC_ADPT_DIR[N,2,1], type 2, multitool place) </TD></TR>
    <TR><TD> /Tool/AdapterNew/adaptDir22 </TD><TD> SlTmToMaAdaptUniData  </TD><TD> SlTmUtil::DATA_KIND_ADAPT_UNI_DATA  </TD><TD> SlTmToMaAdaptUniData::ADAPT_DATA_DIR3_3   </TD><TD> Adapter param 27: direction3 3rd component, ($TC_ADPT_DIR[N,2,2], type 2, multitool place) </TD></TR>
    <TR><TD> /Tool/AdapterNew/adaptAng2  </TD><TD> SlTmToMaAdaptUniData  </TD><TD> SlTmUtil::DATA_KIND_ADAPT_UNI_DATA  </TD><TD> SlTmToMaAdaptUniData::ADAPT_DATA_ANG_3    </TD><TD> Adapter param 28: angle 3, ($TC_ADPT_ANG[N,2], type 2, multitool place)        </TD></TR>
    <TR><TD> /Tool/AdapterNew/adaptAngConst2</TD><TD> SlTmToMaAdaptUniData</TD><TD>SlTmUtil::DATA_KIND_ADAPT_UNI_DATA  </TD><TD> SlTmToMaAdaptUniData::ADAPT_DATA_ANG_CONST_3</TD><TD> Adapter param 29: const angle off. 3, ($TC_ADPT_ANG_CONST[N,2], type 2, multitool place) </TD></TR>
  </TABLE>
</TABLE>
\n
<TABLE>
  <TR><TD><b>Magazine: Magazine Place Data</b> \n
\code
SlTmStore::rContainerColl().rContainer(containerNo).rMagConf().rMagColl().rMag(magNo).rPlaceColl().rPlace(placeNo).rData().setVal(SlTmToMaPlaceData::PlaceDataIdxEnum); 
SlTmStore::rConstContainerColl().rConstContainer(containerNo).rConstMagConf().rConstMagColl().rConstMag(magNo).rConstPlaceColl().rConstPlace(placeNo).rConstData().val(SlTmToMaPlaceData::PlaceDataIdxEnum); 
\endcode
          OPI / BTSS data module: number 0x28 = 40, TP, mag loc params, Magazine location data
  </TD></TR>
  <TABLE>
    <TR><TD> OPI / BTSS item            </TD><TD> data class        </TD><TD> data kind enum                  </TD><TD> data index enum                                           </TD><TD> NC data                                                                                              </TD></TR>
    <TR><TD> -                         </TD><TD> SlTmToMaPlaceData  </TD><TD> SlTmUtil::DATA_KIND_PLACE_DATA  </TD><TD> SlTmToMaPlaceData::PLACE_DATA_IS_AFFECTED_BY_CURR_PLACE   </TD><TD> depends on context: Place is affected by current-place-positions                                     </TD></TR>
    <TR><TD> /Tool/Magazine/placeData  </TD><TD> SlTmToMaPlaceData  </TD><TD> SlTmUtil::DATA_KIND_PLACE_DATA  </TD><TD> SlTmToMaPlaceData::PLACE_DATA_KIND                        </TD><TD> Location kind (read only)                                                              ($TC_MPP1)    </TD></TR>
    <TR><TD> /Tool/Magazine/placeData  </TD><TD> SlTmToMaPlaceData  </TD><TD> SlTmUtil::DATA_KIND_PLACE_DATA  </TD><TD> SlTmToMaPlaceData::PLACE_DATA_TYPE                        </TD><TD> Location type (read only)                                                              ($TC_MPP2)    </TD></TR>
    <TR><TD> /Tool/Magazine/placeData  </TD><TD> SlTmToMaPlaceData  </TD><TD> SlTmUtil::DATA_KIND_PLACE_DATA  </TD><TD> SlTmToMaPlaceData::PLACE_DATA_TNO                         </TD><TD> tNo, T-number of tool (NOT multitool) on this location (place)                                       </TD></TR>
    <TR><TD> /Tool/Magazine/placeData  </TD><TD> SlTmToMaPlaceData  </TD><TD> SlTmUtil::DATA_KIND_PLACE_DATA  </TD><TD> SlTmToMaPlaceData::PLACE_DATA_WATCHNEIGHBOUR              </TD><TD> Consider adjacent (neighbour) location on/off                                          ($TC_MPP3)    </TD></TR>
    <TR><TD> /Tool/Magazine/placeData  </TD><TD> SlTmToMaPlaceData  </TD><TD> SlTmUtil::DATA_KIND_PLACE_DATA  </TD><TD> SlTmToMaPlaceData::PLACE_DATA_STATUS                      </TD><TD> Location status                                                                        ($TC_MPP4)    </TD></TR>
    <TR><TD> /Tool/Magazine/placeData  </TD><TD> SlTmToMaPlaceData  </TD><TD> SlTmUtil::DATA_KIND_PLACE_DATA  </TD><TD> SlTmToMaPlaceData::PLACE_DATA_PHYSREF                     </TD><TD> NC internal reference to physical magazine (read only)                                               </TD></TR>
    <TR><TD> /Tool/Magazine/placeData  </TD><TD> SlTmToMaPlaceData  </TD><TD> SlTmUtil::DATA_KIND_PLACE_DATA  </TD><TD> SlTmToMaPlaceData::PLACE_DATA_TYPEINDEX                   </TD><TD> Location type index (location type numbering)                                          ($TC_MPP5) or </TD></TR>
    <TR><TD> /Tool/Magazine/placeData  </TD><TD> SlTmToMaPlaceData  </TD><TD> SlTmUtil::DATA_KIND_PLACE_DATA  </TD><TD> SlTmToMaPlaceData::PLACE_DATA_WEARGROUP                   </TD><TD> Wear group number, if location kind = 1                                                ($TC_MPP5)    </TD></TR>
    <TR><TD> /Tool/Magazine/placeData  </TD><TD> SlTmToMaPlaceData  </TD><TD> SlTmUtil::DATA_KIND_PLACE_DATA  </TD><TD> SlTmToMaPlaceData::PLACE_DATA_ADAPTNO                     </TD><TD> Number of adapter in magazine location                                                 ($TC_MPP7)    </TD></TR>
    <TR><TD> /Tool/Magazine/placeData  </TD><TD> SlTmToMaPlaceData  </TD><TD> SlTmUtil::DATA_KIND_PLACE_DATA  </TD><TD> SlTmToMaPlaceData::PLACE_DATA_RESERVED_FOR_MIXED_TNO_MTNO </TD><TD> magPlTNoReservedFor: T / MT number of tool or multitool, for which place is reserved.  ($TC_MPP66)   </TD></TR>
    <TR><TD> /Tool/Magazine/placeData  </TD><TD> SlTmToMaPlaceData  </TD><TD> SlTmUtil::DATA_KIND_PLACE_DATA  </TD><TD> SlTmToMaPlaceData::PLACE_DATA_ASSOC_SPIND_NO              </TD><TD> magPlAssocSpindNo: If spindle/toolholder: spindleNo of spindel                         ($TC_MPP_SP)  </TD></TR>
    <TR><TD> /Tool/Magazine/placeData  </TD><TD> SlTmToMaPlaceData  </TD><TD> SlTmUtil::DATA_KIND_PLACE_DATA  </TD><TD> SlTmToMaPlaceData::PLACE_DATA_IS_TNO_A_TNO_OR_MTNO        </TD><TD> magPlTNoIs: tNo/magPlTNoReservedFor is a tool or a multitool                   (similar $P_TMNOIS)   </TD></TR>
    <TR><TD> /Tool/Magazine/placeData  </TD><TD> SlTmToMaPlaceData  </TD><TD> SlTmUtil::DATA_KIND_PLACE_DATA  </TD><TD> SlTmToMaPlaceData::PLACE_DATA_MIXED_TNO_MTNO              </TD><TD> T / MT number of tool / multitool in this location                                     ($TC_MPP6)    </TD></TR>
    <TR><TD> /Tool/Magazine/placeData  </TD><TD> SlTmToMaPlaceData  </TD><TD> SlTmUtil::DATA_KIND_PLACE_DATA  </TD><TD> SlTmToMaPlaceData::PLACE_DATA_MTNO                        </TD><TD> MT number of multitool (NOT tool) in this location                                                   </TD></TR>
    <TR><TD> /Tool/Magazine/placeData  </TD><TD> SlTmToMaPlaceData  </TD><TD> SlTmUtil::DATA_KIND_PLACE_DATA  </TD><TD> SlTmToMaPlaceData::PLACE_DATA_RESERVED_FOR_TNO            </TD><TD> magPlTNoReservedFor: TNo of tool (NOT multitool),  for which place is reserved.                      </TD></TR>
    <TR><TD> /Tool/Magazine/placeData  </TD><TD> SlTmToMaPlaceData  </TD><TD> SlTmUtil::DATA_KIND_PLACE_DATA  </TD><TD> SlTmToMaPlaceData::PLACE_DATA_RESERVED_FOR_MTNO           </TD><TD> magPlTNoReservedFor: MTNo of multitool (NOT tool), for which place is reserved.                      </TD></TR>
    <!-- not supported yet 
    not supported yet -->
  </TABLE>
</TABLE>
\n
<TABLE>
  <TR><TD><b>Magazine: Magazine Place User Data (OEM Data)</b> \n
\code
SlTmStore::rContainerColl().rContainer(containerNo).rMagConf().rMagColl().rMag(magNo).rPlaceColl().rPlace(placeNo).rUser().setVal(SlTmToMaPlaceUser::PlaceUserIdxEnum); 
SlTmStore::rConstContainerColl().rConstContainer(containerNo).rConstMagConf().rConstMagColl().rConstMag(magNo).rConstPlaceColl().rConstPlace(placeNo).rConstUser().val(SlTmToMaPlaceUser::PlaceUserIdxEnum); 
\endcode
          OPI data module: number 0x3F = 63, TUP,  mag loc user params as integer, Magazine place user data in integer data type or \n
          OPI data module: number 0x61 = 97, TUPD, mag loc user params as double,  Magazine place user data in double data type. \n
          See also SlTmSysDeviceData::DEV_DATA_IDX_EXIST_MAG_AND_PLACE_USER_AND_APPL_DATA_DOUBLE_OPI and \n
          SlTmToMaContainerData::CONTAINER_DATA_EXIST_MAG_AND_PLACE_USER_AND_APPL_DATA_DOUBLE_OPI.
  </TD></TR>
  <TABLE>
    <TR><TD> OPI / BTSS item                    </TD><TD> data class         </TD><TD> data kind enum                 </TD><TD> data index enum                   </TD><TD> NC data                            </TD></TR>
    <TR><TD> /Tool/Magazine/userPlaceData       </TD><TD> SlTmToMaPlaceUser  </TD><TD> SlTmUtil::DATA_KIND_PLACE_USER </TD><TD> SlTmToMaPlaceUser::PLACE_USER_1   </TD><TD> Place User-Param 1,  ($TC_MPPC1)   </TD></TR>
    <TR><TD> /Tool/Magazine/userPlaceData       </TD><TD> SlTmToMaPlaceUser  </TD><TD> SlTmUtil::DATA_KIND_PLACE_USER </TD><TD> SlTmToMaPlaceUser::PLACE_USER_2   </TD><TD> Place User-Param 2,  ($TC_MPPC2)   </TD></TR>
    <TR><TD> /Tool/Magazine/userPlaceData       </TD><TD> SlTmToMaPlaceUser  </TD><TD> SlTmUtil::DATA_KIND_PLACE_USER </TD><TD> SlTmToMaPlaceUser::PLACE_USER_3   </TD><TD> Place User-Param 3,  ($TC_MPPC3)   </TD></TR>
    <TR><TD> /Tool/Magazine/userPlaceData       </TD><TD> SlTmToMaPlaceUser  </TD><TD> SlTmUtil::DATA_KIND_PLACE_USER </TD><TD> SlTmToMaPlaceUser::PLACE_USER_4   </TD><TD> Place User-Param 4,  ($TC_MPPC4)   </TD></TR>
    <TR><TD> /Tool/Magazine/userPlaceData       </TD><TD> SlTmToMaPlaceUser  </TD><TD> SlTmUtil::DATA_KIND_PLACE_USER </TD><TD> SlTmToMaPlaceUser::PLACE_USER_5   </TD><TD> Place User-Param 5,  ($TC_MPPC5)   </TD></TR>
    <TR><TD> /Tool/Magazine/userPlaceData       </TD><TD> SlTmToMaPlaceUser  </TD><TD> SlTmUtil::DATA_KIND_PLACE_USER </TD><TD> SlTmToMaPlaceUser::PLACE_USER_6   </TD><TD> Place User-Param 6,  ($TC_MPPC6)   </TD></TR>
    <TR><TD> /Tool/Magazine/userPlaceData       </TD><TD> SlTmToMaPlaceUser  </TD><TD> SlTmUtil::DATA_KIND_PLACE_USER </TD><TD> SlTmToMaPlaceUser::PLACE_USER_7   </TD><TD> Place User-Param 7,  ($TC_MPPC7)   </TD></TR>
    <TR><TD> /Tool/Magazine/userPlaceData       </TD><TD> SlTmToMaPlaceUser  </TD><TD> SlTmUtil::DATA_KIND_PLACE_USER </TD><TD> SlTmToMaPlaceUser::PLACE_USER_8   </TD><TD> Place User-Param 8,  ($TC_MPPC8)   </TD></TR>
    <TR><TD> /Tool/Magazine/userPlaceData       </TD><TD> SlTmToMaPlaceUser  </TD><TD> SlTmUtil::DATA_KIND_PLACE_USER </TD><TD> SlTmToMaPlaceUser::PLACE_USER_9   </TD><TD> Place User-Param 9,  ($TC_MPPC9)   </TD></TR>
    <TR><TD> /Tool/Magazine/userPlaceData       </TD><TD> SlTmToMaPlaceUser  </TD><TD> SlTmUtil::DATA_KIND_PLACE_USER </TD><TD> SlTmToMaPlaceUser::PLACE_USER_10  </TD><TD> Place User-Param 10, ($TC_MPPC10)  </TD></TR>
    <TR><TD> ...                                </TD><TD> ...                </TD><TD> ...                            </TD><TD> ...                               </TD><TD> ...                                </TD></TR>
    <TR><TD> /Tool/Magazine/userPlaceData       </TD><TD> SlTmToMaPlaceUser  </TD><TD> SlTmUtil::DATA_KIND_PLACE_USER </TD><TD> SlTmToMaPlaceUser::PLACE_USER_64  </TD><TD> Place User-Param 64, ($TC_MPPC64)  </TD></TR>
    <TR><TD> or </TD><TD></TD><TD></TD><TD></TD><TD></TD></TR>
    <TR><TD> /Tool/Magazine/userPlaceDataDouble </TD><TD> SlTmToMaPlaceUser  </TD><TD> SlTmUtil::DATA_KIND_PLACE_USER </TD><TD> SlTmToMaPlaceUser::PLACE_USER_1   </TD><TD> Place User-Param 1,  ($TC_MPPC1)   </TD></TR>
    <TR><TD> /Tool/Magazine/userPlaceDataDouble </TD><TD> SlTmToMaPlaceUser  </TD><TD> SlTmUtil::DATA_KIND_PLACE_USER </TD><TD> SlTmToMaPlaceUser::PLACE_USER_2   </TD><TD> Place User-Param 2,  ($TC_MPPC2)   </TD></TR>
    <TR><TD> /Tool/Magazine/userPlaceDataDouble </TD><TD> SlTmToMaPlaceUser  </TD><TD> SlTmUtil::DATA_KIND_PLACE_USER </TD><TD> SlTmToMaPlaceUser::PLACE_USER_3   </TD><TD> Place User-Param 3,  ($TC_MPPC3)   </TD></TR>
    <TR><TD> /Tool/Magazine/userPlaceDataDouble </TD><TD> SlTmToMaPlaceUser  </TD><TD> SlTmUtil::DATA_KIND_PLACE_USER </TD><TD> SlTmToMaPlaceUser::PLACE_USER_4   </TD><TD> Place User-Param 4,  ($TC_MPPC4)   </TD></TR>
    <TR><TD> /Tool/Magazine/userPlaceDataDouble </TD><TD> SlTmToMaPlaceUser  </TD><TD> SlTmUtil::DATA_KIND_PLACE_USER </TD><TD> SlTmToMaPlaceUser::PLACE_USER_5   </TD><TD> Place User-Param 5,  ($TC_MPPC5)   </TD></TR>
    <TR><TD> /Tool/Magazine/userPlaceDataDouble </TD><TD> SlTmToMaPlaceUser  </TD><TD> SlTmUtil::DATA_KIND_PLACE_USER </TD><TD> SlTmToMaPlaceUser::PLACE_USER_6   </TD><TD> Place User-Param 6,  ($TC_MPPC6)   </TD></TR>
    <TR><TD> /Tool/Magazine/userPlaceDataDouble </TD><TD> SlTmToMaPlaceUser  </TD><TD> SlTmUtil::DATA_KIND_PLACE_USER </TD><TD> SlTmToMaPlaceUser::PLACE_USER_7   </TD><TD> Place User-Param 7,  ($TC_MPPC7)   </TD></TR>
    <TR><TD> /Tool/Magazine/userPlaceDataDouble </TD><TD> SlTmToMaPlaceUser  </TD><TD> SlTmUtil::DATA_KIND_PLACE_USER </TD><TD> SlTmToMaPlaceUser::PLACE_USER_8   </TD><TD> Place User-Param 8,  ($TC_MPPC8)   </TD></TR>
    <TR><TD> /Tool/Magazine/userPlaceDataDouble </TD><TD> SlTmToMaPlaceUser  </TD><TD> SlTmUtil::DATA_KIND_PLACE_USER </TD><TD> SlTmToMaPlaceUser::PLACE_USER_9   </TD><TD> Place User-Param 9,  ($TC_MPPC9)   </TD></TR>
    <TR><TD> /Tool/Magazine/userPlaceDataDouble </TD><TD> SlTmToMaPlaceUser  </TD><TD> SlTmUtil::DATA_KIND_PLACE_USER </TD><TD> SlTmToMaPlaceUser::PLACE_USER_10  </TD><TD> Place User-Param 10, ($TC_MPPC10)  </TD></TR>
    <TR><TD> ...                                </TD><TD> ...                </TD><TD> ...                            </TD><TD> ...                               </TD><TD> ...                                </TD></TR>
    <TR><TD> /Tool/Magazine/userPlaceDataDouble </TD><TD> SlTmToMaPlaceUser  </TD><TD> SlTmUtil::DATA_KIND_PLACE_USER </TD><TD> SlTmToMaPlaceUser::PLACE_USER_64  </TD><TD> Place User-Param 64, ($TC_MPPC64)  </TD></TR>
  </TABLE>
</TABLE>
\n
<TABLE>
  <TR><TD><b>Magazine: Magazine Place Application Specific Data (Siemens Data)</b> \n
\code
SlTmStore::rContainerColl().rContainer(containerNo).rMagConf().rMagColl().rMag(magNo).rPlaceColl().rPlace(placeNo).rAppl().setVal(SlTmToMaPlaceAppl::PlaceApplIdxEnum); 
SlTmStore::rConstContainerColl().rConstContainer(containerNo).rConstMagConf().rConstMagColl().rConstMag(magNo).rConstPlaceColl().rConstPlace(placeNo).rConstAppl().val(SlTmToMaPlaceAppl::PlaceApplIdxEnum); 
\endcode
          OPI data module: number 0x52 = 82, TAP,  mag loc appl params as integer, Application-specific magazine location data in integer data type or \n
          OPI data module: number 0x63 = 99, TAPD, mag loc appl params as double,  Application-specific magazine location data in double data type. \n
          See also SlTmSysDeviceData::DEV_DATA_IDX_EXIST_MAG_AND_PLACE_USER_AND_APPL_DATA_DOUBLE_OPI and \n
          SlTmToMaContainerData::CONTAINER_DATA_EXIST_MAG_AND_PLACE_USER_AND_APPL_DATA_DOUBLE_OPI.
  </TD></TR>
  <TABLE>
    <TR><TD> OPI / BTSS item                    </TD><TD> data class         </TD><TD> data kind enum                 </TD><TD> data index enum                   </TD><TD> NC data                             </TD></TR>
    <TR><TD> /Tool/Magazine/applPlaceData       </TD><TD> SlTmToMaPlaceAppl  </TD><TD> SlTmUtil::DATA_KIND_PLACE_APPL </TD><TD> SlTmToMaPlaceAppl::PLACE_APPL_1   </TD><TD> Place Appl-Param 1,  ($TC_MPPCS1)   </TD></TR>
    <TR><TD> /Tool/Magazine/applPlaceData       </TD><TD> SlTmToMaPlaceAppl  </TD><TD> SlTmUtil::DATA_KIND_PLACE_APPL </TD><TD> SlTmToMaPlaceAppl::PLACE_APPL_2   </TD><TD> Place Appl-Param 2,  ($TC_MPPCS2)   </TD></TR>
    <TR><TD> /Tool/Magazine/applPlaceData       </TD><TD> SlTmToMaPlaceAppl  </TD><TD> SlTmUtil::DATA_KIND_PLACE_APPL </TD><TD> SlTmToMaPlaceAppl::PLACE_APPL_3   </TD><TD> Place Appl-Param 3,  ($TC_MPPCS3)   </TD></TR>
    <TR><TD> /Tool/Magazine/applPlaceData       </TD><TD> SlTmToMaPlaceAppl  </TD><TD> SlTmUtil::DATA_KIND_PLACE_APPL </TD><TD> SlTmToMaPlaceAppl::PLACE_APPL_4   </TD><TD> Place Appl-Param 4,  ($TC_MPPCS4)   </TD></TR>
    <TR><TD> /Tool/Magazine/applPlaceData       </TD><TD> SlTmToMaPlaceAppl  </TD><TD> SlTmUtil::DATA_KIND_PLACE_APPL </TD><TD> SlTmToMaPlaceAppl::PLACE_APPL_5   </TD><TD> Place Appl-Param 5,  ($TC_MPPCS5)   </TD></TR>
    <TR><TD> /Tool/Magazine/applPlaceData       </TD><TD> SlTmToMaPlaceAppl  </TD><TD> SlTmUtil::DATA_KIND_PLACE_APPL </TD><TD> SlTmToMaPlaceAppl::PLACE_APPL_6   </TD><TD> Place Appl-Param 6,  ($TC_MPPCS6)   </TD></TR>
    <TR><TD> /Tool/Magazine/applPlaceData       </TD><TD> SlTmToMaPlaceAppl  </TD><TD> SlTmUtil::DATA_KIND_PLACE_APPL </TD><TD> SlTmToMaPlaceAppl::PLACE_APPL_7   </TD><TD> Place Appl-Param 7,  ($TC_MPPCS7)   </TD></TR>
    <TR><TD> /Tool/Magazine/applPlaceData       </TD><TD> SlTmToMaPlaceAppl  </TD><TD> SlTmUtil::DATA_KIND_PLACE_APPL </TD><TD> SlTmToMaPlaceAppl::PLACE_APPL_8   </TD><TD> Place Appl-Param 8,  ($TC_MPPCS8)   </TD></TR>
    <TR><TD> /Tool/Magazine/applPlaceData       </TD><TD> SlTmToMaPlaceAppl  </TD><TD> SlTmUtil::DATA_KIND_PLACE_APPL </TD><TD> SlTmToMaPlaceAppl::PLACE_APPL_9   </TD><TD> Place Appl-Param 9,  ($TC_MPPCS9)   </TD></TR>
    <TR><TD> /Tool/Magazine/applPlaceData       </TD><TD> SlTmToMaPlaceAppl  </TD><TD> SlTmUtil::DATA_KIND_PLACE_APPL </TD><TD> SlTmToMaPlaceAppl::PLACE_APPL_10  </TD><TD> Place Appl-Param 10, ($TC_MPPCS10)  </TD></TR>
    <TR><TD> or </TD><TD></TD><TD></TD><TD></TD><TD></TD></TR>
    <TR><TD> /Tool/Magazine/applPlaceDataDouble </TD><TD> SlTmToMaPlaceAppl  </TD><TD> SlTmUtil::DATA_KIND_PLACE_APPL </TD><TD> SlTmToMaPlaceAppl::PLACE_APPL_1   </TD><TD> Place Appl-Param 1,  ($TC_MPPCS1)   </TD></TR>
    <TR><TD> /Tool/Magazine/applPlaceDataDouble </TD><TD> SlTmToMaPlaceAppl  </TD><TD> SlTmUtil::DATA_KIND_PLACE_APPL </TD><TD> SlTmToMaPlaceAppl::PLACE_APPL_2   </TD><TD> Place Appl-Param 2,  ($TC_MPPCS2)   </TD></TR>
    <TR><TD> /Tool/Magazine/applPlaceDataDouble </TD><TD> SlTmToMaPlaceAppl  </TD><TD> SlTmUtil::DATA_KIND_PLACE_APPL </TD><TD> SlTmToMaPlaceAppl::PLACE_APPL_3   </TD><TD> Place Appl-Param 3,  ($TC_MPPCS3)   </TD></TR>
    <TR><TD> /Tool/Magazine/applPlaceDataDouble </TD><TD> SlTmToMaPlaceAppl  </TD><TD> SlTmUtil::DATA_KIND_PLACE_APPL </TD><TD> SlTmToMaPlaceAppl::PLACE_APPL_4   </TD><TD> Place Appl-Param 4,  ($TC_MPPCS4)   </TD></TR>
    <TR><TD> /Tool/Magazine/applPlaceDataDouble </TD><TD> SlTmToMaPlaceAppl  </TD><TD> SlTmUtil::DATA_KIND_PLACE_APPL </TD><TD> SlTmToMaPlaceAppl::PLACE_APPL_5   </TD><TD> Place Appl-Param 5,  ($TC_MPPCS5)   </TD></TR>
    <TR><TD> /Tool/Magazine/applPlaceDataDouble </TD><TD> SlTmToMaPlaceAppl  </TD><TD> SlTmUtil::DATA_KIND_PLACE_APPL </TD><TD> SlTmToMaPlaceAppl::PLACE_APPL_6   </TD><TD> Place Appl-Param 6,  ($TC_MPPCS6)   </TD></TR>
    <TR><TD> /Tool/Magazine/applPlaceDataDouble </TD><TD> SlTmToMaPlaceAppl  </TD><TD> SlTmUtil::DATA_KIND_PLACE_APPL </TD><TD> SlTmToMaPlaceAppl::PLACE_APPL_7   </TD><TD> Place Appl-Param 7,  ($TC_MPPCS7)   </TD></TR>
    <TR><TD> /Tool/Magazine/applPlaceDataDouble </TD><TD> SlTmToMaPlaceAppl  </TD><TD> SlTmUtil::DATA_KIND_PLACE_APPL </TD><TD> SlTmToMaPlaceAppl::PLACE_APPL_8   </TD><TD> Place Appl-Param 8,  ($TC_MPPCS8)   </TD></TR>
    <TR><TD> /Tool/Magazine/applPlaceDataDouble </TD><TD> SlTmToMaPlaceAppl  </TD><TD> SlTmUtil::DATA_KIND_PLACE_APPL </TD><TD> SlTmToMaPlaceAppl::PLACE_APPL_9   </TD><TD> Place Appl-Param 9,  ($TC_MPPCS9)   </TD></TR>
    <TR><TD> /Tool/Magazine/applPlaceDataDouble </TD><TD> SlTmToMaPlaceAppl  </TD><TD> SlTmUtil::DATA_KIND_PLACE_APPL </TD><TD> SlTmToMaPlaceAppl::PLACE_APPL_10  </TD><TD> Place Appl-Param 10, ($TC_MPPCS10)  </TD></TR>
  </TABLE>
</TABLE>
\n
<TABLE>
  <TR><TD><b>Magazine: Magazine General Data</b> \n
          \n
          For change notifications, i.e. for SlTmToMaMagData::MAG_DATA_STATE and SlTmToMaMagData::MAG_DATA_ACTPLACE, \n
          use ::SlTmMassDataToolMagListChangedData::m_ListMagazineCollMap and ::SlTmMassDataToolMagListChangedData::m_ListCurrPlaceCollVec \n
          when SlTmQCmd::signalNotifySubscribeToolMagList() arrives. \n
          Signal must be ordered by SlTmQCmd::subscribeToolMagList(), \n
          where pointer of a client owned object of type SlTmMassDataToolMagListChangedData is given to a SlTmQCmd class object. \n
          Use SlTmCmd::subscribeToolMagList() with SlTmCmdCallBackI::onNotifySubscribeToolMagList() analogical. 
          \n
\code
SlTmStore::rContainerColl().rContainer(containerNo).rMagConf().rMagColl().rMag(magNo).rData().setVal(SlTmToMaMagData::MagDataIdxEnum); 
SlTmStore::rConstContainerColl().rConstContainer(containerNo).rConstMagConf().rConstMagColl().rConstMag(magNo).rConstData().val(SlTmToMaMagData::MagDataIdxEnum); 
\endcode
          OPI / BTSS data module: number 0x27 = 39, TM, mag data, Magazine data, general data \n
  </TD></TR>
  <TABLE>
    <TR><TD> OPI / BTSS item                                     </TD><TD> data class       </TD><TD> data kind enum                </TD><TD> data index enum                                      </TD><TD> NC data                                         </TD></TR>
    <TR><TD> (/Tool/MagazineDescription/magNo)                   </TD><TD> SlTmToMaMagData  </TD><TD> SlTmUtil::DATA_KIND_MAG_DATA  </TD><TD> SlTmToMaMagData::MAG_DATA_MAG_NO                     </TD><TD> Number (not count of) Magazine                  </TD></TR>
    <TR><TD> /Tool/MagazineDescription/magIdent                  </TD><TD> SlTmToMaMagData  </TD><TD> SlTmUtil::DATA_KIND_MAG_DATA  </TD><TD> SlTmToMaMagData::MAG_DATA_IDENT                      </TD><TD> magIdent               ($TC_MAP2)               </TD></TR>
    <TR><TD> /Tool/MagazineDescription/magKind                   </TD><TD> SlTmToMaMagData  </TD><TD> SlTmUtil::DATA_KIND_MAG_DATA  </TD><TD> SlTmToMaMagData::MAG_DATA_KIND                       </TD><TD> magKind                ($TC_MAP1)               </TD></TR>
    <TR><TD> /Tool/MagazineDescription/magState                  </TD><TD> SlTmToMaMagData  </TD><TD> SlTmUtil::DATA_KIND_MAG_DATA  </TD><TD> SlTmToMaMagData::MAG_DATA_STATE                      </TD><TD> magState               ($TC_MAP3)               </TD></TR>
    <TR><TD> /Tool/MagazineDescription/magLink1                  </TD><TD> SlTmToMaMagData  </TD><TD> SlTmUtil::DATA_KIND_MAG_DATA  </TD><TD> SlTmToMaMagData::MAG_DATA_LINK1                      </TD><TD> magLink1               ($TC_MAP4)               </TD></TR>
    <TR><TD> /Tool/MagazineDescription/magLink2                  </TD><TD> SlTmToMaMagData  </TD><TD> SlTmUtil::DATA_KIND_MAG_DATA  </TD><TD> SlTmToMaMagData::MAG_DATA_LINK2                      </TD><TD> magLink2               ($TC_MAP5)               </TD></TR>
    <TR><TD> /Tool/MagazineDescription/magNrPlaces               </TD><TD> SlTmToMaMagData  </TD><TD> SlTmUtil::DATA_KIND_MAG_DATA  </TD><TD> SlTmToMaMagData::MAG_DATA_NRPLACES                   </TD><TD> magNrPlaces            ($TC_MAP6 * $TC_MAP7)    </TD></TR>
    <TR><TD> /Tool/MagazineDescription/magDim                    </TD><TD> SlTmToMaMagData  </TD><TD> SlTmUtil::DATA_KIND_MAG_DATA  </TD><TD> SlTmToMaMagData::MAG_DATA_DIM                        </TD><TD> magDim                 ($TC_MAP6)               </TD></TR>
    <TR><TD> /Tool/MagazineDescription/magActPlace               </TD><TD> SlTmToMaMagData  </TD><TD> SlTmUtil::DATA_KIND_MAG_DATA  </TD><TD> SlTmToMaMagData::MAG_DATA_ACTPLACE                   </TD><TD> magActPlace            ($TC_MAP8)               </TD></TR>
    <TR><TD> /Tool/MagazineDescription/magWearCompoundNo         </TD><TD> SlTmToMaMagData  </TD><TD> SlTmUtil::DATA_KIND_MAG_DATA  </TD><TD> SlTmToMaMagData::MAG_DATA_WEARCOMPOUNDNO             </TD><TD> magWearCompoundNo      ($TC_MAP9)               </TD></TR>
    <TR><TD> /Tool/MagazineDescription/magToolSearchStrat        </TD><TD> SlTmToMaMagData  </TD><TD> SlTmUtil::DATA_KIND_MAG_DATA  </TD><TD> SlTmToMaMagData::MAG_DATA_TOOLSEARCHSTRAT            </TD><TD> magToolSearchStrat     ($TC_MAP10, Bit 0 - 7)   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/magPlaceSearchStrat       </TD><TD> SlTmToMaMagData  </TD><TD> SlTmUtil::DATA_KIND_MAG_DATA  </TD><TD> SlTmToMaMagData::MAG_DATA_PLACESEARCHSTRAT           </TD><TD> magPlaceSearchStrat    ($TC_MAP10, Bit 8 - 15)  </TD></TR>
    <TR><TD> /Tool/MagazineDescription/magDim2                   </TD><TD> SlTmToMaMagData  </TD><TD> SlTmUtil::DATA_KIND_MAG_DATA  </TD><TD> SlTmToMaMagData::MAG_DATA_DIM2                       </TD><TD> magDim2                ($TC_MAP7)               </TD></TR>
    <TR><TD> /Tool/MagazineDescription/magPlaceUserDataNumLimit  </TD><TD> SlTmToMaMagData  </TD><TD> SlTmUtil::DATA_KIND_MAG_DATA  </TD><TD> SlTmToMaMagData::MAG_DATA_PLACE_USER_DATA_NUM_LIMIT  </TD><TD> magPlaceUserDataNumLimit                        </TD></TR>
    <!-- not supported yet 
    not supported yet -->
  </TABLE>
</TABLE>
\n
<TABLE>
  <TR><TD><b>Magazine: Magazine User Data (OEM Data)</b> \n
\code
SlTmStore::rContainerColl().rContainer(containerNo).rMagConf().rMagColl().rMag(magNo).rUser().setVal(SlTmToMaMagUser::MagUserIdxEnum); 
SlTmStore::rConstContainerColl().rConstContainer(containerNo).rConstMagConf().rConstMagColl().rConstMag(magNo).rConstUser().val(SlTmToMaMagUser::MagUserIdxEnum); 
\endcode
          OPI data module: number 0x3E = 62, TUM,  mag user params as integer, Magazine user data in double data type or \n
          OPI data module: number 0x60 = 96, TUMD, mag user params as double,  Magazine user data in double data type. \n
          See also SlTmSysDeviceData::DEV_DATA_IDX_EXIST_MAG_AND_PLACE_USER_AND_APPL_DATA_DOUBLE_OPI and \n
          SlTmToMaContainerData::CONTAINER_DATA_EXIST_MAG_AND_PLACE_USER_AND_APPL_DATA_DOUBLE_OPI.
  </TD></TR>
  <TABLE>
    <TR><TD> OPI / BTSS item                          </TD><TD> data class       </TD><TD> data kind enum               </TD><TD> data index enum               </TD><TD> NC data                               </TD></TR>
    <TR><TD> /Tool/MagazineDescription/userData       </TD><TD> SlTmToMaMagUser  </TD><TD> SlTmUtil::DATA_KIND_MAG_USER </TD><TD> SlTmToMaMagUser::MAG_USER_1   </TD><TD> Magazine User-Param 1,  ($TC_MAPC1)   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/userData       </TD><TD> SlTmToMaMagUser  </TD><TD> SlTmUtil::DATA_KIND_MAG_USER </TD><TD> SlTmToMaMagUser::MAG_USER_2   </TD><TD> Magazine User-Param 2,  ($TC_MAPC2)   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/userData       </TD><TD> SlTmToMaMagUser  </TD><TD> SlTmUtil::DATA_KIND_MAG_USER </TD><TD> SlTmToMaMagUser::MAG_USER_3   </TD><TD> Magazine User-Param 3,  ($TC_MAPC3)   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/userData       </TD><TD> SlTmToMaMagUser  </TD><TD> SlTmUtil::DATA_KIND_MAG_USER </TD><TD> SlTmToMaMagUser::MAG_USER_4   </TD><TD> Magazine User-Param 4,  ($TC_MAPC4)   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/userData       </TD><TD> SlTmToMaMagUser  </TD><TD> SlTmUtil::DATA_KIND_MAG_USER </TD><TD> SlTmToMaMagUser::MAG_USER_5   </TD><TD> Magazine User-Param 5,  ($TC_MAPC5)   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/userData       </TD><TD> SlTmToMaMagUser  </TD><TD> SlTmUtil::DATA_KIND_MAG_USER </TD><TD> SlTmToMaMagUser::MAG_USER_6   </TD><TD> Magazine User-Param 6,  ($TC_MAPC6)   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/userData       </TD><TD> SlTmToMaMagUser  </TD><TD> SlTmUtil::DATA_KIND_MAG_USER </TD><TD> SlTmToMaMagUser::MAG_USER_7   </TD><TD> Magazine User-Param 7,  ($TC_MAPC7)   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/userData       </TD><TD> SlTmToMaMagUser  </TD><TD> SlTmUtil::DATA_KIND_MAG_USER </TD><TD> SlTmToMaMagUser::MAG_USER_8   </TD><TD> Magazine User-Param 8,  ($TC_MAPC8)   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/userData       </TD><TD> SlTmToMaMagUser  </TD><TD> SlTmUtil::DATA_KIND_MAG_USER </TD><TD> SlTmToMaMagUser::MAG_USER_9   </TD><TD> Magazine User-Param 9,  ($TC_MAPC9)   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/userData       </TD><TD> SlTmToMaMagUser  </TD><TD> SlTmUtil::DATA_KIND_MAG_USER </TD><TD> SlTmToMaMagUser::MAG_USER_10  </TD><TD> Magazine User-Param 10, ($TC_MAPC10)  </TD></TR>
    <TR><TD> ...                                      </TD><TD> ...              </TD><TD> ...                          </TD><TD> ...                           </TD><TD> ...                                   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/userData       </TD><TD> SlTmToMaMagUser  </TD><TD> SlTmUtil::DATA_KIND_MAG_USER </TD><TD> SlTmToMaMagUser::MAG_USER_64  </TD><TD> Magazine User-Param 64, ($TC_MAPC64)  </TD></TR>
    <TR><TD> or </TD><TD></TD><TD></TD><TD></TD><TD></TD></TR>
    <TR><TD> /Tool/MagazineDescription/userDataDouble </TD><TD> SlTmToMaMagUser  </TD><TD> SlTmUtil::DATA_KIND_MAG_USER </TD><TD> SlTmToMaMagUser::MAG_USER_1   </TD><TD> Magazine User-Param 1,  ($TC_MAPC1)   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/userDataDouble </TD><TD> SlTmToMaMagUser  </TD><TD> SlTmUtil::DATA_KIND_MAG_USER </TD><TD> SlTmToMaMagUser::MAG_USER_2   </TD><TD> Magazine User-Param 2,  ($TC_MAPC2)   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/userDataDouble </TD><TD> SlTmToMaMagUser  </TD><TD> SlTmUtil::DATA_KIND_MAG_USER </TD><TD> SlTmToMaMagUser::MAG_USER_3   </TD><TD> Magazine User-Param 3,  ($TC_MAPC3)   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/userDataDouble </TD><TD> SlTmToMaMagUser  </TD><TD> SlTmUtil::DATA_KIND_MAG_USER </TD><TD> SlTmToMaMagUser::MAG_USER_4   </TD><TD> Magazine User-Param 4,  ($TC_MAPC4)   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/userDataDouble </TD><TD> SlTmToMaMagUser  </TD><TD> SlTmUtil::DATA_KIND_MAG_USER </TD><TD> SlTmToMaMagUser::MAG_USER_5   </TD><TD> Magazine User-Param 5,  ($TC_MAPC5)   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/userDataDouble </TD><TD> SlTmToMaMagUser  </TD><TD> SlTmUtil::DATA_KIND_MAG_USER </TD><TD> SlTmToMaMagUser::MAG_USER_6   </TD><TD> Magazine User-Param 6,  ($TC_MAPC6)   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/userDataDouble </TD><TD> SlTmToMaMagUser  </TD><TD> SlTmUtil::DATA_KIND_MAG_USER </TD><TD> SlTmToMaMagUser::MAG_USER_7   </TD><TD> Magazine User-Param 7,  ($TC_MAPC7)   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/userDataDouble </TD><TD> SlTmToMaMagUser  </TD><TD> SlTmUtil::DATA_KIND_MAG_USER </TD><TD> SlTmToMaMagUser::MAG_USER_8   </TD><TD> Magazine User-Param 8,  ($TC_MAPC8)   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/userDataDouble </TD><TD> SlTmToMaMagUser  </TD><TD> SlTmUtil::DATA_KIND_MAG_USER </TD><TD> SlTmToMaMagUser::MAG_USER_9   </TD><TD> Magazine User-Param 9,  ($TC_MAPC9)   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/userDataDouble </TD><TD> SlTmToMaMagUser  </TD><TD> SlTmUtil::DATA_KIND_MAG_USER </TD><TD> SlTmToMaMagUser::MAG_USER_10  </TD><TD> Magazine User-Param 10, ($TC_MAPC10)  </TD></TR>
    <TR><TD> ...                                      </TD><TD> ...              </TD><TD> ...                          </TD><TD> ...                           </TD><TD> ...                                   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/userDataDouble </TD><TD> SlTmToMaMagUser  </TD><TD> SlTmUtil::DATA_KIND_MAG_USER </TD><TD> SlTmToMaMagUser::MAG_USER_64  </TD><TD> Magazine User-Param 64, ($TC_MAPC64)  </TD></TR>
  </TABLE>
</TABLE>
\n
<TABLE>
  <TR><TD><b>Magazine: Magazine Application Specific Data (Siemens Data)</b> \n
\code
SlTmStore::rContainerColl().rContainer(containerNo).rMagConf().rMagColl().rMag(magNo).rAppl().setVal(SlTmToMaMagAppl::MagApplIdxEnum); 
SlTmStore::rConstContainerColl().rConstContainer(containerNo).rConstMagConf().rConstMagColl().rConstMag(magNo).rConstAppl().val(SlTmToMaMagAppl::MagApplIdxEnum); 
\endcode
          OPI data module: number 0x51 = 81, TAM,  mag appl params as integer, Application-specific magazine data in integer data type or \n
          OPI data module: number 0x62 = 98, TAMD, mag appl params as double,  Application-specific magazine data in double data type. \n
          See also SlTmSysDeviceData::DEV_DATA_IDX_EXIST_MAG_AND_PLACE_USER_AND_APPL_DATA_DOUBLE_OPI and \n
          SlTmToMaContainerData::CONTAINER_DATA_EXIST_MAG_AND_PLACE_USER_AND_APPL_DATA_DOUBLE_OPI.
  </TD></TR>
  <TABLE>
    <TR><TD> OPI / BTSS item                          </TD><TD> data class       </TD><TD> data kind enum               </TD><TD> data index enum               </TD><TD> NC data                                </TD></TR>
    <TR><TD> /Tool/MagazineDescription/applData       </TD><TD> SlTmToMaMagAppl  </TD><TD> SlTmUtil::DATA_KIND_MAG_APPL </TD><TD> SlTmToMaMagAppl::MAG_APPL_1   </TD><TD> Magazine Appl-Param 1,  ($TC_MAPCS1)   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/applData       </TD><TD> SlTmToMaMagAppl  </TD><TD> SlTmUtil::DATA_KIND_MAG_APPL </TD><TD> SlTmToMaMagAppl::MAG_APPL_2   </TD><TD> Magazine Appl-Param 2,  ($TC_MAPCS2)   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/applData       </TD><TD> SlTmToMaMagAppl  </TD><TD> SlTmUtil::DATA_KIND_MAG_APPL </TD><TD> SlTmToMaMagAppl::MAG_APPL_3   </TD><TD> Magazine Appl-Param 3,  ($TC_MAPCS3)   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/applData       </TD><TD> SlTmToMaMagAppl  </TD><TD> SlTmUtil::DATA_KIND_MAG_APPL </TD><TD> SlTmToMaMagAppl::MAG_APPL_4   </TD><TD> Magazine Appl-Param 4,  ($TC_MAPCS4)   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/applData       </TD><TD> SlTmToMaMagAppl  </TD><TD> SlTmUtil::DATA_KIND_MAG_APPL </TD><TD> SlTmToMaMagAppl::MAG_APPL_5   </TD><TD> Magazine Appl-Param 5,  ($TC_MAPCS5)   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/applData       </TD><TD> SlTmToMaMagAppl  </TD><TD> SlTmUtil::DATA_KIND_MAG_APPL </TD><TD> SlTmToMaMagAppl::MAG_APPL_6   </TD><TD> Magazine Appl-Param 6,  ($TC_MAPCS6)   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/applData       </TD><TD> SlTmToMaMagAppl  </TD><TD> SlTmUtil::DATA_KIND_MAG_APPL </TD><TD> SlTmToMaMagAppl::MAG_APPL_7   </TD><TD> Magazine Appl-Param 7,  ($TC_MAPCS7)   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/applData       </TD><TD> SlTmToMaMagAppl  </TD><TD> SlTmUtil::DATA_KIND_MAG_APPL </TD><TD> SlTmToMaMagAppl::MAG_APPL_8   </TD><TD> Magazine Appl-Param 8,  ($TC_MAPCS8)   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/applData       </TD><TD> SlTmToMaMagAppl  </TD><TD> SlTmUtil::DATA_KIND_MAG_APPL </TD><TD> SlTmToMaMagAppl::MAG_APPL_9   </TD><TD> Magazine Appl-Param 9,  ($TC_MAPCS9)   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/applData       </TD><TD> SlTmToMaMagAppl  </TD><TD> SlTmUtil::DATA_KIND_MAG_APPL </TD><TD> SlTmToMaMagAppl::MAG_APPL_10  </TD><TD> Magazine Appl-Param 10, ($TC_MAPCS10)  </TD></TR>
    <TR><TD> or </TD><TD></TD><TD></TD><TD></TD><TD></TD></TR>
    <TR><TD> /Tool/MagazineDescription/applDataDouble </TD><TD> SlTmToMaMagAppl  </TD><TD> SlTmUtil::DATA_KIND_MAG_APPL </TD><TD> SlTmToMaMagAppl::MAG_APPL_1   </TD><TD> Magazine Appl-Param 1,  ($TC_MAPCS1)   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/applDataDouble </TD><TD> SlTmToMaMagAppl  </TD><TD> SlTmUtil::DATA_KIND_MAG_APPL </TD><TD> SlTmToMaMagAppl::MAG_APPL_2   </TD><TD> Magazine Appl-Param 2,  ($TC_MAPCS2)   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/applDataDouble </TD><TD> SlTmToMaMagAppl  </TD><TD> SlTmUtil::DATA_KIND_MAG_APPL </TD><TD> SlTmToMaMagAppl::MAG_APPL_3   </TD><TD> Magazine Appl-Param 3,  ($TC_MAPCS3)   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/applDataDouble </TD><TD> SlTmToMaMagAppl  </TD><TD> SlTmUtil::DATA_KIND_MAG_APPL </TD><TD> SlTmToMaMagAppl::MAG_APPL_4   </TD><TD> Magazine Appl-Param 4,  ($TC_MAPCS4)   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/applDataDouble </TD><TD> SlTmToMaMagAppl  </TD><TD> SlTmUtil::DATA_KIND_MAG_APPL </TD><TD> SlTmToMaMagAppl::MAG_APPL_5   </TD><TD> Magazine Appl-Param 5,  ($TC_MAPCS5)   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/applDataDouble </TD><TD> SlTmToMaMagAppl  </TD><TD> SlTmUtil::DATA_KIND_MAG_APPL </TD><TD> SlTmToMaMagAppl::MAG_APPL_6   </TD><TD> Magazine Appl-Param 6,  ($TC_MAPCS6)   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/applDataDouble </TD><TD> SlTmToMaMagAppl  </TD><TD> SlTmUtil::DATA_KIND_MAG_APPL </TD><TD> SlTmToMaMagAppl::MAG_APPL_7   </TD><TD> Magazine Appl-Param 7,  ($TC_MAPCS7)   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/applDataDouble </TD><TD> SlTmToMaMagAppl  </TD><TD> SlTmUtil::DATA_KIND_MAG_APPL </TD><TD> SlTmToMaMagAppl::MAG_APPL_8   </TD><TD> Magazine Appl-Param 8,  ($TC_MAPCS8)   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/applDataDouble </TD><TD> SlTmToMaMagAppl  </TD><TD> SlTmUtil::DATA_KIND_MAG_APPL </TD><TD> SlTmToMaMagAppl::MAG_APPL_9   </TD><TD> Magazine Appl-Param 9,  ($TC_MAPCS9)   </TD></TR>
    <TR><TD> /Tool/MagazineDescription/applDataDouble </TD><TD> SlTmToMaMagAppl  </TD><TD> SlTmUtil::DATA_KIND_MAG_APPL </TD><TD> SlTmToMaMagAppl::MAG_APPL_10  </TD><TD> Magazine Appl-Param 10, ($TC_MAPCS10)  </TD></TR>
  </TABLE>
</TABLE>
\n
<TABLE>
  <TR><TD><b>Magazine Configuration: Magazine Configuration Data</b> \n
\code
SlTmStore::rContainerColl().rContainer(containerNo).rMagConf().rData().setVal(SlTmToMaMagConfData::MagConfDataIdxEnum); 
SlTmStore::rConstContainerColl().rConstContainer(containerNo).rConstMagConf().rConstData().val(SlTmToMaMagConfData::MagConfDataIdxEnum); 
\endcode
          OPI / BTSS data module: number 0x2C, 44, TMC, mag configuration data, Magazine configuration data
  </TD></TR>
  <TABLE>
    <TR><TD> OPI / BTSS item              </TD><TD> data class      </TD><TD> data kind enum               </TD><TD> data index enum                             </TD><TD> NC data  </TD></TR>
    <TR><TD> /Tool/MagazineConfiguration/magCBIdent    </TD><TD> SlTmToMaMagConfData  </TD><TD> SlTmUtil::DATA_KIND_MAGCONF_DATA  </TD><TD> SlTmToMaMagConfData::MAGCONF_DATA_IDENT                </TD><TD> name of magazine configuration (magCBIdent) ($TC_MAMP1)        </TD></TR>
    <TR><TD> /Tool/MagazineConfiguration/magBLMag      </TD><TD> SlTmToMaMagConfData  </TD><TD> SlTmUtil::DATA_KIND_MAGCONF_DATA  </TD><TD> SlTmToMaMagConfData::MAGCONF_DATA_LOAD_MAG_NO          </TD><TD> number (not count) of the internal load magazine (magBLMag)    </TD></TR>
    <TR><TD> /Tool/MagazineConfiguration/magZWMag      </TD><TD> SlTmToMaMagConfData  </TD><TD> SlTmUtil::DATA_KIND_MAGCONF_DATA  </TD><TD> SlTmToMaMagConfData::MAGCONF_DATA_BUFFER_MAG_NO        </TD><TD> number (not count) of the internal buffer magazine (magZWMag)  </TD></TR>
    <TR><TD> /Tool/MagazineConfiguration/magSearch     </TD><TD> SlTmToMaMagConfData  </TD><TD> SlTmUtil::DATA_KIND_MAGCONF_DATA  </TD><TD> SlTmToMaMagConfData::MAGCONF_DATA_TOOL_SEARCH          </TD><TD> kind of tool search (magSearch) ($TC_MAMP2)                    </TD></TR>
    <TR><TD> /Tool/MagazineConfiguration/magSearch     </TD><TD> SlTmToMaMagConfData  </TD><TD> SlTmUtil::DATA_KIND_MAGCONF_DATA  </TD><TD> SlTmToMaMagConfData::MAGCONF_DATA_PLACE_SEARCH         </TD><TD> kind of search for empty magazine location ($TC_MAMP2)         </TD></TR>
    <TR><TD> /Tool/MagazineConfiguration/magVPlaces    </TD><TD> SlTmToMaMagConfData  </TD><TD> SlTmUtil::DATA_KIND_MAGCONF_DATA  </TD><TD> SlTmToMaMagConfData::MAGCONF_DATA_NUM_ORDINARY_PLACES  </TD><TD> count of places without load and buffer (magVPlaces)           </TD></TR>
    <TR><TD> /Tool/MagazineConfiguration/magRPlaces    </TD><TD> SlTmToMaMagConfData  </TD><TD> SlTmUtil::DATA_KIND_MAGCONF_DATA  </TD><TD> SlTmToMaMagConfData::MAGCONF_DATA_NUM_ALL_PLACES       </TD><TD> count of all places (incl. load and buffer) (magRPlaces)       </TD></TR>
    <TR><TD> /Tool/MagazineConfiguration/modeWearGroup </TD><TD> SlTmToMaMagConfData  </TD><TD> SlTmUtil::DATA_KIND_MAGCONF_DATA  </TD><TD> SlTmToMaMagConfData::MAGCONF_DATA_MODE_WEARGROUP       </TD><TD> mode of handling wear group (modeWearGroup) ($TC_MAMP3)        </TD></TR>
    <TR><TD> -                                         </TD><TD> SlTmToMaMagConfData  </TD><TD> SlTmUtil::DATA_KIND_MAGCONF_DATA  </TD><TD> SlTmToMaMagConfData::MAGCONF_DATA_NUM_ALL_MAGS         </TD><TD> count of all magazins (incl. load and buffer)                  </TD></TR>
    <TR><TD> -                                         </TD><TD> SlTmToMaMagConfData  </TD><TD> SlTmUtil::DATA_KIND_MAGCONF_DATA  </TD><TD> SlTmToMaMagConfData::MAGCONF_DATA_NUM_ORDINARY_MAGS    </TD><TD> count of magazins without load and buffer                      </TD></TR>
    <!-- not supported yet 
    not supported yet -->
  </TABLE>
</TABLE>
\n
<TABLE>
  <TR><TD><b>MultiTool: MultiTool General Data</b> \n
\code
SlTmStore::rContainerColl().rContainer(containerNo).rMultiToolColl().rMultiTool(mtNo).rData().setVal(SlTmToMaMultiToolData::MultiToolDataIdxEnum); 
SlTmStore::rConstContainerColl().rConstContainer(containerNo).rConstMultiToolColl().rConstMultiTool(mtNo).rConstData().val(SlTmToMaMultiToolData::MultiToolDataIdxEnum); 
\endcode
          OPI / BTSS data module: number 0x5A, 90, MTD, Multitool data, general data
  </TD></TR>
  <TABLE>
    <TR><TD> OPI / BTSS item                 </TD><TD> data class             </TD><TD> data kind enum                      </TD><TD> data index enum                                                 </TD><TD> NC data                                                                  </TD></TR>
    <TR><TD> -                               </TD><TD> SlTmToMaMultiToolData  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_DATA  </TD><TD> SlTmToMaMultiToolData::MULTITOOL_DATA_MTNO                      </TD><TD> Multitool number, number (not count) of multitool, mtNo                  </TD></TR>
    <TR><TD> /Tool/MT/multitoolNumLoc        </TD><TD> SlTmToMaMultiToolData  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_DATA  </TD><TD> SlTmToMaMultiToolData::MULTITOOL_DATA_NUM_LOC                   </TD><TD> count of locations (places) in multitool  ($TC_MTPN)                     </TD></TR>
    <TR><TD> /Tool/MT/multitoolIdent         </TD><TD> SlTmToMaMultiToolData  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_DATA  </TD><TD> SlTmToMaMultiToolData::MULTITOOL_DATA_IDENT                     </TD><TD> multitool Ident                           ($TC_MTP2)                     </TD></TR>
    <TR><TD> /Tool/MT/multitoolInMag         </TD><TD> SlTmToMaMultiToolData  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_DATA  </TD><TD> SlTmToMaMultiToolData::MULTITOOL_DATA_INMAG                     </TD><TD> multitools current magazine               ($A_TOOLMN)                    </TD></TR>
    <TR><TD> /Tool/MT/multitoolInPlace       </TD><TD> SlTmToMaMultiToolData  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_DATA  </TD><TD> SlTmToMaMultiToolData::MULTITOOL_DATA_INPLACE                   </TD><TD> multitools current place                  ($A_TOOLMLN)                   </TD></TR>
    <TR><TD> /Tool/MT/multitoolMyMag         </TD><TD> SlTmToMaMultiToolData  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_DATA  </TD><TD> SlTmToMaMultiToolData::MULTITOOL_DATA_MYMAG                     </TD><TD> multitools owned magazine                 ($A_MYMN)                      </TD></TR>
    <TR><TD> /Tool/MT/multitoolMyPlace       </TD><TD> SlTmToMaMultiToolData  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_DATA  </TD><TD> SlTmToMaMultiToolData::MULTITOOL_DATA_MYPLACE                   </TD><TD> multitools owned place                    ($A_MYMLN)                     </TD></TR>
    <TR><TD> /Tool/MT/multitoolStateL        </TD><TD> SlTmToMaMultiToolData  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_DATA  </TD><TD> SlTmToMaMultiToolData::MULTITOOL_DATA_STATE                     </TD><TD> multitools state                          ($TC_MTP8)                     </TD></TR>
    <TR><TD> /Tool/MT/multitoolplace_spec    </TD><TD> SlTmToMaMultiToolData  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_DATA  </TD><TD> SlTmToMaMultiToolData::MULTITOOL_DATA_PLACE_SPEC                </TD><TD> multitools place spec                     ($TC_MTP7)                     </TD></TR>
    <TR><TD> /Tool/MT/multitoolsize_down     </TD><TD> SlTmToMaMultiToolData  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_DATA  </TD><TD> SlTmToMaMultiToolData::MULTITOOL_DATA_SIZE_DOWN                 </TD><TD> multitools size down                      ($TC_MTP6)                     </TD></TR>
    <TR><TD> /Tool/MT/multitoolsize_left     </TD><TD> SlTmToMaMultiToolData  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_DATA  </TD><TD> SlTmToMaMultiToolData::MULTITOOL_DATA_SIZE_LEFT                 </TD><TD> multitools size left                      ($TC_MTP3)                     </TD></TR>
    <TR><TD> /Tool/MT/multitoolsize_right    </TD><TD> SlTmToMaMultiToolData  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_DATA  </TD><TD> SlTmToMaMultiToolData::MULTITOOL_DATA_SIZE_RIGHT                </TD><TD> multitools size right                     ($TC_MTP4)                     </TD></TR>
    <TR><TD> /Tool/MT/multitoolsize_upper    </TD><TD> SlTmToMaMultiToolData  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_DATA  </TD><TD> SlTmToMaMultiToolData::MULTITOOL_DATA_SIZE_UPPER                </TD><TD> multitools size upper                     ($TC_MTP5)                     </TD></TR>
    <TR><TD> /Tool/MT/multitoolPosition      </TD><TD> SlTmToMaMultiToolData  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_DATA  </TD><TD> SlTmToMaMultiToolData::MULTITOOL_DATA_POSITION                  </TD><TD> multitoolplace-no in special position     ($TC_MTP_POS)                  </TD></TR>
    <TR><TD> /Tool/MT/multitoolProtAreaFile  </TD><TD> SlTmToMaMultiToolData  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_DATA  </TD><TD> SlTmToMaMultiToolData::MULTITOOL_DATA_PROT_AREA_FILE            </TD><TD> multitools protection area file           ($TC_MTP_PROTA)                </TD></TR>
    <TR><TD> /Tool/MT/multitoolKindOfDist    </TD><TD> SlTmToMaMultiToolData  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_DATA  </TD><TD> SlTmToMaMultiToolData::MULTITOOL_DATA_KIND_OF_DIST              </TD><TD> multitools kind of distance               ($TC_MTP_KD)                   </TD></TR>
    <TR><TD> computed by OPERATE             </TD><TD> SlTmToMaMultiToolData  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_DATA  </TD><TD> SlTmToMaMultiToolData::MULTITOOL_DATA_ADAPTNO                   </TD><TD> multitools adapt no                       (derived from $TC_MPP8)        </TD></TR>
    <!-- not supported yet 
    <TR><TD> /Tool/MT/multitoolAdaptNo       </TD><TD> SlTmToMaMultiToolData  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_DATA  </TD><TD> SlTmToMaMultiToolData::MULTITOOL_DATA_ADAPTNO                   </TD><TD> multitools adapt no   _multitooladapter_  (derived from $TC_MPP8)        </TD></TR>
    <TR><TD> /Tool/MT/multitoolMaxVelo       </TD><TD> SlTmToMaMultiToolData  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_DATA  </TD><TD> SlTmToMaMultiToolData::MULTITOOL_DATA_MAX_VELO                  </TD><TD> multitools max velocity                   ($TC_MTP_MAX_VELO)             </TD></TR>
    <TR><TD> /Tool/MT/multitoolMaxAcc        </TD><TD> SlTmToMaMultiToolData  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_DATA  </TD><TD> SlTmToMaMultiToolData::MULTITOOL_DATA_MAX_ACC                   </TD><TD> multitools max acceleration               ($TC_MTP_MAX_ACC)              </TD></TR>
    not supported yet -->
  </TABLE>
</TABLE>
\n
<TABLE>
  <TR><TD><b>MultiTool: MultiTool User Data (OEM Data)</b> \n
\code
SlTmStore::rContainerColl().rContainer(containerNo).rMultiToolColl().rMultiTool(mtNo).rUser().setVal(SlTmToMaMultiToolUser::MultiToolUserIdxEnum); 
SlTmStore::rConstContainerColl().rConstContainer(containerNo).rConstMultiToolColl().rConstMultiTool(mtNo).rConstUser().val(SlTmToMaMultiToolUser::MultiToolUserIdxEnum); 
\endcode
          OPI data module: number 0x5C, 92, MTUD, multitool user params, Multitool data for OEM
  </TD></TR>
  <TABLE>
    <TR><TD> OPI / BTSS item   </TD><TD> data class             </TD><TD> data kind enum                     </TD><TD> data index enum                          </TD><TD> NC data                               </TD></TR>
    <TR><TD> /Tool/MT/userData </TD><TD> SlTmToMaMultiToolUser  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_USER </TD><TD> SlTmToMaMultiToolUser::MULTITOOL_USER_1  </TD><TD> Multitool User-Param 1,  ($TC_MTPC1)  </TD></TR>
    <TR><TD> /Tool/MT/userData </TD><TD> SlTmToMaMultiToolUser  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_USER </TD><TD> SlTmToMaMultiToolUser::MULTITOOL_USER_2  </TD><TD> Multitool User-Param 2,  ($TC_MTPC2)  </TD></TR>
    <TR><TD> /Tool/MT/userData </TD><TD> SlTmToMaMultiToolUser  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_USER </TD><TD> SlTmToMaMultiToolUser::MULTITOOL_USER_3  </TD><TD> Multitool User-Param 3,  ($TC_MTPC3)  </TD></TR>
    <TR><TD> /Tool/MT/userData </TD><TD> SlTmToMaMultiToolUser  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_USER </TD><TD> SlTmToMaMultiToolUser::MULTITOOL_USER_4  </TD><TD> Multitool User-Param 4,  ($TC_MTPC4)  </TD></TR>
    <TR><TD> /Tool/MT/userData </TD><TD> SlTmToMaMultiToolUser  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_USER </TD><TD> SlTmToMaMultiToolUser::MULTITOOL_USER_5  </TD><TD> Multitool User-Param 5,  ($TC_MTPC5)  </TD></TR>
    <TR><TD> /Tool/MT/userData </TD><TD> SlTmToMaMultiToolUser  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_USER </TD><TD> SlTmToMaMultiToolUser::MULTITOOL_USER_6  </TD><TD> Multitool User-Param 6,  ($TC_MTPC6)  </TD></TR>
    <TR><TD> /Tool/MT/userData </TD><TD> SlTmToMaMultiToolUser  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_USER </TD><TD> SlTmToMaMultiToolUser::MULTITOOL_USER_7  </TD><TD> Multitool User-Param 7,  ($TC_MTPC7)  </TD></TR>
    <TR><TD> /Tool/MT/userData </TD><TD> SlTmToMaMultiToolUser  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_USER </TD><TD> SlTmToMaMultiToolUser::MULTITOOL_USER_8  </TD><TD> Multitool User-Param 8,  ($TC_MTPC8)  </TD></TR>
    <TR><TD> /Tool/MT/userData </TD><TD> SlTmToMaMultiToolUser  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_USER </TD><TD> SlTmToMaMultiToolUser::MULTITOOL_USER_9  </TD><TD> Multitool User-Param 9,  ($TC_MTPC9)  </TD></TR>
    <TR><TD> /Tool/MT/userData </TD><TD> SlTmToMaMultiToolUser  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_USER </TD><TD> SlTmToMaMultiToolUser::MULTITOOL_USER_10 </TD><TD> Multitool User-Param 10, ($TC_MTPC10) </TD></TR>
    <TR><TD> ...               </TD><TD> ...                    </TD><TD> ...                                </TD><TD> ...                                      </TD><TD> ...                                   </TD></TR>
    <TR><TD> /Tool/MT/userData </TD><TD> SlTmToMaMultiToolUser  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_USER </TD><TD> SlTmToMaMultiToolUser::MULTITOOL_USER_64 </TD><TD> Multitool User-Param 64, ($TC_MTPC64) </TD></TR>
  </TABLE>
</TABLE>
\n
<TABLE>
  <TR><TD><b>MultiTool: MultiTool Application Data (Siemens Data)</b> \n
\code
SlTmStore::rContainerColl().rContainer(containerNo).rMultiToolColl().rMultiTool(mtNo).rAppl().setVal(SlTmToMaMultiToolAppl::MultiToolApplIdxEnum); 
SlTmStore::rConstContainerColl().rConstContainer(containerNo).rConstMultiToolColl().rConstMultiTool(mtNo).rConstAppl().val(SlTmToMaMultiToolAppl::MultiToolApplIdxEnum); 
\endcode
          OPI data module: number 0x5E, 94, MTAD, multitool appl params, Application-specific multitool data for SIEMENS
  </TD></TR>
  <TABLE>
    <TR><TD> OPI / BTSS item   </TD><TD> data class             </TD><TD> data kind enum                     </TD><TD> data index enum                          </TD><TD> NC data                                </TD></TR>
    <TR><TD> /Tool/MT/applData </TD><TD> SlTmToMaMultiToolAppl  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_APPL </TD><TD> SlTmToMaMultiToolAppl::MULTITOOL_APPL_1  </TD><TD> Multitool Appl-Param 1,  ($TC_MTPCS1)  </TD></TR>
    <TR><TD> /Tool/MT/applData </TD><TD> SlTmToMaMultiToolAppl  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_APPL </TD><TD> SlTmToMaMultiToolAppl::MULTITOOL_APPL_2  </TD><TD> Multitool Appl-Param 2,  ($TC_MTPCS2)  </TD></TR>
    <TR><TD> /Tool/MT/applData </TD><TD> SlTmToMaMultiToolAppl  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_APPL </TD><TD> SlTmToMaMultiToolAppl::MULTITOOL_APPL_3  </TD><TD> Multitool Appl-Param 3,  ($TC_MTPCS3)  </TD></TR>
    <TR><TD> /Tool/MT/applData </TD><TD> SlTmToMaMultiToolAppl  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_APPL </TD><TD> SlTmToMaMultiToolAppl::MULTITOOL_APPL_4  </TD><TD> Multitool Appl-Param 4,  ($TC_MTPCS4)  </TD></TR>
    <TR><TD> /Tool/MT/applData </TD><TD> SlTmToMaMultiToolAppl  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_APPL </TD><TD> SlTmToMaMultiToolAppl::MULTITOOL_APPL_5  </TD><TD> Multitool Appl-Param 5,  ($TC_MTPCS5)  </TD></TR>
    <TR><TD> /Tool/MT/applData </TD><TD> SlTmToMaMultiToolAppl  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_APPL </TD><TD> SlTmToMaMultiToolAppl::MULTITOOL_APPL_6  </TD><TD> Multitool Appl-Param 6,  ($TC_MTPCS6)  </TD></TR>
    <TR><TD> /Tool/MT/applData </TD><TD> SlTmToMaMultiToolAppl  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_APPL </TD><TD> SlTmToMaMultiToolAppl::MULTITOOL_APPL_7  </TD><TD> Multitool Appl-Param 7,  ($TC_MTPCS7)  </TD></TR>
    <TR><TD> /Tool/MT/applData </TD><TD> SlTmToMaMultiToolAppl  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_APPL </TD><TD> SlTmToMaMultiToolAppl::MULTITOOL_APPL_8  </TD><TD> Multitool Appl-Param 8,  ($TC_MTPCS8)  </TD></TR>
    <TR><TD> /Tool/MT/applData </TD><TD> SlTmToMaMultiToolAppl  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_APPL </TD><TD> SlTmToMaMultiToolAppl::MULTITOOL_APPL_9  </TD><TD> Multitool Appl-Param 9,  ($TC_MTPCS9)  </TD></TR>
    <TR><TD> /Tool/MT/applData </TD><TD> SlTmToMaMultiToolAppl  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_APPL </TD><TD> SlTmToMaMultiToolAppl::MULTITOOL_APPL_10 </TD><TD> Multitool Appl-Param 10, ($TC_MTPCS10) </TD></TR>
  </TABLE>
</TABLE>
\n
<TABLE>
  <TR><TD><b>Multitool: Multitool Place Data</b> \n
\code
SlTmStore::rContainerColl().rContainer(containerNo).rMultiToolColl().rMultiTool(mtNo).rMultiToolPlaceColl().rMultiToolPlace(multiToolPlaceNo).rData().setVal(SlTmToMaMultiToolPlaceData::MultiToolPlaceDataIdxEnum); 
SlTmStore::rConstContainerColl().rConstContainer(containerNo).rConstMultiToolColl().rConstMultiTool(mtNo).rConstMultiToolPlaceColl().rConstMultiToolPlace(multiToolPlaceNo).rConstData().val(SlTmToMaMultiToolPlaceData::MultiToolPlaceDataIdxEnum); 
\endcode
          OPI / BTSS data module: number 0x5B, 91, MTP, multitool loc params, multitool place data 
  </TD></TR>
  <TABLE>
    <TR><TD> OPI / BTSS item             </TD><TD> data class                  </TD><TD> data kind enum                            </TD><TD> data index enum                                                             </TD><TD> NC data                                                                </TD></TR>
    <TR><TD> /Tool/MTPlace/mtPlaceData   </TD><TD> SlTmToMaMultiToolPlaceData  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_PLACE_DATA  </TD><TD> SlTmToMaMultiToolPlaceData::MULTITOOL_PLACE_DATA_DIST_LENGTH                </TD><TD> place distance length                     ($TC_MTPPL)                  </TD></TR>
    <TR><TD> /Tool/MTPlace/mtPlaceData   </TD><TD> SlTmToMaMultiToolPlaceData  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_PLACE_DATA  </TD><TD> SlTmToMaMultiToolPlaceData::MULTITOOL_PLACE_DATA_DIST_ANGLE                 </TD><TD> place distance angle                      ($TC_MTPPA)                  </TD></TR>
    <TR><TD> /Tool/MTPlace/mtPlaceData   </TD><TD> SlTmToMaMultiToolPlaceData  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_PLACE_DATA  </TD><TD> SlTmToMaMultiToolPlaceData::MULTITOOL_PLACE_DATA_TYPE                       </TD><TD> Location type (read access only)          ($TC_MTPP2)                  </TD></TR>
    <TR><TD> /Tool/MTPlace/mtPlaceData   </TD><TD> SlTmToMaMultiToolPlaceData  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_PLACE_DATA  </TD><TD> SlTmToMaMultiToolPlaceData::MULTITOOL_PLACE_DATA_STATUS                     </TD><TD> multitool place status                    ($TC_MTPP4)                  </TD></TR>
    <TR><TD> /Tool/MTPlace/mtPlaceData   </TD><TD> SlTmToMaMultiToolPlaceData  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_PLACE_DATA  </TD><TD> SlTmToMaMultiToolPlaceData::MULTITOOL_PLACE_DATA_TNO                        </TD><TD> T number of tool in this multitool place  ($TC_MTPP6)                  </TD></TR>
    <TR><TD> /Tool/MTPlace/mtPlaceData   </TD><TD> SlTmToMaMultiToolPlaceData  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_PLACE_DATA  </TD><TD> SlTmToMaMultiToolPlaceData::MULTITOOL_PLACE_DATA_ADAPT_NO                   </TD><TD> Number of adapter in multitool place      ($TC_MTPP7)                  </TD></TR>
  </TABLE>
</TABLE>
\n
<TABLE>
  <TR><TD><b>MultiTool: MultiTool Place User Data (OEM Data)</b> \n
\code
SlTmStore::rContainerColl().rContainer(containerNo).rMultiToolColl().rMultiTool(mtNo).rMultiToolPlaceColl().rMultiToolPlace(multiToolPlaceNo).rUser().setVal(SlTmToMaMultiToolPlaceUser::MultiToolPlaceUserIdxEnum); 
SlTmStore::rConstContainerColl().rConstContainer(containerNo).rConstMultiToolColl().rConstMultiTool(mtNo).rConstMultiToolPlaceColl().rConstMultiToolPlace(multiToolPlaceNo).rConstUser().val(SlTmToMaMultiToolPlaceUser::MultiToolPlaceUserIdxEnum); 
\endcode
          OPI data module: number 0x5D, 93, MTUP, multitool loc user params, multitool place data for OEM 
  </TD></TR>
  <TABLE> 
    <TR><TD> OPI / BTSS item        </TD><TD> data class                  </TD><TD> data kind enum                           </TD><TD> data index enum                                     </TD><TD> NC data                                      </TD></TR>
    <TR><TD> /Tool/MTPlace/userData </TD><TD> SlTmToMaMultiToolPlaceUser  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_PLACE_USER </TD><TD> SlTmToMaMultiToolPlaceUser::MULTITOOL_PLACE_USER_1  </TD><TD> Multitool Place User-Param 1,  ($TC_MTPPC1)  </TD></TR>
    <TR><TD> /Tool/MTPlace/userData </TD><TD> SlTmToMaMultiToolPlaceUser  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_PLACE_USER </TD><TD> SlTmToMaMultiToolPlaceUser::MULTITOOL_PLACE_USER_2  </TD><TD> Multitool Place User-Param 2,  ($TC_MTPPC2)  </TD></TR>
    <TR><TD> /Tool/MTPlace/userData </TD><TD> SlTmToMaMultiToolPlaceUser  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_PLACE_USER </TD><TD> SlTmToMaMultiToolPlaceUser::MULTITOOL_PLACE_USER_3  </TD><TD> Multitool Place User-Param 3,  ($TC_MTPPC3)  </TD></TR>
    <TR><TD> /Tool/MTPlace/userData </TD><TD> SlTmToMaMultiToolPlaceUser  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_PLACE_USER </TD><TD> SlTmToMaMultiToolPlaceUser::MULTITOOL_PLACE_USER_4  </TD><TD> Multitool Place User-Param 4,  ($TC_MTPPC4)  </TD></TR>
    <TR><TD> /Tool/MTPlace/userData </TD><TD> SlTmToMaMultiToolPlaceUser  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_PLACE_USER </TD><TD> SlTmToMaMultiToolPlaceUser::MULTITOOL_PLACE_USER_5  </TD><TD> Multitool Place User-Param 5,  ($TC_MTPPC5)  </TD></TR>
    <TR><TD> /Tool/MTPlace/userData </TD><TD> SlTmToMaMultiToolPlaceUser  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_PLACE_USER </TD><TD> SlTmToMaMultiToolPlaceUser::MULTITOOL_PLACE_USER_6  </TD><TD> Multitool Place User-Param 6,  ($TC_MTPPC6)  </TD></TR>
    <TR><TD> /Tool/MTPlace/userData </TD><TD> SlTmToMaMultiToolPlaceUser  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_PLACE_USER </TD><TD> SlTmToMaMultiToolPlaceUser::MULTITOOL_PLACE_USER_7  </TD><TD> Multitool Place User-Param 7,  ($TC_MTPPC7)  </TD></TR>
    <TR><TD> /Tool/MTPlace/userData </TD><TD> SlTmToMaMultiToolPlaceUser  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_PLACE_USER </TD><TD> SlTmToMaMultiToolPlaceUser::MULTITOOL_PLACE_USER_8  </TD><TD> Multitool Place User-Param 8,  ($TC_MTPPC8)  </TD></TR>
    <TR><TD> /Tool/MTPlace/userData </TD><TD> SlTmToMaMultiToolPlaceUser  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_PLACE_USER </TD><TD> SlTmToMaMultiToolPlaceUser::MULTITOOL_PLACE_USER_9  </TD><TD> Multitool Place User-Param 9,  ($TC_MTPPC9)  </TD></TR>
    <TR><TD> /Tool/MTPlace/userData </TD><TD> SlTmToMaMultiToolPlaceUser  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_PLACE_USER </TD><TD> SlTmToMaMultiToolPlaceUser::MULTITOOL_PLACE_USER_10 </TD><TD> Multitool Place User-Param 10, ($TC_MTPPC10) </TD></TR>
    <TR><TD> ...                    </TD><TD> ...                         </TD><TD> ...                                      </TD><TD> ...                                                 </TD><TD> ...                                          </TD></TR>
    <TR><TD> /Tool/MTPlace/userData </TD><TD> SlTmToMaMultiToolPlaceUser  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_PLACE_USER </TD><TD> SlTmToMaMultiToolPlaceUser::MULTITOOL_PLACE_USER_64 </TD><TD> Multitool Place User-Param 64, ($TC_MTPPC64) </TD></TR>
  </TABLE>
</TABLE>
\n
<TABLE>
  <TR><TD><b>MultiTool: MultiTool Place Application Data (Siemens Data)</b> \n
\code
SlTmStore::rContainerColl().rContainer(containerNo).rMultiToolColl().rMultiTool(mtNo).rMultiToolPlaceColl().rMultiToolPlace(multiToolPlaceNo).rAppl().setVal(SlTmToMaMultiToolPlaceAppl::MultiToolPlaceApplIdxEnum); 
SlTmStore::rConstContainerColl().rConstContainer(containerNo).rConstMultiToolColl().rConstMultiTool(mtNo).rConstMultiToolPlaceColl().rConstMultiToolPlace(multiToolPlaceNo).rConstAppl().val(SlTmToMaMultiToolPlaceAppl::MultiToolPlaceApplIdxEnum); 
\endcode
          OPI data module: number 0x5F, 95, MTAP, multitool loc appl params, application-specific multitool place data for SIEMENS
  </TD></TR>
  <TABLE>
    <TR><TD> OPI / BTSS item        </TD><TD> data class                  </TD><TD> data kind enum                           </TD><TD> data index enum                                     </TD><TD> NC data                                       </TD></TR>
    <TR><TD> /Tool/MTPlace/applData </TD><TD> SlTmToMaMultiToolPlaceAppl  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_PLACE_APPL </TD><TD> SlTmToMaMultiToolPlaceAppl::MULTITOOL_PLACE_APPL_1  </TD><TD> Multitool Place Appl-Param 1,  ($TC_MTPPCS1)  </TD></TR>
    <TR><TD> /Tool/MTPlace/applData </TD><TD> SlTmToMaMultiToolPlaceAppl  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_PLACE_APPL </TD><TD> SlTmToMaMultiToolPlaceAppl::MULTITOOL_PLACE_APPL_2  </TD><TD> Multitool Place Appl-Param 2,  ($TC_MTPPCS2)  </TD></TR>
    <TR><TD> /Tool/MTPlace/applData </TD><TD> SlTmToMaMultiToolPlaceAppl  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_PLACE_APPL </TD><TD> SlTmToMaMultiToolPlaceAppl::MULTITOOL_PLACE_APPL_3  </TD><TD> Multitool Place Appl-Param 3,  ($TC_MTPPCS3)  </TD></TR>
    <TR><TD> /Tool/MTPlace/applData </TD><TD> SlTmToMaMultiToolPlaceAppl  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_PLACE_APPL </TD><TD> SlTmToMaMultiToolPlaceAppl::MULTITOOL_PLACE_APPL_4  </TD><TD> Multitool Place Appl-Param 4,  ($TC_MTPPCS4)  </TD></TR>
    <TR><TD> /Tool/MTPlace/applData </TD><TD> SlTmToMaMultiToolPlaceAppl  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_PLACE_APPL </TD><TD> SlTmToMaMultiToolPlaceAppl::MULTITOOL_PLACE_APPL_5  </TD><TD> Multitool Place Appl-Param 5,  ($TC_MTPPCS5)  </TD></TR>
    <TR><TD> /Tool/MTPlace/applData </TD><TD> SlTmToMaMultiToolPlaceAppl  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_PLACE_APPL </TD><TD> SlTmToMaMultiToolPlaceAppl::MULTITOOL_PLACE_APPL_6  </TD><TD> Multitool Place Appl-Param 6,  ($TC_MTPPCS6)  </TD></TR>
    <TR><TD> /Tool/MTPlace/applData </TD><TD> SlTmToMaMultiToolPlaceAppl  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_PLACE_APPL </TD><TD> SlTmToMaMultiToolPlaceAppl::MULTITOOL_PLACE_APPL_7  </TD><TD> Multitool Place Appl-Param 7,  ($TC_MTPPCS7)  </TD></TR>
    <TR><TD> /Tool/MTPlace/applData </TD><TD> SlTmToMaMultiToolPlaceAppl  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_PLACE_APPL </TD><TD> SlTmToMaMultiToolPlaceAppl::MULTITOOL_PLACE_APPL_8  </TD><TD> Multitool Place Appl-Param 8,  ($TC_MTPPCS8)  </TD></TR>
    <TR><TD> /Tool/MTPlace/applData </TD><TD> SlTmToMaMultiToolPlaceAppl  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_PLACE_APPL </TD><TD> SlTmToMaMultiToolPlaceAppl::MULTITOOL_PLACE_APPL_9  </TD><TD> Multitool Place Appl-Param 9,  ($TC_MTPPCS9)  </TD></TR>
    <TR><TD> /Tool/MTPlace/applData </TD><TD> SlTmToMaMultiToolPlaceAppl  </TD><TD> SlTmUtil::DATA_KIND_MULTITOOL_PLACE_APPL </TD><TD> SlTmToMaMultiToolPlaceAppl::MULTITOOL_PLACE_APPL_10 </TD><TD> Multitool Place Appl-Param 10, ($TC_MTPPCS10) </TD></TR>
  </TABLE>
</TABLE>
\n
<TABLE>
  <TR><TD><b>TISO: ISO2.2 / ISO3.2 Correction Values</b> \n
\code
SlTmStore::rContainerColl().rContainer(containerNo).rTIsoColl().rTIsoData(hdNo).setVal(SlTmToMaTIsoData::TIsoDataIdxEnum); 
SlTmStore::rConstContainerColl().rConstContainer(containerNo).rConstTIsoColl().rConstTIsoData(hdNo).val(SlTmToMaTIsoData::TIsoDataIdxEnum); 
\endcode
          OPI / BTSS data module: number 0x1D = 29, TISO, ISO corr values for ISO2.2 and ISO3.2
  </TD></TR>
  <TABLE>
    <TR><TD> OPI / BTSS item              </TD><TD> data class      </TD><TD> data kind enum               </TD><TD> data index enum                             </TD><TD> NC data  </TD></TR>
    <TR><TD> -                                     </TD><TD> SlTmToMaTIsoData  </TD><TD> SlTmUtil::DATA_KIND_TISO_DATA  </TD><TD> SlTmToMaTIsoData::TISO_HDNO                      </TD><TD> H/D-Number (not count) of ISO2.2 or ISO3.2 HD correction data set, hdNo      </TD></TR>
    <TR><TD> -                                     </TD><TD> SlTmToMaTIsoData  </TD><TD> SlTmUtil::DATA_KIND_TISO_DATA  </TD><TD> SlTmToMaTIsoData::TISO_IS_AFFECTED_BY_CURR_CHAN  </TD><TD> depends on context: HD correction data set is affected by curr channel data  </TD></TR>
    <TR><TD> /Tool/IsoHDCompensation/isoCorrParam  </TD><TD> SlTmToMaTIsoData  </TD><TD> SlTmUtil::DATA_KIND_TISO_DATA  </TD><TD> SlTmToMaTIsoData::TISO_2_H                       </TD><TD> ISO2.2, $TC_ISO_H,   geometry, length offset,                 like $TC_DP3   </TD></TR>
    <TR><TD> /Tool/IsoHDCompensation/isoCorrParam  </TD><TD> SlTmToMaTIsoData  </TD><TD> SlTmUtil::DATA_KIND_TISO_DATA  </TD><TD> SlTmToMaTIsoData::TISO_2_HW                      </TD><TD> ISO2.2, $TC_ISO_HW,  wear,     length offset,                 like $TC_DP12  </TD></TR>
    <TR><TD> /Tool/IsoHDCompensation/isoCorrParam  </TD><TD> SlTmToMaTIsoData  </TD><TD> SlTmUtil::DATA_KIND_TISO_DATA  </TD><TD> SlTmToMaTIsoData::TISO_2_D                       </TD><TD> ISO2.2, $TC_ISO_D,   geometry, radius offset,                 like $TC_DP6   </TD></TR>
    <TR><TD> /Tool/IsoHDCompensation/isoCorrParam  </TD><TD> SlTmToMaTIsoData  </TD><TD> SlTmUtil::DATA_KIND_TISO_DATA  </TD><TD> SlTmToMaTIsoData::TISO_2_DW                      </TD><TD> ISO2.2, $TC_ISO_DW,  wear,     radius offset,                 like $TC_DP15  </TD></TR>
    <TR><TD> /Tool/IsoHDCompensation/isoCorrParam  </TD><TD> SlTmToMaTIsoData  </TD><TD> SlTmUtil::DATA_KIND_TISO_DATA  </TD><TD> SlTmToMaTIsoData::TISO_3_L1                      </TD><TD> ISO3.2, $TC_ISO_L1,  geometry  length offset of direction L1, like $TC_DP3   </TD></TR>
    <TR><TD> /Tool/IsoHDCompensation/isoCorrParam  </TD><TD> SlTmToMaTIsoData  </TD><TD> SlTmUtil::DATA_KIND_TISO_DATA  </TD><TD> SlTmToMaTIsoData::TISO_3_L1W                     </TD><TD> ISO3.2, $TC_ISO_L1W, wear,     length offset of direction L1, like $TC_DP12  </TD></TR>
    <TR><TD> /Tool/IsoHDCompensation/isoCorrParam  </TD><TD> SlTmToMaTIsoData  </TD><TD> SlTmUtil::DATA_KIND_TISO_DATA  </TD><TD> SlTmToMaTIsoData::TISO_3_L2                      </TD><TD> ISO3.2, $TC_ISO_L2,  geometry, length offset of direction L2, like $TC_DP4   </TD></TR>
    <TR><TD> /Tool/IsoHDCompensation/isoCorrParam  </TD><TD> SlTmToMaTIsoData  </TD><TD> SlTmUtil::DATA_KIND_TISO_DATA  </TD><TD> SlTmToMaTIsoData::TISO_3_L2W                     </TD><TD> ISO3.2, $TC_ISO_L2W, wear,     length offset of direction L2, like $TC_DP13  </TD></TR>
    <TR><TD> /Tool/IsoHDCompensation/isoCorrParam  </TD><TD> SlTmToMaTIsoData  </TD><TD> SlTmUtil::DATA_KIND_TISO_DATA  </TD><TD> SlTmToMaTIsoData::TISO_3_L3                      </TD><TD> ISO3.2, $TC_ISO_L3,  geometry, length offset of direction L3, like $TC_DP5   </TD></TR>
    <TR><TD> /Tool/IsoHDCompensation/isoCorrParam  </TD><TD> SlTmToMaTIsoData  </TD><TD> SlTmUtil::DATA_KIND_TISO_DATA  </TD><TD> SlTmToMaTIsoData::TISO_3_L3W                     </TD><TD> ISO3.2, $TC_ISO_L3W, wear,     length offset of direction L3, like $TC_DP14  </TD></TR>
    <TR><TD> /Tool/IsoHDCompensation/isoCorrParam  </TD><TD> SlTmToMaTIsoData  </TD><TD> SlTmUtil::DATA_KIND_TISO_DATA  </TD><TD> SlTmToMaTIsoData::TISO_3_R                       </TD><TD> ISO3.2, $TC_ISO_R,   geometry, radius offset,                 like $TC_DP6   </TD></TR>
    <TR><TD> /Tool/IsoHDCompensation/isoCorrParam  </TD><TD> SlTmToMaTIsoData  </TD><TD> SlTmUtil::DATA_KIND_TISO_DATA  </TD><TD> SlTmToMaTIsoData::TISO_3_RW                      </TD><TD> ISO3.2, $TC_ISO_RW,  wear,     radius offset,                 like $TC_DP15  </TD></TR>
    <TR><TD> /Tool/IsoHDCompensation/isoCorrParam  </TD><TD> SlTmToMaTIsoData  </TD><TD> SlTmUtil::DATA_KIND_TISO_DATA  </TD><TD> SlTmToMaTIsoData::TISO_3_Q                       </TD><TD> ISO3.2, $TC_ISO_Q,   geometry, point direction,               like $TC_DP2   </TD></TR>
  </TABLE>
</TABLE>
\n
<TABLE>
  <TR><TD><b>Misc OPI / BTSS data items</b> \n
          \n
          Further data is relevant for OPERATEs (HMI SolutionLines) toolmanagement: 
          - current tool related activities in channel
          - current magazine place positions
          - array sizes in sltmservices data store classes
          - devices (NC's) abilities and sizes of NCs data
          .
  </TD></TR>
  <TR><TD>
          <b>current tool related activities in channel</b> \n
          based on OPI / BTSS data module number 0x7F = 127, C/S, channel-specific state data, \n
          \c /Channel/State/..., i.e. \c /Channel/State/actTNumber, \n  
          see SlTmToMaCurrChanData::CurrChanDataIdxEnum, i.e. SlTmToMaCurrChanData::CURR_CHAN_DATA_ACT_T_NUMBER \n
          in SlTmToMaCurrChanData, referenced by ::SlTmToMaCurrChan::rData() and ::SlTmToMaCurrChan::rConstData() \n
          in SlTmToMaCurrChan \n
          in SlTmToMaCurrChanColl of ::SlTmToolMagListCurrChanCollMapType \n 
          in ::SlTmMassDataToolMagListChangedData::m_ListCurrChanCollMap, \n
          via SlTmQCmd::signalNotifySubscribeToolMagList() / SlTmQCmd::subscribeToolMagList() \n 
          and accordingly SlTmCmdCallBackI::onNotifySubscribeToolMagList() / SlTmCmd::subscribeToolMagList()
  </TD></TR>
  <TR><TD>
          <b>current magazine place positions</b> \n
          based on \c /Tool/MagazineDescription/magActPlace and other data, \n
          see SlTmToMaCurrPlaceData in \n
          ::SlTmToMaCurrPlaceCollVecType ::SlTmMassDataToolMagListChangedData::m_ListCurrPlaceCollVec \n
          via SlTmQCmd::signalNotifySubscribeToolMagList() / SlTmQCmd::subscribeToolMagList() \n 
          and accordingly SlTmCmdCallBackI::onNotifySubscribeToolMagList() / SlTmCmd::subscribeToolMagList()
  </TD></TR>
  <TR><TD>
          <b>array sizes in sltmservices data store classes</b> \n
          see SlTmToMaContainerSize::ToMaContainerSizeIdxEnum in \n
          SlTmToMaContainerSize via SlTmQCmd::getToMaContainerSize() and accordingly SlTmCmd::getToMaContainerSize()
  </TD></TR>
  <TR><TD>
          <b>devices (NC's) abilities and sizes of NCs data</b> 
          
          A lot of information about whole NC and channels of NC, \n
          based on OPI / BTSS data \n
          (i.e \c /Nck/Configuration/..., \c /Channel/Configuration/..., \c /Nck/State/..., \c /Channel/State/...) \n
          and on NC machine and setting data \n
          (i.e. $MN_..., $MC_...) \n
          is contained here: \n
\code
const SlTmSysDeviceData& SlTmStore::rConstSys().rConstDeviceColl().rConstDevice(devNo).rConstDeviceData().val(SlTmSysDeviceData::SysDeviceEnum);
SlTmUtil::DATA_KIND_DEVICE_DATA;

const SlTmSysChannelData& SlTmStore::rConstSys().rConstDeviceColl().rConstDevice(devNo).rConstChannelColl().rChannelData(chanNo).val(SlTmSysChannelData::ChannelDataEnum); 
SlTmUtil::DATA_KIND_CHANNEL_DATA;
\endcode
  </TD></TR>
</TABLE>
\n
<TABLE>
  <TR><TD><b>Methods of SlTmQCmd and associated PI-Services of NC</b> \n
          These list shows SlTmQCmd methods and their associated NC-PI-Services. \n
          If user has experience in using NC-PI-Services, \n
          this can help to find adequate SlTmQCmd methods and parameters.
  </TD></TR>
  <TABLE>
    <TR><TD> SlTmQCmd methods, part 1                           </TD><TD> PI-Service </TD><TD> PI-Service </TD><TD> PI-Service </TD><TD> PI-Service </TD><TD> PI-Service </TD><TD> PI-Service </TD><TD> PI-Service </TD><TD> PI-Service </TD><TD> PI-Service </TD><TD> PI-Service </TD></TR>
    <TR><TD> SlTmQCmd::createEdgeAsync()                        </TD><TD> -          </TD><TD> _N_CRCEDN  </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD></TR>
    <TR><TD> SlTmQCmd::createMultiToolAndLoadIntoMagAsync()     </TD><TD> _N_MMCSEM  </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> _N_TMCRMT  </TD><TD> _N_TMFDPL  </TD><TD> -          </TD><TD> _N_TMMVTL  </TD><TD> -          </TD><TD> -          </TD></TR>
    <TR><TD> SlTmQCmd::createMultiToolAsync()                   </TD><TD> _N_MMCSEM  </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> _N_TMCRMT  </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD></TR>
    <TR><TD> SlTmQCmd::createToolAndInsertIntoMultiToolAsync()  </TD><TD> _N_MMCSEM  </TD><TD> _N_CRCEDN  </TD><TD> -          </TD><TD> -          </TD><TD> _N_TMCRTC  </TD><TD> _N_FDPLMT  </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD></TR>
    <TR><TD> SlTmQCmd::createToolAndLoadIntoMagAsync()          </TD><TD> _N_MMCSEM  </TD><TD> _N_CRCEDN  </TD><TD> -          </TD><TD> -          </TD><TD> _N_TMCRTC  </TD><TD> _N_TMFDPL  </TD><TD> -          </TD><TD> _N_TMMVTL  </TD><TD> -          </TD><TD> -          </TD></TR>
    <TR><TD> SlTmQCmd::createToolAsync()                        </TD><TD> _N_MMCSEM  </TD><TD> _N_CRCEDN  </TD><TD> -          </TD><TD> -          </TD><TD> _N_TMCRTC  </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD></TR>
    <TR><TD> SlTmQCmd::deleteEdgeAsync()                        </TD><TD> -          </TD><TD> -          </TD><TD> _N_DELECE  </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD></TR>
    <TR><TD> SlTmQCmd::deleteMultiToolAsync()                   </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> _N_TMDLMT  </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD></TR>
    <TR><TD> SlTmQCmd::deleteToolAsync()                        </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> _N_DELETO  </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD></TR>
    <TR><TD> SlTmQCmd::insertToolIntoMultiToolAsync()           </TD><TD> _N_MMCSEM  </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> _N_FDPLMT  </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD></TR>
    <TR><TD> SlTmQCmd::loadToolIntoMagAsync()                   </TD><TD> _N_MMCSEM  </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> _N_TMFDPL  </TD><TD> -          </TD><TD> _N_TMMVTL  </TD><TD> -          </TD><TD> -          </TD></TR>
    <TR><TD> SlTmQCmd::positionMagazineAndReactivateAsync()     </TD><TD> _N_MMCSEM  </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> _N_TMPOSM  </TD><TD> _N_TRESMO  </TD></TR>
    <TR><TD> SlTmQCmd::positionMagazineAsync()                  </TD><TD> _N_MMCSEM  </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> _N_TMPOSM  </TD><TD> -          </TD></TR>
    <TR><TD> SlTmQCmd::positionMultiToolAsync()                 </TD><TD> _N_MMCSEM  </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> _N_POSMT_  </TD><TD> -          </TD></TR>
    <TR><TD> SlTmQCmd::reactivateAsync()                        </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> _N_TRESMO  </TD></TR>
    <TR><TD> SlTmQCmd::relocateToolAsync()                      </TD><TD> _N_MMCSEM  </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> _N_TMFDPL  </TD><TD> -          </TD><TD> _N_TMMVTL  </TD><TD> -          </TD><TD> -          </TD></TR>
    <TR><TD> SlTmQCmd::searchForEmptyMultiToolPlaceAsync()      </TD><TD> _N_MMCSEM  </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> _N_FDPLMT  </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD></TR>
    <TR><TD> SlTmQCmd::searchForEmptyPlaceByPropertiesAsync()   </TD><TD> _N_MMCSEM  </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> _N_TMFPBP  </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD></TR>
    <TR><TD> SlTmQCmd::searchForEmptyPlaceByToolAsync()         </TD><TD> _N_MMCSEM  </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> _N_TMFDPL  </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD></TR>
    <TR><TD> SlTmQCmd::takeOutToolFromMultiToolAndDeleteAsync() </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> _N_DELETO  </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD></TR>
    <TR><TD> SlTmQCmd::unloadMultiToolFromMagAndDeleteAsync()   </TD><TD> _N_MMCSEM  </TD><TD> -          </TD><TD> -          </TD><TD> _N_TMDLMT  </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> _N_TMMVTL  </TD><TD> -          </TD><TD> -          </TD></TR>
    <TR><TD> SlTmQCmd::unloadToolFromMagAndDeleteAsync()        </TD><TD> _N_MMCSEM  </TD><TD> -          </TD><TD> -          </TD><TD> _N_DELETO  </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> _N_TMMVTL  </TD><TD> -          </TD><TD> -          </TD></TR>
    <TR><TD> SlTmQCmd::unloadToolFromMagAsync()                 </TD><TD> _N_MMCSEM  </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> _N_TMMVTL  </TD><TD> -          </TD><TD> -          </TD></TR>
    <TR><TD> -                                                  </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD></TR>
    <TR><TD> SlTmQCmd methods, part 2                           </TD><TD> PI-Service </TD><TD> PI-Service </TD><TD> PI-Service </TD><TD> PI-Service </TD><TD> PI-Service </TD><TD> PI-Service </TD><TD> PI-Service </TD><TD> PI-Service </TD><TD> PI-Service </TD><TD> PI-Service </TD></TR>
    <TR><TD> SlTmQCmd::writeDataSync()                          </TD><TD> -          </TD><TD> _N_SETUDT  </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD></TR>
    <TR><TD> SlTmQCmd::setDNosToZeroAsync()                     </TD><TD> -          </TD><TD> -          </TD><TD> _N_DZERO_  </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD></TR>
    <TR><TD> SlTmQCmd::checkDNosAsync()                         </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> _N_CHEKDM  </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD></TR>
    <TR><TD> SlTmQCmd::activateWearGroupAsync()                 </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> _N_TMAWCO  </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD></TR>
    <TR><TD> SlTmQCmd::setToolStateAsync()                      </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> _N_SETTST  </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD></TR>
    <TR><TD> SlTmQCmd::checkDNosAndActivateAsync()              </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> _N_CHEKDM  </TD><TD> _N_TMAWCO  </TD><TD> _N_SETTST  </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD><TD> -          </TD></TR>
  </TABLE>
  <TR><TD><b>Short explanation of NC-PI-Services</b>
  </TD></TR>
  <TABLE>
    <TR><TD> Explanation                                                   </TD><TD> PI-Service </TD></TR>
    <TR><TD> MMC-Semaphore                                                 </TD><TD> _N_MMCSEM  </TD></TR>
    <TR><TD> Creates a cutting edge by specifying an edge no.              </TD><TD> _N_CRCEDN  </TD></TR>
    <TR><TD> Deletes a cutting egde                                        </TD><TD> _N_DELECE  </TD></TR>
    <TR><TD> Deletes tool                                                  </TD><TD> _N_DELETO  </TD></TR>
    <TR><TD> Searches for empty location inside mulitool                   </TD><TD> _N_FDPLMT  </TD></TR>
    <TR><TD> Positions a multitool (inside toolholder)                     </TD><TD> _N_POSMT_  </TD></TR>
    <TR><TD> Creates multitool                                             </TD><TD> _N_TMCRMT  </TD></TR>
    <TR><TD> Creates tool with specified edge number                       </TD><TD> _N_TMCRTC  </TD></TR>
    <TR><TD> Deletes multitool                                             </TD><TD> _N_TMDLMT  </TD></TR>
    <TR><TD> Searches an empty place for loading by (multi-)tool           </TD><TD> _N_TMFDPL  </TD></TR>
    <TR><TD> Searches for empty location by properties                     </TD><TD> _N_TMFPBP  </TD></TR>
    <TR><TD> Loads, unloads or relocates a (multi-)tool                    </TD><TD> _N_TMMVTL  </TD></TR>
    <TR><TD> Activates data changes in NC during NC program activity       </TD><TD> _N_SETUDT  </TD></TR>
    <TR><TD> Positions a magazine or (multi-)tool                          </TD><TD> _N_TMPOSM  </TD></TR>
    <TR><TD> Reactivates (multi-)tool, Resets monitoring values            </TD><TD> _N_TRESMO  </TD></TR>
    <TR><TD> Sets value of optDNo of every tool edge to 0                  </TD><TD> _N_DZERO_  </TD></TR>
    <TR><TD> Checks D numbers                                              </TD><TD> _N_CHEKDM  </TD></TR>
    <TR><TD> Activates wear group                                          </TD><TD> _N_TMAWCO  </TD></TR>
    <TR><TD> Sets or resets tools "active" state in wear group context     </TD><TD> _N_SETTST  </TD></TR>
  </TABLE>
</TABLE>
\n
\cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
<TABLE>
  <TR><TD><b>sltmservice internal OPI / BTSS data items</b> \n
          \n
          Further data is important for OPERATEs (HMI SolutionLines) toolmanagement: \n
          devices sizes of NCs data: \n
\code
// sltmservice internal:
SlTmSysDeviceSize SlTmStore::rConstSys().rConstDeviceColl().rConstDevice(devNo).rConstDeviceSize().val(SlTmSysDeviceSize::SysDeviceSizeIdxEnum);
\endcode
  </TD></TR>
</TABLE>
\n
<!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

 
 <!-- not supported yet
not supported yet -->
 
<!--
-->
 
<!-- doxygen_should_skip_this
doxygen_should_skip_this -->
 
<!-- 
<TR><TD>   </TD></TR>
<TD>   </TD><TD>   </TD>

<TABLE> starts a table. 
</TABLE> ends a table. 
<TD> Starts a new table data element. 
</TD> Ends a table data element. 
<TR> Starts a new table row. 
</TR> Ends a table row. 
--> 
 
 <!-- doxygen_should_skip_this
      ALIASES                =  "doxygen_should_skip_this=\ifnot DOXYGEN_SHOULD_SKIP_THIS" \
                                "end_doxygen_should_skip_this=\endif" \
                                "doxygen_this_is_for_internal_use_only_and_hidden_in_oa_doc_co=\cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC" \
                                "end_doxygen_this_is_for_internal_use_only_and_hidden_in_oa_doc_co=\endcond" \
                                "doxygen_this_is_for_internal_use_only_and_hidden_in_oa_doc_if=\if DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC" \
                                "end_doxygen_this_is_for_internal_use_only_and_hidden_in_oa_doc_if=\endif" \
                                "#============================================================================================" \
                                "# doxygen_this_is_for_internal_use_only_and_hidden_in_oa_doc... and                          " \
                                "# DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC:                                " \
                                "#                                                                                            " \
                                "# cond via alias does not work;                                                              " \
                                "# if is limited to work within one comment only and does not span beteween comments;         " \
                                "# cond does its work well, spanning over all comments of a file and within comments too:     " \
                                "# So we solely use backslash_cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC " \
                                "# to mark all internal parts of source code.                                                 " \
                                "#                                                                                            " \
                                "#============================================================================================"
 doxygen_should_skip_this -->

 
\cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
\n
\n
This documentation has been made for internal use only. \n
It exclusively shows some parts, which are hidden in Open Architecture Documentation. \n
\n
\n
<!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

\cond DOXYGEN_THIS_IS_ALLWAYS_HIDDEN_IN_DOC
\n
This part of documentation should never be shown; \n
To do so, do NEVER insert ENABLED_SECTIONS = DOXYGEN_THIS_IS_ALLWAYS_HIDDEN_IN_DOC in doxconf file. \n
\n
<!-- DOXYGEN_THIS_IS_ALLWAYS_HIDDEN_IN_DOC --> \endcond


*/


class SlTmQRWLocker;


// ////////////////////////////////////////////////////////////////////////////
/*! 
\class  SlTmStore sltmstore.h
  \brief  This class contains tool and magazine and system data 
          of OPERATEs (HMI SolutionLines) Toolmanagement Service.
         
  This class holds data of classes:
  - QReadWriteLock             get pointer by SlTmStore::pReadWriteLock()           
  - SlTmToMaContainerColl   referenced by SlTmStore::rContainerColl()            
                                      and SlTmStore::rConstContainerColl()
  - SlTmSys                 referenced by SlTmStore::rSys()            
                                      and SlTmStore::rConstSys()
  - SlTmToMaLists           referenced by SlTmStore::rLists()            
                                      and SlTmStore::rConstLists()
  .

  SlTmSys contains system data from device (i.e. NC, Transline-PLC) and 
  in case of NC channel system data.
  Further this class contains SlTmToMaLists for access to sorted data.

  For writing and reading stores data (including all referenced contained data) 
  in our multi threaded environment, it is necessary
  to sequentialize access. 
  
  Therefore everybody must use stores 
  read write lock QReadWriteLock* SlTmStore.pReadWriteLock() 
  by a SlTmQRWLocker. See also \ref multithreading.
  

*/
class SL_TM_UTILITIES_EXPORT SlTmStore
{
public:
  // CREATORS 
  /// \brief constructor
  ///
  /// Number of Elements of contained data is set to 0.
  explicit SlTmStore();

  /// \brief copy constructor
  /// Exemption: SlTmToMaLists m_Lists: lists are NOT copied.
  SlTmStore(const SlTmStore& rSourceObj /*!< source object */);
  
  /// \brief destructor
  /// Exemption: SlTmToMaLists m_Lists: lists subscribers are NOT notified.
  virtual ~SlTmStore();
  
  
  // MANIPULATORS 

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmStore& rData)
  /// Exemption: SlTmToMaLists m_Lists: lists are NOT imported / exported.
  QDataStream& importData(
    QDataStream& rStream,               /*!< binary source stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  /// Exemption: SlTmToMaLists m_Lists: lists are NOT copied.
  SlTmStore& operator= (const SlTmStore& rSourceObj /*!< source object */
                       );
  
  /// \brief return pointer to read write lock of store 
  ///        to sequentalize multithreaded access
  /// 
  /// Never try to lock a QReadWriteLock more than one times 
  /// within one thread.
  /// Either read access or write access can be acquired, not both for same time.
  /// 
  /// Use a SlTmQRWLocker to use QReadWriteLock in your code.
  /// 
  /// See also \ref multithreading.
  QReadWriteLock*       pReadWriteLock(void);        
  
  /// \brief returns reference to container collection
  SlTmToMaContainerColl&    rContainerColl(void);        
  
  /// \brief returns reference to system data of connected devices
  SlTmSys&                  rSys(void);        
  
  /// \brief returns reference to lists (sorted data)
  SlTmToMaLists&            rLists(void);        
  
  /// \brief Announce containers, which containes changed data. 
  /// 
  /// In parameter \a rChangedContainerNoVector, a list of changed containers 
  /// has to be given as QVector.
  /// 
  /// This announcement is used by stores lists (see rLists()), 
  /// to keep track of changes, refresh lists 
  /// and notify list subscribers about changes.
  /// 
  /// This may ocour mostly synchronous within this method.
  /// 
  /// In later implementations it may be possible to anounce changes in
  /// finer granularity, i.e. tools and places.
  /// Therefore  signature of method is going to be extended.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int announceChangedData(
              SlTmQRWLocker&                             rStoresQRWLocker,    
                        ///< Read or Write Locker for Stores QReadWriteLock 
                        ///< for temporary unlock while giving control away
                        ///< (ie. during SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                        ///< and subsequent relock (usually via SlTmQRWTmpUnlocker).
              const bool&                                rIsCancelOrdered,    
                        ///< Verify this before starting long lasting computations,
                        ///< and before giving control away 
                        ///< (ie. SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                        ///< and after obtaining control back after relock.
                        ///< In case of (true == rIsCancelOrdered) return immediately by setting error return value.
              const SlTmToMaContainerNosValueVectorType& rChangedContainerNoVector, 
                        ///< all changed containerNo keys as QVector 
                        ///< of SlTmToMaContainerNoType container numbers 
              const bool                                 parDoExportEvenUnchangedData2 = true    
                        ///< Do send all list-connected data objects of list, not only IsChanged-marked one; \n
                        ///< Call is triggered by global changes like change of list parameters, \n
                        ///< not by individual data changes in (NC/Transline-PLC-)device; \n
                        ///< All data, not only changed one, must be send to subscriber \n
                        ///< Value \c false: export exclusively isChanged-marked list-connected data objects of list elements; \n
                        ///< Value \c true: export changed and unchanged list-connected data objects of list elements (default). \n
                        ///< Only relevant in case of SlTmMassData2ToolMagListChangedData, \n
                        ///< indicated by (SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA2 == \a massDataStreamCode) 
                         );

  /// \brief set trace counter
  void setStoreDataTracesToDoCounter( 
    const quint32 counter         ///< counter
                                    );

  /// \brief verify and decrement trace counter and give some info
  ///
  /// \retval true: do a trace output
  bool utilizeStoreDataTracesToDoCounter( 
    const bool doDecrement,        ///< decrement counter after
    QString&   rFileName           ///< recommended file name
                                        );
  
  /// \brief set trace counter
  void setListChangeNotifyTracesToDoCounter( 
    const quint32 counter        ///< counter
                                           );

  /// \brief verify and decrement trace counter and give some info
  ///
  /// \retval true: do a trace output
  bool utilizeListChangeNotifyTracesToDoCounter( 
    const bool doDecrement,        ///< decrement counter after
    QString&   rFileName           ///< recommended file name
                                               );
  
  /// \brief set trace counter
  void setListTracesToDoCounter( 
    const quint32 counter        ///< counter
                               );

  /// \brief verify and decrement trace counter and give some info
  ///
  /// \retval true: do a trace output
  bool utilizeListTracesToDoCounter( 
    const bool doDecrement,        ///< decrement counter after
    QString&   rFileName           ///< recommended file name
                                   );
  


  // ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmStore& rData)
  /// Attention: SlTmToMaLists are exported as text.
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmStore& rData)
  /// Exemption: SlTmToMaLists are NOT exported / imported.
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


  /// \brief returns const reference to container collection
  const SlTmToMaContainerColl&  rConstContainerColl(void) const;
  
  /// \brief returns const reference to system data of connected devices
  const SlTmSys&                rConstSys(void) const;        
  
  /// \brief returns const reference to lists (sorted data)
  const SlTmToMaLists&          rConstLists(void) const;        
  

  // FRIENDS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmStore& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmStore& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmStore& rData);

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// Exemption: SlTmToMaLists m_Lists: lists are NOT copied.
  ///
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmStore& rSourceObj /*!< source object */
                    );

  // ACCESSORS

  // MEMBER DATA
  QReadWriteLock                 m_ReadWriteLock;   ///< stores read write lock, 
                                                    ///< use it always when read or write stores data!
  SlTmToMaContainerColl          m_ContainerColl;   ///< container collection
  SlTmSys                        m_Sys;             ///< system data of all connected devices
  SlTmToMaLists                  m_Lists;           ///< lists of data  
  quint32 m_StoreAnnounceDataTracesToDoCounter;     ///< private trace of store to do counter
  quint32 m_ListChangeNotifyTracesToDoCounter;      ///< private trace of list changes to do counter
  quint32 m_ListTracesToDoCounter;                  ///< private trace of list to do counter
  void*                          m_Reserved;        // ... binary compatibility

};   

// FRIEND OPERATORS:
// MANIPULATORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator>> for data import to \a rData from binary QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Import to \a rData from binary \a rStream 
/// (contains int count and all member values as QVariants).
/// 
/// Stream data determinates number of member values.
/// 
/// If a stream element is not castable, corresponding member data is set to 0.
/// 
/// Exemption: SlTmToMaLists m_Lists: lists are NOT imported / exported.
SL_TM_UTILITIES_EXPORT QDataStream& operator>> (
                                    QDataStream& rStream,        /*!< binary data stream source */ 
                                    SlTmStore& rData             /*!< import target object */
                                               );


// ACCESSORS
/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,              /*!< text data stream target */ 
                                    const SlTmStore& rData             /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
/// Exemption: SlTmToMaLists m_Lists: lists are NOT imported / exported.
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,              /*!< binary data stream target */ 
                                    const SlTmStore& rData             /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

// end of class SlTmStore
// ////////////////////////////////////////////////////////////////////////////
#endif // !defined(SL_TM_STORE_H)
