///////////////////////////////////////////////////////////////////////////////
/*! \file	slomsdom.h
 *  \author Harald Amrehn
 *  \date   31.03.2015
 *  \brief	SlOmsDomAdapter interface
 *  This file is part of the OmsDomAdapter
 *  
 *  (C) Copyright Siemens AG MC R&D 2015. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SLOMSDOM_H
#define SLOMSDOM_H

#if defined(WIN32) || defined(WIN64)
#if defined (OMSDOMADAPTER_EXPORTS)
#define SLOMSDOMADAPTER __declspec (dllexport)
#else
#define SLOMSDOMADAPTER __declspec (dllimport)
#endif
#else
#define SLOMSDOMADAPTER
#endif

#define SLOMSDOM_ADAPTER_NAME             "OmsDomAdapter"
#define SLOMSDOM_GET_INST_OF_SLOMSDOM     "_SlGetInstOfSlOmsDom@0"
#define SLOMSDOM_DELETE_INST_OF_SLOMSDOM  "_SlDeleteInstOfSlOmsDom@4"
#define SLOMSDOM_SLOMSDOM_INIT            "_SlOmsDomInit@4"
#define SLOMSDOM_SLOMSDOM_FINI            "_SlOmsDomFini@4"
#define SLOMSDOM_SLOMSDOM_BACKUP          "_SlOmsDomBackup@12"
#define SLOMSDOM_SLOMSDOM_RESTORE         "_SlOmsDomRestore@12"


class SlOmsDom_Privat;
class SlOmsDomCallbackInterface;
class SlOmsDomCom;


class SLOMSDOMADAPTER SlOmsDom
{
public:
  SlOmsDom();
  virtual ~SlOmsDom();

  virtual long init();
  virtual long fini();

  virtual long backup(/*in*/const char* szTarget,
                      /*in*/const char* szAbsFile);

  virtual long backupAsync(/*in*/const char* szTarget,
                           /*in*/const char* szAbsFile,
                           /*in*/SlOmsDomCallbackInterface* pCallBack,
                           /*out*/long& lRequestId);

  virtual long restore(/*in*/const char* szTarget,
                       /*in*/const char* szAbsFile);

  virtual long restoreAsync(/*in*/const char* szTarget,
                            /*in*/const char* szAbsFile,
                            /*in*/SlOmsDomCallbackInterface* pCallBack,
                            /*out*/long& lRequestId);

  virtual long start(/*in*/const char* szTarget);

  virtual long startAsync(/*in*/const char* szTarget,
                          /*in*/SlOmsDomCallbackInterface* pCallBack,
                          /*out*/long& lRequestId);

  virtual long stop(/*in*/const char* szTarget);

  virtual long stopAsync(/*in*/const char* szTarget,
                         /*in*/SlOmsDomCallbackInterface* pCallBack,
                         /*out*/long& lRequestId);

  virtual long state(/*in*/const char* szTarget,
                     /*out*/int& rnState,
                     /*out*/std::string& rszState);

  /* 
  returns PLC state in completedWithData() of SlOmsDomCallbackInterface:
  rstrlstOut[0]: std::string OMSDOM_FCT_STATE as number
  rstrlstOut[1]: std::string state as number, see state()
  rstrlstOut[2]: std::string state as text
  */
  virtual long stateAsync(/*in*/const char* szTarget,
                          /*in*/SlOmsDomCallbackInterface* pCallBack,
                          /*out*/long& lRequestId);

  virtual long cancel(long lRequestID);

  static void unregisterCallback(void* pIF);

  SlOmsDomCom* m_pOmsDomCom;

protected:
  SlOmsDom_Privat* m_pData;
};


class SLOMSDOMADAPTER SlOmsDomPw
{
public:
  SlOmsDomPw();
  virtual ~SlOmsDomPw();

  virtual long init();
  virtual long fini();

  virtual long backup(/*in*/const char* szTarget,
                      /*in*/const char* szAbsFile,
                      /*in*/const char* szPassword);

  virtual long backupAsync(/*in*/const char* szTarget,
                           /*in*/const char* szAbsFile,
                           /*in*/const char* szPassword,
                           /*in*/SlOmsDomCallbackInterface* pCallBack,
                           /*out*/long& lRequestId);

  virtual long restore(/*in*/const char* szTarget,
                       /*in*/const char* szAbsFile,
                       /*in*/const char* szPassword);

  virtual long restoreAsync(/*in*/const char* szTarget,
                            /*in*/const char* szAbsFile,
                            /*in*/const char* szPassword,
                            /*in*/SlOmsDomCallbackInterface* pCallBack,
                            /*out*/long& lRequestId);

  virtual long start(/*in*/const char* szTarget,
                     /*in*/const char* szPassword);

  virtual long startAsync(/*in*/const char* szTarget,
                          /*in*/const char* szPassword,
                          /*in*/SlOmsDomCallbackInterface* pCallBack,
                          /*out*/long& lRequestId);

  virtual long stop(/*in*/const char* szTarget,
                    /*in*/const char* szPassword);

  virtual long stopAsync(/*in*/const char* szTarget,
                         /*in*/const char* szPassword,
                         /*in*/SlOmsDomCallbackInterface* pCallBack,
                         /*out*/long& lRequestId);

  virtual long state(/*in*/const char* szTarget,
                     /*in*/const char* szPassword,
                     /*out*/int& rnState,
                     /*out*/std::string& rszState);

  /* 
  returns PLC state in completedWithData() of SlOmsDomCallbackInterface:
  rstrlstOut[0]: std::string OMSDOM_FCT_STATE as number
  rstrlstOut[1]: std::string state as number, see state()
  rstrlstOut[2]: std::string state as text
  */
  virtual long stateAsync(/*in*/const char* szTarget,
                          /*in*/const char* szPassword,
                          /*in*/SlOmsDomCallbackInterface* pCallBack,
                          /*out*/long& lRequestId);

  virtual long protectionInfo(/*in*/const char* szTarget,
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
  virtual long protectionInfoAsync(/*in*/const char* szTarget,
                                   /*in*/SlOmsDomCallbackInterface* pCallBack,
                                   /*out*/long& lRequestId);

  virtual long checkPassword(/*in*/const char* szTarget,
                             /*in*/const char* szPassword,
                             /*out*/bool& rbPasswordOk);

  /* 
  returns if password is correct in completedWithData() of SlOmsDomCallbackInterface:
  rstrlstOut[0]: std::string OMSDOM_FCT_CHECKPASSW as number
  rstrlstOut[1]: std::string password correct flag as number, 0 for false, not 0 for true
  */
  virtual long checkPasswordAsync(/*in*/const char* szTarget,
                                  /*in*/const char* szPassword,
                                  /*in*/SlOmsDomCallbackInterface* pCallBack,
                                  /*out*/long& lRequestId);

  virtual long cancel(long lRequestID);

  static void unregisterCallback(void* pIF);

  SlOmsDomCom* m_pOmsDomCom;

protected:
  SlOmsDom_Privat* m_pData;
};


class SlOmsDomCallbackInterface
{
public:
  SlOmsDomCallbackInterface() : m_pIF(0) {};
  virtual ~SlOmsDomCallbackInterface() {if (0 != m_pIF) {SlOmsDomPw::unregisterCallback(m_pIF); setIF(0);}};

  virtual void completed(/*in*/long lRet) {};
  virtual void completedWithData(/*in*/long lRet,/*in*/std::vector<std::string>& rstrlstOut) {};
  virtual void canceled(void) {};
  virtual void progress(/*in*/long lPercentage,/*in*/const char* szText) {};

  void setIF(void* pIF) {m_pIF = pIF;};

private:
  void* m_pIF;
};


class SLOMSDOMADAPTER SlOmsDomPwCallbackInterface : public SlOmsDomCallbackInterface
{
public:
  SlOmsDomPwCallbackInterface() {};
  virtual ~SlOmsDomPwCallbackInterface() {};

  // derived from SlOmsDomCallbackInterface:
  //  virtual void completed(/*in*/long lRet)
  //  virtual void completedWithData(/*in*/long lRet,/*in*/std::vector<std::string>& rstrlstOut)
  //  virtual void canceled(void)
  //  virtual void progress(/*in*/long lPercentage,/*in*/const char* szText)

  // default implementation of completedWithData:
  // checks vector rstrlstOut[0] and calls completed, completedState, completedProtectionInfo, completedCheckPassword or completedUnknownData
  virtual void completedWithData(/*in*/long lRet,/*in*/std::vector<std::string>& rstrlstOut);
  virtual void completedState(/*in*/long lRet,/*in*/ int nState,/*in*/ const char* szState) {};
  virtual void completedProtectionInfo(/*in*/long lRet,/*in*/ int nProtectionLevel,/*in*/ bool bFailsafe,/*in*/ bool bPasswordNeeded) {};
  virtual void completedCheckPassword(/*in*/long lRet,/*in*/ bool bPasswordOk) {};
  virtual void completedUnknownData(/*in*/long lRet,/*in*/std::vector<std::string>& rstrlstOut) {};
};


#if defined(WIN32) || defined(WIN64)
// creator pattern, needed for dynamical link
extern "C"
{
  SLOMSDOMADAPTER SlOmsDom* WINAPI SlGetInstOfSlOmsDom(void); /* creates an instance
                                                                 of SlOmsDom and
                                                                 returns the pointer
                                                                 to this instance */

  SLOMSDOMADAPTER void WINAPI SlDeleteInstOfSlOmsDom(SlOmsDom* pOmsDom); // deletes an instance of SlOmsDom

  SLOMSDOMADAPTER long WINAPI SlInitOfSlOmsDom(/*in*/SlOmsDom* pOmsDom); // init of SlOmsDom

  SLOMSDOMADAPTER long WINAPI SlFiniOfSlOmsDom(/*in*/SlOmsDom* pOmsDom); // fini of SlOmsDom

  SLOMSDOMADAPTER long WINAPI SlOmsDomBackup(/*in*/SlOmsDom* pOmsDom,
                                             /*in*/const char* szTarget,
                                             /*in*/const char* szAbsFile); // calls pOmsDom->backup(szTarget,szAbsFile)

  SLOMSDOMADAPTER long WINAPI SlOmsDomRestore(/*in*/SlOmsDom* pOmsDom,
                                              /*in*/const char* szTarget,
                                              /*in*/const char* szAbsFile); // calls pOmsDom->restore(szTarget,szAbsFile)

  SLOMSDOMADAPTER long WINAPI SlOmsDomStart(/*in*/SlOmsDom* pOmsDom,
                                           /*in*/const char* szTarget); // calls pOmsDom->start(szTarget)

  SLOMSDOMADAPTER long WINAPI SlOmsDomStop(/*in*/SlOmsDom* pOmsDom,
                                           /*in*/const char* szTarget); // calls pOmsDom->stop(szTarget)
}
#endif

#endif

