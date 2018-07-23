////////////////////////////////////////////////////////////////////////////////
//
//  FileName    : KTimeLimitationBindItemMgr.h
//  Version     : 1.0
//  Creator     : XiaYong
//  Create Date : 2009-11-17
//  Comment     : 
//
////////////////////////////////////////////////////////////////////////////////

#include <map>
#include "Engine/KMemory.h"
#ifndef _KTIMELIMITATIONBINDITEMMGR_H_
#define _KTIMELIMITATIONBINDITEMMGR_H_
struct KTIME_LIMITATION_BIND_ITEM 
{
    std::vector<DWORD>  vecPlayerList;
    DWORD               dwOwnerID;
    time_t              nEndTime;
    BOOL                bDataChanged;
};
typedef KMemory::KAllocator<std::pair<DWORD, KTIME_LIMITATION_BIND_ITEM> > KBASE_INFO_TABLE_ALLOC;
typedef std::map<DWORD, KTIME_LIMITATION_BIND_ITEM, less<DWORD>, KBASE_INFO_TABLE_ALLOC> MAP_LIMITATION_BIND_ITEM;

class KScene;
class KTimeLimitationBindItemMgr
{
public:
    BOOL Init(KScene* pScene);
    void Activate();

    BOOL AddItem(DWORD dwItemID, DWORD dwOwnerID, int nLeftTime = 0);
    void DelItem(DWORD dwItemID);

    BOOL IsPlayerCanHaveTheItem(DWORD dwItemID, DWORD dwPlayerID);

    BOOL AddPlayer(DWORD dwItemID, DWORD dwPlayerID);
    BOOL RemovePlayer(DWORD dwItemID, DWORD dwPlayerID);
    BOOL GetAllPlayer(DWORD dwItemID, std::vector<DWORD> &vecPlayers);
    
    void OnPlayerLeaveScene(DWORD dwPlayerID);

    int  GetLeftTime(DWORD dwItemID);

    DWORD GetOwner(DWORD dwItemID);
    BOOL SetOwner(DWORD dwItemID, DWORD dwOwnerID);

private:
    void DoSyncTimeLimitationBindItemInfo(DWORD dwItemID, KTIME_LIMITATION_BIND_ITEM* pItemInfo);

private:
    MAP_LIMITATION_BIND_ITEM m_mapLimitationBindItem;
    KScene* m_pScene;
};
#endif
