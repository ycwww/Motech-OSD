/*! 
 *  \file	slatwerror.h
 *  \author Krisztian Balogh
 *  \date   23.08.2013
 *
 *  Header-File with errorcodes for Operate-ATW
*/

#ifndef SL_ATW_ERROR_H
#define SL_ATW_ERROR_H

#include "slerror.h"

//**ModuleCode:0x03100000
//**ModuleName:HMI - Operate-ATW
//**TextFile:
//**TextContext:

// modules
//**ErrBeginSubModules
//**Name: SlAtwAtcGen
#define SL_ATW_ATC_ERROR_BIT               0x00000400     //!< module ATW file and certificate generator
//**Name: SlAtwLogic
#define SL_ATW_LOGIC_ERROR_BIT             0x00000800     //!< module ATW Logic
//**Name: SlAtwDialog
#define SL_ATW_DIALOG_ERROR_BIT            0x00001000     //!< module ATW Dialog


//**ErrEndSubModules
 
/////////////////
// error codes //
/////////////////
//**ErrBeginGlobalErrorCodes
//**Text: no error
#define SL_ATW_ERROR_SUCCESS                               0x00000000  //!< no error

// general errors                                                  
//**Text: internal error
#define SL_ATW_ERROR_INTERNAL_ERR                          0x80000001  //!< internal error
//**Text: unknown error
#define SL_ATW_ERROR_UNKNOWN_ERR                           0x80000002  //!< unknown error
//**Text: no memory
#define SL_ATW_ERROR_NO_MEMORY                             0x80000003  //!< no memory
//**Text: not implemented yet
#define SL_ATW_ERROR_NOT_IMPLEMENTED                       0x80000004  //!< not implemented yet
//**Text: could not open file
#define SL_ATW_ERROR_FILE_OPEN                             0x80000005  //!< could not open file
//**Text: file is corrupt
#define SL_ATW_ERROR_BAD_FILE                              0x80000006  //!< file is corrupt
//**Text: invailid function parameters
#define SL_ATW_ERROR_INV_PARAM                             0x80000007  //!< invailid function parameters
//**Text: function failed
#define SL_ATW_ERROR_NOT_OK                                0x80000008  //!< function failed
//**Text: no iface, that handles this request
#define SL_ATW_ERROR_NOT_HANDLED                           0x80000009  //!< no iface, that handles this request
//**Text: file does not exist
#define SL_ATW_ERROR_FILE_NOT_FOUND                        0x8000000A  //!< file does not exist
//**Text: error on reading file
#define SL_ATW_ERROR_FILE_READ                             0x8000000B  //!< error on reading file
//**Text: error on writing file
#define SL_ATW_ERROR_FILE_WRITE                            0x8000000C  //!< error on writing file
//**Text: file too big to read
#define SL_ATW_ERROR_FILE_TOO_BIG                          0x8000000D  //!< file too big to read
//**Text: component busy, function execution not possible at the moment
#define SL_ATW_ERROR_BUSY                                  0x8000000E  //!< component busy, function execution not possible at the moment
//**Text: function not allowed
#define SL_ATW_ERROR_ACCESS_DENIED                         0x8000000F  //!< function not allowed

// specific errors                                                 
//**Text: file content not valid
#define SL_ATW_ERROR_FILE_NOT_VALID                        0x80000101  //!< file content not valid
//**Text: data not found
#define SL_ATW_ERROR_DATA_NOT_FOUND                        0x80000102  //!< data not found
//**Text: process aborted (invalid state)
#define SL_ATW_ERROR_ABORT                                 0x80000103  //!< process aborted (invalid state)
//**Text: file version is not valid
#define SL_ATW_ERROR_VERSION                               0x80000104  //!< file version is not valid
//**Text: session data and machine data do not match
#define SL_ATW_ERROR_SESSION_MISMATCH                      0x80000105  //!< session data and machine data do not match
//**Text: template version number does not match ATW version
#define SL_ATW_ERROR_TEMPLATE_VERSION                      0x80000106  //!< template version number does not match ATW version
//**Text: template syntax error
#define SL_ATW_ERROR_TEMPLATE_SYNTAX                       0x80000107  //!< template syntax error
//**Text: template syntax error
#define SL_ATW_PROGRESS_VSK_CANCEL                         0x80000108  //!< process aborted (user interaktion)
//**Text: atw in offline modus
#define SL_ATW_ERROR_OFFLINE                               0x80000109  //!< atw in offline modus


/////////////////////// 
// error calculators //
///////////////////////
#define SLATW_ATC_ERR(nError)    SL_ATW_ATC_ERROR_BIT    |SL_ERR_ATW |nError  //!< Error calc. for module AtwAtcGen
#define SLATW_LOGIC_ERR(nError)  SL_ATW_LOGIC_ERROR_BIT  |SL_ERR_ATW |nError  //!< Error calc. for module AtwLogic
#define SLATW_DIALOG_ERR(nError) SL_ATW_DIALOG_ERROR_BIT |SL_ERR_ATW |nError  //!< Error calc. for module AtwDialog

//**ErrEndErrorCodes

#endif // SL_ATW_ERROR_H
