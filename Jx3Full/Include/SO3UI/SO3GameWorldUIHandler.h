#ifndef SO3_GAME_WORLD_UI_HANDLER_H
#define SO3_GAME_WORLD_UI_HANDLER_H

#include "Global.h"
#include "KTongDef.h"
#include "SO3Result.h"
#include "KAuctionDef.h"

struct KUIEventCharacterSay
{
	char*	pszDialogKey;
	DWORD	dwCharacterID;
	DWORD	dwTalkChannel; 
    DWORD   dwDialogID;

};
 
struct KUIEventItemListUpdate
{
	DWORD dwBoxIndex;
	DWORD dwX;
};

struct KUIEvnetItemExchanged
{
	DWORD dwBox1;
	DWORD dwX1;
	DWORD dwBox2;
	DWORD dwX2;
};

struct KUIEventDestroyItem
{
	DWORD dwBoxIndex;
	DWORD dwX;
	int nVersion;
	int dwTabType;
	int dwIndex;
};

struct KUIEventMoneyUpdate
{
	int nMoney;
    int nPrevMoney;
	BOOL bShowMsg;
};

struct KUIEventContributionUpdate
{
    int nPreContribution;
    int nContribution;
};

struct KUIBuffUpdata
{
    DWORD dwPlayerID;
    BOOL  bDelete;
    int   nIndex;
    BOOL  bCanCancel;
    DWORD dwBuffID;
    int   nBuffLevel;
    int   nCount;
    int   nEndFrame;
    BOOL  bInit;
};

struct KUIEventOpenRecipeBook
{
	DWORD dwItemID;
};

struct KUIEventOpenBook
{
	DWORD dwBookID;
	DWORD dwSubID;
	DWORD dwItemID;
	DWORD dwRecipeID;
};

struct KUIEventUpdateBookState
{
	DWORD dwBookID;
};

struct KUIEventPeekPlayerBookState
{
	DWORD dwPlayerID;
};

struct KUIEventPeekPlayerQuest
{
	DWORD dwPlayerID;
};

struct KUIEventSkillUpdate
{
    DWORD dwSkillID;
    DWORD dwSkillLevel;
};

struct KUIEventCraftUpdate
{
    DWORD dwProfessionID;
};

struct KUIEventCraftRemove
{
	DWORD dwProfessionID;
};

struct KUIEventRecipeUpdate 
{
	DWORD dwProfession;
	DWORD dwCraftID;
	DWORD dwRecipeID;
};

struct KUIEventLearnProfession
{
	DWORD dwProfessionID;
};

struct KUIEventLearnBranch  
{
	DWORD dwProfessionID;
	DWORD dwBranchID;
};

struct KUIEventForgetProfession
{
	DWORD dwProfessionID;
};

struct KUIEventAddProfessionProficiency
{
	DWORD dwProfessionID;
	DWORD dwProficiency;
};

struct KUIEventProfessionLevelUp
{
	DWORD dwProfessionID;
	DWORD dwNewLevel;
};

struct KUIEventSetProfessionAdjustLevel
{
    DWORD dwProfessionID;
    DWORD dwAdjustLevel;
};

struct KUIEventSetProfessionMaxLevel
{
	DWORD dwProfessionID;
	DWORD dwNewMaxLevel;
};

struct KUIEventLearnRecipe
{
	DWORD dwCraftID;
	DWORD dwRecipeID;
};

struct KUIEventReputationRespond
{
    DWORD dwForceID;
    int   nNumber;
};

struct KUIEventCastingBarEnd
{
	SKILL_RESULT_CODE	nResultCode;
};

struct KUIEventCheckOpenDoodad
{
    
};

struct KUIEventOpenDoodad
{
	DWORD	dwDoodadID;
	DWORD	dwPlayerID;
};

struct KUIEventCloseDoodad
{
	DWORD	dwDoodadID;
	DWORD	dwPlayerID;
};

struct KUIEventSyncLootList
{
	DWORD	dwDoodadID;
};

struct KUIEventLootItem
{
	DWORD	dwPlayerID;
	DWORD	dwItemID;
	DWORD	dwCount;
};

struct KUIEventDistributeItem
{
	DWORD	dwPlayerID;
	DWORD	dwItemID;
};

struct KUIEventBeginRollItem
{
	DWORD	dwDoodadID;
	DWORD	dwItemID;
    int     nLeftRollFrame;
};

struct KUIEventRollItem
{
	DWORD	dwPlayerID;
	DWORD	dwItemID;
	int		nRandom;
};

struct KUIEventCancelRollItem
{
	DWORD	dwPlayerID;
	DWORD	dwItemID;
};

struct KUIEventSyncTeamBaseInfo
{
    DWORD dwTeamID;
    DWORD dwLeaderID;
    int   nLootMode;
    int   nRollQuality;
    BOOL  bAddTeamMemberFlag;
};

struct KUIEventTeamDisband
{
    DWORD dwTeamID;
};

struct KUIEventTeamAddMember
{
    DWORD dwTeamID;
    DWORD dwMemberID;
    int   nGroupIndex;
};

struct KUIEventTeamSyncMember
{
    DWORD dwTeamID;
    DWORD dwMemberID;
    int   nGroupIndex;
};

struct KUIEventTeamDelMember
{
    DWORD dwTeamID;
    DWORD dwMemberID;
    char szName[_NAME_LEN];
    int   nGroupIndex;
};

struct KUIEventTeamInviteRequest
{
    char szInviteSrc[_NAME_LEN];
};

struct KUIEventTeamInviteRespond 
{
    char szInviteDst[_NAME_LEN];
    int  nRespondCode;
};

struct KUIEventTeamApplyRequest
{
    char szApplySrc[_NAME_LEN];
};

struct KUIEventTeamApplyRespond
{
    char szApplyDst[_NAME_LEN];
    int  nRespondCode;
};

struct KUIEventTeamMessageNotify 
{
    int     nCode;
    char    szName[_NAME_LEN];
};

struct  KUIEventUpdateTeamMemberInfo
{
    DWORD dwTeamID;
    DWORD dwMemberID;
};

struct  KUIEventUpdateTeamMemberLMR
{
	DWORD dwTeamID;
	DWORD dwMemberID;
};

struct KUIEventSetTeamMemberOnlineFlag
{
    DWORD dwTeamID;
    DWORD dwMemberID;
    BOOL  bOnlineFlag;
};

struct KUIEventTeamLeaderChanged
{
    DWORD dwTeamID;
    DWORD dwNewLeaderID;
};

struct KUIEventTeamAuthorityChanged
{
    int     nAuthorityType;
    DWORD   dwTeamID;
    DWORD   dwOldAuthorityID;
    DWORD   dwNewAuthorityID;
};

struct KUIEventTeamMemberSignpostNotify
{
    int nX;
    int nY;
};
struct KUIEventTeamLootModeChanged
{
    DWORD dwTeamID;
    int   nLootMode;
};

struct KUIEventTeamRollQualityChanged
{
	DWORD	dwTeamID;
	int		nRollQuality;
};

struct  KUIEventSetDistributeMan
{
    DWORD dwDistributeMan;
};

struct  KUIEventSetFormationLeader
{
    DWORD dwFormationLeader;
};

struct KUIEventTeamChangeMemberGroup
{
    DWORD dwMemberID;
    DWORD dwDstMemberID;
    int   nSrcGroupIndex;
    int   nDstGroupIndex;
};

struct KUIEventQuestAccepted
{
    int         nQuestIndex;
	DWORD		dwQuestID;
};

struct KUIEventQuestFailed
{
    int         nQuestIndex;
};

struct KUIEventQuestCanceled
{
	DWORD		dwQuestID;
};

struct KUIEventFinishQuest
{
	DWORD       dwQuestID;
	BOOL        bForceFinish;
    BOOL        bAssist;
    int         nAddStamina;
    int         nAddThew;
};

struct KUIEventQuestShared
{
	DWORD		dwSrcPlayerID;
	DWORD		dwQuestID;
};

struct KUIEventQuestDataUpdate
{
	int			        nQuestIndex;
    QUEST_EVENT_TYPE	eEventType;
    int                 nValue1;
    int                 nValue2;
};

struct KUIEventOpenWindow
{
	DWORD	dwIndex;
	LPCSTR	szText;
	DWORD	dwTargetType;
	DWORD	dwTargetID;
};

struct KUIEventSceneBeginLoad
{
	char szPath[MAX_PATH];
};

struct KUIEventSceneEndLoad
{
	DWORD dwSceneID;
};

struct KUIEventPlayerCustomDataLoaded
{
    DWORD dwPlayerID;
};

struct KUIEventCurrentPlayerForceChanged
{
    DWORD dwCurrentPlayerID;
};

struct KUIEventPlayerStateUpdate
{
	DWORD dwPlayerID;
};

struct KUIEventPlayerWeakUpdate
{
    DWORD dwPlayerID;
};

struct KUIEventPlayerDisplayDataUpdate
{
	DWORD dwPlayerID;
};

struct KUIEventPlayerEnterScene
{
	DWORD dwPlayerID;
};

struct KUIEventPlayerLeaveScene
{
	DWORD dwPlayerID;
};

struct KUIEventNpcStateUpdate
{
	DWORD dwNpcID;
};

struct KUIEventNpcDropTargetUpdate
{
	DWORD dwNpcID;
};

struct KUIEventNpcWeakUpdate
{
    DWORD dwNpcID;
};

struct KUIEventNpcDisplayDataUpdate
{
	DWORD dwNpcID;
};

struct KUIEventNpcEnterScene
{
	DWORD dwNpcID;
};

struct KUIEventNpcLeaveScene
{
	DWORD dwNpcID;
};

struct KUIEventNpcTalk
{
    DWORD   dwNpcID;
	DWORD	dwTalkChannel;
    DWORD   dwDialogID;
	char*	pszDialogKey;
};

struct KUIEventDoodadEnterScene
{
	DWORD dwDoodadID;
};

struct KUIEventDoodadLeaveScene
{
	DWORD dwDoodadID;
};

struct KUIEventShopOpenNotify
{
    DWORD     dwShopID;
    int       nShopType;
    DWORD     dwValidPage;
    bool      bCanRepair;
    DWORD     dwNpcID;
};

struct KUIEventShopUpdateItem
{
    DWORD     dwShopID;      
    DWORD     dwPageIndex;  
    DWORD     dwPos;      
};

struct KUIEventTradingInvite
{
    DWORD dwTradingInviter; 
};

struct KUIEventTradingOpenNotify
{
    DWORD dwCharacterID;    // 交易的另一方ID(相对客户端玩家)
};

struct KUIEventTradingUpdateConfirm
{
    DWORD dwCharacterID;
    BOOL  bConfirm;
};

struct KUIEventTradingUpdateItem
{
    DWORD dwCharacterID;
	DWORD dwBoxIndex;
	DWORD dwPosIndex;
    DWORD dwGridIndex;
};

struct KUIEventTradingUpdateMoney
{
    DWORD dwCharacterID;
    int   nMoney;
};

struct KUIEventTradingClose
{
};


struct KUIEventPlayerTalk 
{
    DWORD dwTalkerID;
    DWORD dwTalkChannel;
    BOOL  bEcho;   // 在密聊时,这项表示是否Echo消息
    char  szName[_NAME_LEN]; // 不同的情况不同解释,比如一般指Talker,但是密聊Echo时指Receiver
};

struct KUIEventNpcTalkUseSentenceID 
{
    DWORD   dwTalkerID;
    DWORD   dwTalkChannel;
    char    szTalkerName[_NAME_LEN];
    DWORD   dwSentenceID;
};

////////////////////////////////////////////////////////////////////////////////
//输出消息的事件最好都放在这里,这个都会调用"SYS_MSG"这个事件，
//第一个参数就是消息分类的名称
///////////////////////////////////////////////////////////////////////////////
struct KUIEventSysErrorMsg
{
	char*	pszText;
};

struct KUIEventSkillCastLog
{
    DWORD   dwCaster;
    DWORD   dwSkillID;
    DWORD   dwLevel;
};

struct KUIEventSkillCastRespondLog
{
    DWORD   dwCaster;
    DWORD   dwSkillID;
    DWORD   dwLevel;
    int     nRespond;
};

struct KUIEventSkillEffectLog
{
	DWORD		dwCaster;
	DWORD		dwTarget;
    BOOL        bReact;
    int         nType;
    DWORD       dwID;
    DWORD       dwLevel;
    BOOL        bCriticalStrike;
    int         nDamageType;
    int         nValue;
};

struct KUIEventSkillBlockLog
{
    DWORD dwCaster;
    DWORD dwTarget;
    int   nType;
    DWORD dwID;
    DWORD dwLevel;
    int   nDamageType;
};

struct KUIEventSkillShieldLog
{
    DWORD dwCaster;
    DWORD dwTarget;
    int   nType;
    DWORD dwID;
    DWORD dwLevel;
};

struct KUIEventSkillMissLog
{
    DWORD dwCaster;
    DWORD dwTarget;
    int   nType;
    DWORD dwID;
    DWORD dwLevel;
};

struct KUIEventSkillHitLog
{
    DWORD dwCaster;
    DWORD dwTarget;
    int   nType;
    DWORD dwID;
    DWORD dwLevel;
};

struct KUIEventSkillDodgeLog 
{
    DWORD dwCaster;
    DWORD dwTarget;
    int   nType;
    DWORD dwID;
    DWORD dwLevel;
};

struct KUIEventExpLog 
{
    DWORD dwPlayerID;
    int   nAddExp;
};

struct KUIEventCommonHealthLog 
{
    DWORD dwCharacterID;
    int   nDeltaLife;
};

struct KUIEventCommonHealthText 
{
    DWORD dwCharacterID;
    int   nDeltaLife;
};

struct KUIEventBuffLog
{
    DWORD dwTarget;
    BOOL  bCanCancel;
    DWORD dwID;
    int   nLevel;
    BOOL  bAddOrDel;
};

struct KUIEventBuffImmunityLog
{
    DWORD dwTarget;
    BOOL  bCanCancel;
    DWORD dwID;
    int   nLevel;
};

struct KUIEventCharacterDeath
{
    DWORD dwCharacterID;
    char  szKiller[_NAME_LEN];
};

struct KUISyncPlayerRevive
{
    BOOL    bReviveInSite;
    BOOL    bReviveInAlter;
    BOOL    bReviveByPlayer;
    int     nLeftReviveFrame;
    DWORD   dwReviver;
    int     nMessageID;
};

struct KUIEventFightHint
{
    BOOL bFight;
};

struct KUIEventSkillEffectText
{
	DWORD	dwCasterID;
    DWORD   dwTargetID;
    DWORD   dwSkillID;
    DWORD   dwSkillLevel;
    BOOL    bCriticalStrike;
    int     nType;
    int     nValue;
};

struct KUIEventSkillBlockText
{
    DWORD dwCasterID;
    DWORD dwTargetID;
};

struct KUIEventSkillMissText
{
	DWORD dwCasterID;
	DWORD dwTargetID;
};

struct KUIEventSkillBuffText
{
    DWORD dwCharacterID;
    BOOL  bCanCancel;
    DWORD dwID;
    int   nLevel;
};

struct KUIEventBuffImmunityText
{
    DWORD dwCharacterID;
};

struct KUIEventSkillDodgeText
{
    DWORD dwCasterID;
	DWORD dwTargetID;
};

struct KUIEventSkillCastRespond
{
    int nRespondCode;
};

struct KUIEventItemUseRespond
{
	int     nRespondCode;
};

struct KUIEventAddItemRespond
{
	int     nRespondCode;
    char    szItemName[ITEM_NAME_LEN];
};

struct KUIEventUseItemRespond
{
	int     nRespondCode;
    DWORD   dwProfessionID;
    DWORD   dwProfessionBranchID;
    DWORD   dwProfessionLevel;
};

struct KUIEventTradingRespond
{
    int nRespondCode;
};

struct KUIEventLootRespond
{
	int nRespondCode;
};

struct KUIEventCraftCastRespond
{
	int		nCraftCastRespond;
	DWORD	dwCraftID;
	DWORD	dwRecipeID;
	DWORD	dwTargetType;
	DWORD	dwTargetID;
};

struct KUIEventQuestRespond
{
    DWORD   dwQuestID;
	int     nQuestRespond;
};

struct KUIEventLoginNotify
{
	int     nEvent;
    char    szMatrixPosition[9];
};

struct KUIEventLoginQueueState
{
	int nPosition;
};

struct KUIEventSkillProgress 
{
    int     nTotalFrame;
    DWORD   dwSkillID;
    DWORD   dwSkillLevel;
};

struct KUIEventRecipeProgress
{
	int		nTotalFrame;
	DWORD	dwCraftID;
	DWORD	dwRecipeID;
};

struct KUIEventPickProgress
{
    int     nTotalFrame;
    DWORD   dwDoodadID;
};

struct KUIEventCustomOTActionProgress
{
	int		nTotalFrame;
	char	szActionName[CUSTOM_OTACTION_NAME_LEN];
	int		nType;
};

struct KUIEventShopRespond
{
    int nRespondCode;
    int nMoney;
};

struct KUIEventPKRespond
{
	int nRespondCode;
};
// ----------------------------------------------------------------------------

struct KUIEventMailRespond
{
    int     nRespondCode;
};

struct KUIEventSendMailResult
{
    int     nIndex;
    int     nResult;
};

struct KUIEventMailListUpdate
{
	int     nUnreadCount;
	int     nTotalCount;
};

struct KUIEventGetMailContent
{
    DWORD   dwMailID;
};

struct KUIEventNewMailNotify
{
    int     nUnreadCount;
    int     nTotalCount;
};

// ----------------------------------------------------------------------------

struct KUIEventResponseMsg 
{
    int nRespondCode;
};

struct KUIEventFellowshipRespond
{
    int  nFellowshipRespond;
};

struct KUIEventFellowshipChange
{
    int   nRespondCode;
    DWORD dwPlayerID;
    DWORD dwValue1;
    DWORD dwValue2;
    char  szName[_NAME_LEN];
};

struct KUIEventBeAddFellowship
{
    int   nRespondCode;
    DWORD dwPlayerID;
    char  szName[_NAME_LEN];
};

struct KUIEventFellowshipNotify
{
    bool bLoad;
    bool bFoe;
    char szName[_NAME_LEN];
};

struct KUIEventAddFellowshipAttraction
{
    char    szAlliedPlayerName[_NAME_LEN];
    int     nAttaction;
};

struct KUIEventUpdateMiniMapNpcMark
{
	DWORD dwNpcID;
	int nX;
	int nY;
};

struct KUIEventUpdateMiniMapDoodadMark
{
	DWORD dwDoodadID;
	int nX;
	int nY;
	int nParam;
};

struct KUIEventUpdateRelation
{
	DWORD dwCharacterID;
};

struct KUIEventApplyDuel
{
	DWORD dwSrcPlayerID;
	DWORD dwDstPlayerID;
};

struct KUIEventAcceptDuel
{
	DWORD dwSrcPlayerID;
	DWORD dwDstPlayerID;
    int   nEndFrame;
};

struct KUIEventRefuseDuel
{
	DWORD dwSrcPlayerID;
	DWORD dwDstPlayerID;
};

struct KUIEventStartDuel
{
	DWORD dwTargetPlayerID;
};

struct KUIEventCancelDuel
{
	DWORD dwTargetPlayerID;
};

struct KUIEventWinDuel
{
	DWORD dwWinnerID;
	DWORD dwLosserID;
};

struct KUIEventSlayInfo
{
	DWORD dwPlayerID;
    int   nSeconds;
};

struct KUIEventOpenBank
{
	DWORD dwNpcID;
};

struct KUIEventUpdateMapMark
{
	int nX;
	int nY;
	int nZ;
	int nType;
	char szComment[MAX_MAP_MARK_COMMENT_LEN];
};

struct KUIEventUpdateRegionInfo
{
	DWORD dwRegionInfo;
};

struct KUIEventPlayMiniGame
{
	DWORD dwGameID;
};


struct KUIEventPlayerQiUpdate
{
    DWORD dwPlayerID;
};

struct KUIEventPlayerExperienceUpdate
{
    DWORD dwPlayerID;
};

struct KUIEventPlayerLevelUpdate
{
    DWORD dwPlayerID;
	int nLevel;
	int	nStrength;		// 力量
	int	nAgility;		// 身法
	int	nVigor;			// 体质
	int	nSpirit;		// 根骨
    int nSpunk;			// 精神
	int	nMaxLife;
	int	nMaxMana;
    int nMaxRage;
    int nMaxStamina;	// 精力
    int nMaxThew;       // 体力

};

struct KUIEventUpdateMidMapMark
{
	int nMapID;
	int nX;
	int nY;
	int nType;
	char szComment[MAX_MIDMAP_MARK_COMMENT_LEN];
};

struct KUIEventStartEscortQuest
{
	DWORD dwStartPlayerID;
	DWORD dwQuestID;
};

struct KUIEventQuestTimeUpdate
{
	int nQuestIndex;
	int nLastTime;
};

struct KUIEventQuestMarkUpdate
{
    DWORD dwNpcID;
};

struct KUIEventUpdateRadar
{
	DWORD dwRadarType;
	DWORD dwRadarParam;
};

struct KUIEventUpdateReputation
{
	DWORD dwForceID;
	BOOL  bNewForce;	
};

struct KUIEventReputationLevelUp
{
	DWORD dwForceID;
    BOOL bLevelUp; // false 为 degrade
};

struct KUIEventPeekOtherPlayer 
{
    int     nResult;
    DWORD   dwPlayerID;
};

struct KUIEventBanishPlayer 
{
    int nBanishCode;
    int nLeftSeconds;
};

struct KUIEventRoadTrackErrorID
{
    int nErrorID;
};

struct KUIEventTrainValueUpdate
{
    int nAddTrain;
};

struct KUIEventSwitchMapResult 
{
    int nErrorID;
};

struct KUIEventCastCommonSkill
{
    BOOL bEnterOrLeaveCast;
};

struct KUIEventOpenVenationRetCode
{
    BOOL bOpenVenationRetCode;
    int  nVenationID;
};

struct KUIEventShareQuestResult 
{
    DWORD   dwQuestID;
    DWORD   dwDestPlayerID;
    int     nResultCode;
};

struct KUIEventUpdatePlayerSchoolID
{
    DWORD   dwPlayerID;
    DWORD   dwSchoolID;
};

struct KUIEventFinishAssistQuest
{
    char    szName[_NAME_LEN];
    DWORD   dwQuestID;
};

struct KUIEventKillPoint
{
	DWORD   dwPlayerID;
	DWORD   dwPoint;
};

struct KUIAddSkillRecipe
{
    DWORD   dwRecipeID;
    DWORD   dwRecipeLevel;
};

struct KUIEventJoinBattleFieldQueue
{
    DWORD   dwMapID;
    int     nErrorCode;
};

struct KUIEventLeaveBattleFieldQueue
{
    DWORD   dwMapID;
    int     nErrorCode;
};

struct KUIEventBattleFieldNotify
{
    int     nType;
    int     nAvgQueueTime;
    int     nPassTime;
    DWORD   dwMapID;
    int     nCopyIndex;
};

struct KUIEventUpdateBattleFieldList
{
    DWORD dwMapID;
    int   nCopyIndex;
};

struct KUIEventInviteJoinTongRequest
{
    DWORD dwInviterID;
    DWORD dwTongID;
    char  szInviterName[_NAME_LEN];
    char  szTongName[_NAME_LEN];
};

struct KUIEventAuctionLookupRespond
{
    int nApplyType;
    int nRespondCode;
};

struct KUIEventAuctionCommonRespond
{
    int nRespondCode;
};

struct KUIEventAuctionMessageNotify 
{
    int     nNotifyCode;
    char    szSaleName[SALE_NAME_LEN];
    int     nPrice;
};

struct KUIEventChangeTongNotify
{
    KCHANGE_TONG_REASON eReason;
    char                szTongName[_NAME_LEN];
};

struct KUIEventTongNotify
{   
    int   nEventCode;
    char* pszRoleName;
};

struct KUIEventTongStateChange
{
    int nTongState;
};

struct KUIEventTongGroupRightChange
{
    char szGroupName[_NAME_LEN];
};

struct KUIEventTongGroupNameChange
{
    char szOldGroupName[_NAME_LEN];
    char szNewGroupName[_NAME_LEN];
};

struct KUIEventTongGroupWageChange
{
    char szGroupName[_NAME_LEN];
    int  nWage;
};

struct KUIEventTongMemberJoinOrQuit
{
    char szMemberName[_NAME_LEN];
    int  nType;
};

struct KUIEventTongMemberChangeGroup
{
    char szMemberName[_NAME_LEN];
    char szOldGroupName[_NAME_LEN];
    char szNewGroupName[_NAME_LEN];
};

struct KUIEventTongMasterChange
{
    char szOldMasterName[_NAME_LEN];
    char szNewMasterName[_NAME_LEN];
};

struct KUIEventTongMemberOnlineStateChange
{
    char szMemberName[_NAME_LEN];
    BOOL bIsOnline;
};

struct KUIEventTongGroupEnabled
{
    char szGroupName[_NAME_LEN];
};

struct KUIEventTongMaxMemberCountChange
{
    int nMaxMemberCount;
};

struct KUIEventShowTongOnlineMessage
{
    char* pszOnlineMessage;
};

struct KUIEventOpenTongRepertory
{
    char szTongName[_NAME_LEN];
    int  nEnabledPageNum;
};

struct KUIEventCampInfo 
{
    int nResult;
};

struct KUIEventChargeLimitNotify
{
    int nCode;
};

struct KUIEventUpdatePrestige 
{
    int nOldPrestige;
};

struct KUIEventChangeCamp 
{
    DWORD dwPlayerID;
};

struct KUIEventSyncAchievementData
{
    DWORD   dwPlayerID;
};

struct KUIEventNewAchievement 
{
    int     nAchievementID;
};

struct KUIEventAchievementAnnounce 
{
    char    szRoleName[_NAME_LEN];
    BYTE    byType;
    int     nAchievementID;
};

struct KUIEventSyncDesignationData
{
    DWORD   dwPlayerID;
};

struct KUIEventSetGeneration
{
    DWORD   dwPlayerID;
    int     nGenerationIndex;
    int     nNameInForceIndex;
};

struct KUIEventAcquireDesignation
{
    int     nPrefix;
    int     nPostfix;
};

struct KUIEventDesignationAnnounce
{
    char    szRoleName[_NAME_LEN];
    int     nPrefix;
    int     nPostfix;
    BYTE    byType;
};

struct KUIEventRemoveDesignation
{
    DWORD   dwPlayerID;
    int     nPrefix;
    int     nPostfix;
};

struct KUIEventSetCurrentDesignationRespond
{
    DWORD   dwPlayerID;
    int     nPrefix;
    int     nPostfix;
    BOOL    bDisplayFlag;
};


struct KUIEventStopAutoMove
{
    char* pszReason;
    DWORD dwTargetType;
    DWORD dwTargetID;
};

struct KUIEventReachPoint
{
    float fX;
    float fY;
    float fZ;
};

struct KUIEventUpdateTongRepertoryPage
{
    int nPageIndex;
};

struct KUIEventOptimizationHint
{
    DWORD dwLevel;
    DWORD dwFPS;
};

struct KUIEventGameCardSellRespond 
{
    BYTE byCode;
};

struct KUIEventGameCardBuyRespond 
{
    BYTE byCode;
};

struct KUIEventGameCardCancelRespond 
{
    BYTE byCode;
};

struct KUIEventSeekMentorYell
{
    char szPlayerName[_NAME_LEN];
    char szTongName[_NAME_LEN];
    BYTE byForceID;
    BYTE byRoleLevel;
    BYTE byRoleType;
};

struct KUIEventSeekApprenticeYell
{
    char szPlayerName[_NAME_LEN];
    char szTongName[_NAME_LEN];
    BYTE byForceID;
    BYTE byRoleLevel;
    BYTE byRoleType;
};

struct KUIEventMentorValueChange
{
    int nValueChange;
};

struct KUIThreatRankList
{
    DWORD   dwCharacterID;
    int     nRank;
};

enum UI_OUTPUT_MESSAGE_EVENT_TYPE
{
    UI_OME_SKILL_CAST_LOG,
    UI_OME_SKILL_CAST_RESPOND_LOG,
    UI_OME_SKILL_EFFECT_LOG,                // 技能最终产生的效果(生命值变化)
    UI_OME_SKILL_BLOCK_LOG,                 // 格挡    
    UI_OME_SKILL_SHIELD_LOG,                // 技能被屏蔽
    UI_OME_SKILL_MISS_LOG,                  // 技能未命中目标
    UI_OME_SKILL_HIT_LOG,                   // 技能命中目标
    UI_OME_SKILL_DODGE_LOG,                 // 技能被闪避
    UI_OME_BUFF_LOG,                        // 获得或失去技能 
    UI_OME_BUFF_IMMUNITY,
    UI_OME_EXP_LOG,  
    UI_OME_COMMON_HEALTH_LOG,  
    UI_OME_DEATH_NOTIFY,                    // 角色死亡
    UI_OME_SKILL_RESPOND,                   // 技能释放响应码(失败的时候)

	UI_OME_ITEM_RESPOND,		            // 物品操作响应代码(失败的时候)
    UI_OME_ADD_ITEM_RESPOND,
    UI_OME_USE_ITEM_RESPOND,		         
    UI_OME_TRADING_RESPOND,
    UI_OME_SHOP_RESPOND,                    // 商店响应码
	UI_OME_PK_RESPOND,
    UI_OME_MAIL_RESPOND,
    UI_OME_MAIL_COUNT_INFO,
	UI_OME_CHAT_RESPOND,					// 聊天响应
	UI_OME_LOOT_RESPOND,					// 拾取的响应代码
	UI_OME_CRAFT_RESPOND,					// 生活技能响应代码
	UI_OME_QUEST_RESPOND,					// 任务相应代码
    UI_OME_FELLOWSHIP_RESPOND,              // 好友相应代码

	//生活技能学习提示信息
	UI_OME_LEARN_PROFESSION,
	UI_OME_LEARN_BRANCH,
	UI_OME_FORGET_PROFESSION,
	UI_OME_ADD_PROFESSION_PROFICIENCY,
	UI_OME_PROFESSION_LEVEL_UP,
    UI_OME_SET_PROFESSION_ADJUST_LEVEL,
	UI_OME_SET_PROFESSION_MAX_LEVEL,
	UI_OME_LEARN_RECIPE,

    //声望变化提示信息
    UI_OME_REPUTATION,

	//切磋相关的提示信息
	UI_OME_APPLY_DUEL,
	UI_OME_ACCEPT_DUEL,
	UI_OME_REFUSE_DUEL,
	UI_OME_START_DUEL,
	UI_OME_CANCEL_DUEL,
    UI_OME_FINISH_DUEL,
	UI_OME_WIN_DUEL,

	//屠杀相关的提示信息
	UI_OME_APPLY_SLAY,
    UI_OME_START_SLAY,
	UI_OME_CLOSE_SLAY,
	UI_OME_SLAY_CLOSED,

	UI_OME_LEVEL_UP,

    UI_OME_BANISH_PLAYER,
    
    UI_OME_CHECK_OPNE_DOODAD,

    UI_UPDATE_ACCUMULATE_VALUE,

	UI_OME_SYS_ERROR,
};

#ifndef MAKE_UI_OUTPUT_MESSAGE_EVENT_TYPE_STR
#define MAKE_UI_OUTPUT_MESSAGE_EVENT_TYPE_STR(id) (#id)
#endif


class IKSO3GameWorldUIHandler
{
public:
	virtual~IKSO3GameWorldUIHandler() {}
	virtual void Release() {}

	virtual BOOL GetPassword(LPCSTR szTreePath, char szDestMD5String[64]) { return FALSE; }

    virtual void OnCharacterSay(KUIEventCharacterSay const& param) {}
	virtual void OnItemListUpdate(KUIEventItemListUpdate const& param) {}
	virtual void OnItemExchanged(KUIEvnetItemExchanged const& param) {}
	virtual void OnDestroyItem(KUIEventDestroyItem const& Param) {}

	virtual void OnMoneyUpdate(KUIEventMoneyUpdate const& param) {}
    virtual void OnContributionUpdate(KUIEventContributionUpdate const& param) {}
    virtual void OnSkillUpdate(KUIEventSkillUpdate const& param) {}
	virtual void OnSkillExpUpdate(KUIEventSkillUpdate const& param) {}
    virtual void OnCastingBarStart() {}
    virtual void OnCastingBarEnd(KUIEventCastingBarEnd const& param) {}

	virtual void OnCraftUpdate(KUIEventCraftUpdate const& param) {}		
	virtual void OnCraftRemove(KUIEventCraftRemove const& param) {}
	virtual void OnRecipeUpdate(KUIEventRecipeUpdate const& param) {}

	virtual void OnLearnProfession(KUIEventLearnProfession const& param) {}
	virtual void OnLearnBranch(KUIEventLearnBranch const& param) {}
	virtual void OnForgetProfession(KUIEventForgetProfession const& param) {}
	virtual void OnAddProfessionProficiency(KUIEventAddProfessionProficiency const& param) {}
	virtual void OnProfessionLevelUp(KUIEventProfessionLevelUp const& param) {}
    virtual void OnSetProfessAdjustLevel(KUIEventSetProfessionAdjustLevel const& param) {}
	virtual void OnSetProfessionMaxLevel(KUIEventSetProfessionMaxLevel const& param) {}
	virtual void OnLearnRecipe(KUIEventLearnRecipe const& param) {} 
    virtual void OnReputationRespond(KUIEventReputationRespond const& param) {}

	virtual void OnOpenDoodad(KUIEventOpenDoodad const& param) {}
	virtual void OnCloseDoodad(KUIEventCloseDoodad const& param) {}
	virtual void OnSyncLootList(KUIEventSyncLootList const& param) {}
	virtual void OnLootItem(KUIEventLootItem const& param) {}
    virtual void OnDistributeItem(KUIEventDistributeItem const& param) {};
	virtual void OnBeginRollItem(KUIEventBeginRollItem const& param) {}
	virtual void OnRollItem(KUIEventRollItem const& param) {}
	virtual void OnCancelRollItem(KUIEventCancelRollItem const& param) {}

    virtual void OnSyncTeamBaseInfo(KUIEventSyncTeamBaseInfo const& param) {}
    virtual void OnSyncTeamMemberData(KUIEventTeamSyncMember const& param) {}
    virtual void OnTeamAddMember(KUIEventTeamAddMember const& param) {}
    virtual void OnTeamDelMember(KUIEventTeamDelMember const& param) {}
    virtual void OnTeamInviteRequest(KUIEventTeamInviteRequest const& param) {}
    virtual void OnTeamApplyRequest(KUIEventTeamApplyRequest const& param) {}
    virtual void OnTeamMessageNotify(KUIEventTeamMessageNotify const& param) {}
    virtual void OnUpdateTeamMemberInfo(KUIEventUpdateTeamMemberInfo const& param) {}
    virtual void OnTeamLootModeChanged(KUIEventTeamLootModeChanged const& param) {}
	virtual void OnTeamRollQualityChanged(KUIEventTeamRollQualityChanged const& param) {}
    virtual void OnSetTeamMemberOnlineFlag(KUIEventSetTeamMemberOnlineFlag const& param) {}
    virtual void OnTeamDisband(KUIEventTeamDisband const& param) {}
    virtual void OnTeamLeaderChanged(KUIEventTeamLeaderChanged const& param) {}
    virtual void OnTeamAuthorityChanged(KUIEventTeamAuthorityChanged const& param) {}
    virtual void OnTeamMemberSignpostNotify(KUIEventTeamMemberSignpostNotify const& param) {}
	virtual void OnUpdateTeamMemberLMR(KUIEventUpdateTeamMemberLMR const& param) {}
	virtual void OnUpdateTeamMemberPosition(KUIEventUpdateTeamMemberInfo const& param) {}
    virtual void OnTeamSetDistributeManNotify(KUIEventSetDistributeMan const& param) {}
    virtual void OnTeamSetFormationLeaderNotify(KUIEventSetFormationLeader const& param) {}
	virtual void OnTeamSetMark() {}
    virtual void OnTeamCampChange() {}
    virtual void OnTeamLevelUpRaid() {}
    virtual void OnTeamChangeMemberGroup(KUIEventTeamChangeMemberGroup const& param) {};

	virtual void OnQuestAccepted(KUIEventQuestAccepted const& param) {}
    virtual void OnQuestFailed(KUIEventQuestFailed const& param) {}
	virtual void OnQuestCanceled(KUIEventQuestCanceled const& param) {}
	virtual void OnFinishQuest(KUIEventFinishQuest const& param) {}
	virtual void OnQuestShared(KUIEventQuestShared const& param) {}
	virtual void OnQuestDataUpdate(KUIEventQuestDataUpdate const& param) {}
	virtual void OnQuestListUpdate(void) {}
	virtual void OnStartEscortQuest(KUIEventStartEscortQuest const& param) {}
	virtual void OnQuestTimeUpdate(KUIEventQuestTimeUpdate const& param) {}
    virtual void OnQuestMarkUpdate(KUIEventQuestMarkUpdate const& param) {};

	virtual void OnSysMsg(KUIEventSysErrorMsg const& param) {}
	virtual void OnOpenWindow(KUIEventOpenWindow const& param) {}

	virtual void OnSceneBeginLoad(KUIEventSceneBeginLoad const& param) {}
	virtual void OnSceneEndLoad(KUIEventSceneEndLoad const& param) {}

	virtual void OnPlayerExperienceUpdate(KUIEventPlayerExperienceUpdate const& param) {}
    virtual void OnPlayerLevelUpdate(KUIEventPlayerLevelUpdate const& param) {}

    virtual void OnSyncRoleDataBegin() {}
    virtual void OnSyncRoleDataEnd() {}

	virtual void OnCurrentPlayerForceChanged(KUIEventCurrentPlayerForceChanged const& param) {}

	virtual void OnPlayerStateUpdate(KUIEventPlayerStateUpdate const& param) {}
    virtual void OnPlayerWeakUpdate(KUIEventPlayerWeakUpdate const& param) {}
	virtual void OnPlayerDisplayDataUpdate(KUIEventPlayerDisplayDataUpdate const& param) {}
	virtual void OnPlayerEnterScene(KUIEventPlayerEnterScene const& param) {}
	virtual void OnPlayerLeaveScene(KUIEventPlayerLeaveScene const& param) {}
    virtual void OnPlayerTalk(KUIEventPlayerTalk const& param) {}
    virtual void OnNpcTalkUseSentenceID(KUIEventNpcTalkUseSentenceID const& param) {}

    virtual void OnFellowshipUpdate() {}
    virtual void OnFoeUpdate() {}
    virtual void OnBlackListUpdate() {}
    virtual void OnFellowshipRespond(KUIEventFellowshipRespond const& param) {}
    virtual void OnFellowshipChange(KUIEventFellowshipChange const& param) {}
    virtual void OnFellowshipLogin(KUIEventFellowshipNotify const& param) {}
    virtual void OnAddFellowshipAttraction(KUIEventAddFellowshipAttraction const& param) {}
    virtual void OnFellowshipAttractionFallOff() {}
    virtual void OnBeAddFellowship(KUIEventBeAddFellowship const& param) {}

    virtual void OnNpcStateUpdate(KUIEventNpcStateUpdate const& param) {}
	virtual void OnNpcDropTargetUpdate(KUIEventNpcDropTargetUpdate const& param) {}
    virtual void OnNpcWeakUpdate(KUIEventNpcWeakUpdate const& param) {}
	virtual void OnNpcDisplayDataUpdate(KUIEventNpcDisplayDataUpdate const& param) {}
	virtual void OnNpcEnterScene(KUIEventNpcEnterScene const& param) {}
	virtual void OnNpcLeaveScene(KUIEventNpcLeaveScene const& param) {}
    virtual void OnNpcTalk(KUIEventNpcTalk const& param) {}

	virtual void OnDoodadEnterScene(KUIEventDoodadEnterScene const& param) {}
	virtual void OnDoodadLeaveScene(KUIEventDoodadLeaveScene const& param) {}

    virtual void OnShopUpdateItem(KUIEventShopUpdateItem const& param) {}
	virtual void OnShopOpenNotify(KUIEventShopOpenNotify const& param) {}

    virtual void OnTradingInvite(KUIEventTradingInvite const& param) {}
    virtual void OnTradingOpenNotify(KUIEventTradingOpenNotify const& param) {}
    virtual void OnTradingUpdateConfirm(KUIEventTradingUpdateConfirm const& param) {}
    virtual void OnTradingUpdateItem(KUIEventTradingUpdateItem const& param) {}
    virtual void OnTradingUpdateMoney(KUIEventTradingUpdateMoney const& param) {}
    virtual void OnTradingClose(KUIEventTradingClose const& param) {}

    virtual void OnSkillCastLog(KUIEventSkillCastLog const& param) {}
    virtual void OnSkillCastRespondLog(KUIEventSkillCastRespondLog const& param) {}
    virtual void OnSkillEffectLog(KUIEventSkillEffectLog const& param) {}		// 在战斗记录里面写日志
    virtual void OnSkillBlockLog(KUIEventSkillBlockLog const& param) {}
    virtual void OnSkillShieldLog(KUIEventSkillShieldLog const& param) {}
    virtual void OnSkillMissLog(KUIEventSkillMissLog const& param) {}
    virtual void OnSkillHitLog(KUIEventSkillHitLog const& param) {}
    virtual void OnSkillDodgeLog(KUIEventSkillDodgeLog const& param) {}			// 在战斗记录里面写日志

    virtual void OnBuffLog(KUIEventBuffLog const& param) {}
    virtual void OnBuffImmunityLog(KUIEventBuffImmunityLog const& param) {}
    virtual void OnExpLog(KUIEventExpLog const& param) {}

    virtual void OnCommonHealthLog(KUIEventCommonHealthLog& param) {}
    virtual void OnCommonHealthText(KUIEventCommonHealthText& param) {}

    virtual void OnCharacterDeath(KUIEventCharacterDeath const& param) {}
    virtual void OnClientPlayerDeath() {}
    virtual void OnSyncPlayerRevive(KUISyncPlayerRevive const& param) {}

    virtual void OnFightHint(KUIEventFightHint const& param) {}
	virtual void OnSkillEffectText(KUIEventSkillEffectText const& param) {} 
    virtual void OnSkillMissText(KUIEventSkillMissText const& param) {}
    virtual void OnSkillBlockText(KUIEventSkillBlockText const& param) {}
    virtual void OnSkillBuffText(KUIEventSkillBuffText const& param) {}
    virtual void OnBuffImmunityText(KUIEventBuffImmunityText const& param) {}
    virtual void OnSkillDodgeText(KUIEventSkillDodgeText const& param) {}
    virtual void OnSkillCastRespond(KUIEventSkillCastRespond  const& param) {}

	virtual void OnSkillMountKungFu(KUIEventSkillUpdate const& param) {}
	virtual void OnSkillUnmountKungfu(KUIEventSkillUpdate const& param) {}

    virtual void OnBuffUpdata(KUIBuffUpdata const & param) {}

	virtual void OnOpenRecipeBook(KUIEventOpenRecipeBook const& param) {}
	virtual void OnOpenBook(KUIEventOpenBook const& param) {}
	virtual void OnUpdateBookState(KUIEventUpdateBookState const& param) {}
    virtual void OnPeekPlayerBookState(KUIEventPeekPlayerBookState const& param) {}
    virtual void OnPeekPlayerQuest(KUIEventPeekPlayerQuest const& param) {}

    virtual void OnSkillPrepareProgress(KUIEventSkillProgress const& param) {}
    virtual void OnSkillChannelProgress(KUIEventSkillProgress const& param) {}
    virtual void OnSkillAccumulateProgress(KUIEventSkillProgress const& param) {}
    virtual void OnSkillCast(KUIEventSkillCastLog const& param) {}

    virtual void OnSkillAccumulateSuccess(KUIEventSkillProgress const& param) {}

	virtual void OnRecipePrepareProgress(KUIEventRecipeProgress const& param) {}

    virtual void OnOTActionProgressUpdate(int nFrame) {} // 进度条打退,其实是增加或者缩减总共的进度条时间
    virtual void OnOTActionProgressBreak(DWORD dwCharacterID) {}            // 进度条打断
    virtual void OnPickPrepareProgress(KUIEventPickProgress const& param) {}

	virtual void OnCustomOTActionProgress(KUIEventCustomOTActionProgress const& param) {}

	virtual void OnItemUseRespond(KUIEventItemUseRespond  const& param) {}
    virtual void OnAddItemRespond(KUIEventAddItemRespond  const& param) {}
    virtual void OnUseItemRespond(KUIEventUseItemRespond  const& param) {}

    virtual void OnTradingRespond(KUIEventTradingRespond const& param) {}

	virtual void OnLootRespond(KUIEventLootRespond const& param) {}

	virtual void OnCraftCastRespond(KUIEventCraftCastRespond const& param) {}

	virtual void OnQuestRespond(KUIEventQuestRespond const& param) {}

	virtual void OnLoginNotify(KUIEventLoginNotify const& param) {}
    virtual void OnLoginQueueState(KUIEventLoginQueueState const& param) {}

    virtual void OnShopRespond(KUIEventShopRespond const& param) {}
	virtual void OnPKRespond(KUIEventPKRespond const& param) {}
    
    virtual void OnSendMailResult(KUIEventSendMailResult const& param) {}
    virtual void OnMailRespond(KUIEventMailRespond const& param) {}
	virtual void OnMailListUpdate(KUIEventMailListUpdate const& param) {}
    virtual void OnGetMailContent(KUIEventGetMailContent const& param) {}
    virtual void OnGetGmMessageMail(KUIEventGetMailContent const& param) {}
    virtual void OnGetPlayerMessageMail(KUIEventGetMailContent const& param) {}
    virtual void OnNewMailNotify(KUIEventNewMailNotify const& param) {}

    virtual void OnUpdateSelectTarget() {}

    virtual void OnResponseMsg(KUIEventResponseMsg const& param) {}

	virtual void OnUpdateMiniMapNpcMark(KUIEventUpdateMiniMapNpcMark const& param) {}
	virtual void OnUpdateMiniMapDoodadMark(KUIEventUpdateMiniMapDoodadMark const& param) {}

	virtual void OnUpdateRelation(KUIEventUpdateRelation const& param) {}
	virtual void OnUpdateAllRelation() {}
	virtual void OnUpdateKillPoint(KUIEventKillPoint const& Param) {}

	virtual void OnApplyDuel(KUIEventApplyDuel const& param) {}
    virtual void OnLeaveDuel() {}
    virtual void OnReturnDuel() {}
	virtual void OnAcceptDuel(KUIEventAcceptDuel const& param) {}
	virtual void OnRefuseDuel(KUIEventRefuseDuel const& param) {}
	virtual void OnStartDuel(KUIEventStartDuel const& param) {}
	virtual void OnCancelDuel(KUIEventCancelDuel const& param) {}
    virtual void OnFinishDuel(){}
	virtual void OnWinDuel(KUIEventWinDuel const& param) {}
	
	virtual void OnApplySlay(KUIEventSlayInfo const& param) {}
    virtual void OnStartSlay(KUIEventSlayInfo const& param) {}
	virtual void OnCloseSlay(KUIEventSlayInfo const& param) {}
	virtual void OnSlayClosed(KUIEventSlayInfo const& param) {}

	virtual void OnOpenBank(KUIEventOpenBank const& param) {}
	virtual void OnUpdateBankSlot() {}

	virtual void OnUpdateMapMark(KUIEventUpdateMapMark const& param) {}
	virtual void OnUpdateRegionInfo(KUIEventUpdateRegionInfo const& param) {}
	virtual void OnUpdateMidMapMark(KUIEventUpdateMidMapMark const& param) {}
    virtual void OnPlayerLevelUp(KUIEventPlayerLevelUpdate const& param) {}

	virtual void OnPlayMiniGame(KUIEventPlayMiniGame const& param) {}

	virtual void OnUpdateRadar(KUIEventUpdateRadar const& param) {}

	virtual void OnDisconnect() {}
    virtual void OnPlayerKickAccount() {} // 你的账号已经在另一台机器上登陆,你被迫下线
	virtual void OnConnectGameServerFailed() {}

	virtual void OnShowSwimmingProgress() {}
	virtual void OnHideSwimmingProgress() {}

	virtual void OnUpdateReputation(KUIEventUpdateReputation const& param) {}
	virtual void OnReputationLevelUp(KUIEventReputationLevelUp const& param) {}

    virtual void OnPeekOtherPlayer(KUIEventPeekOtherPlayer const& param) {}

    virtual void OnSkillRecipeListUpdate() {}

    virtual void OnBanishPlayer(KUIEventBanishPlayer const& param) {}

    virtual void OnUpdateRoadTrackForce(){}

    virtual void OnRoadTrackErrorID(KUIEventRoadTrackErrorID const& param) {}

    virtual void OnUpdateRouteNodeOpenList() {}

    virtual void OnOpenDoodadMoveStateError(){}

    virtual void OnUpdateAccumulateValue(){}

    virtual void OnStartAutoFly(){}
    virtual void OnEndAutoFly(){}
    virtual void OnAutoFlySwitchMap(){}
    
    virtual void OnTrainValueUpdate(KUIEventTrainValueUpdate const& param){}
    virtual void OnSwitchMapResult(KUIEventSwitchMapResult const& param){}

    virtual void OnCastCommonSkill(KUIEventCastCommonSkill const& param){}

    virtual void OnOpenVenationRetCode(KUIEventOpenVenationRetCode const& param){}

    virtual void OnShareQuestResult(KUIEventShareQuestResult const& param){}

    virtual void OnUpdatePlayerSchoolID(KUIEventUpdatePlayerSchoolID const& param){}

    virtual void OnUpdateAssistDailyCount(){}

	virtual void OnMapVisitFlagChanged(){}

	virtual void SetInLogin(BOOL bLogin){}

    virtual void OnAddSkillRecipe(KUIAddSkillRecipe const& param) {}

    virtual void OnDailyQuestUpdate() {}

    virtual void OnJoinBattleFieldQueue(KUIEventJoinBattleFieldQueue const& param) {}
    virtual void OnLeaveBattleFieldQueue(KUIEventLeaveBattleFieldQueue const& param) {}
    virtual void OnBattleFieldNotify(KUIEventBattleFieldNotify const& param) {}
    virtual void OnBattleFieldEnd() {}
    virtual void OnSyncBattleFieldStatistics() {}
    virtual void OnUpdateBattleFieldList(KUIEventUpdateBattleFieldList const& param) {}
    virtual void OnUpdateBattleFieldObjective() {}
    
    virtual void OnUpdateCampInfo(){}
    virtual void OnUpdatePrestige(KUIEventUpdatePrestige const& param){}
    virtual void OnMaxPrestigeNotify(){};
    virtual void OnUpdateHeroFlag(){}

    virtual void OnUpdateTongInfo() {};
    virtual void OnUpdateTongRoster() {};
    virtual void OnInvitePlayerJoinTongRequest(KUIEventInviteJoinTongRequest const& param) {};
    virtual void OnPlayerChangeTongNotify(KUIEventChangeTongNotify const& param) {};

    virtual void OnTongStateChange(KUIEventTongStateChange const& param){};
    virtual void OnTongGroupRightChange(KUIEventTongGroupRightChange const& param){};
    virtual void OnTongGroupNameChange(KUIEventTongGroupNameChange const& param){};
    virtual void OnTongGroupWageChange(KUIEventTongGroupWageChange const& param){};
    virtual void OnTongMemberJoinOrQuit(KUIEventTongMemberJoinOrQuit const& param){};
    virtual void OnTongMemberChangeGroup(KUIEventTongMemberChangeGroup const& param){};
    virtual void OnTongMasterChange(KUIEventTongMasterChange const& param){};
    virtual void OnTongCampChange(KCAMP eCamp){};
    virtual void OnShowTongOnlineMessage(KUIEventShowTongOnlineMessage const& param){};
    virtual void OnOpenTongRepertory(KUIEventOpenTongRepertory const& param){};
    virtual void OnTongMemberOnlineStateChange(KUIEventTongMemberOnlineStateChange const& param){};
    virtual void OnTongGroupEnabled(KUIEventTongGroupEnabled const& param){};
    virtual void OnUpdateTongClientDataFinish(KTONG_UPDATE_FLAG eFlag){};
    virtual void OnTongMaxMemberCountChange(KUIEventTongMaxMemberCountChange const& param){};
    virtual void OnUpdateTongRepertoryPage(KUIEventUpdateTongRepertoryPage const& param){};
    virtual void OnTongEventNotify(TONG_EVENT_NOTIFY_CODE eEventCode){};

    virtual void OnAuctionLookupRespond(KUIEventAuctionLookupRespond const& param){}
    virtual void OnAuctionSellRespond(KUIEventAuctionCommonRespond const& param){}
    virtual void OnAuctionBidRespond(KUIEventAuctionCommonRespond const& param){}
    virtual void OnAuctionCancelRespond(KUIEventAuctionCommonRespond const& param){}
    virtual void OnAuctionMessageNotify(KUIEventAuctionMessageNotify const& param){}

    virtual void OnCampInfoNotify(KUIEventCampInfo const& param){}

    virtual void OnChargeLimitNotify(KUIEventChargeLimitNotify const& param){}

    virtual void OnRemoteLuaCall(const char cszCommand[], BYTE* pbyData, size_t uDataLen){};

    virtual void OnChangeCamp(KUIEventChangeCamp const& param){};

    virtual void OnSyncAchievementData(KUIEventSyncAchievementData const& param){}
    virtual void OnNewAchievement(KUIEventNewAchievement const& param){}
    virtual void OnAchievementAnnounce(KUIEventAchievementAnnounce const& param){}
    virtual void OnUpdateAchievementPoint(int nDelta){}
    virtual void OnUpdateAchievementCount(){}

    virtual void OnSyncDesignationData(KUIEventSyncDesignationData const& param){}
    virtual void OnSetGenerationNotify(KUIEventSetGeneration const& param){}
    virtual void OnAcquireDesignation(KUIEventAcquireDesignation const& param){}
    virtual void OnDesignationAnnounce(KUIEventDesignationAnnounce const& param){}
    virtual void OnRemoveDesignation(KUIEventRemoveDesignation const& param){}
    virtual void OnSetCurrentDesignationRespond(KUIEventSetCurrentDesignationRespond const& param){}

    virtual void OnStopFollow(KUIEventStopAutoMove const& param){};

    virtual void OnStopAutoMoveToTarget(KUIEventStopAutoMove const& param){};

    virtual void OnStopAutoMoveToPoint(KUIEventReachPoint const& param){};

    virtual void OnOptimizationHint(KUIEventOptimizationHint const& param){}

    virtual void OnAccountEndOfDayTime() {}

    virtual void OnGameCardSellRespond(KUIEventGameCardSellRespond const& param) {}
    virtual void OnGameCardBuyRespond(KUIEventGameCardBuyRespond const& param) {}
    virtual void OnGameCardLookupRespond() {}
    virtual void OnGameCardCancelRespond(KUIEventGameCardCancelRespond const& param) {}

    virtual void OnSyncCoin() {}

    virtual void OnSeekMentorYell(KUIEventSeekMentorYell const& param) {}
    virtual void OnSeekApprenticeYell(KUIEventSeekApprenticeYell const& param) {}
    virtual void OnMentorValueChange(KUIEventMentorValueChange const& param) {}
    
    virtual void OnChangeCampFlag(DWORD dwPlayerID) {}

    virtual void OnCharacterThreatRanklist(DWORD dwThreatListOwnerID, int nRankCount, KUIThreatRankList* pRankList) {}
};


#endif // SO3_GAME_WORLD_UI_HANDLER_H
