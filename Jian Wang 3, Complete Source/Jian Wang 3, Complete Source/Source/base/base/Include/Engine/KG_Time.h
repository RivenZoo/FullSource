//////////////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   KG_Time.h
//  Version     :   1.0
//  Creater     :   ZhaoChunFeng, Freeway Chen
//  Date        :   2004-11-9 16:22:31
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef _KG_TIME_H_
#define _KG_TIME_H_     1

#ifdef WIN32
#include "KWin32.h"
#endif

#ifndef  ENGINE_API
#define  ENGINE_API
#endif

#ifdef WIN32

ENGINE_API unsigned long KG_GetTickCount();

#else

ENGINE_API unsigned long KG_GetTickCount();

#endif


ENGINE_API int KG_stime(time_t *ptmTime);


inline unsigned long long RDTSC()		// ReaD Time Stamp Counter
{
#ifdef WIN32
	__asm RDTSC
#else
    unsigned long long ullCPUTick = 0;
    unsigned uCPUTickLow  = 0;
    unsigned uCPUTickHigh = 0;

    __asm__ __volatile__("rdtsc" : "=a" (uCPUTickLow), "=d" (uCPUTickHigh): );

    ullCPUTick = (((unsigned long long)uCPUTickHigh) << 32) + uCPUTickLow;
    return ullCPUTick;
#endif
}

#endif

