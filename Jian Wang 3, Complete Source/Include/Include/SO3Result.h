#ifndef _SO3_RESULT_H_
#define _SO3_RESULT_H_

// 错误返回值分类
enum ERROR_CODE_TYPE
{
	ectInvalid = 0,

	ectSkillErrorCode,
	ectLoginErrorCode,
	ectQuestErrorCode,
    ectFellowshipErrorCode,
    ectFellowshipAttractionErrorCode,
	ectItemErrorCode,
    ectTradingErrorCode,
    ectTalkErrorCode,
	ectCraftErrorCode,
	ectLootItemErrorCode,
    ectMailErrorCode,
    ectTeamNotifyCode,
	ectAddItemErrorCode,
    ectPeekOtherPlayerErrorCode,
    ectShopEventNotifyCode,
	ectPKErrorCode,
    ectFellowshipOnline,
    ectFoeOnline,
    ectBanishNotifyCode,
    ectRoadTrackErrorCode,
    ectSwitchMapErrorCode,
    ectUseItemErrorCode,
    ectOpenVenationRetCode,
    ectShareQuestErrorCode,
    ectSetQuestAssistDailyCount,
    ectFinishAssistQuest,
    ectAddSkillRecipe,
    ectFellowshipAttractionFallOff,
    ectCampResultCode,
    ectChargeLimitCode,

	ectTotal
};

// 添加道具的错误提示
enum ADD_ITEM_RESULT_CODE
{
	aircInvalid = 0,

	aircSuccess,
	aircFailed,

	aircNotEnoughFreeRoom,	// 没有足够的背包空间			
	aircItemAmountLimited,	// 你无法获得更多的此类物品
    aircCannotPutThatPlace, // 不能放在该位置

	aircTotal
};

// 技能相关的错误返回值
enum SKILL_RESULT_CODE
{
	srcInvalid = 0,

	srcSuccess,             // 成功
	srcFailed,              // 失败，未定义原因

    srcInvalidCastMode,     // 释放方式不对
	srcNotEnoughLife,		// 血量不足
	srcNotEnoughMana,		// 内力不足
    srcNotEnoughRage,       // 怒气不足
	srcNotEnoughStamina,	// 体力不足
	srcNotEnoughItem,		// 道具不足
    srcNotEnoughAmmo,       // 弹药不足
	srcSkillNotReady,		// 技能CD时间未到
    srcInvalidSkill,        // 无效的技能
    srcInvalidTarget,       // 无效的目标
    srcNoTarget,            // 没有目标
    srcNeedTarget,          // 需要指定一个目标
    srcTooCloseTarget,      // 目标太近
	srcTooFarTarget,		// 目标太远
    srcOutOfAngle,          // 目标角度不对
    srcTargetInvisible,     // 目标不在视线范围内
    srcWeaponError,         // 武器不匹配
    srcWeaponDestroy,       // 武器已损坏(耐久度为0)
    srcAmmoError,           // 弹药与武器不匹配
    srcNotEquitAmmo,        // 没有装备弹药
    srcMountError,          // 没有装备对应的武功
    srcInOTAction,          // 正处于其他OTAction行为
    srcOnSilence,           // 正处于禁言状态
    srcNotFormationLeader,  // 不是阵眼，不能释放阵法
    srcNotEnoughMember,     // 组成阵法的成员不足
    srcNotStartAccumulate,  // 没有开始蓄气
    srcBuffError,           // 没有所需要的Buff
    srcNotInFight,          // 不能在战斗中
    srcMoveStateError,      // 移动状态错误
    srcErrorByHorse,        // 上下马的状态出错
    srcBuffInvalid,         // 你作用的BUFF不存在
    srcForceEffect,         // 更强大的效果在作用中
    srcBuffImmunity,        // 你的BUFF被免疫了
    srcTargetLifeError,     // 目标血量不满足
    srcSelfLifeError,     // 自身血量不满足
    srcDstMoveStateError,
    srcNotTeam,            // 没有组队
    srcMapBan,

	srcTotal
};

enum LOOT_ITEM_RESULT_CODE
{
	lircInvalid = 0,

	lircSuccess,            // 成功
	lircFailed,             // 失败，未定义原因

	lircInventoryIsFull,	// 背包已满
	lircNotExistLootItem,	// 要拾取的物品不存在
	lircAddLootItemFailed,	// 拾取的物品无法放入背包
	lircNoLootTarget,		// 无拾取目标Doodad
	lircTooFarToLoot,		// 太远而不能拾取
	lircOverItemLimit,		// 超过携带上限

	lircTotal
};

enum QUEST_RESULT_CODE
{
	qrcInvalid = 0,

	qrcSuccess,
	qrcFailed,

	qrcErrorQuestIndex,					//错误的任务索引
	qrcErrorQuestID,					//错误的任务ID
	qrcQuestListFull,					//任务列表已满
	qrcErrorQuestState,					//错误的任务状态
	qrcAlreadyAcceptQuest,				//已经接受了任务
	qrcAlreadyFinishedQuest,			//已经完成了任务
	qrcCannotFindQuest,					//任务配置表中找不到指定的任务
	qrcTooLowLevel,						//角色等级太低
	qrcTooHighLevel,					//角色等级太高
	qrcErrorGender,						//角色性别不符合要求
	qrcErrorRoleType,					//角色体型不对
	qrcErrorForceID,					//角色门派不对
	qrcCooldown,						//Cooldown计时器未到时间
	qrcPrequestUnfinished,				//前置任务没完成
	qrcErrorItemCount,					//错误的任务物品数量
	qrcErrorKillNpcCount,				//错误的杀怪数量
	qrcTooLongTime,						//做任务时间超过限制
	qrcErrorTaskValue,					//错误的任务变量数值
	qrcAssistQuestListFull,				//协助任务列表错误
	qrcErrorAssistQuestIndex,			//错误的协助任务序号
	qrcErrorStartNpcTarget,				//目标Npc身上不能接该任务
	qrcErrorStartDoodadTarget,			//目标Doodad身上不能接该任务
	qrcErrorEndNpcTarget,				//目标Npc身上不能交该任务
	qrcErrorEndDoodadTarget,			//目标Doodad身上不能交该任务
	qrcNoStartQuestItem,				//没有任务起始道具
	qrcNoEndQuestItem,					//没有结束起始道具
	qrcTooEarlyTime,					//接任务时间太早
	qrcTooLateTime,						//接任务时间太晚
	qrcTooLowSkillLevel,				//武功技能等级太低
	qrcTooLowLifeLevel,					//生活技能等级太低
	qrcErrorGenerateItem,				//生成任务奖励物品失败
	qrcAddItemFailed,					//添加任务奖励物品失败
	qrcAddMoneyFailed,					//添加金钱失败
	qrcAddReputationFailed,				//添加声望失败
	qrcNotEnoughStartItem,				//接任务道具不足
	qrcNotEnoughFreeRoom,				//背包空间不足
	qrcErrorMap,						//错误的地图
	qrcUnfinishedQuest,					//未完成任务，不能协助
	qrcCannotFindQuestInDestPlayer,		//无法在目标玩家身上找到需要协助的任务
	qrcNeedAccept,						//必须先接任务才能交
	qrcNoNeedAccept,					//不用接就能交的任务
	qrcQuestFailed,						//此任务已失败
	qrcAddSkillFailed,					//添加技能失败
	qrcNotEnoughMoney,					//金钱不足
    qrcMoneyLimit,                      //钱已经达到上限
    qrcErrorRepute,                     //声望不满足
    qrcAddPresentItemFailed,            //无法奖励任务完成道具
    qrcDailyQuestFull,                  //每日任务已满
    qrcEscortQuestIsRunning,            //其他人正在做这个护送任务
    qrcErrorCamp,                       //阵营不对
    qrcQuestEndBookNotMemorized,        //必须阅读整套书
    qrcChargeLimit,
    qrcRequireApprentice,               //需求是徒弟
    qrcTooManyQuestOfferItem,           //任务发放道具超过拥有限制

	qrcTotal
};

enum ITEM_RESULT_CODE
{
	ircInvalid = 0,

	ircSuccess,
	ircFailed,

	ircItemNotExist,					// 物品不存在
	ircNotEnoughDurability,				// 耐久度不足或叠加数量不足
	ircErrorEquipPlace,					// 装备物品栏位置错误
    ircForceError,                      // 门派不对
	ircTooLowAgility,					// 敏捷太低,不能装备
	ircTooLowStrength,					// 力量太低,不能装备
	ircTooLowSpirit,					// 根骨太低,不能装备
	ircTooLowVitality,					// 体质太低,不能装备
	ircTooLowLevel,						// 等级太低,不能装备
	ircTooLowDurability,				// 耐久度为零,不能装备
	ircCannotEquip,						// 物品不可被装备
	ircCannotPutToThatPlace,			// 物品无法放置到那个位置	
	ircCannotDisablePackage,			// 背包内有东西无法卸下
	ircPackageNotEnoughSize,			// 背包大小不足
	ircPackageErrorType,				// 背包类型不符
	ircPlayerIsDead,					// 死亡状态不能进行这个操作
	ircBankPackageDisabled,				// 银行背包没有激活,不能往上放背包
    ircEquipedPackageCannotDestroy,     // 已经装备上的背包不能摧毁
    ircBinded,                          // 物品已经绑定
    ircCannotDestroy,                   // 该物品不能被摧毁
    ircGenderError,                     // 性别不符合
    ircPlayerInFight,                   // 战斗中不能切换
    ircOnHorse,                         // 骑马的时候不能拿下马
    ircCampCannotEquip,                 // 当前所在阵营不能装备该物品
    ircRequireProfession,               // 需要学习某生活技能
    ircRequireProfessionBranch,         // 需要学习某生活技能分支
    ircProfessionLevelTooLow,           // 生活技能等级太低

	ircTotal
};

enum USE_ITEM_RESULT_CODE
{
	uircInvalid = 0,

	uircSuccess,
	uircFailed,
    
    uircItemNotExist,                    // 物品不存在   
    uircCannotUseItem,                   // 物品不能使用
    uircNotEnoughDurability,             // 耐久度不够
    uircNotReady,                        // 物品还没准备好
    uircUseInPackage,					 // 在背包中才能使用
	uircUseWhenEquipped,				 // 装备上才能使用该物品
    uircTooLowLevel,                     // 等级太低
    uircRequireProfession,               // 需要学习某生活技能
    uircRequireProfessionBranch,         // 需要学习某生活技能分支
    uircProfessionLevelTooLow,           // 生活技能等级太低
    uircOnHorse,                         // 正在骑马
    uircInFight,                         // 正在战斗
    uircRequireMale,                     // 男人才能使用
    uircRequireFeMale,                   // 女人才能使用
    uircCampCannotUse,                   // 角色所在阵营不能使用
    uircCannotCastSkill,                 // 不能释放物品上的技能
    uircCastSkillFailed,                 // 释放失败
    uircCostItemDurabilityFailed,        // 消耗耐久度失败
    uircForceError,                      // 门派不对
    uircAleardHaveDesignation,           // 已经获得该称号

	uircTotal
};

enum PARTY_NOTIFY_CODE
{
    epncInvalid = 0,
    epncPlayerInviteNotExist,
    epncPlayerApplyNotExist,
    epncPlayerAlreadInYourTeam,
    epncPlayerAlreadInOtherTeam,
    epncYouAlreadInTeamState,
    epncPlayerIsBusy,
    epncInvitationDenied,   
    epncApplicationDenied,
    epncPlayerNotOnline,
    epncDestTeamIsFull,
    epncYourTeamIsFull,
    epncInvitationOutOfDate,  // 邀请已经过期
    epncApplicationOutOfDate, // 申请已经过期
    epncTeamCreated,
    epncTeamJoined,
    epncInvitationDone,       // 你向XXX发出邀请
    epncApplicationDone,      // 你向XXX发出申请
    epncInvitationReject,     // 你拒绝了XXX的邀请
    epncApplicationReject,    // 你拒绝了XXX的申请
    epncCampError,
    epncTotal
};

enum SHOP_SYSTEM_RESPOND_CODE
{
    ssrcInvalid = 0,
    ssrcSellSuccess,                    // 出售成功
    ssrcBuySuccess,                     // 购买成功
    ssrcRepairSuccess,                  // 修理成功
    ssrcSellFailed,                     // 出售失败
    ssrcBuyFailed,                      // 购买失败
    ssrcRepairFailed,                   // 修理成功

    ssrcTooFarAway,                     // 距离太远了
    ssrcNotEnoughMoney,                 // 金钱不足
    ssrcNotEnoughPrestige,              // 威望点数不足
    ssrcNotEnoughContribution,          // 贡献点数不足
    ssrcAchievementRecordError,         // 游戏完成度不够
    ssrcNotEnoughAchievementPoint,      // 成就点数不足
    ssrcNotEnoughRepate,                // 声望不足
    ssrcNotEnoughRank,                  // 称号不达要求
    ssrcItemSoldOut,                    // 商店该物品卖完了
    ssrcBagFull,                        // 背包已满
    ssrcItemExistLimit,                 // 物品拥有限制
    ssrcItemNotNeedRepair,              // 物品不需修理
    ssrcNoneItemNeedRepair,             // 没有物品可以修理
    ssrcCanNotSell,                     // 不能出售改该物品
    ssrcItemHadLimit,                   // 物品拥有达到上限
    ssrcItemModifiedWhileBuy,           // 在你发出购买请求的这段时间内，该栏物品发生了变化
    ssrcYouDeath,                       // 你挂了
    ssrcItemBroken,                     // 该物品耐久度太低，无法出售。
    ssrcItemNotInPackage,               // 物品不在背包中。
    ssrcNotEnoughItem,                  // 需要的道具不足

    ssrcTotal
};

enum TRADING_RESULT_CODE
{
    trcInvalid,
    trcSuccess,
    trcFailed,                  

    trcInvalidTarget,
    trcInvalidInvite,           // 交易邀请已过期
    trcRefuseInvite,            // 目标拒绝邀请
    trcTargetNotInGame,         // 邀请的目标不在游戏中
    trcTargetBusy,              // 目标正在忙
    trcYouBusy,                 // 你正在忙别的事情
    trcTooFar,                  // 距离太远了
    trcTradingCancel,           // 交易取消
    trcTradingCanceled,         // 交易被取消
    trcItemBeBound,             // 物品已绑定
    trcNotEnoughMoney,          // 没有足够的金钱
    trcNotEnoughFreeRoom,       // 没有足够的空间    
    trcItemExistAmountLimit,    // 物品拥有超过上限
    trcYouDead,                 // 玩家已经死亡
    trcItemNotInPackage,        // 只有背包内的物品可以交易
    trcTargetDead,              // 目标已经死亡

    trcTotal
};

enum CRAFT_RESULT_CODE
{
	crcInvalid = 0,

	crcSuccess,                 // 成功
	crcFailed,                  // 失败，未定义原因

	crcNotEnoughStamina,	    // 精力不足
	crcNotEnoughThew,	        // 体力不足
    crcNotEnoughItem,		    // 道具不足
	crcSkillNotReady,		    // 技能CD时间未到
	crcWeaponError,             // 武器不匹配
	crcTooLowProfessionLevel,   // 生活技能等级太低
    crcTooLowExtProfessionLevel,// 扩展生活技能等级太低
	crcAddItemFailed,			// 添加道具失败
	crcInventoryIsFull,		    // 背包已满
	crcProfessionNotLearned,    // 技能未学习
    crcExtProfessionNotLearned, // 扩展技能未学习
	crcErrorTool,			    // 没有相关工具
	crcBookIsAlreadyMemorized,	// 书籍已经被记忆了
	crcRequireDoodad,			// 需求周围有工作用的Doodad
    crcItemTypeError,           // 目标物品类型不对
    crcBookCannotBeCopy,        // 该书不能被抄录
    crcDoingOTAction,           // 正在做其他的动作
    crcMoveStateError,          // 当前状态无法做这个操作
    crcTooLowLevel,             // 玩家等级太低

	crcTotal
};

enum PLAYER_FELLOWSHIP_RESPOND_CODE
{
    rrcInvalid = 0,

    rrcSuccess,                 // 成功。

    rrcSuccessAdd,              // 添加关系成功
    rrcSuccessAddFoe, 
    rrcSuccessAddBlackList, 

    rrcFailed,                  // 失败，未定义。

    rrcInvalidName,             // 无效的玩家名字。
    rrcAddSelf,                 // 添加自己为好友
    rrcFellowshipListFull,      // 好友列表已满。
    rrcFoeListFull,             // 仇人列表已满。
    rrcBlackListFull,           // 黑名单列表已满。
    rrcFellowshipExists,        // 指定的好友已经存在。
    rrcFoeExists, 
    rrcBlackListExists, 
    rrcFellowshipNotFound,      // 指定的好友不存在。
    rrcFoeNotFound, 
    rrcBlackListNotFound,

    rrcInvalidGroupName,        // 无效的分组名字。
    rrcInvalidRemark,           // 无效的备注。
    rrcFellowshipGroupFull,     // 好友分组已满。
    rrcFellowshipGroupNotFound, // 指定的组不存在。

    rrcInFight,                 // 战斗状态不能操作仇人。

    rrcBeAddFriend,             // 被加入好友
    rrcBeAddFoe,                // 被加入仇人
    rrcBeAddBlackList,          // 被加入黑名单

    rrcTotal
};

enum PEEK_OTHER_PLAYER_RESPOND_CODE
{
    prcInvalid = 0,

    prcSuccess,                 // 成功
    prcFailed,                  // 失败，未定义错误
    prcCanNotFindPlayer,        // 失败，找不到指定玩家
    prcTooFar,                  // 距离太远

    prcTotal
};

enum PK_RESULT_CODE
{
	pkrcInvalid = 0,

	pkrcSuccess,				// 成功
	pkrcFailed,					// 未知错误

	pkrcApplyDuelFailed,
    pkrcTargetIsDueling,
    pkrcInSameTeam,            // 在同一个队伍里面不能PK
    pkrcOutofRange,             // 不在距离范围内
	pkrcApplySlayFailed,
    pkrcLevelTooLow,            // 级别太低
    pkrcPKNotReady,             // CD中

	pkrcTotal
};

enum ROAD_TRACK_RESULT_CODE
{
    rtrcInvalid = 0,

    rtrcSuccess,
    rtrcFailed,

    rtrcNotOpen,
    rtrcCostError,
    rtrcNotEnoughMoney,

    rtrcTotal
};

enum SWITCH_MAP_RESULT_CODE
{
    smrcInvalid = 0,

    smrcSuccess,
    smrcFailed,
    
    smrcMapCreating,
    smrcEnterNewCopyTooManyTimes,
    smrcGameMaintenance,
    smrcGameOverLoaded,
    smrcCreateMapFinished,
    smrcMapCopyCountLimit,

    smrcTotal
};

enum SHARE_QUEST_RESULT_CODE
{
	sqrcInvalid = 0,

	sqrcSuccess,
	sqrcFailed,

	sqrcTooFar,
    sqrcQuestCannotShare,
    sqrcNotInTeam,
    sqrcAlreadyAcceptQuest,
    sqrcAlreadyFinishedQuest,
    sqrcQuestListFull,
    sqrcAcceptQuest,
    sqrcRefuseQuest,

	sqrcTotal
};

enum BATTLE_FIELD_RESULT_CODE
{
    bfrcInvalid = 0,

    bfrcSuccess,
    bfrcFailed,

    bfrcInBlackList,
    bfrcLevelError,
    bfrcForceError,
    bfrcTeamMemberError,
    bfrcTeamSizeError,
    bfrcTooManyJoin,
    bfrcNotInSameMap,
    bfrcCampError,
    bfrcTimeError,

    bfrcTotal
};

enum TONG_EVENT_NOTIFY_CODE
{
    tenInvalid = 0,

    tenInviteSuccess,
    tenInviteNameNotFoundError,
    tenInviteTargetAlreadyJoinTongError,
    tenInviteTargetBusyError,
    tenInviteTargetOfflineError,
    tenInviteNoPermissionError, 

    tenInviteInvaildError,
    tenInviteTimeOutError,
    tenInviteTargetRefuse,
    tenInviteTargetChargeLimit,

    tenInviteMemberNumberLimitError,

    tenKickOutSuccess,
    tenKickOutTargetNotFoundError,
    tenKickOutTargetNoPermissionError,

    tenModifyTongNameSuccess,
    tenModifyTongNameIllegalError,
    tenModifyTongNameNoPermissionError,

    tenModifyAnnouncementSuccess,
    tenModifyAnnouncementNoPermissionError,

    tenModifyOnlineMessageSuccess,
    tenModifyOnlineMessageNoPermissionError,

    tenModifyIntroductionSuccess,
    tenModifyIntroductionNoPermissionError,

    tenModifyRulesSuccess,
    tenModifyRulesNoPermissionError,

    tenModifyGroupNameSuccess,
    tenModifyGroupNameNoPermissionError,

    tenModifyBaseOperationMaskSuccess,
    tenModifyBaseOperationMaskNoPermissionError,

    tenModifyAdvanceOperationMaskSuccess,
    tenModifyAdvanceOperationMaskNoPermissionError,

    tenModifyGroupWageSuccess,
    tenModifyGroupWageNoPermissionError,

    tenModifyMemorabiliaSuccess,
    tenModifyMemorabiliaError,

    tenQuitNotInTongError,
    tenQuitIsMasterError,

    tenChangeMemberGroupSuccess,
    tenChangeMemberGroupError,

    tenChangeMasterSuccess,
    tenChangeMasterError,

    tenChangeMemberRemarkSuccess,
    tenChangeMemberRemarkError,

    tenInviteTargetInRivalCampError,
    tenTargetTongIsRivalCampError,

    tenChangeCampPermissionError,
    tenChangeCampLimitError,

    tenCreateTongNameIllegalError,
    tenCreateTongAlreadyInTongError,
    tenCreateTongNameConflictError,

    tenRepertoryGridFilledError,
    tenRepertoryPageFullError,
    tenPutItemInRepertorySuccess,
    tenItemNotInRepertoryError,
    tenTakeItemFromRepertorySuccess,
    tenExchangeRepertoryItemSuccess,

    tenTakeRepertoryItemPermissionDenyError,
    tenPutItemToRepertoryPermissionDenyError,
    tenStackItemToRepertoryFailError,

    tenSaveMoneySuccess,
    tenSaveMoneyTooMushError,
    tenPaySalarySuccess,
    tenPaySalaryFailedError,

    tenRenameSuccess,
    tenRenameNoRightError,
    tenRenameUnnecessaryError,
    tenRenameConflictError,
    tenRenameIllegalError,

    tenTotal
};

enum CAMP_RESULT_CODE
{
    crtInvalid,

    crtFaild,
    crtSuccess,

    crtTongConflict,
    crtInTeam,

    crtTotal
};

enum CHARGE_LIMIT_CODE
{
    cltInvalid,

    cltTalkWorld,
    cltTalkCamp,
    cltYouTrading,
    cltTargetTrading,
    cltMail,
    cltAuctionBid,
    cltAuctionSell,
    cltYouJoinTong,
    cltTargetJoinTong,
    cltLoginMessage,

    cltTotal
};

enum ENCHANT_RESULT_CODE
{
    ercInvalid,
    
    ercSuccess,
    ercPackageIsFull,
    ercCannotUnMount,
    ercFailed,

    ercTotal
};
#endif	//_SO3_RESULT_H_
