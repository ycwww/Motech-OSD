///////////////////////////////////////////////////////////////////////////////
/*! \file   slhmimakros.h
 *  \author Gerolf Kuehnel
 *  \date   21.07.2003
 *  \brief  Interface of the HMI - Solutionline Styles
 *
 *  Makros used in HMI - Solutionline
 *
 *  This file is part of the HMI Solutionline global defines
 *
 *  (C) Copyright Siemens AG A&D MC 2003-2006. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SlMakros_h)
#define SlMakros_h

#include "slerror.h"

//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//

/*! \def SL_INLINE
 *
 *  defines the inline state. May be changed for optimization
 */
#define SL_INLINE        inline

/*! \def SL_NEW(POINTER,CONSTRUCTOR)
 *
 *  call new and returns and sets Pointer to 0 , if new runs into error
 */

/*! \def SL_NEW_RETURN(POINTER,CONSTRUCTOR,RET_VAL)
 *
 *
 *  call new and returns RET_VAL and sets Pointer to 0, if new runs into error
 */

/*! \def SL_NEW_NORETURN(POINTER,CONSTRUCTOR)
 *
 *  call new and sets Pointer to 0 if new runs into error
 */
// #if defined (__EXCEPTIONS)
// #   define SL_HAS_EXCEPTIONS
// #endif // __EXCEPTIONS


// #if defined (WIN32)
// #   define SL_HAS_EXCEPTIONS
// #endif // SL_HAS_WINCE

#if !defined(SL_HAS_EXCEPTIONS)

#	define SL_NEW_RETURN(POINTER,CONSTRUCTOR,RET_VAL) \
    { \
    	POINTER = new CONSTRUCTOR; \
        if (POINTER == 0) { return RET_VAL; } \
    }

#	define SL_NEW(POINTER,CONSTRUCTOR) \
    { \
        POINTER = new CONSTRUCTOR; \
        if (POINTER == 0) { return; }\
    }


#	define SL_NEW_NORETURN(POINTER,CONSTRUCTOR) \
    { \
    	POINTER = new CONSTRUCTOR;\
    }


#else
#include <new>
#define SL_BAD_ALLOC bad_alloc
#	define SL_NEW_RETURN(POINTER,CONSTRUCTOR,RET_VAL) \
	{   try { POINTER = new CONSTRUCTOR; } \
        catch (SL_BAD_ALLOC) { delete POINTER; POINTER = 0; return RET_VAL; } \
        catch (...) { delete POINTER; POINTER = 0; return RET_VAL; } \
	}

#	define SL_NEW(POINTER,CONSTRUCTOR) \
	{   try { POINTER = new CONSTRUCTOR; } \
        catch (...) { delete POINTER; POINTER = 0; return;} \
	}

#	define SL_NEW_NORETURN(POINTER,CONSTRUCTOR) \
	{   try { POINTER = new CONSTRUCTOR; } \
        catch (...) { delete POINTER; POINTER = 0;}\
	}

#endif // SL_HAS_EXCEPTIONS

//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
// for PIMPL idiom
#define SL_DECL_PIMPL(Class) \
    class Class##Private; \
    Class##Private* m_pData; \
    inline Class##Private* pData() { return reinterpret_cast<Class##Private *>(m_pData); } \
    inline const Class##Private* pData() const { return reinterpret_cast<const Class##Private *>(m_pData); } \
    Class(Class##Private* pData);

#define SL_DECL_PIMPL_INH(Class) \
    class Class##Private; \
    inline Class##Private* pData() { return reinterpret_cast<Class##Private *>(m_pData); } \
    inline const Class##Private* pData() const { return reinterpret_cast<const Class##Private *>(m_pData); } \
    Class(Class##Private* pData);
    
#define SL_GET_PIMPL(Class) Class##Private * const d = pData()


//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//


//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
// for multithreadding
#define SL_OPEN_GUARDED_BLOCK(a)    { QMutexLocker guard(&a);
#define SL_CLOSE_GUARDED_BLOCK      }


//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
// for corba methods to avoid warnings
#if defined(WIN32)
#   define SL_HMI_USE_CORBA_ENV
#else
#   define SL_HMI_USE_CORBA_ENV // ACE_UNUSED_ARG(_ACE_CORBA_Environment_variable);
#endif


//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
// for line seperators
#if defined (WIN32)
#   define SL_HMI_LINE_SEPARATOR   "\n"
#else
#   define SL_HMI_LINE_SEPARATOR   "\r\n"
#endif

//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//

///////////////////////////////////////////////////////////////////////////////
/*! \page pageErrorMacros HMI - Solutionline Errorcode Macros
 *
 *  If you want to check for Errors in returncodes you get, use the macros
 *  #SL_SUCCEEDED or #SL_FAILED. To get the errorcode, use #SL_ERROR_CODE,
 *  to get the modulecode, use #SL_MODULE_CODE.
 *
 *  \section UsingpageErrorMacros Usage
 *  \code
 *  qint32 nReturnValue = functionName(...);
 *  if (SL_SUCCEEDED(nReturnValue))
 *  {
 *      // good case
 *  }
 *  else
 *  {
 *      qint32 nErrorCode = SL_ERRORCODE(nReturnValue);
 *      switch(nReturnValue)
 *      ...
 *  }
 *  \endcode
 *
 *  \sa \ref pageErrorDefines
 */
///////////////////////////////////////////////////////////////////////////////

/*! \def SL_SUCCEEDED(State)
 *
 *  checks, wether the servity bit is set (failure = false) or not
 *  (success = true)
 *  \sa \ref pageErrorMacros
 */
#define SL_SUCCEEDED(State)        ((int)(State) >= 0)

/*! \def SL_FAILED(State)
 *
 *  checks, wether the servity bit is set (failure = true) or not
 *  (success = false)
 *  \sa \ref pageErrorMacros
 */
#define SL_FAILED(State)           ((int)(State)<0)

/*! \def SL_ERROR_CODE(State)
 *
 *  returns the errornumber of the errorcode
 *  \sa \ref pageErrorMacros
 */
#define SL_ERROR_CODE(State)       ((State) & SL_ERR_ERROR_MASK)

/*! \def SL_MODULE_CODE(State)
 *
 *  returns the modulenumber of the errorcode
 *  \sa \ref pageErrorMacros
 */
#define SL_MODULE_CODE(State)      ((State) & SL_ERR_MODULE_MASK)

/*! \def SL_SUB_ERROR_CODE(State)
 *
 *  returns the submodule errornumber of the errorcode
 *  \sa \ref pageErrorMacros
 */
#define SL_SUB_ERROR_CODE(State)   ((State) & SL_ERR_SUB_ERROR_MASK)

/*! \def SL_MODULE_CODE(State)
 *
 *  returns the submodulenumber of the errorcode
 *  \sa \ref pageErrorMacros
 */
#define SL_SUB_MODULE_CODE(State)  ((State) & SL_ERR_SUB_MODULE_MASK)

//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//

/*! \def SL_LINEMSG(desc)
 *
 *  generates an output like warnings and errors of Visual Studio(R). including
 *  filename and linenumber, so in Visual Studio, you can doubleclick the message
 *  and get to the line in the sourcecode.
 */
#define SL_CHSTR(x)  #x
#define SL_CHSTR2(x)  SL_CHSTR(x)
#define SL_LINEMSG(desc)  message(__FILE__ "(" SL_CHSTR2(__LINE__) ") : " desc)

//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//

/*! \page bitMacros HMI - Solutionline Bit Macros
 *  Macros for the handling with several bits in integer variables (type char, int, long)
 *
 *  mask    specifies the changing or checking bits in the variable.
 *          1 -> changing/checking, 0 -> not changing/checking
 *  \sa \ref bitMacros
 */

/*! \def SL_HMI_SET_BITMASK(variable,mask)
 *
 *  set the masked bits in variable
 *  \sa \ref bitMacros
 */
#define SL_HMI_SET_BITMASK(variable,mask)    ((variable) |= (mask))

/*! \def SL_HMI_CLR_BITMASK(variable,mask)
 *
 *  reset the masked bits in variable
 *  \sa \ref bitMacros
 */
#define SL_HMI_CLR_BITMASK(variable,mask)    ((variable) &= ~(mask))

/*! \def SL_HMI_CHECK_BITMASK(variable,mask)
 *
 *  checks, wether the masked bits in variable are set
 *  returns the setting bits and 0 if none bits of the mask set
 *  \sa \ref bitMacros
 */
#define SL_HMI_CHECK_BITMASK(variable,mask)   ((variable) & (mask))


/*! Macros for the handling with single bits in integer variables (type char, int, long)
 *
 *  bitnum  specifies the changing or checking bit in the variable.
 *          0 -> first bit (MSB), 1 -> second bit ...
 *  \sa \ref bitMacros
 */

/*! \def SL_HMI_SET_BITNUM(variable,bitnum)
 *
 *  set the specified bit in variable
 *  \sa \ref bitMacros
 */
#define SL_HMI_SET_BITNUM(variable,bitnum)   ((variable) |= 1 << (bitnum))

/*! \def SL_HMI_CLR_BITNUM(variable,bitnum)
 *
 *  reset the specified bit in variable
 *  \sa \ref bitMacros
 */
#define SL_HMI_CLR_BITNUM(variable,bitnum)   ((variable) &= ~(1 << (bitnum)))

/*! \def SL_HMI_CHECK_BITNUM(variable,bitnum)
 *
 *  checks the specified bit in variable
 *  \sa \ref bitMacros
 */
#define SL_HMI_CHECK_BITNUM(variable,bitnum)  (((variable) >> (bitnum)) & 1)

//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
///////////////////////////////////////////////////////////////////////////
// ENUM sort criteria for SlHmisettings
///////////////////////////////////////////////////////////////////////////
enum HmiSlCaseSensitivity 
{
    SL_HMI_NOT_SORTED,
    SL_HMI_PRIORISED_SORTED,
    SL_HMI_ASCENDING_SORTED,
    SL_HMI_DESCENDING_SORTED,
};

#if !defined(SL_HMI_EXPORT)
#   if defined(WIN32) || defined(WIN64)
#       ifdef SL_HMI_MAKE_DLL
#           define SL_HMI_EXPORT  __declspec(dllexport)
#       else
#           define SL_HMI_EXPORT  __declspec(dllimport)
#       endif
#   else
#       define SL_HMI_EXPORT
#   endif
#endif

namespace SlHmiEx
{
	// thread-safe ACE init/fini functions
	int SL_HMI_EXPORT initACE();
	int SL_HMI_EXPORT finiACE();
}

#endif //SlMakros_h

