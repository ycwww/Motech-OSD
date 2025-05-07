///////////////////////////////////////////////////////////////////////////////
/*! \file   sltmserviceadapter.h
 *  \author Ursula Hahn
 *  \date   02.2005
 *  \brief  Headerfile for class SlTmServiceAdapter
 *
 *  This file is part of the HMI Solutionline Toolmanagement
 *
 *  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_TM_SERVICE_ADAPTER_H)
#define SL_TM_SERVICE_ADAPTER_H

// #include <ace/svc_export.h>
// #if !defined (ACE_LACKS_PRAGMA_ONCE)
// #pragma once
// #endif /* ACE_LACKS_PRAGMA_ONCE */

#if !defined (SL_TM_SVC_ADAPTER_EXPORT)
#  if defined (WIN32) || defined (WIN64)
#     if defined (SL_TM_SVC_ADAPTER_EXPORTS)
#        define SL_TM_SVC_ADAPTER_EXPORT __declspec (dllexport)
#     else
#        define SL_TM_SVC_ADAPTER_EXPORT __declspec (dllimport)
#     endif
#  else
#      define SL_TM_SVC_ADAPTER_EXPORT
#  endif
#endif


#include <QtCore/QObject>

#include "slsfwserviceadapterptr.h"

class SlTmQCmd;
class SlTmCmd;
class SlTmInfo;
class SlTmAsyncCmdIdManager;
class SlTmClientStore;

class SlTmServiceAdapter;

/*! \template class SlSfwServiceAdapterPtr
 *  This is the forward definition
 */
// MOC_SKIP_BEGIN
template class SL_TM_SVC_ADAPTER_EXPORT SlSfwServiceAdapterPtr<SlTmServiceAdapter>;
// MOC_SKIP_END


/*! Smartpointer to the Serviceadapter. You should use this pointer instead of
 *  using the service class directly
*/
typedef SlSfwServiceAdapterPtr<SlTmServiceAdapter> SlTmServiceAdapterPtrType;


/*! \class SlTmServiceAdapter SlTmServiceAdapter.h
 *  \brief Serviceadapter of Toolmanagement
 *
*/
class SL_TM_SVC_ADAPTER_EXPORT SlTmServiceAdapter : public QObject
{
    Q_OBJECT

public:

    /*! \fn static int getObject(SlTmServiceAdapter*& rpAdapter);
     *  \param1 rpAdapter  a reference to the pointer to be filled with an 
     *                     instance of the SlTmServiceAdapter
     *  \retval int        errorcode, if an error occured, otherwise 0
     *
     *  This static function creates a SlTmServiceAdapter if non exists
     *  in the local process. There may only be one SlTmServiceAdapter in the
     *  process (process singleton).
    */
    static int getObject(SlTmServiceAdapter*& rpAdapter);

    /*! \fn static int releaseObject(SlTmServiceAdapter* pInstance);
     *  \param1 pInstance  instance of the SlTmServiceAdapter
     *  \retval int        errorcode, if an error occured, otherwise 0
     *
     *  This static function removes SlTmServiceAdapter if its the last
     *  reference in the local process.
    */
    static int releaseObject(SlTmServiceAdapter* pInstance);


    /// \brief  function call to SlTmService which starts all asynchronous functions
    /// \retval int #SL_TM_OK if ok, #SL_TM_FAILED if not 
    virtual int allAsync(
                         const int containerNo,               /*!< number of target-container */
                         const int cmd,                       /*!< specifies main command */
                         const int subCmd,                    /*!< specifies sub command */
                         const int streamCode,                /*!< special info to use dataStream_in */
                         const QByteArray& rRequestBinData,   /*!< binary input Data Stream to service,
                                                                   with function internal parameters */
                         SlTmQCmd* pQCmdObj,                  /*!< pointer to client-object SlTmQCmd */
                         int& cmdId,                          /*!< in or out parameter, commandID to identify correlated commands or 0 */
                         SlTmInfo& rInfo                      /*!< \a SlTmInfo additional info to return value if needed */
                        ) = 0;

   /// \brief  function call to SlTmService which starts all asynchronous functions
    /// \retval \a SL_TM_OK if ok, \a SL_TM_FAILED if not 
    virtual int allAsync(
                         const int containerNo,               /*!< number of target-container */
                         const int cmd,                       /*!< specifies main command */
                         const int subCmd,                    /*!< specifies sub command */
                         const int streamCode,                /*!< special info to use dataStream_in */
                         const QByteArray& rRequestBinData,   /*!< binary input Data Stream to service,
                                                                   with function internal parameters */
                         SlTmCmd* pCmdObj,                    /*!< pointer to client-object SlTmCmd */
                         int& cmdId,                          /*!< in or out parameter, commandID to identify correlated commands or 0 */
                         SlTmInfo& rInfo                      /*!< \a SlTmInfo additional info to return value if needed */
                        ) = 0;


    /// \brief  function call to SlTmService which executes all synchronous functions
    /// \retval int #SL_TM_OK if ok, #SL_TM_FAILED if not
    virtual int allSync(
                        const int containerNo,                ///< number of target-container
                        const int cmd,                        ///< specifies main command
                        const int subCmd,                     ///< specifies sub command
                        const int streamCode,                 ///< special info to use dataStream_in
                        const QByteArray& rBinDataToService,  ///< binary input Data Stream to service,
                                                              ///< with function internal parameters
                        QByteArray& rBinDataFromService,      ///< from service received data
                        int& cmdId,                           ///< in/out commandID to identify correlated commands or 0
                        SlTmInfo& rInfo,                      ///< \a SlTmInfo additional info to return value if needed
                        const bool svcRequestIdNeeded = false,      ///< service request id is needed, because it's a
                                                              ///< follow-up order
                        const bool isAdapterShutdown = false  ///< if true shutdown of adapter is active
                       ) = 0;

    /// \brief  function initializes a Subscriber to PO Reset inside SlTmServiceAdapter
    /// \retval int #SL_TM_OK if ok, #SL_TM_FAILED if not
    virtual int initPOResetSubscriber(
                        SlTmQCmd* pQCmdObj,                   ///< pointer to client-object SlTmQCmd
                        int& cmdId,                           ///< in or out parameter, commandID to identify correlated commands or 0
                        SlTmInfo& rInfo                       ///< \a SlTmInfo additional info to return value if needed
                       ) = 0;

    /// \brief  function initializes a Subscriber to PO Reset inside SlTmServiceAdapter
    /// \retval \a SL_TM_OK if ok, \a SL_TM_FAILED if not
    virtual int initPOResetSubscriber(
                        SlTmCmd* pCmdObj,                     ///< pointer to client-object SlTmCmd
                        int& cmdId,                           ///< in or out parameter, commandID to identify correlated command or 0
                        SlTmInfo& rInfo                       ///< \a SlTmInfo additional info to return value if needed
                       ) = 0;

    /// \brief  function deletes a Subscriber to PO Reset inside SlTmServiceAdapter
    /// \retval int #SL_TM_OK if ok, #SL_TM_FAILED if not (cmdId was not found)
    virtual int deletePOResetSubscriber(
                        const int cmdId,                      ///< commandID to identify correlated command
                        SlTmInfo& rInfo,                      ///< \a SlTmInfo additional info to return value if needed
                        const bool isAdapterShutdown = false  ///< if true shutdown of adapter is active
                       ) = 0;

    /// \brief  function deletes command in m_CmdIdManager 
    virtual void cancelNotifyForCmd(
                        const int cmdId                       ///< commandID to identify correlated command
                       ) = 0;
                       
    virtual int cancelServiceCmd(
                        int cmdId,                            ///< commandID to identify correlated command
                        const bool isAdapterShutdown = false  ///< if true shutdown of adapter is active
                       ) = 0;
                         
    // test only    SlTmQCmd-objects are counted
    virtual int actualizeQCmdCounter(
                        int changeVal
                       ) = 0;

    /// \brief test only: starts shutdown of SlTmserviceAdpter, is called testdialog via SlTmQCmd
    virtual int onAdapterShutdown() = 0;

    /////////////////
    /// ACCESSORS
    /////////////////
    /// returns pointer to \a m_CmdIdManager (\a SlTmAsyncCmdIdManager)
    virtual SlTmAsyncCmdIdManager* pCmdIdManager() = 0;

    /// returns pointer to \a m_ClientStore (\a SlTmClientStore)
    virtual SlTmClientStore* pClientStore() = 0;

    /// returns reference to \a m_ClientStore (\a SlTmClientStore)
    virtual SlTmClientStore& rClientStore() = 0;

    /// returns const reference to \a m_ClientStore (\a SlTmClientStore)
    virtual const SlTmClientStore& rConstClientStore() = 0;

signals:
    ///////////////////////////////////////////////////////////////////////////
    // SIGNALS
    ///////////////////////////////////////////////////////////////////////////


protected:
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS (protected)
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn SlTmServiceAdapter(QObject* pParent = 0, const char* pName = 0);
     *  \param1  pParent  pointer to parent object
     *  \param2  pName    intenal name of the object, used for debugging
     *
     *  Creates an SlTmServiceAdapter
    */
    SlTmServiceAdapter(QObject* pParent = 0, const char* pName = 0);

private:
    // test only
    static int s_RefCounter;                      ///< count of existing references to singleton

};

#endif // !defined(SL_TM_SERVICE_ADAPTER_H)
