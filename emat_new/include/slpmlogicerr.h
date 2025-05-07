/*! \file   slpmlogicalerr.h
 *  \author Hans-Jürgen Hümmer
 *  \date   20.02.2007
 *  \brief  Error codes for slpmlogic.dll, HMI Solution Line
 *
 *  (C) Copyright Siemens AG 2007
*/

#ifndef SLPM_LOGIC_ERR_H_
#define SLPM_LOGIC_ERR_H_

#include "slerror.h"

///////////////////////////////////////////////////////////////////////////////
//**ModuleCode: 0x01C00000
//**ModuleName: HMI - SlPmLogic
//**TextFile:
//**TextContext:

//**ErrBeginSubModules
//**Name:SlPmLogic filecopy
#define SLPM_LOGIC_FILECOPY   0x00001000
//**Name:SlPmLogic activate definition files
#define SLPM_LOGIC_ACTIVATE   0x00002000
//**Name:SlPmLogic selecting files
#define SLPM_LOGIC_SELFILES   0x00003000
//**Name:SlPmLogic plc function
#define SLPM_LOGIC_PLCCODE    0x00004000
//**ErrEndSubModules

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginGlobalErrorCodes
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SLPM_LOGIC_FILECOPY
//**Text:cannot create a new filename
#define SLPM_NO_NAMEFOUND            0x80000001
//**Text:cannot rename workpiece, contains already new workpiece name
#define SLPM_WORKPIECE_CONFLICT      0x80000002
//**Text:on ncu no directory can be created but a workpiece under /WKS.DIR
#define SLPM_ONLY_WORKPIECE_ON_NCU   0x80000003
//**Text:program can only modified by program correctur because emergency stop
#define SLPM_ISWORKING_EMERGENCYSTOP 0x80000004
//**Text:the program is selected to channel and active
#define SLPM_ISWORKING_NORESET       0x80000005
//**Text:ncu is not in reset state for channel
#define SLPM_NOT_ALL_CHAN_RESETTED   0x80000006
//**Text:no move because destination contains source
#define SLPM_NOMOVE_RECURSION        0x80000007
//**Text:no access level for writing file
#define SLPM_NO_ACCESSLEVEL_WRITE    0x80000008
//**Text:no access level for reading file
#define SLPM_NO_ACCESSLEVEL_READ     0x80000009
//**Text:no access level for deleting file
#define SLPM_NO_ACCESSLEVEL_DELETE   0x8000000A
//**Text:could not delete file
#define SLPM_NO_DELETE               0x8000000B
//**Text:on ncu no directories but workpieces can be renamed
#define SLPM_RENAME_NO_DIR_ON_NCU    0x8000000C
//**Text:destination is not allowed
#define SLPM_ILLEGAL_DESTINATION     0x8000000D
//**Text:extension is not allowed for the destination directory on ncu
#define SLPM_SYNTAX_WRONG_EXTENSION  0x8000000E
//**Text:extension has not exact 3 characters
#define SLPM_SYNTAX_NO_EXTENSION     0x8000000F
//**Text:only character, digit or _
#define SLPM_SYNTAX_WRONG_CHAR       0x80000010
//**Text:name length on ncu max. 28 (with extension)
#define SLPM_SYNTAX_NAME_TOO_LONG    0x80000011
//**Text:the destination device is full
#define SLPM_NOSPACE_ON_DEVICE       0x80000012
//**Text:source has been skipped
#define SLPM_SKIPPED                 0x80000013
//**Text:destination already exist
#define SLPM_EXIST                   0x80000014
//**Text:directory on ncu only extension DIR
#define SLPM_ONLY_DIR_ON_NCU         0x80000015
//**Text:could not delete hmi system directory
#define SLPM_CANT_DELETE_SYSTEM_DIR  0x80000016
//**Text:archive can not be on ncu
#define SLPM_CANT_CREATE_ARC_ON_NCU  0x80000017
//**Text:ostore is active on current channel
#define SLPM_ERROR_OSTORE_ON         0x80000018
//**Text:file is opened by ncu
#define SLPM_OPENED_BY_NCU           0x80000019
//**Text:path length on ncu max. 100 characters
#define SLPM_SYNTAX_PATH_TOO_LONG    0x8000001A
//**Text:workpiece can't contain a subdirectory
#define SLPM_WPD_NO_SUBDIR           0x8000001B
//**Text:extension can't be changed
#define SLPM_FIXED_EXTENSION         0x8000001C
//**Text:on ncu the maximum directory level is 9
#define SLPM_MAX_NCU_DIR_LEVEL       0x8000001D
//**Text:on ncu directory can't conain a subdirectory
#define SLPM_NCU_NO_SUBDIR           0x8000001E
//**Text:file/directory can't be moved to ncu
#define SLPM_CAN_NOT_MOVE_TO_NCU     0x8000001F
//**Text:file type not allowed to workpiece
#define SLPM_ILLEGAL_WORKPIECE_FILE  0x80000090
//**Text:file is distributed by joblist
#define SLPM_DISTRIBUTED_FILE        0x80000091
//**Text:workpiece is distributed by joblist
#define SLPM_DISTRIBUTED_WORKPIECE   0x80000092
//**Text:joblist is active
#define SLPM_DISTRIBUTED_JOBLIST     0x80000093
//**Text:file type not allowed to workpiece on ncu
#define SLPM_NO_NC_WORKPIECE_FILE    0x80000094
//**Text:extension WPD and DIR not allowed for files on ncu
#define SLPM_NO_VALID_NC_FILE_EXT    0x80000095
//**Text:ncu has no access to file
#define SLPM_NCU_NO_ACCESS_TO_FILE   0x80000096
//**Text:type not allowed on ncu
#define SLPM_NCU_TYPE_NOT_ALLOWED    0x80000097
//**Text:inserting to user archive on SinumerikOne needs option P12
#define SLPM_MISSING_P12_FOR_INSERT  0x80000098
//**Text:file is distributed by joblist and NC not in RESET
#define SLPM_DISTRIBUTED_FILE_NO_RESET      0x80000099
//**Text:workpiece is distributed by joblist and NC not in RESET
#define SLPM_DISTRIBUTED_WORKPIECE_NO_RESET 0x8000009A
//**ErrEndErrorCodes

//**ErrBeginErrorCodes:SLPM_LOGIC_ACTIVATE
//**Text:no connection to current ncu
#define SLPM_NCU_IS_OFFLINE          0x80000020
//**Text:no gud data file selected
#define SLPM_NO_GUD_DATAFILE         0x80000021
//**Text:no gud definiton file selected
#define SLPM_NO_DEFINITION_FILE      0x80000022
//**Text:error at reading //NC/DEF.DIR
#define SLPM_ERROR_READING_DEFDIR    0x80000023
//**Text:error at restoring gud file
#define SLPM_ERROR_RESTORE_GUD       0x80000024
//**Text:error at activating gud file
#define SLPM_ERROR_ACTIVATE          0x80000025
//**Text:error at reading gud data files
#define SLPM_ERROR_COLLECTING_DATA   0x80000026
//**Text:file contains no CHANDATA assignment
#define SLPM_NO_DATA_FILE            0x80000027
//**Text:no dependency found for file
#define SLPM_NO_DEPENDENCY           0x80000028
//**Text:error at executing pi for saving data
#define SLPM_ERROR_SAVING_DATA       0x80000029
//**ErrEndErrorCodes

//**ErrBeginErrorCodes:SLPM_LOGIC_SELFILES
//**Text:no item selected
#define SLPM_NO_ITEM_SELECTED        0x80000030
//**Text:no access to filesystem
#define SLPM_NO_ACCESS_FILESYSTEM    0x80000031

//**Text:no write access to siemens directory
#define SLPM_NO_ACCESS_SIEMES        0x80000032
//**Text:minimum write access is system
#define SLPM_WRITE_ACCESS_SYSTEM     0x80000033
//**Text:minimum write access is manufacturer
#define SLPM_WRITE_ACCESS_MANUFACT   0x80000034
//**Text:minimum write access is service
#define SLPM_WRITE_ACCESS_SERVICE    0x80000035
//**Text:minimum write access is user
#define SLPM_WRITE_ACCESS_USER       0x80000036
//**Text:minimum write access is key 3
#define SLPM_WRITE_ACCESS_KEY3       0x80000037
//**Text:minimum write access is key 2
#define SLPM_WRITE_ACCESS_KEY2       0x80000038
//**Text:minimum write access is key 1
#define SLPM_WRITE_ACCESS_KEY1       0x80000039

//**Text:no write access to active file system
#define SLPM_NO_ACCESS_AFS           0x8000003A
//**Text:no write access to a virtual node
#define SLPM_NO_ACCESS_VIRTUAL_NODE  0x8000003B
//**Text:no delete of siemens item
#define SLPM_NO_DELETE_SIEMENS       0x8000003C
//**Text:no archive of siemens files
#define SL_PM_INFO_ARCHIVE_SIEMENS   0x8000003D
//**Text:filename on hmi not longer than 49 bytes
#define SLPM_FILENAME_TOO_LONG       0x8000003E
//**Text:no part program (MPF/SPF)
#define SLPM_NO_PART_PROGRAM         0x8000003F

//**Text:minimum select access is system
#define SLPM_SELECT_ACCESS_SYSTEM    0x80000040
//**Text:minimum select access is manufacturer
#define SLPM_SELECT_ACCESS_MANUFACT  0x80000041
//**Text:minimum select access is service
#define SLPM_SELECT_ACCESS_SERVICE   0x80000042
//**Text:minimum select access is user
#define SLPM_SELECT_ACCESS_USER      0x80000043
//**Text:minimum select access is key 3
#define SLPM_SELECT_ACCESS_KEY3      0x80000044
//**Text:minimum select access is key 2
#define SLPM_SELECT_ACCESS_KEY2      0x80000045
//**Text:minimum select access is key 1
#define SLPM_SELECT_ACCESS_KEY1      0x80000046

//**Text:minimum read access is system
#define SLPM_READ_ACCESS_SYSTEM    0x80000047
//**Text:minimum read access is manufacturer
#define SLPM_READ_ACCESS_MANUFACT  0x80000048
//**Text:minimum read access is service
#define SLPM_READ_ACCESS_SERVICE   0x80000049
//**Text:minimum read access is user
#define SLPM_READ_ACCESS_USER      0x8000004A
//**Text:minimum read access is key 3
#define SLPM_READ_ACCESS_KEY3      0x8000004B
//**Text:minimum read access is key 2
#define SLPM_READ_ACCESS_KEY2      0x8000004C
//**Text:minimum read access is key 1
#define SLPM_READ_ACCESS_KEY1      0x8000004D

//**Text:function not allowed to active file system
#define SLPM_NOT_ALLOWED_AFS       0x8000004E
//**Text:function not allowed to system nck file
#define SLPM_SYSTEM_NCK_FILE       0x8000004F
//**Text:function not allowed to logbook
#define SLPM_NOT_ALLOWED_LOGFILE   0x80000050
//**Text:no access to protected nck file
#define SLPM_PROTECTED_NCK_FILE    0x80000051
//**Text:select subitem of virtual node
#define SLPM_EXPAND_VIRTUAL_NODE   0x80000052
//**Text:file is SIEMENS internal
#define SLPM_SIEMENS_INTERNAL      0x80000053
//**Text:no access to all drives
#define SLPM_DRIVES_ACCESS_ERROR   0x80000054
//**Text:open workpiece directory by return
#define SLPM_RETURN_TO_OPEN_WPD    0x80000055
//**Text:initial file can only selected in a workpiece
#define SLPM_WRONG_DEST_INIFILE    0x80000056
//**Text:device is not mounted
#define SLPM_DEVICE_NOT_MOUNTED    0x80000057
//**Text:no definition file is selected for activation
#define SLPM_NO_DEF_FILE_SELECTED  0x80000058
//**Text:no multiselection allowed
#define SLPM_NO_MULTI_SELECTION    0x80000059
//**Text:file not allowd for edit
#define SLPM_FILE_NO_EDIT          0x8000005A
//**Text:file selected for program select
#define SLPM_FILE_FOR_PROG_SELECT  0x8000005B
//**Text:copy or cut item before paste
#define SLPM_COPY_CUT_BEFORE_PASTE 0x8000005C
//**Text:select control component
#define SLPM_SEL_SETUP_COMPONENT   0x8000005D
//**Text:only programs for open by multiselection
#define SLPM_MULTISEL_ONLY_PROGRAM 0x8000005E
//**Text:too many programs for open
#define SLPM_TOO_MANY_PROGRAMS     0x8000005F

//**Text:minimum delete access is system
#define SLPM_DEL_ACCESS_SYSTEM     0x80000060
//**Text:minimum delete access is manufacturer
#define SLPM_DEL_ACCESS_MANUFACT   0x80000061
//**Text:minimum delete access is service
#define SLPM_DEL_ACCESS_SERVICE    0x80000062
//**Text:minimum delete access is user
#define SLPM_DEL_ACCESS_USER       0x80000063
//**Text:minimum delete access is key 3
#define SLPM_DEL_ACCESS_KEY3       0x80000064
//**Text:minimum delete access is key 2
#define SLPM_DEL_ACCESS_KEY2       0x80000065
//**Text:minimum delete access is key 1
#define SLPM_DEL_ACCESS_KEY1       0x80000066

//**Text:minimum write access is system
#define SLPM_WR_ACCESS_SYSTEM      0x80000067
//**Text:minimum write access is manufacturer
#define SLPM_WR_ACCESS_MANUFACT    0x80000068
//**Text:minimum write access is service
#define SLPM_WR_ACCESS_SERVICE     0x80000069
//**Text:minimum write access is user
#define SLPM_WR_ACCESS_USER        0x8000006A
//**Text:minimum write access is key 3
#define SLPM_WR_ACCESS_KEY3        0x8000006B
//**Text:minimum write access is key 2
#define SLPM_WR_ACCESS_KEY2        0x8000006C
//**Text:minimum write access is key 1
#define SLPM_WR_ACCESS_KEY1        0x8000006D

//**Text:device is write protected
#define SLPM_DEVICE_IS_READONLY    0x80000080
//**Text:error: extmod call call with ncu program
#define SLPM_ERROR_PROG_ON_NCU     0x80000081
//**Text:ncu can't be switched to METRIC
#define SLPM_ERROR_SCALING_METRIC  0x80000082
//**Text:ncu can't be switched to INCH
#define SLPM_ERROR_SCALING_INCH    0x80000083
//**Text:can't open file
#define SLPM_ERROR_OPEN_FILE       0x80000084
//**Text:too many temporary files
#define SLPM_ERROR_TMP_FILE        0x80000085
//**Text:select partition of USB
#define SLPM_USB_SELECT_PARTITION  0x80000086
//**Text:the free space on system cf card is low
#define SLPM_LOW_SPACE_ON_DEVICE   0x80000087
//**Text:the item is write protected
#define SLPM_ITEM_WRITEPROTECTED   0x80000088
//**Text:can't read pipe file
#define SLPM_CANT_READ_PIPE_FILE   0x80000089
//**Text:the tree contains items
#define SLPM_TREE_NOT_EMPTY        0x8000008A
//**Text:datatype can't be selected
#define SLPM_WRONG_EXT_SELECT      0x8000008B
//**Text:select another ncu
#define SLPM_SELECT_NCU            0x8000008C
//**Text:more than one ncuname in joblist SELECT
#define SLPM_DIFFERENT_NCUS        0x8000008D
//**Text:the free space on system cf card (NCU828D) is low
#define SLPM_LOW_SPACE_ON_SYSDRIVE 0x8000008E
//**Text:the free space on system cf card (NCU40D) is low
#define SLPM_LOW_SPACE_ON_CFCARD   0x8000008F
//**Text:the free space on user system cf card (NCU40D) is low
#define SLPM_LOW_SPACE_FOR_USERMEM 0x800000A0
//**Text:the free space on oem system cf card (NCU40D) is low
#define SLPM_LOW_SPACE_FOR_OEMMEM  0x800000A1
//**Text:it is a internal file. Please use a copy
#define SLPM_USE_A_COPY            0x800000A2

//**ErrEndErrorCodes

//**ErrBeginErrorCodes:SLPM_LOGIC_PLCCODE
//**Text:error plc description at line
#define SLPM_PLC_ERROR_FILE        0x80000070
//**Text:error plc description missing address
#define SLPM_PLC_ADDR_MISSING      0x80000071
//**Text:error plc address too large (>65535)
#define SLPM_PLC_ADDR_OVERFLOW     0x80000072
//**Text:error plc address missing destination
#define SLPM_PLC_ADDR_NO_TARGET    0x80000073
//**Text:error plc end address is less than start address
#define SLPM_PLC_ADDR_RANGE        0x80000074
//**Text:error plc address entire DB and byte range of same DB spezified
#define SLPM_PLC_ADDR_CONFLICT     0x80000075
//**Text:error plc description ; must be set before a comment text
#define SLPM_PLC_MISSING_COMMENT   0x80000076
//**Text:error plc missing address of byte range
#define SLPM_PLC_MISSING_ADDRESS   0x80000077
//**Text:error plc byte range must be end with ]
#define SLPM_PLC_MISSING_BRACKET   0x80000078
//**Text:error plc description file is empty
#define SLPM_PLC_EMPTY_FILE        0x80000079
//**ErrEndErrorCodes

//0x80000080-0x8000008F see SLPM_LOGIC_SELFILES
//0x80000090-0x8000009F see SLPM_LOGIC_FILECOPY

#define SLPMFILECOPYRET(lError) (SL_ERR_PMLOGIC|SLPM_LOGIC_FILECOPY|lError)
#define SLPMACTIVATERET(lError) (SL_ERR_PMLOGIC|SLPM_LOGIC_ACTIVATE|lError)
#define SLPMSELFILESRET(lError) (SL_ERR_PMLOGIC|SLPM_LOGIC_SELFILES|lError)
#define SLPMPLCCODERET(lError)  (SL_ERR_PMLOGIC|SLPM_LOGIC_PLCCODE|lError)

#endif // SLPM_LOGIC_ERR_H_
