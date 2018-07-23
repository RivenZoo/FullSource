//////////////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   KG_CreateGUID.cpp
//  Version     :   1.0
//  Creater     :   Freeway Chen
//  Date        :   2004-12-9 16:11:12
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////

#include "Precompile.h"
#include "KWin32.h"
#include <time.h>
#include <string.h>
#include "KGPublic.h"
#include "KMutex.h"

#include "KG_Time.h"
#include "KG_CreateGUID.h"
#include "inoutmac.h"

static KMutex gs_Lock;
static int gs_nCreateGUIDInitFlag = false;
static unsigned long gs_ulBaseCount = 0;

static unsigned char gs_MacAddress[6] = { 0 };


static unsigned gs_holdrand = 0;

static inline unsigned _Rand()
{
    gs_holdrand = gs_holdrand * 214013L + 2531011L;

    return gs_holdrand;
}


static inline int _InitMacAddress()
{
    return gGetMacAndIPAddress(NULL, NULL, gs_MacAddress, NULL);
}

int KG_CreateGUID(GUID *pGuid)
{
    int nResult = false;
    unsigned uValue = 0;
    
    KG_PROCESS_ERROR(pGuid);
    
    if (!gs_nCreateGUIDInitFlag)
    {
        gs_Lock.Lock();
        if (!gs_nCreateGUIDInitFlag)
        {
            _InitMacAddress();
            gs_holdrand = KG_GetTickCount();
            
            gs_nCreateGUIDInitFlag = true;
        }
        gs_Lock.Unlock();
    }
    
    memset(pGuid, 0, sizeof(*pGuid));
    
    memcpy(pGuid->Data4, gs_MacAddress, sizeof(gs_MacAddress));
    
    gs_Lock.Lock();
    
    pGuid->Data1 = ++gs_ulBaseCount;
    uValue = _Rand();
    
    gs_Lock.Unlock();
    
    pGuid->Data2 = (unsigned short)(uValue & 0xffff);
    pGuid->Data3 = (unsigned short)((uValue >> 16) & 0xffff);
    
    nResult = true;    
Exit0:
    return nResult;
}
