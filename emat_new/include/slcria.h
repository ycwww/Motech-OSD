///////////////////////////////////////////////////////////////////////////////
/*! \file   slcria.h
*   \author Michael Schlemper
*   \date   22.03.2006
*   \brief  Headerfile for typedefs
*
*   This file is part of the HMI Solutionline criteria analysis service.
*
*   (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#if !defined SL_CRIA_H_
#define SL_CRIA_H_


#if defined WIN32
#if defined (SL_CRIA_SVC_ADAPTER_EXPORTS)
#define SL_CRIA_SVC_ADAP_EXPORTS __declspec (dllexport)
#else
#define SL_CRIA_SVC_ADAP_EXPORTS __declspec (dllimport)
#endif
#else
#define SL_CRIA_SVC_ADAP_EXPORTS
#endif


#endif //!defined SL_CRIA_H_
