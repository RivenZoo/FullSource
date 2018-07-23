//---------------------------------------------------------------------------
// Blade Engine (c) 1999-2000 by Kingsoft
//
// File:	KWin32.h
// Date:	2001.10.10
// Code:	Daphnis
// Desc:	Percompiled header files of Win32 Platform
//---------------------------------------------------------------------------
#ifndef KWin32_H
#define KWin32_H 

#include "Ksdef.h"

#pragma warning (disable: 4786)

#ifdef _STANDALONE
	#define ENGINE_API
#else
#ifndef ENGINE_API
	#ifdef ENGINE_EXPORTS
		#define ENGINE_API __declspec(dllexport)
	#else
		#define ENGINE_API __declspec(dllimport)
	#endif
#endif
#endif

#ifndef __linux
	#ifdef _STANDALONE
		#include <winsock2.h>
	#endif
	//#define _WIN32_WINNT  0x0400
	//#include <windows.h>
	#define DIRECTINPUT_VERSION 0x800
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
	#if _MSC_VER > 1000
		#pragma once
	#endif // _MSC_VER > 1000

    //#include <windows.h>
    #include <mmsystem.h>

#else	// #ifndef __linux

//	#ifdef WIN32
//		#define SUCCEEDED(x)		((x) > 0)
//	#else
//		#define SUCCEEDED(x)		((long)x >= 0)
//	#endif

	#ifndef HWND
		#define HWND unsigned long
	#endif

	#include <stdarg.h> 
	#include <pthread.h>
	#include <unistd.h>
	#define SOCKET_ERROR -1
#endif	// #ifndef __linux #else

//---------------------------------------------------------------------------
// Insert your headers here
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
//---------------------------------------------------------------------------
#include <stdio.h>

#ifndef ITOA
#define ITOA(NUMBER)  #NUMBER
#endif

#ifndef __TEXT_LINE__
#define __TEXT_LINE__(LINE) ITOA(LINE)
#endif

#ifndef KSG_ATTENTION
#define KSG_ATTENTION(MSG) __FILE__"("__TEXT_LINE__(__LINE__)") : ATTENTION "#MSG
#endif

//---------------------------------------------------------------------------
#endif
