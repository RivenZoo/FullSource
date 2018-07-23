/************************************************************************/
/* A cache uses LRU algorithm, acts as a map container.                 */
/* Copyright: Kingsoft 2007										        */
/* Author	: Jeffrey Chen												*/
/* Note	    : This container is NOT consider to be thread-safe!         */
/* Changelog:                                                           */
/*          2007-12-03                                                  */
/*          Init function add a param to specify a EraseFunc instance.  */
/************************************************************************/

#ifndef _KLRU_CACHE_MAP_H_
#define _KLRU_CACHE_MAP_H_

template<class TKey, class TValue>
struct KDefaultEraseFunc
{
    inline BOOL operator() (const TKey& crKey, TValue& rValue)
    {
        return true;
    };
};

template<class TKey, class TValue>
struct KDefaultUnInitEraseFunc
{
    inline BOOL operator() (const TKey& crKey, TValue& rValue)
    {
        rValue.UnInit();
        return true;
    };
};

template<class TKey, class TValue>
struct KBuffFreeAttribEraseFunc
{
    inline BOOL operator() (const TKey& crKey, TValue& rValue)
    {
        FREE_ATTRIB_LIST(rValue.pAttribList);
        FREE_ATTRIB_LIST(rValue.pEndTimeAttrib);
        rValue.dwSerialNumber = 0;
        return true;
    };
};

template<class TKey, class TValue>
struct KBuffFreeAttribEraseFunc2
{
    inline BOOL operator() (const TKey& crKey, TValue& rValue)
    {
        FREE_ATTRIB_LIST(rValue.m_pBeginAttribList);
        FREE_ATTRIB_LIST(rValue.m_pActiveAttribList);
        FREE_ATTRIB_LIST(rValue.m_pEndTimeAttribList);
        rValue.m_dwSerialNumber = 0;
        return true;
    };
};

// LRU Cache class ///////////////////////////////////////////////////////

template<
    class TKey, 
    class TValue, 
    class TEraseFunc = KDefaultEraseFunc<TKey, TValue> 
>
class KLRUCahceMap
{
public:
    KLRUCahceMap();
    ~KLRUCahceMap();

    BOOL                Init(int nCapacity = 1024, int nRecycleSize = 1);
    BOOL                Init(TEraseFunc& rEraseFunc, int nCapacity = 1024, int nRecycleSize = 1);
    void                UnInit();

    TValue*             Find(const TKey& crKey);
    TValue*             Insert(const TKey& crKey);
    BOOL                Erase(const TKey& crKey);
    BOOL                Clear();
    size_t              Size();

    template<class TFunc>
    void                Traverse(TFunc& rFunc);

private:    // Data struct
    typedef std::map<TKey, void*>           KCACHE_MAP;
    typedef typename KCACHE_MAP::iterator   KCACHE_MAP_IT;

    struct KCACHE_NODE 
    {
        TValue          ValueObj;
        KCACHE_MAP_IT   it;
        KCACHE_NODE*    pPrevLRUNode;
        KCACHE_NODE*    pNextLRUNode;
    };

private:    // Internal function
    BOOL                _Erase(KCACHE_MAP_IT it);
    int                 _Recycle();

private:    // Member variable
    int                 m_nCapacity;
    int                 m_nRecycleSize;

    KCACHE_MAP          m_CacheMap;

    KCACHE_NODE         m_LRUListHead;
    KCACHE_NODE         m_LRUListEnd;
    KCACHE_NODE         m_LRUFreeList;
    KCACHE_NODE*        m_pPreAllocatedNodes;

    TEraseFunc          m_EraseFunc;
};

// -----------------------------------------------------------------------

#define KLRU_LIST_INSERT_NODE(pPos, pNode)                              \
    do                                                                  \
    {                                                                   \
        (pNode)->pPrevLRUNode = (pPos);                                 \
        (pNode)->pNextLRUNode = (pPos)->pNextLRUNode;                   \
                                                                        \
        if ((pPos)->pNextLRUNode)                                       \
            (pPos)->pNextLRUNode->pPrevLRUNode = (pNode);               \
        (pPos)->pNextLRUNode = (pNode);                                 \
    } while(false)

#define KLRU_LIST_REMOVE_NODE(pNode)                                    \
    do                                                                  \
    {                                                                   \
        (pNode)->pPrevLRUNode->pNextLRUNode = (pNode)->pNextLRUNode;    \
        if ((pNode)->pNextLRUNode)                                      \
            (pNode)->pNextLRUNode->pPrevLRUNode = (pNode)->pPrevLRUNode;\
                                                                        \
        (pNode)->pPrevLRUNode = NULL;                                   \
        (pNode)->pNextLRUNode = NULL;                                   \
    } while(false)


template<class TKey, class TValue, class TEraseFunc>
KLRUCahceMap<TKey, TValue, TEraseFunc>::KLRUCahceMap()
{
    m_nCapacity                 = 0;
    m_nRecycleSize              = 0;
    m_pPreAllocatedNodes        = NULL;
    m_LRUListHead.pPrevLRUNode  = NULL;
    m_LRUListHead.pNextLRUNode  = &m_LRUListEnd;
    m_LRUListEnd.pPrevLRUNode   = &m_LRUListHead;
    m_LRUListEnd.pNextLRUNode   = NULL;
}

template<class TKey, class TValue, class TEraseFunc>
KLRUCahceMap<TKey, TValue, TEraseFunc>::~KLRUCahceMap()
{
    ASSERT(!m_pPreAllocatedNodes);
}

template<class TKey, class TValue, class TEraseFunc>
BOOL KLRUCahceMap<TKey, TValue, TEraseFunc>::Init(int nCapacity, int nRecycleSize)
{
    BOOL            bResult     = false;
    KCACHE_NODE*    pFreeNodes  = NULL;

    KG_PROCESS_ERROR(nCapacity    > 0);
    KG_PROCESS_ERROR(nRecycleSize > 0);

    m_nCapacity                 = nCapacity;
    m_nRecycleSize              = nRecycleSize; 

    m_LRUListHead.pPrevLRUNode  = NULL;
    m_LRUListHead.pNextLRUNode  = &m_LRUListEnd;
    m_LRUListEnd.pPrevLRUNode   = &m_LRUListHead;
    m_LRUListEnd.pNextLRUNode   = NULL;

    m_pPreAllocatedNodes = new KCACHE_NODE[nCapacity];
    KG_PROCESS_ERROR(m_pPreAllocatedNodes);

    m_pPreAllocatedNodes[0].pPrevLRUNode = &m_LRUFreeList;
    m_pPreAllocatedNodes[0].pNextLRUNode = NULL;
    for (int i = 1; i < nCapacity; i++)
    {
        m_pPreAllocatedNodes[i].pPrevLRUNode = &m_pPreAllocatedNodes[i - 1];
        m_pPreAllocatedNodes[i].pNextLRUNode = NULL;

        m_pPreAllocatedNodes[i - 1].pNextLRUNode = &m_pPreAllocatedNodes[i];
    }

    m_LRUFreeList.pPrevLRUNode = NULL;
    m_LRUFreeList.pNextLRUNode = m_pPreAllocatedNodes;

    bResult = true;
Exit0:
    if (!bResult)
    {
        KG_DELETE_ARRAY(m_pPreAllocatedNodes);
    }
    return bResult;
}

template<class TKey, class TValue, class TEraseFunc>
BOOL KLRUCahceMap<TKey, TValue, TEraseFunc>::Init(TEraseFunc& rEraseFunc, int nCapacity, int nRecycleSize)
{
    m_EraseFunc = rEraseFunc;

    return Init(nCapacity, nRecycleSize);
}

template<class TKey, class TValue, class TEraseFunc>
void KLRUCahceMap<TKey, TValue, TEraseFunc>::UnInit()
{
    Clear();

    m_nCapacity                 = 0;
    m_nRecycleSize              = 0;

    m_LRUListHead.pPrevLRUNode  = NULL;
    m_LRUListHead.pNextLRUNode  = &m_LRUListEnd;
    m_LRUListEnd.pPrevLRUNode   = &m_LRUListHead;
    m_LRUListEnd.pNextLRUNode   = NULL;

    m_LRUFreeList.pNextLRUNode  = NULL;

    KG_DELETE_ARRAY(m_pPreAllocatedNodes);

//Exit0:
    return;
}

template<class TKey, class TValue, class TEraseFunc>
TValue* KLRUCahceMap<TKey, TValue, TEraseFunc>::Find(const TKey& crKey)
{
    TValue*         pResult = NULL;
    KCACHE_NODE*    pNode   = NULL;
    KCACHE_MAP_IT   it;

    it = m_CacheMap.find(crKey);
    if (it != m_CacheMap.end())
    {
        pNode = (KCACHE_NODE*)(it->second);
        ASSERT(pNode);

        KLRU_LIST_REMOVE_NODE(pNode);
        KLRU_LIST_INSERT_NODE(&m_LRUListHead, pNode);

        pResult = &(pNode->ValueObj);
    }

    return pResult;
}

template<class TKey, class TValue, class TEraseFunc>
TValue* KLRUCahceMap<TKey, TValue, TEraseFunc>::Insert(const TKey& crKey)
{
    TValue*                         pResult         = NULL;
    KCACHE_NODE*                    pNode           = NULL;
    int                             nLeftCapacity   = 0;
    std::pair<KCACHE_MAP_IT, bool>  RetPair;

    nLeftCapacity = m_nCapacity - (int)m_CacheMap.size();
    if (nLeftCapacity < 1)
    {
        nLeftCapacity += _Recycle();
    }
    KGLOG_PROCESS_ERROR(nLeftCapacity > 0);

    pNode = m_LRUFreeList.pNextLRUNode;
    ASSERT(pNode);
    KLRU_LIST_REMOVE_NODE(pNode);

    RetPair = m_CacheMap.insert(std::make_pair(crKey, (void*)pNode));
    KGLOG_PROCESS_ERROR(RetPair.second);

    pNode->it = RetPair.first;

    pResult = &(pNode->ValueObj);
    KLRU_LIST_INSERT_NODE(&m_LRUListHead, pNode);
    pNode = NULL;

Exit0:
    if (pNode)
    {
        KLRU_LIST_INSERT_NODE(&m_LRUFreeList, pNode);
        pNode = NULL;
    }
    return pResult;
}

template<class TKey, class TValue, class TEraseFunc>
BOOL KLRUCahceMap<TKey, TValue, TEraseFunc>::Erase(const TKey& crKey)
{
    BOOL            bResult     = false;
    BOOL            bRetCode    = false;
    KCACHE_MAP_IT   it;

    it = m_CacheMap.find(crKey);
    KG_PROCESS_ERROR(it != m_CacheMap.end());

    bRetCode = _Erase(it);
    KG_PROCESS_ERROR(bRetCode);

    bResult = true;
Exit0:
    return bResult;
}

template<class TKey, class TValue, class TEraseFunc>
BOOL KLRUCahceMap<TKey, TValue, TEraseFunc>::Clear()
{
    BOOL            bResult     = false;
    BOOL            bRetCode    = false;
    KCACHE_NODE*    pNode       = NULL;
    size_t          uSize       = 0;
    size_t          uErase      = 0;
    
    uSize = m_CacheMap.size();

    for (pNode = m_LRUListHead.pNextLRUNode; pNode != &m_LRUListEnd; NULL)
    {
        KCACHE_NODE* pDelNode = pNode;

        pNode = pNode->pNextLRUNode;

        bRetCode = _Erase(pDelNode->it);
        if (bRetCode)
        {
            uErase++;
        }
    }

    KGLOG_PROCESS_ERROR(uSize == uErase);

    bResult = true;
Exit0:
    return bResult;
}

template<class TKey, class TValue, class TEraseFunc>
size_t KLRUCahceMap<TKey, TValue, TEraseFunc>::Size()
{
    return m_CacheMap.size();
}

template<class TKey, class TValue, class TEraseFunc>
template<class TFunc>
void KLRUCahceMap<TKey, TValue, TEraseFunc>::Traverse(TFunc& rFunc)
{
    BOOL            bRetCode    = false;
    KCACHE_NODE*    pNode       = NULL;
    KCACHE_MAP_IT   it;
    KCACHE_MAP_IT   itEnd;

    itEnd = m_CacheMap.end();
    for (it = m_CacheMap.begin(); it != itEnd; ++it)
    {
        pNode = (KCACHE_NODE*)(it->second);
        ASSERT(pNode);

        bRetCode = rFunc(it->first, pNode->ValueObj);
        KG_PROCESS_ERROR(bRetCode);
    }

Exit0:
    return;
}

template<class TKey, class TValue, class TEraseFunc>
BOOL KLRUCahceMap<TKey, TValue, TEraseFunc>::_Erase(KCACHE_MAP_IT it)
{
    BOOL            bResult     = false;
    BOOL            bRetCode    = false;
    KCACHE_NODE*    pNode       = NULL;

    pNode = (KCACHE_NODE*)it->second;
    ASSERT(pNode);

    bRetCode = m_EraseFunc(it->first, pNode->ValueObj);
    KG_PROCESS_ERROR(bRetCode);

    KLRU_LIST_REMOVE_NODE(pNode);
    KLRU_LIST_INSERT_NODE(&m_LRUFreeList, pNode);
    
    m_CacheMap.erase(it);

    bResult = true;
Exit0:
    return bResult;
}

template<class TKey, class TValue, class TEraseFunc>
int KLRUCahceMap<TKey, TValue, TEraseFunc>::_Recycle()
{
    int     nCount      = 0;
    BOOL    bRetCode    = false;

    while (nCount < m_nRecycleSize)
    {
        ASSERT(m_LRUListEnd.pPrevLRUNode);
        KG_PROCESS_ERROR(m_LRUListEnd.pPrevLRUNode != &m_LRUListHead);

        bRetCode = _Erase(m_LRUListEnd.pPrevLRUNode->it);
        KGLOG_PROCESS_ERROR(bRetCode);

        nCount++;
    }

Exit0:
    return nCount;
}

//////////////////////////////////////////////////////////////////////////

#endif
