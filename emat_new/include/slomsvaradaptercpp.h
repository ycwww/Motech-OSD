///////////////////////////////////////////////////////////////////////////////
/*! \file	slomsvarcom.h
 *  \author M. Hoseus
 *  \date   31.03.2015
 *  \brief	SlOmsVarAdapter interface
 *  This file is part of the OmsVarAdapter
 *  
 *  (C) Copyright Siemens AG MC R&D 2015. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SLOMSVARCOM_H
#define SLOMSVARCOM_H

#if defined WIN32
#if defined (SLOMSVARADAPTER_EXPORTS)
    #define SLOMSVARADAPTER_CPP __declspec (dllexport)
#else
    #define SLOMSVARADAPTER_CPP __declspec (dllimport)
#endif
#else
    #define SLOMSVARADAPTER_CPP
#endif

#include <string>
#include <vector>

class SlOmsVarAdapterCppImpl;

class SLOMSVARADAPTER_CPP SlOmsVarAdapterCpp
{

public:
	SlOmsVarAdapterCpp();
	virtual ~SlOmsVarAdapterCpp();

	virtual long read(std::string target, std::string varString, std::string varValue) = 0;
	virtual long write(std::string target, std::string varString, std::string varValue) = 0;

private:
	SlOmsVarAdapterCppImpl* m_pOmsVarAdapterCppImpl;
};

// creator pattern, needed for dynamical link
extern "C"
{
	//Creates an instance of SlOmsVarCom and returns the pointer to this instance 
	SLOMSVARADAPTER_CPP SlOmsVarAdapterCpp* WINAPI SlGetInstOfSlOmsVarAdapterCpp(void); 

	// deletes an instance of SlOmsVarAdapterCpp
	SLOMSVARADAPTER_CPP void WINAPI SlDeleteInstOfSlOmsVarAdapterCpp(SlOmsVarAdapterCpp* pOmsVarAdapterCpp);
}

#endif
