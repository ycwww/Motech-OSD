//////////////////////////////////////////////////////////////////////////////
/*! \file   slfsenum.h
 *  \author Harald Amrehn
 *  \date   19.02.2009
 *  \brief  Enums for file service
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG MC R&D 2009. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SLFS_ENUM_H_INCLUDED)
#define SLFS_ENUM_H_INCLUDED

// for each entry DEVICE_[1..24] of logdrive.ini
// mount state of device
enum SlFsDeviceMountState
{
  LOGDRIVE_LOGSTATE_NOT_CONFIGURED   =  0, // is not not configured
  LOGDRIVE_LOGSTATE_OK               =  1, // is OK
  LOGDRIVE_LOGSTATE_TRY              =  2, // try to connect
  LOGDRIVE_LOGSTATE_DOUBLE_SYMB_NAME =  3, // dublicate symbolic name
  LOGDRIVE_LOGSTATE_MISSING_SERVER   =  4, // missing server
  LOGDRIVE_LOGSTATE_MISSING_SHARE    =  5, // missing share
  LOGDRIVE_LOGSTATE_MISSING_USER     =  6, // missing user
  LOGDRIVE_LOGSTATE_MISSING_PASSWORD =  7, // missing password
  LOGDRIVE_LOGSTATE_MISSING_REALPATH =  8, // missing real path
  LOGDRIVE_LOGSTATE_INVALID_REALPATH =  9, // invalid real path
  LOGDRIVE_LOGSTATE_INVALID_USB_PORT = 10, // invalid USB port path
  LOGDRIVE_LOGSTATE_CREDENTIAL_CONFL = 11, // credential conflict
  LOGDRIVE_LOGSTATE_LOGON_FAILURE    = 12, // logon failure
  LOGDRIVE_LOGSTATE_INVALID_PASSWORD = 13, // invalid password
  LOGDRIVE_LOGSTATE_PERMISSION_DENIED= 14, // permision denied
  LOGDRIVE_LOGSTATE_INVALID_TYPE     = 15, // invalid device type
  LOGDRIVE_LOGSTATE_IGNORE_TYPE      = 16, // ignore device type (FTP or NC)
  LOGDRIVE_LOGSTATE_INVALID_SHARE    = 17, // invalid share
};

// use for restarting drive
enum SlFsRestartDrive
{
  DRIVE_HMI = -1,
  // device = smb|<server>|<share> or nfs|<server> or USB.<connector>
  //          for PC: USB.#|<device>   device := [A,Z]: or [A,Z]
  DRIVE_FORCE,              // any change of devices.lst (without argument) or waiting for device
  DRIVE_EXIST_SYMBOLNAME,   // symbolic name(XX) exist
  DRIVE_NO_SYMBOLNAME,
  DRIVE_SYMBOL_MOUNTED      // symbolic name exist and has been mounted
};

enum SlFsWindeviceType
{
  WIN_DEVICE_FIXED     = 1,
  WIN_DEVICE_REMOVABLE = 0x02,
  WIN_DEVICE_REMOTE    = 0x04,
  WIN_DEVICE_CDROM     = 0x08,
  WIN_DEVICE_RAMDISK   = 0x10,
  WIN_DEVICE_ALL       = 0x1f
};

// bitmask for device type (1-15)
#define PATH_TYPE_BITMASK 0xff
// only for usb if PATH_TYPE_USBPARTITIONSTRUCT is set
// access to partition (1-N) from <logdrive>, 0 no parttion set
#define PATH_TYPE_PARTITION(X) (X >> 24)

// enum for execute command "typeOfPath"
enum SlFsPathType
{
  PATH_TYPE_NC = 1,
  PATH_TYPE_PLC,
  PATH_TYPE_CP,
  PATH_TYPE_CFCARD,
  PATH_TYPE_DNC,
  PATH_TYPE_COM,
  PATH_TYPE_FTP,
  // //ACTTCU/
  PATH_TYPE_ACTTCU,
  // //TCU/
  PATH_TYPE_GLOBALTCU,
  PATH_TYPE_NET,
  // Linux: /...  Windows: <Dev>:...
  PATH_TYPE_LOCAL,
  // NCU828D only: removable User CF Card
  PATH_TYPE_USERCF,
  // additional bit if local path is local drive on ncu 7x
  //                              external CFCard on tiger
  PATH_TYPE_LOCALDEVICE        = 0x000100,
  // additional bit if root of device, for USB //USB: or //USB:/01
  PATH_TYPE_ROOT               = 0x000200,
  // additional bit if device is defined as global part program storage
  PATH_TYPE_GLOBAL_PPS         = 0x000400,
  // additional bit for usb
  PATH_TYPE_USBFRONT           = 0x000800,
  // additional bit for usb partition struct on file system
  // ../01 ../02
  PATH_TYPE_USBPARTITIONSTRUCT = 0x001000,
  // additional bit for usb if partition supported and path == //USB:
  PATH_TYPE_SELECT_PARTITION   = 0x002000,
  // additional bit if device is locked for nck
  PATH_TYPE_LOCKED_FOR_NCK     = 0x004000
};

#endif // SLFS_ENUM_H_INCLUDED
