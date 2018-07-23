///////////////////////////////////////////////////////////////
//	
//  FileName		:   KLibrary.h
//  Composer		:	wangbin
//	latest Modify	:	2006-01-12
//  Comment			:   动态库的跨平台封装
//	
///////////////////////////////////////////////////////////////

#ifndef __KLIBRARY_H__
#define __KLIBRARY_H__

#ifdef __linux
#include "./KLibrary_linux.h"
#else
#include "./KLibrary_win32.h"
#endif

#endif //__KLIBRARY_H__
