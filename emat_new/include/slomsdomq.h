///////////////////////////////////////////////////////////////////////////////
/*! \file	slomsdomq.h
 *  \author Harald Amrehn
 *  \date   31.03.2015
 *  \brief	SlOmsDomAdapter interface
 *  This file is part of the OmsDomAdapter
 *  
 *  (C) Copyright Siemens AG MC R&D 2015. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SLOMSDOMQ_H
#define SLOMSDOMQ_H

#if defined(WIN32) || defined(WIN64)
#if defined (OMSDOMADAPTER_EXPORTS)
#define SLOMSDOMADAPTER __declspec (dllexport)
#else
#define SLOMSDOMADAPTER __declspec (dllimport)
#endif
#else
#define SLOMSDOMADAPTER
#endif

#include "slomsdom.h"
#include <QtCore/QString>

#define SLOMSDOMQ_ADAPTER_NAME             "OmsDomAdapter"
#define SLOMSDOM_GET_INST_OF_SLOMSDOMQ     "_SlGetInstOfSlOmsDomQ@0"
#define SLOMSDOM_DELETE_INST_OF_SLOMSDOMQ  "_SlDeleteInstOfSlOmsDomQ@4"


class SLOMSDOMADAPTER SlOmsDomQ : public SlOmsDom
{
public:
  SlOmsDomQ();
  virtual ~SlOmsDomQ();

  virtual long backup(/*in*/const QString& strTarget,
                      /*in*/const QString& strAbsFile);

  virtual long backupAsync(/*in*/const QString& strTarget,
                           /*in*/const QString& strAbsFile,
                           /*in*/SlOmsDomCallbackInterface* pCallBack,
                           /*out*/long& lRequestId);

  virtual long restore(/*in*/const QString& strTarget,
                       /*in*/const QString& strAbsFile);

  virtual long restoreAsync(/*in*/const QString& strTarget,
                            /*in*/const QString& strAbsFile,
                            /*in*/SlOmsDomCallbackInterface* pCallBack,
                            /*out*/long& lRequestId);

  virtual long start(/*in*/const QString& strTarget);

  virtual long startAsync(/*in*/const QString& strTarget,
                          /*in*/SlOmsDomCallbackInterface* pCallBack,
                          /*out*/long& lRequestId);

  virtual long stop(/*in*/const QString& strTarget);

  virtual long stopAsync(/*in*/const QString& strTarget,
                         /*in*/SlOmsDomCallbackInterface* pCallBack,
                         /*out*/long& lRequestId);

  /* nState:
  NOT_SUPPORTED           = 0   Status ungueltig
  STOP_FW_UPDATE          = 1   PLC befindet sich im STOP wg. FW-Update
  STOP_SELFINITIALIZATION = 3   PLC im STOP waehrend der Selbstinitialisierung im Hochlauf
  STOP                    = 4   PLC im allgemeinen Zustand STOP
  STARTUP                 = 6   PLC befindet sich im Anlauf
  RUN                     = 8   PLC im allgemeinen Zustand RUN
  RUN_REDUNDANT           = 9   wird aktuell von AS noch nicht verwendet
  HALT                    = 10  PLC befindet sich im Zustand HALT (z.B. Debugger)
  RUNSYNCUP               = 11  wird aktuell von AS noch nicht verwendet
  SYNCUP                  = 12  wird aktuell von AS noch nicht verwendet
  DEFECTIVE               = 13  Defekt/Absturz
  ERROR_SEARCH            = 14  wird aktuell von AS noch nicht verwendet
  NOPOWER                 = 15  Betriebszustand "Spannungslos"
  CIR                     = 16  wird aktuell von AS noch nicht verwendet (Change in Run)
  STOP_WITHOUT_ODIS       = 17  PLC im Zustand STOP, ohne das die Ausgaenge abgeschaltet sind
  RUN_ODIS                = 18  PLC im Zustand RUN, aber die Ausgaenge sind abgeschaltet
  PGM_TEST                = 19  Testzustand fuer OMS+
  */
  virtual long state(/*in*/const QString& strTarget,
                     /*out*/int& rnState,
                     /*out*/QString& rstrState);

  /* 
  returns PLC state in completedWithData() of SlOmsDomCallbackInterface:
  rstrlstOut[0]: std::string OMSDOM_FCT_STATE as number
  rstrlstOut[1]: std::string state as number, see state()
  rstrlstOut[2]: std::string state as text
  */
  virtual long stateAsync(/*in*/const QString& strTarget,
                          /*in*/SlOmsDomCallbackInterface* pCallBack,
                          /*out*/long& lRequestId);
};


class SLOMSDOMADAPTER SlOmsDomPwQ : public SlOmsDomPw
{
public:
  SlOmsDomPwQ();
  virtual ~SlOmsDomPwQ();

  virtual long backup(/*in*/const QString& strTarget,
                      /*in*/const QString& strAbsFile,
                      /*in*/const QString& strPassword);

  virtual long backupAsync(/*in*/const QString& strTarget,
                           /*in*/const QString& strAbsFile,
                           /*in*/const QString& strPassword,
                           /*in*/SlOmsDomCallbackInterface* pCallBack,
                           /*out*/long& lRequestId);

  virtual long restore(/*in*/const QString& strTarget,
                       /*in*/const QString& strAbsFile,
                       /*in*/const QString& strPassword);

  virtual long restoreAsync(/*in*/const QString& strTarget,
                            /*in*/const QString& strAbsFile,
                            /*in*/const QString& strPassword,
                            /*in*/SlOmsDomCallbackInterface* pCallBack,
                            /*out*/long& lRequestId);

  virtual long start(/*in*/const QString& strTarget,
                     /*in*/const QString& strPassword);

  virtual long startAsync(/*in*/const QString& strTarget,
                          /*in*/const QString& strPassword,
                          /*in*/SlOmsDomCallbackInterface* pCallBack,
                          /*out*/long& lRequestId);

  virtual long stop(/*in*/const QString& strTarget,
                    /*in*/const QString& strPassword);

  virtual long stopAsync(/*in*/const QString& strTarget,
                         /*in*/const QString& strPassword,
                         /*in*/SlOmsDomCallbackInterface* pCallBack,
                         /*out*/long& lRequestId);

  /* nState:
  NOT_SUPPORTED           = 0   Status ungueltig
  STOP_FW_UPDATE          = 1   PLC befindet sich im STOP wg. FW-Update
  STOP_SELFINITIALIZATION = 3   PLC im STOP waehrend der Selbstinitialisierung im Hochlauf
  STOP                    = 4   PLC im allgemeinen Zustand STOP
  STARTUP                 = 6   PLC befindet sich im Anlauf
  RUN                     = 8   PLC im allgemeinen Zustand RUN
  RUN_REDUNDANT           = 9   wird aktuell von AS noch nicht verwendet
  HALT                    = 10  PLC befindet sich im Zustand HALT (z.B. Debugger)
  RUNSYNCUP               = 11  wird aktuell von AS noch nicht verwendet
  SYNCUP                  = 12  wird aktuell von AS noch nicht verwendet
  DEFECTIVE               = 13  Defekt/Absturz
  ERROR_SEARCH            = 14  wird aktuell von AS noch nicht verwendet
  NOPOWER                 = 15  Betriebszustand "Spannungslos"
  CIR                     = 16  wird aktuell von AS noch nicht verwendet (Change in Run)
  STOP_WITHOUT_ODIS       = 17  PLC im Zustand STOP, ohne das die Ausgaenge abgeschaltet sind
  RUN_ODIS                = 18  PLC im Zustand RUN, aber die Ausgaenge sind abgeschaltet
  PGM_TEST                = 19  Testzustand fuer OMS+
  */
  virtual long state(/*in*/const QString& strTarget,
                     /*in*/const QString& strPassword,
                     /*out*/int& rnState,
                     /*out*/QString& rstrState);

  /* 
  returns PLC state in completedWithData() of SlOmsDomCallbackInterface:
  rstrlstOut[0]: std::string OMSDOM_FCT_STATE as number
  rstrlstOut[1]: std::string state as number, see state()
  rstrlstOut[2]: std::string state as text
  */
  virtual long stateAsync(/*in*/const QString& strTarget,
                          /*in*/const QString& strPassword,
                          /*in*/SlOmsDomCallbackInterface* pCallBack,
                          /*out*/long& lRequestId);

  virtual long protectionInfo(/*in*/const QString& strTarget,
                              /*out*/int& rnProtectionLevel,
                              /*out*/bool& rbFailsafe,
                              /*out*/bool& rbPasswordNeeded);

  /* 
  returns PLC protection level, fail save state and if password is needed in completedWithData() of SlOmsDomCallbackInterface:
  rstrlstOut[0]: std::string OMSDOM_FCT_PROTINFO as number
  rstrlstOut[1]: std::string protection level as number
  rstrlstOut[2]: std::string fail save state as number, 0 for false, not 0 for true
  rstrlstOut[3]: std::string  password needed flag as number, 0 for false, not 0 for true
  */
  virtual long protectionInfoAsync(/*in*/const QString& strTarget,
                                   /*in*/SlOmsDomCallbackInterface* pCallBack,
                                   /*out*/long& lRequestId);

  virtual long checkPassword(/*in*/const QString& strTarget,
                             /*in*/const QString& strPassword,
                             /*out*/bool& rbPasswordOk);

  /* 
  returns if password is correct in completedWithData() of SlOmsDomCallbackInterface:
  rstrlstOut[0]: std::string OMSDOM_FCT_CHECKPASSW as number
  rstrlstOut[1]: std::string password correct flag as number, 0 for false, not 0 for true
  */
  virtual long checkPasswordAsync(/*in*/const QString& strTarget,
                                  /*in*/const QString& strPassword,
                                  /*in*/SlOmsDomCallbackInterface* pCallBack,
                                  /*out*/long& lRequestId);
};


#if defined(WIN32) || defined(WIN64)
// creator pattern, needed for dynamical link
extern "C"
{
  SLOMSDOMADAPTER SlOmsDomQ* WINAPI SlGetInstOfSlOmsDomQ(void); /*!< Creates an instance
                                                                     of SlOmsDomQ and
                                                                     returns the pointer
                                                                     to this instance */

  SLOMSDOMADAPTER void WINAPI SlDeleteInstOfSlOmsDomQ(SlOmsDomQ* pOmsDomQ); // deletes an instance of SlOmsDomQ
} 
#endif

#endif
