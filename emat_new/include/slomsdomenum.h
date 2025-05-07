//////////////////////////////////////////////////////////////////////////////
/*! \file   slomsdomenum.h
 *  \author Harald Amrehn
 *  \date   01.04.2015
 *  \brief  Enums for omsdom
 *
 *  This file is part of the HMI OmsDomAdapter/Service.
 *
 *  (C) Copyright Siemens AG MC R&D 2015. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SLOMSDOM_ENUM_H_INCLUDED)
#define SLOMSDOM_ENUM_H_INCLUDED

// function id's
enum SlOmsDomFctId
{
  OMSDOM_FCT_BACKUP   =  1,   // get archive
                              // input parameters:
                              //  string vector[0] = target name
                              //  string vector[1] = file name with absolute path
                              //  string vector[2] = password or empty
                              // output parameters: empty string vector
                              // return value: error if < 0, else success

  OMSDOM_FCT_RESTORE  =  2,   // write archive
                              // input parameters:
                              //  string vector[0] = target name
                              //  string vector[1] = file name with absolute path
                              //  string vector[2] = password or empty
                              // output parameters: empty string vector
                              // return value: error if < 0, else success

  OMSDOM_FCT_START    =  3,   // start PLC
                              // input parameters:
                              //  string vector[0] = target name
                              //  string vector[1] = password or empty
                              // output parameters: empty string vector
                              // return value: error if < 0, else success

  OMSDOM_FCT_STOP     =  4,   // stop PLC
                              // input parameters:
                              //  string vector[0] = target name
                              //  string vector[1] = password or empty
                              // output parameters: empty string vector
                              // return value: error if < 0, else success
  OMSDOM_FCT_STATE    =  5,   // state of PLC
                              // input parameters:
                              //  string vector[0] = target name
                              //  string vector[1] = password or empty
                              // output parameters, if asynchronous through onCompleted:
                              //  string vector[0] = "5" for number OMSDOM_FCT_STATE
                              //  string vector[1] = state for number
                              //  string vector[2] = state as text
                              // return value: error if < 0, else success
  OMSDOM_FCT_PROTINFO =  6,   // protection information of PLC
                              // input parameters:
                              //  string vector[0] = target name
                              // output parameters, if asynchronous through onCompleted:
                              //  string vector[0] = "6" for number OMSDOM_FCT_PROTINFO
                              //  string vector[1] = protection level for number
                              //  string vector[2] = failsafe active = "1" or not = "0" for bool
                              //  string vector[3] = password needed = "1" or not = "0" for bool
                              // return value: error if < 0, else success
  OMSDOM_FCT_CHECKPASSW = 7   // check password of PLC
                              // input parameters:
                              //  string vector[0] = target name
                              //  string vector[1] = password or empty
                              // output parameters, if asynchronous through onCompleted:
                              //  string vector[0] = "7" for number OMSDOM_FCT_CHECKPASSW
                              //  string vector[1] = password correct = "1" or not = "0" for bool
                              // return value: error if < 0, else success
};

#endif // SLFS_ENUM_H_INCLUDED
