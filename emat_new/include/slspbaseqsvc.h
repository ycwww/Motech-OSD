///////////////////////////////////////////////////////////////////////////////
/*! \file   slspbaseqsvc.h
 *  \author Harald Amrehn
 *  \date   12.10.2006
 *  \brief  SlSpBaseQSvc interface
 *  This file is part of the solution line sp service
 *
 *  (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////


#ifndef SLSP_BASEQSVC_H_
#define SLSP_BASEQSVC_H_


#include "slspserviceadapter.h"


class SlSpBaseQSvc_Privat;

class SLSPSVCADAPTER SlSpBaseQSvc : public QObject
{
public:

  SlSpBaseQSvc();
  ~SlSpBaseQSvc();

  /*! \fn long init()
  *  \retval long Erfolgsstatus des Aufrufs, siehe slsperr.h.
  *
  *  Initialisierung des SlArchiveQSvc-Objekts.
  *  Diese Funktion ruft man immer als erstes auf.
  */
  long init();

  /*! \fn long fini()
  *  \retval long Erfolgsstatus des Aufrufs, siehe slsperr.h.
  *
  *  Ressourcenfreigabe des SlArchiveQSvc-Objekts. Diese Funktion ruft man
  *  immer als letztes auf.
  *  return-Wert siehe slsperr.h
  */
  long fini();

  /*! \fn long sendReply(long lRequestId, SlSpReply_Enum enumReply)
  *  \param lRequestId Handle zur Identifikation der asynchronen Operation.
  *  \param enumReply Folgende Antwortmoeglichkeiten stehen zur Verfuegung:
  *                   SLSP_ANSWER_YES - ja, fuer diese Frage
  *                   SLSP_ANSWER_YESALL - ja, fuer diese und alle folgenden
  *                                        Fragen
  *                   SLSP_ANSWER_NO - nein, fuer diese Frage
  *                   SLSP_ANSWER_NOALL - nein, fuer diese und alle folgenden
  *                                       Fragen.
  *  \retval long Erfolgsstatus des Aufrufs, siehe slsperr.h.
  *
  *  Die Funktion sendReply verwendet man in den folgenden Rueckfragen (Signalen) als
  *  Antwortfunktion:
  *   askReadArchive
  *   askOverwrite
  *   askNckVersionType
  *   askEvent.
  */
  long sendReply(/*in*/ long lRequestId,/*in*/ SlSpReply_Enum enumReply);

  /*! \fn long cancel(long lRequestId)
  *  \param lRequestId Handle zur Identifikation der asynchronen Operation.
  *  \retval long Erfolgsstatus des Aufrufs, siehe slsperr.h.
  *
  *  Einen asynchronen Aufruf kann man unter Angabe des entsprechenden Handle
  *  abbrechen. Die Fertigmeldung erfolgt mit Emittierung des Signals canceled.
  */
  long cancel(/*in*/ long lRequestId);

  void setRequestId(long lRequestId, long lRet);

  void resetRequestId(long lRequestId);

protected:
  SlSpServiceAdapter*   m_pSpService;
  SlSpIClient*          m_pSpClient;
  SlSfwOrbManager*      m_pSpORB;
  SlSpIServiceSinkImpl* m_pSpSink;
  bool                  m_bInit;
  SlSpBaseQSvc_Privat*  m_pData;

  friend class SlSpIServiceSinkImpl;
};

#endif
