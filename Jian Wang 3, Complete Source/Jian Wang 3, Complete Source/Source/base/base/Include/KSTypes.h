#ifndef _KSTYPES_H_
#define _KSTYPES_H_ 1

#ifdef __cplusplus
extern "C"{
#endif

/* [local] */ 

#ifndef CALLTYPE_DEFINED
#define CALLTYPE_DEFINED

#if  (defined(_MSC_VER) || defined(__ICL))
	#define KSCOMSTDMETHOD			__stdcall
	#define KSCOMFASTCALLMETHOD		__fastcall
	#define KSCOMCDECLMETHOD		__cdecl
#elif   defined(__GNUC__)
	#define KSCOMSTDMETHOD			__attribute__ ((stdcall))
	#define KSCOMFASTCALLMETHOD
	#define KSCOMCDECLMETHOD
#else   // NOT
	#define KSCOMSTDMETHOD
	#define KSCOMFASTCALLMETHOD
	#define KSCOMCDECLMETHOD
#endif  // NOT

#ifndef STDMETHODCALLTYPE
	#define STDMETHODCALLTYPE KSCOMSTDMETHOD
#endif

#endif  // CALLTYPE_DEFINED

#ifndef NULL
	#define NULL 0
#endif  // NULL

#ifndef MAX_PATH
	#ifdef  __linux
		#define MAX_PATH 1024
	#else
		#define MAX_PATH 260
	#endif
#endif  // MAX_PATH

#define __RPC_FAR


typedef unsigned char byte;
typedef unsigned long KSDWORD;

typedef int KSBOOL;

typedef unsigned char KSBYTE;

typedef unsigned short KSWORD;

typedef KSDWORD DWORD;

typedef KSWORD WORD;

typedef KSBYTE BYTE;

typedef char *PCHAR;

typedef unsigned long ULONG;

#if 0
typedef __int64 LONGLONG;

typedef unsigned __int64 ULONGLONG;

#endif
#ifdef __GNUC__
typedef long long			LONGLONG;
typedef unsigned long long	ULONGLONG;
#else
typedef __int64				LONGLONG;
typedef unsigned __int64	ULONGLONG;
#endif	// _GCC_COMPLIER_
//typedef unsigned short wchar_t;

typedef wchar_t WCHAR;

typedef WCHAR OLECHAR;

typedef OLECHAR __RPC_FAR *LPOLESTR;

typedef const OLECHAR __RPC_FAR *LPCOLESTR;

#if 0
typedef struct  _LARGE_INTEGER
    {
    LONGLONG QuadPart;
    }	LARGE_INTEGER;

typedef struct  _ULARGE_INTEGER
    {
    ULONGLONG QuadPart;
    }	ULARGE_INTEGER;

#endif
typedef union _LARGE_INTEGER {
//    struct {
//        KSDWORD LowPart;
//        long HighPart;
//    };
    struct {
        KSDWORD LowPart;
        long HighPart;
    } u;
    LONGLONG QuadPart;
} LARGE_INTEGER;
typedef LARGE_INTEGER __RPC_FAR *PLARGE_INTEGER;

typedef union _ULARGE_INTEGER {
//    struct {
//        KSDWORD LowPart;
//        KSDWORD HighPart;
//    };
    struct {
        KSDWORD LowPart;
        KSDWORD HighPart;
    } u;
    ULONGLONG QuadPart;
} ULARGE_INTEGER;
typedef ULARGE_INTEGER __RPC_FAR *PULARGE_INTEGER;

#ifndef KAV_HANDLE_DEFINED
#define KAV_HANDLE_DEFINED
typedef void __RPC_FAR *KAVHANDLE;

#endif // KAV_HANDLE_DEFINED



#ifdef __cplusplus
}
#endif

#endif // _KSTYPES_H_
