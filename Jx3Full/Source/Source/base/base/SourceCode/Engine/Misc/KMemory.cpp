#include "Precompile.h"
#include <limits.h>
#include <assert.h>
#include <vector>
#include <cstddef>
#include "KG_InterlockedVariable.h"
#include "KG_InterlockSingleList.h"
#include "KMutex.h"
#include "KGPublic.h"
#include "KMemory.h"

// warning C4200: 使用了非标准扩展 : 结构/联合中的零大小数组
#pragma warning(disable: 4200)

struct KMBlock
{
    KG_SLIST_ENTRY Link;
};

typedef std::vector<void*> KORG_HEAD_TABLE;

struct KMBarrel
{
    KORG_HEAD_TABLE HeadTable;
    size_t          uBlockSize;
    int             nTotalAlloc;
    int             nLastAlloc;
    KG_SLIST_HEADER FreeList;
};

enum
{
    MATCH_S = sizeof(void*),
    MATCH_M = MATCH_S * 4,
    MATCH_L = 1024,

    MATCH_S_SECTION = 128,
    MATCH_M_SECTION = 4096,
    MATCH_L_SECTION = 1024 * 256,

    MATCH_S_COUNT = (MATCH_S_SECTION  / MATCH_S),
    MATCH_M_COUNT = ((MATCH_M_SECTION - MATCH_S_SECTION)  / MATCH_M),
    MATCH_L_COUNT = ((MATCH_L_SECTION - MATCH_M_SECTION)  / MATCH_L),

    TOTAL_BARREL_COUNT = (MATCH_S_COUNT + MATCH_M_COUNT + MATCH_L_COUNT),
};

struct KUserBlockHeader 
{
    int    nMagic;
    size_t uSize;
    BYTE   byUserData[0];
};

static size_t       g_uUsedMemorySize   = 0;
static KMBarrel*    g_pBarrelTable      = NULL;
static KMutex       g_Mutex;
static char         g_szFileName[MAX_PATH] = "defatlt.memory";

#define             MEMORY_POOL_VERSION     1

namespace KMemory
{
    BOOL PreAlloc();
    BOOL Save();
    BOOL Load();
    int  GetBarrelIndex(size_t uBlockSize);
    BOOL Expend(KMBarrel* pBarrel);
};

BOOL KMemory::Initialize(const char cszFileName[])
{
    BOOL        bResult      = false;
    int         nIndex       = 0;
    size_t      uBlockSize   = 0;

    if (cszFileName)
    {
        strncpy(g_szFileName, cszFileName, sizeof(g_szFileName));
        g_szFileName[sizeof(g_szFileName) - 1] = '\0';
    }

    g_pBarrelTable = new KMBarrel[TOTAL_BARREL_COUNT];
    KG_PROCESS_ERROR(g_pBarrelTable);

    memset(g_pBarrelTable, 0, sizeof(KMBarrel) * TOTAL_BARREL_COUNT);

    for (int i = 0; i < TOTAL_BARREL_COUNT; i++)
    {
        KG_InitializeSListHead(&g_pBarrelTable[i].FreeList);
    }

    while (uBlockSize < MATCH_S_SECTION)
    {
        uBlockSize += MATCH_S;
        g_pBarrelTable[nIndex].uBlockSize = uBlockSize;
        nIndex++;
    }

    while (uBlockSize < MATCH_M_SECTION)
    {
        uBlockSize += MATCH_M;
        g_pBarrelTable[nIndex].uBlockSize = uBlockSize;
        nIndex++;
    }

    while (uBlockSize < MATCH_L_SECTION)
    {
        uBlockSize += MATCH_L;
        g_pBarrelTable[nIndex].uBlockSize = uBlockSize;
        nIndex++;
    }

    Load();

    PreAlloc();
    
    bResult = true;
Exit0:
    if (!bResult)
    {
        KG_DELETE_ARRAY(g_pBarrelTable);
    }
    return bResult;
}

void KMemory::Finalize()
{
    Save();

    for (int i = 0; i < TOTAL_BARREL_COUNT; i++)
    {
        KMBarrel* pBarrel = g_pBarrelTable + i;
        int       nCount  = (int)pBarrel->HeadTable.size();

        for (int j = 0; j < nCount; j++)
        {
            void* pBlock = pBarrel->HeadTable[j];
            free(pBlock);
        }
    }
    
    KG_DELETE_ARRAY(g_pBarrelTable);
}

BOOL KMemory::PreAlloc()
{
    BOOL            bResult = false;

    for (int nBarrelIndex = 0; nBarrelIndex < TOTAL_BARREL_COUNT; nBarrelIndex++)
    {
        KMBarrel*       pBarrel = &g_pBarrelTable[nBarrelIndex];

        if (pBarrel->nLastAlloc < 1)
        {
            continue;
        }

        Expend(pBarrel);
    }    

    bResult = true;
//Exit0:
    return bResult;
}

int KMemory::GetBarrelIndex(size_t uBlockSize)
{
    int nIndex = -1;

    KG_PROCESS_ERROR(uBlockSize > 0);

    uBlockSize--;

    if (uBlockSize < MATCH_S_SECTION)
    {
        nIndex = (int)(uBlockSize / MATCH_S);
    }
    else if (uBlockSize < MATCH_M_SECTION)
    {
        nIndex = MATCH_S_COUNT + (int)(uBlockSize - MATCH_S_SECTION) / MATCH_M;
    }
    else if (uBlockSize < MATCH_L_SECTION)
    {
        nIndex = MATCH_S_COUNT + MATCH_M_COUNT + (int)(uBlockSize - MATCH_M_SECTION) / MATCH_L;
    }

Exit0:
    return nIndex;
}

BOOL KMemory::Expend(KMBarrel* pBarrel)
{
    BOOL            bResult     = false;
    BYTE*           pbyAddr     = NULL;
    KMBlock*        pBlock      = NULL;
    KG_SLIST_ENTRY* pLink       = NULL;
    int             nIncCount   = 0;

    g_Mutex.Lock();

    pLink = KG_InterlockedPopEntrySList(&pBarrel->FreeList);
    if (pLink)
    {
        KG_InterlockedPushEntrySList(&pBarrel->FreeList, pLink);
        goto Exit0;
    }

    if (pBarrel->nTotalAlloc == 0)
    {
        nIncCount = (int)(pBarrel->nLastAlloc * 0.95f);
    }
    else
    {
        nIncCount = pBarrel->nTotalAlloc / 8;
    }

    if (nIncCount < 1)
    {
        nIncCount = 1;
    }
    
    pbyAddr = (BYTE*)malloc(pBarrel->uBlockSize * nIncCount);
    KG_PROCESS_ERROR(pbyAddr);

    pBarrel->HeadTable.push_back(pbyAddr);

    for (int i = 0; i < nIncCount; i++)
    {
        pBlock = (KMBlock*)pbyAddr;

        pBlock->Link.Next = NULL;
        KG_InterlockedPushEntrySList(&pBarrel->FreeList, &pBlock->Link);

        pbyAddr += pBarrel->uBlockSize;
    }

    pBarrel->nTotalAlloc += nIncCount;

    bResult = true;
Exit0:
    g_Mutex.Unlock();
    return bResult;
}

void* KMemory::RawAlloc(size_t uSize)
{
    void*           pResult         = NULL;
    KMBarrel*       pBarrel         = NULL;
    int             nBarrelIndex    = GetBarrelIndex(uSize);
    KG_SLIST_ENTRY* pLink           = NULL;
    size_t          uAllocedSize    = uSize;

    if (nBarrelIndex == -1)
    {
        pResult = malloc(uSize);
        goto Exit0;
    }

    pBarrel = g_pBarrelTable + nBarrelIndex;

    assert(pBarrel->uBlockSize >= uSize);
    assert(pBarrel->uBlockSize >= sizeof(KMBlock));
    
    uAllocedSize = pBarrel->uBlockSize;

    pLink = KG_InterlockedPopEntrySList(&pBarrel->FreeList);
    if (pLink == NULL)
    {
        Expend(pBarrel);
        pLink = KG_InterlockedPopEntrySList(&pBarrel->FreeList);
    }
    KG_PROCESS_ERROR(pLink);
    
    pResult = CONTAINING_RECORD(pLink, KMBlock, Link);
Exit0:
    if (pResult)
    {
        assert(uAllocedSize < LONG_MAX);
        KG_InterlockedExchangeAdd((long*)&g_uUsedMemorySize, (long)uAllocedSize);
    }
    return pResult;
}

void  KMemory::RawFree(void* pvAddr, size_t uSize)
{
    int         nBarrelIndex    = GetBarrelIndex(uSize);
    size_t      uFreeSize       = uSize;
    KMBarrel*   pBarrel         = &g_pBarrelTable[nBarrelIndex];
    KMBlock*    pBlock          = (KMBlock*)pvAddr;

    if (nBarrelIndex == -1)
    {
        free(pvAddr);
        goto Exit0;
    }
    
    uFreeSize = pBarrel->uBlockSize;

    pBlock->Link.Next = NULL;
    KG_InterlockedPushEntrySList(&pBarrel->FreeList, &pBlock->Link);

Exit0:
    assert(uFreeSize < LONG_MAX);
    KG_InterlockedExchangeAdd((long*)&g_uUsedMemorySize, -(long)(uFreeSize));
    return;
}

size_t KMemory::GetUsedSize()
{
    return g_uUsedMemorySize;
}

#define  KUSER_BLOCK_MAGIC  0x19810824
#define  KIDLE_BLOCK_MAGIC  0x42801891

void* KMemory::Alloc(size_t uSize)
{
    void*             pvResult    = NULL;
    size_t            uAllockSize = sizeof(KUserBlockHeader) + uSize;
    KUserBlockHeader* pBlock      = NULL;

    pBlock = (KUserBlockHeader*)RawAlloc(uAllockSize);
    if (pBlock)
    {
        pBlock->nMagic = KUSER_BLOCK_MAGIC;
        pBlock->uSize  = uAllockSize;

        pvResult       = pBlock->byUserData;
    }

    return pvResult;
}

void  KMemory::Free(void* pvAddr)
{
    KUserBlockHeader* pBlock = CONTAINING_RECORD(pvAddr, KUserBlockHeader, byUserData);

    assert(pBlock->nMagic == KUSER_BLOCK_MAGIC);

    pBlock->nMagic = KIDLE_BLOCK_MAGIC;

    RawFree(pBlock, pBlock->uSize);
}

BOOL KMemory::Save()
{
    BOOL    bResult = false;
    FILE*   pFile   = NULL;

    KG_PROCESS_ERROR(g_pBarrelTable);

    pFile = fopen(g_szFileName, "w");
    KG_PROCESS_ERROR(pFile);

    fprintf(pFile, "version=%d\n", MEMORY_POOL_VERSION);

    for (int nBarrelIndex = 0; nBarrelIndex < TOTAL_BARREL_COUNT; nBarrelIndex++)
    {
        KMBarrel* pBarrel       = &g_pBarrelTable[nBarrelIndex];
        int       nAllocCount   = 0;

        if (pBarrel->nLastAlloc == 0)
        {
            nAllocCount = pBarrel->nTotalAlloc;
        }
        else
        {
            nAllocCount = (pBarrel->nTotalAlloc * 1 + pBarrel->nLastAlloc * 3) / 4;
        }

        if (nAllocCount < 1)
        {
            continue;
        }

        fprintf(pFile, "S%u=%d\n", pBarrel->uBlockSize, nAllocCount);
    }

    bResult = true;
Exit0:
    if (pFile)
    {
        fclose(pFile);
        pFile = NULL;
    }
    return bResult;
}

BOOL KMemory::Load()
{
    BOOL    bResult     = false;
    int     nRetCode    = false;
    int     nVersion    = 0;
    FILE*   pFile       = NULL;

    pFile = fopen(g_szFileName, "r");
    KG_PROCESS_ERROR(pFile);

    nRetCode = fscanf(pFile, "version=%d\n", &nVersion);
    KG_PROCESS_ERROR(nRetCode != EOF);

    KG_PROCESS_ERROR(nVersion == MEMORY_POOL_VERSION);

    while (true)
    {
        int       nBarrelIndex  = 0;
        size_t    uBlockSize    = 0;
        int       nTotalAlloc   = 0;

        nRetCode = fscanf(pFile, "S%u=%d\n", &uBlockSize, &nTotalAlloc);
        if (nRetCode == EOF)
        {
            break;
        }

        nBarrelIndex = GetBarrelIndex(uBlockSize);
        if (nBarrelIndex == -1)
        {
            continue;
        }

        if (nTotalAlloc < 1 || nTotalAlloc > INT_MAX / 2)
        {
            continue;
        }

        g_pBarrelTable[nBarrelIndex].nLastAlloc = nTotalAlloc;
    }

    bResult = true;
Exit0:
    if (pFile)
    {
        fclose(pFile);
        pFile = NULL;
    }
    return bResult;
}
