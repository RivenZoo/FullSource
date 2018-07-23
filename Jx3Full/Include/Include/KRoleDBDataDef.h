/************************************************************************/
/* 剑三角色数据结构定义			                                        */
/* Copyright : Kingsoft 2005										    */
/* Author	 : Zhu Jianqiu												*/
/************************************************************************/

#ifndef _KROLE_DB_DATA_DEF_H_
#define _KROLE_DB_DATA_DEF_H_

#include "SO3ProtocolBasic.h"

#define MAX_ROLE_DATA_SIZE          (1024 * 256)

enum ROLE_DATA_BLOCK_TYPE
{
	rbtInvalid = 0,

	rbtSkillList,
	rbtItemList,
	rbtQuestList,
	rbtProfessionList,
    rbtStateInfo,
    rbtBuffList,
	rbtRepute,
	rbtUserPreferences,
	rbtBookState,
    rbtSkillRecipeList,
	rbtRecipeList,
    rbtCoolDownTimer,
    rbtRoadOpenList,
    rbtCustomData,
    rbtVisitedMap,
    rbtPQList,
    rbtHeroData,
    rbtAchievementData,
    rbtDesignationData,
    rbtRandData,
    rbtAntiFarmerData,
    rbtMentorData,

	rbtTotal
};

#pragma	pack(1)

// -----角色基本信息定义------

struct KROLE_POSITION_DB
{
    DWORD	dwMapID;
    int	    nMapCopyIndex;
    int		nX;
    int		nY;
    int		nZ;
    BYTE    byFaceDirection;
};

struct KRoleBaseHeader 
{
    int     nVersion;
};

struct KRoleBaseInfo : KRoleBaseHeader
{
    char                cRoleType;
    KROLE_POSITION_DB   CurrentPos;
    KROLE_POSITION_DB   LastEntry;
    BYTE	            byLevel;
    BYTE                byCamp;
    BYTE                byForceID;
    WORD                wRepresentId[perRepresentCount];
    time_t	            nLastSaveTime;
    time_t              nLastLoginTime;
    time_t              nTotalGameTime;
    time_t              nCreateTime;
    BYTE                byReserved[16];
};

struct KROLE_LIST_INFO
{
    DWORD	            dwPlayerID;
    char	            szAccount[_NAME_LEN];
    char	            szRoleName[_NAME_LEN];
    KRoleBaseInfo       BaseInfo;
    BYTE                byCanRename;
    time_t              nFreezeTime;
    time_t              nDeleteTime;
};

// -----角色扩展数据定义------

struct KRoleDataHeader
{
	DWORD	dwVer;
	DWORD	dwCRC;
	DWORD	dwLen;
};

struct KRoleBlockHeader
{
    int     nType;
    DWORD   dwVer;
    DWORD   dwLen;
};

// 角色属性数据
struct KROLE_STATE_INFO
{
    BYTE    byMoveState;
    WORD    wCurrentTrack;
    int     nMoveFrameCounter;
    WORD    wFromFlyNode;
    WORD    wTargetCityID;

	int     nExperience;

	int		nCurrentLife;				
	int		nCurrentMana;				
    int     nCurrentStamina;
    int     nCurrentThew;

    int     nAddTrainTimeInToday;
    int     nCurrentTrainValue;
    int     nUsedTrainValue;
    WORD    wReserved;

    BYTE    byPKState;
    WORD    wCloseSlayLeftTime; // 单位：秒

    WORD    wLeftReviveFrame;
    time_t  nLastSituReviveTime;
    BYTE    bySituReviveCount;
    DWORD   dwKillerID;

    WORD    wCurrentKillPoint;
    int     nReserved0;

    int     nCurrentPrestige; // 威望
    time_t  nBanTime;
    int     nContribution;    // 贡献值
    int     nMaxLevel;
    BOOL    bHideHat;         // 是否隐藏帽子

    BYTE    byTalkWorldDailyCount;
    BYTE    byTalkForceDailyCount;
    BYTE    byTalkCampDailyCount;
    BYTE    byKilledCount;
    time_t  nNextResetKilledCountTime;

    BYTE    byCampFlag;

    BYTE    byReserved[23];
};

struct KUSER_ROLE_GENERATOR_PARAM
{
	char	szRoleName[_NAME_LEN];
	char    cRoleType;
    DWORD   dwMapID;
    int     nMapCopyIndex;
    WORD    wRepresentId[perRepresentCount];
};

struct KDB_ROLE_GENERATOR_PARAM
{
    char    szAccountName[_NAME_LEN];
    int     nX;
    int     nY;
    int     nZ;
    BYTE    byDirection;
    KUSER_ROLE_GENERATOR_PARAM UserParam;
};

// 交通点存到结构
struct KROLE_ROAD_INFO
{
    int nOpenNodeCount;
    int OpenNodeList[0];
};

struct KHERO_DATA 
{
    BYTE byHeroFlag;
    BYTE byDataLen;
    BYTE byData[0];
};

struct KFORCE_DB_DATA
{
    WORD    wCount;
    struct FORECE_INFO 
    {
        BYTE    byForce;
        BYTE    byFightFlag;
        BYTE    byLevel;
        short   shRepute;
        BYTE    byShow;
    }   ForceInfo[0];
};

struct KMENTOR_DATA_ON_PLAYER
{
    int     nAcquiredMentorValue;
    time_t  nLastEvokeMentorTime;
    BYTE    byEvokeMentorCount;
    BYTE    byMaxApprenticeCount;

    BYTE    byReserved[22];
};

#pragma pack()

#endif	//_KROLE_DB_DATA_DEF_H_
