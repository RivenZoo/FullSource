#ifndef _KSCRIPTCLIENT_H_ 
#define _KSCRIPTCLIENT_H_ 

#ifdef _CLIENT

#include <set>
#include <string>
#include "Engine/KMemory.h"
#include "lzo/lzoconf.h"

class KScriptClient 
{
public:
    KScriptClient();

    BOOL Setup();
    BOOL Accept(const char cszFunction[], BYTE* pbyData, size_t uDataLen);

    int  Call(Lua_State* L);

private:
    BOOL AcceptToScriptClient(const char cszFunction[], BYTE* pbyData, size_t uDataLen);

private:
    DWORD       m_dwScript;
    BYTE        m_byOriginalBuffer[LZO_ORIGINAL_BUFFER_LEN];
    BYTE        m_byCompressBuffer[LZO_COMPRESS_BUFFER_LEN];
    lzo_align_t m_LzoWorkBuffer[((lzo_uint32)(16384L * lzo_sizeof_dict_t) + (sizeof(lzo_align_t) - 1)) / sizeof(lzo_align_t)];
};

#endif

#endif
