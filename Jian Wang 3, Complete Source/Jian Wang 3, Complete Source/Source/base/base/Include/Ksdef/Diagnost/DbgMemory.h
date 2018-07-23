/* -------------------------------------------------------------------------
//	文件名		：	ksdef/diagnost/dbgmemory.h
//	创建者		：	lailigao
//	创建时间	：	2004-5-9 10:47:16
//	功能描述	：	
//					repot from kfc
// -----------------------------------------------------------------------*/
#ifndef __KSDEF_DIAGNOST_DBGMEMORY_H__
#define __KSDEF_DIAGNOST_DBGMEMORY_H__
/*
// -------------------------------------------------------------------------
#if defined(X_OS_WINDOWS)
	#define	_CRTDBG_MAP_ALLOC	// 使用CrtMemoryDebug
	#include <crtdbg.h>
#endif

// -------------------------------------------------------------------------
// --> Memory leak checker - SetBreakAlloc

#if defined(X_OS_WINDOWS)
#	define _XSetBreakAlloc(nAllocBreak) 	_CrtSetBreakAlloc(nAllocBreak)
#else
#	define _XSetBreakAlloc(nAllocBreak)		0
#endif // defined(X_OS_WINDOWS)

#ifndef SetBreakAlloc
	#define SetBreakAlloc(nAllocBreak)			_XSetBreakAlloc(nAllocBreak)
#endif

// -------------------------------------------------------------------------
// --> Memory leak checker by inspecting memory operation

#if defined(X_SUPPORT_CRTDBG) && defined(_DEBUG)
#if !defined(DEBUG_NEW)

INLINEAPI_(int) _XNormalBlockType()
{
	static int tmpFlag = 
		_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
	return _NORMAL_BLOCK;
}

#undef	malloc
#undef	calloc
#undef	realloc
#define malloc(s)       _malloc_dbg(s, _XNormalBlockType(), __FILE__, __LINE__)
#define calloc(c, s)    _calloc_dbg(c, s, _XNormalBlockType(), __FILE__, __LINE__)
#define realloc(p, s)   _realloc_dbg(p, s, _XNormalBlockType(), __FILE__, __LINE__)
#define DEBUG_NEW		new(_XNormalBlockType(), __FILE__, __LINE__)

#endif // DEBUG_NEW
#endif // SUPPORT_CRTDBG
*/
#ifndef DEBUG_NEW
#define DEBUG_NEW		new
#endif

// -------------------------------------------------------------------------

#endif /* __KSDEF_DIAGNOST_DBGMEMORY_H__ */
