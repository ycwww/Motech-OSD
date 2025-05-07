/*! \file   slmaerror.h
 *  \author Harald Vieten (MG)
 *  \date   28.02.2006
 *  \brief  Errornumber intervals for HMI Solution Line Machine/Parameter
 *
 *  (C) Copyright Siemens AG 2006
*/
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_MA_ERROR_INCLUDE)
#define SL_MA_ERROR_INCLUDE

#include "slerror.h"

///////////////////////////////////////////////////////////////////////////////
//**ModuleCode: 0x01600000
//**ModuleName: HMI - SL slmalogic, ma form logic, pa form logic
//**TextFile:
//**TextContext:

//**ErrBeginSubModules
//**Name:slmalogic
#define SL_MA_LOGIC             0x00010000
//**Name:slmaformlogic
#define SL_MA_FORMLOGIC         0x00020000
//**Name:slpaformlogic
#define SL_PA_FORMLOGIC         0x00030000
//**Name:slmaform
#define SL_MA_FORM              0x00040000
//**Name:slpaform
#define SL_PA_FORM              0x00050000
//**Name:slstepncconfig
#define SL_STEP_NC_CONFIG       0x00060000
//**ErrEndSubModules

///////////////////////////////////////////////////////////////////////////////
// help funktions for easy error return
///////////////////////////////////////////////////////////////////////////////
static inline long slmalogicError(long nCode = SL_ERR_SUCCESS)
{
    return ((SL_ERR_MA_PA) | (SL_MA_LOGIC) | (nCode));
}

static inline long slmaFormlogicError(long nCode = SL_ERR_SUCCESS)
{
    return ((SL_ERR_MA_PA) | (SL_MA_FORMLOGIC) | (nCode));
}

static inline long slpaFormlogicError(long nCode = SL_ERR_SUCCESS)
{
    return ((SL_ERR_MA_PA) | (SL_PA_FORMLOGIC) | (nCode));
}

static inline long slmaFormError(long nCode = SL_ERR_SUCCESS)
{
    return ((SL_ERR_MA_PA) | (SL_MA_FORM) | (nCode));
}

static inline long slpaFormError(long nCode = SL_ERR_SUCCESS)
{
    return ((SL_ERR_MA_PA) | (SL_PA_FORM) | (nCode));
}

static inline long slStepNcConfigError(long nCode = SL_ERR_SUCCESS)
{
    return ((SL_ERR_MA_PA) | (SL_STEP_NC_CONFIG) | (nCode));
}

///////////////////////////////////////////////////////////////////////////////
// Help System error codes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// global errors from         0x80000001 to 0x800000FF
// local errors from          0x80000100 to 0x800002FF
// local states from          0x00000300 to 0x000003FF
//
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginGlobalErrorCodes
//**Text:no error
#define SL_MA_NO_ERROR                                         SL_ERR_SUCCESS
//**Text:a ma_pa object is created, no dynamic activities, cap resources released

//**Text:general error
#define SL_MA_ERROR                                            0x80000001
//**Text:no memory could be allocated
#define SL_MA_ERROR_NO_MEMORY                                  0x80000002
//**Text:change object state was not possible
#define SL_MA_ERROR_SET_STATE                                  0x80000003
//**Text:at least on of the function parameters is wrong
#define SL_MA_ERROR_SET_VALUE_PARAMETER                        0x80000004
//**Text:write value failed, cap error
#define SL_MA_ERROR_SET_VALUE_CAP                              0x80000005
//**Text:write value failed, permission denied
#define SL_MA_ERROR_SET_VALUE_ACCESS_LEVEL                     0x80000006
//**Text:write value failed, value out of range
#define SL_MA_ERROR_SET_VALUE_LIMIT                            0x80000007
//**Text:write value failed, value out of range
#define SL_MA_ERROR_INDEX_OUT_OF_RANGE                         0x80000008
//**Text:in current chan state (run, stop, reset) not allowed
#define SL_MA_ERROR_CHAN_STATE                                 0x80000009
//**Text:pi action failed 
#define SL_MA_ERROR_START_PI_CAP                               0x8000000A
//**Text:read value failed, cap error
#define SL_MA_ERROR_GET_VALUE_CAP                              0x8000000B
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
// codes for slmalogic                                                       //
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_MA_LOGIC
//**Text:general error
#define SL_MA_LOGIC_ERROR                                         0x80000101
//**Text:the buffer to store program times in is full
#define SL_MA_LOGIC_PROGRAM_TIMES_BUFFER_FULL                     0x80000102
//**Text:return value program loading was successfuly started
#define SL_MA_LOGIC_PROGRAM_LOADING_OK                            0x00000301
//**Text:return value program loading was successfuly finished
#define SL_MA_LOGIC_PROGRAM_LOADING_READY                         0x00000302
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
// codes for slmaformlogic                                                   //
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_MA_FORMLOGIC
//**Text:general error
#define SL_MA_FORMLOGIC_ERROR                                     0x80000101
//**Text:serupro start refused by nck, dry-run is active
#define SL_MA_FORMLOGIC_ERROR_SERUPRO_DRY                         0x80000201
//**Text:Block Search: No search target
#define SL_MA_ERROR_BLOCK_SEARCH_NO_TARGET                        0x80000202
//**Text:Block Search: No search target in a channel
#define SL_MA_ERROR_BLOCK_SEARCH_CHAN_NO_TARGET                   0x80000203
//**Text:Block Search: Step worker error
#define SL_MA_ERROR_BLOCK_SEARCH_STEP_ERROR                       0x80000204
//**Text:Block Search: Chan state is not reset
#define SL_MA_ERROR_BLOCK_SEARCH_NOT_RESET                        0x80000205
//**Text:Block Search: Chan state is not reset or stop
#define SL_MA_ERROR_BLOCK_SEARCH_NOT_RESET_STOP                   0x80000206
//**Text:Block Search: without calculation in main program only
#define SL_MA_ERROR_BLOCK_SEARCH_NOT_MAINPROGRAM                  0x80000207
//**No special text, block search was abort 
#define SL_MA_ERROR_BLOCK_SEARCH_ABORT                            0x80000208
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
// codes for slpaformlogic                                                   //
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_PA_FORMLOGIC
//**Text:general error
#define SL_PA_FORMLOGIC_ERROR                                     0x80000101
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
// codes for slmaform                                                        //
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_MA_FORM
//**Text:general error
#define SL_MA_FORM_ERROR                                          0x80000101
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
// codes for slpaform                                                        //
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_PA_FORM
//**Text:general error
#define SL_PA_FORM_ERROR                                          0x80000101
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
// codes for slstepnclogic                                                   //
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_STEP_NC_CONFIG
//**Text:md service not working, refresh failed
#define SL_STEP_NC_CONFIG_NO_MD                                   0x80000101
//**ErrEndErrorCodes

#endif // SL_MA_ERROR_INCLUDE
