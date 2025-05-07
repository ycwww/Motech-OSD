// /////////////////////////////////////////////////////////////////////////////
/*! \file   slomsvaradapterc.h
 *  \author M. Hoseus
 *  \date   31.03.2015
 *  \brief  SlOmsVarAdapter C and C++ interface without Qt
 *  This file is part of the SlOmsVarAdapter
 *  
 *  (C) Copyright Siemens AG MC R&D 2015. All rights reserved.
 */
// /////////////////////////////////////////////////////////////////////////////

#ifndef SLOMSVAR_H
#define SLOMSVAR_H

#if defined WIN32
#if defined (SLOMSVARADAPTER_EXPORTS)
#define SLOMSVARADAPTER_C __declspec (dllexport)
#else
#define SLOMSVARADAPTER_C __declspec (dllimport)
#endif
#else
#define SLOMSVARADAPTER_C
#endif

/*! 
  \class SlOmsVarAdapterC slomsvaradapterc.h
  \brief This is the documentation of the lightweight client user interface SlOmsVarAdapterC.

  SlOmsVarAdapterC offers a C++ interface without having Qt data types in interface.

  (C) Copyright Siemens AG DF MC 2015. All rights reserved.
  
*/
class SLOMSVARADAPTER_C SlOmsVarAdapterC
{
public:

  /*! 
   *  \brief Constructor of C-Interface of SlOmsVarAdapater
   */
  SlOmsVarAdapterC();

  /*! 
   *  \brief Destructor of C-Interface of SlOmsVarAdapater
   */
  virtual ~SlOmsVarAdapterC();

  /*! 
   *  \brief reads PLC data by C-Interface of SlOmsVarAdapater
   *
   *  Synchronous read of PLC-Variable
   *
   *  \return 0 if successful; or non-zero if failed.
   */
  virtual long read( 
                     const char* szTarget,     ///< [in] szTarget a IP Address of the PLC
                     const char* szVarString,  ///< [in] szVarString a PLC variable name
                     char* szVarValue,         ///< [in] buffer to fill with the value of the variable in the PLC
                     long bufLen               ///< [in] length of the buffer in bytes
                   ) = 0;

  /*! 
   *  \brief writes PLC data by C-Interface of SlOmsVarAdapater
   *
   *  Synchronous write of PLC-Variable
   *
   *  \return 0 if successful; or non-zero if failed.
   */
  virtual long write( 
                      const char* szTarget,    ///< [in] szTarget a IP Address of the PLC
                      const char* szVarString, ///< [in] szVarString a PLC variable name
                      const char* szVarValue   ///< [in] szVarValue the value to write to the variable in the PLC
                     ) = 0;

protected:

};

// creator pattern, needed for dynamical link
extern "C"
{
  /*! \brief creates an instance of SlOmsVarAdapterC and returns the pointer to this instance; \n
   *         belongs to creator pattern, needed for dynamical link.
   */
  SLOMSVARADAPTER_C SlOmsVarAdapterC* SlGetInstOfSlOmsVarAdapterC(void); 

  /*! \brief deletes an instance of SlOmsVar; \n
   *         belongs to creator pattern, needed for dynamical link.
   */
  SLOMSVARADAPTER_C void SlDeleteInstOfSlOmsVarAdapterC(SlOmsVarAdapterC* pOmsVarAdapterC); 

  /*! \brief reads PLC data via SlOmsVarService and OMS+; \n
   *         belongs to creator pattern, needed for dynamical link.
   */
  SLOMSVARADAPTER_C long SlOmsVarAdapterCRead(SlOmsVarAdapterC* pOmsVarAdapterC, const char* szTarget, const char* szVarString, char* szVarValue, long bufSize);

  /*! \brief writes PLC data via SlOmsVarService and OMS+; \n
   *         belongs to creator pattern, needed for dynamical link.
   */
  SLOMSVARADAPTER_C long SlOmsVarAdapterCWrite(SlOmsVarAdapterC* pOmsVarAdapterC, const char* szTarget, const char* szVarString, const char* szVarValue);

}

//For C-Interface

/// \brief creates an instance of SlOmsVarAdapterC and returns the pointer to this instance; \n
///        for C-Interface.
typedef SlOmsVarAdapterC* (* pfnGetInstOfSlOmsVarAdapterC) (void);

/// \brief deletes an instance of SlOmsVar; \n
///        for C-Interface. 
typedef void (* pfnDeleteInstOfSlOmsVarAdapterC) (SlOmsVarAdapterC*);

/// \brief reads PLC data via SlOmsVarService and OMS+; \n
///        for C-Interface.
typedef long (* pfnSlOmsVarAdapterCRead) (SlOmsVarAdapterC*, const char*, const char*, char*, long);

/// \brief writes PLC data via SlOmsVarService and OMS+; \n
///        for C-Interface.
typedef long (* pfnSlOmsVarAdapterCWrite) (SlOmsVarAdapterC*, const char*, const char*, const char*);

#define PROC_NAME_GET_INST "SlGetInstOfSlOmsVarAdapterC"
#define PROC_NAME_DEL_INST "SlDeleteInstOfSlOmsVarAdapterC"
#define PROC_NAME_READ_VAR "SlOmsVarAdapterCRead"
#define PROC_NAME_WRITE_VAR "SlOmsVarAdapterCWrite"

#endif 
