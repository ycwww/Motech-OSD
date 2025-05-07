
#if !defined(SL_DC_WIN_TYPES_H)
#define SL_DC_WIN_TYPES_H

#include <ace/OS.h>

#if defined(LINUX)

// Standard constants
#undef FALSE
#undef TRUE
#undef NULL

#define FALSE   0
#define TRUE    1
#define NULL    0

#define CONST               const

#define CALLBACK
#define WINAPI

#ifndef VOID
#define VOID void
typedef char CHAR;
#endif
#ifndef SHORT
typedef short SHORT;
#endif
#ifndef LONG
typedef long LONG;
#endif

typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef FLOAT               *PFLOAT;
typedef BOOL                *PBOOL;
typedef BOOL                *LPBOOL;
typedef BYTE                *PBYTE;
typedef BYTE                *LPBYTE;
typedef int                 *PINT;
typedef int                 *LPINT;
typedef WORD                *PWORD;
typedef WORD                *LPWORD;
typedef long                *LPLONG;
typedef DWORD               *PDWORD;
typedef DWORD               *LPDWORD;
typedef void                *LPVOID;
typedef CONST void          *LPCVOID;
typedef LONG                HRESULT;


typedef int                 INT;
typedef unsigned int        UINT;
typedef unsigned int        *PUINT;

typedef char     WCHAR;
typedef char     TCHAR;

typedef CONST WCHAR *LPCWSTR, *PCWSTR;
typedef CONST WCHAR *LPCUWSTR, *PCUWSTR;

typedef WCHAR *PWCHAR;
typedef WCHAR *LPWCH, *PWCH;
typedef CONST WCHAR *LPCWCH, *PCWCH;
typedef WCHAR *LPWSTR, *PWSTR;
typedef WCHAR *LPUWSTR, *PUWSTR;

typedef CHAR *LPSTR, *PSTR;
typedef CONST CHAR *LPCSTR, *PCSTR;

typedef LPWSTR LPTCH, PTCH;
typedef LPWSTR PTSTR, LPTSTR;
typedef LPCWSTR PCTSTR, LPCTSTR;
typedef LPUWSTR PUTSTR, LPUTSTR;
typedef LPCUWSTR PCUTSTR, LPCUTSTR;
typedef LPWSTR LP;

typedef SHORT *PSHORT;
typedef LONG *PLONG;

typedef void *PVOID;

typedef long LONG_PTR, *PLONG_PTR;
typedef unsigned long ULONG_PTR, *PULONG_PTR;

typedef ULONG_PTR DWORD_PTR, *PDWORD_PTR;

typedef ULONG_PTR SIZE_T;

typedef void *HANDLE;
#define DECLARE_HANDLE(name) struct name##__ { int unused; }; typedef struct name##__ *name

DECLARE_HANDLE(HINSTANCE);
typedef HINSTANCE HMODULE;      /* HMODULEs can be used in place of HINSTANCEs */

DECLARE_HANDLE            (HWND);

#endif /* LINUX */

typedef void*           HCONV;
typedef void*           HSZ;
typedef void*           HDDEDATA;
typedef double          DOUBLE;

#endif /* SL_DC_WIN_TYPES_H */
