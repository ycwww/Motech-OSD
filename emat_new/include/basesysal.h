#pragma once

#ifndef _BASESYSAL_H
#define _BASESYSAL_H	//!< prevent multiple including

/*! \file basesysal.h
 \brief  Interface export all functions of the library (.dll or .so).
 \author Siegfried Vogel at siemens.com
 \date   25.11.2013

 Define all necessary defines and data types, which are needed for the
 Interface of the base system abstraction layer libbrary.
 */
/*! \mainpage BaseSysAL (base system abstraction layer) library.
 \tableofcontents

 The BaseSysAL library (libbasesysal.so / basesysal.dll) is an abstraction layer
 between base system and applications like HMI.

 \section sec1 Introduction
 It is our long-term goal to concentrate all functions concerned with base
 system and has also a relation to higher application like HMI. This group of
 functions embraces HW specific issues an also some abstraction of the
 operating system or the directory structure.
 If you have the need of new functionality or you need any extension of
 existing library functions, do not realize it yourself, but ask for extensions
 at base team.

 \section sec2 References
 List of modules:
 <ul>
 <li> \ref groupGeneral
 <li> \ref groupErrno
 <li> \ref groupSlhw
 <li> \ref groupSlNetwork
 <li> \ref groupSvic
 <li> \ref groupMuli
 </ul>
 */
/*! \defgroup groupGeneral General declarations
 \brief  General declarations of the Sinumerik Library.

 All declarations of the BaseSysAL Library, which could not be assigned to
 specific module.
 */
/*! \defgroup groupSlNetwork Information about network adapters
 \brief  Functions for handle with network adapters.

 Different devices from SINUMERIK have different number of network adapters.
 Each adapter is managed by the operating system by a name like "eth0"
 (LINUX) or "{06CE7F14-038D-497A-B8ED-08160946E9CD}" (windows). Because this
 name is cryptic under windows (GUID), there is also a friendly name like
 "Ethernet 1 (System Network)". Each adapter has a name or identifier of its
 connector like "X120" or "Eth1". Also each adapter has a purpose like system
 network or company network.

 Function | Description
 ----: | :----
 \ref basesysal_getAdapterNum() | Get number of a network adapters.
 \ref basesysal_getAdapterFriendlyName() | Get friendly name of an adapter.
 \ref basesysal_getAdapterName() | Get name of an adapter.
 \ref basesysal_getAdapterConnectorName() | Get connector name of an adapter.
 \ref basesysal_getAdapterPurpose() | Get purpose of an adapter.
 \ref basesysal_findAdapterByPurpose() | Find an network adapter by purpose.
 \ref basesysal_refreshAdapterSettings() | Refresh adapter setting
 \ref basesysal_getAdapterIp() | Get IP of Adapter
 \ref basesysal_getAdapterAliasIp() | Get IP of adapter alias
 \ref basesysal_getAdapterServerIp() | Get adapter server IP
 \ref basesysal_getAdapterState() | Get state of adapter

 Include slhw_network.h

 Example:
 \code{.c}
 ..
 #include "basesysal.h"
 ..
 int main(void)
 {
   SLHW_ERROR err;
   const char *friendly_name = NULL;
   uint32_t numAdapter = 0;
   uint32_t i = 0;
   
   numAdapter = basesysal_getAdapterNum();//get number network adapters
   ..
   for (i = 0; i < numAdapter; i++) {//iterate all adapters     ..
     friendly_name = basesysal_getAdapterFriendlyName(i);//get friendly name of adapter
     if (NULL != friendly_name)
         printf("Friendly name of adapter %d: %s\n", i, friendly_name);
   }
 }
 
 \endcode
 */

/*! \addtogroup groupGeneral
 @{
*/

#if defined(WIN32) && _MSC_VER < 1600
	typedef signed char int8_t;
	typedef short int16_t;
	typedef int int32_t;
	typedef __int64 int64_t;

	typedef unsigned char uint8_t;
	typedef unsigned short uint16_t;
	typedef unsigned int uint32_t;
	typedef unsigned __int64 uint64_t;
#else //WIN32
	#include <stdint.h>
#endif //WIN32

#include <string.h>

/*! \def BASESYSAL_SPEC
 \brief spec as DLL ex/import

 Windows only: A DLL, which exports entity, have to use
 "__declspec(dllexport)" to export a entity (function, variable, class, ...)
*/
/*! \def BASESYSAL_API
 \brief DLL ex/imports must be C declarations

 Windows only: All exported functions must be C declarations
*/

#ifdef WIN32
	#ifdef BASESYSAL_EXPORTS
		#define BASESYSAL_SPEC __declspec(dllexport)
	#else
		#define BASESYSAL_SPEC __declspec(dllimport)
	#endif
	#define BASESYSAL_CDECL __cdecl
	#define BASESYSAL_API __cdecl
#else /*WIN32*/
	#define BASESYSAL_SPEC
	#define BASESYSAL_CDECL
	#define BASESYSAL_API
#endif /*WIN32*/

#ifdef WIN32
#define BASESYSAL_DLL_NAME "basesysal.dll"
#else
#define BASESYSAL_DLL_NAME "libbasesysal.so.1"
#endif

//! @}

/*! \addtogroup groupErrno
 @{
*/

/*!
 Error codes of the library functions.
 */

typedef enum {
	BASESYSAL_ERR_OK = 0,                    //!< No error.
	BASESYSAL_ERR_INVALID_PARAMETER = -1,    //!< At least one parameter is invalid.
	BASESYSAL_ERR_METRIC_NOT_AVAILABLE = -2, //!< Selected metric is not available
	BASESYSAL_ERR_DLL_NOT_FOUND = -3,        //!< one needed dynamics library not found
	BASESYSAL_ERR_PROC_NOT_FOUND = -4,       //!< one needed procedure not found
	BASESYSAL_ERR_UNKNOWN_ERROR = -5,        //!< a unknown error from a sub library
	BASESYSAL_ERR_HWID_UNKNOWN = -6,         //!< HWID is unknown
	BASESYSAL_ERR_FUNCTION_NOT_ACCESSIBLE = -7,  //!< Function is not accessible
	BASESYSAL_ERR_NOT_FOUND               = -8,  //!< the wanted entity was not found
} BASESYSAL_ERROR;

//! @}

/*! \addtogroup groupSvic
 @{
*/

/*!
 Enumeration of possible metrics.
 */
typedef enum {
//	BASESYSAL_VERSION = 0,              //!< Version of libbase

	BASESYSAL_SYS_NET_NAME = 0x010000,  //!< friendly name of interface of system network
	BASESYSAL_COM_NET_NAME,             //!< friendly name of interface of company network
	BASESYSAL_IBN_NET_NAME,             //!< friendly name of interface of IBN network (linux only)
	BASESYSAL_SYS_NET_ALIAS,            //!< alias name of interface of system network
	BASESYSAL_COM_NET_ALIAS,            //!< alias name of interface of company network
	BASESYSAL_IBN_NET_ALIAS,            //!< alias name of interface of IBN network (linux only)

	BASESYSAL_CFG_SIEMENS = 0x020000,   //!< directory of config files (siemens)
	BASESYSAL_CFG_ADDON,                //!< directory of config files (addon)
	BASESYSAL_CFG_OEM,                  //!< directory of config files (oem)
	BASESYSAL_CFG_USER,                 //!< directory of config files (user)
	BASESYSAL_BASESYS_INI_SIEMENS,      //!< path of base system config (siemens)
	BASESYSAL_BASESYS_INI_ADDON,        //!< path of base system config (addon)
	BASESYSAL_BASESYS_INI_OEM,          //!< path of base system config (oem)
	BASESYSAL_BASESYS_INI_USER,         //!< path of base system config (user)
	BASESYSAL_TCU_INI_SIEMENS,          //!< path of tcu support config (siemens)
	BASESYSAL_TCU_INI_ADDON,            //!< path of tcu support config (addon)
	BASESYSAL_TCU_INI_OEM,              //!< path of tcu support config (oem)
	BASESYSAL_TCU_INI_USER,             //!< path of tcu support config (user)

	BASESYSAL_NETBOOT_DIR = 0x030000,   //!< path of siemens netboot directory
	BASESYSAL_TCU_DIR,                  //!< path of TCU directory
} BASESYSAL_METRIC;

//! @}

/*! \addtogroup groupSlhw
 @{
*/

/*!
 Enumeration of possible hardware components.
 */
typedef enum {
	BASESYSAL_COMP_NONE = -1,//!< no component
	BASESYSAL_COMP_MAIN = 0, //!< main hardware; A hardware may consist of more than one component (TCU plus panel)
//	BASESYSAL_COMP_PANEL,    //!< panel specific; A panel is conclusion of display and keyboard.
//	BASESYSAL_COMP_KEYBOARD, //!< keyboard specific; There separate keyboards like QWERTY-keyboard.
//	BASESYSAL_COMP_FPGA,     //!< FPGA specific
//	BASESYSAL_COMP_MEM_CARD, //!< Memory-CARD specific
} BASESYSAL_COMPONENT_T;

/*!
 Enumeration of possible elements of a hardware component.
 */
typedef enum {
//	BASESYSAL_HWINFO_NONE               =  -1, //!< value for undefined element
//	BASESYSAL_HWINFO_MAGIC              =   0, //!< magic pattern (array of uint8_t with length 8)
//	BASESYSAL_HWINFO_VER                =   1, //!< version of hw info block structure (array of uint8_t with length 4)
//	BASESYSAL_HWINFO_LEN                =   2, //!< length of hw info block (uint16_t)
//	BASESYSAL_HWINFO_BGRNAME            =   3, //!< name of board (nul terminated string; upto 128 characters)
//	BASESYSAL_HWINFO_MLFB               =   4, //!< order number (nul terminated string; upto 20 characters)
//	BASESYSAL_HWINFO_SERIAL_NUM         =   5, //!< serial number (nul terminated string; upto 26 characters)
//	BASESYSAL_HWINFO_HW_REV             =   6, //!< hardware revision (array of char with length 2)
//	BASESYSAL_HWINFO_MAC1               =   7, //!< mac address 1 (array of uint8_t with length 6)
//	BASESYSAL_HWINFO_MAC2               =   8, //!< mac address 2 (array of uint8_t with length 6)
//	BASESYSAL_HWINFO_MAC3               =   9, //!< mac address 3 (array of uint8_t with length 6)
//	BASESYSAL_HWINFO_MAC4               =  10, //!< mac address 4 (array of uint8_t with length 6)
//	BASESYSAL_HWINFO_MAC_AUX1           =  11, //!< behind mac address 1 follow another mac (uint8_t)
//	BASESYSAL_HWINFO_MAC_AUX2           =  12, //!< behind mac address 2 follow another mac (uint8_t)
//	BASESYSAL_HWINFO_MAC_AUX3           =  13, //!< behind mac address 3 follow another mac (uint8_t)
//	BASESYSAL_HWINFO_MAC_AUX4           =  14, //!< behind mac address 4 follow another mac (uint8_t)
//	BASESYSAL_HWINFO_PHYS_DEV1          =  15, //!< mapping of mac 1 to external interface (array of uint8_t with length 4)
//	BASESYSAL_HWINFO_PHYS_DEV2          =  16, //!< mapping of mac 2 to external interface (array of uint8_t with length 4)
//	BASESYSAL_HWINFO_PHYS_DEV3          =  17, //!< mapping of mac 3 to external interface (array of uint8_t with length 4)
//	BASESYSAL_HWINFO_PHYS_DEV4          =  18, //!< mapping of mac 4 to external interface (array of uint8_t with length 4)
//	BASESYSAL_HWINFO_HWID               =  19, //!< hardware ID (array of uint8_t with length 4)
//	BASESYSAL_HWINFO_FLASH_SIZE         =  20, //!< size of FLASH in KB (uint32_t)
//	BASESYSAL_HWINFO_SDRAM_SIZE         =  21, //!< size of SD-RAM in KB (uint32_t)
//	BASESYSAL_HWINFO_SDRAM_IDC_SIZE     =  22, //!< size of SD-RAM in KB (IDC32) (uint16_t)
//	BASESYSAL_HWINFO_FEATURE_FLAGS      =  23, //!< feature flags (needed by localhws)
////	BASESYSAL_HWINFO_FF_USE_PBIF_IDC    =  24, //!< 
//	BASESYSAL_HWINFO_FF_DCK_AVAIL       =  25, //!< direct keys available
//	BASESYSAL_HWINFO_FF_NUM_HANDWHEELS  =  26, //!< number of handwheels
	BASESYSAL_HWINFO_FF_EVO_SYSTEM      =  27, //!< is an EvoLine system
////	BASESYSAL_HWINFO_FF_FPUIPE_ENABLED  =  28, //!< 
////	BASESYSAL_HWINFO_FF_UART2_FIFO      =  29, //!< 
////	BASESYSAL_HWINFO_FF_UART2_PCFREQ    =  30, //!< 
////	BASESYSAL_HWINFO_FF_NVRAM_NO_ENERGY =  31, //!< 
////	BASESYSAL_HWINFO_FF_MOBILE_PN       =  32, //!< 
////	BASESYSAL_HWINFO_FF_FAN_REQUIRED    =  33, //!< 
////	BASESYSAL_HWINFO_FF_ANA_OUT_AVAIL   =  34, //!< 
	BASESYSAL_HWINFO_PERFORMANCE_CLASS  =  35, //!< performance class (uint8_t)
//	BASESYSAL_HWINFO_PERFORMANCE_BRAKE  =  36, //!< performance brake (uint8_t)
	BASESYSAL_HWINFO_HW_CATEGORY        =  37, //!< hardware category (nul terminated string)
	BASESYSAL_HWINFO_HW_FAMILY          =  38, //!< hardware family (uint32_t)
//	BASESYSAL_HWINFO_NVRAM_SIZE         =  39, //!< size of NV-RAM
//	BASESYSAL_HWINFO_NVRAM_TIME_DSAVE   =  40, //!< DSAVE time of NV-RAM
//	BASESYSAL_HWINFO_NVRAM_RSC_BACKUP   =  41, //!< available size of NV-RAM to RSC
//	BASESYSAL_HWINFO_TIMER_FREQ         =  42, //!< timer frequency
//	BASESYSAL_HWINFO_MODE_ATA_DMA       =  43, //!< valid modi of ATA and DMA interfaces
//	BASESYSAL_HWINFO_PORT_INT_USB_FLASH =  44, //!< port of interal USB storage
//	BASESYSAL_HWINFO_VER_SRM            =  45, //!< SRM version
//	BASESYSAL_HWINFO_FPGA_ADDR          =  46, //!< FPGA address
//	BASESYSAL_HWINFO_BL_BRIGHTNESS      =  47, //!< backlight brightness
//	BASESYSAL_HWINFO_BL_LIMIT_MAX       =  48, //!< backlight brightness (max.)
//	BASESYSAL_HWINFO_BL_LIMIT_MIN       =  49, //!< backlight brightness (min.)
//	BASESYSAL_HWINFO_FW_FLAGS           =  50, //!< firmware flags
//	BASESYSAL_HWINFO_HORI_RES           =  51, //!< horizontal resolution in pixel (uint32_t)
//	BASESYSAL_HWINFO_VERT_RES           =  52, //!< vertical resolution in pixel (uint32_t)
//	BASESYSAL_HWINFO_DISPL_DIAG         =  53, //!< display size (diagonal) in inch multiplied by 10 (uint32_t)
//	BASESYSAL_HWINFO_TOUCH_VER          =  54, //!< version of touch controller (uint32_t)
//	BASESYSAL_HWINFO_KEYB_ALPHA         =  55, //!< value !=0 ==> there are alpha numeric keys (uint32_t)
//	BASESYSAL_HWINFO_KEYB_HOTKEY        =  56, //!< value !=0 ==> there are hotkeys (uint32_t)
//	BASESYSAL_HWINFO_KEYB_CURSOR        =  57, //!< value !=0 ==> there are cursor keys (uint32_t)
//	BASESYSAL_HWINFO_KEYB_DIGIT         =  58, //!< value !=0 ==> there are digit keys (uint32_t)
//	BASESYSAL_HWINFO_SK_HORI_UPPER      =  59, //!< value !=0 ==> there are upper horizontal softkeys (uint32_t)
//	BASESYSAL_HWINFO_SK_HORI_LOWER      =  60, //!< value !=0 ==> there are lower horizontal softkeys (uint32_t)
//	BASESYSAL_HWINFO_SK_VERT_LEFT       =  61, //!< value !=0 ==> there are left vertical softkeys (uint32_t)
//	BASESYSAL_HWINFO_SK_VERT_RIGHT      =  62, //!< value !=0 ==> there are right vertical softkeys (uint32_t)
//	BASESYSAL_HWINFO_SK_VERT_LEFT_EXT   =  63, //!< value !=0 ==> there are ext. left vertical softkeys (uint32_t)
//	BASESYSAL_HWINFO_SK_VERT_RIGHT_EXT  =  64, //!< value !=0 ==> there are ext. right vertical softkeys (uint32_t)
//	BASESYSAL_HWINFO_OEM_LAYOUT         =  65, //!< OEM layout to display ("NORMAL", "DMG", ..) (nul terminated string; upto 8 characters)
//	BASESYSAL_HWINFO_REFR_RATE          =  66, //!< refrsh rate
//	BASESYSAL_HWINFO_DISPL_CON          =  67, //!< display connection
//	BASESYSAL_HWINFO_HW_INT             =  68, //!< hardware interface
//	BASESYSAL_HWINFO_TCU_INT            =  69, //!< TCU integration
	BASESYSAL_HWINFO_HW_TYPE            =  70, //!< hardware type (nul terminated string)

//	BASESYSAL_HWINFO_FPGA_VERSION       = 100, //!< FPGA version

//	BASESYSAL_HWINFO_MEM_CARD_MODEL     = 201, //!< model of Memory-Card
//	BASESYSAL_HWINFO_MEM_CARD_SERIAL    = 202, //!< serial number of Memory-Card
//	BASESYSAL_HWINFO_MEM_CARD_CAPACITY  = 203, //!< capacity of Memory-Card
//	BASESYSAL_HWINFO_MEM_CARD_FREE_KB   = 204, //!< free capacity of Memory-Card in KB
//	BASESYSAL_HWINFO_MEM_CARD_TYPE      = 205, //!< type of Memory-Card (0=unknown; 1=CF; 2=SD; ...)

//	BASESYSAL_TCO_POWERUP_NUM           = 300, //!< count of power ups
//	BASESYSAL_TCO_POWERUP_HOUR          = 301, //!< hours of operation
//	BASESYSAL_TCO_MAX_TEMP_EXCEEDED     = 302, //!< max. temp. exceede
//	BASESYSAL_TCO_MEM_CARD_WRITE_COUNT  = 303, //!< count of write counts to Memory-Card
} BASESYSAL_ELEMENT_T;

#ifdef __cplusplus	/* Declarations also in C++-Files */
	extern "C" {
#endif /* __cplusplus */

/*!
 \brief Set the error code of the last call to a function of the SINUMERIK library.
 \param [in] err Error code to set. Use one of the values from #SLHW_ERROR.
 \return -

 Set the error code of the last call to a function of the SINUMERIK library.
 Normally there is no need for explicit setting of the error code, because 
 every library function will reset the error code to SLHW_ERR_OK.
 \since 1.0
 */
BASESYSAL_SPEC void BASESYSAL_API basesysal_setLastError(BASESYSAL_ERROR err);

/*!
 \brief Get the error code of the last call to a function of the SINUMERIK library.
 \return Error code of last call to a function of the SINUMERIK library.

 Get the error code of the last call to a function of the SINUMERIK library.
 See slhw_errno.h for possible values.
 \since 1.0
 */
BASESYSAL_SPEC BASESYSAL_ERROR BASESYSAL_API basesysal_getLastError(void);

/*!
 \brief  Get one metric from base system.
 \param  [in] met Metric Id.
 \return If function fails, NULL pointer is returned. Otherwise a pointer to
 nul terminated string is returned.

 Get one metric from base system like the TCU directory.
 \since 1.0
 */
BASESYSAL_SPEC const char * BASESYSAL_API basesysal_getMetric(BASESYSAL_METRIC met);

/*!
 \brief  Convert HWID to hardware category.
 \param  [in] hwid Hardware Id.
 \return If function fails, NULL pointer is returned. Otherwise a pointer to
 nul terminated string is returned.

 Convert a hwid to a HW category like 'NCU' or 'TCU'.
 \since 1.0
 */
BASESYSAL_SPEC const char * BASESYSAL_API basesysal_convertToHwCategory(const unsigned char *hwid);

/*!
 \brief  Convert HWID to hardware type.
 \param  [in] hwid Hardware Id.
 \return If function fails, NULL pointer is returned. Otherwise a pointer to
 nul terminated string is returned.

 Convert a hwid to a HW type like 'NCU 730.1' or 'OP08T'.
 \since 1.0
 */
BASESYSAL_SPEC const char * BASESYSAL_API basesysal_convertToHwType(const unsigned char *hwid);

#ifdef WIN32
/*!
 \brief  Get infos about local panel.
 \param  [OUT] uiXResMax Pointer to max. resolution in x direction.
 \param  [OUT] uiYResMax Pointer to max. resolution in x direction.
 \param  [OUT] uiXRes Pointer to resolution in x direction.
 \param  [OUT] uiYRes Pointer to resolution in x direction.
 \param  [OUT] exists Pointer to exists flag (0 => not exists; 1 = exists).
 \return If function fails, 0 is returned. Otherwise 1 is returned.

 Get infos about local panel.
 \since 1.0
 */
BASESYSAL_SPEC int BASESYSAL_API basesysal_Panel_GetInfo(uint32_t *uiXResMax, uint32_t *uiYResMax, uint32_t *uiXRes, uint32_t *uiYRes, int *exists);

/*!
 \brief  Get infos about local monitor.
 \param  [OUT] uiXResMax Pointer to max. resolution in x direction.
 \param  [OUT] uiYResMax Pointer to max. resolution in x direction.
 \param  [OUT] uiXRes Pointer to resolution in x direction.
 \param  [OUT] uiYRes Pointer to resolution in x direction.
 \param  [OUT] exists Pointer to exists flag (0 => not exists; 1 = exists).
 \return If function fails, 0 is returned. Otherwise 1 is returned.

 Get infos about local monitor.
 \since 1.0
 */
BASESYSAL_SPEC int BASESYSAL_API basesysal_Monitor_GetInfo(uint32_t *uiXResMax, uint32_t *uiYResMax, uint32_t *uiXRes, uint32_t *uiYRes, int *exists);
#endif

/*!
 \brief Get one info about HW.
 \param [in] comp Selects one HW component
 \param [in] elem Selects one element of the HW component
 \param [out] buf Pointer to output buffer
 \param [in,out] len Pointer to size of buffer. Call it with the size of your buffer. The needed size is always set by this function.
 \retval BASESYSAL_ERR_METRIC_NOT_AVAILABLE If HW info block is not present or invalid.
 \retval BASESYSAL_ERR_INVALID_PARAMETER If one of the parameters is invalid.
 \retval BASESYSAL_ERR_INSUFFICIENT_BUFFER If the value of len is insufficient to take full info.
 \return Otherwise BASESYSAL_ERR_OK is returned.

 Get one information about a element of a hardware component selected by parameter comp.
 \since 1.0
 */
BASESYSAL_SPEC BASESYSAL_ERROR BASESYSAL_API basesysal_getHwinfo(const BASESYSAL_COMPONENT_T comp, const BASESYSAL_ELEMENT_T elem, void *buf, size_t *len);

//! @name Function pointer for use with GetProcAddress()/dlsym().
//! @{

typedef void (BASESYSAL_API * PFN_basesysal_setLastError)(BASESYSAL_ERROR err);
typedef BASESYSAL_ERROR (BASESYSAL_API * PFN_basesysal_getLastError)(void);
typedef const char * (BASESYSAL_API * PFN_basesysal_getMetric)(BASESYSAL_METRIC met);
typedef const char * (BASESYSAL_API * PFN_basesysal_convertToHwCategory)(const unsigned char *hwid);
typedef const char * (BASESYSAL_API * PFN_basesysal_convertToHwType)(const unsigned char *hwid);
typedef BASESYSAL_ERROR (BASESYSAL_API * PFN_basesysal_getHwinfo)(const BASESYSAL_COMPONENT_T comp, const BASESYSAL_ELEMENT_T elem, void *buf, size_t *len);
#ifdef WIN32
typedef int (BASESYSAL_API * PFN_basesysal_Panel_GetInfo)(uint32_t *uiXResMax, uint32_t *uiYResMax, uint32_t *uiXRes, uint32_t *uiYRes, int *bExists);
typedef int (BASESYSAL_API * PFN_basesysal_Monitor_GetInfo)(uint32_t *uiXResMax, uint32_t *uiYResMax, uint32_t *uiXRes, uint32_t *uiYRes, int *bExists);
#endif
//! @}

//! @name Defines for use with GetProcAddress()/dlsym() to identify the function.
//! @{

#define FN__BASESYSAL_SETLASTERROR        "basesysal_setLastError"
#define FN__BASESYSAL_GETLASTERROR        "basesysal_getLastError"
#define FN__BASESYSAL_GETMETRIC           "basesysal_getMetric"
#define FN__BASESYSAL_CONVERTTOHWCATEGORY "basesysal_convertToHwCategory"
#define FN__BASESYSAL_CONVERTTOHWTYPE     "basesysal_convertToHwType"
#define FN__BASESYSAL_PANEL_GETINFO       "basesysal_Panel_GetInfo"
#define FN__BASESYSAL_MONITOR_GETINFO     "basesysal_Monitor_GetInfo"
#define FN__BASESYSAL_GETHWINFO           "basesysal_getHwinfo"
//! @}

/*! \addtogroup groupSlNetwork
 @{
*/

/*!
 Possible purpose of an network adapter.
 */
typedef enum {
	BASESYSAL_IFC_UNKNOWN = 0,					//!< Unknown or unspecific purpose
	BASESYSAL_IFC_SYSTEM,						//!< system network
	BASESYSAL_IFC_COMPANY,						//!< company netowrk
	BASESYSAL_IFC_IBN,							//!< IBN network
	BASESYSAL_IFC_DRIVE,							//!< drive network
	BASESYSAL_IFC_PN,							//!< ProfiNet (CBE30, e.g.)
	BASESYSAL_IFC_PLC,							//!< network related to PLC
} BASESYSAL_IFC_PURPOSE;

/*! value for a invalid index into the array of all network adapters */
#define BASESYSAL_INVALID_NETWORK_INDEX 0xFFFFFFFF

/*!
 \brief Get the number of network adapters.
 \return Number of network adapters. May be 0!

 Get the number of network adapters of local device.
 \since 1.0
 */
BASESYSAL_SPEC uint32_t BASESYSAL_API basesysal_getAdapterNum(void);

/*!
 \brief Get the friendly name of a network adapter.
 \param index Index of network adapter
 \return If the index is invalid NULL is returned. Call basesysal_getLastError() to get error code.
 \return Otherwise a pointer to a nul terminated character array is returned which contains the friendly name of the adapter.

 Get the friendly name of a network adapter.
 LINUX: "eth0", "eth1", ...
 Windows: "Local area connection", ...
 \since 1.0
 */
BASESYSAL_SPEC const char * BASESYSAL_API basesysal_getAdapterFriendlyName(const uint32_t index);

/*!
 \brief Get the name of a network adapter.
 \param index Index of network adapter
 \return If the index is invalid NULL is returned. Call basesysal_getLastError() to get error code.
 \return Otherwise a pointer to a nul terminated character array is returned which contains the name of the adapter.

 Get the name of a network adapter.
 LINUX: "eth0", "eth1", ...
 Windows: "{06CE7F14-038D-497A-B8ED-08160946E9CD}", ...
 \since 1.0
 */
BASESYSAL_SPEC const char * BASESYSAL_API basesysal_getAdapterName(const  uint32_t index);

/*!
 \brief Get the connector name of a network adapter.
 \param index Index of network adapter
 \return If the index is invalid NULL is returned. Call basesysal_getLastError() to get error code.
 \return Otherwise a pointer to a nul terminated character array is returned which contains the label of the connector of the adapter.

 Get the connector name of a network adapter.
 LINUX: "X120", "X130", ...
 Windows: "Eth1", "Eth2", "X60", ...
 \since 1.0
 */
BASESYSAL_SPEC const char * BASESYSAL_API basesysal_getAdapterConnectorName(const uint32_t index);

/*!
 \brief Get the purpose of a network adapter.
 \param [in] index Index of Adapter
 \return If the index is invalid BASESYSAL_IFC_UNKNOWN is returned. Call basesysal_getLastError() to get error code.
 \return Otherwise the purpose of the adapter is returned. See \ref BASESYSAL_IFC_PURPOSE for a list of all possible values.

 Get the purpose of a network adapter.
 \since 1.0
 */
BASESYSAL_SPEC BASESYSAL_IFC_PURPOSE BASESYSAL_API basesysal_getAdapterPurpose(const uint32_t index);

/*!
 \brief Get the MAC address of a network adapter.
 \param [in] index Index of Adapter
 \return If the index is invalid NULL is returned. Call basesysal_getLastError() to get error code.
 \return Otherwise the MAC address of the adapter is returned.

 Get the purpose of a network adapter.
 \since 1.0
 */
BASESYSAL_SPEC const uint8_t * BASESYSAL_API basesysal_getAdapterMac(const uint32_t index);

/*!
 \brief Get the MAC address of a network adapter.
 \param [in] index Index of Adapter
 \param [out] enabled Either the adapter is enabled (TRUE) or disabled (FALSE).
 \return If the index is invalid BASESYSAL_ERR_INVALID_PARAMETER is returned.
 \return Otherwise BASESYSAL_ERR_OK is returned.

 Get the purpose of a network adapter.
 \since 1.0
 */
BASESYSAL_SPEC BASESYSAL_ERROR BASESYSAL_API basesysal_isAdapterEnabled(const uint32_t index, int *enabled);

/*!
 \brief Find a network adapter by purpose.
 \param purpose [in] Purpose of the adapter.
 \return If the purpose is invalid or no adapter with the specified purpose was found BASESYSAL_INVALID_NETWORK_INDEX is returned. Call basesysal_getLastError() to get error code.
 \return Otherwise the index of the adapter with the defined purpose is returned.

 Find a network adapter by purpose. See \ref BASESYSAL_IFC_PURPOSE for a list of all possible values.
 \since 1.0
 */
BASESYSAL_SPEC uint32_t BASESYSAL_API basesysal_findAdapterByPurpose(BASESYSAL_IFC_PURPOSE purpose);

/*!
 \brief Refresh the cached settings of a network adapter.
 \param [in] index Index of Adapter
 \return If the index is invalid SLHW_ERR_INVALID_PARAMETER is returned.
 \return Otherwise SLHW_ERR_OK is returned.

 Refresh the cached settings of a network adapter.
 \attention The IP is cached. If you need really actual state call
            slhw_RefreshAdapterSettings() in front.
 \since 1.1
 */
BASESYSAL_SPEC BASESYSAL_ERROR BASESYSAL_API basesysal_refreshAdapterSettings(const uint32_t index);

/*!
 \brief Refresh the settings of a network adapter.
 \param [in] index Index of Adapter
 \param [out] ip Pointer to an IPv4 address
 \param [out] subnetMask Pointer to an IPv4 subnet mask
 \return If the index is invalid SLHW_ERR_INVALID_PARAMETER is returned.
 \return Otherwise SLHW_ERR_OK is returned.

 Refresh the settings of a network adapter. The settings are cached.
 \since 1.1
 */
BASESYSAL_SPEC BASESYSAL_ERROR BASESYSAL_API basesysal_getAdapterIp(const uint32_t index, uint32_t *ip, uint32_t *subnetMask);

/*!
 \brief Get the Alias-IP address of a network adapter.
 \param [in] index Index of Adapter
 \param [out] ip Pointer to an IPv4 address
 \param [out] subnetMask Pointer to an IPv4 subnet mask
 \return If the index is invalid SLHW_ERR_INVALID_PARAMETER is returned.
 \return Otherwise SLHW_ERR_OK is returned.

 Get the Alias-IP address of a network adapter.
 \attention The alias IP is cached. If you need really actual state call
            slhw_RefreshAdapterSettings() in front.
 \since 1.1
 */
BASESYSAL_SPEC BASESYSAL_ERROR BASESYSAL_API basesysal_getAdapterAliasIp(const uint32_t index, uint32_t *ip, uint32_t *subnetMask);

/*!
 \brief Get the IP address DHCP/DNS server of a network adapter.
 \param [in] index Index of Adapter
 \param [out] ip Pointer to an IPv4 address
 \param [out] subnetMask Pointer to an IPv4 subnet mask
 \return If the index is invalid SLHW_ERR_INVALID_PARAMETER is returned.
 \return Otherwise SLHW_ERR_OK is returned.

 Get the IP address DHCP/DNS server of a network adapter.
 \attention The alias IP is cached. If you need really actual state call
            slhw_RefreshAdapterSettings() in front.
 \since 1.1
 */
BASESYSAL_SPEC BASESYSAL_ERROR BASESYSAL_API basesysal_getAdapterServerIp(const uint32_t index, uint32_t *ipServer);

/*!
 \brief Get the state of a network adapter.
 \param [in] index Index of Adapter
 \param [out] state
 \return If the index is invalid SLHW_ERR_INVALID_PARAMETER is returned.
 \return Otherwise SLHW_ERR_OK is returned.

 Get the status of a network adapter.
 \since 1.1
 */
BASESYSAL_SPEC BASESYSAL_ERROR BASESYSAL_API basesysal_getAdapterState(const uint32_t index, uint32_t *state);

/*!
 Serval bits of the flags for DNS query.
 */
#define BASESYSAL_NET_FLAGS_COM     0x00000001	/*!<if the query gets no response
    for the DNS query on system network, perfrom a query on company network*/

/*!
 \brief Perform a DNS query on system network.
 \param [in] name DNS name of host of interest
 \param [in] flags Flags for the call
 \param [out] ip IP address of host
 \retval BASESYSAL_ERR_INVALID_PARAMETER: If name or ip is a NULL pointer
 \retval BASESYSAL_ERR_NOT_FOUND: If host is not known at DNS server
 \retval BASESYSAL_ERR_FUNCTION_NOT_ACCESSIBLE: If there is no adatapter for system network
 \retval BASESYSAL_ERR_OK: If DNS qzery is successful.

 Perform a DNS query on system network. This ist especially on Windows system
 with multiple network adapters of interest, because the network adapters may
 have different priority for DNS requests.
 \since 1.x
 */
BASESYSAL_SPEC BASESYSAL_ERROR BASESYSAL_API basesysal_sysNetDnsQuery(const char *name, const uint32_t flags, uint32_t *ip);

//! @name Function pointer for use with GetProcAddress()/dlsym().
//! @{

typedef uint32_t (BASESYSAL_API * PFN_basesysal_getAdapterNum)(void);
typedef const char * (BASESYSAL_API * PFN_basesysal_getAdapterFriendlyName)(const uint32_t index);
typedef const char * (BASESYSAL_API * PFN_basesysal_getAdapterName)(const  uint32_t index);
typedef const char * (BASESYSAL_API * PFN_basesysal_getAdapterConnectorName)(const uint32_t index);
typedef BASESYSAL_IFC_PURPOSE (BASESYSAL_API * PFN_basesysal_getAdapterPurpose)(const uint32_t index);
typedef const uint8_t * (BASESYSAL_API * PFN_basesysal_getAdapterMac)(const uint32_t index);
typedef BASESYSAL_ERROR (BASESYSAL_API * PFN_basesysal_isAdapterEnabled)(const uint32_t index, int *enabled);
typedef uint32_t (BASESYSAL_API * PFN_basesysal_findAdapterByPurpose)(BASESYSAL_IFC_PURPOSE purpose);
typedef BASESYSAL_ERROR (BASESYSAL_API * PFN_basesysal_refreshAdapterSettings)(const uint32_t index);
typedef BASESYSAL_ERROR (BASESYSAL_API * PFN_basesysal_getAdapterIp)(const uint32_t index, uint32_t *ip, uint32_t *subnetMask);
typedef BASESYSAL_ERROR (BASESYSAL_API * PFN_basesysal_getAdapterAliasIp)(const uint32_t index, uint32_t *ip, uint32_t *subnetMask);
typedef BASESYSAL_ERROR (BASESYSAL_API * PFN_basesysal_getAdapterServerIp)(const uint32_t index, uint32_t *ipServer);
typedef BASESYSAL_ERROR (BASESYSAL_API * PFN_basesysal_getAdapterState)(const uint32_t index, uint32_t *state);
typedef BASESYSAL_ERROR (BASESYSAL_API * PFN_basesysal_sysNetDnsQuery)(const char *name, const uint32_t flags, uint32_t *ip);
//! @}

//! @name Defines for use with GetProcAddress()/dlsym() to identify the function.
//! @{

#define FN__BASESYSAL_GETADAPTERNUM           "basesysal_getAdapterNum"
#define FN__BASESYSAL_GETADAPTERFRIENDLYNAME  "basesysal_getAdapterFriendlyName"
#define FN__BASESYSAL_GETADAPTERNAME          "basesysal_getAdapterName"
#define FN__BASESYSAL_GETADAPTERCONNECTORNAME "basesysal_getAdapterConnectorName"
#define FN__BASESYSAL_GETADAPTERPURPOSE       "basesysal_getAdapterPurpose"
#define FN__BASESYSAL_GETADAPTERMAC           "basesysal_getAdapterMac"
#define FN__BASESYSAL_ISADAPTERENABLED        "basesysal_isAdapterEnabled"
#define FN__BASESYSAL_FINDADAPTERBYPURPOSE    "basesysal_findAdapterByPurpose"
#define FN__BASESYSAL_REFRESHADAPTERSETTINGS  "basesysal_refreshAdapterSettings"
#define FN__BASESYSAL_GETADAPTERIP            "basesysal_getAdapterIp"
#define FN__BASESYSAL_GETADAPTERALIASIP       "basesysal_getAdapterAliasIp"
#define FN__BASESYSAL_GETADAPTERSERVERIP      "basesysal_getAdapterServerIp"
#define FN__BASESYSAL_GETADAPTERSTATE         "basesysal_getAdapterState"
#define FN__BASESYSAL_SYSNETDNSQUERY          "basesysal_sysNetDnsQuery"
//! @}

//! @}

#ifdef __cplusplus	/* Declarations also in C++-Files */
	}
#endif /* __cplusplus */

//! @}

#endif //_BASESYSAL_H
