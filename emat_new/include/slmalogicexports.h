///////////////////////////////////////////////////////////////////////////////
/*! \file   slmalogicexports.h
 *  \author Harald Vieten
 *  \date   05.07.2007
 *  \brief  DLL-Export declaration for machine logic
 *
 *  This file is part of the HMI Solutionline, Business Logic Machine/Parameter.
 *
 *  (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////


#if !defined (SL_MA_LOGIC_EXPORT)
#  if defined (WIN32) || defined (WIN64)
#     if defined (SLMALOGIC_EXPORTS)
#        define SL_MA_LOGIC_EXPORT __declspec (dllexport)
#     else
#        define SL_MA_LOGIC_EXPORT __declspec (dllimport)
#     endif
#  else
#      define SL_MA_LOGIC_EXPORT
#  endif
#endif

#if !defined (SL_MA_LOGIC_EXTERN)
#  if defined (SLMALOGIC_EXPORTS)
#     define SL_MA_LOGIC_EXTERN
#  else
#     define SL_MA_LOGIC_EXTERN extern
#  endif
#endif
