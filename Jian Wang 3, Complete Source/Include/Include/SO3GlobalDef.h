#ifndef _KG_GLOBAL_DEF_H_
#define _KG_GLOBAL_DEF_H_

#ifdef __GNUC__
#include <stdint.h>
#endif

// disable: warning C4200: nonstandard extension used : zero-sized array in struct/union
#pragma warning(disable:4200)

#define ID_PREFIX_BIT_NUM	    2
#define MAX_GS_COUNT		    24
#define CLIENT_ITEM_ID_PREFIX	0x01
#define NPC_ID_PREFIX	        0x01

// 创建INT64
#define MAKE_INT64(__A__, __B__)	(((uint64_t)(__A__) << 32) + (uint64_t)__B__)

#define ERROR_ID		0

// 动态障碍分组的无效值
#define INVALID_OBSTACLE_GROUP  (-1)
// 有效的动态障碍分组索引号取值范围: [0, 4096)
#define MAX_OBSTACLE_GROUP      4096

// 场景和游戏世界的空间划分大小定义
#define MAX_REGION_WIDTH_BIT_NUM	6	//地图中X坐标上最多的Region个数
#define MAX_REGION_HEIGHT_BIT_NUM	6	//地图中Y坐标上最多的Region个数

#define REGION_GRID_WIDTH_BIT_NUM	6	//Region中X坐标上最多的Cell个数
#define REGION_GRID_HEIGHT_BIT_NUM	6	//Region中Y坐标上最多的Cell个数

#define CELL_LENGTH_BIT_NUM			5	//格子中的象素点精度
#define ALTITUDE_BIT_NUM			6

#define MAX_Z_ALTITUDE_BIT_NUM		16	//Z轴的最大值位数(ALTITUDE)
#define MAX_Z_POINT_BIT_NUM         (MAX_Z_ALTITUDE_BIT_NUM + ALTITUDE_BIT_NUM)

#define MOVE_DEST_RANGE_BIT_NUM		12
#define MOVE_DEST_RANGE				(1 << MOVE_DEST_RANGE_BIT_NUM)

#define	MAX_VELOCITY_XY_BIT_NUM		(CELL_LENGTH_BIT_NUM + 2)
#define MAX_VELOCITY_Z_BIT_NUM		(ALTITUDE_BIT_NUM + 6)
// 用于水平速度收敛计算时消除计算误差,注意,这个值最好不要小于收敛计算时的分母数值
#define VELOCITY_ZOOM_BIT_NUM      4
#define VELOCITY_ZOOM_COEFFICIENT (1 << VELOCITY_ZOOM_BIT_NUM)

#define MAX_ZOOM_VELOCITY_BIT_NUM   (MAX_VELOCITY_XY_BIT_NUM + VELOCITY_ZOOM_BIT_NUM)
#define MAX_ZOOM_VELOCITY           ((1 << MAX_ZOOM_VELOCITY_BIT_NUM) - 1)

#define MAX_VELOCITY_XY				((1 << MAX_VELOCITY_XY_BIT_NUM) - 1)
// 注意,Z轴速度是有符号,可以为负值的,目前取值区间为[-512, 511], 10 bits
#define MAX_VELOCITY_Z				((1 << (MAX_VELOCITY_Z_BIT_NUM - 1)) - 1)
#define MIN_VELOCITY_Z				(-(1 << (MAX_VELOCITY_Z_BIT_NUM - 1)))

#define MAX_X_COORDINATE_BIT        (MAX_REGION_WIDTH_BIT_NUM  + REGION_GRID_WIDTH_BIT_NUM  + CELL_LENGTH_BIT_NUM)
#define MAX_Y_COORDINATE_BIT        (MAX_REGION_HEIGHT_BIT_NUM + REGION_GRID_HEIGHT_BIT_NUM + CELL_LENGTH_BIT_NUM)
#define MAX_X_COORDINATE            ((1 << MAX_X_COORDINATE_BIT) - 1)
#define MAX_Y_COORDINATE            ((1 << MAX_Y_COORDINATE_BIT) - 1)

//坐标相关定义
#define MAX_REGION_WIDTH			(1 << MAX_REGION_WIDTH_BIT_NUM)
#define MAX_REGION_HEIGHT			(1 << MAX_REGION_HEIGHT_BIT_NUM)
#define MAX_Z_ALTITUDE				((1 << MAX_Z_ALTITUDE_BIT_NUM) - 1)
#define MAX_Z_POINT				    ((1 << MAX_Z_POINT_BIT_NUM) - 1)

#define REGION_GRID_WIDTH			(1 << REGION_GRID_WIDTH_BIT_NUM)
#define REGION_GRID_HEIGHT			(1 << REGION_GRID_HEIGHT_BIT_NUM)

#define CELL_LENGTH					(1 << CELL_LENGTH_BIT_NUM)
#define POINT_PER_ALTITUDE			(1 << ALTITUDE_BIT_NUM)
#define ALTITUDE_2_CELL				(POINT_PER_ALTITUDE * LOGICAL_CELL_CM_LENGTH/ ALTITUDE_UNIT / CELL_LENGTH)

#define MAX_GRAVITY_BIT_NUM          5
#define MAX_GRAVITY                 ((1 << MAX_GRAVITY_BIT_NUM) - 1)

#define LOGICAL_CELL_CM_LENGTH		50
#define _3D_CELL_CM_LENGTH			100

// 地表高度计量单位(厘米)
#define ALTITUDE_UNIT				((LOGICAL_CELL_CM_LENGTH) / 4.0f)
#define TERRAIN_MIN_HEIGHT			(-65536.0f / 4.0f * ALTITUDE_UNIT)
#define TERRAIN_MAX_HEIGHT			(65536.0f / 4.0f * ALTITUDE_UNIT)

#define ALTITUDE_TO_XYPOINT(Altitude)   ((Altitude) * 8)
#define ZPOINT_TO_XYPOINT(Z)            ((Z) / 8)
#define XYPOINT_TO_ZPOINT(XY)           ((XY) * 8)
#define ZPOINT_TO_ALTITUDE(Z)           ((Z) / POINT_PER_ALTITUDE)

#define AI_PARAM_COUNT		8
#define DIALOG_ACTION_ID	1					//对话的表情ID

#define	MAX_TARGET_RANGE		(CELL_LENGTH * REGION_GRID_WIDTH * 2)

// 爬坡障碍高度差
#define CLIMB_ABILITY 	    (XYPOINT_TO_ZPOINT(CELL_LENGTH))

// 主角移动时定位前方目标点的距离,30米
#define MOVE_TARGET_RANGE   (30 * 100 * 32 / 50)

#define MAX_MOVE_STATE_BIT_NUM  5
#define MAX_MOVE_STATE_VALUE    ((1 << MAX_MOVE_STATE_BIT_NUM) - 1)

#define MAX_JUMP_COUNT_BIT 2
#define MAX_JUMP_COUNT ((1 << MAX_JUMP_COUNT_BIT) - 1)

// 最大MapID,MapID取值范围(0, MAX_MAP_ID]
#define MAX_MAP_ID UCHAR_MAX
#define MAX_MAP_ID_DATA_SIZE (((MAX_MAP_ID) - 1) / (CHAR_BIT) + 1)

#define BANISH_PLAYER_WAIT_SECONDS      30
#define DELETE_SCENE_WAIT_SECONDS       (BANISH_PLAYER_WAIT_SECONDS + 5) 

// 玩家装备表现
// 小心: 美术在资源(动作标签)里面引用了这里的枚举数值,修改可能造成问题,找相关人员确认.
enum PLAYER_EQUIP_REPRESENT
{
    perFaceStyle,          // 脸型              
    
    perHairStyle,          // 发型              
    
    perHelmStyle,          // 头盔外形          
    perHelmColor,          // 头盔颜色          
    perHelmEnchant,        // 头盔附魔效果      

    perChestStyle,         // 上装样式          
    perChestColor,         // 上装颜色          
    perChestEnchant,       // 上装附魔效果      

    perWaistStyle,         // 腰带外形          
    perWaistColor,         // 腰带颜色          
    perWaistEnchant,       // 腰带附魔          

    perBangleStyle,        // 护腕外形          
    perBangleColor,        // 护腕颜色          
    perBangleEnchant,      // 护腕附魔          

    perBootsStyle,         // 鞋子外形          
    perBootsColor,         // 鞋子颜色          

    perWeaponStyle,        // 武器外形          
    perWeaponEnchant1,     // 武器附魔1         
    perWeaponEnchant2,     // 武器附魔2         

    perBackExtend,         // 背部扩展          
    perWaistExtend,        // 腰部扩展          

    perHorseStyle,         // 马
    perHorseAdornment1,    // 马的装饰1
    perHorseAdornment2,    // 马的装饰2
    perHorseAdornment3,    // 马的装饰3
    perHorseAdornment4,    // 马的装饰4
    perReserved,           // 保留  
    perRepresentCount
};

// AI类型最好只往后面增加
// 如果要中间插入或删除,小心有些函数指针数组出错
enum AI_TYPE
{
	aitInvalid = 0,

	aitBase,
	aitPlayer,
	aitWood,

	aitTotal
};

// AI的行为状态
enum KAI_STATE
{
	aisInvalid = 0,

	aisIdle,        // 发呆,通常指到达某目标后的空闲
	aisWander,		// 闲逛
	aisPatrol,      // 巡逻到某个点的过程中
	aisFollow,      // 跟随
	aisAlert,       // 盯着目标,可能是在aisPatrol中发现一个目标,然后盯着它,也可能是Idle是发现目标,然后盯着它
	aisPursuit,     // 追击
	aisKeepAway,    // 后退
	aisEscape,      // 逃跑
	aisReturn,      // Attack完成以后返回

	//增加新的状态
	aisWait			// Npc小队AI中等待队友的状态 
};

enum AI_SKILL_TYPE
{
	aistInvalid = 0,

	aistPeriodTarget,
	aistPeriodSelf,
	aistPeriodFriend,
	aistPassiveRespond,
	aistChannelingBreak,
	aistTargetCount,
	aistSelfHP,
    aistPeriodTargetRange,

    aistMainThreatNThreat,
    aistBaseThreatNThreat,
    aistDamageThreatNThreat,
    aistTherapyThreatNThreat,
    aistSpecialThreatNThreat,

    aistBaseRandomTarget,
    aistBaseRandomNotSelectTarget,
    aistInRangeRandomTarget,
    aistInRangeRandomNotSelectTarget,
    aistOutRangeRandomTarget,
    aistOutRangeRandomNotSelectTarget,
    aistNearestTarget,
    aistNearestNotSelectTarget,

    aistPeriodTargetNotClear,
    aistTargetCountNotClear,
    aistPeriodTargetRangeNotClear,

	aistTotal
};

//角色体形
enum ROLE_TYPE
{
	rtInvalid = 0,

	rtStandardMale,     // 标准男
	rtStandardFemale,   // 标准女
    rtStrongMale,       // 魁梧男
    rtSexyFemale,       // 性感女
    rtLittleBoy,        // 小男孩
    rtLittleGirl,       // 小孩女

	rtTotal
};

enum KBUFF_REPRESENT_POS
{
    brpTrample = 0,     // 脚下踩着的
    brpBody,            // 身上的
    brpTopHead,         // 顶在头上的

    brpTotal
};


//角色交互动作
enum CHARACTER_ACTION_TYPE
{
	catInvalid = 0,

	catDialogue,		//对话
	catHowl,			//嚎叫

	catTotal
};

//势力相关定义
enum FORCE_RELATION_TYPE
{
	frtInvalid = 0,

	frtExalted,
	frtRevered,
	frtHonored,
	frtFriendly,

	frtNeutral,

	frtUnfriendly,
	frtHostile,
	frtHated,

	frtTotal
};

enum KCAMP
{
    cNeutral, // 中立阵营
    cGood,    // 正义阵营
    cEvil,    // 邪恶阵营

    cTotal
};

enum SCENE_OBJ_RELATION_TYPE
{
	sortInvalid		= 0,

	sortNone		= 1,
	sortSelf		= 2,
	sortAlly		= 4,
	sortEnemy		= 8,
	sortNeutrality	= 16,
	sortParty		= 32,

	sortAll	= sortNone | sortAlly | sortEnemy | sortSelf | sortNeutrality | sortParty,

	sortTotal,
};

struct KForceRelation
{
	int						nRelation;
	FORCE_RELATION_TYPE		eRelationType;
};

// 技能的作用结果类型
enum KSKILL_RESULT_TYPE
{
    serPhysicsDamage = 0,
    serSolarMagicDamage,
    serNeutralMagicDamage,
    serLunarMagicDamage,
    serPoisonDamage,

    serReflectiedDamage,    

    serTherapy,             // 受到治疗
    serStealLife,           // 偷取目标的生命  
    serAbsorbDamage,      
    serShieldDamage,
    serParryDamage,
    serInsightDamage,

    serTotal
};


// 道具相关
#define MAX_ITEM_BASE_COUNT		6
#define	MAX_ITEM_REQUIRE_COUNT	6
#define	MAX_ITEM_MAGIC_COUNT	12


#define SETTING_DIR			"settings"

#define MAP_LIST_FILE_NAME	"MapList.tab"

// 脚本回调函数名
#define SCRIPT_ON_LOAD		"OnLoad"

// 地图障碍和场景物体
#define MAP_DIR				"maps"			//目录
#define MAP_FILE_EXT		"map"			//后缀

// 字符串长度定义
#define TITLE_LEN			32
#define TASK_NAME_LEN		256
#define FUNC_NAME_LEN		32
#define MAX_CHAT_TEXT_LEN	768

//扩展点
#define MAX_EXT_POINT_COUNT   8

//势力相关定义
#define MAX_FORCE_COUNT			128
#define FORCE_NAME_LEN			32



//地图标记的注释长度
#define MAX_MAP_MARK_COMMENT_LEN 32
#define MAX_MIDMAP_MARK_COMMENT_LEN 32

enum KMAP_TYPE
{
    emtInvalid = -1,
    
    emtNormalMap,       // 正常场景
    emtDungeon,         // 任务副本
    emtBattleField,     // 战场
    emtBirthMap,        // 新手村

    emtTotal
};

enum KMAP_CAMP_TYPE
{
    emctInvalid = 0,

    emctAllProtect,  // 全保护地图
    emctProtectGood, // 保护浩气盟
    emctProtectEvil, // 保护恶人谷
    emctNeutral,     // 中立地图
    emctFight,       // 争夺地图
    emctTotal
};

#define CLOSE_CAMP_FLAG_TIME 5 * 60 // 关闭阵营开关的时间，单位:秒

// 最大外网数据包的大小
#define MAX_EXTERNAL_PACKAGE_SIZE	    (1024 * 32)

#ifdef _PERFORMANCE_OPTIMIZATION
    extern DWORD g_dwGameFps;
    #define GAME_FPS					g_dwGameFps			//游戏帧数
#else
    #define GAME_FPS                    16
#endif


// 组队相关定义
// PARTY: 组队的队伍
#define INVALID_TEAM_GROUP  (-1)
// 整个游戏世界的最大允许的队伍数
#define MAX_PARTY_COUNT     4096
// 一支队伍允许的最大玩家数目
#define PARTY_MARK_COUNT        16

#define MAX_PLAYER_PER_GROUP    5
#define MIN_TEAM_GROUP_NUM      1
#define MAX_TEAM_GROUP_NUM      5

#define MAX_PARTY_SIZE      (MAX_PLAYER_PER_GROUP * MAX_TEAM_GROUP_NUM)

#define INVALID_SKILL_ID    0

enum KTEAM_AUTHORITY_TYPE
{
    tatInvalid,

    tatLeader,
    tatDistribute,
    tatMark,

    tatTotal
};

enum ITEM_LOOT_MODE
{
    ilmInvalid = 0,

	ilmFreeForAll,		// 队伍内自由拾取
	ilmDistribute,		// 高于品质线的物品分配者分配，其它物品轮流
	ilmGroupLoot,		// 高于品质线的物品roll决定归属，其它物品轮流

	ilmTotal           
};

enum INVENTORY_TYPE
{
	ivtEquipment = 0,
	ivtPackage,
	ivtBank,
	ivtSlot,
	ivtSoldlist,
    ivtTotal,
};

enum EQUIPMENT_INVENTORY_TYPE
{
	eitMeleeWeapon = 0,		// 近战武器
	eitRangeWeapon,			// 远程武器
	eitChest,				// 上衣
	eitHelm,				// 头部
	eitAmulet,				// 项链
	eitLeftRing,			// 左手戒指
	eitRightRing,			// 右手戒指
	eitWaist,				// 腰带
	eitPendant,				// 腰缀
	eitPants,				// 裤子
	eitBoots,				// 鞋子
	eitBangle,				// 护臂
	eitWaistExtend,			// 腰部扩展类装备，酒壶之类的
	eitPackage1,            // 扩展背包1
	eitPackage2,			// 扩展背包2
	eitPackage3,			// 扩展背包3
	eitPackage4,			// 扩展背包4
	eitBankPackage1,
	eitBankPackage2,
	eitBankPackage3,
	eitBankPackage4,
	eitBankPackage5,
	eitArrow,				// 暗器
    eitBackExtend,
    eitHorse,               // 坐骑 
	eitTotal
};

// ----------------- TALK ---------------------------->
#define CLIENT_TALK_LINK_ITEM_BUFFER_SIZE 1024

#define TALK_ERROR_S_OK                     0
#define TALK_ERROR_E_ERROR                  1
#define TALK_ERROR_E_OUT_OF_BUFFER          2
#define TALK_ERROR_E_NOT_IN_PARTY           3
#define TALK_ERROR_E_NOT_IN_SENCE           4
#define TALK_ERROR_E_PLAYER_NOT_FOUND       5
#define TALK_ERROR_E_PLAYER_OFFLINE         6
#define TALK_ERROR_E_YOU_BLACKLIST_TARGET   7
#define TALK_ERROR_E_TARGET_BLACKLIST_YOU   8
#define TALK_ERROR_E_BAN                    9
#define TALK_ERROR_E_CD                     10
#define TALK_ERROR_E_NOT_IN_TONG            11
#define TALK_ERROR_E_TONG_CAN_NOT_SPEAK     12
#define TALK_ERROR_E_DAILY_LIMIT            13
#define TALK_ERROR_E_NOT_IN_FORCE           14
#define TALK_ERROR_E_CHARGE_LIMIT           15

enum TALK_DATA_BLOCK_TYPE
{
    tdbInvalid = 0,
    tdbText,
    tdbLinkName,
    tdbLinkItem,
	tdbLinkItemInfo,
	tdbLinkQuest,
	tdbLinkRecipe,
    tdbLinkEnchant,
	tdbLinkSkill,
	tdbLinkSkillRecipe,
	tdbEmotion,
    tdbLinkBook,
	tdbLinkAchievement,
	tdbLinkDesignation,
    tdbEventLink,

    tdbTotal
};

// 聊天类型
enum CHARACTER_TALK_TYPE
{
    trInvalid = 0,

    // Player to Player chat.
    trNearby,           // 近聊
    trTeam,             // 小队聊天
    trRaid,             // 团队聊天
    trBattleField,      // 战场团队
    trSence,            // 同场景聊天（城聊）
    trWhisper,          // 密聊
    trFace,             // 表情频道

    // System message
    trLocalSys,         // 本地系统消息
    trGlobalSys,        // 全局系统消息
    trGmMessage,        // GM 

    // NPC to Player chat.
    trNpcNearby,
    trNpcTeam,
    trNpcSence,
    trNpcWhisper,
    trNpcSayTo,         // NPC 和指定的玩家说话；功能上类似密聊，但是聊天的内容出现在客户端的NPC近聊频道。
    trNpcYellTo,        // NPC 向指定的玩家大喊；功能上类似密聊，但是聊天的内容出现在客户端的NPC地图频道。
    trNpcFace,
    trNpcSayToTargetUseSentenceID,
    trNpcSayToCamp,

    // Ognization
    trTong,
    trWorld,
    trForce,
    trCamp,
    trMentor,
    trFriends,

    // Player custom channel.
    trCustomCh1 = 100,  // 玩家自定义频道预留
    trCustomCh2,
    trCustomCh3,
    trCustomCh4,
    trCustomCh5,
    trCustomCh6,
    trCustomCh7,
    trCustomCh8,

    // Debug message
    trDebugThreat,

    trTotal
};

//好友相关宏定义
#define KG_FELLOWSHIP_MAX_ATTRACTION        1500
#define KG_FELLOWSHIP_MIN_ATTRACTION       -1500
#define KG_FELLOWSHIP_MAX_RECORD            80
#define KG_FELLOWSHIP_MAX_FOE_RECORD        30
#define KG_FELLOWSHIP_MAX_BLACKLIST_RECORD  20
#define KG_FELLOWSHIP_MAX_CUSTEM_GROUP      8

// 角色状态机的状态
enum CHARACTER_MOVE_STATE
{
	cmsInvalid = 0,				// 无效状态

	// 受控状态
	cmsOnStand,					// 站立状态
	cmsOnWalk,					// 走路状态
	cmsOnRun,					// 跑步状态
    cmsOnJump,                  // 跳跃状态
    cmsOnSwimJump,              // 水中跳跃
    cmsOnSwim,                  // 水中游泳
    cmsOnFloat,                 // 水中悬浮
	cmsOnSit,					// 坐状态

	// 不受控状态
	cmsOnKnockedDown,			// 被击倒状态
	cmsOnKnockedBack,			// 被击退状态
	cmsOnKnockedOff,			// 被击飞状态 
    cmsOnHalt,                  // 定身(眩晕、笑穴等等)
    cmsOnFreeze,                // 不能动(固定动作)
    cmsOnEntrap,                // 不能移动
    cmsOnAutoFly,               // 自动移动,比如坐车等

	cmsOnDeath,					// 死亡状态
	cmsOnDash,					// 冲刺状态
    cmsOnPull,                  // 被抓状态，被别人抓住自己拉到对方身边
    cmsOnRepulsed,              // 滑步状态，一个会减速的状态

    cmsOnRise,                  // 爬起状态
    cmsOnSkid,                  // 停滑状态

	cmsTotal
};

enum KPQ_STATISTICS_INDEX 
{
    psiKillCount        = 0,
    psiDecapitateCount,
    psiSoloCount,
    psiHarmOutput,
    psiTreatOutput,
    psiInjury,
    psiDeathCount,
    psiThreatOutput,
    psiSkillMark,
    psiSpecialOp1,
    psiSpecialOp2,
    psiSpecialOp3,
    psiSpecialOp4,
    psiFinalMark,
    psiAwardMoney,
    psiAwardExp,
    psiAward1,
    psiAward2,
    psiAward3,

    psiTotal
};

#define ROLE_NAME_LEN       32

#pragma	pack(1)
// 头像相关数据
struct KPORTRAIT_INFO
{
    DWORD   dwFaceStyle : 5;
    DWORD   dwHairStyle : 8;
    DWORD   dwHelmStyle : 8;
    DWORD   dwHelmColor : 3;
    
    DWORD   dwReserved  : 8;    // 对齐
    // <-- 32 bits --

    BOOL operator != (const KPORTRAIT_INFO& crOther)
    {
        return memcmp(this, &crOther, sizeof(KPORTRAIT_INFO)) != 0;
    }
};

#pragma	pack()
// <---------------------------------------------------

#ifdef WIN32
#define STR_CASE_CMP(szA, szB) _mbsicmp((unsigned char*)(szA), (unsigned char*)(szB))
#else   // linux
#define STR_CASE_CMP(szA, szB) strcasecmp(szA, szB)
#endif


// 战场相关
#define MAX_BATTLE_SIDE             4
#define INVALID_BATTLE_SIDE         (-1)

#define INIT_CAMP_LEVEL 5 
#define CAMP_LEVEL_COUNT ((INIT_CAMP_LEVEL) * 2 + 1)

#define MAKE_IN_RANGE(Value, MinValue, MaxValue)        \
    do                                                  \
    {                                                   \
        assert(MinValue <= MaxValue);                   \
        if ((Value) > (MaxValue)) (Value) = (MaxValue); \
        if ((Value) < (MinValue)) (Value) = (MinValue); \
    }                                                   \
    while (false)


enum BANISH_PLAYER_CODE
{
    bpcInvalid = 0,

    bpcMapRefresh,
    bpcMapUnload,
    bpcNotInMapOwnerTeam,
    bpcCancelBanish,

    bpcTotal
};

class KRegion;
struct KCell;

struct KPOSITION_RECORD
{
    CHARACTER_MOVE_STATE    eMoveState;
    int                     nX;
    int                     nY;
    int                     nZ;
    int                     nDestX;
    int                     nDestY;
    int                     nVelocityXY;
    int                     nDirectionXY;
    int                     nVelocityZ;
    int                     nConvergenceSpeed;
    int                     nCurrentGravity;
    int                     nJumpCount;	
    int                     nFaceDirection;
    int                     nDivingCount;
    BOOL                    bTryPathState;
    int                     nTryPathSide;
    BOOL                    bSlip;
    int                     nJumpLimitFrame;
    int                     nCurrentTrack;
    int                     nFromNode;
    int                     nTargetCity;
    int                     nMoveFrameCount;
    KRegion*                pRegion;
    KCell*                  pCell;
};

// lzo压缩源串大小和目标串大小(字节)
#define LZO_ORIGINAL_BUFFER_LEN (60 * 1024)
#define LZO_COMPRESS_BUFFER_LEN (LZO_ORIGINAL_BUFFER_LEN + LZO_ORIGINAL_BUFFER_LEN / 16 + 64 + 3)

#endif	//_KG_GLOBAL_DEF_H_
