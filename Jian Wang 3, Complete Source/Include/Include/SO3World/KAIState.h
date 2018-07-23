////////////////////////////////////////////////////////////////////////////////
//
//  FileName    : KAIState.h
//  Version     : 1.0
//  Creator     : Chen Jie, zhaochunfeng
//  Comment     : AI×´Ì¬½áµã
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _KAISTATE_H_ 
#define _KAISTATE_H_ 

#include "Luna.h"
#include "KAIAction.h"

class KCharacter;
class KAILogic;

class KAIState
{
public:
    KAIState(KAILogic* pAILogic) { assert(pAILogic); m_pAILogic = pAILogic; };

    KAIActionHandle GetEventHandler(int nEvent);

private:
    struct KAI_EVENT_HANDLE  
    {
        int             nEvent;
        KAIActionHandle ActionKey;
    };

    std::vector<KAI_EVENT_HANDLE>   m_EventHandleVector;    // Event handles
    KAILogic*                       m_pAILogic;

public:
    DECLARE_LUA_CLASS(KAIState);
    int LuaHandleEvent(Lua_State* L);
    void DebugStateInfo();
};

#endif //_KAISTATE_H_
