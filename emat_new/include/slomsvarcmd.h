
// /////////////////////////////////////////////////////////////////////////////
/*! \file   slomsvarcmd.h
 *  \author Com & Diag Team
 *  \date   21.07.2015
 *  \brief  Header file for class SlOmsVarCmd
 *
 *  This file is part of the HMI Solutionline SlOmsVar
 *
 *  (C) Copyright Siemens AG DF MC 2015. All rights reserved.
 */
// /////////////////////////////////////////////////////////////////////////////

#if !defined(SL_OMSVAR_CMD_H)
#define SL_OMSVAR_CMD_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QEvent>
#include <QtCore/QBitArray>
#include <QtCore/QVector>
#include <QtCore/QMap>
#include <QtCore/QMutex>

#include "slhmitemplatesqt.h"
#include "slomsvarstreamtypes.h"
#include "slomsvarcmdcallbackb.h"

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


class SlOmsVarCmdPrivate;
class SlOmsVarQMutexLocker;

/*! 
  \class SlOmsVarCmd slomsvarcmd.h
  \brief This is the documentation of the lightweight client user interface SlOmsVarCmd \n
         (which belongs to slomsvaradapter). \n
         It exists to prevent client from dealing with slomsvaradapter \n
         and to make access to slomsvarsvc easier.

  SlOmsVarCmd offers an interface which allows client to call it from within a free thread, not only from within QtMainThread.

  Client must implement it's own call back class, derived from base class SlOmsVarCmdCallBackB 
  to receive the asynchronous results by callback functions defined in class SlOmsVarCmdCallBackB.
  
  Using SlOmsVarCmd, client can e.g.
  - xxxx
  - yyyy
  .
  
  To avoid problems please pay attention to the following rules:
  - To avoid blocking the callback thread, client is asked to return from callback functions very quickly.
  - Whenever deleting SlOmsVarCmd objects, the following order is mendatory: \n
    first delete SlOmsVarCmd object and then objects whose pointers have been passed to this SlOmsVarCmd object \n
    (mainly SlOmsVarCmdCallBackB object). \n
    And don't forget to unadvise ... before deleting a SlOmsVarCmd object, which has been used for an advise. \n
  - Each SlOmsVarCmd-object needs it's own callback.object! \n
  - If a SlOmsVarCmd-object is active with an asynchronous function (if an asynchronous function of SlOmsVarCmd object has been started), \n
    it mustn't be used to call a further function! \n
    To check for an activity you can use SlOmsVarCmd::isActive(). If this returns false, SlOmsVarCmd object may be used again.
  - All comand objects for asyn. action (and its callback objects) must be \n
    created on heap (by new) and \n
    deleted by doCoordinatedDeleteOfCmdAndRelatedCbObject() after unsubscribe action \n
    to prevent destruction while callback is in action \n
    which would cause a crash.
  .
  
  
  To use the SlOmsVarCmd interface, \n
  the client must implement it's own (from SlOmsVarCmdCallBackB derived) callback class \n
  for asynchronously receiving results of called SlOmsVarCmd-Commands:
  
  
  \code
  ;// for example
  class ClientOmsVarCmdCallBack : public SlOmsVarCmdCallBackB
  {
    public:
       // creators ...
       // ...
       virtual void dataChangeNotification(...);
 
  \endcode
      
  Furthermore client must create SlOmsVarCmd-objects and ClientOmsVarCmdCallBack-objects. \n
  All communication with slomsvarsvc will be done via these objects.
  
  \code
  ;// for example
  SL_NEW_NORETURN(m_pDataChangeSubscriberOmsVarCmdCallBack, ClientOmsVarCmdCallBack(...));
  SL_NEW_NORETURN(m_pDataChangeSubscriberOmsVarCmd, SlOmsVarCmd(m_pDataChangeSubscriberOmsVarCmdCallBack, QString("NameOfCLient"));
  ;// ...
  ;// also possible SL_NEW_RETURN(...) or SL_NEW(...)
  \endcode  
  

  (C) Copyright Siemens AG DF MC 2015. All rights reserved.
  
*/
class SL_OMSVAR_CMD_EXPORT SlOmsVarCmd
{    
public:
  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
 
  /// \brief constructor for sync. read or write and with name of client
  SlOmsVarCmd(const QString& rNameOfClient);
  
  /// \brief constructor for asyn. action like dataChangeSubscribe() and with name of client 
  /// 
  /// Restriction: All comand objects for asyn. action (and its callback objects) must be \n
  ///              created on heap (by new ...) and \n
  ///              must be deleted by doCoordinatedDeleteOfCmdAndRelatedCbObject() after unsubscribe action \n
  ///              to prevent destruction while callback is in action \n
  ///              which would cause a crash.
  SlOmsVarCmd(SlOmsVarCmdCallBackB* pCBObjClient, QString& rNameOfClient);

  /// \brief destructor
  virtual ~SlOmsVarCmd(void);
  
  ///////////////////////////////////////////////////////////////////////////
  // MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////

  
  ///////////////////////////////////////////////////////////////////////////
  // ACCESSORS
  ///////////////////////////////////////////////////////////////////////////

  /// \brief This function allows the user of \a SlOmsVarCmd to ask if the \a SlOmsVarCmd-Object is active
  /// 
  /// \retval \a true if command-object is active, \a false if not
  bool isActive() const;

  /// \brief  function reads a single value from a PLC variable
  /// 
  /// \retval long ::SL_ERR_SUCCESS if Ok, ::SL_ERR_FAIL or an error code if not 
  /// \ref syncErrors
  /// \n
  /// 
  /// \n
  /// \ref delayedupdate 
  /// \n
  /// \n
  /// 
  long read(
              const QString& target,         ///< IP Address of target PLC
              const QString& varString,      ///< name of PLC variable to be read 
              QVariant& varValue             ///< value read from PLC variable
           );
  


  /// \brief  function reads multi values from PLC variables
  /// 
  /// \retval long ::SL_ERR_SUCCESS if Ok, ::SL_ERR_FAIL or an error code if not 
  /// \ref syncErrors
  /// \n
  /// 
  /// \n
  /// \ref delayedupdate 
  /// \n
  /// \n
  /// 
  long read(
            const QString& target,         ///< IP Address of target PLC
            SlOmsVarReadSpecVectorType& rReadSpecVec,  ///< in: vector of type ::SlOmsVarReadSpecType \n
                                                       ///< containing data specifications
            SlOmsVarReadResultVectorType& rReadResultVec    ///< out: vector of type ::SlOmsVarReadResultType \n
                                                            ///< containing result data
           );


  /// \brief  function writes a single value into a PLC variable
  /// 
  /// \retval long ::SL_ERR_SUCCESS if Ok, ::SL_ERR_FAIL or an error code if not 
  /// \ref syncErrors
  /// \n
  /// 
  /// \n
  /// \ref delayedupdate 
  /// \n
  /// \n
  /// 
  long write(
              const QString& target,         ///< IP Address of target PLC
              const QString& varString,      ///< name of PLC variable to be written
              const QVariant& varValue       ///< value to be written into PLC variable
           );

  /// \brief  function writes multi values into PLC variables
  /// 
  /// \retval long ::SL_ERR_SUCCESS if Ok, ::SL_ERR_FAIL or an error code if not 
  /// \ref syncErrors
  /// \n
  /// 
  /// \n
  /// \ref delayedupdate 
  /// \n
  /// \n
  /// 
  long write(
              const QString& target,         ///< IP Address of target PLC
              SlOmsVarWriteSpecVectorType& rWriteSpecVec,   ///< in/out: vector of type ::SlOmsVarWriteSpecType \n
                                                            ///< containing data specifications and value
              SlOmsVarWriteResultVectorType& rWriteResultVec  ///< out: vector of type ::SlOmsVarWriteResultType \n
                                                              ///< containing errorValues
             );


  /// \brief  function reads a single value from a PLC variable
  /// 
  ///         Pay Attentention: \n
  ///         This function exits only transitional and will be removed later
  ///
  /// \retval long ::SL_ERR_SUCCESS if Ok, ::SL_ERR_FAIL or an error code if not 
  /// \ref syncErrors
  /// \n
  /// 
  /// \n
  /// \ref delayedupdate 
  /// \n
  /// \n
  /// 
  long read(
              const QString& target,         ///< IP Address of target PLC
              const QString& varString,      ///< name of PLC variable to be read 
              QString& varValue              ///< value (inside QString) read from PLC variable
           );

  /// \brief  function writes a single value into a PLC variable
  /// 
  /// \retval long ::SL_ERR_SUCCESS if Ok, ::SL_ERR_FAIL or an error code if not 
  /// \ref syncErrors
  /// \n
  /// 
  /// \n
  /// \ref delayedupdate 
  /// \n
  /// \n
  /// 
  long write(
              const QString& target,         ///< IP Address of target PLC
              const QString& varString,      ///< name of PLC variable to be written
              const QString& varValue        ///< value (inside QString) to be written into PLC variable
            );


  /// \brief  Subscribe for data changes
  /// 
  /// \retval long ::SL_ERR_SUCCESS if Ok, ::SL_ERR_FAIL or an error code if not 
  /// \ref syncErrors
  /// \n
  /// 
  /// \n
  /// \ref delayedupdate 
  /// \n
  /// \n
  /// 
  long dataChangeSubscribe(
              SlOmsVarDataChangeSubscribeSpecVectorType& rVecDataChangeSubscribeSpec,
                                                                ///< in / out: vector of type ::SlOmsVarDataChangeSubscribeSpecType \n
                                                                ///< containing data specifications
              unsigned long timeout = 20000                     ///< timeout in msec
                          );


  /// \brief  Unsubscribe for data changes
  /// 
  /// \retval long ::SL_ERR_SUCCESS if Ok, ::SL_ERR_FAIL or an error code if not.
  /// 
  /// Attention: Even after returning from dataChangeUnsubscribe() or during dataChangeUnsubscribe() \n
  /// may happen a data change notification SlOmsVarCmdCallBackB::dataChangeNotification() via cb object, \n
  /// which has been invoked parallel to dataChangeUnsubscribe() (in other thread) or \n
  /// is caused by unsubscribe (stacked on same thread as unsubscribe). \n
  /// \n
  /// Immediately after returning from dataChangeUnsubscribe() \n
  /// it is possible to order deletion of SlOmsVarCmd cmd AND related SlOmsVarCmdCallBackB cb object via doCoordinatedDeleteOfCmdAndRelatedCbObject().
  /// \n
  /// \ref syncErrors
  /// \n
  /// 
  /// \n
  /// \ref delayedupdate 
  /// \n
  /// \n
  /// 
  long dataChangeUnsubscribe(void);



  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief  Get reference to QMutex for management of asynchronous actions and related objects
  /// 
  ///         This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
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

  /// \brief Delete SlOmsVarCmd cmd AND SlOmsVarCmdCallBackB cb object or \n
  ///        mark it as to delete after callback SlOmsVarCmdCallBackB::dataChangeNotification() \n
  ///        has returned from clients derived class implementation \n
  ///        if callback SlOmsVarCmdCallBackB::dataChangeNotification() is in action.
  /// 
  /// Attention: Do not forget to unsubscribe via dataChangeUnsubscribe() before. \n
  /// 
  /// Cb object is that one which has been given in constructor of cmd object SlOmsVarCmd(SlOmsVarCmdCallBackB* pCBObjClient, QString& rNameOfClient). \n
  /// 
  /// For proper shutdown of serviceadapter it is important to delete all cmd and cb objects before, 
  /// because they keep serviceadapter singleton at life by holding references to serviceadapter.
  /// 
  /// Delete of such cmd and cb objects who are in use of asynchronous action must not be done by direct delete 
  /// but by this methode doCoordinatedDeleteOfCmdAndRelatedCbObject().
  /// 
  ///  \retVal Returns true if cmd object and cb object have been immediately deleted.
  bool doCoordinatedDeleteOfCmdAndRelatedCbObject(void); 


  // /////////////////////////////////////////////////////////////////////////
  // NOTIFY-FUNCTIONS
  // /////////////////////////////////////////////////////////////////////////

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief  notify function for all functions started with allAsync(). \n
  ///         This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  void notifyAllAsync(
                       const int cmdState,                   ///< \a SlOmsVarFuncDef::STATE_ACTIVE = is active, \n
                                                             ///< \a SlOmsVarFuncDef::STATE_END_OK = is ready, \n
                                                             ///< \a SlOmsVarFuncDef::STATE_END_ERROR = is ready with an error, \n
                                                             ///< \a SlOmsVarFuncDef::STATE_DATA_ERROR = subscription with error, data are invalid
                       const int funcNo,                     ///< number of active function  
                       const int streamCode,                 ///< special info to use \a rBinDataFromService 
                       const QByteArray& rBinDataFromService,           ///< binary data, arrived from service 
                       SlOmsVarQMutexLocker& rAsyncActionRMutexLocker   ///< recursive mutex locker for unlocking during client notification
                     ); 
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

  ///////////////////////////////////////////////////////////////////////////
  // Event-Handling
  ///////////////////////////////////////////////////////////////////////////

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief  Perhaps needed later. \n
  ///         This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  virtual void customEvent(
                           QEvent* pCustomEvent   ///< pointer to an event object \a QEvent 
                          );


  /// \brief  Perhaps needed later. \n
  ///         This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  virtual bool event(
                     QEvent* pEvent               ///<  pointer to an event object \a QEvent 
                    );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

protected:
    ///////////////////////////////////////////////////////////////////////////
    // Protected Methods
    ///////////////////////////////////////////////////////////////////////////

private:
  SlOmsVarCmdCallBackB* m_pCBObjClient;         ///<  pointer to callback-object of client 
  int m_FuncNo;                                 ///<  code number of last function of command-object 
  int m_CmdState;                               ///<  state of last function of command-object 
  int m_CmdId;                                  ///<  commandID to identify an active command 
  // these parameters are important for this class and will ever exist,
  // therefore they are defined directly SlOmsVarCmd
  
  SlOmsVarCmdPrivate* m_pSlOmsVarCmdData;               /*!< pointer to private data */

  // copy constructor not allowed
  SlOmsVarCmd(const SlOmsVarCmd& rCopy);

  // assignment operator not allowed
  SlOmsVarCmd& operator=(const SlOmsVarCmd& rCopy);
  
  // returns name of client (owner of SlOmsVarCmd-object) 
  QString nameOfClient() const;

};

#endif // !defined(SL_TM_CMD_H)


