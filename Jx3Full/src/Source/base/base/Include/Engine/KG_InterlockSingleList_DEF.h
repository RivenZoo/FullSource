//////////////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   KG_InterlockSingleList_DEF.h
//  Version     :   1.0
//  Creater     :   
//  Date        :   2004-10-12 9:57:24
//  Comment     :   define file
//
//////////////////////////////////////////////////////////////////////////////////////

#ifndef _KG_INTERLOCKSINGLELIST_DEF_H_
#define _KG_INTERLOCKSINGLELIST_DEF_H_  1

#include <stddef.h>

typedef unsigned long long ULONGLONG;
typedef long long LONGLONG;
typedef unsigned short WORD;

#ifndef CONTAINING_RECORD
#define CONTAINING_RECORD(address, type, field) ((type *)( \
    (char *)(address) - \
    (ptrdiff_t)(&((type *)0)->field)))
#endif

typedef struct _KG_SLIST_ENTRY {
    struct _KG_SLIST_ENTRY *Next;
} KG_SLIST_ENTRY, *PKG_SLIST_ENTRY;

typedef union _KG_SLIST_HEADER 
{
    ULONGLONG Alignment;
    struct {
        KG_SLIST_ENTRY Next;
        WORD   Depth;
        WORD   Sequence;
    };
} KG_SLIST_HEADER, *PKG_SLIST_HEADER;




#endif
