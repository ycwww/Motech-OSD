/*! \file   slfverror.h
 *  \author Lars Lechner und Holger Strobelt
 *  \date   August.2004
 *  \brief  Errornumber intervals for HMI - FV FileViewer
 *
 *  (C) Copyright Siemens AG 2004
*/

#if !defined(SL_FV_ERROR_H)
#define SL_FV_ERROR_H


#include "slerror.h"

///////////////////////////////////////////////////////////////////////////////
//**ModuleCode: 0x00A00000
//**ModuleName: HMI - SL FileViewer
//**TextFile:
//**TextContext:


//**ErrBeginSubModules
//**Name:FileViewerWidget
#define SL_FV_WIDGET              0x00001000
//**Name:DataModel
#define SL_FV_DATA_MODEL          0x00002000
//**Name:ConfigFile
#define SL_FV_CONFIG_FILE         0x00003000
//**Name:ViewBase
#define SL_FV_VIEW_BASE           0x00004000
//**Name:CollectorBase
#define SL_FV_FS_COLLECTOR        0x00010000
//**ErrEndSubModules

///////////////////////////////////////////////////////////////////////////////
// FileViewer error codes
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginGlobalErrorCodes
//**Text:no error
#define SL_FV_NO_ERROR                  SL_ERR_SUCCESS
//**Text:no memory could be allocated
#define SL_FV_NO_MEMORY                      0x80000001
//**Text:refresh of file or all open folders failed
#define SL_FV_REFRESH_FAILED                 0x80000002
//**Text:open directories failed
#define SL_FV_OPEN_FAILED                   0x80000003
//**Text:close directories failed
#define SL_FV_CLOSE_FAILED                  0x80000004
//**Text:getting attributes failed
#define SL_FV_GET_ATTRIBUTES_FAILED         0x80000005
//**Text:no nc found
#define SL_FV_NO_NC                         0x80000006
//**Text:The folder or file doesn't exist
#define SL_FV_NO_ITEM                     0x80000007
//**Text:setting data managment failed
#define SL_FV_SET_DATA_MANAG_FAILED         0x80000008
//**Text:setting view failed
#define SL_FV_SET_VIEW_FAILED               0x80000009
//**Text:setting file viewer widget failed
#define SL_FV_SET_WIDGET_FAILED             0x8000000A
//**Text:setting data collector failed
#define SL_FV_SET_DATA_COLL_FAILED          0x8000000B
//**Text:item was not selected/deselected
#define SL_FV_SET_SELECTED_FAILED           0x8000000C
//**Text:column index to big
#define SL_FV_NO_COLUMN                     0x8000000D
//**Text:config file could not opened
#define SL_FV_OPEN_CONFIG_FILE_FAILED       0x8000000E
//**Text:config file content could not be set to dom document
#define SL_FV_SET_DOM_CONTENT_FAILED        0x8000000F
//**Text:sort is not enable
#define SL_FV_SORT_NOT_ENABLED              0x80000010
//**Text:opening of a folder was stopped by fileviewer
#define SL_FV_SUPRESS_OPEN_FOLDER           0x80000011
//**Text:pointer contains no valid value
#define SL_FV_POINTER_NOT_INITIALIZED       0x80000012
//**Text:fileViewer is not connected to fileService
#define SL_FV_IS_NOT_ONLINE                 0x80000013
//**Text:the given node is not virtual
#define SL_FV_NODE_NOT_VIRTUAL              0x80000014
//**Text:Parent/Root/Start node not found
#define SL_FV_PARENT_NODE_NOT_FOUND         0x80000015
//**Text:Directory path already fetched
#define SL_FV_DIR_PATH_ALREADY_FETCHED      0x00000010
//**ErrEndErrorCodes

//**ErrBeginErrorCodes:SL_FV_WIDGET
//**Text:view dll not found
#define SL_FV_WIDGET_NO_VIEW                0x80000155
//**Text:collector dll not found
#define SL_FV_WIDGET_NO_COLLECTOR           0x80000156
//**ErrEndErrorCodes

//**ErrBeginErrorCodes:SL_FV_DATA_MODEL
//**Text:You can not change the data while the model is refreshing 
#define SL_FV_REFRESH_LOCK                  0x80000001
//**Text:Child nodes could not be inserted, because the parent is not a virtual node
#define SL_FV_INSERT_CHILD_NODES_OF_FAILED  0x80000002
//**Text:A node could not be removed, because its parent is not a virtual node
#define SL_FV_REMOVE_NODE_FAILED            0x80000003
//**Text:An asynchronous operation was aborted because the node was removed
#define SL_FV_OPERATION_ABORTED             0x80000004
//**Text:The model index given to the file viewer was not legal for its data model (e.g. index of other file viewer, row or column out of range)
#define SL_FV_ILLEGAL_MODEL_INDEX           0x80000005
//**ErrEndErrorCodes

//**ErrBeginErrorCodes:SL_FV_FS_COLLECTOR
//**Text:The file service adapter could not be initialized
#define SL_FV_FS_ADAPTER_INIT_FAILED        0x80000001
//**ErrEndErrorCodes

#endif // SL_FV_ERROR_H
