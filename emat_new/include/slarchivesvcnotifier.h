/*! \file   slarchivesvcnotifier.h
 *  \author Harald Amrehn
 *  \date   22.02.2008
 *  \brief  Header file for SlArchiveSvcNotifier interface.
 *  This file is part of the solution line archive service.
 *
 *  (C) Copyright Siemens AG Industry A&D MC 2008. All rights reserved.
*/

#ifndef SLSP_ARCHIVESVCNOTIFIER_H_
#define SLSP_ARCHIVESVCNOTIFIER_H_

#include "slspserviceadapter.h"


struct SlArchiveSvcNotifierCallbackInterface
{
  // all parameters are of type "in"
  virtual void notify(SlSpFunctionCall_Enum enumCallState,
                      SlSpFunctionId_Enum enumFunctionId,
                      const QString& rstrInfo) {};
};


class SlArchiveSvcNotifier_Privat;

class SLSPSVCADAPTER SlArchiveSvcNotifier
{
public:
  SlArchiveSvcNotifier();
  virtual ~SlArchiveSvcNotifier();

  long init();
  long fini();

  long registerCallback(SlArchiveSvcNotifierCallbackInterface* pCallBack,
                        bool bAsync);
  long unregisterCallback(void);

protected:
  void notify(bool bCallState, long lFunctionId, const QString& rstrInfo);

  SlSpServiceAdapter*                    m_pSpService;
  SlSpIClientNotify*                     m_pSpClient;
  SlSpIServiceSinkNotifyImpl*            m_pSpSink;
  SlSfwOrbManager*                       m_pSpORB;
  bool                                   m_bInit;
  bool                                   m_bAsync;
  SlArchiveSvcNotifierCallbackInterface* m_pSpCallBack;
  SlArchiveSvcNotifier_Privat*           m_pData;

  friend class SlSpIServiceSinkNotifyImpl;
};


// creator pattern, needed for dynamical link
extern "C"
{
  SLSPSVCADAPTER SlArchiveSvcNotifier* SlEdGetInstOfSlArchiveSvcNotifier(void); /*!< Creates an instance
                                                                   of SlArchiveSvcNotifier and
                                                                   returns the pointer
                                                                   to this instance */
}

#endif
