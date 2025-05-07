///////////////////////////////////////////////////////////////////////////////
/*! \file   slsteplogicexports.h
 *  \author Jeyapalan Rasappah
 *  \date   22.11.2012
 *  \brief  DLL-Export declaration for step logic
 *
 *  This file is part of the HMI Solutionline, Business StepLogic.
 *
 *  (C) Copyright Siemens AG A&D MC 2012. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////


#if !defined (SL_STEP_LOGIC_EXPORT)
#  if defined (WIN32) || defined (WIN64)
#     if defined (SLSTEPLOGIC_EXPORTS)
#        define SL_STEP_LOGIC_EXPORT __declspec (dllexport)
#     else
#        define SL_STEP_LOGIC_EXPORT __declspec (dllimport)
#     endif
#  else
#      define SL_STEP_LOGIC_EXPORT
#  endif
#endif

#if !defined (SL_STEP_LOGIC_EXTERN)
#  if defined (SLSTEPLOGIC_EXPORTS)
#     define SL_STEP_LOGIC_EXTERN
#  else
#     define SL_STEP_LOGIC_EXTERN extern
#  endif
#endif
