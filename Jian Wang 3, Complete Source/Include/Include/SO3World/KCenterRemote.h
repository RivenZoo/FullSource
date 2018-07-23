#ifndef _KCENTERREMOTE_H_ 
#define _KCENTERREMOTE_H_ 

#ifdef _SERVER

#include "lzo/lzoconf.h"

class KCenterRemote
{
public:
    KCenterRemote();

    void Setup();

    BOOL Accept(const char cszFunction[], BYTE* pbyData, size_t uDataLen);

    int  Call(Lua_State* L);

private:
    DWORD       m_dwScript;
    BYTE        m_byOriginalBuffer[LZO_ORIGINAL_BUFFER_LEN];
    BYTE        m_byCompressBuffer[LZO_COMPRESS_BUFFER_LEN];
    lzo_align_t m_LzoWorkBuffer[((lzo_uint32)(16384L * lzo_sizeof_dict_t) + (sizeof(lzo_align_t) - 1)) / sizeof(lzo_align_t)];
};

#endif

#endif
