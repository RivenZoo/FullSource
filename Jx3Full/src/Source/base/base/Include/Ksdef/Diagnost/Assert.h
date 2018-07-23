 /* -------------------------------------------------------------------------
//	文件名		：	ksdef/diagnost/assert.h
//	创建者		：	lailigao
//	创建时间	：	2004-5-9 11:33:25
//	功能描述	：	
//					repot from kfc
// -----------------------------------------------------------------------*/
#ifndef __KSDEF_DIAGNOST_ASSERT_H__
#define __KSDEF_DIAGNOST_ASSERT_H__

#if defined(_DEBUG)// || defined(Release_Diagnost)
#define Release_Trace
#define Release_MsgBox
#define Release_Assert
#endif
// -------------------------------------------------------------------------

#if defined(X_CC_GCC)
#	define KS_BREAKPOINT()			__asm__ __volatile__("int $0x03")
#else
#	define KS_BREAKPOINT()			__asm { int 3 }
#endif

#ifndef KS_ABORT
#define KS_ABORT()					exit (3)
#endif

// -------------------------------------------------------------------------
#if !defined(Release_Assert)

#ifndef ASSERT_ONCE2
#define ASSERT_ONCE2(e, msg)	NULL
#endif

#ifndef ASSERT2
#define ASSERT2(e, msg)		NULL
#endif

#ifndef ASSERT_
#define ASSERT_						NULLFN
#endif

#ifndef ASSERT_ONCE_
#define ASSERT_ONCE_				NULLFN
#endif

#ifndef REPORT_
#define REPORT_						NULLFN
#endif

#ifndef REPORT_ONCE_
#define REPORT_ONCE_				NULLFN
#endif

#else

#if defined(X_OS_WINDOWS)
	#ifndef ASSERT2
		#define ASSERT2(e, msg)												\
			do { if (!(e) &&												\
				(1 == _CrtDbgReport(_CRT_ASSERT, __FILE__, __LINE__, NULL, NULL))) \
				 _CrtDbgBreak(); } while (0)
	#endif //ASSERT2 - windows

#else //defined(X_OS_WINDOWS)

	#ifndef ASSERT2
		#if defined(X_CC_BC) || defined(X_CC_GCC)
			#define ASSERT2(e, msg)		INL_ASSERT(e)
		#else
			#define ASSERT2(e, msg)											\
				do {														\
					if (!(e))												\
					{														\
						KS_BREAKPOINT();									\
					}														\
				} while(0)
		#endif
	#endif //ASSERT2 - not windows

#endif // !defined(X_OS_WINDOWS)

#ifndef ASSERT_ONCE2
#define ASSERT_ONCE2(e, msg)												\
	do {																	\
		if (!(e))															\
		{																	\
			static int fReported = 0;										\
			ASSERT2(fReported, msg);										\
			fReported = 1;													\
		}																	\
	} while(0)
#endif

#endif // defined(Release_Assert)
// -------------------------------------------------------------------------

#ifndef VERIFY
#	if defined(_DEBUG)
#		define VERIFY(e)			ASSERT(e)
#	else
#		define VERIFY(e)			e
#	endif
#endif

#ifndef VERIFY_OK
#define VERIFY_OK(hr)				VERIFY( SUCCEEDED(hr) )
#endif

#ifndef _DEBUG_ONLY
#	if defined(_DEBUG)
#		define _DEBUG_ONLY(e)		e
#	else
#		define _DEBUG_ONLY(e)		NULL
#	endif
#endif

#ifndef DEBUG_ONLY
#define DEBUG_ONLY(e)				_DEBUG_ONLY(e)
#endif

#ifndef ASSERT
#define ASSERT(e)					ASSERT2(e, NULL)
#endif

#ifndef ASSERT_OK
#define ASSERT_OK(hr)				ASSERT( SUCCEEDED(hr) )
#endif

#ifndef ASSERT_ONCE
#define ASSERT_ONCE(e)				ASSERT_ONCE2(e, #e)
#endif

#ifndef REPORT
#define REPORT(msg)					ASSERT2(FALSE, msg)
#endif

#ifndef REPORT_ONCE
#define REPORT_ONCE(msg)			ASSERT_ONCE2(FALSE, msg)
#endif

// -------------------------------------------------------------------------

// -------------------------------------------------------------------------

#if !defined(INL_ASSERT)
#	if !defined(_DEBUG)
#		define INL_ASSERT(e)				NULL

#	elif defined(X_CC_BC) || defined(X_CC_GCC) // Linux Complier
#		include <stdio.h> // <assert.h>
#		define INL_ASSERT(e)												\
			do { if (!(e))													\
				printf("!!!!!!!!!!!!!!Assert %s(%d)\n", __FILE__, __LINE__); } while(0)
#	else
#		define INL_ASSERT			ASSERT
#	endif
#endif

// -------------------------------------------------------------------------

#endif /* __KSDEF_DIAGNOST_ASSERT_H__ */
