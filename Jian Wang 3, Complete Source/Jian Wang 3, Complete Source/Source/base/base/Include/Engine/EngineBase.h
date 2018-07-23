//---------------------------------------------------------------------------
//	预编译头文件,Engine2的基本公共定义头问件
//	Copyright : Kingsoft Season 2004
//	Author	:   Wooy(Wu yue)
//	CreateTime:	2004-3-21
//---------------------------------------------------------------------------
#ifndef _ENGINE_BASE_H_
#define _ENGINE_BASE_H_

#ifdef __GNUC__     // linux
	#define		ENGINE_API
	#define		C_ENGINE_API extern "C"
#else               //WIN32
	#ifdef ENGINE_EXPORTS
		#define ENGINE_API __declspec(dllexport)
		#define C_ENGINE_API extern "C" __declspec(dllexport)
	#else
		#define ENGINE_API __declspec(dllimport)
		#define C_ENGINE_API extern "C" __declspec(dllimport)
	#endif
#endif


#endif //_ENGINE_BASE_H_
