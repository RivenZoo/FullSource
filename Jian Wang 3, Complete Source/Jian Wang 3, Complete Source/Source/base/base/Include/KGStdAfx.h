#ifndef KG_STDAFX_H
#define	KG_STDAFX_H

#ifdef WIN32

#ifndef _CRT_SECURE_NO_DEPRECATE
#define	_CRT_SECURE_NO_DEPRECATE
#endif

#ifndef _CRT_NONSTDC_NO_DEPRECATE
#define	_CRT_NONSTDC_NO_DEPRECATE
#endif

#ifndef _USE_32BIT_TIME_T
#define	_USE_32BIT_TIME_T
#endif

//#define DECLSPEC_DEPRECATED
// 下面这个宏在2005下似乎会导致内存分配与释放不一致，大家就忍忍_malloca重定义的警告吧
//#define	_CRTDBG_MAP_ALLOC	// 使用CrtMemoryDebug 

#ifndef ASSERT
#include <assert.h>
#define ASSERT(x)	assert(x)
#endif

#else

#endif
#endif

