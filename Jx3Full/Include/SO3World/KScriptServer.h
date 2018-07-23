#ifndef _KSCRIPTSERVER_H_  
#define _KSCRIPTSERVER_H_  

#ifdef _SERVER

#include <set>
#include <string>
#include "Engine/KMemory.h"
#include "lzo/lzoconf.h"

class KScriptServer
{
public:
    KScriptServer();

    BOOL Setup();
    BOOL IsFunctionRegistered(const char cszFunction[]);

    BOOL Accept(KPlayer* pPlayer, const char cszFunction[], BYTE* pbyData, size_t uDataLen);

    int  Call(Lua_State* L);

    void    Reset();
    BYTE*   PushNumber(double fValue);
    BYTE*   PushString(const char cszValue[]);
    BYTE*   PushNill();
    BYTE*   PushBool(BOOL bValue);
    BYTE*   NewTable();
    BYTE*   SetTable(BYTE* pbyTableBegin, BYTE* pbyTableEnd);
    BOOL    Call(int nConnIndex, const char cszFunction[]);

private:
    DWORD       m_dwScript;
    BYTE        m_byOriginalBuffer[LZO_ORIGINAL_BUFFER_LEN];
    BYTE        m_byCompressBuffer[LZO_COMPRESS_BUFFER_LEN];
    lzo_align_t m_LzoWorkBuffer[((lzo_uint32)(16384L * lzo_sizeof_dict_t) + (sizeof(lzo_align_t) - 1)) / sizeof(lzo_align_t)];
    BYTE*       m_pbyPos;

    typedef std::set<kstring, std::less<kstring>, KMemory::KAllocator<kstring> > KREGISTER_TABLE;
    KREGISTER_TABLE m_RegisterTable;

public:
    int  LuaRegister(Lua_State* L);

    DECLARE_LUA_CLASS(KScriptServer);
};

#endif

#endif
