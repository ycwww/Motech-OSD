// ////////////////////////////////////////////////////////////////////////////
/*! 
  \file   sltmsvcqbasubscriberi.h
  \author Reinhold Guenthner
  \date   11.2005
  \brief  Headerfile for interface base class 
          SlTm-Service-Subsciber SlTmSvcQBASubscriberI 
          with QByteArray&-Interface. 
          (abstract mixin base class)
          
  This file is part of the HMI Solutionline Toolmanagement.
  
  Some Enums of his classes may also be used by client software to control lists 
  of toolmanagement data.

  
    
  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
*/
// ////////////////////////////////////////////////////////////////////////////


#if !defined(SL_TM_SVC_QBA_SUBSCRIBER_I_H)
#define SL_TM_SVC_QBA_SUBSCRIBER_I_H


#include "sltmstreamcode.h"
#include "sltminfo.h"


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
// emty


// ////////////////////////////////////////////////////////////////////////////
///  \class  SlTmSvcQBASubscriberI sltmsvcqbasubscriberi.h
///  \brief  This pure virtual base class (abstract mixin base class)
///          is used as interface for 
///          implementation of SlTm-Service-Subsciber classes 
///          with QByteArray&-Interface.
///   
///  Usually SlTm-Service exports result data via QDataStream operator> or
///  export-Method to QByteArray and 
///  calls SlTmSvcQBASubscriberI virtual method onNotify(... QByteArray& ...)
///  of subscriber object.         
///          
///  Implementation of onNotify() of derived Class can i.e. convert         
///  QByteArrays data to Corba octed data and send it synchronously          
///  to service adapters data data sink object via Corba.       
///          
///  Lifetime of QByteArray reference is during call of onNotify() only.       
///          
///  onNotify() contains also status information in case of canceledSubscription,         
///  which can be used by derived implementation i. e. to self delete subsciber.
///          
class SL_TM_UTILITIES_EXPORT SlTmSvcQBASubscriberI
{
public:
  /// \brief enum for subscription state in notification 
  enum NotificationStateEnum
  { 
    SUBSCRIPTION_FINISHED   = -1, ///< subscription is finished: 
                                  ///< this is the last notification if
                                  ///< subscription is unsubscribed or canceled.
                                  ///< \a pQBAData does NOT contain data and is 0.
    SUBSCRIPTION_ACTIVE     =  1, ///< subscription is active
                                  ///< \a pQBAData contains data.
  };

  //  // CREATORS 
  //  virtual ~SlTmSvcQBASubscriberI() = 0 {}; causes an error in linux compilation.
  // brief destructor
  virtual ~SlTmSvcQBASubscriberI() = 0;
  

  // MANIPULATORS 
  /// \brief notify subscribers implementation.
  ///        \a streamCode contains stream code, \a pQBAData contains data.
  /// 
  /// If \a notificationState == SlTmSvcQBASubscriberI::SUBSCRIPTION_FINISHED,
  /// then pQBAData is 0 (is a null pointer) 
  /// and \ streamCode == SlTmStreamCode::UNDEFINED
  /// 
  /// If \a pQBAData != 0 and streamCode == SlTmStreamCode::EMPTY, 
  /// \a pQBAData QByteArray with pQBAData->count() == 0 is empty.
  /// 
  /// If \a streamCode == SlTmStreamCode::UNDEFINED, then do NOT use *pQBAData.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  virtual int onNotify(
    NotificationStateEnum          notificationState, 
                                         ///< notification state, 
                                         ///< see SlTmSvcQBASubscriberI::NotificationStateEnum
    SlTmStreamCode::StreamCodeEnum streamCode,
                                         ///< stream code for \a pQBAData byte array
    const QByteArray*              pQBAData,          
                                         ///< Pointer to notification data
                                         ///< of type QByteArray or 0.
                                         ///< Lifetime is limited to 
                                         ///< lifetime of onNotify method.
    SlTmInfo                       tmInfo
                                         ///< SlTmInfo toolmanagements info object
                      ) = 0;
  
  

  // ACCESSORS
  // empty
  
  // FRIENDS
  //friend classes
  // empty
  
  
protected:  
  // MANIPULATORS 
  // empty
  
  // ACCESSORS
  // empty
  
private:
  // MANIPULATORS 
  // empty

  
  // ACCESSORS
  // empty

};

// FRIEND OPERATORS:
// ACCESSORS
// empty



// end of class SlTmSvcQBASubscriberI
// ////////////////////////////////////////////////////////////////////////////






#endif // !defined(SL_TM_SVC_QBA_SUBSCRIBER_I_H)
