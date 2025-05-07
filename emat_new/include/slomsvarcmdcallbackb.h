
///////////////////////////////////////////////////////////////////////////////
/*! \file   slomsvarcmdcallbackb.h
 *  \author Com & Diag Team
 *  \date   08.2015
 *  \brief  Header file for class SlOmsVarCmdCallBackB
 *
 *  This file is part of the HMI Solutionline SlOmsVar
 *
 *  This file has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
 *
 *  (C) Copyright Siemens AG DF MC 2015. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_OMSVAR_CMD_CALLBACK_B_H)
#define SL_OMSVAR_CMD_CALLBACK_B_H

//#include "ace/OS.h"

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QEvent>
#include <QtCore/QBitArray>
#include <QtCore/QVector>
#include <QtCore/QMap>
#include <QtCore/QMutex>

#include "slhmitemplatesqt.h"
#include "slomsvarstreamtypes.h"

#if !defined (SL_OMSVAR_CMD_EXPORT)
#  if defined (WIN32) || defined (WIN64)
#     if defined (SL_OMSVAR_CMD_EXPORTS)
#        define SL_OMSVAR_CMD_EXPORT __declspec (dllexport)
#     else
#        define SL_OMSVAR_CMD_EXPORT __declspec (dllimport)
#     endif
#  else
#      define SL_OMSVAR_CMD_EXPORT
#  endif
#endif


class SlOmsVarCmd;
class SlOmsVarCmdCallBackBPrivate;

/*! 
  \class  SlOmsVarCmdCallBackB slomsvarcmdcallbackb.h
  \brief  This base class is used as interface for implementation of classes 
          which contain client's callback functions, needed by SlOmsVarCmd-functions
          to notify asynchronous results. \n
          This class has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
    
  To receive the results of asynchronous SlOmsVarCmd-functions a client develops it's own 
  implementation of needed methods derived from SlOmsVarCmdCallBackB.
  For each asynchronous function SlOmsVarCmd-object calls back client using a special
  function ...Notification() inside client's own implementation.
  
  So that client has to do only Notification-implementations for used SlOmsVarCmd-functions
  this class is not pure vitual.
  So for not used SlOmsVarCmd-functions dummy function bodies are provided in this class.
  
  Client must give back control very soon, because for each process there's only
  one callback-thread for all clients using the SlOmsVarCmd-interface.
  
  All callback objects for asyn. action (and its comand objects) must be \n
  created on heap by new and \n
  deleted by SlOmsVarCmd::doCoordinatedDeleteOfCmdAndRelatedCbObject() \n
  after unsubscribe action SlOmsVarCmd::dataChangeUnsubscribe() \n
  to prevent destruction while callback is in action \n
  which would cause a crash.

  \n
  Please pay attention to: \ref delayedupdate 
  \n
  \n
  
 */ 
class SL_OMSVAR_CMD_EXPORT SlOmsVarCmdCallBackB
{
public:

  /// \brief constructor
  SlOmsVarCmdCallBackB(void);
  SlOmsVarCmdCallBackB(const QString& rNameOfClient);

  /// \brief destructor
  virtual ~SlOmsVarCmdCallBackB(void);



  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief  Get reference to QMutex for management of asynchronous actions and related objects.
  /// 
  ///  This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  /// 
  /// \retVal reference of QMutex
  QMutex& rAsyncActionRMutex(
                               bool* pIsRefOK ///< if false: returned reference is invalid, do not use returned reference
                            );

  void isCallBackInAction(bool val);             ///< set value: is a callback (within clients implementation of dataChangeNotification) in action. This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  bool isCallBackInAction(void) const;           ///< get value: is a callback (within clients implementation of dataChangeNotification) in action. This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.

  void isCoordinatedDeleteToDo(bool val);        ///< set value: do delete call back object after call back notify has finished. This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  bool isCoordinatedDeleteToDo(void) const;      ///< get value: do delete call back object after call back notify has finished. This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.

  bool doCoordinatedDelete(void);                ///< delete object or mark it as to delete if callback in action. Returns true if immediately deleted. This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


 /*! 
  *  \brief  Asynchronous result of dataChangeSubscribe()
  *          Clients implemented callback function must give back control very soon.
  *
  *  As there is no locking mechanism involved, client is not allowed to access \n
  *  callback data outside of it's callback function or even in an other thread than call back thread. \n
  *  If client needs to access data outside of call back thread, \n
  *  a lock guarded copy of data must be made within callback function.
  * 
  */
  virtual void dataChangeNotification(
                  SlOmsVarCmd& rCmdObj,  ///< reference to command-object SlOmsVarCmd
                  const SlOmsVarDataChangeSubscribeResultVectorType& rVecDataChangeSubscribeResult,
                                         ///< in: vector of type ::SlOmsVarDataChangeSubscribeResultVectorType \n
                                         ///< containing result data for dataChangeSubscribe
                  int cmdState           ///< actual state of command (cmdState) \n
                                         ///< SlOmsVarFuncDef::STATE_ACTIVE = is active \n
                                         ///< SlOmsVarFuncDef::STATE_END_OK = has finished \n
                                         ///< SlOmsVarFuncDef::STATE_END_ERROR = has finished with an error \n
                                         ///< SlOmsVarFuncDef::DATA_ERROR = subscription with error, data invalid
                                     );

private:

  SlOmsVarCmdCallBackBPrivate* m_pCbPrivate;



  // copy constructor not allowed
  SlOmsVarCmdCallBackB(const SlOmsVarCmdCallBackB& rCopy);

  // assignment operator not allowed
  SlOmsVarCmdCallBackB& operator=(const SlOmsVarCmdCallBackB& rCopy);

  // returns name of client (owner of SlOmsVarCmd-object) 
  QString nameOfClient() const;


};
#endif // !defined(Sl_OMSVAR_CMD_CALLBACK_B_H)


