#ifndef _KGW_CONST_LIST_
#define _KGW_CONST_LIST_

#include "Global.h"

#define PLAYER_AND_QUEST_DIFF_LEVEL_COUNT 4 
#define MAX_KILL_COUNT                    11

struct KGWConstList
{
public:
	// AI
	int nMaxThreatCount;
	int nNpcSkillCommonCD;
	int nNpcCommonShortCD;
    int nAISearchByLifeConversionLevel;

	// PK
	int nPKFlagDoodadTemplateID;
    int nSlayCDIndex;
    int nWaitSlayTime;
    int nCloseSlayTime;
    int nMinDuelLevel;
    int nMinRevengeLevel;
    int nMinSlayLevel;
    int nMinBeSlayedLevel;
    int nKillPointReduceCycle;
    int nReduceKillPoint;

    // Mail
    int nMailDelaySecondOnText;
    int nMailDelaySecondOnMoney;
    int nMailDelaySecondOnItem;
    int nMailSurvivalTime;

	// Item
	int nBankPackagePrice[MAX_BANK_PACKAGE_COUNT];

    // Fellowship
    int nTeamAttractiveInterval;       // 组队增加好感度的间隔(Frame)
    int nTeamAttractiveRange;          // 组队增加好感度的距离
    int nTeamAttractiveUpLimit;        // 组队增加好感度的上限值
    int nTeamAttractiveAdd;

    int nTeamAttractiveIntervalOnlyGroup;       // 组队增加好感度的间隔(Frame)
    int nTeamAttractiveRangeOnlyGroup;          // 组队增加好感度的距离
    int nTeamAttractiveUpLimitOnlyGroup;        // 组队增加好感度的上限值
    int nTeamAttractiveAddOnlyGroup;

    int nDuelAttractiveDailyCount;      // 切磋增加好感度的每日限制
    int nDuelAttractiveUpLimit;         // 切磋增加好感度的上限值
    int nDuelAttractiveAdd;

    int nAssistAttractiveUpLimit;       // 协助任务增加好感度的上限值
    int nAssistPresentContribution;     // 一个帮会的人互相协助增加贡献度

    int nWhisperAttractiveDailyCount;   // 密聊增加好感度的每日限制
    int nWhisperAttractiveUpLimit;      // 密聊增加好感度的上限值
    int nWhisperAttractiveAdd;

    int nAttractiveLevel[MAX_FELLOWSHIP_ATTRACTIVE_LEVEL];          // 好感度等级的划分
    int nAttractiveAchievement[MAX_FELLOWSHIP_ATTRACTIVE_LEVEL];    // 好感度等级成就
    int nCountAchievement[MAX_FELLOWSHIP_COUNT_ACHIEVEMENT];        // 好友数量成就

    int nDifferentCampApplyJoinTeam;                                // 不同阵营组队需要的好感度等级

    // 溺水而亡的时间,单位: 秒
    int nDrowningTime;
    int nSaveInterval;
    
    // NPC死亡后,产生尸体的延迟时间
    int nCorpseGenerationFrame;

    // 玩家可升级的最大等级
    int nPlayerMaxLevel;

    // Skill
    int nRiseFrame;
    int nSkidFrame;
    int nNoAddSkillExp;

    // Talk
    int nSceneChannelCoolDownID;
    int nWorldChannelCoolDownID;
    int nForceChannelCoolDownID;
    int nCampChannelCoolDownID;
    int nMentorChannelCoolDownID;
    int nFriendsChannelCoolDownID;

    // 仇恨插件接口
    int nApplyThreatRankListCD;

    int nPlayerAndQuestDiffLevel[PLAYER_AND_QUEST_DIFF_LEVEL_COUNT];

    // 阵营威望相关的奖励与惩罚
    int nReducePrestigeOnDeath;
    int nSoloKill;
    int nLastHit;
    int nCommonKill;
    int nKillerTeamMember;
    int nSameCampKill;
    int nSameCampAssistKill;
    int nKilledCountPercent[MAX_KILL_COUNT];
    int nResetKilledCountCycle;
    // 阵营威望上限
    int nMaxPrestige; 
    
    // 是否使用新的使用道具机制，过渡用
    BOOL bNewUseItemStyle;

    // 收费相关
    int nFreeMaxLevel;      // 免费阶段最大等级
    int nFreeDurationTime;  // 免费最长时间
    int nEndOfDayTimeDealy; // 截止时间断线延时

    // 全局任务计数成就
    int nQuestCountAchievementID;
    int nAssistQuestCountAchievementID;
    int nFinishQuestAssistByOtherAchievementID;

    int nNpcReviveTimeReduceThreshold;
    int nNpcReviveTimeIncreaseThreshold;
    int nNpcReviveTimeReduceRate;
    int nNpcReviveTimeIncreaseRate;

    int nMaxDesignationBynameIndex;

    // 反打钱
    int     nAntiFarmerCheckOnlineTimeRange;
    float   fAntiFarmerOnlineRate;
    float   fAntiFarmerKillNpcRate;
    int     nAntiFarmerKillNpcTypeNum;
    int     nAntiFarmerRecordKillNpcNum;
    int     nAntiFarmerPunishTime;
    float   fAntiFarmerPunishRate;

    BOOL bFreeForAll;
    BOOL bDistribute;
    BOOL bGroupLoot;

    int  nLootItemQualityToLog;

	BOOL Init();
	void UnInit();
private:
	BOOL LoadData(IIniFile* piIniFile);
};

#endif //_KGW_CONST_LIST_
