/*-----------------------------------------------------------------------------
 *    Copyright (C) Siemens AG 2004-2008   All Rights Reserved.   Confidential
 *-----------------------------------------------------------------------------
 *
 *-----------------------------------------------------------------------------
 * Projekt:             HMI
 * Modul:               SLKEYS.H  Keyboard Definitions
 * Bearbeiter:          Nickel
 *-----------------------------------------------------------------------------
 * Change Log:
 *
 *-----------------------------------------------------------------------------
*/

#ifndef _SLKEYS_H
#define _SLKEYS_H

//-----------------------------------------------------------------------------
//                            ====================
//     1.                     KEY-CODE DEFINITIONS      (numeral organized)
//                            ====================
//-----------------------------------------------------------------------------

// some abbreviations
// HU = horizontal upper (upper horizontal softkey bar)
// VR = vertical right   (right vertical softkey bar)
// HL = horizontal lower (lower horizontal softkey bar)
// VL = vertical left    (left vertical softkey bar)

//key type definition
#define SL_SOFTKEY_TYPE                   0x10000000
#define SL_HARDKEY_TYPE                   0x20000000
#define SL_HOTKEY_TYPE                    0x40000000

#define SL_TYPE_MASK                      0x70000000 //use dialogmanager



//softkeybar help definition
#define SL_KEYPAD_HU                      0x00010000 // horizontal upper bar
#define SL_KEYPAD_VR                      0x00020000 // vertical right bar
#define SL_KEYPAD_HL                      0x00030000 // horizontal lower bar
#define SL_KEYPAD_VL                      0x00040000 // vertical left bar
#define SL_KEYPAD_US_VL                   0x00050000 // upper screen vertical left bar
#define SL_KEYPAD_US_VR                   0x00060000 // upper screen vertical right bar
#define SL_KEYPAD_MASK                    0x000F0000 //use dialogmanager


//softkeyposition help definition
#define SL_SOFTKEY_1                      0x00000001
#define SL_SOFTKEY_2                      0x00000002
#define SL_SOFTKEY_3                      0x00000003
#define SL_SOFTKEY_4                      0x00000004
#define SL_SOFTKEY_5                      0x00000005
#define SL_SOFTKEY_6                      0x00000006
#define SL_SOFTKEY_7                      0x00000007
#define SL_SOFTKEY_8                      0x00000008
#define SL_SOFTKEY_9                      0x00000009
#define SL_SOFTKEY_10                     0x0000000A
#define SL_SOFTKEY_MASK                   0x0000000F //use dialogmanager


// the combination from softkeybar and softkeyposition yields
// the information for the dialog manager.
#define SL_KEYINFO_HU_SK1                 (SL_KEYPAD_HU | SL_SOFTKEY_1 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_HU_SK2                 (SL_KEYPAD_HU | SL_SOFTKEY_2 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_HU_SK3                 (SL_KEYPAD_HU | SL_SOFTKEY_3 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_HU_SK4                 (SL_KEYPAD_HU | SL_SOFTKEY_4 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_HU_SK5                 (SL_KEYPAD_HU | SL_SOFTKEY_5 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_HU_SK6                 (SL_KEYPAD_HU | SL_SOFTKEY_6 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_HU_SK7                 (SL_KEYPAD_HU | SL_SOFTKEY_7 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_HU_SK8                 (SL_KEYPAD_HU | SL_SOFTKEY_8 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_HU_SK9                 (SL_KEYPAD_HU | SL_SOFTKEY_9 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_HU_SK10                (SL_KEYPAD_HU | SL_SOFTKEY_10 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_VR_SK1                 (SL_KEYPAD_VR | SL_SOFTKEY_1 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_VR_SK2                 (SL_KEYPAD_VR | SL_SOFTKEY_2 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_VR_SK3                 (SL_KEYPAD_VR | SL_SOFTKEY_3 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_VR_SK4                 (SL_KEYPAD_VR | SL_SOFTKEY_4 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_VR_SK5                 (SL_KEYPAD_VR | SL_SOFTKEY_5 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_VR_SK6                 (SL_KEYPAD_VR | SL_SOFTKEY_6 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_VR_SK7                 (SL_KEYPAD_VR | SL_SOFTKEY_7 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_VR_SK8                 (SL_KEYPAD_VR | SL_SOFTKEY_8 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_VR_SK9                 (SL_KEYPAD_VR | SL_SOFTKEY_9 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_VR_SK10                (SL_KEYPAD_VR | SL_SOFTKEY_10 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_HL_SK1                 (SL_KEYPAD_HL | SL_SOFTKEY_1 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_HL_SK2                 (SL_KEYPAD_HL | SL_SOFTKEY_2 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_HL_SK3                 (SL_KEYPAD_HL | SL_SOFTKEY_3 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_HL_SK4                 (SL_KEYPAD_HL | SL_SOFTKEY_4 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_HL_SK5                 (SL_KEYPAD_HL | SL_SOFTKEY_5 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_HL_SK6                 (SL_KEYPAD_HL | SL_SOFTKEY_6 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_HL_SK7                 (SL_KEYPAD_HL | SL_SOFTKEY_7 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_HL_SK8                 (SL_KEYPAD_HL | SL_SOFTKEY_8 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_HL_SK9                 (SL_KEYPAD_HL | SL_SOFTKEY_9 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_HL_SK10                (SL_KEYPAD_HL | SL_SOFTKEY_10 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_VL_SK1                 (SL_KEYPAD_VL | SL_SOFTKEY_1 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_VL_SK2                 (SL_KEYPAD_VL | SL_SOFTKEY_2 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_VL_SK3                 (SL_KEYPAD_VL | SL_SOFTKEY_3 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_VL_SK4                 (SL_KEYPAD_VL | SL_SOFTKEY_4 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_VL_SK5                 (SL_KEYPAD_VL | SL_SOFTKEY_5 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_VL_SK6                 (SL_KEYPAD_VL | SL_SOFTKEY_6 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_VL_SK7                 (SL_KEYPAD_VL | SL_SOFTKEY_7 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_VL_SK8                 (SL_KEYPAD_VL | SL_SOFTKEY_8 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_VL_SK9                 (SL_KEYPAD_VL | SL_SOFTKEY_9 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_VL_SK10                (SL_KEYPAD_VL | SL_SOFTKEY_10 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_US_VR_SK1              (SL_KEYPAD_US_VR | SL_SOFTKEY_1 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_US_VR_SK2              (SL_KEYPAD_US_VR | SL_SOFTKEY_2 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_US_VR_SK3              (SL_KEYPAD_US_VR | SL_SOFTKEY_3 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_US_VL_SK1              (SL_KEYPAD_US_VL | SL_SOFTKEY_1 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_US_VL_SK2              (SL_KEYPAD_US_VL | SL_SOFTKEY_2 | SL_SOFTKEY_TYPE)
#define SL_KEYINFO_US_VL_SK3              (SL_KEYPAD_US_VL | SL_SOFTKEY_3 | SL_SOFTKEY_TYPE)

// special keys (help definitions)
#define   SL_SPECIAL_KEY_F9               0x00000010
#define   SL_SPECIAL_KEY_F10              0x00000020
#define   SL_SPECIAL_KEY_F11              0x00000030
#define   SL_SPECIAL_KEY_F12              0x00000040
#define   SL_SPECIAL_KEY_SHIFT_F9         0x00000050
#define   SL_SPECIAL_KEY_SHIFT_F10        0x00000060
#define   SL_SPECIAL_KEY_SHIFT_F11        0x00000070
#define   SL_SPECIAL_KEY_SHIFT_F12        0x00000080
#define   SL_SPECIAL_KEY_CTRL_F9          0x00000090
#define   SL_SPECIAL_KEY_CTRL_F10         0x000000A0
#define   SL_SPECIAL_KEY_CTRL_F11         0x000000B0
#define   SL_SPECIAL_KEY_CTRL_F12         0x000000C0
#define   SL_SPECIAL_KEY_ALT_F9           0x000000D0
#define   SL_SPECIAL_KEY_ALT_F10          0x000000E0
#define   SL_SPECIAL_KEY_ALT_F11          0x000000F0
#define   SL_SPECIAL_KEY_ALT_F12          0x00000100
#define   SL_SPECIAL_KEY_HOME             0x00000110
#define   SL_SPECIAL_KEY_ESCAPE           0x00000120
#define   SL_SPECIAL_KEY_END_NB           0x00000130
#define   SL_SPECIAL_KEY_PAGE_DOWN_NB     0x00000140
#define   SL_SPECIAL_KEY_HOME_NB          0x00000150
#define   SL_SPECIAL_KEY_PAGE_UP_NB       0x00000160
#define   SL_SPECIAL_KEY_END_CUR_DOWN_NB  0x00000170
#define   SL_SPECIAL_KEY_VIRT_KEY_1       0x00000180
#define   SL_SPECIAL_KEY_VIRT_KEY_2       0x00000190
#define   SL_SPECIAL_RES_VIRT_KEY_4       0x000001A0
#define   SL_SPECIAL_RES_VIRT_KEY_5       0x000001B0
#define   SL_SPECIAL_RES_VIRT_KEY_6       0x000001C0
#define   SL_SPECIAL_RES_VIRT_KEY_7       0x000001D0
#define   SL_SPECIAL_RES_VIRT_KEY_8       0x000001E0
#define   SL_SPECIAL_RES_VIRT_KEY_9       0x000001F0
#define   SL_SPECIAL_RES_VIRT_KEY_10      0x00000200
#define   SL_NC_RESET_KEY                 0x00000210 //YSNC specific, mapped to PLC
#define   SL_SCREENSHOT_KEY               0x00000220
#define   SL_TRACE_ACTIVATE_KEY           0x00000230
#define   SL_TRACE_DEACTIVATE_KEY         0x00000240
#define   SL_SWITCH_LANGUAGE_FORWARD_KEY  0x00000250
#define   SL_SWITCH_LANGUAGE_BACKWARD_KEY 0x00000260
#define   SL_SPECIAL_KEY_CTRL_1			      0x00000270
#define   SL_SPECIAL_KEY_CTRL_2			      0x00000280
#define   SL_SPECIAL_KEY_CTRL_3			      0x00000290
#define   SL_SPECIAL_KEY_CTRL_6			      0x000002A0
#define   SL_SPECIAL_KEY_CTRL_7			      0x000002B0
#define   SL_SPECIAL_KEY_CTRL_8			      0x000002C0
#define   SL_SPECIAL_KEY_CTRL_SHIFT_F9    0x000002D0
#define   SL_SPECIAL_KEY_CTRL_SHIFT_F10   0x000002E0
#define   SL_SPECIAL_KEY_CTRL_SHIFT_F11   0x000002F0
#define   SL_SPECIAL_KEY_CTRL_SHIFT_F12   0x00000300





//hook messages, may be derived from keys or any other stuff
#define   FUNC_KEY_PRESSED_IN_OEM_MODE    0x00000300
//essential buttons of the dialogmanager
#define   SL_RECALL_KEY                (SL_SPECIAL_KEY_F9 | SL_HARDKEY_TYPE)
#define   SL_ETC_KEY                   (SL_SPECIAL_KEY_SHIFT_F9 | SL_HARDKEY_TYPE)
#define   SL_WINDOW_CHANGE_KEY         (SL_SPECIAL_KEY_HOME | SL_HARDKEY_TYPE)

//essential buttons of the systemmanager
#define   SL_AEREA_MENU                (SL_SPECIAL_KEY_F10 | SL_HARDKEY_TYPE)
#define   SL_AREA_MENU                  SL_AEREA_MENU
#define   SL_CHANNEL_KEY               (SL_SPECIAL_KEY_F11 | SL_HARDKEY_TYPE)
#define   SL_INFO_KEY                  (SL_SPECIAL_KEY_F12 | SL_HARDKEY_TYPE)
#define   SL_MASCHINE_KEY              (SL_SPECIAL_KEY_SHIFT_F10 | SL_HARDKEY_TYPE)
#define   SL_KEY_ESCAPE                (SL_SPECIAL_KEY_ESCAPE | SL_HARDKEY_TYPE)

// gimme keys masks
#define SL_AEREA_MENU_GIMME		0x00000001	//f10
#define SL_AREA_MENU_GIMME    SL_AEREA_MENU_GIMME //f10
#define SL_CHANNEL_KEY_GIMME	0x00000002	//f11
#define SL_KEY_ESCAPE_GIMME		0x00000004	//esc
#define SL_MASCHINE_KEY_GIMME	0x00000008	//shift+f10
#define SL_END2TAB_KEY_GIMME	0x00000010	//tab instead of end ... @TODO - if needed, this should be added !
#define SL_SOFT_KEY_GIMME		0x00000020	//f1-f8,shift+f1-shift+f8,f9,shif+f9,f12,home
#define SL_SOFT_KEY_GIMME_EX	0x00000040	//f9, Shift-f9, f10, Shift-f10, f11, Shift-f11, f12, Shift-f12, home

#define SL_GIMME_SK_HU                   0x00000001  // horizontal upper softkeys (F1 - F8)
#define SL_GIMME_SK_VR                   0x00000002  // vertical right softkeys (Shift+F1 - Shift+F8)
#define SL_GIMME_SK_HL                   0x00000004  // horizontal lower softkeys (Ctrl+F1 - Ctrl+F8)
#define SL_GIMME_SK_VL                   0x00000008  // vertical right softkeys (Shift+Ctrl+F1 - Shift+Ctrl+F8)
#define SL_GIMME_RECALL                  0x00000010  // RECALL (F9)
#define SL_GIMME_ETC                     0x00000020  // ETC (Shift+F9)
#define SL_GIMME_MENU_SELECT             0x00000040  // MENU SELECT (F10)
#define SL_GIMME_MACHINE_OPT             0x00000080  // MACHINE (Shift+F10)
#define SL_GIMME_CHANNEL                 0x00000100  // 1..n CHANNEL (F11)
#define SL_GIMME_MACHINE_HARDKEY         0x00000200  // MACHINE (Shift+F11)
#define SL_GIMME_HELP                    0x00000400  // HELP (F12)
#define SL_GIMME_CUSTOM_HARDKEY          0x00000800  // CUSTOM (Shift+F12)
#define SL_GIMME_ALARM_CANCEL            0x00001000  // ALARM CANCEL (ESC)
#define SL_GIMME_NEXT_WINDOW             0x00002000  // NEXT WINDOW (HOME)
#define SL_GIMME_PROGRAM_HARDKEY         0x00004000  // PROGRAM (END)
#define SL_GIMME_ALARM_HARDKEY           0x00008000  // ALARM (PAGE UP)
#define SL_GIMME_TOOL_OFFSET_HARDKEY     0x00010000  // TOOL OFFSET (PAGE DOWN)
#define SL_GIMME_PROGRAM_MANAGER_HARDKEY 0x00020000  // PROGRAM MANAGER (HOME NUMPAD)
#define SL_GIMME_SK_EXT_HU               0x00040000  // extended horizontal upper softkeys (F13 - F20)
#define SL_GIMME_SK_EXT_VR               0x00080000  // extended vertical right softkeys (Shift+F13 - Shift+F20), HT8 left direct keys
#define SL_GIMME_SK_EXT_HL               0x00100000  // extended horizontal lower softkeys (Ctrl+F13 - Ctrl+F20)
#define SL_GIMME_SK_EXT_VL               0x00200000  // extended vertical left softkeys (Shift+Ctrl+F13 - Shift+Ctrl+F20), HT8 right direct keys
#define SL_GIMME_MENU_USER               0x00400000  // MENU USER (Ctrl+F10)
#define SL_GIMME_MENU_FUNCTION           0x00800000  // MENU USER (Ctrl+Shift+F10)



//hardkey buttons of the systemmanager
#define   SL_HARDKEY_1     (SL_SPECIAL_KEY_SHIFT_F11 | SL_HARDKEY_TYPE)         // [M]-Position
#define   SL_HARDKEY_2     (SL_SPECIAL_KEY_END_NB | SL_HARDKEY_TYPE)            // Programming Editor
#define   SL_HARDKEY_3     (SL_SPECIAL_KEY_PAGE_DOWN_NB | SL_HARDKEY_TYPE)      // Tool-Offset
#define   SL_HARDKEY_4     (SL_SPECIAL_KEY_HOME_NB | SL_HARDKEY_TYPE)           // Programm-Manager
#define   SL_HARDKEY_5     (SL_SPECIAL_KEY_PAGE_UP_NB | SL_HARDKEY_TYPE)        // Diagnostic (Alarm)
#define   SL_HARDKEY_6     (SL_SPECIAL_KEY_SHIFT_F12 | SL_HARDKEY_TYPE)         // Custom Hardkey
#define   SL_HARDKEY_6_EX  (SL_SPECIAL_KEY_CUR_DOWN_NB | SL_HARDKEY_TYPE)       // Shit! 802D-Panel steps out of line!!
#define   SL_HARDKEY_7     (SL_SPECIAL_KEY_VIRT_KEY_1 | SL_HARDKEY_TYPE)        // [M] Machine  mapping, real key. but mapped by rngkrnl
#define   SL_HARDKEY_8     (SL_SPECIAL_KEY_VIRT_KEY_2 | SL_HARDKEY_TYPE)        // Area-Menu-Select mapping, real key, but mapped by rngkrnl
#define   SL_HARDKEY_9     (SL_SPECIAL_KEY_CTRL_F9 | SL_HARDKEY_TYPE)           // Maintenance Hardkey, real key on specific YSNC-OP
#define   SL_HARDKEY_10    (SL_SPECIAL_KEY_CTRL_F10 | SL_HARDKEY_TYPE)          // MENU USER
#define   SL_HARDKEY_11    (SL_SPECIAL_KEY_CTRL_SHIFT_F10 | SL_HARDKEY_TYPE)    // MENU FUNCTION
#define   SL_HARDKEY_12    (SL_SPECIAL_RES_VIRT_KEY_6 | SL_HARDKEY_TYPE)        //Reseved for future
#define   SL_HARDKEY_13    (SL_SPECIAL_RES_VIRT_KEY_7 | SL_HARDKEY_TYPE)        //Reseved for future
#define   SL_HARDKEY_14    (SL_SPECIAL_RES_VIRT_KEY_8 | SL_HARDKEY_TYPE)        //Reseved for future
#define   SL_HARDKEY_15    (SL_SPECIAL_RES_VIRT_KEY_9 | SL_HARDKEY_TYPE)        //Reseved for future
#define   SL_HARDKEY_16    (SL_SPECIAL_RES_VIRT_KEY_10 | SL_HARDKEY_TYPE)       //Reseved for future





//-----------------------------------------------------------------------------
//                            ====================
//     2.                     KEY-STATE DEFINITIONS  (bitfield organized)
//                            ====================
//-----------------------------------------------------------------------------

#define  SL_KEY_PRESSED             0x00000001
#define  SL_KEY_RELEASED            0x00000002


//-----------------------------------------------------------------------------
//                            =========================
//     3.                     KEY-EXTENSION DEFINITIONS  t.b.d.
//                            =========================
//-----------------------------------------------------------------------------

// dynamically configurable accelerators/hotkeys
// e.g. hotkey:="Key_Control|Key_Shift|Key_U"
// consists of max. 2 modifier keys {Key_Control,Key_Shift,Key_Alt} and one of the keys {Key_A,...,Key_Z}

const int ACCEL_CTRL             = 0x00000001;
const int ACCEL_SHIFT            = 0x00000002;
const int ACCEL_ALT              = 0x00000004;
const int SL_KEY_FLAG_EXTENDED   = 0x00000008;
const int SL_KEY_FLAG_AUTOREPEAT = 0x00000010;

#endif   //_SLKEYS_H
