//////////////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   KG_InterlockSingleList_MSC_x86.h
//  Version     :   1.0
//  Creater     :   
//  Date        :   2004-10-12 9:57:24
//  Comment     :   Microsoft Visual C++ Implement for x86 CPU
//
//////////////////////////////////////////////////////////////////////////////////////

#ifndef _KG_INTERLOCKSINGLELIST_MSC_X86_H_
#define _KG_INTERLOCKSINGLELIST_MSC_X86_H_  1

#include "KG_InterlockSingleList_DEF.h"


__declspec(naked) 
inline void *__fastcall __KG_InterlockedPopEntrySList(PKG_SLIST_HEADER ListHead) 
{
    __asm push    ebx
    __asm push    ebp
    __asm mov     ebp, ecx                    //__fastcall方式下，入口参数放在ecx(edx...)中的！
    __asm mov     edx, [ebp] + 4               //KG_SLIST_HEADER结构中的后面两个WORD参数一起放到edx里面
    __asm mov     eax, [ebp] + 0               //这个是KG_SLIST_HEADER结构中的Next指针
Epop10: 
    __asm or      eax, eax         
    __asm jz      short Epop20                //如果链表为空，就返回空
    __asm mov     ecx, edx
    __asm add     ecx, 0FFFFH                 //相当于将低16位减1，高16位加1（因为前面的进位）
    __asm mov     ebx, [eax] 
    __asm lock cmpxchg8b qword ptr [ebp]     
    //lock指令锁住总线，保证这个指令操作过程中该地址不会被修改
    //ebp所指向的64位操作数，也就是我们的头结构地址，而EDX:EAX构成的数值其实也是这个结构，所以一般他们都是相等的！
    //如果不等（那说明上面的几条指令的执行过程中，头结构的内容被其他的线程修改了），该指令会将头结构重新读到edx:eax
    //如果相等，会将ecx:ebx构成的64位操作数（其实就是pop后的新的头结构内容）内容放到我们的头结构中，从而实现了头结
    //构数据的更新
    __asm jnz     short Epop10    
Epop20: 
    __asm pop     ebp               
    __asm pop     ebx 

    __asm ret
}

__declspec(naked)
inline void *__fastcall __KG_InterlockedPushEntrySList(PKG_SLIST_HEADER ListHead, void* ListEntry)
{
    __asm push    ebx   
    __asm push    ebp   
    __asm mov     ebp, ecx            //__fastcall方式下，入口参数ListHead放在ecx中的,ListEntry放在edx中的
    __asm mov     ebx, edx    
    __asm mov     edx, [ebp] + 4
    __asm mov     eax, [ebp] + 0
Epsh10: 
    __asm mov     [ebx], eax
    __asm mov     ecx, edx  
    __asm add     ecx, 010001H

    __asm lock cmpxchg8b qword ptr [ebp]      

    __asm jnz     short Epsh10 

    __asm pop     ebp                
    __asm pop     ebx                
    __asm ret
}

__declspec(naked) 
inline void *__fastcall __KG_InterlockedFlushSList(PKG_SLIST_HEADER ListHead) 
{
    __asm push    ebx
    __asm push    ebp
    __asm mov     ebp, ecx                    //__fastcall方式下，入口参数放在ecx(edx...)中的！
    __asm xor     ebx, ebx
    __asm mov     edx, [ebp] + 4               //KG_SLIST_HEADER结构中的后面两个WORD参数一起放到edx里面
    __asm mov     eax, [ebp] + 0               //这个是KG_SLIST_HEADER结构中的Next指针
Epop10: 
    __asm or      eax, eax         
    __asm jz      short Epop20                //如果链表为空，就返回空
    __asm mov     ecx, edx
    __asm mov     cx,  bx
    __asm lock cmpxchg8b qword ptr [ebp]     
    __asm jnz     short Epop10    
Epop20: 
    __asm pop     ebp               
    __asm pop     ebx 

    __asm ret
}

inline PKG_SLIST_ENTRY KG_InterlockedFlushSList(PKG_SLIST_HEADER ListHead)
{
    return (PKG_SLIST_ENTRY)__KG_InterlockedFlushSList(ListHead);
}

inline PKG_SLIST_ENTRY KG_InterlockedPopEntrySList(PKG_SLIST_HEADER ListHead) 
{
    return (PKG_SLIST_ENTRY)__KG_InterlockedPopEntrySList(ListHead);
}

inline PKG_SLIST_ENTRY KG_InterlockedPushEntrySList(PKG_SLIST_HEADER ListHead, PKG_SLIST_ENTRY ListEntry)
{
    return (PKG_SLIST_ENTRY)__KG_InterlockedPushEntrySList(ListHead, (void *)ListEntry);
}


#endif
