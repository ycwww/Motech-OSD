/*! \file   slsuerror.h
 *  \author Andrea Szalontai
 *  \date   01.03.2011
 *  \brief  Errornumber intervals for HMI Operate Inbetriebnahme (Setup)
 *
 *  (C) Copyright Siemens AG A&D MC 2011. All rights reserved.
*/

#if !defined(SL_SU_ERROR_H)
#define SL_SU_ERROR_H


#include "slerror.h"
#include "slhmimakros.h"


///////////////////////////////////////////////////////////////////////////////
//**ModuleCode: 0x02A00000
//**ModuleName: HMI - SL Inbetriebnahme
//**TextFile:
//**TextContext:

//**ErrBeginSubModules
//**Name:SlSu_Profibus
#define SLSU_ERR_PROFIBUS                  0x00000400
//**ErrEndSubModules

//**ErrBeginSubModules
//**Name:SlSu_FileComp
#define SLSU_ERR_FILECOMP                  0x00000800
//**ErrEndSubModules

//**ErrBeginSubModules
//**Name:SlSuMd_File
#define SLSUMD_ERR_FILE                    0x00000C00
//**ErrEndSubModules

//**ErrBeginSubModules
//**Name:SlSuData
#define SLSUDATA_ERR                       0x00001000
//**ErrEndSubModules

//**ErrBeginSubModules
//**Name:SlSuNcMemory
#define SLSU_ERR_NCMEMORY                  0x00001400
//**ErrEndSubModules

//**ErrBeginSubModules
//**Name:SlSuNcPitchErrComp
#define SLSU_PITCH_ERR_COMP                0x00002000
//**ErrEndSubModules

//**ErrBeginSubModules
//**Name:SlSuNcPitchErrComp
#define SLSU_PITCH_ERR_COMP                0x00002000
//**ErrEndSubModules

//**ErrBeginSubModules
//**Name:SlSuCtEditor
#define SLSU_CT_EDI_ERR                    0x00002400
//**ErrEndSubModules


//**ErrBeginGlobalErrorCodes
//**Text:Unknown error
#define SLSU_UNKNOWN_ERROR                 0x80000001
//**ErrEndErrorCodes

//**ErrBeginErrorCodes:SLSU_ERR_PROFIBUS
//**Text:The DLL was not initialized, or it was not possible to read all data.
#define SL_DPERR_NOT_INITIALIZED           0x80000001
//**Text:Toggle indexes are out of range or refer to the same DO.
#define SL_DPERR_TOGGLE_INDEX              0x80000002
//**Text:Not enough free spaces in the given P978 array.
#define SL_DPERR_NO_SPACE_FOR_SORT         0x80000003
//**Text:No free space in the P978 array for the given DO type.
#define SL_DPERR_NO_SPACE_FOR_TYPE         0x80000004
//**Text:The base type of a DO cannot be determined.
#define SL_DPERR_BASE_TYPE                 0x80000005
//**Text:At least two DOs with the same ID.
#define SL_DPERR_DOUBLE_DO_ID              0x80000006
//**Text:The DO type ID is not between 0 and 255.
#define SL_DPERR_INVALID_DO_TYPE           0x80000007
//**Text:The DLL cannot find the requested internal data.
#define SL_DPERR_INTERNAL                  0x80000008
//**Text:Not enough memory to allocate new objects.
#define SL_DPERR_OUT_OF_MEMORY             0x80000009
//**Text:Function was called with invalid parameters.
#define SL_DPERR_INVALID_PARAM             0x8000000A
//**Text:Parameter p9 cannot be set.
#define SL_DPERR_P9_ASYNC                  0x8000000B


//**ErrBeginErrorCodes:SLSU_ERR_FILECOMP
//**Text: QFile error.
#define SL_FC_QFILE_ERROR                  0x80000001
//**Text: Run out of memory.
#define SL_FC_MEMORY_OUT                   0x80000002
//**Text: Bad pointer used.
#define SL_FC_BAD_POINTER                  0x80000003
//**Text: MD modification faild.
#define SL_FC_MD_MODIFY_ERROR              0x80000004
//**Text: Temporary directory not accessible
#define SL_FC_TEMP_DIR_ERROR               0x80000005



//**ErrBeginErrorCodes:SLSUMD_ERR_FILE
//**Text: Destination file name BY SAVE PROCESS does not defined.
#define SLSUMDFILE_NOT_DEF_DEST_FILE_NAME    0x80000001
//**Text: Invalid pointer.
#define SLSUMDFILE_INVALID_POINTER           0x80000002
//**Text: Invalid variable is readed.
#define SLSUMDFILE_INVALID_VARIABLE          0x80000003
//**Text: Inadequate variable type is readed.
#define SLSUMDFILE_INVALID_VAR_TYPE          0x80000004
//**Text: Selected directori path was null.
#define SLSUMDFILE_SEL_DIR_PATH_NULL         0x80000005
//**Text: Screen switching is faild.
#define SLSUMDFILE_SCREEN_SWITCH_FAILD       0x80000006
//**Text: Empty property was readed.
#define SLSUMDFILE_EMPTY_PROPERTY            0x80000007
//**Text: Invalide file type was readed.
#define SLSUMDFILE_INVALID_FILE_TYPE         0x80000008
//**Text: Incorrect unit value.
#define SLSUMDFILE_INCORR_UNIT_VALUE         0x80000009
//**Text: Path does not exists.
#define SLSUMDFILE_PATH_NOT_EXITS            0x8000000A
//**Text: Slot connection faild.
#define SLSUMDFILE_SLOT_CONNECT_FAILD        0x8000000B
//**Text: Slot disconnection faild.
#define SLSUMDFILE_SLOT_DISCONNECT_FAILD     0x8000000C
//**Text: Invalid Call Back pointer.
#define SLSUMDFILE_INVALID_CB_POINTER        0x8000000D
//**Text: Invalid SlArcDrv pointer.
#define SLSUMDFILE_INVALID_ARC_DRV_POINTER   0x8000000E
//**Text: Command can not be interpreted.
#define SLSUMDFILE_NOT_INTERPRETED_COMMAND   0x8000000F
//**Text: Object direct selection faild.
#define SLSUMDFILE_OBJ_DIRECT_SEL_FAIL       0x80000010
//**Text: Inadequate path.
#define SLSUMDFILE_INADEQUATE_PATH           0x80000011
//**Text: Invalid Widget pointer.
#define SLSUMDFILE_INVALID_WIDGET_POINTER    0x80000012
//**Text: Incorrect DG_DLG type.
#define SLSUMDFILE_INCORR_DG_DLG_TYPE        0x80000013
//**Text: QFile error.
#define SLSUMDFILE_FILE_ERROR                0x80000014
//**ErrEndErrorCodes


//**ErrBeginErrorCodes:SLSU_ERR_DRV_AX_ASSIGN
//**Text: Parameter Type Missmatch.
#define SLSU_DRV_AX_ASS_PARAMETER_TYPE_MISM  0x80000001
//**Text: Inconsistant Parameter List. The Count of Parameter Names and Parameter Values aren't equal.
#define SLSU_DRV_AX_ASS_PAR_LIST_INCONSIST   0x80000002
//**Text: Inconsistant Parameter List. The Count of Parameter Names and Parameter Types aren't equal.
#define SLSU_DRV_AX_ASS_PAR_LIST_INCONSIST2  0x80000003
//**Text: Attempt to get a nonexisting parameter.
#define SLSU_DRV_AX_ASS_PAR_NOT_EXIST        0x80000004
//**Text: Invalid Parameter pointer.
#define SLSU_DRV_AX_ASS_INVALID_PAR_POINTER  0x80000005
//**Text: Wrong SlMDText pointer.
#define SLSU_DRV_AX_ASS_SLMDTEXT_POINTER_ERR 0x80000006
//**Text: Invalid Error Object pointer.
#define SLSU_DRV_AX_ASS_INV_ERR_POINTER      0x80000007
//**Text: Invalid Object Handle, Acc Type and Btss Unit.
#define SLSU_DRV_AX_ASS_HANDLE_BTSS_ERR      0x80000008
//**Text: Inadequate Acc Type.
#define SLSU_DRV_AX_ASS_INADEQUATE_ACCTYPE   0x80000009
//**Text: Can't get Acc Type and Unit from SLMD.
#define SLSU_DRV_AX_ASS_SLMD_ERROR_01        0x8000000A
//**Text: Invalide Object Handle.
#define SLSU_DRV_AX_ASS_INVALIDE_OBJ_HANDLE  0x8000000B
//**Text: Wrong SlMD pointer.
#define SLSU_DRV_AX_ASS_SLMD_POINTER_ERR     0x8000000C
//**Text: Drive Object index is out of Boundary.
#define SLSU_DRV_AX_ASS_DRVIDX_OUTOFBOUNDARY 0x8000000D
//**Text: QVariant conversion error.
#define SLSU_DRV_AX_ASS_CONVERSION_ERR       0x8000000E
//**Text: Internal software error.
#define SLSU_AXASS_INTERNAL_ERROR            0x8000000F
//**Text: Timeout when saving a drive object
#define SLSU_AXASS_DO_SAVE_TIMEOUT           0x80000010
//**Text: One or more parameters are not stored in the object parmeter list.
#define SLSU_AXASS_POLLING_DATA_ERROR        0x80000011
//**Text: The Polling was started a secund time.
#define SLSU_AXASS_POLLING_DOUBLE_START      0x80000012
//**Text: Unknown parameter type.
#define SLSU_DRV_AX_ASS_PARAMETER_TYPE_ERROR 0x80000013
//**Text: Asynchron function call aberted by user
#define SLSUDATA_ASYNC_FCT_CALL_ABORTED      0x80000014
//**ErrEndErrorCodes

//**ErrBeginErrorCodes:SLSU_PITCH_ERR_COMP
//**Text: Can't create temporary file for writing
#define SL_PEC_CANT_CREATE_TEMP_FILE         0x80000001
//**Text: Can't open temporary file for reading
#define SL_PEC_CANT_OPEN_TEMP_FILE           0x80000002
//**Text: Error occured while reading machine data
#define SL_PEC_READ_DATA_ERROR               0x80000003
//**Text: Not all channels are in reset state
#define SL_PEC_NC_CHAN_RESET_ERROR           0x80000004

//**ErrEndErrorCodes


//**ErrBeginErrorCodes:SLSU_ERR_NCMEMORY
//**Text: Source file couldn't be found.
#define SLSU_ERR_NCMEMORY_FILE_NOT_FOUND     0x80000001
//**Text: Can not open source file.
#define SLSU_ERR_NCMEMORY_FILE_OPEN          0x80000002
//**Text: The source XML conntent is invalid.
#define SLSU_ERR_NCMEMORY_XML_CONNTENT       0x80000003
//**Text: The source XML conntent data type error.
#define SLSU_ERR_NCMEMORY_XML_CONNTENT_DATA  0x80000004
//**Text: The base data not set.
#define SLSU_ERR_NCMEMORY_BASE_DATA          0x80000005
//**Text: The bate in the source file is not correct.
#define SLSU_ERR_NCMEMORY_DATA_INVALID       0x80000006
//**Text: ID dublication error.
#define SLSU_ERR_NCMEMORY_ID_INVALID         0x80000007
//**Text: Get NCK Version or Type error. 
#define SLSU_ERR_NCMEMORY_GET_NCK_VERSION    0x80000008
//**Text: XML for current NCK version not found. 
#define SLSU_ERR_NCMEMORY_VERSION_XML_NOT_FOUND   0x80000009
//**Text: Data use not enabled for this access level. 
#define SLSU_ERR_NCMEMORY_LOW_ACCESS_LEVEL   0x80000010

//**ErrBeginErrorCodes:SLSU_CT_EDI_ERR
//**Text: File does not exist.
#define SLSU_CT_EDI_ERR_FILE_NOT_EXIST          0x80000001
//**Text: File is already opened.
#define SLSU_CT_EDI_ERR_FILE_ALREADY_OPENED     0x80000002
//**Text: File can not opened.
#define SLSU_CT_EDI_ERR_FILE_OPEN_FAILED        0x80000003
//**Text: File can not parsed.
#define SLSU_CT_EDI_ERR_FILE_PARSE_FAILD        0x80000004
//**Text: Not template file.
#define SLSU_CT_EDI_ERR_FILE_NOT_TEMPLATE       0x80000005
//**Text: <VersionInfo> tag not found.
#define SLSU_CT_EDI_ERR_VERSION_INFO_MISS       0x80000006
//**Text: <FormatVersion> tag not found.
#define SLSU_CT_EDI_ERR_FORMAT_VERSION_MISS     0x80000007
//**Text: Not expected version.
#define SLSU_CT_EDI_ERR_NOT_EXPECTED_VERSION    0x80000008
//**Text: Attempt to close document, but there is no opened document.
#define SLSU_CT_EDI_ERR_NO_OPENED_DOCUMENT      0x80000009
//**Text: Auxiliary file is already opened.
#define SLSU_CT_EDI_ERR_AUX_FILE_ALREADY_OPENED 0x8000000A
//**Text: Not expected auxiliary file for CT-Editor.
#define SLSU_CT_EDI_ERR_FILE_NOT_EXPECTED_AUX   0x8000000B
//**Text: It is not possible to create new template because an other template file is open.
#define SLSU_CT_EDI_ERR_FILE_OTHER_TEMP_OPENED  0x8000000C
//**Text: It is not possible to create new template because the file already exists.
#define SLSU_CT_EDI_ERR_FILE_ALREADY_EXISTS     0x8000000D
//**Text: It is not possible to create new template because the auxiliary file isn't loaded.
#define SLSU_CT_EDI_ERR_FILE_NO_AUX_FILE        0x8000000E
//**Text: It is not possible to open template because the auxiliary file isn't loaded.
#define SLSU_CT_EDI_ERR_FILE_OPEN_NO_AUX_FILE   0x8000000F
//**Text: File can not saved.
#define SLSU_CT_EDI_ERR_FILE_SAVE_FAILED        0x80000010
//**Text: Data not exists.
#define SLSU_CT_EDI_ERR_DATA_NOT_EXISTS         0x80000011
//**Text: Busy.
#define SLSU_CT_EDI_ERR_BUSY                    0x80000012
//**Text: Aborted.
#define SLSU_CT_EDI_ERR_ABORTED                 0x80000013
//**ErrEndErrorCodes

// Error code construction makros
#define SLDRVAX_ERROR(Code) (SL_ERR_SU | SLSUDATA_ERR | (Code))
#define SLSUDATA_ERROR(Code) (SL_ERR_SU | SLSUDATA_ERR | (Code))
#define ERR_CONSTRUCT(Code) (SL_ERR_SU | SLSUDATA_ERR | (Code))
#define SLPITCHERRCOMPERR(Code) (SL_ERR_SU | SLSU_PITCH_ERR_COMP | (Code))
#define SLSU_CT_EDI_ERROR(Code) (SL_ERR_SU | SLSU_CT_EDI_ERR | (Code))
#endif // SL_SU_ERROR_H
