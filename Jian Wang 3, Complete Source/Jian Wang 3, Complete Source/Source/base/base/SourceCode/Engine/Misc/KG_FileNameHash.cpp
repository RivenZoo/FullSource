#include "Precompile.h"
#include "KGPublic.h"
#include "KG_FileNameHash.h"

inline unsigned int Time33Hash(const wchar_t *pcwszString)
{
    unsigned int uHash = 0;
    while (*pcwszString)
        uHash = (uHash << 5) + uHash + *pcwszString++;

    return uHash;
}

// BKDR hash function use 131
inline unsigned int BKDRHash(const wchar_t *pcwszString)
{
    unsigned int uHash = 0;
    while (*pcwszString)
        //uHash = uHash * 131 + *pcwszString++;
        uHash = (uHash << 7) + (uHash << 1) + uHash + *pcwszString++;

    return uHash;
} 

inline int KG_DispatchHash(KG_HASH_TYPE eHashType, const wchar_t cwszString[], unsigned int *puRetHash)
{
    int nResult = false;

    switch(eHashType)
    {
    case KG_HASH_TIME33:
        *puRetHash = Time33Hash(cwszString);
        break;
    case KG_HASH_BKDR:
        *puRetHash = BKDRHash(cwszString);
        break;
    default:
        KG_ASSERT_EXIT(false);
        break;
    }

    nResult = true;
Exit0:
    return nResult;
}
 
int KG_ConvertFileName(const char cszString[], wchar_t wszRetFileName[])
{
    int nResult  = false;
    int nRetCode = false;

    wchar_t *pwszCurrent = NULL;
    size_t   uStrSize    = 0;

    KG_PROCESS_ERROR(cszString);
    KG_PROCESS_ERROR(wszRetFileName);

    uStrSize = strlen(cszString) + 1;
    KG_PROCESS_ERROR(uStrSize <= MAX_PATH);

    nRetCode = (int)mbstowcs(wszRetFileName, cszString, uStrSize);
    KG_PROCESS_ERROR(nRetCode > 0);

    wszRetFileName[uStrSize - 1] = L'\0';

#ifdef WIN32
    // towlower() is too slow on windows, use windows api instead
    CharLowerBuffW(wszRetFileName, uStrSize);

    for (pwszCurrent = wszRetFileName; *pwszCurrent != L'\0'; ++pwszCurrent)
    {
        if (*pwszCurrent == L'/')
        {
            *pwszCurrent = L'\\';
        }
    }
#else
    for (pwszCurrent = wszRetFileName; *pwszCurrent != L'\0'; ++pwszCurrent)
    {
        *pwszCurrent = towlower(*pwszCurrent);
        if (*pwszCurrent == L'/')
        {
            *pwszCurrent = L'\\';
        }
    }
#endif // WIN32

    nResult = true; 
Exit0:
    return nResult;
}

C_ENGINE_API int KG_StringHashW(KG_HASH_TYPE eHashType, const wchar_t cwszString[], unsigned int *puRetHash)
{
    int nResult = false;
    int nRetCode = false;

    KG_PROCESS_ERROR(puRetHash);
    KG_PROCESS_ERROR(cwszString);
    KG_PROCESS_ERROR(eHashType > KG_HASH_INVALID && eHashType < KG_HASH_TOTAL);

    nRetCode = KG_DispatchHash(eHashType, cwszString, puRetHash);
    KG_PROCESS_ERROR(nRetCode);

    nResult = true;
Exit0:
    return nResult;
}

C_ENGINE_API int KG_FileNameHash(KG_HASH_TYPE eHashType, const char cszFileName[], unsigned int *puRetHash)
{
    int nResult = false;
    int nRetCode = false;
    wchar_t wszConvertedFileName[MAX_PATH];

    KG_PROCESS_ERROR(puRetHash);
    KG_PROCESS_ERROR(cszFileName);
    KG_PROCESS_ERROR(eHashType > KG_HASH_INVALID && eHashType < KG_HASH_TOTAL);

    nRetCode = KG_ConvertFileName(cszFileName, wszConvertedFileName);
    KG_PROCESS_ERROR(nRetCode);

    nRetCode = KG_DispatchHash(eHashType, wszConvertedFileName, puRetHash);
    KG_PROCESS_ERROR(nRetCode);

    nResult = true;
Exit0:
    return nResult;
}
