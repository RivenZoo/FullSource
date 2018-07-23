#ifndef _KTONG_REPERTORY_CACHE_H_
#define _KTONG_REPERTORY_CACHE_H_ 

#include "KTongDef.h"

class KItem;

struct KTongRepertoryCachePage
{
    int     m_nLastUpdateCounter;
    BOOL    m_bGetRight;
    BOOL    m_bPutRight;
    KItem*  m_pItems[TONG_REPERTORY_PAGE_CAPACITY];
};

class KTongRepertoryCache
{
public:
    KTongRepertoryCachePage m_Pages[TONG_REPERTORY_PAGE_NUM];
    int                     m_nMaxPageNum;
    
public:
    BOOL Init();
    void UnInit();
    void Reset();

    BOOL TakeItemToPos(int nPageIndex, int nPos, int nBoxIndex, int nBoxPos);
    BOOL TakeItem(int nPageIndex, int nPos);

    BOOL PutItemToPos(int nBoxIndex, int nBoxPos, int nPageIndex, int nPagePos);
    BOOL PutItem(int nBoxIndex, int nBoxPos, int nPageIndex);

    BOOL ExchangeItemPos(int nSrcPageIndex, int nSrcPos, int nDstPageIndex, int nDstPos);

    BOOL StackItem(int nPageIndex, int nPagePos, int nBoxIndex, int  nBoxPos, int nStackNum);

private:
    BOOL CheckTakePageRight(int nPageIdex);
    BOOL CheckPutPageRight(int nPageIndex);
};

#endif // _KTONG_REPERTORY_CACHE_H_
