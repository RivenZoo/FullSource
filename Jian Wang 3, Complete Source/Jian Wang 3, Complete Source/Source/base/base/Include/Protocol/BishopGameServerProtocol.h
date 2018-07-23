#ifndef _BISHOP_GAME_SERVER_PROTOCOL_H_
#define _BISHOP_GAME_SERVER_PROTOCOL_H_

#include "../ProtocolBasic.h"

enum B2G_PROTOCOL_ID // Bishop ==> Game server
{
    B2G_PROTOCOL_BEGIN = PROTOCOL_BIG_PACKAGE_BEGIN,
    B2G_PLAYER_LOGIN_REQUEST,                   // 玩家请求进入游戏，传递角色数据到Game server,ref : tagGuidableInfo + role data
    B2G_QUERY_SERVER_INFO = PROTOCOL_NORMAL_PACKAGE_BEGIN + 1,  // 查询game server基本信息, ref : tagQueryGameSvrInfo
    B2G_QUERY_MAP_INFO,                         // 查询地图加载信息, ref : tagQueryMapInfo
    B2G_EXT_POINTS_OPERATION_RESULT,            // 附加点操作结果
    B2G_OFFLINE_LIVE_KICK_ACCOUNT_REQUEST,      // 离线挂机中请求踢号!
    B2G_PRE_TRANSFER_SERVER_RET,                // 附加点操作的结果返回, ref :tagReturnChangeExtPoint
    B2G_ACCOUNT_FREE_TIME_CLEANING_RESULT,      // 清除新手帐号的免费时间操作的结果, ref : TRYOUT_TIMEOUT_RES
    B2G_GATEWAY_BROADCAST,                      // 发送系统广播, ref : tagGatewayBroadCast
    B2G_PING,                                   // 回ping包, ref: PING_COMMAND
    B2G_USE_SPREADER_CDKEY_RET,                 // 回新手推广CDKEY处理的结果, ref: tagUseSpreaderCDKey
    B2G_CONFIRM_ACCOUNT_OFFLINE_REQUEST,        // 确认玩家帐号没有在游戏世界中, ref : CONFIRM_ACCOUNT_OFFLINE_REQUEST
    B2G_IB_PLAYER_BUY_ITEM_RESULT,              // 玩家在IB模式下购买物品的回应包。
    B2G_IB_PLAYER_USE_ITEM_RESULT,              // 玩家在IB模式下使用物品的回应包。
    B2G_PLAYER_SET_CHARGE_FLAG_RET,             // 修改用户Charge_Flag结果
    B2G_ACCOUNT_TRANSFER_RESULT,                // 帐号之间转账结果
    B2G_ACCOUNT_USER_EXCHANGE_RESULT,           // 玩家金币兑换时间应答包
    B2G_PLAYER_QUERY_TRANSFER_RESULT,           // 玩家转帐查询的回应包
    B2G_PLAYER_FREEZE_FEE_RESULT,               // 玩家冻结费用回应包
    B2G_PAYSYS_2_GAMEWORLD,                     // 这是个通用协议: Paysys到游戏世界
	B2G_SERVER_CONNECTEDINIT_READY,				// 网关对GameServer连接的初始化完成
    B2G_IB_PLAYER_BUY_MULTI_ITEM_RESULT,        // 玩家在IB模式下购买多个物品的回应包
    B2G_IB_PLAYER_USE_MULTI_ITEM_RESULT,        // 玩家在IB模式下使用多个物品的回应包
    B2G_PLAYER_INFO_RESULT,                     // 获取帐号信息返回
    B2G_IB_PLAYER_BUY_ITEM_RESULT_SD,           // 盛大玩家在IB模式下购买物品的返回
    B2G_IB_PLAYER_BUY_MULTI_ITEM_RESULT_SD,     // 盛大玩家在IB模式下购买多个物品的返回
};

enum G2B_PROTOCOL_ID // Game server ==> Bishop
{
    G2B_PROTOCOL_BEGIN = PROTOCOL_NORMAL_PACKAGE_BEGIN,
    G2B_UPDATE_SERVER_INFO,                 // 更新server信息, ref : tagGameSvrInfo
    G2B_UPDATE_MAP_INFO,                    // 更新地图信息, ref : tagUpdateMapID
    G2B_PLAYER_LOGIN_PERMISSION,            // 玩家登陆的允许信息!
    G2B_PLAYER_ENTER_GAME,                  // 玩家进入游戏, ref : tagEnterGame
    G2B_PLAYER_LEAVE_GAME,                  // 玩家离开游戏, ref : tagLeaveGame
    G2B_PRE_TRANSFER_SERVER,                // 跨服通知(这个玩家即将跨到我这里来了), ref : tagRegisterAccount (新: + RELAY_DATA + tagPermitPlayerExchange)
    G2B_EXT_POINTS_OPERATION,               // 请求附加点操作, ref : tagChangeExtPoint
    G2B_ADD_PLAYER_TO_BLACK_LIST,           // 将指定帐号加入黑名单, ref : TDenyAccount
    G2B_DYNAMIC_UPDATE_MAP_INFO,            // 动态更新地图, ref : tagDynamicUpdateMapID
    G2B_PLAYER_OFFLINE_LIVE_NOTIFY,         // 通知Bishop,该帐号离线挂机, ref : tagOfflineRequestAsk
    G2B_PLAYER_OFFLINE_LIVE_TIMEOUT,        // 玩家的离线挂机时间用完了, ref : tagOfflineTimeoutRes
    G2B_OFFLINE_LIVE_KICK_ACCOUNT_RESULT,   // 离线挂机踢号的结果, ref : tagOfflineKickoutRes
    G2B_CLEANUP_ACCOUNT_FREE_TIME,          // 清除新手帐号的免费时间, ref : TRYOUT_TIMEOUT_REQ
    G2B_PING,                               // ping包，ref : PING_COMMAND
    G2B_USE_SPREADER_CDKEY,                 // 传递新手推广CDKEY给PaySys, ref: tagUseSpreaderCDKeyRet
    G2B_CONFIRM_ACCOUNT_OFFLINE_RESPOND,    // 确认玩家没有在游戏里面, ref : CONFIRM_ACCOUNT_OFFLINE_RESPOND
    G2B_IB_PLAYER_BUY_ITEM,                 // 玩家在IB模式下购买物品。
    G2B_IB_PLAYER_USE_ITEM,                 // 玩家在IB模式下使用物品。
    G2B_DYNAMIC_UPDATE_SERVER_INFO,         // 动态更新server信息 ref : tagDynamicUpdateSvrInfo
    G2B_PLAYER_SET_CHARGE_FLAG_REQ,         // 修改用户Charge_Flag请求
    G2B_ACCOUNT_TRANSFER_REQUEST,           // 帐号之间转账请求
    G2B_ACCOUNT_USER_EXCHANGE,              // 玩家金币兑换时间
    G2B_PLAYER_QUERY_TRANSFER,              // 玩家转帐查询
    G2B_PLAYER_FREEZE_FEE,                  // 玩家冻结费用
    G2B_GAMEWORLD_2_PAYSYS,                 // 这是个通用协议: 游戏世界到Paysys的请求
    G2B_IB_PLAYER_BUY_MULTI_ITEM,           // 玩家在IB模式下购买多个物品
    G2B_IB_PLAYER_USE_MULTI_ITEM,           // 玩家在IB模式下使用多个物品
    G2B_QUERY_PLAYER_INFO,                  // 获取帐号信息
    G2B_IB_PLAYER_BUY_ITEM_SD,              // 盛大玩家在IB模式下购买物品
    G2B_IB_PLAYER_BUY_MULTI_ITEM_SD,        // 盛大玩家在IB模式下购买多个物品
    G2B_NOTIFY_SVR_FUNC_TYPE,				// 通知bishop本条线的类型
};

enum SvrFuncNotifyType
{
	SFNT_FUNCTYPE = 0,
	SFNT_FUNCLIST,
	SFNT_FUNCALL,
};

#pragma	pack(push, 1)

#define	AP_WARNING_ALL_PLAYER_QUIT			1
#define	AP_NOTIFY_GAMESERVER_SAFECLOSE		2
#define	AP_NOTIFY_ALL_PLAYER				3
#define	AP_NOTIFY_PLAYER_KICKOUT			4
#define	MAX_GATEWAYBROADCAST_LEN	260
struct tagGatewayBroadCast : public tagProtocolHeader2
{
    UINT	uCmdType;
    char	szData[MAX_GATEWAYBROADCAST_LEN];
};


struct tagQueryGameSvrInfo : public tagProtocolHeader
{	
	int nZoneID;
};

struct tagGameSvrFuncTypeInfo : public tagProtocolHeader
{	
	BYTE		byNotifyType;		//通知修改的类型，见上面的枚举SvrFuncNotifyType
	WORD		wSvrFuncType;
	DWORD		dwSvrFuncList;
};

struct tagGameSvrInfo : public tagProtocolHeader
{
    UINT			nIPAddr_Intraner;
    UINT			nIPAddr_Internet;

    unsigned short	nPort;
    WORD			wCapability;
    int				nGameWorldLowerVersion; // 游戏逻辑 <--> 客户端协议最低版本号
    int				nGameWorldUpperVersion; // 游戏逻辑 <--> 客户端协议最高版本号
};

struct tagPermitPlayerLogin : public tagProtocolHeader2
{
    GUID guid;
    char szAccountName[_NAME_LEN];
    char szRoleName[_NAME_LEN];
    bool bPermit;
};




struct tagEnterGame : public tagProtocolHeader
{
    char szAccountName[_NAME_LEN];
};

#define NORMAL_LEAVEGAME	0x0		// lock account
#define HOLDACC_LEAVEGAME	0x1A	// clear resource but don't to unlock account 

struct tagLeaveGame : public tagProtocolHeader
{
    BYTE cCmdType;
    WORD nExtPoint;        //将要扣除的附送点
    char szAccountName[_NAME_LEN];
};


struct tagRegisterAccount : public tagProtocolHeader
{
    char szAccountName[_NAME_LEN];
};


#define CHANGE_EXT_POINT_SILVER	0x1

struct tagChangeExtPoint : public tagProtocolHeader
{
    char szAccountName[_NAME_LEN];
    union
    {
        unsigned uExtPointIndex;    // 将要改变的附加点的索引
        unsigned uSilverType;       // 银票的类型，高16位（0：表示大银票，1：表示小银票）
        //             低16位（0：转为点数，：转为包（周）月）
    };
    int      nChangeValue;      // 附加点被修改的值，可正可负，或者银票的数目
    unsigned uFlag;             // 如果是0表示附加点的变化，如果是CHANGE_EXT_POINT_SILVER : 表示银票的处理
    int      nPlayerDataIndex;  // 玩家数据的索引号，用来处理返回协议
};

struct tagReturnChangeExtPoint : public tagProtocolHeader
{
    int nResult;
    char szAccountName[_NAME_LEN];
    unsigned uFlag;
    int      nPlayerDataIndex;  // 玩家数据的索引号，用来处理返回协议
};

struct tagDynamicUpdateMapID : public tagProtocolHeader
{
    BOOL	bRelay;	//如果是relay则，填1，如果是gameserver则填0
    int		nMapId;
    int		nMapCopyId;
    int		nAction;	//1表示注册，0表示注销
};

struct tagDynamicUpdateSvrInfo : public tagProtocolHeader
{
    int nPlayerCount;
};

struct tagOfflineRequestReq : public ProtocolHeader//PROTOCOL_MSG_HEADER
{
    char szAccount[_NAME_LEN];	// 账号名，包含结束符
    char szRole[_NAME_LEN];		// 角色名，包含结束符
};

struct tagOfflineRequestAsk : public tagOfflineRequestReq
{
    DWORD dwMapId;				// 玩家所在的地图ID
    int	  nIndex;				// GameServer中的玩家索引
};

struct tagOfflineRequestRes : public tagOfflineRequestReq
{
    BYTE	nResult;			// 结果。1：成功，0：失败
    BYTE	nReason;			// 失败原因：成功时为0
    DWORD	dwLeftTime;			// 剩余离线挂机时间，单位是分钟
};

// 离线挂机踢号请求
struct tagOfflineKickoutAsk : public ProtocolHeader2 //PROTOCOL_MSG_HEADER
{
    char szAccount[_NAME_LEN];	// 账号名，包含结束符
    int	 nIndex;				// GameServer中的玩家索引
};

// 离线挂机踢号结果
struct tagOfflineKickoutRes : public ProtocolHeader2 //PROTOCOL_MSG_HEADER
{
    char szAccount[_NAME_LEN];	// 账号名，包含结束符
    BYTE nResult;				// 1表示存盘成功，0表示存盘失败
    WORD wExtPoint;				// 扩展点
};

// 离线挂机超时结果
struct tagOfflineTimeoutRes : public tagOfflineRequestReq
{
    WORD	wExtPoint;			// 扩展点
};

struct TDenyAccount : public tagProtocolHeader
{
    char	szAccount[_NAME_LEN];	// 账号名
    DWORD	dwTimeout;				// 禁止登录的时间间隔(s)
};

/**
* @description 未充值的新手账号到了20级（可设定）时，即使免费的10小时未使用完，
也将被从游戏世界中踢除，同时向paysys发送协议将可使用时间设置为0
* @protocol	c2s_tryout_timeout_req GameServer=>Bishop
* @author		wangbin
* @datetime	2004-12-28 09:57
*/
struct TRYOUT_TIMEOUT_REQ
{
    BYTE	ProtocolType;
    BYTE	nReason;				// 原因（保留）
    char	szAccount[_NAME_LEN];	// 账号名
    int		nPlayerIndex;			// 玩家数组索引
};

/**
* @description 未充值的新手账号到了20级（可设定）时，即使免费的10小时未使用完，
也将被从游戏世界中踢除，同时向paysys发送协议将可使用时间设置为0。
从网关主动踢号也走这个协议。
* @protocol	s2c_tryout_timeout_res Bishop=>GameServer
* @author		wangbin
* @datetime	2004-12-28 09:57
*/
struct TRYOUT_TIMEOUT_RES
{
    BYTE	ProtocolType;
    BYTE	nResult;				// 处理结果，1为成功，0为失败
    char	szAccount[_NAME_LEN];	// 账号名
    int		nPlayerIndex;			// 玩家数组索引
};

struct tagUseSpreaderCDKey : public ProtocolHeader
{
    char szAccountName[_NAME_LEN];
    char szCDKey[_NAME_LEN];
    int  nPlayerDataIndex;	
};

struct tagUseSpreaderCDKeyRet : public ProtocolHeader
{
    char szAccountName[_NAME_LEN];
    int  nPlayerDataIndex;
    int  nResult;
};

struct CONFIRM_ACCOUNT_OFFLINE_REQUEST : public ProtocolHeader2
{
    char szAccountName[_NAME_LEN];
};

struct CONFIRM_ACCOUNT_OFFLINE_RESPOND : public ProtocolHeader2
{
    int nReserve;   // 保留位，填0即可
};

#define MAX_ITEM_COUNT_IN_PACKAGE_FROM_SERVER 16

struct KG2BAccountBuyItem : public ProtocolHeader2
{
    char        szAccount[_NAME_LEN];
    int         nPlayerDataIndex;                                  // 玩家在游戏世界的编号
    int         nGoodsIndex;                                       // 商品在商品的编号
    int         nItemTypeID;                                       // 物品类型ID
    int         nItemLevel;                                        // 物品级别(与物品类型ID一起唯一定位物品)
    int         nUseType;                                          // 使用类型(enumIB_ItemUseType)
    int         nPrice;                                            // 购买价格
    DWORD       dwOverdueTime;                                     // 保期期(差值)
};

#define MAX_SD_UNIQUEID_SIZE 33
struct KG2BAccountBuyItemSD : public KG2BAccountBuyItem
{
    char        szSDUniqueId[MAX_SD_UNIQUEID_SIZE];
};

struct KG2BAccountBuyMultiItem : public ProtocolHeader2
{
    char        szAccount[_NAME_LEN];
    int         nPlayerDataIndex;                                  // 玩家在游戏世界的编号
    int         nGoodsIndex;                                       // 商品在商品的编号
    int         nItemTypeID;                                       // 物品类型ID
    int         nItemLevel;                                        // 物品级别(与物品类型ID一起唯一定位物品)
    int         nUseType;                                          // 使用类型(enumIB_ItemUseType)
    int         nPrice;                                            // 购买价格
    DWORD       dwOverdueTime;                                     // 保期期(差值)
    int         nItemCount;                                        // 请求的物品数量
    BYTE        byUseItemNow;                                      // 购买的同时使用掉物品
};

struct KG2BAccountBuyMultiItemSD : public KG2BAccountBuyMultiItem
{
    char        szSDUniqueId[MAX_SD_UNIQUEID_SIZE];
};

struct KG2BAccountUseItem : public ProtocolHeader2
{
    char        szAccount[_NAME_LEN];
    int         nPlayerDataIndex;                                   // 玩家在游戏世界的编号
    int         nItemTypeID;                                        // 物品类型ID
    int         nItemLevel;                                         // 物品级别(与物品类型ID一起唯一定位物品)
    long long   llItemGUID;                                         // 物品在数据库的唯一编号
};

struct KG2BAccountUseMultiItem : public ProtocolHeader2
{
    char        szAccount[_NAME_LEN];
    int         nPlayerDataIndex;                                   // 玩家在游戏世界的编号
    int         nItemTypeID;                                        // 物品类型ID
    int         nItemLevel;                                         // 物品级别(与物品类型ID一起唯一定位物品)
    int         nItemCount;                                         // 请求的物品数量
    long long   llItemGUID[MAX_ITEM_COUNT_IN_PACKAGE_FROM_SERVER];  // 物品在数据库的唯一编号
};

struct KB2GAccountBuyItemRet : public ProtocolHeader2
{
    char         szAccount[_NAME_LEN];
    int          nPlayerDataIndex;                                  // 玩家在游戏世界的编号
    int          nGoodsIndex;                                       // 商品在商品的编号
    int          nItemTypeID;                                       // 物品类型ID
    int          nItemLevel;                                        // 物品级别(与物品类型ID一起唯一定位物品)
    int          nPrice;                                            // 购买价格
    long long    llItemGUID;                                        // 物品在数据库的唯一编号
    int          nResult;                                           // 结果返回码
};

struct KB2GAccountBuyItemRetSD : public KB2GAccountBuyItemRet
{
    char        szSDUniqueId[MAX_SD_UNIQUEID_SIZE];
};

struct KB2GAccountBuyMultiItemRet : public ProtocolHeader2
{
    char         szAccount[_NAME_LEN];
    int          nPlayerDataIndex;                                  // 玩家在游戏世界的编号
    int          nGoodsIndex;                                       // 商品在商品的编号
    int          nItemTypeID;                                       // 物品类型ID
    int          nItemLevel;                                        // 物品级别(与物品类型ID一起唯一定位物品)
    int          nPrice;                                            // 购买价格
    int          nItemCount;                                        // 请求的物品数量
    long long    llItemGUID[MAX_ITEM_COUNT_IN_PACKAGE_FROM_SERVER]; // 物品在数据库的唯一编号
    int          nResult;                                           // 结果返回码
};

struct KB2GAccountBuyMultiItemRetSD : public KB2GAccountBuyMultiItemRet
{
    char        szSDUniqueId[MAX_SD_UNIQUEID_SIZE];
};

struct KB2GAccountUseItemRet : public ProtocolHeader2
{
    char        szAccount[_NAME_LEN];
    int         nPlayerDataIndex;                                   // 玩家在游戏世界的编号
    int         nItemTypeID;                                        // 物品类型ID
    int         nItemLevel;                                         // 物品级别(与物品类型ID一起唯一定位物品)
    long long   llItemGUID;                                         // 物品在数据库的唯一编号
    int         nResult;                                            // 结果返回码
};

struct KB2GAccountUseMultiItemRet : public ProtocolHeader2
{
    char        szAccount[_NAME_LEN];
    int         nPlayerDataIndex;                                   // 玩家在游戏世界的编号
    int         nItemTypeID;                                        // 物品类型ID
    int         nItemLevel;                                         // 物品级别(与物品类型ID一起唯一定位物品)
    int         nItemCount;                                         // 请求的物品数量
    long long   llItemGUID[MAX_ITEM_COUNT_IN_PACKAGE_FROM_SERVER];  // 物品在数据库的唯一编号
    int         nResult;                                            // 结果返回码
};

struct KB2GPlayerSetChargeFlagReq : public ProtocolHeader2
{
    char    szAccount[_NAME_LEN];
    DWORD   dwLastLoginIP;
    int     nChargeFlag;                                    // 0:免费,1:收费
};

struct KB2GPlayerSetChargeFlagRet : public ProtocolHeader2
{
    char    szAccount[_NAME_LEN];
    int     nChargeFlag;                                    // 0:免费,1:收费
    int     nResult;
};

struct KG2BAccountTransferRequest : public ProtocolHeader2
{
    long long   llTransferGUID;                             // 交易操作的唯一编号,由游戏世界传给Paysys.丢包后查询的依据
    char        szAccountDest[_NAME_LEN];                   // 目标账户
    char        szAccountSrc[_NAME_LEN];                    // 源账户
    DWORD       dwTransferFlag;
    DWORD       dwTransferType;                             // 1: 计点转帐; 2: 金币转帐; 3: 扩展点转帐
    DWORD       dwExtPoint;                                 // 扩展点转帐时的扩展点索引
    DWORD       dwTransferAmount;                           // 转帐的数目
};

struct KB2GAccountTransferResult : public ProtocolHeader2
{
    long long   llTransferGUID;                             // 交易操作的唯一编号,由游戏世界传给Paysys.丢包后查询的依据
    char        szAccountDest[_NAME_LEN];                   // 目标账户
    char        szAccountSrc[_NAME_LEN];                    // 源账户
    DWORD       dwTransferFlag;   
    DWORD       dwTransferType;                             // 1: 计点转帐, 2: 金币转帐, 3: 扩展点转帐
    DWORD       dwExtPoint;                                 // 扩展点转帐时的扩展点索引
    DWORD       dwTransferAmount;                           // 转帐的数目
    int         nResult;                                    // 1 成功, 2: 失败, 3: 找不到帐号, 1100: 金币余额不足
};

struct KG2BAccountUserExchange : public ProtocolHeader2
{
    char   szAccount[_NAME_LEN];
    DWORD  dwExchangeType; 
    DWORD  dwDestAmount;                                    // 兑换成的数目
    DWORD  dwSrcAmount;                                     // 被兑换的数目
};

struct KB2GAccountUserExchangeResult : public ProtocolHeader2
{
    char   szAccount[_NAME_LEN];
    DWORD  dwExchangeType; 
    DWORD  dwDestAmount;                                    // 兑换成的数目
    DWORD  dwSrcAmount;                                     // 被兑换的数目
    
    int    nResult;
};


struct KG2BAccountQueryTransfer : ProtocolHeader2
{
    long long llTransferGUID;                               // 交易操作的唯一编号,由游戏世界传给Paysys
};

struct KB2GAccountQueryTransferResult : ProtocolHeader2
{
    long long llTransferGUID;                               // 交易操作的唯一编号,由游戏世界传给Paysys
    DWORD     dwTransferTime;
    char      szAccountDest[_NAME_LEN]; 
    char      szAccountSrc[_NAME_LEN]; 
    DWORD     dwTransferFlag;
    DWORD     dwTransferType;
    DWORD     dwExtPoint;                                   // 若是扩展点冻结，该字段为扩展索引（0～7）
    DWORD     dwTransferAmount;
    DWORD     dwTransferResult;

    int       nResult;
};

struct KG2BPlayerFreezeFee : ProtocolHeader2
{
    long long   llFreezeGUID;
    char        szAccount[_NAME_LEN];
    DWORD       dwFreezeFlag;
    DWORD       dwFreezeType;
    DWORD       dwExtPoint;                                // 若是扩展点冻结，该字段为扩展索引（0～7）
    DWORD       dwFreezeAmount;
};

struct KB2GPlayerFreezeFeeResult : ProtocolHeader2
{
    long long   llFreezeGUID;
    char        szAccount[_NAME_LEN];
    DWORD       dwFreezeFlag;
    DWORD       dwFreezeType;
    DWORD       dwExtPoint;                                // 若是扩展点冻结，该字段为扩展索引（0～7）
    DWORD       dwFreezeAmount;

    int         nResult;
};

struct KG2BGameworld2Paysys : ProtocolHeader2
{
    unsigned uDataSize;
    BYTE     byData[0];
};

struct KB2GPaysys2Gameworld : ProtocolHeader2
{
    unsigned uDataSize;
    BYTE     byData[0];
};

struct KG2BQueryPlayerInfo : ProtocolHeader2
{
    char     szAccount[_NAME_LEN]; 
};

struct KB2GPlayerInfoResult : ProtocolHeader2
{
    int               nResult;
    char              szAccount[_NAME_LEN];
    tagExtPointInfo   ExtPointInfo;
    DWORD             dwEndDate;
    DWORD             dwLeftSecond;
    DWORD             dwLastLoginTime;
    DWORD             dwLastLoginIP;
    DWORD             dwLeftCoin;            //剩余金币
    DWORD             dwLastLogoutTime;
    DWORD             dwActiveIP;
    DWORD             dwActiveTime;
    DWORD             dwActiveType;
};

#pragma pack(pop)

#endif
