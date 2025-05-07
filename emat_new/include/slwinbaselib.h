#if !defined( _SLWINBASELIB_H )
#define _SLWINBASELIB_H

#include <tchar.h>
#include "windows.h"

//export functions of pcuhwsvc.dll
#ifdef SLWINBASELIB_EXPORTS
#define SLWINBASELIB_API __declspec(dllexport)
#else
#define SLWINBASELIB_API __declspec(dllimport)
#endif

/****************************************************************************/
// functions returncode
//   0 if OK
//   system errorcode if error

SLWINBASELIB_API int slwbSetLocalTime(SYSTEMTIME* st);
SLWINBASELIB_API int slwbNetshCmd(TCHAR* szCmd);
SLWINBASELIB_API int slwbRouteCmd(TCHAR* szCmd);

//SJ: disabled because not used
#if 0
SLWINBASELIB_API DWORD slwbStartSharing(TCHAR* szAbsSSHcmd, TCHAR* szAbsKeyName, TCHAR* szPCUName,
										TCHAR* szLocalPath, TCHAR* szShareName, TCHAR* szNCU_IP);
SLWINBASELIB_API DWORD slwbStopSharing(TCHAR* szAbsSSHcmd, TCHAR* szAbsKeyName, TCHAR* szShareName, TCHAR* szNCU_IP);

SLWINBASELIB_API DWORD slwbStartSharing(TCHAR* szAbsSSHcmd, TCHAR* szPCUName,
										TCHAR* szLocalPath, TCHAR* szShareName, TCHAR* szNCU_IP);
SLWINBASELIB_API DWORD slwbStopSharing(TCHAR* szAbsSSHcmd, TCHAR* szShareName, TCHAR* szNCU_IP);
#endif
//SJ END

/****************************************************************************/

#endif //_SLWINBASELIB_H