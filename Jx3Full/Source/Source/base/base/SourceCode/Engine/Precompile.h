//---------------------------------------------------------------------------
//	Engine的预编译头问件
//	Copyright : Kingsoft Season 2004
//	Author	:   Wooy(Wu yue)
//	CreateTime:	2004-3-21
//---------------------------------------------------------------------------
#ifndef _ENGINE_PRECOMPILE_H
#define _ENGINE_PRECOMPILE_H

#include "KGStdAfx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	#define _WIN32_WINNT 0x0500
	#include <windows.h>
    #include "KWin32.h"
    #include "winsock2.h"
#else
	#include <pthread.h>
#endif

#include "../../Include/CommonDefine.h"
#include "EngineBase.h"

#endif //#ifndef _ENGINE_PRECOMPILE_H
