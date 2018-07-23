/* -------------------------------------------------------------------------
//	文件名		：	ksdef/Stddef.h
//	创建者		：	lailigao
//	创建时间	：	2004-5-9 10:50:33
//	功能描述	：	
//					repot from kfc
// -----------------------------------------------------------------------*/
#ifndef __KSDEF_STDDEF_H__
#define __KSDEF_STDDEF_H__

// =========================================================================
// --> Platform(kskern) Cofiguration

#if !defined(X_OS_WINDOWS) || defined(__USES_KSKERN__)
#	undef  USES_KSKERN
#	define USES_KSKERN
#endif

// =========================================================================

#if defined(X_OS_WINDOWS)

	#ifndef _WINDOWS_ //_WINDEF_
		#define _WIN32_WINNT  0x0400
		#include <windows.h>
		#define WIN32_LEAN_AND_MEAN
	#endif

	#if !defined(_OBJBASE_H_) && !defined(USES_KSKERN)
		#include <objbase.h>
	#else
		#include <stdlib.h>
	#endif

	typedef ULONG REFERENCE;

	#if defined(KSDEF_USES_SOCKET) && !defined(_WINSOCKAPI_)
		#if( _WIN32_WINNT >= 0x0400)
			#include <winsock2.h>
			#include <mswsock.h>
		#else
			#include <winsock.h>
		#endif /* _WIN32_WINNT >=  0x0400 */
	#endif

#else // !defined(X_OS_WINDOWS)

	#ifndef __KSDEF_KERN_TYPEDEF_H__
	#include "Kern/TypeDef.h"
	#endif

	#ifndef __KERN_ERRNO_H__
	#include "Kern/Errno.h"
	#endif

	#include <stdlib.h>

	#if defined(X_CC_BC)
	typedef LONG REFERENCE;
	#else
	typedef ULONG REFERENCE;
	#endif

#endif  // !defined(X_OS_WINDOWS)

// -------------------------------------------------------------------------

typedef unsigned HPTR;
typedef unsigned HBSTR;
typedef HPTR HWSTR;
typedef WCHAR KSWCHAR;

#pragma pack(1)

struct _Kern_AStrData
{
	char _data[1];
};

struct _Kern_WStrData
{
	KSWCHAR _data[1];
};

struct _Kern_Data
{
	char _data[1];
};

#pragma pack()

typedef struct _Kern_AStrData* KSASTR;
typedef struct _Kern_WStrData* KSWSTR;
typedef struct _Kern_Data* KSDATA;

// -------------------------------------------------------------------------

#ifndef NULL_HGBL
#define NULL_HGBL				0
#endif

// -------------------------------------------------------------------------
// --> Platform(OS) Cofiguration

#if defined(X_OS_WINDOWS)
#define X_SUPPORT_HGLOBAL		// HGLOBAL
#define X_SUPPORT_INCDEC		// InterlockedIncrement/InterlockedDecrement

#undef  wcstombs
#undef  mbstowcs
#define wcstombs(psz, pwcs, cch) WideCharToMultiByte(CP_ACP, 0, pwcs, -1, psz, cch, 0, 0)
#define mbstowcs(pwcs, psz, cch) MultiByteToWideChar(CP_ACP, 0, psz, -1, pwcs, cch)

#elif defined(X_OS_LINUX)

#define DLL_PROCESS_ATTACH		1
#define DLL_PROCESS_DETACH		0

#endif

// -------------------------------------------------------------------------
// --> Platform(Compiler) Cofiguration

#if defined(X_CC_VC)
#	pragma warning(disable:4786)
#	pragma warning(disable:4099)
#	define X_SUPPORT_STDCALL
#	define X_SUPPORT_NULLFN
#	define X_SUPPORT_DEFINE_WSTRING			// 支持在字符串前加L前缀，如: L"Hello"
#	define X_SUPPORT_DEFINE_LOCAL_WSTRING	// 支持在中文字符串前加L前缀，如: L"你好"
#	define X_SUPPORT_snwprintf				// 支持_snwprintf函数
#	define X_SUPPORT_swscanf				// 支持swscanf函数
#	define X_SUPPORT_itow					// 支持_itow函数
//#	define USES_DEFSTL
#	if !defined(_MFC_OVERRIDES_NEW)
#		define X_SUPPORT_CRTDBG
#	endif
#	define __KS_STR(x)			#x
#	define __KS_STR2(x)			__KS_STR(x)
#	define __KS_FILE_LINE		__FILE__ "(" __KS_STR2(__LINE__) "): Warning: "
//#	define prompt(desc)			message(__KS_FILE_LINE desc)
#	define COMPILE_MSG(desc)	message(__KS_FILE_LINE desc)
#	define linklib(szLib)		comment(lib, szLib)
#elif defined(X_CC_BC)
#	define X_SUPPORT_STDCALL
#	define X_SUPPORT_export					// 支持__export
//#	define USES_DEFSTL
//#	define _USE_OLD_RW_STL
#   define _STLP_NO_MEMBER_TEMPLATES
#	define _STLP_NO_MEMBER_TEMPLATE_CLASSES
#   define __STL_NO_MEMBER_TEMPLATES
#	define __STL_NO_MEMBER_TEMPLATE_CLASSES
#	ifndef __STDIO_H
#		include <stdio.h>
#	endif
#	pragma argsused			    // args not used
#	pragma warn -8080		    // variable declare but not used
#	pragma warn -8008		    // Condition is always true (or false)
#	pragma warn -8066		    // Unreachable code
#   if defined(__cplusplus) && !defined(X_DISABLE_MAXMIN_INLINE)
    namespace std {
        inline unsigned min(unsigned a, unsigned b)
            { return a < b ? a : b; }
        inline unsigned max(unsigned a, unsigned b)
            { return b < a ? a : b; }
        inline int min(int a, int b)
            { return a < b ? a : b; }
		inline int max(int a, int b)
            { return b < a ? a : b; }
    };
#   endif
#elif defined(X_CC_GCC)
#	define X_SUPPORT_STDCALL
//#	define USES_DEFSTL
#	define __stdcall			__attribute__((stdcall))
#	define __cdecl
#else
#	define __cdecl
#endif

#if !defined(X_SUPPORT_STDCALL)
#	if defined(X_NOUSE_STDCALL)
#		define __stdcall
#	else
#		error "Unsupport __stdcall?"
#	endif
#endif // !defined(X_SUPPORT_STDCALL)

#if !defined(X_SUPPORT_export)
#define __export
#endif

#if !defined(COMPILE_MSG)
#define COMPILE_MSG(desc)	message(desc)
#endif

#if !defined(linklib)
#define linklib(szLib)	message(szLib)
#endif

// =========================================================================

#if !defined(EXTERN_C)
#ifdef __cplusplus
#define EXTERN_C				extern "C"
#else
#define EXTERN_C
#endif
#endif

#ifndef APIENTRY
#define APIENTRY				__stdcall
#endif

#ifndef STDAPI
#define STDAPI                  EXTERN_C HRESULT __stdcall
#define STDAPI_(type)           EXTERN_C type __stdcall
#endif

#ifndef STDMETHOD
#define STDMETHODCALLTYPE		__stdcall
#define STDMETHOD(method)       virtual HRESULT STDMETHODCALLTYPE method
#define STDMETHOD_(type,method) virtual type STDMETHODCALLTYPE method
#define STDMETHODIMP            HRESULT STDMETHODCALLTYPE
#define STDMETHODIMP_(type)     type STDMETHODCALLTYPE
#endif

#ifndef INLINEAPI
#define INLINEAPI				inline HRESULT __stdcall
#define INLINEAPI_(type)		inline type __stdcall
#endif

#ifndef CDECLAPI
#define CDECLAPI				inline HRESULT __cdecl
#define CDECLAPI_(type)			inline type __cdecl
#endif

#ifndef EXPORTAPI
#define EXPORTAPI				STDAPI __export
#define EXPORTAPI_(type)		STDAPI_(type) __export
#endif

#ifndef STDPROC
#define STDPROC					virtual HRESULT __stdcall
#define STDPROC_(Type)			virtual Type __stdcall
#endif

#ifndef PURE
#define PURE					= 0
#endif

#ifndef DECLARE_IID
#define DECLARE_IID(Interface)	EXTERN_C const GUID IID_##Interface;
#endif

#ifndef DECLARE_CLSID
#define DECLARE_CLSID(ComClass)	EXTERN_C const GUID CLSID_##ComClass;
#endif

// =========================================================================
// 当条件为假时跳转：
#define KS_CHECK_BOOLEX(result, expr)										\
	if (!(result))															\
	{																		\
		expr;																\
		REPORT_ONCE(L"KS_CHECK_BOOLEX(" L ## #result L", " L ## #expr L");"); \
		goto KS_EXIT;														\
	}
#define KS_CHECK_BOOL(result)			KS_CHECK_BOOLEX(result, NULL)
#define KS_CHECK(hr)					KS_CHECK_BOOL(SUCCEEDED(hr))

#define CHECK_BOOLEX(result, expr)											\
	if (!(result))															\
	{																		\
		expr;																\
		goto KS_EXIT;														\
	}
#define	CHECK_BOOL(result)				CHECK_BOOLEX(result, NULL)
#define CHECK(hr)						CHECK_BOOL(SUCCEEDED(hr))

#if !defined(KS_TRY)
#	if defined(_DEBUG)
#		define KS_TRY
#		define KS_CATCH(e)				if (0)
#	else
#		define KS_TRY					try
#		define KS_CATCH(e)				catch(e)
#	endif
#endif

// =========================================================================

#ifndef	countof
#define countof(array)					(sizeof(array)/sizeof(array[0]))
#endif

#ifndef AllocMemory
#define AllocMemory(cb)					malloc(cb)
#define ReallocMemory(pv, cb)			realloc(pv, cb)
#define FreeMemory(pv)					free(pv)
#endif

#ifndef FillMemory
#define FillMemory(p, len, c)			memset(p, c, len)
#define ZeroMemory(p, len)				memset(p, 0, len)
#define CopyMemory(dst, src, len)		memcpy(dst, src, len)
#define MoveMemory(dst, src, len)		memmove(dst, src, len)
#endif

#ifndef ZeroStruct
#define ZeroStruct(buf)					ZeroMemory(&(buf), sizeof(buf))
#endif

#ifndef TokenVal
#define TokenVal(p, type)				(*((type*&)(p))++)
#endif

#ifndef TokenSize
#define TokenSize(p, size)				(((const char*&)(p)) += (size))
#endif

#ifndef ROUND
#define ROUND(x, y)						(((x)+(y)-1) & ~((y)-1))
#endif

#ifndef MAX
	#define MAX(x, y)					((x) > (y) ? (x) : (y))
	#define MIN(x, y)					((x) < (y) ? (x) : (y))
#endif

//#ifndef max
//	#define max(x, y)					MAX(x, y)
//	#define min(x, y)					MIN(x, y)
//#endif

#ifndef MAX_PATH
#define MAX_PATH		260
#endif

#ifndef _MAX_PATH
#define _MAX_PATH		MAX_PATH
#define _MAX_FNAME		256
#define _MAX_DRIVE		3
#define _MAX_DIR		256
#define _MAX_EXT		256
#endif

#ifndef _offsetof
#	if defined(X_CC_GCC)
#		define _offsetof(coclass, member)	( (size_t)&((coclass*)64)->member - 64 )
#	else
#		define _offsetof(coclass, member)	( (size_t)&((coclass*)0)->member )
#	endif
#endif

#ifndef FILE_BEGIN
	#define FILE_BEGIN           0
	#define FILE_CURRENT         1
	#define FILE_END             2
#endif

// -------------------------------------------------------------------------

#endif /* __KSDEF_STDDEF_H__ */
