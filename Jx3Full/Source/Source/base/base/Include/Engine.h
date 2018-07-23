//---------------------------------------------------------------------------
//  Engine头文件,引用Engine的其他模块包含此头问件来获得Engine各种接口数据的定义
//	Copyright : Kingsoft Season 2004
//	Author	:   Wooy(Wu yue)
//	CreateTime:	2004-3-21
//---------------------------------------------------------------------------
#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "KGStdAfx.h"
#include <string.h>		// 修正新版本GCC的编译错误
#include "./CommonDefine.h"
#include "./Engine/EngineBase.h"

#include "./Engine/Debug.h"
#include "./Engine/EDOneTimePad.h"		//译码与解码
#include "./Engine/KSG_MD5_String.h"	//md5译码与解码
#include "./Engine/KSG_StringProcess.h"	//字符串处理
#include "./Engine/Text.h"				//文字处理
#include "./Engine/File.h"				//文件操作
#include "./Engine/FileType.h"			//ini文件类型
#include "./Engine/KFileCache.h"		//文件缓存
#include "./Engine/Random.h"
#include "./Engine/KCodePoints.h"
#include "./Engine/KList.h"
#include "./Engine/LinkStructEx.h"
#include "./Engine/KBinsTree.h"
#include "./Engine/SmartPtr.h"
#include "./Engine/KPolygon.h"
#include "./Engine/KLinkArray.h"		//旧功能代码，新代码请应用KOccupyList
#include "./Engine/KOccupyList.h"		//占用表
#include "./Engine/KLogFile.h"			//日志记录功能模块(Jizheng 2004-9-2)
#include "./Engine/KLuaWrap.h"

#include "./Engine/CRC32.h"

//----以下接口的定义涉及到平台相关----
#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
#else
	#include <pthread.h>
	#include <assert.h>
#endif

#include "./Engine/Mutex.h"
#include "./Engine/RecycleBin.h"
#include "./Engine/Timer.h"
#include "./Engine/KThread.h"
#include "./Engine/ObjCache.h"

#ifdef WIN32
	#include "./Engine/KWin32App.h"
	#include "./Engine/KUrl.h"
	#include "./Engine/Kime.h"
#endif

#endif //ifndef _ENGINE_H_
