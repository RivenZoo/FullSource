//---------------------------------------------------------------------------
// 剑侠情缘网络版2 GameMasterCentral 互联互通
// 版权所有:       2006-2007 金山软件(Kingsoft)
// 创建日期与作者: 2006 越子(wooy)
//---------------------------------------------------------------------------
// GameMasterCentral与游戏世界的各种Master服务之间的协议接口
//---------------------------------------------------------------------------
#ifndef __GAME_MASTER_CENTRAL_GAMEMASTER_PROTOCOL_H__
#define __GAME_MASTER_CENTRAL_GAMEMASTER_PROTOCOL_H__
#include "ProtocolBasic.h"
#include "GameMasterServiceDef.h"

#pragma	pack(push, 1)

enum GAME_MASTER_PROTOCOL_LIST
{
	GM_P_NORMAL	= PROTOCOL_NORMAL_PACKAGE_BEGIN,
	GM_P_OPERATION_REQUEST,					//操作请求，数据包格式见GAME_MASTER_PROTOCOL_HEADER
	GM_P_OPERATION_REQUEST_ON_ACCOUNT,		//带被操作帐号名称信息的操作请求，数据包格式见GAME_MASTER_PROTOCOL_WITH_OBJNAME
	GM_P_OPERATION_REQUEST_ON_ROLE,			//带被操作角色名称信息的操作请求，数据包格式见GAME_MASTER_PROTOCOL_WITH_OBJNAME
	GM_P_OPERATION_REQUEST_ON_OBJECT,		//带被操作对象名称信息的操作请求，数据包格式见GAME_MASTER_PROTOCOL_WITH_OBJNAME
	GM_P_OPERATION_RESPONSE,				//请求处理结果
};

//跟随GM_P_NORMAL协议的子协议
enum GAME_MASTER_NORMAL_SUB_PROTOCOL
{
	GMN_P_SERVICE_LOGIN = 1,		//游戏世界的服务程序连上GMC后,首先发此登陆消息
	GMN_P_SERVICE_PING,
	GMN_P_SERVICE_INFO,				//GMC在收到GMN_P_SERVICE_LOGIN消息后，回复服务程序信息给对方，让对方知道自己身份
};

struct GAME_MASTER_SERVICE_PING : tagBiProtoHeaderNoLen
{
	unsigned int uTime;
};

//每个游戏世界的服务程序连上GMC后,首先发此登陆消息给它
struct GAME_MASTER_SERVICE_LOGIN : tagBiProtoHeaderNoLen
{
	int					nIdentifier;	//id 或者 识别号 用于以后可能支持单台GMS机器上同时启动多个相同的要连入GMC的程序
	unsigned int		uServiceType;	//接入GameMasterCentral的MasterService服务程序所提供的服务的类型,见MASTER_SERVICE_TYPE
	char				szOperatorAccount[32];
	char				szOperatorPasswd[64];
	char				Reserved[32];
};

//GMC在收到GMN_P_SERVICE_LOGIN消息后，回复服务程序信息给对方，让对方知道自己身份
struct GAME_MASTER_SERVICE_INFO : tagBiProtoHeaderNoLen
{
	int					nAreaIndex;			//服务器组的1级编号
	int					nGroupIndex;		//服务器组的2级编号
	unsigned int		uServerId;		//服务器组的唯一数字型ID
	char				szServerName[32];	//服务器组的唯一字符串型ID
	char				szZoneName[32];		//所在的区的名称
	char				Reserved[12];
};

//带流水号的协议包头
struct GAME_MASTER_PROTOCOL_HEADER : PrtocolLengthHeader
{
	GAME_MASTER_PROTOCOL_INFO	ProtInfo;
};

//操作帐号的协议包头
struct GAME_MASTER_PROTOCOL_WITH_OBJNAME : GAME_MASTER_PROTOCOL_HEADER
{
	NAMED_OBJECT_IDENTIFIER	Obj;
};

//带流水号和数据块的协议包
struct GAME_MASTER_PROTOCOL_WITH_DATA : GAME_MASTER_PROTOCOL_HEADER
{
	DATA_CONTENT	Data;
};
#define GAME_MASTER_PROTOCOL_WITH_DATA_SIZE(n)		\
	((n > 0) ? (sizeof(GAME_MASTER_PROTOCOL_WITH_DATA) + n - 1) : sizeof(GAME_MASTER_PROTOCOL_HEADER))

//操作帐号和数据块的协议包
struct GAME_MASTER_PROTOCOL_WITH_OBJNAME_AND_DATA : GAME_MASTER_PROTOCOL_WITH_OBJNAME
{
	DATA_CONTENT	Data;
};
#define GAME_MASTER_PROTOCOL_WITH_OBJNAME_AND_DATA_SIZE(n)	\
	((n > 0) ? (sizeof(GAME_MASTER_PROTOCOL_WITH_OBJNAME_AND_DATA) + n - 1) : sizeof(GAME_MASTER_PROTOCOL_WITH_OBJNAME))

//带流水号和区服信息的协议包的包头
struct OPERATION_PROTOCOL_WITH_SVR_IDX_HEADER : GAME_MASTER_PROTOCOL_HEADER
{
	GAME_MASTER_SERVICE_SVR		ServiceSvr;
};

#pragma	pack(pop)

#endif// #ifndef __GAME_MASTER_CENTRAL_GAMEMASTER_PROTOCOL_H__
