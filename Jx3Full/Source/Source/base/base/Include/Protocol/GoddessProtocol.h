#ifndef _GODDESS_PROTOCOL_H_
#define _GODDESS_PROTOCOL_H_

#include "../ProtocolBasic.h"

enum GODDESS_C2S_PROTOCOL_ID    // Goddess client ==> server
{
    GODDESS_C2S_PROTOCOL_BEGIN = PROTOCOL_BIG_PACKAGE_BEGIN,
    GDC2S_SAVE_ROLE_DATA,         // 存储角色数据, ref : TProcessData
    GDC2S_SET_STATISTIC_INFO,     // 更新统计信息, ref : TProcessData

    GDC2S_PING = PROTOCOL_NORMAL_PACKAGE_BEGIN + 1, // ping, ref : PING_COMMAND
    GDC2S_QUERY_ROLE_LIST,        // 获取角色列表, ref : TProcessData
    GDC2S_QUERY_ROLE_DATA,        // 获取角色数据, ref : TProcessData
    GDC2S_CREATE_ROLE,            // 创建角色, ref : TProcessData
    GDC2S_DELETE_ROLE,            // 删除角色, ref : TProcessData

    GDC2S_LOCK_OR_UNLOCK_ROLE,    // 角色数据加/解锁操作, ref : LOCK_OR_UNLOCK_ROLE
    GDC2S_PLAYER_ENTER_GAME,      // 角色进入游戏, ref : TProcessData
    GDC2S_PLAYER_LEAVE_GAME,      // 角色离开游戏或者是进入游戏失败, ref : TProcessData
    GDC2S_SHUTDOWN_GODDESS,       // 从网关关闭Goddess, ref : TProcessData
    GDC2S_QUERY_STATISTIC_INFO,   // 获取统计信息, ref : TProcessData
    GDC2S_TRANSFER_ROLE,          // 角色数据转服, ref : ???
    GDC2S_QUERY_ROLE_LIST_ITEM,   // 获取单个角色列表信息, ref : TProcessData

    GDC2S_LOCK_OR_UNLOCK_ROLE_EXT,// 角色数据加/解锁操作, 该操作有返回包 ref : LOCK_OR_UNLOCK_ROLE_EXT
    GDC2S_CREATE_TONGNAME,        // 创建帮会名，ref : CREATE_TONG_NAME
    GDC2S_QUERY_ROLE_LIST_IN_ZONE,// 获取一个大区内一个账号的所有角色名和其所在服务器，ref : TProcessData
	GDC2S_CANCLE_TONGNAME,		  // 取消一个帮会名的注册 ref: TProcessData

	GDC2S_SYNC_ZONE_INFO,			// 通知区服信息过来 ref: TRocessData, pDataBuffer=szGroup
	GDC2S_ROLE_BASE_OPER,			// 对角色数据的一些基本操作协议 ref:TProcessData
	GDC2S_USE_CHICKEN_HORSE,		// 使用激活码 ref:CHICKEN_HORSE
	GDC2S_LOTTERY_REQUEST,			// 奖券相关请求
	GDC2S_LIMITE_OUTPUT_REQUEST,	// 全区限制产出请求
};

enum GODDESS_S2C_PROTOCOL_ID     // Goddess server ==> client
{
    GODDESS_S2C_PROTOCOL_BEGIN = PROTOCOL_BIG_PACKAGE_BEGIN,
    GDS2C_RETURN_ROLE_DATA,       // 返回角色数据, ref : TProcessData + role data
    GDS2C_CREATE_ROLE_RESULT,     // 创建角色数据的操作结果, ref : TProcessData,pDataBuf[0]取值参见enum CREATE_ROLE_RESULT
    GDS2C_RETURN_ROLE_LIST_ITEM,  // 返回单个角色列表信息, ref : TProcessData

    GDS2C_PING = PROTOCOL_NORMAL_PACKAGE_BEGIN + 1, // ping back, ref : PING_COMMAND    

    GDS2C_RETURN_ROLE_LIST,       // 返回角色列表, ref : TProcessData + role list data(如果本区role_list_num为0则后面跟QueryFamilyListInZone()的结果)
    GDS2C_SAVE_ROLE_DATA_RESULT,  // 存储角色数据返回结果, ref : TProcessData
    GDS2C_DELETE_ROLE_RESULT,     // 删除角色数据返回结果, ref : TProcessData
    GDS2C_SHUTDOWN_CMD_RESPOND,   // 剑网新加协议: 关闭命令的响应结果, ref : TProcessData
    GDS2C_RETURN_STATISTIC_INFO,  // 返回统计信息, ref : TProcessData

    GDS2C_RETURN_LOCK_OR_UNLOCK_ROLE_EXT, // 返回角色数据加/解锁的操作结果, ref : TProcessData,  
                                          // TProcessData.pDataBuffer[0]:0 failed, TProcessData.pDataBuffer[0]:1 success

    GDS2C_CREATE_TONGNAME_RESULT, // 返回创建帮会名的结果, ref : TProcessData
                                  // TProcessData.pDataBuffer[0]:0 failed, TProcessData.pDataBuffer[0]:1 success

    GDS2C_SET_STATISTIC_INFO_RESULT,   // 更新统计信息返回结果, ref : TProcessData,
                                       // TProcessData.pDataBuffer[0]:0 failed, TProcessData.pDataBuffer[0]:1 success
    GDS2C_RETURN_ROLE_LIST_IN_ZONE,     // 返回一个大区内一个账号的所有角色名及其所在服务器，ref : TProcessData,ROLE_IN_ZONE
                                       // TProcessData.pDataBuffer[0]  : 0 failed, 1 success
                                       // &TProcessData.pDataBuffer[1] : (unsigned)uRoleCount + ROLE_IN_ZONE[uRoleCount]
	GDS2C_SYNC_ZONE_INFO_RET,		// 返回区服同步结果 ref:TProcessData pDataBuffer=true false
	GDS2C_ROLE_BASE_OPER_RET,		// 返回角色基本操作的结果 ref:TProcessData
	GDS2C_USE_CHICKEN_HORSE_RET,	// 返回使用激活码操作的结果 ref:CHICKEN_HORSE
	GDS2C_LOTTERY_RESPONSE,			// 奖券相关
	GDS2C_LIMITE_OUTPUT_RESPONSE,	// 全区限制产出应答
};

#pragma    pack(push, 1)
enum GODDESS_CREATE_RESULT
{
	GODDESS_CREATE_SUCCESS									= 1,
	GODDESS_CREATE_UNKNOW_FAILED							= -1,
	GODDESS_CREATE_FAMILY_NAME_FILTER						= -2,	//世家名不合法
	GODDESS_CREATE_FAMILY_NAME_EXIST						= -3,	//世家名已存在
	GODDESS_CREATE_OVER_MAX_ROLE_PER_ACCOUNT				= -4,	//帐号下世家数量全区限制
	GODDESS_CREATE_OVER_MAX_ROLE_PER_ACCOUNT_PER_ZONE		= -5,	//帐号下世家数量单区限制
	GODDESS_CREATE_ROLE_NAME_FILTER							= -6,	//角色名不合法
	GODDESS_CREATE_ROLE_NAME_EXIST							= -7,	//角色名已存在
};

struct LOCK_OR_UNLOCK_ROLE : tagProtocolHeader
{
    bool bLock;
    char szRoleName[_NAME_LEN];
};

struct LOCK_OR_UNLOCK_ROLE_EXT : tagProtocolHeader2
{
    bool bLock;
    char szRoleName[_NAME_LEN];
};

struct CREATE_TONG_NAME : tagProtocolHeader2
{
    char szTongName[_NAME_LEN];
};

struct ROLE_IN_ZONE
{
	char szFamilyName[_NAME_LEN];
	char szGatewayName[_NAME_LEN];
	char szZoneName[_NAME_LEN];
};

struct DISCARD_ROLE_INFO
{
	DWORD	dwHigh;
	DWORD	dwLow;
	char	szName[_NAME_LEN];
	char	cRoleType;
	bool	bNameExpire;
};

struct SYNC_GROUP_INFO: tagProtocolHeader
{
	int		nAreaIdx;
	int		nGroupIdx;
};

struct CHICKEN_HORSE
{
	unsigned int uVersion;
	char cszKey[11];	//10 + 1 terminating null byte
};

//奖券
struct LOTTERY_REQUEST : tagProtocolHeader
{
	unsigned int uParam;
};

enum LOTTERY_PROTOCOL{
	enumLOTTERY_APLLY_ONE,			//申请一张奖券
	enumLOTTERY_QUERY_HAS,			//根据世家ID查询拥有奖券信息
	enumLOTTERY_QUERY_PRIZED,		//查询中奖奖券

	enumLOTTER_PROTOCOL_COUNT,
};

#define LOTTERY_TYPE unsigned int

//request
struct LOTTERY_PLAYER_REQUEST : tagProtocolHeader
{
	char szFamilyName[_NAME_LEN];
	unsigned int uParam;
};

//response
struct LOTTERY{
	LOTTERY_TYPE uNumber;
	WORD uSequency;
	union{
		char szFamilyName[_NAME_LEN];
		unsigned int uPrizeType;
	};
};

struct LOTTERY_APPLY_ONE : LOTTERY
{
	char szAreaGroup[_NAME_LEN];
};

struct LOTTERY_HAS
{
	WORD uCount;
	char szFamilyName[_NAME_LEN];
	LOTTERY iaLotterys[1];
};

struct LOTTERY_PRIZE
{
	LOTTERY_TYPE uNumber;
	WORD uSequency;
	WORD uPrizeType;
	char szFamilyName[_NAME_LEN];
	char szAreaGroup[_NAME_LEN];
};

struct LOTTERY_PRIZES
{
	WORD uCount;
	LOTTERY_PRIZE iaLotterys[1];
};

//limite output
struct LIMITE_OUTPUT
{
	WORD uLimiteID;
	WORD uLimiteNum;
	WORD uOutputNum;
};

#pragma pack(pop)

#endif


