//////////////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   KGCRT.h
//  Version     :   1.0
//  Creater     :   Freeway Chen
//  Date        :   2004-12-23 9:28:46
//  Comment     :   Kingsoft Game C Runtime
//
//////////////////////////////////////////////////////////////////////////////////////

#ifndef _KGCRT_H
#define _KGCRT_H    1

#include "EngineBase.h"

#if (defined(_MSC_VER) || defined(__ICL))
#include <direct.h>
#include <io.h>
#else   // if linux
#endif

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if (defined(_MSC_VER) || defined(__ICL))
#define snprintf  _snprintf
#define vsnprintf _vsnprintf
#endif 

//#if (defined(_MSC_VER) || defined(__ICL))
//#define fileno _fileno
//#endif

inline unsigned KG_Rand()
{
    static unsigned s_uHoldRand = (unsigned)time(NULL);
    
    s_uHoldRand = s_uHoldRand * 214013L + 2531011L;

    return s_uHoldRand;
}


#if (defined(_MSC_VER) || defined(__ICL))
#define KG_mkdir mkdir
#else   // if linux
inline int KG_mkdir(const char cszDir[])
{
    return mkdir(cszDir, 0777);
}
#endif

#define KG_rmdir rmdir
#define KG_chdir chdir

#if (defined(_MSC_VER) || defined(__ICL))

inline struct tm *localtime_r(const time_t *timep, struct tm *result)
{
    struct tm *ptm = localtime(timep);
    if (
        (result) &&
        (ptm)
    )
    {
        *result = *ptm;
    }

    return ptm;
};
#endif

#ifndef PATH_MAX
#define PATH_MAX    1024
#endif

#ifdef __GNUC__
// return true or false 
int kbhit();
#endif // __GNUC__, for "kbhit()" implementation

#endif // _KGCRT_H
