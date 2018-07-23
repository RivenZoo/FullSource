//---------------------------------------------------------------------------
//  跨线程临界控制
//	Copyright : Kingsoft Season 2004
//	Author	:   Wooy(Wu yue)
//	CreateTime:	2004-5-18
//---------------------------------------------------------------------------
#ifndef _ENGINE_MUTEX_H_
#define _ENGINE_MUTEX_H_

#ifdef WIN32
	#ifndef	WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN
		#include <windows.h>
	#endif
#else
	#include <pthread.h>
#endif


#ifdef WIN32
	#define	EngineInterlockedExchange	InterlockedExchange
#else
	inline long EngineInterlockedExchange(long volatile* Target, long Value)
	{
		#define __xg(x) ((volatile long *)(x))
		__asm__ __volatile__("xchgl %k0,%1"
			:"=r" (Value)
			:"m" (*__xg(Target)), "0" (Value)
			:"memory");
		//long = 64bit
		//__asm__ __volatile__("xchgq %0,%1"
		//	:"=r" (Value)
		//	:"m" (*__xg(Target)), "0" (Value)
		//	:"memory");
		return Value;
	}
#endif

#ifdef	WIN32
	//控制变量类型
	#define MUTEX_TYPEDEF			CRITICAL_SECTION
	//控制变量声明
	#define MUTEX_DECLARE(name)		CRITICAL_SECTION	name
	//控制变量初始化
	#define	MUTEX_INIT(name)		InitializeCriticalSection(&name);
	//控制变量销毁
	#define	MUTEX_DELETE(name)		DeleteCriticalSection(&name);
	//进入临界区
	#define MUTEX_LOCK(name)		EnterCriticalSection(&name);
	//离开临界区
	#define	MUTEX_UNLOCK(name)		LeaveCriticalSection(&name);
#else
	//控制变量类型
	#define MUTEX_TYPEDEF			pthread_mutex_t
	//控制变量声明
	#define MUTEX_DECLARE(name)		pthread_mutex_t	name
	//控制变量初始化
	#define	MUTEX_INIT(name)		pthread_mutex_init(&name, NULL);
	//控制变量销毁
	#define	MUTEX_DELETE(name)		pthread_mutex_destroy(&name);
	//进入临界区
	#define MUTEX_LOCK(name)		pthread_mutex_lock(&name);
	//离开临界区
	#define	MUTEX_UNLOCK(name)		pthread_mutex_unlock(&name);
#endif

#endif	//ifndef _ENGINE_MUTEX_H_
