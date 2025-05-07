/*! \file   slgfwerror.h
 *  \author Gerolf Kuehnel and Hans Hubmann
 *  \date   07.11.2003
 *  \brief  Errornumber intervals for HMI - SL Framework
 *
 *  (C) Copyright Siemens AG 2003
*/

#if !defined(SL_GFW_ERROR_INCLUDE)
#define SL_GFW_ERROR_INCLUDE

#include "slerror.h"

///////////////////////////////////////////////////////////////////////////////
//**ModuleCode: 0x00100000
//**ModuleName: HMI - SL GuiFramework
//**TextFile:
//**TextContext:

//**ErrBeginSubModules
//**Name:SlGfwLineEdit
#define SL_GFW_LINEEDIT             0x00001000
//**Name:SlGfwComboBox
#define SL_GFW_COMBOBOX             0x00002000
//**Name:SlGfwListBox
#define SL_GFW_LISTBOX              0x00003000
//**Name:SlGfwToggleBox
#define SL_GFW_TOGGLEBOX            0x00004000
//**Name:SlGfwCheckBox
#define SL_GFW_CHECKBOX             0x00005000
//**Name:SlGfwOptionButton
#define SL_GFW_OPTIONBUTTON         0x00006000
//**Name:SlGfwLabel
#define SL_GFW_LABEL                0x00007000
//**Name:SlGfwFormWidget
#define SL_GFW_FORMWIDGET           0x00008000
//**Name:SlGfwSoftKey
#define SL_GFW_SOFTKEY              0x00009000
//**Name:SlGfwHmiSoftKey
#define SL_GFW_HMI_SOFTKEY          0x0000A000
//**Name:SlGfwDialogBar
#define SL_GFW_DIALOGBAR            0x0000B000
//**Name:SlGfwHmiDialogBar
#define SL_GFW_HMI_DIALOGBAR        0x0000C000
//**Name:SlGfwGuiComponentManager
#define SL_GFW_GUI_COMPONENT_MGT    0x0000E000
//**Name:SlGfwHmiDialog
#define SL_GFW_HMI_DIALOG           0x0000F000
//**Name:SlGfwHmiPanel
#define SL_GFW_HMI_PANEL            0x00010000
//**Name:SlGfwSerializeManager
#define SL_GFW_SERIALIZE_MGT        0x00020000
//**Name:SlGfwConverter
#define SL_GFW_CONVERTER            0x00030000
//**Name:SlGfwPdfWidget
#define SL_GFW_PDF_WIDGET           0x00040000
//**ErrEndSubModules



///////////////////////////////////////////////////////////////////////////////
// Framework error codes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// general errors from 0x80000001 to 0x8000003F
//**ErrBeginGlobalErrorCodes
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
// Errorcodes for LineEdit
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Errorcodes for ComboBox
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Errorcodes for ListBox
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Errorcodes for ToggleBox
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Errorcodes for CheckBox
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Errorcodes for OptionButton
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Errorcodes for Label
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Errorcodes for FormWidget
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Errorcodes for SoftKey
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Errorcodes for HmiSoftKey
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Errorcodes for DialogBar
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Errorcodes for HmiDialogBar
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Errorcodes for SlGfwGuiComponentManager
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_GFW_GUI_COMPONENT_MGT
//**Text:plugin library could not be found
#define SL_GFW_GCM_LIB_NOT_FOUND           0x80000001
//**Text:Library is not a GUI framework plugin library. The main reason for this error is that the library depends on other libraries and one or more of these other libraries are missing or incompatible. Check with Dependency Walker or similar tools.
#define SL_GFW_GCM_NO_PLUGIN_LIBRARY       0x80000002
//**Text:Plugin does not support requested plugin interface
#define SL_GFW_GCM_NO_INTERFACE            0x80000003
//**Text:No class name for gui component was specified
#define SL_GFW_GCM_NO_CLASS_NAME           0x80000004
//**Text:GUI component could not be created. Please check the appl and base directory within the oem and user path. The main reason for this error is that binary incompatible versions of some libraries are located in one of these directories.
#define SL_GFW_GCM_COMPONENT_CREATE_FAILED 0x80000005
//**Text:GUI component does not exist
#define SL_GFW_GCM_NO_COMPONENT            0x80000006
//**Text:GUI component does not exist
#define SL_GFW_GCM_COMPONENT_EXISTS        0x00000007
//**Text:An OA Runtime option is needed but not set
#define SL_GFW_GCM_NO_OA_RUNTIME_OPTION    0x80000008
//**Text:A facade with the given name or pointer is already registered.
#define SL_GFW_GCM_FACADE_ALREADY_REGISTERED 0x80000050
//**Text:A facade with the given name is not registered.
#define SL_GFW_GCM_FACADE_NOT_REGISTERED   0x80000050
//**Text:Invalid argument for this function call
#define SL_GFW_INVALID_ARGUMENT            0x80000100
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
// Errorcodes for SlGfwHmiDialog
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_GFW_HMI_DIALOG
//**Text:no configuration file and class name specified
#define SL_GFW_DLG_CONF_NOT_SPECIFIED           0x80000002
//**Text:configuration file could not be found
#define SL_GFW_DLG_CONF_NOT_FOUND               0x80000003
//**Text:configuration file could not be opened
#define SL_GFW_DLG_CONF_OPEN_ERROR              0x80000004
//**Text:configuration file has incompatible version
#define SL_GFW_DLG_CONF_INCOMPATIBLE            0x80000005
//**Text:file is not a dialog configuration file
#define SL_GFW_DLG_CONF_TYPE                    0x80000006
//**Text:the dialog configuration is not loaded
#define SL_GFW_DLG_CONF_NOT_LOADED              0x80000007
//**Text:The menu does not exist
#define SL_GFW_MENU_NOT_EXIST                   0x80000010
//**Text:The etc level does not exist on the menu
#define SL_GFW_ETC_NOT_EXIST                    0x80000011
//**Text:The softkey is not in the specified softkey group
#define SL_GFW_SOFTKEY_IS_NOT_IN_GROUP          0x80000012
//**Text:The softkey does not exist
#define SL_GFW_SOFTKEY_NOT_EXIST                0x80000013
//**Text:The softkey is not a toggle softkey
#define SL_GFW_SOFTKEY_IS_NOT_TOGGLE            0x80000014
//**Text:The profile does not exist in the toggle softkey
#define SL_GFW_TOGGLE_SOFTKEY_PROFILE_NOT_EXIST 0x80000015
//**Text:The screen does not exist / is not configured.
#define SL_GFW_SCREEN_NOT_EXIST                 0x80000016
//**Text:A screen change was denied by the current screen or dialog.
#define SL_GFW_SCREEN_CHANGE_DENIED             0x80000017
//**Text:Invalid argument for this function call
#define SL_GFW_INVALID_ARGUMENT                 0x80000100
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
// Errorcodes for SlGfwHmiPanel
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_GFW_HMI_PANEL
//**Text:no configuration file and class name specified
#define SL_GFW_PAN_CONF_NOT_SPECIFIED           0x80000002
//**Text:configuration file could not be found
#define SL_GFW_PAN_CONF_NOT_FOUND               0x80000003
//**Text:configuration file could not be opened
#define SL_GFW_PAN_CONF_OPEN_ERROR              0x80000004
//**Text:configuration file has incompatible version
#define SL_GFW_PAN_CONF_INCOMPATIBLE            0x80000005
//**Text:file is not a panel configuration file
#define SL_GFW_PAN_CONF_TYPE                    0x80000006
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
// Errorcodes for SlGfwSerializeManager
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_GFW_SERIALIZE_MGT
//**Text:persistance file could not be opened
#define SL_GFW_SMGT_FILE_OPEN_ERROR             0x80000001
//**Text:persistance file is empty and contains no data
#define SL_GFW_SMGT_FILE_EMPTY                  0x80000002
//**Text:serialized data for an object was not found in the persistance file
#define SL_GFW_SMGT_OBJECT_NOT_FOUND            0x80000003
//**Text:a serialize transaction on the persistance file is already running
#define SL_GFW_SMGT_TRANSACTION_IS_RUNNING      0x80000004
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
// Errorcodes for SlGfwConverter
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_GFW_CONVERTER
//**Text:The XML file was not found.
#define SL_GFW_CV_XML_FILE_NOT_FOUND            0x80000001
//**Text:The XML could not be opened.
#define SL_GFW_CV_XML_FILE_OPEN_ERROR           0x80000002
//**Text:The XML parser could not parse the file because it contains errors.
#define SL_GFW_CV_XML_CONTENT_ERROR             0x80000003
//**Text:The HMI file was not found.
#define SL_GFW_CV_HMI_FILE_NOT_FOUND            0x80000004
//**Text:The HMI could not be opened.
#define SL_GFW_CV_HMI_FILE_OPEN_ERROR           0x80000005
//**Text:The HMI which should be read has the wrong type.
#define SL_GFW_CV_HMI_FILE_WRONG_TYPE           0x80000006
//**Text:The HMI which should be read has an incompatible version.
#define SL_GFW_CV_HMI_FILE_WRONG_VERSION        0x80000007


//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
// Errorcodes for SlGfwPdfWidget
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_GFW_PDF_WIDGET
//**Text:couldn't open the PDF file
#define SL_GFW_PFD_ERR_OPEN_FILE                0x80000001
//**Text:couldn't read the page catalog
#define SL_GFW_PFD_ERR_BAD_CATALOG              0x80000002
//**Text:PDF file was damaged and couldn't be repaired
#define SL_GFW_PFD_ERR_DAMAGED                  0x80000003
//**Text:file was encrypted and password was incorrect or not supplied
#define SL_GFW_PFD_ERR_ENCRYOTED                0x80000004
//**Text:nonexistent or invalid highlight file
#define SL_GFW_PFD_ERR_HIGHLIGHT_FILE           0x80000005
//**Text:invalid printer
#define SL_GFW_PFD_ERR_BAD_PRINTER              0x80000006
//**Text:error during printing
#define SL_GFW_PFD_ERR_BAD_PRINTING             0x80000007
//**Text:PDF file doesn't allow that operation
#define SL_GFW_PFD_ERR_PERMISSION               0x80000008
//**Text:invalid page number
#define SL_GFW_PFD_ERR_BAD_PAGE_NUM             0x80000009
//**Text:file I/O error
#define SL_GFW_PFD_ERR_FILE_IO                  0x80000010
//**Text:NULL object handle
#define SL_GFW_PFD_ERR_NO_HANDLE                0x80000011
//**Text:out of memory
#define SL_GFW_PFD_ERR_OUT_OF_MEMORY            0x80000012
//**Text:PDF component is busy
#define SL_GFW_PFD_ERR_BUSY                     0x80000013
//**Text:invalid argument
#define SL_GFW_PFD_ERR_BAD_ARG                  0x80000014
//**Text:unknown error
#define SL_GFW_PFD_ERR_UNKNOWN                  0x80000015
//**ErrEndErrorCodes


#endif // SL_GFW_ERROR_INCLUDE
