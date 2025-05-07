#ifndef SL_FS_DATAPOOL_NAMESPACE_H
#define SL_FS_DATAPOOL_NAMESPACE_H

#define SLFS_COMMAND_REFRESH_SUI                "refreshSUI"

// <RO> <bool> reads "systemconfiguration/miscellaneous" "distributeJoblist"
#define SLFS_NAMESPACE_SUI_ISACTIVE             "SlHmi.SUI.isActive"
// <RO> <unsigned int> will be incremented by command SLFS_COMMAND_REFRESH_SUI
#define SLFS_NAMESPACE_SUI_COUNTER              "SlHmi.SUI.counter"

//      <QStringList>
#define SLFS_NAMESPACE_SELECTION_LIST           "SlHmi.Selection.List"
//      <bool>
#define SLFS_NAMESPACE_SELECTION_ISCUT          "SlHmi.Selection.isCut"
//      <int> -2: none -1: SystemManager, 0,... ProgrammManager
#define SLFS_NAMESPACE_SELECTION_SOURCE         "SlHmi.Selection.Source"

// <RO> <int> each access decrements the value -1,-2,....
#define SLFS_NAMESPACE_ARCHIVE_NEXTID           "SlHmi.Archive.nextId"

// <RO> <bool> true if local fileattribute are defined in slfsfileattributes.ini
#define SLFS_NAMESPACE_EXIST_LOCAL_FILEATTRIB   "SlHmi.Fileservice.existFileAttribute"

//      <QStringList> list of active GUD files
#define SLFS_NAMESPACE_NCU_ACTIVE_GUDS          "SlHmi.Ncu.GUDS.ActiveFiles"

// <RO> <QStringList> list of active GUD files for NCU
// example : //NC/DEF.DIR/GUD4.DEF //NC/DEF.DIR/GUD4_INCL.DEF
#define SLFS_NAMESPACE_NCU_X_ACTIVE_GUDS        "SlHmi.NcuX.%1.GUDS.ActiveFiles"
// <RO> <QStringList> list of all GUD modul names for NCU if empty -> ncu not valid, please wait
// example SMAC, MMAC, UMAC, PMAC, SGUD, ...
#define SLFS_NAMESPACE_NCU_X_GUD_MODULNAMES     "SlHmi.NcuX.%1.GUDS.ModulNames"
// <RO> <QString> for all active GUD moduls : description of active data {NC|CH|NCCH}
//                                            if GUD file contains REDEF statement REDEF is appended
//                for all macros            : description of first macro <macro name>[ -ACTIVE-]
//                for all include files     : (first) <macro name>
//                
//      <gudname>$<description>[#<gudname>$<description>]
#define SLFS_NAMESPACE_NCU_X_GUD_DATA           "SlHmi.NcuX.%1.GUDS.ActiveData"
// <RO> <QString> for all active GUD moduls : list of included files
//      <file>$<include1>[$<include2>][#<file>$<include1>[$<include2>]]
// example : GUD4.DEF$GUD4_INCL.DEF$GUD4_INCL2.DEF#GUD4_INCL.DEF$GUD4_INCL3.DEF
#define SLFS_NAMESPACE_NCU_X_GUD_INCLUDE        "SlHmi.NcuX.%1.GUDS.Includes"

///////////////////////////////////////////////////////////////////////////////
//
//        #(SLFS_NAMESPACE_VNCK_NAMELIST) == #(SLFS_NAMESPACE_VNCK_ROOTDIR_LIST)
// SLFS_NAMESPACE_VNCK_NAMELIST[i]: ncu name of virtual ncu[i], corresponding root
//       directory on HMI from SLFS_NAMESPACE_VNCK_ROOTDIR_LIST[i]
//
// <RO> <QStringList> list of virtual ncu's, empty for internal HMI
#define SLFS_NAMESPACE_VNCK_NAMELIST            "SlHmi.VNCK.NcuNameList"
// <RO> <QStringList> list of root diretories of virtual ncu's, empty for internal HMI
#define SLFS_NAMESPACE_VNCK_ROOTDIR_LIST        "SlHmi.VNCK.RootDirList"
//
///////////////////////////////////////////////////////////////////////////////

// <RO> <bool> , true if hardware of NCU828D supports User CF card, default: false
#define SLFS_NAMESPACE_NCU828D_SUPPORTS_USERCF  "SlHmi.NCU828D.supportsUserCF"

// START              ----- logical devices for EES -----
// <RO> <QString> device name of global partprogram storage, default:
#define SLFS_NAMESPACE_DEVICE_GTPSDEVICE        "SlHmi.Device.gTPSDevice"
// <RO> <QString> symbolic name of local directory, default:
#define SLFS_NAMESPACE_DEVICE_LDIR              "SlHmi.Device.lDIR"
// <RO> <QString> 828D only: symbolic name of system data directory, default:
#define SLFS_NAMESPACE_DEVICE_SYS_CARD          "SlHmi.Device.Sys_Card"
// <RO> <QString> 828D only: symbolic name of user CF card, default:
#define SLFS_NAMESPACE_DEVICE_CF_CARD           "SlHmi.Device.CF_Card"
// <RO> <QString> symbolic name of global partprogram storage, default:
#define SLFS_NAMESPACE_DEVICE_GTPS              "SlHmi.Device.gTPS"
// <RO> <bool> , true if passive filesystem of ncu has been defined, default: false
#define SLFS_NAMESPACE_DEVICE_EXIST_NCU_PFS     "SlHmi.Device.existNcuPFS"
// <RO> <QString> , list of NCU cycle directories (CMA,CUS) for program manager, default:
#define SLFS_NAMESPACE_DEVICE_PROG_NCU_CYCLES   "SlHmi.Device.NcuProgCycles"
// <RO> <QStringList> , list of all devices from logdrive.ini except ncu devices or ftp, default: <empty>
#define SLFS_NAMESPACE_DEVICE_LIST              "SlHmi.DeviceList"
// <RO> <QStringList> , list of all usb devices (and UserCF card for NCU828D) from logdrive.ini, default: <empty>
#define SLFS_NAMESPACE_REMOVABLE_DEVICE_LIST    "SlHmi.RemovableDeviceList"

// <RO> <QString> symbolic name of LOCAL_DRIVE:
// NCU828D: <empty> if LOCAL_DRIVE exist
// 828D: CF_CARD (if exist in logdrive.ini)
#define SLFS_NAMESPACE_DEVICE_LINK_LOCAL_DRIVE  "SlHmi.Device.Link.Local_Drive"
// <RO> <QString> symbolic name of CF_CARD:
// 828D: <empty> if CF_CARD exist in logdrive.ini
// NCU840D: LOCAL_DRIVE
#define SLFS_NAMESPACE_DEVICE_LINK_CF_CARD      "SlHmi.Device.Link.CF_Card"
// <RO> <QString> symbolic name of SYS_CARD:
// 828D: <empty> if SYS_CARD in logdrive.ini, else CF_CARD
// NCU840D: LOCAL_DRIVE
#define SLFS_NAMESPACE_DEVICE_LINK_SYS_CARD     "SlHmi.Device.Link.Sys_Card"

// <RO> <int> max. EES device index [1..], default: 24
#define SLFS_NAMESPACE_DEVICE_MAX_EESINDEX      "SlHmi.Device.MaxEESIndex"
// notice: recent part of namespace is the (casesensitive) entry name of section [DEVICE_x]
// <RO> <QString>, [USB.Front|USB.X203|USB.X204|USB.<xx>|smb|nfs|Local_Drive|NC|FTP]
//                 default:  -> end of data
#define SLFS_NAMESPACE_DEVICE_N_TYPE            "SlHmi.Device.%1.Type"
// <RO> <QString> USB: tcuName, FTP/smb/nfs: server name, default:
#define SLFS_NAMESPACE_DEVICE_N_DEVICE          "SlHmi.Device.%1.Server"
// <RO> <QString> only USB, default:  -> all usb partition
#define SLFS_NAMESPACE_DEVICE_N_PARTITION       "SlHmi.Device.%1.Partition"
// <RO> <QString>, subpath default:
#define SLFS_NAMESPACE_DEVICE_N_REALPATH        "SlHmi.Device.%1.RealPath"
// <RO> <int>, [0..7], default:7
#define SLFS_NAMESPACE_DEVICE_N_ACCESSLEVEL     "SlHmi.Device.%1.AccessLevel"
// <RO> <int> softkey number of program manager [1..24], default:0
#define SLFS_NAMESPACE_DEVICE_N_SOFTKEYNR       "SlHmi.Device.%1.SoftkeyNr"
// <RO> <QString> hmi softkey description default:
#define SLFS_NAMESPACE_DEVICE_N_SOFTKEYID       "SlHmi.Device.%1.SoftkeyId"
// <RO> <QString> softkey icon of program manager, default:
#define SLFS_NAMESPACE_DEVICE_N_ICON            "SlHmi.Device.%1.SoftkeyIcon"
// <RO> <QString>softkey text, default:
#define SLFS_NAMESPACE_DEVICE_N_SOFTKEYTEXT     "SlHmi.Device.%1.SoftkeyText"
// <RO> <QString>text context of text resource, default:
#define SLFS_NAMESPACE_DEVICE_N_TEXTCONTEXT     "SlHmi.Device.%1.TextContext"
// <RO> <QString>text file of text resource, default:
#define SLFS_NAMESPACE_DEVICE_N_TEXTFILE        "SlHmi.Device.%1.TextFile"
// <RO> <QString> symbolic name of device, default:
#define SLFS_NAMESPACE_DEVICE_N_SYMBDEVICENAME  "SlHmi.Device.%1.SymbDeviceName"
// <RO> <int> port number for connection only FTP, default:0
#define SLFS_NAMESPACE_DEVICE_N_PORT            "SlHmi.Device.%1.Port"
// <RO> <QString> additial usb port information , default:
#define SLFS_NAMESPACE_DEVICE_N_USBPORTPATH     "SlHmi.Device.%1.UsbPortPath"
// <RO> <int> timeout, 0=no timeout only FTP, default:0
#define SLFS_NAMESPACE_DEVICE_N_TIMEOUT         "SlHmi.Device.%1.ConnectionTimeout"
// <RO> <QString>, default: false
#define SLFS_NAMESPACE_DEVICE_N_WAITFORDEVICE   "SlHmi.Device.%1.NckWaitForDevice"
// <RO> <QString>, default:
#define SLFS_NAMESPACE_DEVICE_N_USERNAME        "SlHmi.Device.%1.Username"
// <RO> <QString>, default:
#define SLFS_NAMESPACE_DEVICE_N_PASSWORD        "SlHmi.Device.%1.Password"
// <RO> <bool>, default: false
#define SLFS_NAMESPACE_DEVICE_N_SHAREDEVICE     "SlHmi.Device.%1.ShareDevice"
// <RO> <QString>, device name for FTP, USB, default:
#define SLFS_NAMESPACE_DEVICE_N_SHARENAME       "SlHmi.Device.%1.ShareName"
// <RO> <QString>, ignore device for Nck, default:0
#define SLFS_NAMESPACE_DEVICE_N_NONEES          "SlHmi.Device.%1.nonEES"
// END                ----- logical devices for EES -----

#endif
