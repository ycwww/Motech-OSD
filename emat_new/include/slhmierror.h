/*! \file   slhmierror.h
 *  \author Gerolf Kuehnel and Hans Hubmann
 *  \date   25.06.2004
 *  \brief  Errornumber intervals for HMI - global classes and utilities
 *
 *  (C) Copyright Siemens AG 2004
*/

#if !defined(SL_HMI_ERROR_INCLUDE)
#define SL_HMI_ERROR_INCLUDE

#include "slerror.h"

///////////////////////////////////////////////////////////////////////////////
//**ModuleCode: 0x00900000
//**ModuleName: HMI - SL Utilities
//**TextFile:
//**TextContext:

//**ErrBeginSubModules
//**Name:SlHmiFileAccess
#define SL_HMI_FILE_ACCESS          0x00000400
//**Name:SlHmiSettings
#define SL_HMI_SETTINGS             0x00000800
//**Name:SlHmiDoubleBuffer
#define SL_HMI_DOUBLE_BUFFER        0x00001000
//**Name:SlHmiFunctions
#define SL_HMI_FUNCTIONS            0x00002000
//**Name:SlHmiConverter
#define SL_HMI_CONVERTER            0x00004000
//**Name:SlHmiConverterEngine
#define SL_HMI_CONVERTER_ENGINE     0x00008000
//**Name:SlHmiCalculator
#define SL_HMI_CALCULATOR           0x00010000
//**ErrEndSubModules

///////////////////////////////////////////////////////////////////////////////
// global error codes
///////////////////////////////////////////////////////////////////////////////

//**ErrBeginGlobalErrorCodes
//**Text:file not found
#define SL_HMI_FILE_NOT_FOUND   0x80000001
//**Text:no memory could be allocated
#define SL_HMI_NO_MEMORY        0x80000002
//**Text:Access was denied by OS
#define SL_HMI_FILE_ACCESS_DENIED 0x80000003
//**Text:no search directories are defined
#define SL_HMI_NO_SEARCH_DIRS 0x80000004
//**Text:the write file couldn't be generated
#define SL_HMI_FILE_NOT_CREATED 0x80000005
//**Text:unnown error
#define SL_HMI_UNKNOWN_ERROR 0x800000FF
//**Text:the subdirectory could not be found / doesn't exist
#define SL_HMI_HMI_DIR_NOT_EXIST    0x00000001
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
// Errorcodes for SlHmiFileAccess
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_HMI_FILE_ACCESS
//**Text:the imagefile does not exist for the given resolution
#define SL_HMI_IMAGE_RES_NOT_EXIST        0x00000101
//**Text:there is no directory for the given resolution
#define SL_HMI_RES_DIR_NOT_EXIST    0x80000102
//**Text:The given image could not be loaded, QPixmap::load returned false.
#define SL_HMI_IMAGE_NOT_LOADED        0x80000103
//**Text:The given category does not exist, a user dir was returned.
#define SL_HMI_CATEGORY_NOT_EXIST        0x80000104
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
// Errorcodes for SlHmiSettings and SlHmiIniSettings
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_HMI_SETTINGS
//**Text:the given entry does not exist
#define SL_HMI_ENTRY_NOT_EXIST          0x80000101
//**Text:the given section does not exist
#define SL_HMI_SECTION_NOT_EXIST        0x80000102
//**Text:the profile does not exist
#define SL_HMI_PROFILE_NOT_EXIST        0x80000103
//**Text:the settings could not be written, cause there is no space on HD
#define SL_HMI_FS_NO_SPACE_ON_HD        0x80000104
//**Text:the file is readonly, so nothing was written
#define SL_HMI_FILE_READ_ONLY             0x80000105
//**Text:the directory to write to does not exist
#define SL_HMI_HMI_USER_DIR_NOT_EXIST   0x80000106
//**Text:value type for XML is not supported, e.g. ByteArray
#define SL_HMI_INVALID_VALUETYPE        0x80000107
//**Text: File is not open or cannot be opened
#define SL_HMI_FILE_NOT_OPEN            0x80000108
//**Text: File cannot be locked
#define SL_HMI_FILE_NOT_LOCKED          0x80000109
//**Text: File is already open
#define SL_HMI_FILE_ALREADY_OPEN        0x80000110
//**Text: Error in XML-File
#define SL_HMI_INVALID_XML              0x80000111
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
// Errorcodes for SlHmiConverter
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_HMI_CONVERTER
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
// Errorcodes for SlHmiConverterEngine
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_HMI_CONVERTER_ENGINE
//**Text:The converter engine was given an invalid converter job.
#define SL_HMI_CVE_INVALID_JOB          0x80000001
//**Text:The converter used has either specified no input or output files.
#define SL_HMI_CVE_NO_FILES             0x80000002
//**Text:The converter job list was empty.
#define SL_HMI_CVE_JOB_LIST_EMPTY       0x80000003
//**Text:One or more conversion failed while processing a batch conversion.
#define SL_HMI_CVE_BATCH_CONVERT_ERROR  0x00000004
//**Text:The loaded library is not a plugin library.
#define SL_HMI_CVE_NOT_A_PLUGIN_LIB     0x80000005
//**Text:No converter was found for the specified file.
#define SL_HMI_CVE_NO_CONVERTER_FOUND   0x80000006
//**Text:A converter could not be created.
#define SL_HMI_CVE_CONVERTER_CREATE_ERROR 0x80000007
//**Text:The implementation string of the converter is wrong. It has the syntax "library.classname"
#define SL_HMI_CVE_WRONG_IMPLEMENTATION 0x80000008
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
// Errorcodes for Calculator
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_HMI_CALCULATOR
//**Text:Divisor zero, unusable result
#define SL_HMI_NULL_DIVISION    0x80000040
//**Text:Term incorrect, unusable result
#define SL_HMI_CONVERSION_ERROR    0x80000041
//**Text:Result greater maximal allowed value, unusable result
#define SL_HMI_RANGE_EXCEEDED    0x80000042
//**Text:Negative result not allowed, unusable result
#define SL_HMI_NEGATIVE_BINARY_NUMBER    0x80000043
//**Text:Negative result not allowed, unusable result
#define SL_HMI_NEGATIVE_HEX_NUMBER    0x80000044
//**Text:calculator was aborted
#define SL_HMI_CALCULATION_ABORTED    0x80000045
//**Text:there was a negative number for a sqrt function call
#define SL_HMI_NEGATIVE_ROOT          0x80000046
//**Text:fit could not be calculated due to an invalid quality (Toleranzgrad) given
#define SL_HMI_FIT_INVAL_QUALITY  0x80000047
//**Text:fit could not be calculated due to an invalid position (Toleranzlage) given
#define SL_HMI_FIT_INVAL_POS  0x80000048
//**Text:fit could not be calculated due to an invalid diameter given
#define SL_HMI_FIT_INVAL_DIAM 0x80000049
//**Text:fit could not be calculated due to an undefined error
#define SL_HMI_FIT_UNDEFINED_ERROR 0x80000050
//**Text:calculation Term incomplete
#define SL_HMI_TERM_INCOMPLETE 0x80000051
//**ErrEndErrorCodes


#endif // SL_HMI_ERROR_INCLUDE


