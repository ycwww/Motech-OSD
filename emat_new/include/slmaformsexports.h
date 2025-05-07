///////////////////////////////////////////////////////////////////////////////
/*! \file   slstepmaformsexports.h
 *  \author Rafael Baranowski
 *  \date   02.03.2015
 *  \brief  DLL-Export declaration for machine forms
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2015. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined (SL_MA_FORMS_EXPORT)
#  if defined (WIN32) || defined (WIN64)
#     if defined (SLMAFORMS_EXPORTS)
#        define SL_MA_FORMS_EXPORT __declspec (dllexport)
#     else
#        define SL_MA_FORMS_EXPORT __declspec (dllimport)
#     endif
#  else
#      define SL_MA_FORMS_EXPORT
#  endif
#endif

#if !defined (SL_MA_FORMS_EXTERN)
#  if defined (SLMAFORMS_EXPORTS)
#     define SL_MA_FORMS_EXTERN
#  else
#     define SL_MA_FORMS_EXTERN extern
#  endif
#endif

