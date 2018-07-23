//////////////////////////////////////////////////////////////////////////////////////
//
//  Filename    :   KG_Memory.h
//  Version     :   1.0
//  Author      :   Freeway Chen, ZhaoChunFeng, Chen Jie
//  Date        :   2004-10-22 17:38:19
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////

#ifndef _KG_MEMORY_H_
#define _KG_MEMORY_H_    1

#include <new>
#include <set>

#include "KGPublic.h"
#include "KSUnknown.h"

#include "Engine/KGLog.h"
#include "Engine/KMutex.h"
#include "Engine/KG_InterlockSingleList.h"
#include "Engine/KG_InterlockedVariable.h"

using namespace std;


extern const GUID IID_IKG_Buffer;   // {9B459A98-CB94-4f06-81EF-226CAE16C594}

struct IKG_Buffer : IUnknown
{
public:
    virtual void    *GetData() = 0;
    virtual unsigned GetSize() = 0;
    virtual unsigned GetReserveSize() = 0;
}; 

int KG_MemoryInit(void *pvContext); 
int KG_MemoryUnInit(void *pvContext); 
IKG_Buffer *KG_MemoryCreateBuffer(unsigned uSize);


extern const GUID IID_IKG_Buffer_ReSize; // {3E8AE0B1-724D-42d7-B187-5AC590AD2501}

struct IKG_Buffer_ReSize : IUnknown
{
    virtual int ResetSize() = 0;
    virtual int SetSmallerSize(unsigned uNewSize) = 0;
};

#pragma pack(1)
typedef struct _KG_MemoryBlock
{
    KG_SLIST_ENTRY  m_Next;
    unsigned        m_uSize;
    unsigned char   m_Data[1];
} KG_MemoryBlock;
#pragma pack()

typedef struct _KG_MEMORY_LIST_STRUCT
{
    unsigned uBlockMaxSize;
    KG_SLIST_HEADER List;
} KG_MEMORY_LIST_STRUCT;


class KG_Memory_Debug
{
public:
    int AddBlock(KG_MemoryBlock *pBlock);
    int RemoveBlock(KG_MemoryBlock *pBlock);
    int CheckLeak();

private:
    typedef set<KG_MemoryBlock *> KG_MemoryBlockDebugSet;

    KG_MemoryBlockDebugSet m_MemoryBlocks;

    KMutex                 m_Lock;
};

//////////////////////////////////////////////////////////////////////////
// _KG_Memory_Internal function set
//////////////////////////////////////////////////////////////////////////
int _KG_Memory_Internal_Init(
    unsigned uMemoryListArrayCount,   KG_MEMORY_LIST_STRUCT MemoryListArray[], 
    unsigned uSizeArrayCount,         unsigned uSizeArray[], 
    void    *pvContext
);

int _KG_Memory_Internal_UnInit(
    unsigned uMemoryListArrayCount,   KG_MEMORY_LIST_STRUCT MemoryListArray[],
    void *pvContext
);

KG_MemoryBlock *_KG_Memory_Internal_Alloc(
    unsigned uMemoryListArrayCount,   KG_MEMORY_LIST_STRUCT MemoryListArray[],
    unsigned uSize
);

int _KG_Memory_Internal_Free(
    unsigned uMemoryListArrayCount,   KG_MEMORY_LIST_STRUCT MemoryListArray[],
    KG_MemoryBlock *pBlock
);


//////////////////////////////////////////////////////////////////////////
// template class KG_Memory
//////////////////////////////////////////////////////////////////////////
template <unsigned _uSizeArrayCount, unsigned _uSizeArray[]>
class KG_Memory
{
public:
    void *Alloc(unsigned uSize);
    int   Free(void *pvBlock);

    KG_Memory();
    ~KG_Memory();

private:
    volatile long   m_lAllocCount;
    volatile long   m_lFreeCount;

    KG_MEMORY_LIST_STRUCT   m_MemoryListArray[_uSizeArrayCount];
#ifdef MEMORY_DEBUG
    KG_Memory_Debug         m_Memory_Debug;
#endif
};

template <unsigned _uSizeArrayCount, unsigned _uSizeArray[]>
KG_Memory<_uSizeArrayCount, _uSizeArray>::KG_Memory(void)
{
    int nRetCode = false;

    ASSERT(0    != _uSizeArrayCount);
    ASSERT(NULL != _uSizeArray);

    m_lAllocCount = 0;
    m_lFreeCount  = 0;

    nRetCode = _KG_Memory_Internal_Init(
        _uSizeArrayCount,   m_MemoryListArray, 
        _uSizeArrayCount,   _uSizeArray, 
        NULL
    );
    ASSERT(nRetCode);
}

template <unsigned _uSizeArrayCount, unsigned _uSizeArray[]>
KG_Memory<_uSizeArrayCount, _uSizeArray>::~KG_Memory(void)
{
    int nRetCode = false;

    nRetCode = _KG_Memory_Internal_UnInit(_uSizeArrayCount, m_MemoryListArray, NULL);
    ASSERT(nRetCode);

    #ifdef MEMORY_DEBUG
    nRetCode = m_Memory_Debug.CheckLeak();
    ASSERT(nRetCode);
    #endif
    
    if (m_lAllocCount != m_lFreeCount)
    {
        ASSERT(!"Memory system : memory leak detected!");
        KGLogPrintf(
            KGLOG_ERR, 
            "Bad use of memory system : memory leak detected, leak block [%d]", 
            m_lAllocCount - m_lFreeCount
        );
    }
}

template <unsigned _uSizeArrayCount, unsigned _uSizeArray[]>
void *KG_Memory<_uSizeArrayCount, _uSizeArray>::Alloc(unsigned uSize)
{
    void *pvResult  = NULL;
    int nRetCode    = false;
    KG_MemoryBlock *pBlock = NULL;

    KG_PROCESS_ERROR(uSize > 0);

    pBlock = _KG_Memory_Internal_Alloc(_uSizeArrayCount, m_MemoryListArray, uSize);
    KG_PROCESS_ERROR(pBlock);

    KG_InterlockedIncrement((long *)&m_lAllocCount);

    #ifdef MEMORY_DEBUG
    nRetCode = m_Memory_Debug.AddBlock(pBlock);
    ASSERT(nRetCode);
    #endif

    pvResult = (void *)pBlock->m_Data;

Exit0:
    return pvResult;
}

template <unsigned _uSizeArrayCount, unsigned _uSizeArray[]>
int KG_Memory<_uSizeArrayCount, _uSizeArray>::Free(void *pvBufer)
{
    int nResult  = false;
    int nRetCode = false;
    KG_MemoryBlock *pBlock = NULL;

    KG_PROCESS_ERROR(pvBufer);

    pBlock = CONTAINING_RECORD(pvBufer, KG_MemoryBlock, m_Data);
    ASSERT(pBlock);

    nRetCode = _KG_Memory_Internal_Free(
        _uSizeArrayCount, m_MemoryListArray,
        pBlock
    );
    KG_PROCESS_ERROR(nRetCode);

    KG_InterlockedIncrement((long *)&m_lFreeCount);

    #ifdef MEMORY_DEBUG
    nRetCode = m_Memory_Debug.RemoveBlock(pBlock);
    ASSERT(nRetCode);
    #endif

    nResult = true;
Exit0:
    return nResult;
}

#endif
