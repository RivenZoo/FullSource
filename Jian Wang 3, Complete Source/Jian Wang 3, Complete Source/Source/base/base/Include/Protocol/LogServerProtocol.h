//---------------------------------------------------------------------------
// 剑侠情缘网络版2 GameMasterCentral 互联互通
// 版权所有:       2006-2007 金山软件(Kingsoft)
// 创建日期与作者: 2006 越子(wooy)
//---------------------------------------------------------------------------
// GameMasterCentral与游戏世界的各种Master服务之间的协议接口
//---------------------------------------------------------------------------
#ifndef __LOG_SERVER_PROTOCOL_H__
#define __LOG_SERVER_PROTOCOL_H__

#pragma	pack(push, 1)

enum LOG_SERVER_PROTOCOL_LIST
{
	LOG_SERVER_P_LOGIN	= 32,			//客户端登录消息包
	LOG_SERVER_P_LOGIN_RESP,			//登录消息的回馈包
	LOG_SERVER_P_PING,					// 由客户端主动发ping包，服务端LogSvr原封不动回ping。
	LOG_SERVER_P_QUERY_LOG,
	LOG_SERVER_P_ADD_LOG_COMMON,		// 在(通用)公共日志中增加记录
	LOG_SERVER_P_ADD_LOG_COMMON_RESULT,	// LogServer回给客户端的添加记录结果
	LOG_SERVER_P_ADD_LOG_ITEM,			// 在物品日志中增加记录
};

#define LOG_SERVER_PING_INTERVAL	30	//客户端发出ping包的频率，单位：秒
#define LOG_SERVER_DISCONNCT_TIME	100	//服务端LogSvr在如此长时间未收到网络包后将断开连接，单位：秒

struct LOG_SERVER_S_LOGIN
{
	unsigned char	cProtocol;				// = LOG_SERVER_P_LOGIN
	bool			bFailIfDbNotExist;		//如果数据库不存在是否直接登录失败，而不询问是否创建
	char			szGameSpaceName[32];	//目标游戏世界的名称（哪组服务器？group）
	char			szDatabaseName[32];		//数据库的库名
	char			szDbAccount[32];		//访问数据库的帐号
	char			szDbPassword[64];		//访问数据库的密码
	char			Reserved[8];
};

enum LOG_SERVER_E_LOGIN_RESULT
{
	LOG_SERVER_E_LR_OK = 1,			//登录成功
	LOG_SERVER_E_LR_DB_ACC_ERR,		//登录失败（所使用的数据库帐号密码有误）
	LOG_SERVER_E_LR_DB_NOT_EXIST,	//指定的数据库不存在
	LOG_SERVER_E_LR_FAIL,			//登录失败（其它原因）
};

struct LOG_SERVER_S_LOGIN_RESP
{
	unsigned char	cProtocol;			// = LOG_SERVER_P_LOGIN_RESP
	unsigned char	cResult;
};

//LogServer收到Ping消息包后会原样返回
struct LOG_SERVER_S_PING
{
	unsigned char	cProtocol;	// = LOG_SERVER_P_PING
	unsigned int	uTime;		// = 时间戳
};

struct LOG_SERVER_S_QUERY_LOG
{
	unsigned char	cProtocol;		// = LOG_SERVER_P_QUERY_LOG
	unsigned int	uSerialNo[2];	// 信息包的流水号
	char			szLogSort[32];	// 日志分类
	char			szLogObject[64];// 日志相关的目标对象名
	unsigned int	uParamLen;		// 后面的szParam的长度(不含结尾符'\0')
	char			szParam[1];
	
};

//传入的参数不含结尾符号'\0'的长度
#define LOG_SERVER_S_QUERY_LOG_SIZE(n)			(sizeof(LOG_SERVER_S_QUERY_LOG) + (n) - 1)
#define LOG_SERVER_S_QUERY_LOG_CHECK_SIZE(p,s)	((s) == LOG_SERVER_S_QUERY_LOG_SIZE((p)->uParamLen))

//LOG_SERVER_P_ADD_LOG_COMMON
struct LOG_SERER_S_ADD_LOG_COMMON
{
	unsigned char	cProtocol;		// = LOG_SERVER_P_ADD_LOG_COMMON
	unsigned char	bReturnId;		// 返回新插入日志的id值
	unsigned int	uLogType;		// 日志类型
	unsigned int	uLogFlag;		// 日志标记
	unsigned int	uSerialNo[2];	// 信息包的流水号
	unsigned short	usObjNameLen;	// 对象名称长度(不含结尾符'\0')
	unsigned short	usInfoLen;		// 日志信息长度(对于文本信息，不加'\0'结尾)
	char			ObjNameAndInfo[1];//对象名称与日志信息内容，其总长度为usObjNameLen+usInfoLen(不加'\0'结尾)
};
#define LOG_SERER_S_ADD_LOG_COMMON_SIZE(onl, il)	(sizeof(LOG_SERER_S_ADD_LOG_COMMON) + (onl) + (il) - 1)
#define LOG_SERER_S_ADD_LOG_COMMON_CHECK_SIZE(p,s)	((s) == LOG_SERER_S_ADD_LOG_COMMON_SIZE((p)->usObjNameLen, (p)->usInfoLen))

struct LOG_SERER_S_ADD_LOG_COMMON_RESULT
{
	unsigned char	cProtocol;		// = LOG_SERVER_P_ADD_LOG_COMMON
	unsigned int	uSerialNo[2];	// 请求信息包的流水号
	unsigned int	uLogId;			// 操作结果：新插入日志的id值，如果为0值表示失败
};

#pragma	pack(pop)

#endif// #ifndef __LOG_SERVER_PROTOCOL_H__
