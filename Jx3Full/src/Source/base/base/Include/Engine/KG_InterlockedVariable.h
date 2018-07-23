//////////////////////////////////////////////////////////////////////////////////////
//
//  FileName    : KG_InterlockedVariable.h
//  Version     : 1.0
//  Creater     : Wu Caizhong
//  Create Date : 2004-12-17 14:52:32
//  Comment     : 
//
//////////////////////////////////////////////////////////////////////////////////////

#ifndef _INCLUDE_KG_INTERLOCKEDVARIABLE_H_
#define _INCLUDE_KG_INTERLOCKEDVARIABLE_H_

#ifdef WIN32

#include <windows.h>
#define KG_InterlockedExchangeAdd   InterlockedExchangeAdd
#define KG_InterlockedIncrement InterlockedIncrement
#define KG_InterlockedDecrement InterlockedDecrement

#else 

////////////////////////////////////////////////////////////////////////////////////////////////////
// @berief : performs an atomic addition of a increment value to a addend variable. The function 
//           prevents more than one thread from using the same variable simultaneously.
// @param pValue    : [in][out] Pointer to the variable to be incremented
//        lAddValue : [in]      Value to be added to the variable pointed to by the pValue parameter
// @return : The function returns the initial value of the plValue parameter.
// @remark :The variable pointed to by the parameter must be aligned on a 32-bit boundary; 
//          otherwise, this function will fail on multiprocessor x86 systems and any non-x86 systems.
// Last modify by Freeway Chen, 2008-6-15 11:23:00
inline long KG_InterlockedExchangeAdd(long *plValue, long lAddValue)
{
    long lResult;
    __asm__ __volatile__
    (
        "lock xaddl %%eax, (%1)\n"
        :    
            "=a"(lResult)
        : 
            "c"(plValue), "a"(lAddValue)
        :
            "memory"			
    );
    return lResult;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// @berief : increments (increases by one) the value of the specified 32-bit variable, The function 
//           prevents more than one thread from using the same variable simultaneously
// @param pValue : [in][out] Pointer to the variable to be incremented
// @return : the resulting incremented value.
// @remark :The variable pointed to by the parameter must be aligned on a 32-bit boundary; 
//          otherwise, this function will fail on multiprocessor x86 systems and any non-x86 systems.
// Last modify by Wu Caizhong, 2005-02-03 21:54:34
inline long KG_InterlockedIncrement(long *plValue)
{
    long lResult;
    __asm__ __volatile__
    (
        "movl $0x01, %%eax\n"    
        "lock xaddl %%eax, (%1)\n"
        "incl %%eax\n"
        :    
            "=a"(lResult)
        : 
            "c"(plValue)
        :
            "memory"			
    );
    return lResult;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// @berief : decrements (decreases by one) the value of the specified 32-bit variable, The function 
//           prevents more than one thread from using the same variable simultaneously
// @param pValue : [in][out] Pointer to the variable to be decremented
// @return : the resulting decremented value.
// @remark :The variable pointed to by the parameter must be aligned on a 32-bit boundary; 
//          otherwise, this function will fail on multiprocessor x86 systems and any non-x86 systems.
// Last modify by Wu Caizhong, 2005-02-03 21:54:29
inline long KG_InterlockedDecrement(long *plValue)
{
    long lResult;
    __asm__ __volatile__
    (
        "movl $0xffffffff, %%eax\n"    
        "lock xaddl %%eax, (%1)\n"
        "decl %%eax\n"
        :    
            "=a"(lResult)
        : 
            "c"(plValue)
        :
            "memory"			
    );
    return lResult;
}
#endif // WIN32

#endif //_INCLUDE_KG_INTERLOCKEDVARIABLE_H_
