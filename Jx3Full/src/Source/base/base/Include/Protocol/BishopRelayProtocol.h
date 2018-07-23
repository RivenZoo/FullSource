#ifndef _BISHOP_RELAY_PROTOCOL_H_
#define _BISHOP_RELAY_PROTOCOL_H_

#include "../ProtocolBasic.h"

enum B2R_PROTOCOL_ID // Bishop ==> Relay
{
    B2R_PROTOCOL_BEGIN = PROTOCOL_NORMAL_PACKAGE_BEGIN,
    B2R_GAME_SERVER_LOGIN_NOTIFY,    // Game server登陆Bishop时通知Relay, ref : tagGameSvrLoginRelay
    B2R_PLAYER_LOGIN_REQUEST,        // 请求进入游戏: 剑三协议, ref : PLAYER_LOGIN_GAME_REQUEST
									 //	月影协议, ref : 
    B2R_DELETE_ROLE,                 // 查询角色是否可以删除, ref : tagNotifyToDelRole; 剑三: DELETE_ROLE_REQUEST
    B2R_EXT_POINTS_OPERATION_RESULT, // 附加点操作结果: 剑三协议, ref : B2R_REPLY_OPERATE_EXTPOINT
    B2R_QUERY_IDENTITY_INFO,         // 查询身份信息，就是原来发给relay的query map info 的协议，ref : tagQueryMapInfo
    B2R_PING,                        // ping , ref : PING_COMMAND
    B2R_QUERY_PLAYER_ONLINE_STATE,   // 查询玩家是否在线,可以通过设置标志位表示是否踢号, ref: QUERY_PLAYER_ONLINE_STATE
    B2R_NOTIFY_KICK_ACCOUNT,         // 通知Relay将在线账号踢下去, ref: NOTIFY_KICK_ACCOUNT
    B2R_CREATE_ROLE_REQUEST,         // 请求创建角色
    B2R_QUERY_HOMETOWN_LIST,         // 查询新手村列表
    B2R_ACCOUNT_USER_EXCHANGE_RESULT, // 金币兑换时间的应答协议, ref : KB2R_ACCOUNT_USER_EXCHANGE_RESULT
    B2R_ACCOUNT_TRANSFER_RESULT,      // 帐号之间转账应答协议, ref : KB2R_ACCOUNT_TRANSFER_RESULT
    B2R_PLAYER_QUERY_TRANSFER_RESULT, // 玩家转帐查询应答协议, ref : KB2R_PLAYER_QUERY_TRANSFER_RESULT
    B2R_PLAYER_FREEZE_FEE_RESULT,     // 金币冻结应答协议, ref : KB2R_PLAYER_FREEZE_FEE_RESULT
    B2R_QUERY_ROLE_LIST,              // 查询角色列表，剑三协议
    B2R_ACCOUNT_EXCHANGE_RESULT_EX,   // 玩家寄售
    B2R_QUERY_ZONE_CHARGE_FLAG_RESULT,// 查询ZoneChargeFlag
	B2R_NOTIFY_GROUP,				  // 通知区服配置
};

enum R2B_PROTOCOL_ID // Relay ==> Bishop
{
    R2B_PROTOCOL_BEGIN = PROTOCOL_NORMAL_PACKAGE_BEGIN,
    R2B_PLAYER_LOGIN_RESPOND,       // 玩家登陆的允许信息:  剑三协议, ref : PLAYER_LOGIN_GAME_RESPOND
									// 月影协议: PLAYER_LOGIN_GAME_RESPOND_YY
    R2B_DELETE_ROLE_RESULT,         // 请求删除角色的结果, ref : tagNewDelRoleResponse; 剑三: DELETE_ROLE_RESPOND
    R2B_EXT_POINTS_OPERATION,       // 请求附加点操作: 剑三协议, ref : R2B_OPERATE_EXTPOINT
    R2B_ADD_BLACK_LIST,             // 将指定帐号加入黑名单: 剑三协议, ref : 未定
    R2B_PLAYER_ENTER_GAME,          // 玩家进入游戏, 剑三协议, ref : R2B_PLAYER_LOGIN
    R2B_PLAYER_LEAVE_GAME,          // 玩家离开游戏, 剑三协议, ref : R2B_PLAYER_LOGOUT
    R2B_UPDATE_IDENTITY_INFO,       // 对应于上面的B2R_QUERY_IDENTITY_INFO的应答,ref : tagUpdateMapID
    R2B_PING,                       // ping back, ref : PING_COMMAND
    R2B_NOTIFY_GAME_WORLD_PROTOCOL_VERSION, // 通知Bishop游戏世界的版本号,  剑三协议, ref: NOTIFY_GAME_WORLD_PROTOCOL_VERSION
    R2B_RETURN_PLAYER_ONLINE_STATE, // 返回玩家在线状态, 如果查询时设置了踢号标志且玩家在线,则此时已经在踢号了, 剑三协议, ref: QUERY_PLAYER_ONLINE_STATE
    R2B_CREATE_ROLE_RESPOND,        // 创建角色返回信息
    R2B_SYNC_HOMETOWN_LIST,         // 更新新手村列表
    R2B_ACCOUNT_USER_EXCHANGE_REQUEST, // 金币兑换时间的请求协议, ref : KR2B_ACCOUNT_USER_EXCHANGE_REQUEST
    R2B_ACCOUNT_TRANSFER_REQUEST,   // 帐号之间转账请求协议, ref : KR2B_ACCOUNT_TRANSFER_REQUEST
    R2B_PLAYER_QUERY_TRANSFER_REQUEST, // 玩家转帐查询请求协议, ref : KR2B_PLAYER_QUERY_TRANSFER_REQUEST
    R2B_PLAYER_FREEZE_FEE_REQUEST,  // 金币冻结请求协议, ref : KR2B_PLAYER_FREEZE_FEE_REQUEST
    R2B_QUERY_ROLE_LIST_RESPOND,    // 查询角色列表，剑三协议
    R2B_ACCOUNT_EXCHANGE_REQUEST_EX,// 玩家寄售
    R2B_QUERY_ZONE_CHARGE_FLAG_REQUEST,  // 查询ZoneChargeFlag
	R2B_SET_AT_LEAST_GS_COUNT,		// 通知开始时最少多少个GS才允许玩家进入, ref : KR2B_AT_LEAST_GS_COUNT
};

#pragma	pack(push, 1)

struct tagNotifyGroup : public tagProtocolHeader
{
	int nAreaIdx;
	int nGroupIdx;
};

struct	tagGameSvrLoginRelay : public tagProtocolHeader2 
{
	unsigned int	uGameSvrIp;
	int				nMapCount;
	int				nMapIdList[0];
};

struct tagNotifyToDelRole : public tagProtocolHeader2
{
	char	szRoleName[_NAME_LEN];
};

struct  NOTIFY_GAME_WORLD_PROTOCOL_VERSION : public tagProtocolHeader2 // Relay ==> Bishop, 通知Bishop游戏世界<==>客户端的协议版本号
{
    int nGameWorldProtocolLowerVersion;
    int nGameWorldProtocolUpperVersion;
};

struct  QUERY_PLAYER_ONLINE_STATE : public tagProtocolHeader2   // Bishop ==> Relay,查询玩家是否已经在线
{
    char szAccountName[_NAME_LEN];
};

struct NOTIFY_KICK_ACCOUNT : public tagProtocolHeader2
{
    char szAccountName[_NAME_LEN];
};

struct RETURN_PLAYER_ONLINE_STATE : public tagProtocolHeader2 // Relay ==> Bishop, 返回玩家的在线状态
{
    int  nOnlineState; // 玩家是否在线? (true/false)
};


struct PLAYER_LOGIN_GAME_REQUEST : tagProtocolHeader2   // Bishop ==> Relay, 玩家选择角色请求登陆
{
    char            szAccountName[_NAME_LEN];
    DWORD           dwRoleID;
	tagExtPointInfo	ExtPointInfo;			// 可用的附送点
	tagExtPointInfo	ChangePointInfo;		// 变化的附送点
	unsigned long 	ulLeftTime;				// 剩余时间,以秒为单位,包括点数和包时(包天，包月)
    unsigned long   ulLimitPlayTimeFlag;     // 防沉迷标志位
    unsigned long   ulLimitOnlineSecond;     // 防沉迷累计在线时间
    unsigned long   ulLimitOfflineSecond;    // 防沉迷累计离线时间
};

typedef enum // 该枚举用于: 玩家请求进入游戏的时候, Relay返回请求结果到Bishop
{
    LOGIN_GAME_SUCCESS,         // 登陆请求被接受
    LOGIN_GAME_MAINTENANCE,     // 系统维护，通常是因为找不到MapID对应的Game server,而且也无法动态加载这个地图
    LOGIN_GAME_OVERLOADED,      // 找到了MapID对应的Game server,但是服务器负载已满，无法登陆
    LOGIN_GAME_UNKNOWN_ERROR    // 其他未知原因造成的无法登陆,比如: 已经登陆时,没有经过踢号就尝试登陆
} LOGIN_GAME_RESPOND_CODE;

struct PLAYER_LOGIN_GAME_RESPOND : tagProtocolHeader2   // Relay ==> Bishop, 玩家登陆请求的响应
{
	int			    nRespondCode; // LOGIN_GAME_RESPOND_CODE
    DWORD           dwRoleID;
	GUID		    Guid;
	DWORD			dwLoginIP;
	WORD	        wLoginPort;
};

struct PLAYER_LOGIN_GAME_RESPOND_YY : tagProtocolHeader2 // same with upper
{
	int			    nPermit;
	int				nServerIndex;
	char			szRoleName[32];
	GUID		    Guid;
	DWORD			dwLoginIP;
	WORD	        wLoginPort;
};

struct KR2B_AT_LEAST_GS_COUNT : tagProtocolHeader
{
	int nCount;
};

struct PLAYER_ENTER_GAME : tagProtocolHeader2   // Relay ==> Bishop, 通知消息: 玩家登陆游戏
{
	char szAccountName[_NAME_LEN];
};

struct PLAYER_LEAVE_GAME : tagProtocolHeader2   // Relay ==> Bishop, 玩家退出游戏
{
	char szAccountName[_NAME_LEN];
};

struct REQUEST_RELAY_DELETE_ROLE : tagProtocolHeader2 // Bishop ==> Relay, 请求删除角色(询问是否可以删除,帮主是不能删除的)
{
    char    szAccountName[_NAME_LEN];
	DWORD   dwRoleID;
};

struct RELAY_DELETE_ROLE_RESPOND : tagProtocolHeader2 // Relay ==> Bishop, 请求删除角色的结果(true/false)
{
	int			nResult; // 删除角色的结果(true/false)
};

struct EXT_POINT_OPERATION_REQUEST : tagProtocolHeader2 // Relay ==> Bishop,请求做附加点操作
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

struct EXT_POINT_OPERATION_RESPOND : tagProtocolHeader2 // Bishop ==> Relay, 附加点操作的结果
{
	int         nResult;
	char        szAccountName[_NAME_LEN];
	int         nFlag;
	int         nPlayerDataIndex;  // 玩家数据的索引号，用来处理返回协议	
};

struct KB2R_CREATE_ROLE_REQUEST : tagProtocolHeader2 // Bishop --> Relay, 请求创建角色
{
    char   szAccountName[_NAME_LEN];
};

struct KR2B_CREATE_ROLE_RESPOND : tagProtocolHeader2 // Bishop --> Relay, 创建角色的响应
{
    bool   bSucceed;
    size_t uDataLen;
    BYTE   byData[0];
};

// 查询手村别表,剑三协议
struct KB2R_QUERY_HOMETOWN_LIST : public tagProtocolHeader2
{
    int nReserved;
};

// 同步新手村别表,剑三协议
struct KR2B_SYNC_HOMETOWN_LIST : public tagProtocolHeader2
{
    size_t uDataLen;
    BYTE   byData[0];
};

// KR2B_SYNC_HOMETOWN_LIST协议中用来描述新手村数据的最大size
#define MAX_HOMETOWN_MAP_DESC_DATA_SIZE   1024

struct KR2B_ACCOUNT_USER_EXCHANGE_REQUEST : public tagProtocolHeader2
{
    char   szAccount[_NAME_LEN];
    DWORD  dwExchangeType;
    DWORD  dwDestAmount;                                    // 兑换成的数目
    DWORD  dwSrcAmount;                                     // 被兑换的数目
};

struct KB2R_ACCOUNT_USER_EXCHANGE_RESULT : public tagProtocolHeader2
{
    char   szAccount[_NAME_LEN];
    DWORD  dwExchangeType;
    DWORD  dwDestAmount;                                    // 兑换成的数目
    DWORD  dwSrcAmount;                                     // 被兑换的数目
    
    int    nResult;
};

struct KR2B_ACCOUNT_TRANSFER_REQUEST : public tagProtocolHeader2
{
    long long   llTransferGUID;                             // 交易操作的唯一编号,由游戏世界传给Paysys.丢包后查询的依据
    char        szAccountDest[_NAME_LEN];                   // 目标账户
    char        szAccountSrc[_NAME_LEN];                    // 源账户
    DWORD       dwTransferFlag;
    DWORD       dwTransferType;                             // 1: 计点转帐; 2: 金币转帐; 3: 扩展点转帐
    DWORD       dwExtPoint;                                 // 扩展点转帐时的扩展点索引
    DWORD       dwTransferAmount;                           // 转帐的数目
};

struct KB2R_ACCOUNT_TRANSFER_RESULT : public tagProtocolHeader2
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

struct KR2B_PLAYER_QUERY_TRANSFER_REQUEST : public tagProtocolHeader2
{
    long long llTransferGUID;                               // 交易操作的唯一编号, 由游戏世界传给Paysys
};

struct KB2R_PLAYER_QUERY_TRANSFER_RESULT : public tagProtocolHeader2
{
    long long llTransferGUID;                               // 交易操作的唯一编号, 由游戏世界传给Paysys
    DWORD     dwTransferTime;
    char      szAccountDest[_NAME_LEN]; 
    char      szAccountSrc[_NAME_LEN]; 
    DWORD     dwTransferFlag;
    DWORD     dwTransferType;
    DWORD     dwExtPoint;                                   // 若是扩展点冻结, 该字段为扩展索引（0～7）
    DWORD     dwTransferAmount;
    DWORD     dwTransferResult;

    int       nResult;
};

struct KR2B_PLAYER_FREEZE_FEE_REQUEST : tagProtocolHeader2
{
    long long   llFreezeGUID;
    char        szAccount[_NAME_LEN];
    DWORD       dwFreezeFlag;
    DWORD       dwFreezeType;
    DWORD       dwExtPoint;                                 // 若是扩展点冻结，该字段为扩展索引（0～7）
    DWORD       dwFreezeAmount;
};

struct KR2B_QUERY_ROLE_LIST_RESPOND : tagProtocolHeader2
{
    unsigned        uDataLen;
    unsigned char   byRoleList[0];
};

struct KB2R_PLAYER_FREEZE_FEE_RESULT : tagProtocolHeader2
{
    long long   llFreezeGUID;
    char        szAccount[_NAME_LEN];
    DWORD       dwFreezeFlag;
    DWORD       dwFreezeType;
    DWORD       dwExtPoint;                                 // 若是扩展点冻结，该字段为扩展索引（0～7）
    DWORD       dwFreezeAmount;

    int         nResult;
};

struct KR2B_ACCOUNT_EXCHANGE_REQUEST_EX : tagProtocolHeader2 
{
    char        szSrcAccount[_NAME_LEN];
    char        szDestAccount[_NAME_LEN];
    DWORD       dwExchangeType;
    DWORD       dwDestAmount;
    DWORD       dwSrcAmount;
};

struct KB2R_ACCOUNT_EXCHANGE_RESULT_EX : tagProtocolHeader2
{
    char        szSrcAccount[_NAME_LEN];
    char        szDestAccount[_NAME_LEN];
    DWORD       dwExchangeType;
    DWORD       dwDestAmount;
    DWORD       dwSrcAmount;

    int         nResult;
};

struct KB2R_QUERY_ROLE_LIST : tagProtocolHeader2
{
    char        szAccount[_NAME_LEN];
};

struct KR2B_QUERY_ZONE_CHARGE_FLAG_REQUEST : tagProtocolHeader2
{
    int nReserved;
};

struct KB2R_QUERY_ZONE_CHARGE_FLAG_RESULT : tagProtocolHeader2
{
    int  nZoneChargeFlag;
    int  nZoneID;
    char szZoneName[32];
};


#pragma pack(pop)

#endif

