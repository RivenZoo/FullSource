//////////////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   KG_Time.cpp
//  Version     :   1.0
//  Creater     :   ZhaoChunFeng, Freeway Chen
//  Date        :   2004-11-11 18:26:11
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////
#include "Precompile.h"
#include "KWin32.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <fcntl.h>
#include <string.h>

#ifdef __GNUC__
#include <sys/time.h>
#include <unistd.h>
#include <stdint.h>
#endif

#include "KGPublic.h"
#include "KMutex.h"
#include "KG_Time.h"

static KMutex  gs_StartTickCountLock;

#ifdef __GNUC__
DWORD KG_GetTickCount()
{
    DWORD           dwResult      = 0;
    int             nRetCode      = 0;
    static uint64_t s_uBaseTime   = 0;
    uint64_t        uTime         = 0;
    timeval         TimeVal;

    nRetCode = gettimeofday(&TimeVal, NULL);
    if (nRetCode == 0)
    {
        uTime = ((uint64_t)TimeVal.tv_sec) * 1000 + TimeVal.tv_usec / 1000;
        if (s_uBaseTime == 0)
        {
            gs_StartTickCountLock.Lock();
            if (s_uBaseTime == 0)
            {
                s_uBaseTime = uTime;
            }
            gs_StartTickCountLock.Unlock();
        }
        dwResult = (DWORD)(uTime - s_uBaseTime) + 1; // at least 1, maybe some people use 0 for error  
    }

    return dwResult;
}
#else
DWORD KG_GetTickCount()
{
    unsigned long        ulResult              = 0;
    static unsigned long s_ulStartTickCount    = 0;
    static int           s_nStartFlag          = false;    

    if (!s_nStartFlag)
    {
        gs_StartTickCountLock.Lock();
        if (!s_nStartFlag)
        {
            s_ulStartTickCount = GetTickCount();
            s_nStartFlag = true;
        }
        gs_StartTickCountLock.Unlock();
    }
    
    ulResult = GetTickCount() - s_ulStartTickCount + 1;      // at least 1, maybe some people use 0 for error  
//Exit0:
    return ulResult;    
}
#endif

int KG_stime(time_t *ptmTime)
{
    int nResult  = false;
    int nRetCode = false;

#ifdef WIN32
    tm  tmServerTime;
    tm *pTime = NULL;
    SYSTEMTIME	tmSystemTime;

    pTime = localtime(ptmTime);
    if (!pTime)
         goto Exit0;
    tmServerTime               = *pTime;
    tmSystemTime.wYear         = tmServerTime.tm_year + 1900;
    tmSystemTime.wMonth        = tmServerTime.tm_mon + 1;
    tmSystemTime.wDay          = tmServerTime.tm_mday;
    tmSystemTime.wHour         = tmServerTime.tm_hour;
    tmSystemTime.wMinute       = tmServerTime.tm_min;
    tmSystemTime.wSecond       = tmServerTime.tm_sec;
    tmSystemTime.wDayOfWeek    = tmServerTime.tm_wday;
    tmSystemTime.wMilliseconds = 0;
    nRetCode = SetLocalTime(&tmSystemTime);
    KG_PROCESS_ERROR(nRetCode);
#else
    KG_PROCESS_ERROR(ptmTime);
    
    struct timeval tmval;
    tmval.tv_sec  = *ptmTime;
    tmval.tv_usec = 0;
    
    nRetCode = settimeofday(&tmval, NULL);
    KG_PROCESS_ERROR(nRetCode == 0);
#endif

    nResult = true;
Exit0:
    return nResult;
}
