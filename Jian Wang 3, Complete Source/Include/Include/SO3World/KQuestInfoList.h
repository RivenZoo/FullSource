/************************************************************************/
/* 任务配置表															*/
/* Copyright : Kingsoft 2005										    */
/* Author	 : Zhu Jianqiu												*/
/* History	 :															*/
/*		2005.11.01	Create												*/
/************************************************************************/
#ifndef _KQUEST_INFO_LIST_H_
#define _KQUEST_INFO_LIST_H_

#include <map>
#include <vector>
#include "Global.h"
#include "SO3ProtocolBasic.h"
#include "Luna.h"
#include "KLRUCacheMap.h"

#define QUEST_NAME_LEN					32
#define QUEST_OBJECTIVE_LEN				1026
#define QUEST_DESCRIPTION_LEN			1024
#define QUEST_UNFINISHED_DIALOGUE_LEN	1024
#define QUEST_FINISHED_DIALOGUE_LEN		1024
#define QUEST_VALUE_STR_LEN				256
#define QUEST_GOSSIP_LEN		        1024

#define MAX_QUEST_COUNT			        8192
#define QUEST_END_ITEM_COUNT            8

struct KQuestInfo
{
	DWORD			dwQuestID;
    DWORD           dwClassID;
#ifdef _SERVER
    char            szQuestName[QUEST_NAME_LEN];
#endif

	bool            bShare;										// 是否可共享
	bool            bRepeat;									// 是否可重复
	bool            bAssist;									// 是否可协助
	bool            bAccept;									// 是否需要接了才能交

    bool			bEscortQuest;                               // 是否护送任务
    bool			bPrequestLogic;								// true:and;false:or
    bool            bRequireReputeAll;                          // 接任务时声望限制的逻辑关系(true: AND, false: OR)
    bool			bHidePresent;								// 是否隐藏奖励

    bool			bPresentAll[2];								// 第一组(1-4)道具是否全给或者只给一件
    BYTE            byStartMapID;								// 接任务Npc所在地图的ID, 暂时废弃
    BYTE            byEndMapID;									//交任务Npc所在的地图ID, 暂时废弃
    
    BYTE            byLevel;                                    // 任务等级
    BYTE            byStartItemType;							// 接任务Item类型
    WORD			wStartItemIndex;							// 接任务Item类型			

    BYTE            byMinLevel;									// 接任务最小等级需求
    BYTE            byMaxLevel;									// 接任务最大等级需求
    BYTE            byRequireGender;								// 接任务的性别需求
    BYTE            byRequireRoleType;							// 接受任务的玩家体形需求

    WORD            wRequireSkillID;							// 需求技能
    BYTE            byMinSkillLevel;							// 需求技能最小等级
    BYTE			byRequireLifeSkillID;						// 需求生活技能

    BYTE			byMinLifeSkillLevel;						// 需求技能最小等级
    bool            bRequireApprentice;                         // 需求是徒弟

    BYTE			byStartRequireItemType[QUEST_PARAM_COUNT];	
    WORD			wStartRequireItemIndex[QUEST_PARAM_COUNT];	
    WORD            wStartRequireItemAmount[QUEST_PARAM_COUNT];

#ifdef _SERVER
    BYTE            byOfferItemType[QUEST_PARAM_COUNT];			// 接任务时提供道具的类型
    WORD            wOfferItemIndex[QUEST_PARAM_COUNT];		// 接任务时提供道具的类型
    WORD            wOfferItemAmount[QUEST_PARAM_COUNT];		// 接任务时提供道具的数量
#endif

    BYTE            byRequireForceID[QUEST_PARAM_COUNT];
    BYTE            byReputeLevelMin[QUEST_PARAM_COUNT];
    BYTE            byReputeLevelMax[QUEST_PARAM_COUNT];

    BYTE			byEndItemType;								//交任务Item类型
    WORD            wEndItemIndex;								//交任务Item类型
    BYTE            byRepeatCutPercent;							// 重复做任务时奖励的削减百分比

    BYTE            byRequireCampMask;                           // 阵营需求; 第0,1,2位分别对应中立、正义、邪恶
    BYTE            byTeamRequireMode;                           // 团队模式对任务的需求
    WORD            wPresentSkill;								// 奖励的技能ID

    BYTE            byEndRequireItemType[QUEST_END_ITEM_COUNT];	//交任务时所需道具的类型
    WORD			wEndRequireItemIndex[QUEST_END_ITEM_COUNT];	//交任务时所需道具的类型
    WORD            wEndRequireItemAmount[QUEST_END_ITEM_COUNT];	//交任务时所需道具的数量
    DWORD			dwDropItemDoodadTemplateID[QUEST_END_ITEM_COUNT];	//掉落交任务道具的doodad模板ID
#ifdef _SERVER
    DWORD			dwDropItemNpcTemplateID[QUEST_END_ITEM_COUNT];		//掉落交任务道具的Npc模板ID
    DWORD			dwDropItemRate[QUEST_END_ITEM_COUNT];			//掉落任务道具的几率
    bool			bDropForEach[QUEST_END_ITEM_COUNT];			    //是否每人都获得一个
    bool			bIsDeleteEndRequireItem[QUEST_END_ITEM_COUNT]; //交任务或者删除任务的时候是否删除这个道具
#endif

    DWORD			dwRelationDoodadID[QUEST_PARAM_COUNT * 2];  // 任务相关联的DoodadID

    BYTE			byPresentItemType[QUEST_PARAM_COUNT * 2];	// 交任务时奖励道具的类型
    WORD			wPresentItemIndex[QUEST_PARAM_COUNT * 2];	// 交任务时奖励道具的类型
    WORD            wPresentItemAmount[QUEST_PARAM_COUNT * 2];	// 交任务时奖励道具的数量

    BYTE            byAffectForceID[QUEST_PARAM_COUNT];			// 交任务影响的势力
    int             nAffectForceValue[QUEST_PARAM_COUNT];		// 交任务影响的势力友好度
	
	DWORD			dwStartNpcTemplateID;						// 接任务Npc的模板ID
	DWORD			dwStartDoodadTemplateID;					// 接任务Doodad的模板ID
    
	DWORD			dwCoolDownID;								// CoolDown计时器ID
	
	DWORD			dwPrequestID[QUEST_PARAM_COUNT];			// 前置任务ID
	DWORD			dwSubsequenceID;							// 直接后继任务ID
	int				nStartTime;									// 开始时间
	int				nEndTime;									// 结束时间

    DWORD           dwRequireSchoolMask;                        // 接任务时的门派限制
    
	DWORD			dwEndNpcTemplateID;							//交任务Npc的模板ID
	DWORD			dwEndDoodadTemplateID;						//交任务Doodad的模板ID
    
	int				nFinishTime;								//完成时间限制

	int				nCostMoney;									//交任务需求的金钱

	DWORD			dwKillNpcTemplateID[QUEST_PARAM_COUNT];		//交任务时所需杀死的Npc模板ID
	WORD			wKillNpcAmount[QUEST_PARAM_COUNT];			//交任务时所需杀死的Npc数量

	int				nQuestValue[QUEST_PARAM_COUNT * 2];			//任务变量

	int				nPresentExp;								// 交任务时奖励的经验
	int				nPresentMoney;								// 交任务时奖励的金钱数量

    int             nPresentAssistThew;                         // 协助任务奖励体力
    int             nPresentAssistStamina;                      // 协助任务奖励精力
    int             nPresentAssistFriendship;                   // 协助任务奖励好感度

    DWORD           dwScriptID;
    
    int             nPresentPrestige;                           // 任务奖励威望
    int             nPresentContribution;                       // 任务奖励贡献值
    int             nPresentTrain;                              // 任务奖励修为
#ifdef _SERVER
    int             nAchievementID;                             // 任务成就
    int             nAssistMentorValue;                         // 协助任务中有师傅协助是，给师傅加的师徒值
#endif

//Lua脚本接口
    DWORD getQuestClass(){return dwClassID;}
    DWORD getStartMapID() {return byStartMapID;}
    DWORD getEndMapID() {return byEndMapID;}
    int   getPresentAll1() {return bPresentAll[0];}
    int   getPresentAll2() {return bPresentAll[1];}
    int   getLevel() {return byLevel;}
    DWORD getStartItemType() {return byStartItemType;}
    DWORD getStartItemIndex() {return wStartItemIndex;}
    int   getMinLevel() {return byMinLevel;}
    int   getMaxLevel() {return byMaxLevel;}
    int   getRequireGender() {return byRequireGender;}
    int   getRequireRoleType() {return byRequireRoleType;}
    DWORD getRequireSkillID() {return wRequireSkillID;}
    DWORD getMinSkillLevel() {return byMinSkillLevel;}
    DWORD getRequireLifeSkillID() {return byRequireLifeSkillID;}
    DWORD getMinLifeSkillLevel() {return byMinLifeSkillLevel;}

    DWORD getStartRequireItemType1() {return byStartRequireItemType[0];}
    DWORD getStartRequireItemIndex1() {return wStartRequireItemIndex[0];};
    DWORD getStartRequireItemAmount1() {return wStartRequireItemAmount[0];}
    
    DWORD getStartRequireItemType2() {return byStartRequireItemType[1];}
    DWORD getStartRequireItemIndex2() {return wStartRequireItemIndex[1];}
    DWORD getStartRequireItemAmount2() {return wStartRequireItemAmount[1];}

    DWORD getStartRequireItemType3() {return byStartRequireItemType[2];}
    DWORD getStartRequireItemIndex3() {return wStartRequireItemIndex[2];}
    DWORD getStartRequireItemAmount3() {return wStartRequireItemAmount[2];}

    DWORD getStartRequireItemType4() {return byStartRequireItemType[3];}
    DWORD getStartRequireItemIndex4() {return wStartRequireItemIndex[3];}
    DWORD getStartRequireItemAmount4() {return wStartRequireItemAmount[3];}
    
    DWORD getRequireForceID1() {return byRequireForceID[0];}
    int   getReputeLevelMin1() {return byReputeLevelMin[0];}
    int   getReputeLevelMax1() {return byReputeLevelMax[0];}
    
    DWORD getRequireForceID2() {return byRequireForceID[1];}
    int   getReputeLevelMin2() {return byReputeLevelMin[1];}
    int   getReputeLevelMax2() {return byReputeLevelMax[1];}

    DWORD getRequireForceID3() {return byRequireForceID[2];}
    int   getReputeLevelMin3() {return byReputeLevelMin[2];}
    int   getReputeLevelMax3() {return byReputeLevelMax[2];}

    DWORD getRequireForceID4() {return byRequireForceID[3];}
    int   getReputeLevelMin4() {return byReputeLevelMin[3];}
    int   getReputeLevelMax4() {return byReputeLevelMax[3];}

    DWORD getEndItemType() {return byEndItemType;}
    DWORD getEndItemIndex() {return wEndItemIndex;}
    int   getRepeatCutPercent() {return byRepeatCutPercent;}
    int   getRequireCampMask() {return byRequireCampMask;}
    int   getTeamRequireMode() {return byTeamRequireMode;}
    int   getPresentSkill() {return wPresentSkill;}

    DWORD getEndRequireItemType1() {return byEndRequireItemType[0];}
    DWORD getEndRequireItemIndex1() {return wEndRequireItemIndex[0];}
    DWORD getEndRequireItemAmount1() {return wEndRequireItemAmount[0];}

    DWORD getEndRequireItemType2() {return byEndRequireItemType[1];}
    DWORD getEndRequireItemIndex2() {return wEndRequireItemIndex[1];}
    DWORD getEndRequireItemAmount2() {return wEndRequireItemAmount[1];}

    DWORD getEndRequireItemType3() {return byEndRequireItemType[2];}
    DWORD getEndRequireItemIndex3() {return wEndRequireItemIndex[2];}
    DWORD getEndRequireItemAmount3() {return wEndRequireItemAmount[2];}

    DWORD getEndRequireItemType4() {return byEndRequireItemType[3];}
    DWORD getEndRequireItemIndex4() {return wEndRequireItemIndex[3];}
    DWORD getEndRequireItemAmount4() {return wEndRequireItemAmount[3];}

    DWORD getEndRequireItemType5() {return byEndRequireItemType[4];}
    DWORD getEndRequireItemIndex5() {return wEndRequireItemIndex[4];}
    DWORD getEndRequireItemAmount5() {return wEndRequireItemAmount[4];}

    DWORD getEndRequireItemType6() {return byEndRequireItemType[5];}
    DWORD getEndRequireItemIndex6() {return wEndRequireItemIndex[5];}
    DWORD getEndRequireItemAmount6() {return wEndRequireItemAmount[5];}

    DWORD getEndRequireItemType7() {return byEndRequireItemType[6];}
    DWORD getEndRequireItemIndex7() {return wEndRequireItemIndex[6];}
    DWORD getEndRequireItemAmount7() {return wEndRequireItemAmount[6];}

    DWORD getEndRequireItemType8() {return byEndRequireItemType[7];}
    DWORD getEndRequireItemIndex8() {return wEndRequireItemIndex[7];}
    DWORD getEndRequireItemAmount8() {return wEndRequireItemAmount[7];}

    DWORD getPresentItemType1() {return byPresentItemType[0];}
    DWORD getPresentItemIndex1() {return wPresentItemIndex[0];}
    DWORD getPresentItemAmount1() {return wPresentItemAmount[0];}
    
    DWORD getPresentItemType2() {return byPresentItemType[1];}
    DWORD getPresentItemIndex2() {return wPresentItemIndex[1];}
    DWORD getPresentItemAmount2() {return wPresentItemAmount[1];}

    DWORD getPresentItemType3() {return byPresentItemType[2];}
    DWORD getPresentItemIndex3() {return wPresentItemIndex[2];}
    DWORD getPresentItemAmount3() {return wPresentItemAmount[2];}

    DWORD getPresentItemType4() {return byPresentItemType[3];}
    DWORD getPresentItemIndex4() {return wPresentItemIndex[3];}
    DWORD getPresentItemAmount4() {return wPresentItemAmount[3];}

    DWORD getPresentItemType5() {return byPresentItemType[4];}
    DWORD getPresentItemIndex5() {return wPresentItemIndex[4];}
    DWORD getPresentItemAmount5() {return wPresentItemAmount[4];}

    DWORD getPresentItemType6() {return byPresentItemType[5];}
    DWORD getPresentItemIndex6() {return wPresentItemIndex[5];}
    DWORD getPresentItemAmount6() {return wPresentItemAmount[5];}

    DWORD getPresentItemType7() {return byPresentItemType[6];}
    DWORD getPresentItemIndex7() {return wPresentItemIndex[6];}
    DWORD getPresentItemAmount7() {return wPresentItemAmount[6];}

    DWORD getPresentItemType8() {return byPresentItemType[7];}
    DWORD getPresentItemIndex8() {return wPresentItemIndex[7];}
    DWORD getPresentItemAmount8() {return wPresentItemAmount[7];}
    
    DWORD getAffectForceID1() {return byAffectForceID[0];}
	DWORD getAffectForceID2() {return byAffectForceID[1];}
    DWORD getAffectForceID3() {return byAffectForceID[2];}
    DWORD getAffectForceID4() {return byAffectForceID[3];}

    DWORD getKillNpcAmount1() {return wKillNpcAmount[0];}
    DWORD getKillNpcAmount2() {return wKillNpcAmount[1];}
    DWORD getKillNpcAmount3() {return wKillNpcAmount[2];}
    DWORD getKillNpcAmount4() {return wKillNpcAmount[3];}

    DECLARE_LUA_CLASS(KQuestInfo);

    DECLARE_LUA_STRUCT_DWORD(QuestClassID, dwClassID);	

	DECLARE_LUA_STRUCT_BOOL(Share, bShare);					    // 是否可共享
	DECLARE_LUA_STRUCT_BOOL(Repeat, bRepeat);					// 是否可重复
	DECLARE_LUA_STRUCT_BOOL(Assist, bAssist);					// 是否可协助
	DECLARE_LUA_STRUCT_BOOL(Accept, bAccept);					// 是否先接才能交

	DECLARE_LUA_STRUCT_DWORD(StartNpcTemplateID, dwStartNpcTemplateID);			//接任务Npc的ID
    DECLARE_LUA_STRUCT_DWORD(RequireSchoolMask, dwRequireSchoolMask);

    DECLARE_LUA_STRUCT_BOOL(RequireReputeAll, bRequireReputeAll);

	DECLARE_LUA_STRUCT_DWORD(CoolDownID, dwCoolDownID);		//CoolDown计时器ID
	DECLARE_LUA_STRUCT_BOOL(PrequestLogic, bPrequestLogic);
	DECLARE_LUA_STRUCT_DWORD(PrequestID1, dwPrequestID[0]);			//前置任务ID
	DECLARE_LUA_STRUCT_DWORD(PrequestID2, dwPrequestID[1]);			//前置任务ID
	DECLARE_LUA_STRUCT_DWORD(PrequestID3, dwPrequestID[2]);			//前置任务ID
	DECLARE_LUA_STRUCT_DWORD(PrequestID4, dwPrequestID[3]);			//前置任务ID
	DECLARE_LUA_STRUCT_INTEGER(StartTime, nStartTime);			//开始时间
	DECLARE_LUA_STRUCT_INTEGER(EndTime, nEndTime);				//结束时间
	DECLARE_LUA_STRUCT_DWORD(SubsequenceID, dwSubsequenceID);	//直接后继任务ID   

	DECLARE_LUA_STRUCT_DWORD(EndNpcTemplateID, dwEndNpcTemplateID);			//交任务Npc的ID
    DECLARE_LUA_STRUCT_DWORD(EndDoodadTemplateID, dwEndDoodadTemplateID);   //交任务Doodad的ID  

	DECLARE_LUA_STRUCT_INTEGER(FinishTime, nFinishTime);						//完成时间限制

	DECLARE_LUA_STRUCT_INTEGER(CostMoney, nCostMoney);							//消耗的金钱

	DECLARE_LUA_STRUCT_DWORD(KillNpcTemplateID1, dwKillNpcTemplateID[0]);		//交任务时所需杀死的Npc模板ID
	DECLARE_LUA_STRUCT_DWORD(KillNpcTemplateID2, dwKillNpcTemplateID[1]);		//交任务时所需杀死的Npc模板ID
	DECLARE_LUA_STRUCT_DWORD(KillNpcTemplateID3, dwKillNpcTemplateID[2]);		//交任务时所需杀死的Npc模板ID
	DECLARE_LUA_STRUCT_DWORD(KillNpcTemplateID4, dwKillNpcTemplateID[3]);		//交任务时所需杀死的Npc模板ID

	DECLARE_LUA_STRUCT_INTEGER(QuestValue1, nQuestValue[0]);						//任务变量
	DECLARE_LUA_STRUCT_INTEGER(QuestValue2, nQuestValue[1]);						//任务变量
	DECLARE_LUA_STRUCT_INTEGER(QuestValue3, nQuestValue[2]);						//任务变量
	DECLARE_LUA_STRUCT_INTEGER(QuestValue4, nQuestValue[3]);						//任务变量
	DECLARE_LUA_STRUCT_INTEGER(QuestValue5, nQuestValue[4]);						//任务变量
	DECLARE_LUA_STRUCT_INTEGER(QuestValue6, nQuestValue[5]);						//任务变量
	DECLARE_LUA_STRUCT_INTEGER(QuestValue7, nQuestValue[6]);						//任务变量
	DECLARE_LUA_STRUCT_INTEGER(QuestValue8, nQuestValue[7]);						//任务变量

	DECLARE_LUA_STRUCT_BOOL(HidePresent, bHidePresent);			//是否隐藏奖励

	DECLARE_LUA_STRUCT_INTEGER(PresentExp, nPresentExp);					//交任务时奖励的经验
	DECLARE_LUA_STRUCT_INTEGER(PresentMoney, nPresentMoney);				//交任务时奖励的金钱数量

    DECLARE_LUA_STRUCT_INTEGER(PresentAssistThew, nPresentAssistThew);
    DECLARE_LUA_STRUCT_INTEGER(PresentAssistStamina, nPresentAssistStamina);
    DECLARE_LUA_STRUCT_INTEGER(PresentAssistFriendship, nPresentAssistFriendship);

	DECLARE_LUA_STRUCT_INTEGER(AffectForceValue1, nAffectForceValue[0]);	//交任务影响的势力友好度
	DECLARE_LUA_STRUCT_INTEGER(AffectForceValue2, nAffectForceValue[1]);	//交任务影响的势力友好度
	DECLARE_LUA_STRUCT_INTEGER(AffectForceValue3, nAffectForceValue[2]);	//交任务影响的势力友好度
	DECLARE_LUA_STRUCT_INTEGER(AffectForceValue4, nAffectForceValue[3]);	//交任务影响的势力友好度

    DECLARE_LUA_STRUCT_INTEGER(PresentPrestige, nPresentPrestige);
    DECLARE_LUA_STRUCT_INTEGER(PresentContribution, nPresentContribution);
    DECLARE_LUA_STRUCT_INTEGER(PresentTrain, nPresentTrain);

	int LuaGetHortation(Lua_State* L);
};

class KQuestInfoList
{
public:
	BOOL Init();
	void UnInit();

	KQuestInfo* GetQuestInfo(DWORD dwQuestID);

	int GetNpcQuestString(DWORD dwMapID, DWORD dwNpcTemplateID, char* pszBuffer, size_t uBufferSize);
	BOOL GetNpcQuest(DWORD dwNpcTemplateID, std::vector<DWORD>* pvQuestID);
    BOOL IsNpcQuestExist(DWORD dwNpcTemplateID);
    
private:
	typedef std::map<DWORD, KQuestInfo> MAP_ID_2_QUEST_INFO;
	MAP_ID_2_QUEST_INFO					m_mapID2QuestInfo;

#ifdef _SERVER
	typedef std::multimap<DWORD, DWORD>	MAP_NPC_ID_2_QUEST_ID;
	MAP_NPC_ID_2_QUEST_ID				m_mapNpcID2QuestID;						// 保存掉落任务道具的NPC
#endif

	typedef std::multimap<int64_t, DWORD>	MAP_NPC_2_QUEST_INFO;
	MAP_NPC_2_QUEST_INFO				m_mapNpc2QuestInfo;						//保存起始与完成的NPC

	typedef std::multimap<DWORD, DWORD> MAP_DOODAD_ID_2_QUEST_ID;
	MAP_DOODAD_ID_2_QUEST_ID			m_mapDoodadID2QuestID;					//保存掉落任务道具的Doodad

	typedef std::multimap<DWORD, DWORD> MAP_RDOODAD_ID_2_QUEST_ID;
	MAP_RDOODAD_ID_2_QUEST_ID			m_mapRDoodadID2QuestID;					//保存关联Doodad

	KQuestInfo	m_DefaultQuestInfo;		//默认设定
	
    BOOL LoadQuestInfo(ITabFile* piTabFile, int nIndex, KQuestInfo* pQuestInfo);
    BOOL MakeQuestMap(KQuestInfo* cpQuestInfo);

	friend class KDropCenter;
    friend class KDoodad;
};

#endif	//_KQUEST_INFO_LIST_H_
