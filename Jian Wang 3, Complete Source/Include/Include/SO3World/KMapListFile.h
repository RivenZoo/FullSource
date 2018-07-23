#ifndef _KMAP_LIST_FILE_H_
#define _KMAP_LIST_FILE_H_

#include "Global.h"

struct KMapParams
{
    DWORD   dwMapID;
	char	szMapName[_NAME_LEN];    
    int     nBroadcast;
    BOOL    bCanPK;
    int     nCampType;
    BOOL    bAllScenePlayerInFight;
	char	szDropName[MAX_PATH];
    int     bReviveInSitu;
	char	szResourceFilePath[MAX_PATH];
    int     nMaxPlayerCount;
    DWORD   dwBanSkillMask;
    DWORD   dwBattleRelationMask;
    BOOL    bDoNotGoThroughRoof;
    int     nType;
    int     nRefreshCycle;      // 单位：秒
    int     nQuestCountAchID;   // 场景任务计数成就ID
    int     nLimitTimes;
};

typedef std::map<DWORD, KMapParams> KMAP_PARAM_TABLE;

class KMapListFile
{
public:
	BOOL Init();
    void UnInit(){};

	KMapParams*	GetMapParamByID(DWORD dwMapID);
    KMapParams*	GetMapParamByName(const char cszName[]);

    const KMAP_PARAM_TABLE& GetMapList() { return m_MapParamTable; }

private:
	KMAP_PARAM_TABLE m_MapParamTable;
};

#endif	//_KMAP_LIST_FILE_H_

