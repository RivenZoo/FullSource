#ifndef _GLOBALDEF_H_
#define _GLOBALDEF_H_

// 与具体工程无关的全局性的宏,结构定义:

// PROTOCOL_BIG_PACKAGE_BEGIN之前协议由网络库内部使用!
#define PROTOCOL_BIG_PACKAGE_BEGIN		10
// 从PROTOCOL_BIG_PACKAGE_BEGIN--PROTOCOL_NORMAL_PACKAGE_BEGIN之间为大包协议号!
#define PROTOCOL_NORMAL_PACKAGE_BEGIN	31



//字符串长度定义
#define _NAME_LEN               32
//身份证字符串长度
#define KG_STRING_SIZE_ID_CARD  19

#pragma	pack(1)
#pragma warning(disable: 4200)

#define PROTOCOL_MSG_TYPE unsigned char
#define PROTOCOL_MSG_SIZE (sizeof(PROTOCOL_MSG_TYPE))

#define INTRANER_IP					0
#define INTERNET_IP					1

typedef struct tagProtocolHeader
{
    union
    {
	    PROTOCOL_MSG_TYPE	cProtocol;
	    PROTOCOL_MSG_TYPE	ProtocolType;
	};
} ProtocolHeader, tagProtoHeader;

typedef struct tagProtocolHeader2 :  public tagProtocolHeader
{
	unsigned long ulIdentity;
} ProtocolHeader2;

struct tagLengthFirstProtoHeader
{
	unsigned short uLength;
	union
	{
		PROTOCOL_MSG_TYPE	cProtocol;
		PROTOCOL_MSG_TYPE	ProtocolType;
	};
};

struct tagSubProtoHeader
{
	PROTOCOL_MSG_TYPE	cSubProtocol;
};

struct PrtocolLengthHeader : tagProtoHeader
{
	unsigned short		Length;
};

struct tagBiProtoHeader : PrtocolLengthHeader
{
	PROTOCOL_MSG_TYPE	cSubProtocol;
};

struct tagBiProtoHeaderNoLen : tagProtoHeader
{
	PROTOCOL_MSG_TYPE	cSubProtocol;
};

struct TProcessData
{
	unsigned char	nProtoId;
	size_t			nDataLen;
	unsigned long	ulIdentity;
	bool			bLeave;
	char			pDataBuffer[1];//实际的数据
};

#define KSG_PASSWORD_MAX_SIZE 64

typedef struct tagKSG_PASSWORD
{
    char szPassword[KSG_PASSWORD_MAX_SIZE];    // 现在采用MD5的字符串，由于是32个字符，加上末尾'\0'，需要至少33个空间，因此使用64
} KSG_PASSWORD;

//扩展点
#define MAX_EXT_POINT_COUNT   8

struct tagExtPointInfo
{
	DWORD nExtPoint[MAX_EXT_POINT_COUNT];
};

enum Account_State_Type
{
    OFFLINE = 0x00000001,                   // 离线挂机
    ACTIVED_DYNAMIC_PASSWORD = 0x00000002,  // 激活了动态密码服务
};

struct tagGuidableInfo : public tagProtocolHeader2
{
	GUID            guid;
    tagExtPointInfo ExtPointInfo;       //可用的附送点
	tagExtPointInfo ChangePointInfo;	//变化的附送点
	DWORD			nTotalLeftTime;		//总的可游戏时间,以秒为单位(包括包月和计点)
	DWORD			nLeftTimeOfPoint;	//点数对应的剩余时间,以秒为单位，nTotalLeftTime-nLeftTimeOfPoint可以得到包月时间	
    DWORD           dwLeftMoney;
    unsigned long   uLimitPlayTimeFlag;  // 防沉迷标志位
    unsigned long   uLimitOnlineSecond;  // 防沉迷累计在线时间
    unsigned long   uLimitOfflineSecond; // 防沉迷累计离线时间
    int             nChargeFlag;
    unsigned int    uAccountState;       // 按位使用，每位的意义在枚举Account_State_Type中定义
    char            szPhoneNumber[20];
	size_t	        datalength;
	char	        szData[0];
};

#define	FAIL_REASON_NONE		                0
#define FAIL_REASON_VALID_PWD	                1
#define	FAIL_REASON_NOT_ALLOW	                2
#define	FAIL_REASON_UNKNOWN                     3
#define FAIL_REASON_NAME_FILTER                 4
#define FAIL_REASON_NAME_EXIST                  5
#define FAIL_REASON_OVER_MAX_ROLE_PER_GATEWAY   6
#define FAIL_REASON_OVER_MAX_ROLE_PER_ZONE      7
#define FAIL_REASON_ROLE_NAME_FILTER			8
#define FAIL_REASON_ROLE_NAME_EXIST				9


//删除与新建角色的返回消息带的数据
struct tagNewDelRoleResponse : tagProtocolHeader2
{
	char	szRoleName[_NAME_LEN];
    bool	bSucceeded;	
	BYTE	cFailReason;
};

struct tagQueryMapInfo : public tagProtocolHeader
{
	unsigned int		uTime;
};

struct tagUpdateMapID : public tagProtocolHeader
{	
	//  For example : Are your clear older information when it update local information.	 
	bool bRelay;	//如果是relay则，填1，如果是gameserver则填0
	int nMapCount;	//如果是relay则，填0
	int nServerIndex; //这台服务器是第几台
	int nMaxPlayer;
	char szServerName[32];
	int snMapID[0];	// C4200 warning
};
struct tagServerInfo
{
	unsigned char ucServerNum;
};

struct tagServerInfoElem
{
	char nServerIndex;
	char nPercent;
	WORD nSvrFuncType;
	DWORD dwFuncList;
	char szServerName[32];
};

typedef struct tagPING_COMMAND : public tagProtocolHeader
{
	DWORD dwTime;
} PING_COMMAND;

struct tagSvrConnectedInitReady : public tagProtocolHeader
{
	bool	bReady;
};

// 兑换类型
enum _Exchange_Type
{
    _COIN_EXCHANGE_SECOND  = 1,                             // 金币兑换计点
    _COIN_EXCHANGE_DATE    = 2                              // 金币兑换包时

};

// 转帐标志
enum _Transfer_Flag
{
    _TRANSFER_FREEZE_FEE    = 1,                            // 转帐冻结的金币
    _TRANSFER_UNFREEZE_FEE  = 2                             // 转帐未冻结的金币
};

// 转帐类型
enum _Transfer_Type
{
    _TRANSFER_SECOND   = 1,                                 // 计点
    _TRANSFER_COIN     = 2,                                 // 金币
    _TRANSFER_EXTPOINT = 3                                  // 扩展点
};

// 冻结，解冻计费标志
enum _Freeze_Fee_Flag
{
    _FREEZE   = 1,                                          // 锁定
    _UNFREEZE = 2                                           // 解锁
};

// 冻结，解冻计费类型
enum _Freeze_Fee_Type
{
    _FREEZE_SECOND   = 1,                                   // 计点
    _FREEZE_COIN     = 2,                                   // 金币
    _FREEZE_EXTPOINT = 3                                    // 扩展点
};

enum PasspodVersion
{
    PASSPODVERSION_UNBIND = 0, 
    PASSPODVERSION_ZP3    = 1 //中磐Passpod3.0
};

enum PasspodMode
{
    PASSPODMODE_UNBIND   = 0,
    PASSPODMODE_ZPTOKEN  = 1 //中磐令牌
};

#pragma pack()

#endif 
