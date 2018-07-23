////////////////////////////////////////////////////////////////////////////////
//
//  FileName    : KItemDef.h
//  Version     : 1.0
//  Creator     : Chen Jie, Xia Yong
//  Comment     : 道具系统
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _KITEM_DEF_H_
#define _KITEM_DEF_H_

#define MAX_ITEM_DATA_SIZE sizeof(KCUSTOM_EQUI_DATA)

#pragma	pack(1)
enum ENCHANT_INDEX
{
    eiPermanentEnchant = 0,
    eiTemporaryEnchant,

    eiMount1,
    eiMount2,
    eiMount3,
    eiMount4,

    eiTotal
};

struct KCOMMON_ITEM_DATA 
{
    BYTE    byVersion;
    BYTE    byTabType;
    WORD    wTabIndex;
    BYTE    byBind;
    WORD    wDurability;
    time_t	nGenTime;
};

struct KCUSTOM_EQUI_DATA : KCOMMON_ITEM_DATA
{
    DWORD   dwRandSeed;
    WORD    wEnchant[eiTotal];
    WORD    wLeftEnchantTime;
    BYTE    byColorID;
};

struct KITEM_DB_HEADER 
{
    BYTE byBox;
    BYTE byPos;
    BYTE byDataLen;
    BYTE byData[0];
};
#pragma	pack()

#define CURRENT_ITEM_DATA_VERSION 0

// 道具的种类
enum ITEM_GENRE
{
    igEquipment = 0,	// 装备
    igPotion,			// 药品
    igTaskItem,			// 任务道具
    igMaterial,			// 材料
    igBook,				// 书籍
    igDesignation,      // 称号道具
    igMountItem,        // 镶嵌道具
    igEnchantItem,      // 附魔道具

    igTotal
};

// 装备的大致分类
enum EQUIPMENT_SUB_TYPE
{
    estMeleeWeapon = 0,		// 近战武器
    estRangeWeapon,			// 远程武器
    estChest,				// 上衣
    estHelm,				// 头部
    estAmulet,				// 项链
    estRing,				// 戒指
    estWaist,				// 腰带
    estPendant,				// 腰缀
    estPants,				// 裤子
    estBoots,				// 鞋子
    estBangle,				// 护臂
    estWaistExtend,		    // 腰部扩展类装备，酒壶之类的
    estPackage,				// 包裹
    estArrow,				// 暗器
    estBackExtend,          // 背部扩展
    estHorse,               // 坐骑
    estTotal
};

// 武器的具体分类
enum WEAPON_DETAIL_TYPE
{
    wdtWand = 0,	    // 棍
    wdtSpear,           // 枪
    wdtSword,           // 剑
    wdtFist,            // 拳套
    wdtDoubleWeapon,    // 双手武器,比如: 双刀,双伞
    wdtPen,             // 笔
    wdtSlingShot,       // 钝器
    wdtDart,            // 锐器
    wdtMachDart,        // 机关暗器

    wdtTotal
};

// 镶嵌道具的子类, 与装备子类保持一致
enum ENCHANT_SUB_TYPE
{
    nstMeleeWeapon = estMeleeWeapon,    // 近战武器
    nstRangeWeapon = estRangeWeapon,    // 远程武器
    nstHorse       = estHorse           // 马具
};

// 马具的细类
enum ENCHANT_DETAIL_TYPE
{
    edtHead,            // 头饰
    edtChest,           // 胸饰
    edtFoot,            // 足饰
    edtHangItem,        // 挂件

    edtTotal
};

// 道具品质
enum ITEM_QUALITY
{
    iqLow = 0,				// 劣品
    iqNormal,				// 普通装备，白色
    iqGood,					// 优质
    iqTotal
};

// 绑定类型
enum ITEM_BIND_TYPE
{
    ibtInvalid = 0,
    ibtNeverBind,
    ibtBindOnEquipped,
    ibtBindOnPicked,
    ibtBindOnTimeLimitation,
    ibtTotal
};

enum ITEM_USE_TARGET_TYPE
{
    iuttInvalid = 0,

    iuttNoTarget,
    iuttSelf,
    iuttOtherPlayer,
    iuttNpc,
    iuttCoordinates,
    iuttDoodad,
    iuttItem,

    iuttTotal
};

#endif //_KITEM_DEF_H_
