#ifndef _BISHOP_CLIENT_PROTOCOL_H_
#define _BISHOP_CLIENT_PROTOCOL_H_

#include "../ProtocolBasic.h"

#define BISHOP_PROTOCOL_VERSION 3

enum B2C_PROTOCOL_ID    // Bishop ==> Client
{
    B2C_PROTOCOL_BEGIN = PROTOCOL_NORMAL_PACKAGE_BEGIN,
    B2C_ACCOUNT_VERIFY_RESULT,          // 玩家登陆，身份验证的结果, ref : KLoginAccountInfo
    B2C_RETURN_ROLE_LIST,               // 返回角色列表给客户段, ref : TProcessData + role list data 
    B2C_CREATE_OR_DELETE_ROLE_RESULT,   // 新建或者删除角色的结果, ref : tagNewDelRoleResponse
    B2C_NOTIFY_PLAYER_LOGIN_GAMESVR,    // 通知客户段登陆Game server, ref : tagNotifyPlayerLogin
	B2C_NOTIFY_GAME_VERSION_INFO,		// 将会在连接刚建立的时候发送,把游戏版本信息传到客户端, ref : tagNotifyGameVersion
    B2C_SYNC_HOMETOWN_LIST,             // 同步新手村列表
    B2C_CREATE_ROLE_RESPOND,            // 创建角色应答，剑三协议
    B2C_DELETE_ROLE_RESPOND,            // 删除角色应答，剑三协议
    B2C_RETURN_ROLE_LIST_IN_ZONE,       // 返回大区中的角色表 ref : TProcessData + ROLE_IN_ZONE
	B2C_NOTIFY_PASSPOD_VERIFY,			// 通知客户端验证密宝
	B2C_PASSPOD_VERIFY_RESULT,			// 密宝验证结果
};

enum C2B_PROTOCOL_ID    // Client ==> Bishop
{
    C2B_PROTOCOL_BEGIN = PROTOCOL_NORMAL_PACKAGE_BEGIN,
    C2B_PLAYER_LOGIN_INFO,      // 玩家登陆信息(帐号,密码), ref : KLoginAccountInfo
    C2B_CREATE_ROLE,            // 请求创建角色, ref : NEW_PLAYER_COMMAND, 各项目自定，非统一结构
    C2B_DELETE_ROLE,            // 请求删除角色, ref : tagDBDelPlayer
    C2B_GAME_LOGIN_REQUEST,     // 玩家选择一个角色，请求登陆游戏, ref : tagDBSelPlayer
    C2B_QUERY_HOMETOWN_LIST,    // 请求新手村列表
	C2B_SEL_SUB_SERVER,			// 选择一个子服务器，ref : tagDBSelSubServer
    C2B_PLAYER_LOGIN_INFO_SD,   // 盛大玩家登陆信息, ref : KLoginAccountInfoSD
    C2B_PLAYER_LOGIN_INFO_AND_LOGIN_KEY,// 使用排队登陆的协议
	C2B_PASSPOD_VERIFY,			// 密宝信息
	C2B_PLAYER_LOGIN_INFO_YY,   // yy玩家登陆信息, 其实是通用的认证协议了
};

#pragma	pack(push, 1)

#define	LOGIN_ACCOUNT_MIN_LEN	6
#define LOGIN_ACCOUNT_MAX_LEN	16
#define LOGIN_PASSWORD_MIN_LEN	8
#define LOGIN_PASSWORD_MAX_LEN	16
#define LOGIN_ROLE_NAME_MIN_LEN	6
#define	LOGIN_ROLE_NAME_MAX_LEN	16

//login action return value
//the folloin' value is used in login connect operaion
#define	LOGIN_ACTION_FILTER					0xff0000	//登陆过程中的操作类型过滤数值
#define LOGIN_A_CONNECT						0x010000	//连接
#define	LOGIN_A_NEWACCOUNT					0x020000	//新建账号（账号服务器）
#define	LOGIN_A_SERVERLIST					0x030000	//获取服务器列表（账号服务器）
#define	LOGIN_A_REPORT						0x040000	//通知服务器在线(定期向服务器发送)
#define	LOGIN_A_LOGIN						0x050000	//登陆服务器（账号、游戏服务器）
#define	LOGIN_A_LOGOUT						0x060000	//注销
#define	LOGIN_A_CHARACTERLIST				0x070000	//获取角色列表（游戏服务器）


#define	LOGIN_R_REQUEST						0	//when the login request is send form client to server
#define	LOGIN_R_SUCCESS						1
#define	LOGIN_R_FAILED						2
#define	LOGIN_R_ACCOUNT_OR_PASSWORD_ERROR	3
#define	LOGIN_R_ACCOUNT_EXIST				4
#define	LOGIN_R_TIMEOUT						5
#define	LOGIN_R_IN_PROGRESS					6
#define	LOGIN_R_NO_IN_PROGRESS				7
#define	LOGIN_R_VALID						8    //合法
#define	LOGIN_R_INVALID						9    //非法
// Add by Freeway Chen in 2003.7.1
#define LOGIN_R_INVALID_PROTOCOLVERSION     10  // 协议版本不兼容，详见 KProtocolDef.h's KPROTOCOL_VERSION
#define LOGIN_R_FREEZE						11	// 被冻结
#define LOGIN_R_SMS_LOCK					12	// 账号被短信冻结
#define LOGIN_R_NOT_ACTIVE					13	// 账号未激活
#define LOGIN_R_KICKOUT_OLDACC				14	// 账号踢出中
#define LOGIN_R_ACC_IN_GATEWAY				15	// 账号断在网关中
#define LOGIN_R_INVALID_PROTO				16	// 因为使用了非官方客户端，账号被暂时冻结，请稍后再登录
// 北京Paysys加入激活码的功能:
#define LOGIN_R_CDKEY                       17  // 输入激活码错误 
#define LOGIN_R_ACTIVE                      18  // 账号未被激活,需要激活码
#define LOGIN_R_BLACK_LIST                  19  // 密码连续输错几次，帐号被Paysys锁定到黑名单了
// 2005-10-04 : 增加"系统维护"的返回代码
#define LOGIN_R_SYSTEM_MAINTENANCE          20  // 系统维护中
// 2005-10-13: 验证用过,但是账号正在游戏中(剑三会自动踢号)
#define LOGIN_R_SUCCESS_AND_IN_GAME         21   
// 该账号是新手卡账号(比如随<大众软件>附送的那种),但是没有激活,请到"xxx"网页去激活 ...
#define LOGIN_R_ACCOUNT_CARD_UNACTIVE       22
// 该帐号登录时必须修改密码
#define LOGIN_R_CHANGE_PASSWORD             23
// 输入的激活码不存在
#define LOGIN_R_ACTIVE_CODE_NOT_EXIST       24
// 输入的激活码已经使用过了
#define LOGIN_R_ACTIVE_CODE_ALREADY_USED    25
// 该帐号为防沉迷对象，不允许登录
#define LOGIN_R_LIMIT_ACCOUNT               26

#define LOGIN_R_PASSPOD_SYSTEM              27 // PASSPOD系统错误
#define LOGIN_R_PASSPOD_TOKEN_USED          28 // 令牌已使用
#define LOGIN_R_PASSPOD_TOKEN_FAILED        29 // 验证失败
#define LOGIN_R_PASSPOD_TOKEN_EXPIRED       30 // 令牌过期
#define LOGIN_R_PASSPOD_TOKEN_NOTFOUND      31 // 令牌绑定未找到
#define LOGIN_R_PASSPOD_TOKEN_DISABLE       32 // 令牌已经禁用（挂失）

#define LOGIN_R_LOGIN_KEY_INVALID           33  // 排队拿到的KEY已经失效
#define LOGIN_R_MUTI_ACCOUNT_ONLINE			34  // 同一身份证的多个账号同时登陆
#define LOGIN_R_USER_INFO_MISSED			35  // 实名制信息不全（身份证和联系方式缺一不可）

#define LOGIN_R_PASSPOD_MATRIX_FAILED		36 // 矩阵卡验证失败
#define LOGIN_R_PASSPOD_MATRIX_CARDINVALID	37 // 矩阵卡无效
#define LOGIN_R_PASSPOD_MATRIX_NOTFOUND		38 // 矩阵卡未找到


// 字符串长度
//#define _KG_STRING_SIZE_ID_CARD             22  // 身份证长度
#define _KG_STRING_SIZE_SD_TOKEN            384 // 盛大Token长度
#define _KG_STRING_SIZE_YY_TOKEN            600 // yy Token长度
#define _KG_STRING_SIZE_DEFAULE_RESERVED    16  // 默认保留长度

#define KG_PASSPOD_NONE						0
#define KG_PASSPOD_EKEY						1	//令牌
#define KG_PASSPOD_ECARD					2	//密保卡
#define KG_PASSPOD_ECARD_SEED_NUM			3

enum KLOGIN_EX_FLAG
{
	enumEX_JUST_LOGIN		= 0x1,
};

struct KLoginStructHead
{
	unsigned short	Size;		//size of the struct, if the struct is been inherit, the size is ref the the derive struct
	int				Param;		//be one of the LOGIN_R_* define value combin with a LOGIN_A_* value.
};

// 玩家登陆(上传帐号,密码)以及验证结果都是用这个结构,注: 剑三不用这个!
struct KLoginAccountInfo : KLoginStructHead 
{
	char	        Account[_NAME_LEN];	//account
	KSG_PASSWORD    Password;
	unsigned long   nLeftTime;     //剩余时间    
    int             nGameServerProtocolVersion;	
    int             nBishopProtocolVersion;
	union
	{
		unsigned long   nLeftTimeOfPoint;   // 剩余时间中，点数对应的时间
		BOOL			bKickOutOldAcc;
	};
    char          szActivateCode[_NAME_LEN]; // 激活码，不用的时候置0
    unsigned char byMachineID[16];               // 机器ID

    unsigned long ulLastLoginTime;           // 上次登陆时间,注意,只有在玩家登陆验证通过的情况下,该值才有效,否则是0.
    unsigned long ulLastLoginIP;             // 上次登陆IP,注意,只有在玩家登陆验证通过的情况下,该值才有效,否则是0.
    unsigned long uLimitPlayTimeFlag;        // 防沉迷标志位
    unsigned long uLimitOnlineSecond;        // 防沉迷累计在线时间
    unsigned long uLimitOfflineSecond;       // 防沉迷累计离线时间
    unsigned      uGatewayID;

    BYTE          byPasspodVersion;          // 密保版本
    BYTE          byPasspodMode;             // 密保认证方式
    char          szTokenPassword[10];       // 令牌密码

	DWORD		  dwExFlag;					 // 扩展标记位
};

// 玩家排队登陆
struct KLoginAccountInfoAndLoginKey : public KLoginAccountInfo
{
    unsigned uLoginQueuePlayerID;
    GUID LoginKey;
};

// 盛大玩家登陆(上传帐号,密码)以及验证结果都是用这个结构
struct  KLoginAccountInfoSD : public KLoginAccountInfo 
{
    char         szIDCard[KG_STRING_SIZE_ID_CARD];
    int          nIsIDCardValid;
    char         szToken[_KG_STRING_SIZE_SD_TOKEN];
    char         szReserved[_KG_STRING_SIZE_DEFAULE_RESERVED];
};

// YY登录协议，使用明文帐号+公钥加密的密码
struct  KLoginAccountInfoYy : public KLoginAccountInfoAndLoginKey 
{
	char         szToken[_KG_STRING_SIZE_YY_TOKEN];
};

struct tagKB2C_PASSPOD_VERIFY : tagProtocolHeader
{
	BYTE byPasspodVersion;    // 密宝版本
	BYTE byPasspodMode;       // 密宝认证方式
	char szMatrixPosition[9]; // 需要用户输入的矩阵密码的位置

	int nReturn;
};

typedef tagKB2C_PASSPOD_VERIFY KB2C_PASSPOD_VERIFY_RESULT, KB2C_PASSPOD_VERIFY_NOTIFY;

struct KC2B_PASSPOD_VERIFY : tagProtocolHeader
{
	union
	{
		char szTokenPassword[10]; // 令牌密码
		char szMatrixPassword[9]; // 对应矩阵位置的密码
	};
};

// Client ==> Bishop, 剑三协议, 玩家请求登陆网关(Bishop), 协议: C2B_PLAYER_LOGIN_INFO
struct  KC2B_PLAYER_LOGIN_GATEWAY_REQUEST : public tagProtocolHeader 
{
    char         szAccountName[_NAME_LEN];
    KSG_PASSWORD Password;
    char         szActivateCode[_NAME_LEN]; // 激活码,没用时清零
    int          nGameWorldProtocolVersion;	
    int          nGatewayProtocolVersion;
};

// Bishop ==> Client, 剑三协议, 玩家请求登陆网关(Bishop)的结果, 协议: B2C_ACCOUNT_VERIFY_RESULT
struct  KB2C_PLAYER_LOGIN_GATEWAY_RESPOND : public tagProtocolHeader 
{
    int           nRespondCode;
    unsigned long ulEndOfDayTime;
    unsigned long ulLeftTimeOfPoint;  
    unsigned long ulLastLoginTime;      // 上次登陆时间,注意,只有在玩家登陆验证通过的情况下,该值才有效,否则是0.
    unsigned long ulLastLoginIP;        // 上次登陆IP,注意,只有在玩家登陆验证通过的情况下,该值才有效,否则是0.
    unsigned long ulLimitPlayTimeFlag;   // 防沉迷标志位
    unsigned long ulLimitOnlineSecond;   // 防沉迷累计在线时间
    unsigned long ulLimitOfflineSecond;  // 防沉迷累计离线时间
    int           nGatewayProtocolVersion;
    int           nGameWorldLowerVersion;
    int           nGameWorldUpperVersion;
};

struct tagDBSelPlayer : public tagProtocolHeader2
{
	char	szRoleName[_NAME_LEN];
};

struct tagDBSelSubServer : public tagProtoHeader
{
	unsigned char ucServerIndex;
};

struct tagDBDelPlayer : public tagProtocolHeader
{
	char	        szAccountName[_NAME_LEN];
    KSG_PASSWORD    Password;
	char	        szRoleName[_NAME_LEN];
};


#define ROLE_LOGIN_RESULT_SUCCESS           1   // 允许登陆,ref: tagNotifyPlayerLogin
#define ROLE_LOGIN_RESULT_MAINTENANCE       2   // 角色所在的服务器正在维护中, ref: tagNotifyPlayerLogin
#define ROLE_LOGIN_RESULT_IS_FULL           3   // 角色所在服务器已满,ref: tagNotifyPlayerLogin
#define ROLE_LOGIN_RESULT_UNKNOWN           4   // 其他的未知错误，通常是在角色数据方面,比如数据错误，被锁住了，等等

struct tagNotifyPlayerLogin : public tagProtocolHeader
{
	char            szRoleName[_NAME_LEN];
    int             nResult; // 该值定义如上"ROLE_LOGIN_RESULT_ ... ..."
	GUID            guid;
	UINT			nIPAddr;
	unsigned short	wPort;
};

struct KC2B_GAME_LOGIN_REQUEST : tagProtocolHeader
{
    DWORD dwRoleID;
};

// 玩家请求登录游戏的响应,剑三协议
struct KB2C_ROLE_LOGIN_RESPOND :  tagProtocolHeader
{
    int             nRespondCode;
    DWORD           dwRoleID;
	GUID            guid;
	DWORD			dwIPAddr;
	WORD	        wPort;
};

struct tagNotifyGameVersion : public tagProtocolHeader
{
	int				nMinVersion;
	int				nCurrentVersion;
};

// 创建角色, 剑三协议
struct KC2B_CREATE_ROLE_REQUEST : public tagProtocolHeader
{
    size_t uDataLen;
    BYTE   byData[0];
};

// 删除角色, 剑三协议
struct KC2B_DELETE_ROLE_REQUEST : public tagProtocolHeader
{
    DWORD           dwRoleID;
    KSG_PASSWORD    Password;
};

// 查询手村别表,剑三协议
struct KC2B_QUERY_HOMETOWN_LIST : public tagProtocolHeader
{
    int nReserved;
};

// 同步手村描述数据,剑三协议
struct KB2C_SYNC_HOMETOWN_LIST : public tagProtocolHeader
{
    size_t uDataLen;
    BYTE   byData[0];
};

// 查询角色列表,剑三协议
struct KB2C_RETURN_ROLE_LIST : public tagProtocolHeader
{
    size_t uDataLen;
    BYTE   byData[0];
};

// 返回创建角色应答信息,剑三协议
struct KB2C_CREATE_ROLE_RESPOND : public tagProtocolHeader
{
    bool    bSucceeded;
    size_t  uDataLen;
    BYTE    byData[0];
};

// 返回删除角色应答信息,剑三协议
struct KB2C_DELETE_ROLE_RESPOND : public tagProtocolHeader
{
    DWORD   dwRoleID;
    bool    bSucceeded;
    BYTE	cFailReason;
};

struct KC2B_QUERY_ROLE_LIST_IN_ZONE : public tagProtocolHeader
{
    int nReserved;
};

#pragma pack(pop)

#endif
