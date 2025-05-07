#ifndef SLSP_INF_H_
#define SLSP_INF_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif

// infos
#define SLSP_INF_PROCESSING_DIR             0x1  // processing directory
#define SLSP_INF_NCK_VERSION_TYPE_FAILED    0x2  // coudn't read NC version and/or type
#define SLSP_INF_BYTES_TRANSFERED           0x3  // number of transfered Bytes via file service
#define SLSP_INF_OS_REBOOT_REQUESTED        0x4  // reboot of operating system is requested
#define SLSP_INF_IS_DEINSTALLING_LANGUAGE   0x5  // deinstalling language (.m_strText) is in process
#define SLSP_INF_SLEEP                      0x6  // sleeping until all handlers have checked for dsf archive
#define SLSP_INF_COMPRESS_PROGRESS          0x10 // 7z progress information
#define SLSP_INF_COMPRESS_START             0x11 // 7z for compressing started
#define SLSP_INF_COMPRESS_FINISH            0x12 // 7z for compressing finished

// description warnings
#define  SLSP_DESCRWARN_NODB_CURARC       0x1   // DB doesn't exist in current archive
#define  SLSP_DESCRWARN_NODB_UPGARC       0x2   // DB doesn't exist in upgrade archive
#define  SLSP_DESCRWARN_NODB_BOTHARC      0x3   // DB doesn't exist in current and upgrade archive
#define  SLSP_DESCRWARN_NOBYTE_CURARC     0x4   // byte address of DB doesn't exist in current archive
#define  SLSP_DESCRWARN_NOBYTE_UPGARC     0x5   // byte address of DB doesn't exist in upgrade archive
#define  SLSP_DESCRWARN_NOBYTE_BOTHARC    0x6   // byte address of DB doesn't exist in current and upgrade archive

  // number for askNckVersionType
#define SLSP_INF_WRONG_NCK_VERSION          0x3  // wrong NC version
#define SLSP_INF_WRONG_NCK_TYPE             0x4  // wrong NC type
#define SLSP_INF_WRONG_NCK_VERSION_AND_TYPE 0x5  // wrong NC version and type

  // question id's for sendAsk
#define SLSP_ASK_PROCESS_CFG_RESET_INI      0x10  // ask for downloading CFG_RESET.INI

#endif
