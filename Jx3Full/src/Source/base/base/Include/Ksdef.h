/* -------------------------------------------------------------------------
//	文件名		：	Ksdef.h
//	创建者		：	lailigao
//	创建时间	：	2004-4-15 15:26:52
//	功能描述	：	公共的基础定义
//					repot from kfc
// -----------------------------------------------------------------------*/
#ifndef __INCLUDE_KSBASE_H__
#define __INCLUDE_KSBASE_H__

// -------------------------------------------------------------------------

#if defined(__AFX_H__) // Uses MFC
#undef TRACE
#undef ASSERT
#undef VERIFY
#endif

// -------------------------------------------------------------------------
#ifndef _INC_STDLIB
#include <stdlib.h>		// for malloc, realloc, free, etc.
#endif

#ifndef _INC_MALLOC
#include <malloc.h>		// for alloca
#endif

// -------------------------------------------------------------------------
#ifndef __KSDEF_PLATFORM_H__
#include "Ksdef/Platform.h"	// Platform Detection
#endif

#ifndef __KSDEF_STDDEF_H__
#include "Ksdef/Stddef.h"
#endif

#ifndef __KSDEF_DIAGNOST_H__
#include "Ksdef/Diagnost.h"
#endif

#endif /* __INCLUDE_KSBASE_H__ */
