///////////////////////////////////////////////////////////////////////////////
/*! \file   slsteperror.h
 *  \author Harald Vieten (MG)
 *  \date   07.03.2007
 *  \brief  Errornumber intervals for HMI Solution Line step editor
 *
 *  (C) Copyright Siemens AG A&D MC 2007. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_STEP_ERROR_H)
#define SL_STEP_ERROR_H

#include "slerror.h"

///////////////////////////////////////////////////////////////////////////////
//**ModuleCode: 0x01D00000
//**ModuleName: HMI - SL step editor
//**TextFile:
//**TextContext:

//**ErrBeginSubModules
//**Name:SlStepBaseDataBlock
#define SL_STEP_BASE_DATA_BLOCK           0x00010000
//**Name:SlStepBaseObject
#define SL_STEP_BASE_OBJECT               0x00020000
//**Name:SlStepFormCreator
#define SL_STEP_FORM_CREATOR              0x00030000
//**Name:SlStepObjectCreator
#define SL_STEP_OBJECT_CREATOR            0x00040000
//**Name:SlStepInputData
#define SL_STEP_INPUT_DATA                0x00050000
//**Name:SlEdStepLogic
#define SL_ED_STEP_LOGIC                  0x00060000
//**Name:SlProgramEditFacade
#define SL_PROGRAM_EDIT_FACADE            0x00070000
//**ErrEndSubModules


///////////////////////////////////////////////////////////////////////////////
// Help System error codes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// global errors from         0x80000001 to 0x800000FF
// local errors from          0x80000100 to 0x800003FF
//
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginGlobalErrorCodes
//**Text:no valid toggle states
#define SL_STEP_ERR_NO_VALID_TOGGLE_STATES                     0x80000001
//**Text:no library name was given
#define SL_STEP_ERR_ADD_LIBRARY_NO_NAME                        0x80000002
//**Text:given name is no library or has no form plugin
#define SL_STEP_ERR_ADD_LIBRARY_NO_LIBRARY                     0x80000003
//**Text:no private datas                                                
#define SL_STEP_ERR_ADD_LIBRARY_NO_PRIVATE                     0x80000005
//**Text:no library name was given
#define SL_STEP_ERR_REMOVE_LIBRARY_NO_NAME                     0x80000006
//**Text:no private datas
#define SL_STEP_ERR_REMOVE_LIBRARY_NO_PRIVATE                  0x80000007
//**Text:no plugin found to remove
#define SL_STEP_ERR_REMOVE_LIBRARY_NO_PLUGIN                   0x80000008
//**Text:no library found to remove
#define SL_STEP_ERR_REMOVE_LIBRARY_NO_LIBRARY                  0x80000009
//**Text:library not found
#define SL_STEP_ERR_ADD_LIBRARY_NOT_FOUND                      0x80000010
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
// codes for SlStepBaseDataBlock
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_STEP_BASE_DATA_BLOCK
//**Text:no pointer to parent given
#define SL_STEP_ERR_GET_VALUE_NO_PARENT                        0x80000101
//**Text:no pointer to parent given
#define SL_STEP_ERR_GET_TOGGLE_NO_PARENT                       0x80000102
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
// codes for SlStepBaseObject
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_STEP_BASE_OBJECT
//**Text:no private datas
#define SL_STEP_ERR_SET_APPEARANCE1_NO_PRIVATE                 0x80000101
//**Text:no private datas
#define SL_STEP_ERR_SET_APPEARANCE2_NO_PRIVATE                 0x80000102
//**Text:no private datas
#define SL_STEP_ERR_SET_STREAM_DATAS_NO_PRIVATE                0x80000103
//**Text:no private datas
#define SL_STEP_ERR_INTERPRET_CYCLE_NO_PRIVATE                 0x80000104
//**Text:no private datas
#define SL_STEP_ERR_GENERATE_CYCLE_NO_PRIVATE                  0x80000105
//**Text:empty method of base class called
#define SL_STEP_ERR_INTERPRET_GCODE_EMPTY                      0x80000106
//**Text:no private datas
#define SL_STEP_ERR_GET_VALUE_NO_PRIVATE                       0x80000107
//**Text:no pointer to a value data was retrieved
#define SL_STEP_ERR_GET_VALUE_NO_POINTER                       0x80000108
//**Text:no private datas
#define SL_STEP_ERR_SET_VALUE_NO_PRIVATE                       0x80000109
//**Text:no pointer to a value data was retrieved
#define SL_STEP_ERR_SET_VALUE_NO_POINTER                       0x80000110
//**Text:no private datas
#define SL_STEP_ERR_GET_TOGGLE_NO_PRIVATE                      0x80000111
//**Text:no pointer to a toggle state was retrieved
#define SL_STEP_ERR_GET_TOGGLE_NO_POINTER                      0x80000112
//**Text:no private datas
#define SL_STEP_ERR_SET_TOGGLE_NO_PRIVATE                      0x80000113
//**Text:no pointer to a toggle state was retrieved
#define SL_STEP_ERR_SET_TOGGLE_NO_POINTER                      0x80000114
//**Text:no private datas
#define SL_STEP_ERR_VALID_TOGGLE_NO_PRIVATE                    0x80000115
//**Text:no private datas
#define SL_STEP_ERR_SET_FORM_NUMBER_NO_PRIVATE                 0x80000117
//**Text:empty method of base class called
#define SL_STEP_ERR_CYCLE_KEY_LIST_EMPTY                       0x80000118
//**Text:empty method of base class called
#define SL_STEP_STATE_POST_GENERATOR_EMPTY                     0x00000120
//**Text:empty method of base class called
#define SL_STEP_ERR_CYCLE_NAME_EMPTY                           0x80000121
//**Text:empty method of base class called
#define SL_STEP_ERR_FILL_DIAM_MAP_EMPTY                        0x80000122
//**Text:requested key of value data not found
#define SL_STEP_ERR_TO_VALUE_KEY_NOT_FOUND                     0x80000123
//**Text:requested key of toggle state not found
#define SL_STEP_ERR_TO_TOGGLE_KEY_NOT_FOUND                    0x80000124
//**Text:empty method of base class called
#define SL_STEP_ERR_GENERATE_GCODE_EMPTY                       0x80000125
//**Text:no private datas
#define SL_STEP_ERR_SET_AREA_NO_PRIVATE                        0x80000126
//**Text:no pointer to a toggle state was retrieved
#define SL_STEP_ERR_SET_TOGGLE_VALID_NO_POINTER                0x80000127
//**Text:no private datas
#define SL_STEP_ERR_SET_TECHNOLOGY_NO_PRIVATE                  0x80000128
//**Text:no private datas
#define SL_STEP_ERR_SNAPSHOT_NO_PRIVATE                        0x80000129
//**Text:no private datas
#define SL_STEP_ERR_SET_SNAPSHOT_NO_PRIVATE                    0x80000130
//**Text:no data given to setSnapshot()
#define SL_STEP_ERR_SET_SNAPSHOT_NO_DATA                       0x80000131
//**Text:no private datas
#define SL_STEP_ERR_INTERPRET_WIZARD_NO_PRIVATE                0x80000132
//**Text:no private datas in interpret empty parameter list data block
#define SL_STEP_ERR_INTERPRET_EPL_DB_NO_PRIVATE                0x80000133
//**Text:empty method of base class called
#define SL_STEP_ERR_GENERATE_GCODE_AFTER_CYCLE_EMPTY           0x80000134
//**Text:empty method of base class called
#define SL_STEP_ERR_GENERATE_GCODE_BEFORE_STEP_EMPTY           0x80000135
//**Text:empty method of base class called
#define SL_STEP_ERR_GENERATE_GCODE_AFTER_STEP_EMPTY            0x80000136
//**Text:error in generating step by checking generation
#define SL_STEP_ERR_GENERATOR_INTERPRETER_CHECK                0x80000140
//**Text:empty method of base class called
#define SL_STEP_ERR_INTERPRET_CONTOUR_EMPTY                    0x80000141
//**Text:no private datas
#define SL_STEP_ERR_GET_FORMAT_NO_PRIVATE                      0x80000142
//**Text:requested key in getFormat() not found
#define SL_STEP_ERR_GET_FORMAT_KEY_NOT_FOUND                   0x80000143
//**Text:no nc-code for step was generated
#define SL_STEP_ERR_GENERATOR_NO_STEP_CODE                     0x80000144
//**Text:interpreter needs more nc-code for interpretation
#define SL_STEP_STAT_INTERPRETER_MORE_NC_CODE1                 0x00000145
//**Text:no private datas
#define SL_STEP_ERR_INTERPRET_MULTILINE_NO_PRIVATE             0x80000146
//**Text:empty method of base class called
#define SL_STEP_STATE_GENERATOR_FINISH_EMPTY                   0x00000147
//**Text:no valid pointer given to method as parameter
#define SL_STEP_ERR_GET_END_POINT_PARAMS                       0x80000148
//**Text:no valid pointers given to method as parameter
#define SL_STEP_ERR_GET_TOOL_IDENT_PARAMS                      0x80000149
//**Text:no valid pointer given to method as parameter
#define SL_STEP_ERR_GET_POL_POINT_PARAMS                       0x8000014A
//**Text:no valid pointer given to method scale factor
#define SL_STEP_ERR_SCALE_FACTOR                               0x8000014B
//**Text:no valid pointer given to method programm scale system
#define SL_STEP_ERR_PROGRAM_SCALE_SYSTEM                       0x8000014C
//**Text:no private datas in getDataClass()
#define SL_STEP_ERR_GET_DATA_CLASS_NO_PRIVATE                  0x8000014D
//**Text:requested key in getDataClass() not found
#define SL_STEP_ERR_GET_DATA_CLASS_KEY_NOT_FOUND               0x8000014E
//**Text:no private datas in streamDatas_worker()
#define SL_STEP_ERR_STREAM_DATAS_WORKER_NO_PRIVATE             0x8000014F
//**Text:no call back object given in streamDatas_worker()
#define SL_STEP_ERR_STREAM_DATAS_WORKER_NO_CALL_BACK           0x80000150
//**Text:too much nc-code for multi line interpretation
#define SL_STEP_STAT_INTERPRETER_TOO_MUCH_NC_CODE              0x00000151
//**Text:interpreter found block is a contour
#define SL_STEP_STAT_INTERPRETER_CONTOUR_FOUND                 0x00000152
//**Text:interpreter found block is a wizard
#define SL_STEP_STAT_INTERPRETER_WIZARD_FOUND                  0x00000153
//**Text:interpreter found block is the begining of a known block 
#define SL_STEP_STAT_INTERPRETER_BEGINNING_FOUND               0x00000154
//**Text:interpreter found block is the end of a known block
#define SL_STEP_STAT_INTERPRETER_END_FOUND                     0x00000155
//**Text:interpreter needs more nc-code for interpretation
#define SL_STEP_STAT_INTERPRETER_MORE_NC_CODE2                 0x00000156
//**Text:empty method of base class called
#define SL_STEP_STATE_PRE_GENERATE_CYCLE_EMPTY                 0x00000157
//**Text:generator more nc code to generate
#define SL_STEP_STAT_GENERATOR_MORE_NC_CODE                    0x00000158
//**Text:no interpreter was called when interpreting of wizard code
#define SL_STEP_ERR_INTERPRET_WIZARD_NO_INTERPRETER            0x80000160
//**Text:no stream has wrong (too old?) version
#define SL_STEP_ERR_STREAM_DATAS_WRONG_VERSION                 0x00000159
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
// codes for SlStepInputData
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_STEP_INPUT_DATA
//**Text:read input data no access key given
#define SL_STEP_ERR_INPUT_DATA_READ_NO_ACCESS_KEY              0x80000101
//**Text:read input data no entry found
#define SL_STEP_ERR_INPUT_DATA_READ_NO_ENTRY                   0x80000102
//**Text:read input data wrong version
#define SL_STEP_ERR_INPUT_DATA_READ_WRONG_VERSION              0x80000103
//**Text:read input data no file name was build
#define SL_STEP_ERR_INPUT_DATA_READ_NO_FILE_NAME               0x80000104
//**Text:read input data no data found
#define SL_STEP_ERR_INPUT_DATA_READ_NO_DATA                    0x80000105
//**Text:write input data no access key given
#define SL_STEP_ERR_INPUT_DATA_WRITE_NO_ACCESS_KEY             0x80000151
//**Text:write input data no file name was build
#define SL_STEP_ERR_INPUT_DATA_WRITE_NO_FILE_NAME              0x80000152
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
// codes for SlProgramEditFacade
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_PROGRAM_EDIT_FACADE
//**Text:no pointer to program object
#define SL_FACADE_ERR_NO_EDITOR_OBJ                            0x80000101
//**Text:no pointer to hmi dialog 
#define SL_FACADE_ERR_NO_HMI_DIALOG                            0x80000102
//**Text:no pointer to editor subdialog
#define SL_FACADE_ERR_NO_EDITOR_DIALOG                         0x80000103
//**Text:no program info stored in editor dialog
#define SL_FACADE_ERR_NO_OPEN_FILE_INFO                        0x80000104
//**Text:could not changed r/w mode of program
#define SL_FACADE_ERR_R_RW_CHANGE_ERROR                        0x80000105
//**Text:can not edit program is read only
#define SL_FACADE_ERR_READONLY_ERROR                           0x80000106
//**Text:can not append behind program end
#define SL_FACADE_ERR_PROG_END_EDIT_ERROR                      0x80000107
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
// codes for SlEdStepLogic
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_ED_STEP_LOGIC
#define SL_STEP_ERR_PROTOTYPE_NOT_FOUND                        0x80000100
//**ErrEndErrorCodes

/*! 
 *  \macro SL_STEP_ERROR(X)
 *
 *  Defines the base for return values of the step editor.
 */
#define SL_STEP_ERROR(X)  (SL_ERR_STEP_EDITOR|(X))


///////////////////////////////////////////////////////////////////////////////
// well known error codes
///////////////////////////////////////////////////////////////////////////////

/*!
 *  \def SL_STEP_STAT_MUST_MORE_NC_CODE
 *
 *  Defines the return code for the interpreter if a step must have more nc-code.
 */
#define SL_STEP_STAT_MUST_MORE_NC_CODE  (SL_STEP_ERROR(SL_STEP_BASE_OBJECT|SL_STEP_STAT_INTERPRETER_MORE_NC_CODE1))

/*!
 *  \def SL_STEP_STAT_CAN_MORE_NC_CODE
 *
 *  Defines the return code for the interpreter if a step can have more nc-code.
 */
#define SL_STEP_STAT_CAN_MORE_NC_CODE  (SL_STEP_ERROR(SL_STEP_BASE_OBJECT|SL_STEP_STAT_INTERPRETER_MORE_NC_CODE2))

/*!
 *  \def SL_STEP_STAT_TOO_MUCH_NC_CODE
 *
 *  Defines the return code for the interpreter if last given nc block
 *  doesn't belong to the multi line step.
 */
#define SL_STEP_STAT_TOO_MUCH_NC_CODE (SL_STEP_ERROR(SL_STEP_BASE_OBJECT|SL_STEP_STAT_INTERPRETER_TOO_MUCH_NC_CODE))

/*!
 *  \def SL_STEP_STAT_MORE_NC_CODE
 *
 *  Defines the return code for the interpreter if a step must have more nc-code.
 */
#define SL_STEP_STAT_MORE_NC_CODE  (SL_STEP_ERROR(SL_STEP_BASE_OBJECT|SL_STEP_STAT_GENERATOR_MORE_NC_CODE))

/*!
 *  \def SL_STEP_STAT_CONTOUR_FOUND
 *
 *  Defines the return code for the interpreter if a contour was found.
 */
#define SL_STEP_STAT_CONTOUR_FOUND (SL_STEP_ERROR(SL_STEP_BASE_OBJECT|SL_STEP_STAT_INTERPRETER_CONTOUR_FOUND))

/*!
 *  \def SL_STEP_STAT_WIZARD_FOUND
 *
 *  Defines the return code for the interpreter if a wizard was found.
 */
#define SL_STEP_STAT_WIZARD_FOUND (SL_STEP_ERROR(SL_STEP_BASE_OBJECT|SL_STEP_STAT_INTERPRETER_WIZARD_FOUND))

/*!
 *  \def SL_STEP_STAT_BEGINNING_FOUND
 *
 *  Defines the return code for the interpreter if the begining of a known block 
 */
#define SL_STEP_STAT_BEGINNING_FOUND (SL_STEP_ERROR(SL_STEP_BASE_OBJECT|SL_STEP_STAT_INTERPRETER_BEGINNING_FOUND))

/*!
 *  \def SL_STEP_STAT_END_FOUND
 *
 *  Defines the return code for the interpreter if the end of a known block 
 */
#define SL_STEP_STAT_END_FOUND (SL_STEP_ERROR(SL_STEP_BASE_OBJECT|SL_STEP_STAT_INTERPRETER_END_FOUND))

/*! define a error code for prototype not found */
#define SL_STEP_PROTOTYPE_NOT_FOUND (SL_STEP_ERROR(SL_ED_STEP_LOGIC|SL_STEP_ERR_PROTOTYPE_NOT_FOUND))

/*!
 *  \def SL_STEP_ERR_CHECH_INTERGRITY
 *
 *  define a error code for check integrity error
 */
#define SL_STEP_ERR_CHECH_INTERGRITY (SL_STEP_ERROR(SL_STEP_BASE_OBJECT | SL_STEP_ERR_GENERATOR_INTERPRETER_CHECK))

#endif // SL_STEP_ERROR_H
