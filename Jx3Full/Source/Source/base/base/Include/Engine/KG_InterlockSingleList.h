//////////////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   KG_InterlockSingleList.h
//  Version     :   1.0
//  Creater     :   
//  Date        :   2004-10-12 9:57:24
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////

#ifndef _KG_INTERLOCKSINGLELIST_H_
#define _KG_INTERLOCKSINGLELIST_H_  1

#include <stdlib.h>
#include "KG_InterlockSingleList_DEF.h"

//========================= 函数原型 ==========================================

//初始化单向队列头结构
void KG_InitializeSListHead(PKG_SLIST_HEADER ListHead);
//清空单向队列
PKG_SLIST_ENTRY KG_InterlockedFlushSList(PKG_SLIST_HEADER ListHead);

//push一个结点ListEntry是要push的结点中的next指针变量的地址，返回值是push之前的头指针
PKG_SLIST_ENTRY KG_InterlockedPushEntrySList(PKG_SLIST_HEADER ListHead, PKG_SLIST_ENTRY ListEntry);
//pop一个结点，当然，返回的指针并不直接是pop出的节点的地址，而要通过一个宏CONTAINING_RECORD转换一下
PKG_SLIST_ENTRY KG_InterlockedPopEntrySList(PKG_SLIST_HEADER ListHead);


//========================= 实现部分 ==========================================

#if (defined(_MSC_VER) || defined(__ICL))
#include "KG_InterlockSingleList_MSC_x86.h"
#elif defined(__GNUC__)
#include "KG_InterlockSingleList_GNUC_x86.h"
#endif


inline void KG_InitializeSListHead(PKG_SLIST_HEADER ListHead)
{
    if (!ListHead)
        return;

    ListHead->Next.Next = NULL;
    ListHead->Depth = 0;
    ListHead->Sequence = 0;        
}



#endif
