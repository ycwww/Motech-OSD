///////////////////////////////////////////////////////////////////////////////
/*! \file	slhminamespace.h
 *  \author Zapf Joachim
 *  \date   04.04.2007
 *  \brief	Header file for global namespace of HMI-sl
 *  
 *  (C) Copyright Siemens AG A&D MC 2007. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(_SL_HMI_NAMESPACE_INCLUDED)
#define _SL_HMI_NAMESPACE_INCLUDED


namespace SlHmi
{
  /*! \enum defining for SlAccessLevelEnum*/
  enum SlAccessLevelEnum
  {
    AccessLevelSystem       = 0,     //!< AccessLevel SYSTEM
    AccessLevelManufacturer = 1,     //!< AccessLevel MANUFACTURER
    AccessLevelService      = 2,     //!< AccessLevel SERVICE
    AccessLevelCustomer     = 3,     //!< AccessLevel CUSTOMER
    AccessLevelKey_3        = 4,     //!< AccessLevel KEY_3
    AccessLevelKey_2        = 5,     //!< AccessLevel KEY_2
    AccessLevelKey_1        = 6,     //!< AccessLevel KEY_1
    AccessLevelKey_0        = 7,     //!< AccessLevel KEY_0
    AccessLevelUndefined    = -1     //!< AccessLevel undefined
  };

  /*! \enum defining for SlNckTypeEnum*/
  enum SlNckTypeEnum
  {
    NckType840D_PL          = 0,     //!< NckType 840D Powerline
    NckTypeFM_NC            = 1000,  //!< NckType FM-NC
    NckType810D_PL          = 2000,  //!< NckType 810D Powerline
    NckType802S             = 4000,  //!< NckType 802S
    NckType802D_PL          = 5000,  //!< NckType 802D Powerline
    NckTypeSL               = 6000,  //!< NckType Solutionline
    NckType840D_SL          = 10700, //!< NckType 840D Solutionline
    NckType802D_SL          = 14000, //!< NckType 802D Solutionline
    NckType840Di_SL         = 15000, //!< NckType 840Di Solutionline
    NckType828D_SL          = 16000, //!< NckType 828D Solutionline (TIGER)
    NckType840evo           = 21000, //!< NckType 840 evo
    NckTypeNcLight          = 30000  //!< NckType NC-Light
  };

  /*! \enum defining for SlTechnology*/
  enum SlTechnologyEnum
  {
    TechnologyNone          = 0x00,
    TechnologyUniversal     = 0x01,  //!< Technology Universal
    TechnologyMilling       = 0x02,  //!< Technology Milling
    TechnologyTurning       = 0x04,  //!< Technology Turning
    TechnologyGrinding      = 0x08,  //!< Technology Grinding
    TechnologyStroking      = 0x10,  //!< Technology Stroking
    TechnologyPunching      = 0x20,  //!< Technology Punching

    TechnologyAll           =   TechnologyUniversal 
                              | TechnologyMilling
                              | TechnologyTurning
                              | TechnologyGrinding
                              | TechnologyStroking
                              | TechnologyPunching
  };

  /*! \enum defining acknowledgment modes for MMC commands*/
  enum SlMmcCommandAckMode
  {
      MmcCommandNoAck           = 0, //!< no acknowledgment
      MmcCommandSynchronousAck  = 1, //!< synchronous acknowledgment
      MmcCommandAsynchronousAck = 2  //!< asynchronous acknowledgment
  };

  /*! \enum defining acknowledgment values for MMC commands*/
  enum SlMmcCommandAckValue
  {
      MmcCommandProgrammed = 0, //!< programmed
      MmcCommandBusy       = 1, //!< busy
      MmcCommandFailed     = 2, //!< MMC command failed
      MmcCommandExecuted   = 3  //!< MMC command executed
  };

  enum SlFileAccessFlags
  {
      FileAccessAuto              = 0x00000000, // no special flags set (no skin directories, case-sensitiv...)
      FileAccessSkin              = 0x00000001, // writing in /user/.../skins/skin-name/cfg directory, reading from skin directories + fallback to normal cfg directories
      FileAccessIgnoreCase        = 0x00000002  // reading ignoring case
  };

  enum SlHmiFunctionMode
  {
    HmiPanelMode,
    HmiTerminalMode,
    HmiInterfaceMode
  };
};

#endif // _SL_HMI_NAMESPACE_INCLUDED
