 /* -------------------------------------------------------------------------
//	文件名		：	ksdef/kern/typedef.h
//	创建者		：	lailigao
//	创建时间	：	2004-5-9 11:08:17
//	功能描述	：	
//					repot from kfc
// -----------------------------------------------------------------------*/
#if !defined(__KSDEF_KERN_TYPEDEF_H__) && !defined(_WINDEF_)
#define __KSDEF_KERN_TYPEDEF_H__

#pragma pack(push,1)
#pragma pack(1)

// -------------------------------------------------------------------------

#ifdef __cplusplus
#	undef  NULL
#	define NULL    0
#else
#	ifndef NULL
#	define NULL    ((void *)0)
#	endif
#endif

#ifndef FALSE
#define FALSE	0
#endif

#ifndef TRUE
#define TRUE	1
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef OPTIONAL
#define OPTIONAL
#endif

#undef far
#undef near

#define far
#define near

#ifndef CDECL
#define CDECL	__cdecl
#endif

#ifndef PASCAL
#define PASCAL	__stdcall
#endif

#undef FAR
#undef NEAR
#define FAR                 far
#define NEAR                near

#ifndef CONST
#define CONST               const
#endif

#ifndef MAX_PATH
#define MAX_PATH			260
#endif

// -------------------------------------------------------------------------

#ifndef BASETYPES
#define BASETYPES
typedef unsigned long ULONG;
typedef ULONG *PULONG;
typedef unsigned short USHORT;
typedef USHORT *PUSHORT;
typedef unsigned char UCHAR;
typedef UCHAR *PUCHAR;
typedef char *PSZ;
#endif  /* !BASETYPES */

#ifndef VOID
#define VOID void
typedef char CHAR;
typedef short SHORT;
typedef long LONG;
typedef LONG *PLONG;
#endif

typedef void* PVOID;
typedef unsigned short VARTYPE;
typedef short VARIANT_BOOL;
typedef long SCODE;

typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef double				DOUBLE;
typedef FLOAT               *PFLOAT;
typedef BOOL near           *PBOOL;
typedef BOOL far            *LPBOOL;
typedef BYTE near           *PBYTE;
typedef BYTE far            *LPBYTE;
typedef int near            *PINT;
typedef int far             *LPINT;
typedef WORD near           *PWORD;
typedef WORD far            *LPWORD;
typedef long far            *LPLONG;
typedef DWORD near          *PDWORD;
typedef DWORD far           *LPDWORD;
typedef void far            *LPVOID;
typedef CONST void far      *LPCVOID;

typedef int   		        INT;
typedef int					INT32;
typedef unsigned int        UINT;
typedef unsigned int        *PUINT;
typedef unsigned long long	ULONGLONG;
typedef long long			LONGLONG;
typedef DWORD				LCID;

typedef DWORD   COLORREF;
typedef DWORD*	LPCOLORREF;

#ifndef _HRESULT_DEFINED
#define _HRESULT_DEFINED
typedef LONG HRESULT;
#endif // !_HRESULT_DEFINED

#define MAKEWORD(a, b)      ((WORD)(((BYTE)(a)) | ((WORD)((BYTE)(b))) << 8))
#define MAKELONG(a, b)      ((LONG)(((WORD)(a)) | ((DWORD)((WORD)(b))) << 16))
#define LOWORD(l)           ((WORD)(l))
#define HIWORD(l)           ((WORD)(((DWORD)(l) >> 16) & 0xFFFF))
#define LOBYTE(w)           ((BYTE)(w))
#define HIBYTE(w)           ((BYTE)(((WORD)(w) >> 8) & 0xFF))

// -------------------------------------------------------------------------

#if defined(X_ENCODE_UCS2)
	typedef wchar_t WCHAR;
#elif defined(X_ENCODE_UCS4)
	typedef unsigned short WCHAR;
#else
#   error "Unknown Character Encoding!!!"
#endif

typedef WCHAR*	PWCHAR;
typedef WCHAR*	LPWCH, *PWCH;
typedef WCHAR*	LPWSTR, *PWSTR;
typedef CONST WCHAR* LPCWCH, *PCWCH;
typedef CONST WCHAR* LPCWSTR, *PCWSTR;

typedef CHAR *PCHAR;
typedef CHAR *LPCH, *PCH;

typedef CONST CHAR *LPCCH, *PCCH;
typedef CHAR *NPSTR;
typedef CHAR *LPSTR, *PSTR;
typedef CONST CHAR *LPCSTR, *PCSTR;

// --> Neutral ANSI/UNICODE types and macros
#ifdef  UNICODE

#ifndef _TCHAR_DEFINED
#define _TCHAR_DEFINED
typedef WCHAR TCHAR, *PTCHAR;
typedef WCHAR TBYTE, *PTBYTE;
#endif

typedef LPWSTR LPTCH, PTCH;
typedef LPWSTR PTSTR, LPTSTR;
typedef LPCWSTR LPCTSTR;
typedef LPWSTR LP;
#define __TEXT(quote) L##quote

#else   /* UNICODE */

#ifndef _TCHAR_DEFINED
#define _TCHAR_DEFINED
typedef char TCHAR, *PTCHAR;
typedef unsigned char TBYTE, *PTBYTE ;
#endif /* !_TCHAR_DEFINED */

typedef LPSTR LPTCH, PTCH;
typedef LPSTR PTSTR, LPTSTR;
typedef LPCSTR LPCTSTR;
#define __TEXT(quote) quote

#endif /* UNICODE */

#define TEXT(quote) __TEXT(quote)

// LLG_
#define strcmpi strcasecmp
#define stricmp strcasecmp

#define GUID_DEFINED

typedef struct _GUID {          // size is 16
    DWORD Data1;
    WORD   Data2;
    WORD   Data3;
    BYTE  Data4[8];
} GUID;

// -------------------------------------------------------------------------

typedef struct tagRECT
{
    LONG    left;
    LONG    top;
    LONG    right;
    LONG    bottom;
} RECT, *PRECT, NEAR *NPRECT, FAR *LPRECT;

typedef const RECT FAR* LPCRECT;

typedef struct tagPOINT
{
    LONG  x;
    LONG  y;
} POINT, *PPOINT, NEAR *NPPOINT, FAR *LPPOINT;

typedef struct tagSIZE
{
    LONG        cx;
    LONG        cy;
} SIZE, *PSIZE, *LPSIZE;

typedef union _LARGE_INTEGER
{
	struct {
		DWORD LowPart; 
		LONG  HighPart; 
	};
	LONGLONG QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER; 

typedef union _ULARGE_INTEGER
{
	struct {
		DWORD LowPart; 
		DWORD HighPart;
	};
	ULONGLONG QuadPart;
} ULARGE_INTEGER, *PULARGE_INTEGER;

#ifndef _tagCY_DEFINED
#define _tagCY_DEFINED
#define _CY_DEFINED
typedef union tagCY
{
	struct
	{
#ifdef _MAC
		long Hi;
		long Lo;
#else
		unsigned long Lo;
		long Hi;
#endif
    };
    LONGLONG int64;
} CY;
typedef CY* LPCY;
#endif /* _CY_DEFINED */

/* real definition that makes the C++ compiler happy */
typedef struct tagDEC {
    USHORT wReserved;
    union {
        struct {
            BYTE scale;
            BYTE sign;
        };
        USHORT signscale;
    };
    ULONG Hi32;
    union {
        struct {
#ifdef _MAC
            ULONG Mid32;
            ULONG Lo32;
#else
            ULONG Lo32;
            ULONG Mid32;
#endif
        };
        ULONGLONG Lo64;
    };
} DECIMAL;

// -------------------------------------------------------------------------

#ifndef DECLARE_HANDLE
#ifdef STRICT
	typedef void* HANDLE;
	#define DECLARE_HANDLE(name) struct name##__ { int unused; }; typedef struct name##__ *name
#else
	typedef void* HANDLE;
	#define DECLARE_HANDLE(name) typedef HANDLE name
#endif
	typedef HANDLE* PHANDLE;
#endif

#if !defined(__HMODULE)
#define __HMODULE
	DECLARE_HANDLE(HINSTANCE);
	typedef HINSTANCE HMODULE;	/* HMODULEs can be used in place of HINSTANCEs */
#endif

#ifndef HWND
	#define HWND unsigned long
#endif

// -------------------------------------------------------------------------

#ifndef EXTERN_C
#ifdef __cplusplus
#define EXTERN_C    extern "C"
#else
#define EXTERN_C
#endif
#endif

#ifndef STDAPI
#define STDAPI				EXTERN_C HRESULT __stdcall
#define STDAPI_(type)       EXTERN_C type __stdcall
#endif

#pragma pack(pop)

// -------------------------------------------------------------------------

#ifndef LISet32
#define LISet32(li, v)		((li).HighPart = (v) < 0 ? -1 : 0, (li).LowPart = (v))
#define ULISet32(li, v)		((li).HighPart = 0, (li).LowPart = (v))
#endif
	
#ifndef RGB
#define RGB(r,g,b)		((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
#endif
	

// -------------------------------------------------------------------------

#endif /* __KSDEF_KERN_TYPEDEF_H__ */
