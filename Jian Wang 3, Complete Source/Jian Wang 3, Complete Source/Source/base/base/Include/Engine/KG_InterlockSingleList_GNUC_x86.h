//////////////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   KG_InterlockSingleList_GNUC_x86.h
//  Version     :   1.0
//  Creater     :   
//  Date        :   2004-10-12 9:57:24
//  Comment     :   GNU C/C++ Implement for x86 CPU
//
//////////////////////////////////////////////////////////////////////////////////////

#ifndef _KG_INTERLOCKSINGLELIST_GNUC_X86_H_
#define _KG_INTERLOCKSINGLELIST_GNUC_X86_H_     1

#include "KG_InterlockSingleList_DEF.h"

inline PKG_SLIST_ENTRY KG_InterlockedPopEntrySList(PKG_SLIST_HEADER ListHead)
{
    PKG_SLIST_ENTRY pvRetValue;

    __asm__ __volatile__(
        "movl   4(%1), %%edx\n"     // get current sequence number
        "movl   (%1),  %%eax\n"     // get current next link

        //
        // If the list is empty, then there is nothing that can be removed.
        //

        "1:\n"
        "or     %%eax, %%eax\n"     // check if list is empty
        "jz     2f\n"               // if z set, list is empty

        "movl   %%edx,   %%ecx\n"   // copy sequence number and depth
        "addl   $0xFFFF, %%ecx\n"   // adjust sequence number and depth

        // N.B. It is possible for the following instruction to fault in the rare
        //      case where the first entry in the list is allocated on another
        //      processor and free between the time the free pointer is read above
        //      and the following instruction. When this happens, the access fault
        //      code continues execution by skipping the following instruction.
        //      This results in the compare failing and the entire operation is
        //      retried.

        "movl   (%%eax), %%ebx\n"   // get address of successor entry

        "lock cmpxchg8b (%1)\n"     // compare and exchange

        "jnz    1b\n"               // if z clear, exchange failed

        // Restore nonvolatile registers and return result.

        "2:\n"
        : 
            "=a"(pvRetValue)
        : 
            "D"(ListHead)
        : 
            "ebx", "ecx", "edx", "memory"
        );

    return pvRetValue;
}

inline PKG_SLIST_ENTRY KG_InterlockedPushEntrySList (
    PKG_SLIST_HEADER ListHead,
    PKG_SLIST_ENTRY ListEntry
    )
{
    PKG_SLIST_ENTRY pvRetValue;

    __asm__ __volatile__(
        "movl   (%1),  %%eax\n"     // get current next link
        "movl   4(%1), %%edx\n"     // get current sequence number
        "1:" 
        "movl   %%eax, (%2)\n"      // set next link in new first entry
        "movl   %%edx, %%ecx\n"     // copy sequence number
        "addl   $0x10001, %%ecx\n"  // increment sequence number and depth

        "lock cmpxchg8b (%1)\n"     // compare and exchange

        "jnz     1b\n"              // if z clear, exchange failed
        : 
            "=a"(pvRetValue)
        : 
            "D"(ListHead), 
            "b"(ListEntry)
        : 
            "ecx", "edx", "memory"
        );

    return pvRetValue;
}

inline PKG_SLIST_ENTRY KG_InterlockedFlushSList(PKG_SLIST_HEADER ListHead)
{
    PKG_SLIST_ENTRY pvRetValue;

    __asm__ __volatile__(
        "xorl   %%ebx, %%ebx\n"
        "movl   4(%1), %%edx\n"     // get current sequence number
        "movl   (%1),  %%eax\n"     // get current next link

        //
        // If the list is empty, then there is nothing that can be removed.
        //

        "1:\n"
        "or     %%eax, %%eax\n"     // check if list is empty
        "jz     2f\n"               // if z set, list is empty

        "movl   %%edx,   %%ecx\n"   // copy sequence number and depth
        "movw   %%bx,    %%cx\n"    // set depth = 0

        "lock cmpxchg8b (%1)\n"     // compare and exchange

        "jnz    1b\n"               // if z clear, exchange failed

        // Restore nonvolatile registers and return result.

        "2:\n"
        : 
            "=a"(pvRetValue)
        : 
            "D"(ListHead)
        : 
            "ebx", "ecx", "edx", "memory"
        );

    return pvRetValue;
}


#endif
