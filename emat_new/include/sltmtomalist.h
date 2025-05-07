// ////////////////////////////////////////////////////////////////////////////
/*! 
  \file   sltmtomalist.h
  \author Reinhold Guenthner
  \date   09.2005
  \brief  Headerfile for interface base class of lists: 
          (abstract mixin base class)
          
  This file is part of the HMI Solutionline Toolmanagement.
  
  Some Enums of his classes may also be used by client software to control lists 
  of toolmanagement data.

  
    
  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
*/
// ////////////////////////////////////////////////////////////////////////////


#if !defined(SL_TM_TOMA_LIST_H)
#define SL_TM_TOMA_LIST_H


#include "slhmitemplatesqt.h"

#include "sltmutil.h"
#include "sltmsvcqbasubscriberi.h"
#include "sltmmassdatatoolmaglistchangeddata.h"
#include <QtCore/QTextStream>
#include <QtCore/QMap>
#include <QtCore/QQueue>
#include <QtCore/QByteArray>


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


// /////////////////////////////////////////////////////////////////////////////
// forward declarations:
class SlTmStore; 
class SlTmToMaContainerColl; 


/// \brief This is a typedef to handle subscriptions keys.
/// 
/// This typedef handles subscription SlTmSvcQBASubscriber* pointer
/// to qualify as a key in QMaps.
typedef SlTmSvcQBASubscriberI* SlTmSvcQBASubscriberPointerType; ///< call back object pointer 


/// \brief This is a struct to handle subscriptions data.
/// 
/// This struct handles suscriptions data 
/// together to qualify as a data in QMaps.
typedef struct SlTmToMaListSubscriberDataType 
{
public:
  int                              m_ListElIntervalBeg;              ///< Interval of interest: first list element; \n
                                                                     ///< list elements are counted from 0; \n
                                                                     ///< value of -1: all list elements; \n
                                                                     ///< only relevant in case of SlTmMassDataToolMagListChangedData, \n
                                                                     ///< indicated by (SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA1 == m_MassDataStreamCode) 
  int                              m_ListElIntervalEnd;              ///< Interval of interest: last list element; \n
                                                                     ///< only relevant in case of SlTmMassDataToolMagListChangedData, \n
                                                                     ///< indicated by (SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA1 == m_MassDataStreamCode) 
  SlTmMassDataExportImportMask     m_MassDataExportImportMask;       ///< export / import mask of SlTmMassData2ToolMagListChangedData data parts; \n
                                                                     ///< only relevant in case of SlTmMassData2ToolMagListChangedData, \n
                                                                     ///< indicated by (SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA2 == m_MassDataStreamCode) 
  SlTmToMaExportImportMask         m_StoreToMaDataExportImportMask;  ///< export / import mask of tool, multittol, magazine, place, adapter etc. data; \n
                                                                     ///< only relevant in case of SlTmMassData2ToolMagListChangedData, \n
                                                                     ///< indicated by (SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA2 == m_MassDataStreamCode) 
  SlTmStreamCode::StreamCodeEnum   m_MassDataStreamCode;             ///< stream code of derived massData class of base class SlTmMassDataImportI
  QQueue<QByteArray>               m_ListBinDataQueuedForOnNotify;   ///< QQueue of binary list data to store exported list intervalls between export and invokation of onNotify()

  
  /// \brief constructor
  explicit SlTmToMaListSubscriberDataType(
    const int                              parListElIntervalBeg = 0, 
                                                      ///< Interval of interest: first list element; \n
                                                      ///< list elements are counted from 0; \n
                                                      ///< value of -1: all list elements; \n
                                                      ///< only relevant in case of SlTmMassDataToolMagListChangedData, \n
                                                      ///< indicated by (SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA1 == m_MassDataStreamCode)
    const int                              parListElIntervalEnd = 0,
                                                      ///< Interval of interest: last list element; \n
                                                      ///< only relevant in case of SlTmMassDataToolMagListChangedData, \n
                                                      ///< indicated by (SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA1 == m_MassDataStreamCode)
    const SlTmMassDataExportImportMask&    rMassDataExportImportMask = SlTmMassDataExportImportMask(0),
                                                      ///< export / import mask of SlTmMassData2ToolMagListChangedData data parts; \n
                                                      ///< only relevant in case of SlTmMassData2ToolMagListChangedData, \n
                                                      ///< indicated by (SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA2 == m_MassDataStreamCode) 
    const SlTmToMaExportImportMask&        rStoreToMaDataExportImportMask = SlTmToMaExportImportMask(),
                                                      ///< export / import mask of tool, multittol, magazine, place, adapter etc. data; \n
                                                      ///< only relevant in case of SlTmMassData2ToolMagListChangedData, \n
                                                      ///< indicated by (SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA2 == m_MassDataStreamCode) 
    const SlTmStreamCode::StreamCodeEnum   massDataStreamCode = SlTmStreamCode::UNDEFINED
                                                      ///< stream code of massData pointer of base class SlTmMassDataImportI
                                         )
    : m_ListElIntervalBeg(parListElIntervalBeg),
      m_ListElIntervalEnd(parListElIntervalEnd),
      m_MassDataExportImportMask(rMassDataExportImportMask),
      m_StoreToMaDataExportImportMask(rStoreToMaDataExportImportMask),
      m_MassDataStreamCode(massDataStreamCode),
      m_ListBinDataQueuedForOnNotify()
  {};
  
  /// \brief copy constructor
  SlTmToMaListSubscriberDataType(
    const SlTmToMaListSubscriberDataType& rSourceObj ///< source object
                                )
  {
    /*int retVal =*/ copyMemberVars(rSourceObj);
    return;
  };
  
  /// \brief destructor
  virtual ~SlTmToMaListSubscriberDataType() {};
  
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  ///
  SlTmToMaListSubscriberDataType& operator= (
    const SlTmToMaListSubscriberDataType& rSourceObj ///< source object 
                                            )
  {
    if (this != &rSourceObj)                 // assigning not same object?
    {                  // assignment work:
      /*int retVal =*/ copyMemberVars(rSourceObj);
    }
    return *this;                       // return new object
  };
  
  //   /// \brief This operator< is required to use 
  //   ///        suscriptions data together as a key in QMaps.
  //   /// 
  //   bool operator< (const SlTmToMaListSubscriberDataType& rRight) const
  //   {
  //     if (m_ListElIntervalBeg             != rRight.m_ListElIntervalBeg)             {return (m_ListElIntervalBeg             < m_ListElIntervalBeg);}         
  //     if (m_ListElIntervalEnd             != rRight.m_ListElIntervalEnd)             {return (m_ListElIntervalEnd             < m_ListElIntervalEnd);}         
  //     if (m_MassDataExportImportMask      != rRight.m_MassDataExportImportMask)      {return (m_MassDataExportImportMask      < m_MassDataExportImportMask);}         
  //     if (m_StoreToMaDataExportImportMask != rRight.m_StoreToMaDataExportImportMask) {return (m_StoreToMaDataExportImportMask < m_StoreToMaDataExportImportMask);}         
  //     if (m_MassDataStreamCode            != rRight.m_MassDataStreamCode)            {return (m_MassDataStreamCode            < m_MassDataStreamCode);}         
  //     return (m_ListBinDataQueuedForOnNotify < rRight.m_ListBinDataQueuedForOnNotify);  // wrong
  //   };
  
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmToMaListSubscriberDataType& rSourceObj // source object 
                    )
  {
    
    m_ListElIntervalBeg             = rSourceObj.m_ListElIntervalBeg;
    m_ListElIntervalEnd             = rSourceObj.m_ListElIntervalEnd;
    m_MassDataExportImportMask      = rSourceObj.m_MassDataExportImportMask;
    m_StoreToMaDataExportImportMask = rSourceObj.m_StoreToMaDataExportImportMask;
    m_MassDataStreamCode            = rSourceObj.m_MassDataStreamCode;
    m_ListBinDataQueuedForOnNotify  = rSourceObj.m_ListBinDataQueuedForOnNotify;
    
    return (SlTmUtil::ERR_OK);
  };

  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaListSubscriberDataType& rRight ///< right object
                  ) const
  {
    if (!(m_ListElIntervalBeg                == rRight.m_ListElIntervalBeg))             {return (true);}
    if (!(m_ListElIntervalEnd                == rRight.m_ListElIntervalEnd))             {return (true);}
    if (!(m_MassDataExportImportMask         == rRight.m_MassDataExportImportMask))      {return (true);}
    if (!(m_StoreToMaDataExportImportMask    == rRight.m_StoreToMaDataExportImportMask)) {return (true);}
    if (!(m_MassDataStreamCode               == rRight.m_MassDataStreamCode))            {return (true);}
    return (!(m_ListBinDataQueuedForOnNotify == rRight.m_ListBinDataQueuedForOnNotify));
  };

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaListSubscriberDataType& rRight ///< right object
                  ) const
  {
    if (!(m_ListElIntervalBeg                == rRight.m_ListElIntervalBeg))             {return (false);}
    if (!(m_ListElIntervalEnd                == rRight.m_ListElIntervalEnd))             {return (false);}
    if (!(m_MassDataExportImportMask         == rRight.m_MassDataExportImportMask))      {return (false);}
    if (!(m_StoreToMaDataExportImportMask    == rRight.m_StoreToMaDataExportImportMask)) {return (false);}
    if (!(m_MassDataStreamCode               == rRight.m_MassDataStreamCode))            {return (false);}
    return (m_ListBinDataQueuedForOnNotify   == rRight.m_ListBinDataQueuedForOnNotify);
  };

}SlTmToMaListSubscriberDataType;



/// \brief This is the forward definition for typedef SlTmToMaListSubscriberCollMapType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QMap<SlTmSvcQBASubscriberPointerType, SlTmToMaListSubscriberDataType>;
#endif
// MOC_SKIP_END

/// \brief collection of subscribers
///        as QMap of SlTmSvcQBASubscriberPointerType, 
///        accessed by key of type SlTmSvcQBASubscriberPointerType,
///        data of type SlTmToMaListSubscriberDataType
typedef QMap<SlTmSvcQBASubscriberPointerType, SlTmToMaListSubscriberDataType> SlTmToMaListSubscriberCollMapType;



class SlTmQRWLocker;



// ////////////////////////////////////////////////////////////////////////////
///  \class  SlTmToMaList sltmtomalist.h
///  \brief  This pure virtual base class (abstract mixin base class)
///          is used as interface for 
///          implementation list classes 
///          to sort data from 
///          SlTmToMaStore's containers, tools and magazine places 
///          and to access this data as sorted list.
///          
class SL_TM_UTILITIES_EXPORT SlTmToMaList
{
public:
  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaList(
              SlTmStore* pStore = 0 ///< store whose tools and places are handeled and in which this SlTmToMaLists-object is contained.
                       ) {};

  /// \brief destructor
  virtual ~SlTmToMaList() {}; 
  
  /// \brief make a copy of member (clone) on heap and return pointer to new clone 
  ///         (m_SubscriberCollMap is NOT copied) 
  /// 
  /// \retval SlTmToMaList* pointer to new clone on heap; 
  ///         derived classes return a pointer of derived type.
  virtual SlTmToMaList* clone(void) const = 0;  
  
  
  // MANIPULATORS 
  /// \brief set list active (\a listActive = \c true) or 
  ///        set list inactive (\a listActive = \c false).
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  virtual int setActive(
                SlTmQRWLocker& rStoresQRWLocker,    
                                ///< Read or Write Locker for Stores QReadWriteLock 
                                ///< for temporary unlock while giving control away
                                ///< (ie. during SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                ///< and subsequent relock (usually via SlTmQRWTmpUnlocker).
                const bool&    rIsCancelOrdered,    
                                ///< Verify this before starting long lasting computations,
                                ///< and before giving control away 
                                ///< (ie. SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                ///< and after obtaining control back after relock.
                                ///< In case of (\c true == \a rIsCancelOrdered) return immediately by setting error return value.
                const bool     listActive  ///< \c true: make list active
                       ) = 0;

  /// \brief set list parameters as QString
  /// 
  /// Parameters are given as Text in QString.
  /// 2 Parameters are separated by SlTmToMaListUni::S_PAR_SEPARATOR ("\n").
  /// Each parameter consists of Parameter-Name and Parameter-Value, 
  /// separated by SlTmToMaListUni::S_PAR_NAME_VALUE_SEPARATOR ("=").
  /// Parameter-Names and Parameter-Values are defined by derived class.
  /// 
  /// Example \a rParameters:
  /// "ListSubType=1\nToolNameSorting=1\nDuploOrMachiningSequenceSorting=1"
  /// 
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  virtual int setParameters(
                SlTmQRWLocker& rStoresQRWLocker,    
                                ///< Read or Write Locker for Stores QReadWriteLock 
                                ///< for temporary unlock while giving control away
                                ///< (ie. during SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                ///< and subsequent relock (usually via SlTmQRWTmpUnlocker).
                const bool&    rIsCancelOrdered,    
                                ///< Verify this before starting long lasting computations,
                                ///< and before giving control away 
                                ///< (ie. SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                ///< and after obtaining control back after relock.
                                ///< In case of (\c true == \a rIsCancelOrdered) return immediately by setting error return value.
                const QString& rParameters  ///< list parameters as QString
                           ) = 0;
  
  /// \brief set lists container list
  /// 
  /// Does list sorting for all containers of \a rInListContainerNoVector.
  /// List will contain elements from all containers of \a rInListContainerNoVector.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  virtual int setContainerList(
                SlTmQRWLocker& rStoresQRWLocker,    
                                ///< Read or Write Locker for Stores QReadWriteLock 
                                ///< for temporary unlock while giving control away
                                ///< (ie. during SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                ///< and subsequent relock (usually via SlTmQRWTmpUnlocker).
                const bool&    rIsCancelOrdered,    
                                ///< Verify this before starting long lasting computations,
                                ///< and before giving control away 
                                ///< (ie. SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                ///< and after obtaining control back after relock.
                                ///< In case of (\c true == \a rIsCancelOrdered) return immediately by setting error return value.
                const SlTmToMaContainerNosValueVectorType& rInListContainerNoVector 
                                ///< all in list contained containerNo keys 
                                ///< as QVector 
                                ///< of SlTmToMaContainerNoType container numbers 
                              ) = 0;
  
  /// \brief delets all list elements
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  virtual int deleteAllListElements(
                SlTmQRWLocker& rStoresQRWLocker,    
                                ///< Read or Write Locker for Stores QReadWriteLock 
                                ///< for temporary unlock while giving control away
                                ///< (ie. during SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                ///< and subsequent relock (usually via SlTmQRWTmpUnlocker).
                const bool&    rIsCancelOrdered    
                                ///< Verify this before starting long lasting computations,
                                ///< and before giving control away 
                                ///< (ie. SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                ///< and after obtaining control back after relock.
                                ///< In case of (\c true == \a rIsCancelOrdered) return immediately by setting error return value.
                                   ) = 0;
  
  /// \brief refresh list for a QVector list \a rChangedContainerNoVector of changed containers
  /// 
  /// inserts / verifys / deletes list elements which belongs 
  /// to changed containers of \a rChangedContainerNoVector
  /// and if thera are subscribers: export changes and send onNotify to subscribers.
  /// 
  /// Does export / onNotify, even if changed container list is empty, 
  /// to export / notify in case of unusual changes:
  /// if a container is deleted from lists "container list", 
  /// corresponding list elements are deleted too.
  /// These differences from m_TmpOldListElCollMap must be exported and send to 
  /// subscriber, independent of changes in store.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  virtual int refreshListForChangedContainerList(
              SlTmQRWLocker&                          rStoresQRWLocker,    
                        ///< Read or Write Locker for Stores QReadWriteLock 
                        ///< for temporary unlock while giving control away
                        ///< (ie. during SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                        ///< and subsequent relock (usually via SlTmQRWTmpUnlocker).
              const bool&                                rIsCancelOrdered,    
                        ///< Verify this before starting long lasting computations,
                        ///< and before giving control away 
                        ///< (ie. SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                        ///< and after obtaining control back after relock.
                        ///< In case of (\c true == \a rIsCancelOrdered) return immediately by setting error return value.
              const SlTmToMaContainerNosValueVectorType& rChangedContainerNoVector, 
                        ///< all changed containerNo keys 
                        ///< as QVector 
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
                                                ) = 0;
  

  /// \brief add a subscriber to list
  /// 
  /// Add a SlTmSvcQBASubscriberI* represented by its pointer \a pParCallBackObj.
  /// List element changes will be reported during subscription by calling 
  /// SlTmSvcQBASubscriberI virtual method SlTmSvcQBASubscriberI::onNotify().
  /// 
  /// Subscribers \a pParCallBackObj is key value \n
  /// to identify subsciber in methods removeSubscriber() and \n
  /// changeSubscribersInterval(). \n
  /// Therefore it must be unique and an attempt to subscribe a 2nd time with \n
  /// same \a pParCallBackObj returns an error.
  /// 
  /// If \a pParCallBackObj is of type SlTmMassDataToolMagListChangedData \n
  /// and has SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA1: \n
  /// List element interval of interest is given by \a parListElIntervalBeg and \n
  /// \a parListElIntervalEnd, list elements are counted from 0. \n
  /// Only list element changes within this interval are send by onNotify(...)
  /// 
  /// If \a pParCallBackObj is of type SlTmMassData2ToolMagListChangedData \n
  /// and has SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA2: \n
  /// \a parToMaDataExportImportMask controls which data kinds \n
  /// of tool, place, multitool, adapter and so on data \n
  /// are exported and \a parMassDataExportImportMask controls \n
  /// which parts off SlTmMassData2ToolMagListChangedData are used.
  /// 
  /// A first SlTmSvcQBASubscriberI::onNotify() call to \a pParCallBackObj is invoked \n
  /// to send all list elements of specified interval. \n
  /// (onNotify parameter notificationState == SlTmSvcQBASubscriberI::SUBSCRIPTION_ACTIVE)
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  virtual int addSubscriber(
        SlTmQRWLocker&         rStoresQRWLocker,    
                                          ///< Read or Write Locker for Stores QReadWriteLock 
                                          ///< for temporary unlock while giving control away
                                          ///< (ie. during SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                          ///< and subsequent relock (usually via SlTmSvcQRWTmpUnlocker).
        const bool&            rIsCancelOrdered,    
                                          ///< Verify this before starting long lasting computations,
                                          ///< and before giving control away 
                                          ///< (ie. SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                          ///< and after obtaining control back after relock.
                                          ///< In case of (\c true == \a rIsCancelOrdered) return immediately by setting error return value.
        const int              parListElIntervalBeg = 0, 
                                                   ///< Interval of interest: first list element; \n
                                                   ///< list elements are counted from 0; \n
                                                   ///< value of -1: all list elements; \n
                                                   ///< only relevant in case of SlTmMassDataToolMagListChangedData, \n
                                                   ///< indicated by \a pParCallBackObj has SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA1 
        const int              parListElIntervalEnd = 0, 
                                                   ///< Interval of interest: last list element; \n
                                                   ///< only relevant in case of SlTmMassDataToolMagListChangedData, \n
                                                   ///< indicated by \a pParCallBackObj has SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA1 
        const SlTmMassDataExportImportMask& parMassDataExportImportMask = SlTmMassDataExportImportMask(0),
                                                   ///< export / import mask of SlTmMassData2ToolMagListChangedData data parts; \n
                                                   ///< only relevant in case of SlTmMassData2ToolMagListChangedData, \n
                                                   ///< indicated by \a pParCallBackObj has SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA2 
        const SlTmToMaExportImportMask& parToMaDataExportImportMask = SlTmToMaExportImportMask(),
                                                   ///< export / import mask of tool, multittol, magazine, place, adapter etc. data; \n
                                                   ///< only relevant in case of SlTmMassData2ToolMagListChangedData, \n
                                                   ///< indicated by \a pParCallBackObj has SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA2 
        const SlTmStreamCode::StreamCodeEnum   parMassDataStreamCode = SlTmStreamCode::UNDEFINED, 
                                                   ///< stream code of derived massData class pointer of base class SlTmMassDataImportI for async notify
        SlTmSvcQBASubscriberI* pParCallBackObj      = 0 
                                          ///< pointer to subscribers call back object
                           ) = 0;
  
  /// \brief remove a subscriber from list
  /// 
  /// Remove a subscriber identified by \a pParCallBackObj from list.
  /// 
  /// A last onNotify(...) call to SlTmSvcQBASubscriberI* is invoked
  /// to signal end of subsciption. 
  /// (onNotify parameter notificationState==SlTmSvcQBASubscriberI::SUBSCRIPTION_FINISHED)
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  virtual int removeSubscriber(
                                SlTmQRWLocker&                          rStoresQRWLocker,    
                                      ///< Read or Write Locker for Stores QReadWriteLock 
                                      ///< for temporary unlock while giving control away
                                      ///< (ie. during SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                      ///< and subsequent relock (usually via SlTmQRWTmpUnlocker).
                                const bool&                                rIsCancelOrdered,    
                                      ///< Verify this before starting long lasting computations,
                                      ///< and before giving control away 
                                      ///< (ie. SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                      ///< and after obtaining control back after relock.
                                      ///< In case of (\c true == \a rIsCancelOrdered) return immediately by setting error return value.
                                SlTmSvcQBASubscriberI* pParCallBackObj      = 0 
                                      ///< pointer to subscribers call back object
                              ) = 0;
  
  /// \brief change subscribers list element interval of interest
  /// 
  /// Ssubscriber is identified by \a pParCallBackObj from list.
  /// 
  /// If \a pParCallBackObj is of type SlTmMassDataToolMagListChangedData \n
  /// and has SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA1: \n
  /// List element interval of interest can be modfied by \a parListElIntervalBeg and \n
  /// \a parListElIntervalEnd, list elements are counted from 0. \n
  /// Only list element changes within this interval are send by onNotify(...)
  /// 
  /// 
  /// A first onNotify(...) call to SlTmSvcQBASubscriberI* is invoked
  /// to send all list elements of specified interval.
  /// (onNotify parameter notificationState==SlTmSvcQBASubscriberI::SUBSCRIPTION_ACTIVE)
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  virtual int changeSubscribersInterval(
        SlTmQRWLocker& rStoresQRWLocker,    
                                          ///< Read or Write Locker for Stores QReadWriteLock 
                                          ///< for temporary unlock while giving control away
                                          ///< (ie. during SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                          ///< and subsequent relock (usually via SlTmQRWTmpUnlocker).
        const bool&    rIsCancelOrdered,    
                                          ///< Verify this before starting long lasting computations,
                                          ///< and before giving control away 
                                          ///< (ie. SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                          ///< and after obtaining control back after relock.
                                          ///< In case of (\c true == \a rIsCancelOrdered) return immediately by setting error return value.
        const int              parListElIntervalBeg = 0, 
                                          ///< Interval of interest: first list element
                                          ///< list elements are counted from 0;
                                          ///< value of -1: all list elements
        const int              parListElIntervalEnd = 0, 
                                          ///< Interval of interest: last list element
        SlTmSvcQBASubscriberI* pParCallBackObj      = 0 
                                          ///< pointer to subscribers call back object
                                       ) = 0;

  /// \brief remove all subscribers from list
  /// 
  /// Remove all subscribers from list.
  /// 
  /// A last onNotify(...) call to each SlTmSvcQBASubscriberI* is invoked
  /// to signal end of subsciption. 
  /// (onNotify parameter notificationState==SlTmSvcQBASubscriberI::SUBSCRIPTION_FINISHED)
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  virtual int removeAllSubscribers(
                SlTmQRWLocker& rStoresQRWLocker,    
                                ///< Read or Write Locker for Stores QReadWriteLock 
                                ///< for temporary unlock while giving control away
                                ///< (ie. during SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                ///< and subsequent relock (usually via SlTmQRWTmpUnlocker).
                const bool&    rIsCancelOrdered    
                                ///< Verify this before starting long lasting computations,
                                ///< and before giving control away 
                                ///< (ie. SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                ///< and after obtaining control back after relock.
                                ///< In case of (\c true == \a rIsCancelOrdered) return immediately by setting error return value.
                                  ) = 0;



  // ACCESSORS
  /// \brief is list active (retval = \c true) or
  ///        is list inactive (retval = \c false).
  /// 
  /// \retval bool \c true if list is active, otherwise \c false.
  virtual bool isActive(void) const = 0;

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaList& rData) \n
  /// method is const with exeption of a mutex while reading a map
  virtual QTextStream& exportData(
                          QTextStream& rStream ///< text target stream
                                 ) /*const*/ = 0;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

public:
  // MANIPULATORS 
  // for zombie and occupation counter:
  
  /// \brief Occupy list by a threads usage.
  /// 
  /// Use occupyUsage() and releaseUsage() as a pair of methods
  /// at begin and end of computation in a thread, 
  /// especally if stores lock is temporary unlocked during computation.
  virtual void occupyUsage(void) = 0;

  /// \brief Release lists usage.
  /// 
  /// Use occupyUsage() and releaseUsage() as a pair of methods
  /// at begin and end of computation in a thread, 
  /// especally if stores lock is temporary unlocked during computation.
  virtual void releaseUsage(void) = 0;

  /// \brief Irreversible mutate state of list into zombie state (instead of to delete it immediatly).
  virtual void mutateListIntoAZombie(void) = 0;

  /// \brief Is list occupied (by thread(s) usage)?
  /// 
  /// \retval bool true, if list is occupied by thread usage
  virtual bool isOccupied(void) = 0;

  /// \brief Is list in zombie state? \n
  ///        If true, do not start computations, 
  ///        but finish already running actions. \n
  ///         List is going to be deleted, after last occupation has finished.
  /// 
  /// \retval bool true, if list is a zombie
  virtual bool isZombie(void) = 0;

  /// \brief Verify, if list is in zombie state and list is not occupied: 
  ///        if it is, do delete list itself.
  /// 
  /// \retval bool true, if list has been deleted. Do NEVER access it's member data!
  virtual bool ifListIsAReleasedZombieDoDeleteItself(void) = 0;

  
  // FRIENDS
  //friend classes
  // empty
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //  //friend operators for streaming:
  //  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
  //            QTextStream& rStream,           ///< text data stream target 
  //            const SlTmToMaList& rData    ///< export source object    
  //                                                       );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  
protected:
  // MANIPULATORS 

  
  // ACCESSORS
  // empty
  
private:
  // CREATORS
  /// \brief copy constructor (m_SubscriberCollMap is NOT copied) 
  /// 
  /// This copy constructor is private in virtual base class to avoid wrong assignment between 
  /// differend derived class objects.
  SlTmToMaList(
    const SlTmToMaList& rSourceObj ///< source object
              );


  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  ///        (m_SubscriberCollMap is NOT copied) 
  /// 
  /// This operator= is private in virtual base class to avoid wrong assignment between 
  /// differend derived class objects.
  SlTmToMaList& operator= (
              const SlTmToMaList& rSourceObj ///< source object 
                          );
  
  
  // ACCESSORS
  // empty

};


/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

// FRIEND OPERATORS:
// ACCESSORS
// operator<< for text data export from \a rData to QTextStream \a rStream. \n
//        Data format can change incompatibly between versions of software. \n
//        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
//QTextStream& operator<< (
//                         QTextStream& rStream,                 // text data stream target 
//                         const SlTmToMaList& rData // export source object 
//                        ) { return (rData.exportData(rStream)); };

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// end of class SlTmToMaList
// ////////////////////////////////////////////////////////////////////////////






#endif // !defined(SL_TM_TOMA_LIST_H)
