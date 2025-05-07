///////////////////////////////////////////////////////////////////////////////
/*! \file	slomsdomcom.h
 *  \author Harald Amrehn
 *  \date   31.03.2015
 *  \brief	SlOmsDomAdapter interface
 *  This file is part of the OmsDomAdapter
 *  
 *  (C) Copyright Siemens AG MC R&D 2015. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SLOMSDOMCOM_H
#define SLOMSDOMCOM_H

#if defined(WIN32) || defined(WIN64)
#if defined (OMSDOMADAPTER_EXPORTS)
#define SLOMSDOMADAPTER __declspec (dllexport)
#else
#define SLOMSDOMADAPTER __declspec (dllimport)
#endif
#else
#define SLOMSDOMADAPTER
#endif

#include <string>
#include <vector>
#include "slomsdomenum.h"

#define SLOMSDOMCOM_ADAPTER_NAME             "OmsDomAdapter"
#define SLOMSDOM_GET_INST_OF_SLOMSDOMCOM     "_SlGetInstOfSlOmsDomCom@0"
#define SLOMSDOM_DELETE_INST_OF_SLOMSDOMCOM  "_SlDeleteInstOfSlOmsDomCom@4"


class SlOmsDomCom_Privat;
class SlOmsDomComCallbackInterface;


class SLOMSDOMADAPTER SlOmsDomCom
{
public:
  SlOmsDomCom();
  virtual ~SlOmsDomCom();

  virtual long init();
  virtual long fini();

  virtual long execute(/*in*/SlOmsDomFctId lFctId,
               /*in*/const std::vector<std::string>& rstrlstInParam,
               /*out*/std::vector<std::string>& rstrlstOut);
  virtual long executeAsync(/*in*/SlOmsDomFctId lFctId,
                    /*in*/const std::vector<std::string>& rstrlstInParam,
                    /*in*/SlOmsDomComCallbackInterface* pCallBack,
                    /*out*/long& lRequestId);
  virtual long cancel(long lRequestID);
  virtual void unregisterCallback(SlOmsDomComCallbackInterface* pCallBack);

private:
  long getLastRequestId(void);
  void appendRequestIdToList (long lRequestID);
  void deleteRequestIdFromList (long lRequestID);
  void setRequestId (long lRequestId, long lRet);
  void resetRequestId (long lRequestId);
  void appendRequestIdToMap (long lRequestId, SlOmsDomComCallbackInterface* pCallBack);
  void deleteRequestIdFromMap (long lRequestId);
  void deleteCallBackFromMap (SlOmsDomComCallbackInterface* pCallBack);
  SlOmsDomComCallbackInterface* getCallBackFromMap(long lRequestId);
  void setRequestIdToMap (long lRequestId, SlOmsDomComCallbackInterface* pCallBack, long lRet);
  void resetRequestIdFromMap (long lRequestId);
  void onCompleted(long lRequestId, long lRet, std::vector<std::string>& rstrlstOut);
  void onRequestCanceled(long lRequestId);
  void onProgress(long lRequestId, long lPercentageDone, std::string& rstrText);

  friend class SlOmsDomComSinkImpl;
  SlOmsDomCom_Privat* m_pData;
};


class SlOmsDomComCallbackInterface
{
public:
  SlOmsDomComCallbackInterface() : m_pIF(0) {};
  SlOmsDomComCallbackInterface(SlOmsDomCom* pIF) : m_pIF(pIF) {};
  virtual ~SlOmsDomComCallbackInterface() {if (0 != m_pIF) m_pIF->unregisterCallback(this);};

  virtual void completed(/*in*/long lRet, /*in*/std::vector<std::string>& rstrlstOut) {};
  virtual void canceled(void) {};
  virtual void progress(/*in*/long lPercentageDone,/*in*/std::string& rstrText) {};

  void setIF(SlOmsDomCom* pIF) {m_pIF = pIF;};

private:
  SlOmsDomCom* m_pIF;
};


#if defined(WIN32) || defined(WIN64)
// creator pattern, needed for dynamical link
extern "C"
{
  SLOMSDOMADAPTER SlOmsDomCom* WINAPI SlGetInstOfSlOmsDomCom(void); /*!< Creates an instance
                                                                         of SlOmsDomCom and
                                                                         returns the pointer
                                                                         to this instance */

  SLOMSDOMADAPTER void WINAPI SlDeleteInstOfSlOmsDomCom(SlOmsDomCom* pOmsDomCom); // deletes an instance of SlOmsDomCom
}
#endif

#endif
