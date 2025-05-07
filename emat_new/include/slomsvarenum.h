//////////////////////////////////////////////////////////////////////////////
/*! \file   slomsvarenum.h
 *  \author M. Hoseus
 *  \date   01.04.2015
 *  \brief  Enums for omsvar
 *
 *  This file is part of the HMI OmsVarAdapter/Service.
 *
 *  (C) Copyright Siemens AG MC R&D 2015. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SLOMSVAR_ENUM_H_INCLUDED)
#define SLOMSVAR_ENUM_H_INCLUDED

// function id's
enum SlOmsVarFctId
{
  OMSVAR_FCT_BACKUP   =  1,   // get archive
                              // input parameters:
                              //  string vector[0] = target name
                              //  string vector[1] = file name with absolute path
                              // output parameters: empty string vector
                              // return value: error if < 0, else success

  OMSVAR_FCT_RESTORE  =  2    // write archive
                              // input parameters:
                              //  string vector[0] = target name
                              //  string vector[1] = file name with absolute path
                              // output parameters: empty string vector
                              // return value: error if < 0, else success
};

#endif // SLOMSVAR_ENUM_H_INCLUDED
