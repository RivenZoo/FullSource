//////////////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   KG_CpuTicker.h
//  Version     :   1.0
//  Creater     :   Freeway Chen
//  Date        :   2005/8/4 10:17:00
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////

#ifndef KG_CPUTICKER_H
#define KG_CPUTICKER_H

#define KG_USE_CPUTICKER
//#undef  KG_USE_CPUTICKER

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

#ifdef KG_USE_CPUTICKER
#include "KGLog.h"


#ifdef  WIN32
__declspec(naked) inline void __fastcall GetCPUTicker(unsigned long long *pullTicker)
{
    //__asm push ecx

    __asm push ebx
    __asm push ecx     // Save pTicker

    __asm xor  eax, eax

    //__asm _emit 0x0f    // cpuid - serialise the processor
    //__asm _emit 0xa2

    __asm _emit 0x0f    // rdtsc
    __asm _emit 0x31    

    __asm pop ecx     // Get pTicker
    __asm mov [ecx + 4], edx
    __asm mov [ecx], eax
    __asm pop ebx

    __asm ret

    //__asm pop ecx
}
#else	// WIN32

inline void GetCPUTicker(unsigned long long *pullTicker)
{
    unsigned long long ullCPUTick = 0;

    __asm__ __volatile__("rdtsc" : "=A" (ullCPUTick) : );

	*pullTicker = ullCPUTick;
}

#endif


class KG_CpuTicker
{
public:
    int Push(const char cszFunction[], int nLine);
    int Pop(unsigned uTimeoutTicker, const char cszFunction[], int nLine);

    KG_CpuTicker()  { m_CpuTickerDataVector.reserve(128);     }
    ~KG_CpuTicker() { assert(m_CpuTickerDataVector.empty()); } 

private:
    typedef struct KG_CpuTickerData
    {
        unsigned long long ullCpuTicker;
        char szFunction[256];
        int nLine;
    } KG_CpuTickerData;

    typedef vector<KG_CpuTickerData> KG_CpuTickerDataVector;
    
    KG_CpuTickerDataVector m_CpuTickerDataVector;
};

inline int KG_CpuTicker::Push(const char cszFunction[], int nLine)
{
    KG_CpuTickerData CpuTickerData;

    CpuTickerData.nLine = nLine;
    strncpy(CpuTickerData.szFunction, cszFunction, sizeof(CpuTickerData.szFunction));
    CpuTickerData.szFunction[sizeof(CpuTickerData.szFunction) - 1] = '\0';

    m_CpuTickerDataVector.push_back(CpuTickerData);

    GetCPUTicker(&(m_CpuTickerDataVector.back().ullCpuTicker));

    KGLogPrintf(
        KGLOG_DEBUG,
        "[%s]:%d, start tickers = %I64d", 
        cszFunction,
        nLine,
        m_CpuTickerDataVector.back().ullCpuTicker
    );

    GetCPUTicker(&(m_CpuTickerDataVector.back().ullCpuTicker));
    return true;
}

inline int KG_CpuTicker::Pop(unsigned uTimeoutTicker, const char cszFunction[], int nLine)
{
    unsigned long long ullCpuTicker = 0;

    GetCPUTicker(&ullCpuTicker);

    ullCpuTicker -= m_CpuTickerDataVector.back().ullCpuTicker;

    if (ullCpuTicker > uTimeoutTicker)
    {
        KGLogPrintf(
            KGLOG_DEBUG,
            "[%s]:%d->[%s]:%d timeout, tickers = %I64d", 
            m_CpuTickerDataVector.back().szFunction,
            m_CpuTickerDataVector.back().nLine,
            cszFunction,
            nLine,
            ullCpuTicker
        );
    }

    m_CpuTickerDataVector.pop_back();

    return true;
}

#else   // KG_USE_CPUTICKER

class KG_CpuTicker
{
public:
    int Push(const char cszFunction[], int nLine) { }
    int Pop(unsigned uTimeoutTicker, const char cszFunction[], int nLine) { }
};

#endif  // KG_USE_CPUTICKER

#endif // KG_CPUTICKER_H