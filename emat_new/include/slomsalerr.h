/*! \file   slomsvarerr.h
 *  \author 
 *  \date   01.01.2015
 *  \brief  Error codes for OmsAl-Service, HMI Solution Line
 *
 *  (C) Copyright Siemens AG DF MC 2015-2018. All rights reserved.
*/

#if !defined(SLOMSALERR_H_)
#define SLOMSALERR_H_

#include "slerror.h"

///////////////////////////////////////////////////////////////////////////////
// OmsAl Service Module codes: Intervals for Error numbers
// Mask: 0x000FF000
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//**ModuleCode: 0x03500000
//**ModuleName: HMI - SL OMSAl Service
//**TextFile:
//**TextContext:

//**ErrBeginSubModules
//**Name:Solution Line OMSAl Service
#define SLOMSAl_SERVICE 0x00001000
//**Name:Solution Line OMS+ Variables Service Adapter
#define SLOMSAl_SVC_ADAPTER 0x00002000
//**ErrEndSubModules

#define SVC_ERR(ERR_NO)   {return SL_ERR_OMSAL | SLOMSAl_SERVICE | ERR_NO;}
#define ADAPT_ERR(ERR_NO) {return SL_ERR_OMSAL | SLOMSAl_SVC_ADAPTER | ERR_NO;}

#define SLOMSAL_SVC_ERR(ERR_NO)         (SL_ERR_OMSAL | SLOMSAl_SERVICE | ERR_NO)
#define SLOMSAL_ADAPT_ERR(ERR_NO)       (SL_ERR_OMSAL | SLOMSAl_SERVICE | ERR_NO)

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginGlobalErrorCodes
//**Text:Memory allocation failure
#define SLOMSAl_NO_MEMORY 0x80000001
//**Text:Feature not implemented
#define SLOMSAl_NOT_IMPL 0x80000002


//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SLOMSAl_SERVICE

//**Text:no connection to server established
#define SLOMSAl_NO_CONNECTION_TO_PLC      (SL_ERR_OMSAL | SLOMSAl_SERVICE |0x80000019)
//**Text:session not ok
#define SLOMSAL_SESSION_ERR               (SL_ERR_OMSAL | SLOMSAl_SERVICE |0x80000030)
//**Text:subscription not ok
#define SLOMSAL_SUBSCRIPTION_ERR          (SL_ERR_OMSAL | SLOMSAl_SERVICE |0x80000031)
//**Text:acknowledge not ok
#define SLOMSAL_ACKNOWLEDGE_ERR           (SL_ERR_OMSAL | SLOMSAl_SERVICE |0x80000032)
//**Text:illegal first DAI in history
#define SLOMSAL_ILLEGAL_FIRST_DAI_ERR     (SL_ERR_OMSAL | SLOMSAl_SERVICE |0x80000033)



//**Text:internal call to oms failed
#define SLOMSAL_OMS_INT_ERR               (SL_ERR_OMSAL | SLOMSAl_SERVICE |0x80000040)
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SLOMSAl_SVC_ADAPTER
//**Text:No connection to the service
#define SLOMSAlA_NO_CONNECTION           (SL_ERR_OMSAL | SLOMSAl_SVC_ADAPTER |0x80000003)
//**Text:Error dispatching parameters
#define SLOMSAlA_DISPATCH_FAILED         (SL_ERR_OMSAL | SLOMSAl_SVC_ADAPTER |0x80000004)
//**Text: service not available
#define SLOMSALA_SERVICE_NOT_AVAILABLE   (SL_ERR_OMSAL | SLOMSAl_SVC_ADAPTER |0x80000005)

//**ErrEndErrorCodes


#endif // SLOMSALERR_H_
