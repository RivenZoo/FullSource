//////////////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   KSemaphore.cpp
//  Version     :   1.0
//  Creater     :   Freeway Chen, ZhaoChunFeng
//  Date        :   2005-3-8 21:46:24
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////

#include "Precompile.h"
//#include "KDebug.h"
#include "KSemaphore.h"

// linux
#ifdef __GNUC__

#include <errno.h>

int KSemaphore::Wait()      
 { 
     int nRetCode = -1;

     while (true) 
     {
        nRetCode = sem_wait(&m_Semaphore);    
        if ((nRetCode == -1) && (errno == EINTR))
            continue;
        break;
     }
     return (nRetCode == 0); 
 }

#endif