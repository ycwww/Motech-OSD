///////////////////////////////////////////////////////////////////////////////
/*! \file   slkclogicexports.h
 *  \author Adam Gorecki
 *  \date   11.05.2011
 *  \brief  DLL-Export declaration for kinematic chain logic
 *
 *  This file is part of the HMI Solutionline, Kinematic Logic Machine/Parameter.
 *
 *  (C) Copyright Siemens AG A&D MC 2011. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////


#if !defined (SL_KC_LOGIC_EXPORT)
#  if defined (WIN32) || defined (WIN64)
#     if defined (SLKCLOGIC_EXPORTS)
#        define SL_KC_LOGIC_EXPORT __declspec (dllexport)
#     else
#        define SL_KC_LOGIC_EXPORT __declspec (dllimport)
#     endif
#  else
#      define SL_KC_LOGIC_EXPORT
#  endif
#endif
