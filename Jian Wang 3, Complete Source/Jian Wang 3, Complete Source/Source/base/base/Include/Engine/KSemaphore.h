//////////////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   KSemaphore.h
//  Version     :   1.0
//  Creater     :   Freeway Chen, ZhaoChunFeng
//  Date        :   2005-3-8 21:46:44
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////

#ifndef KSEMAPHORE_H
#define KSEMAPHORE_H    1
//---------------------------------------------------------------------------

#ifdef WIN32

#include "KWin32.h"

class ENGINE_API KSemaphore
{
public:
    int Init(unsigned uInitCount)  { m_hSemaphore = CreateSemaphore(NULL, (long)uInitCount, 0x7fffffff, NULL);  return (m_hSemaphore != NULL);  }
    void UnInit()                    { if (m_hSemaphore) { CloseHandle(m_hSemaphore); m_hSemaphore = NULL;}   }
    int Post()                       { return ReleaseSemaphore(m_hSemaphore, 1, NULL); }
    int Wait()                       { DWORD dwRetCode = WaitForSingleObject(m_hSemaphore, INFINITE); return (dwRetCode == WAIT_OBJECT_0); } 

private:
    HANDLE m_hSemaphore;
};

#else   // POSIX

#include <semaphore.h>

class KSemaphore
{
public:
    int Init(unsigned uInitCount) 
    { 
        int nRetCode = sem_init(&m_Semaphore, 0, uInitCount); 
        return (nRetCode == 0);
    }
    void UnInit()                   { sem_destroy(&m_Semaphore);  }
    int Post()      { int nRetCode = sem_post(&m_Semaphore);    return (nRetCode == 0); }
    int Wait();

private:
    sem_t m_Semaphore;
};

#endif

#endif
