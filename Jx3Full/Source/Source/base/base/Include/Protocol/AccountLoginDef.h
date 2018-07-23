// -------------------------------------------------------------------------
//    文件名        ：    AccountLoginDef.h
//    创建者        ：    万里
//    创建时间    ：    2003-5-2 22:04:24
//    功能描述    ：
//
// -------------------------------------------------------------------------
#ifndef __ACCOUNTLOGINDEF_H__
#define __ACCOUNTLOGINDEF_H__

#ifdef WIN32
#include <WTypes.h>
#endif

#include "../ProtocolBasic.h"

#define KSG_LOGIN3

// 主要用来将用户的端口传递给PaySys
#define KSG_USER_PORT
//#undef KSG_USER_PORT

#pragma    pack(push, 1)


#define LOGIN_USER_ACCOUNT_MIN_LEN        4
#define LOGIN_USER_ACCOUNT_MAX_LEN       32
#define LOGIN_USER_PASSWORD_MIN_LEN       6
#define LOGIN_USER_PASSWORD_MAX_LEN      64
#define LOGIN_USER_BIRTHDAY_MAX_LEN       9

//login action return value
#define ACTION_SUCCESS                  0x1
#define ACTION_FAILED                   0x2
#define E_ACCOUNT_OR_PASSWORD           0x3
#define E_ACCOUNT_EXIST                 0x4
#define E_ACCOUNT_NODEPOSIT             0x5 //点卡余额为零、或无点卡
#define E_ACCOUNT_ACCESSDENIED          0x6
#define E_ADDRESS_OR_PORT               0x7
#define E_ACCOUNT_FREEZE                0x8
#define E_ACCOUNT_CHANGE_EXT_POINT      0x9
#define E_ACCOUNT_USE_SILVER            0xA
///0x0B 这个数值在客户端被定义为其他含义
#define E_ACCOUNT_SMS_LOCK              0xC //账号被用户短信锁定
#define E_ACCOUNT_NOT_ACTIVE            0xD //账号未激活
#define E_ACCOUNT_KICKOUT_OLDACC        0xE
#define E_ACCOUNT_IN_GATEWAY            0xF
#define E_SYSTEM_BUSY                   0x10 //系统忙
#define E_BLACK_LIST                    21  // 帐号被Paysys锁定到黑名单里面了!

#define E_CONNECT_PAYSYS_ACCOUNT        50 // Gateway连Paysys时用户名错
#define E_CONNECT_PAYSYS_PASSWORD       51 // Gateway连Paysys时密码错
#define E_CONNECT_PAYSYS_IP             52 // Gateway连Paysys时IP错
#define E_CONNECT_PAYSYS_MAC            53 // Gateway连Paysys时MAC错

#define E_ACTIVE_CODE_NOT_EXIST         68 // 激活码不存在
#define E_ACTIVE_CODE_ALREADY_USED      69 // 激活码已经使用过了
// 以下两个错误码是用于激活码的功能实现:
#define E_CDKEY                         70  // 输入激活码错误
#define E_ACTIVE                        71  // 账号未被激活,需要激活码

// 以下四个错误码是用于新手推广CDKey的使用的!
// 注: 重用了三个返回码,返回1表示成功,2表示数据库错误,3表示输入的cdkey不存在(就是说输错了)
#define E_ISCDKEY                       74  // 玩家已经使用过cdkey了,一个帐号只能使用一次推广员cdkey
#define E_NEWTIMEOUT                    75  // 该帐号使用已超10小时,不能再使用推广员cdkey
#define E_NEWACTIVED                    76  // 该帐号不能使用推广员cdkey,可能是该玩家帐号属于"推广员新手卡帐号"
#define E_NOAPPLY                       77  // 输入的cdkey已经被用了,或者是该cdkey还没有生效(未被推广员领取)

// 有一种所谓的新手卡账号,比如随<大众软件>附送的那种新手卡账号,在使用时要先激活
// 如果验证时发现还没有激活,就返回这个错误码,玩家需要到指定的网页上去激活
#define E_ACCOUNT_CARD_UNACTIVE         80

// 以下错误码是用于收费后玩家第一次进入游戏提示到网站修改密码
#define E_CHANGE_PASSWORD               86

// 以下错误码是用于Paysys 2.0，属于新加的出错值
#define E_FEE_TYPE_ID_NOT_EXIST                     1000
#define E_ACCOUNT_CHARGE_NOT_FOUND_OR_OVERDUE       1001
#define E_CHARGE_PARAM_ERROR                        1002
#define E_CHARGE_SILVER_DENOMINATOR_ERROR           1003
#define E_CHARGE_SILVER_SILVER_TYPE_ERROR           1004
#define E_GATEWAY_STATE_NOT_FOUND                   1005
#define E_GATEWAY_STATE_NOT_SET_WORK_CONNECTION_ID  1006
#define E_GATEWAY_STATE_NEW_CONNECTION_ID           1007
#define E_GATEWAY_STATE_PARAM_ERROR                 1008
#define E_PARAM_ERROR                               1009
#define E_ZONE_ID_NOT_EXIST                         1010
#define E_ZONE_NAME_NOT_EXIST                       1011
#define E_GATEWAY_NAME_NOT_EXIST                    1012
#define E_NOT_A_FREE_GATEWAY                        1013
#define E_ZONE_STATE_NOT_MATCH                      1014
#define E_ZONE_ACCOUNT_ID_NOT_EXIST                 1015 //在分区表中不存在
#define E_ZONE_NOT_CHARGED                          1016 //该网关所属的分区没有收费

// Added by zhaofine, for IB only
#define E_IB_NO_ENOUGH_COIN                         1100 // 在购买物品时，金币余额不足。
#define E_IB_ITEM_NOT_EXIST                         1101 // 物品不存在
#define E_IB_ITEM_HAS_BEEN_USED                     1102 // 物品存在，但是已被消耗
#define E_IB_ITEM_EXPIRED                           1103 // 物品存在，但是已失效
#define S_IB_ITEM_NOT_IN_SAME_GATEWAY               1200 // 物品存在，购买与消耗的网关不一致。

#define E_LIMIT_ACCOUNT                             1400 // 该帐号为防沉迷对象，不允许登录
#define E_PASSPOD_VERIFY_TIME                       1701 // 还未到解锁时间就验证

//以下错误代码用于盛大 by 申屠元
#define E_ID_CARD_NOT_EXIST                         1900

#define E_LIMIT_MUTI_ACCOUNT_ONLINE                 1401 // 不允许同一防沉迷身份证下多个账号在线
#define E_REAL_NAME_PARAM_ERROR                     4024 // 玩家实名信息错误

//以下错误码是给毒霸用的
#define E_OVER_MAX_BIND_TIMES                       3001 //超过最大绑定数
#define E_OVER_MAX_TRANSFER_TIMES                   3002 //超过最大漫游数
#define E_HAS_APPLIED_TRIAL_ACCOUNT                 3003 //已经试用过了

//以下错误代码用于密宝
#define S_PASSPOD_SUCCESS                           5000 //验证成功
#define E_PASSPOD_SYSTEM                            5001 //PASSPOD系统错误
#define E_PASSPOD_TOKEN_USED                        5002 //令牌已使用
#define E_PASSPOD_TOKEN_FAILED                      5003 //令牌验证失败
#define E_PASSPOD_TOKEN_EXPIRED                     5004 //令牌过期
#define E_PASSPOD_TOKEN_NOTFOUND                    5005 //令牌绑定未找到
#define E_PASSPOD_TOKEN_DISABLE                     5006 //令牌已经禁用（挂失）
#define E_PASSPOD_MATRIX_FAILED                     5007 //矩阵卡验证失败
#define E_PASSPOD_MATRIX_CARDINVALID                5008 //矩阵卡无效
#define E_PASSPOD_MATRIX_NOTFOUND                   5009 //矩阵卡未找到

#define ACCOUNT_CURRENT_VERSION                     10

typedef enum
{
    AccountUser = 1,                  // 用户进入游戏调用的协议，一般使用KAccountUser结构，返回用    AccountUserReturn
    AccountUserLoginInfo,             // 普通用户登陆使用的协议，一般使用KAccountUserLoginInfo结构，返回用    AccountUserReturnEx
    ServerAccountUserLoginInfo,       // 服务端用户的登陆使用的协议，一般是网关，Relay等用户登陆使用    KServerAccountUserLoginInfo结构，需要验证IP和网卡的MAC地址，使用AccountUserReturn协议返回，结构使用    KAccountUserReturnVerify
    AccountUserReturn,                // 用户登陆返回，一般使用KAccountUserReturn结构
    AccountUserTimeInfo,              // RelayServer使用
    ServerOptionInfo,                 // RelayServer使用
    ServerInfo,                       // RelayServer使用
    AccountUserVerify,                // 用户修改密码使用，一般使用KAccountUserLoginInfo结构
    AccountUserReturnEx,              // 返回用户的登陆结果，包括附加点，一般使用KAccountUserReturnExt结构
    AccountUserLogout,                // 玩家退出游戏协议，一般使用KAccountUserLogout结构，返回使用    AccountUserReturn
    AccountChangeExtPoint,            // 玩家修改附加点，或者使用银票（转为时间），一般使用    KAccountUserChangeExtPoint结构，使用AccountUserReturn,但是返回结构使用KAccountUserReturnExt2
    AccountUserGetIp,                 // RelayServer使用
    AccountSpreaderCDKEY = 22,        // 传递新手推广CDKEY给PaySys
    AccountSpreaderCDKEYRet = 23,     // 返回新手推广CDKEY使用结果


    AccountIB_ItemBuy = 30,           // 传递购物申请给PaySys
    AccountIB_ItemBuyRet,             // 返回传递购物结果
    AccountIB_ItemUse,                // 传递物品使用申请给PaySys
    AccountIB_ItemUseRet,             // 返回物品使用结果
    AccountIB_UserLoginInfo = 34,     // 专用于IB模式的登入子协议，该子协议将增加一个字段来表示金币余额。
    
    AccountUserSetChargeFlag = 35,    //修改用户Charge_Flag
	AccountUserSetChargeFlagRet,

    AccountUserTransfer    = 37,      //转帐
    AccountUserTransferRet = 38,        

    ChangeAccountState  = 40,         // 更改帐号状态，KChangeAccountState
    ChangeAccountStateRetrun,         // 更改帐号状态返回，KChangeAccountStateRet

    AccountUserExchange     = 42,     // 玩家兑换
    AccountUserExchargeRet  = 43,  

    AccountUserQueryTransfer    = 44, // 转帐查询
    AccountUserQueryTransferRet = 45,

    AccountUserFreezeFee    = 46,     // 玩家冻结费用
    AccountUserFreezeFeeRet = 47,

    AccountIB_MultiItemBuy = 50,      // 传递购物申请给PaySys
    AccountIB_MultiItemBuyRet = 51,   // 返回传递购物结果
    AccountIB_MultiItemUse = 52,      // 传递物品使用申请给PaySys
    AccountIB_MultiItemUseRet = 53,   // 返回物品使用结果
    
    AccountUserInfo         = 54,     // 获取帐号信息
    AccountUserInfoRet      = 55,     // 获取帐号信息返回
    
    AccountUserPasspodVerify    = 56, //密宝认证
    AccountUserPasspodVerifyRet = 57, //密宝认证返回

    
    AccountIB_ItemBuy_SD = 60,        // 传递购物申请给PaySys
    AccountIB_ItemBuyRet_SD = 61,     // 购买物品的返回结果
    AccountIB_MultiItemBuy_SD = 62,   // 传递购物申请给PaySys
    AccountIB_MultiItemBuyRet_SD = 63,// 购买物品的返回结果

    GetZoneChargeFlag = 65,           // 获取区计费标志
    GetZoneChargeFlagRet = 66,        // 获取区计费标志返回
    
    AccountUserExchangeEx = 67,       // 玩家寄售
    AccountUserExchangeExRet = 68,     // 玩家寄售返回结果

    AccountUserPasspodVerifyEx = 69,  // 玩家密保认证协议扩展
    AccountUserPasspodVerifyRetEx = 70,

    AccountUserInfoEx    = 71,
    AccountUserInfoRetEx = 72,        // 获取账号信息返回，扩展
	
} ACCOUNTHEADTYPE;

// 通用协议: 游戏世界到Paysys的请求子类型
enum G2P_COMMON_REQUEST_SubType
{
	enumTypeAccountActivePresentCode = 48,			//礼品卡
};
// 通用协议: 游戏世界到Paysys的请求子协议
enum G2P_COMMON_REQUEST_SubProtocol
{
	enumProtocolAccountActivePresentCode = 50,		//礼品卡
};

// 通用协议: Paysys到游戏世界的回应子类型
enum P2G_COMMON_REPLY_SubType
{
	enumTypeAccountActivePresentCodeRet = 49,		//礼品卡
};
// 通用协议: Paysys到游戏世界的回应子协议
enum P2G_COMMON_REPLY_SubProtocol
{
	enumProtocolAccountActivePresentCodeRet = 50,	//礼品卡
};

struct KAccountHead
{
    WORD  Size;        // size of the struct
    WORD  Version;     // ACCOUNT_CURRENT_VERSION
    WORD  Type;
    DWORD Operate;     // gateway used
};

struct KAccountUser : public KAccountHead
{
    char Account[LOGIN_USER_ACCOUNT_MAX_LEN];    //account
};

struct KAccountUserReturn : public KAccountUser
{
    int nReturn;
};

struct KAccountUserPassword : public KAccountUser
{
    char Password[LOGIN_USER_PASSWORD_MAX_LEN];    //password
};

struct KAccountUserLogout : public KAccountUser
{
    WORD nExtPoint; //将要扣除的附送点
};

typedef enum _PLAYER_SOURCE
{
    PLAYER_SOURCE_INVALID = 0,
    PLAYER_SOURCE_KS, // Kingsoft Player
    PLAYER_SOURCE_SD,  // SNDA Player
	PLAYER_SOURCE_YY,  // yy Player
} PLAYER_SOURCE;

struct KAccountUserLoginInfo : public KAccountUserPassword  // Bishop ==> Paysys, 玩家身份验证!
{
    DWORD UserIP;
    DWORD UserPort;
    BYTE  byMachineID[16];      // 相同的MachineID的连接被认为是同一台电脑多开
    BYTE  nLogout;              // 1表示login时要先logout，0表示正常登录
    char  szActivateCode[LOGIN_USER_ACCOUNT_MAX_LEN];
    
    BYTE  byPasspodVersion;     // 密宝版本
    BYTE  byPasspodMode;        // 密宝认证方式
    char  szTokenPassword[10];  // 令牌密码
    char  szMatrixPosition[9];  // 需要用户输入的矩阵密码的位置
    char  szMatrixPassword[9];  // 对应矩阵位置的密码

    BYTE  byReserve[33];
};

struct  KAccountUserLoginInfoSD : public KAccountUserPassword
{
    DWORD UserIP;
    DWORD UserPort;
    BYTE  byMachineID[16];      // 相同的MachineID的连接被认为是同一台电脑多开
    BYTE  nLogout;              // 1表示login时要先logout，0表示正常登录
    char  szActivateCode[LOGIN_USER_ACCOUNT_MAX_LEN];

    BYTE  byPasspodVersion;     // 密宝版本
    BYTE  byPasspodMode;        // 密宝认证方式
    char  szTokenPassword[10];  // 令牌密码
    char  szMatrixPosition[9];  // 需要用户输入的矩阵密码的位置
    char  szMatrixPassword[9];  // 对应矩阵位置的密码

    char  szIDCard[KG_STRING_SIZE_ID_CARD]; // 身份证

    BYTE  byReserve[14];
};

struct  KAccountUserLoginInfoSDExt : public KAccountUserPassword
{
	DWORD UserIP;
	DWORD UserPort;
	BYTE  byMachineID[16];      // 相同的MachineID的连接被认为是同一台电脑多开
	BYTE  nLogout;              // 1表示login时要先logout，0表示正常登录
	char  szActivateCode[LOGIN_USER_ACCOUNT_MAX_LEN];

	BYTE  byPasspodVersion;     // 密宝版本
	BYTE  byPasspodMode;        // 密宝认证方式
	char  szTokenPassword[10];  // 令牌密码
	char  szMatrixPosition[9];  // 需要用户输入的矩阵密码的位置
	char  szMatrixPassword[9];  // 对应矩阵位置的密码

	char  szIDCard[KG_STRING_SIZE_ID_CARD]; // 身份证

	BYTE  byReserve[128];
};

struct KServerAccountUserLoginInfo : public KAccountUserPassword // Bishop ==> Paysys, Bishop身份验证，适用剑网Paysys
{
    DWORD Address;
    BYTE  MacAddress[6];
    DWORD nLastTime;
    DWORD nPlayerCount;
};

struct KServerAccountUserLoginInfo2 : KAccountHead      // Bishop ==> Paysys, Bishop身份验证，适用北京Paysys
{
    char          szAccountName[LOGIN_USER_ACCOUNT_MAX_LEN];
    char          szPassWord[LOGIN_USER_PASSWORD_MAX_LEN];
    int           nReserved;
    unsigned      dwUserIP;
    unsigned char byMacAddress[6];
    unsigned      dwLastLiveTime;
};

struct KAccountUserFullInfo : public KAccountUserPassword
{
    DWORD UserIP;
    char  Password2[LOGIN_USER_PASSWORD_MAX_LEN]; //secpassword
};

struct KAccountUserIp : public KAccountUser
{
    DWORD UserIP;
};

struct KAccountUserReturnVerify : public KAccountUserReturn
{
    long dwVerifyTime;
};

typedef struct _USER_RET_PLAY_LIMIT_PLAY_TIME
{
    int          nLimit_Player_Flag;
    int          nLimitOnlineSecond;
    int          nLimitOfflineSecond;
} USER_RET_PLAY_LIMIT_PLAY_TIME;

#define ACCOUNT_MAX_EXT_POINT_COUNT 8
struct KAccountUserReturnExt : public KAccountUserReturn    // Paysys ==> Bishop, 玩家身份验证结果!
{
    union
    {
        struct
        {
            WORD nExtPoint;         //可用的附送点
            WORD nExtPoint1;        //可用的附送点1
            WORD nExtPoint2;        //可用的附送点2
            WORD nExtPoint3;        //可用的附送点3
            WORD nExtPoint4;        //可用的附送点4
            WORD nExtPoint5;        //可用的附送点5
            WORD nExtPoint6;        //可用的附送点6
            WORD nExtPoint7;        //可用的附送点7
        };
        WORD nExtPointArray[ACCOUNT_MAX_EXT_POINT_COUNT];
    };

    // 玩家剩余时间分为包时和点数两部分传下来
    DWORD dwEndOfDayTime;    // 玩家包时(包天,包月等)的截止时间, time_t, 单位秒
    DWORD nLeftTimeOfPoint;  // 剩余点数
    DWORD dwLastLoginTime;   // 玩家上次登陆的时间
    DWORD dwLastLoginIP;     // 玩家上次登陆的IP

    union
    {
        struct
        {
            DWORD dwLimitPlayTimeFlag;   // Reserve[0]..Reserve[3]
            DWORD dwLimitOnlineSecond;   // Reserve[4]..Reserve[7]
            DWORD dwLimitOfflineSecond;  // Reserve[8]..Reserve[11]
            int   nChargeFlag;           // byReserve[12] .. Reserve[15]
            unsigned int  uAccountState; // byReserve[16] .. Reserve[19] 
            char  szMobileNumber[20];    // byReserve[20] .. byReserve[39]
            DWORD dwGatewayID;           // byReserve[40] .. byReserve[43]
            BYTE  byPasspodVersion;      // byReserve[44] .. byReserve[44]密宝版本
            BYTE  byPasspodMode;         // byReserve[45] .. byReserve[45]密宝认证方式
            char  szMatrixPosition[9];   // byReserve[46] .. byReserve[54]需要用户输入的矩阵密码的位置
        };
        BYTE  byReserve[64];
    };
};

struct KAccountUserReturnExt2 : public KAccountUserReturn // Paysys ==> Bishop, 附加点操作的结果!
{
    unsigned uFlag;
    int      nPlayerDataIndex;  // 用来将返回协议到达GameServer时，表示取得玩家的数据
};

#define CHANGE_EXT_POINT_SILVER         0x1
struct KAccountUserChangeExtPoint : public KAccountUser // Bishop ==> Paysys, 请求操作附加点!
{
    union
    {
        unsigned uExtPointIndex;    // 将要改变的附加点的索引
        unsigned uSilverType;       // 银票的类型，高16位（0：表示大银票，1：表示小银票）
                                    //             低16位（0：转为点数，：转为包（周）月）
    };
    int          nChangeValue;      // 附加点被修改的值，可正可负，或者银票的数目
    int          nPlayerDataIndex;  // 用来将返回协议到达GameServer时，表示取得玩家的数据
    unsigned     uFlag;             // 如果是0表示附加点的变化，如果是CHANGE_EXT_POINT_SILVER : 表示银票的处理
};

struct KAccountUserTimeInfo : public KAccountUserReturn
{
    DWORD nTime;
};

typedef enum
{
    server_OnlinePlayerCount = 0x0001,
    server_RegisterCount = 0x0002,
    server_Login = 0x0004,
    server_Logout = 0x0008,
    server_PlayerWhere = 0x0010,
    server_LoginAlready = 0x0020,
    server_PlayerWhereID = 0x0040,
    server_GWRelayID = 0x0080,
} SERVERTYPE;

struct KServerInfo : public KAccountUser
{
    short nServerType;
    DWORD nValue;
};

/**
 * @description 未充值的新手账号到了20级（可设定）时，即使免费的10小时未使用完，
                也将被从游戏世界中踢除，同时向paysys发送协议将可使用时间设置为0
 * @protocol    c2s_tryout_timeout_req Bishop=>Paysys
 * @author        wangbin
 * @datetime    2004-12-28 14:46
 */
struct TRYOUT_TIMEOUT_ASK : KAccountHead
{
    UINT    nIdentity;                                // GameServer标识
    BYTE    nReason;                                  // 原因（保留）
    int     nPlayerIndex;                             // 玩家数组索引
    char    szAccount[LOGIN_USER_ACCOUNT_MAX_LEN];    // 账号名
};

/**
 * @description 未充值的新手账号到了20级（可设定）时，即使免费的10小时未使用完，
                也将被从游戏世界中踢除，同时向paysys发送协议将可使用时间设置为0
 * @protocol    s2c_tryout_timeout_res Paysys=>Bishop
 * @author        wangbin
 * @datetime    2004-12-28 14:47
 */
struct TRYOUT_TIMEOUT_ANS : KAccountHead
{
    UINT    nIdentity;                                // GameServer标识
    BYTE    nResult;                                  // 处理结果，1为成功，0为失败
    int     nPlayerIndex;                             // 玩家数组索引
    char    szAccount[LOGIN_USER_ACCOUNT_MAX_LEN];    // 账号名
};



#define KG_SPREAD_NEW_PLAYER_CDKEY_FLAG    2
#define KG_VIRTUAL_GOODS_REPORT_FLAG       15

// 从北京新的Paysys中拿到的接口，用来处理新手推广CDKey
struct  TAccountCDKEY : public KAccountHead
{
    char  szAccountName[32];
    short nFlag;         // KG_SPREAD_NEW_PLAYER_CDKEY_FLAG：新手推广的序列号验证

    int   nChangeValue;
    char  ChangeStr[64]; // 若flag=KG_SPREAD_NEW_PLAYER_CDKEY_FLAG时，该字符串表示新手推广的序列号
    int   nResevrval;
    char  ResevrStr[64];
};

// 向Paysys报告虚拟物品（元宝、金币、银票等）的结构
#define KG_MAX_GOODS_TYPE_COUNT 8
struct tagVirtualGoodsStatistic : KAccountHead
{
	char               szAccountName[32];  // fill:NULL\0
	short              nFlag;              // fill:15

    // report how many kinds of goods, the max value is KG_MAX_GOODS_TYPE_COUNT
    // such as 4, then the avaible values in llMoneyCount is the head 4 int64
    int                nGoodsTypeCount;

#ifdef WIN32
    unsigned __int64   ullGoodsAmount[KG_MAX_GOODS_TYPE_COUNT];
#else
	unsigned long long ullGoodsAmount[KG_MAX_GOODS_TYPE_COUNT];
#endif

    int                nResevrval;
    char               ResevrStr[64];
};

struct  TAccountCDKEYRet : public KAccountHead
{
    char  szAccountName[32];
    short nFlag;     // KG_SPREAD_NEW_PLAYER_CDKEY_FLAG：新手推广的序列号验证

    int   nResult;   // 请求返回结果
    char  ResevrStr[64];
    int   nResevrval;
};

//设置玩家计费状态
struct KAccountSetChargeFlag : public KAccountUser
{
    DWORD dwLastLoginIP;
    int   nChargeFlag;                           //0:免费,1:收费
    BYTE byReserve[128];
};
struct KAccountSetChargeFlagRet : public KAccountUser
{
    int   nChargeFlag;                           //0:免费,1:收费
    WORD  nExtPoint; 
    WORD  nExtPoint1;
    WORD  nExtPoint2;
    WORD  nExtPoint3;
    WORD  nExtPoint4;
    WORD  nExtPoint5;
    WORD  nExtPoint6;
    WORD  nExtPoint7;
    DWORD dwEndOfDayTime;    // 玩家包时(包天,包月等)的截止时间, time_t, 单位秒
    DWORD nLeftTimeOfPoint;  // 剩余点数
    union
    {
        struct  
        {
            DWORD nLeftTimeOfDay;    // byReserve[0] .. byReserve[3] 玩家计天的剩余秒数
            DWORD dwEndTimeOfFee;    // byReserve[4] .. byReserve[7]
        };
        BYTE byReserve[128];
    };
    int   nResult;
};

//////////////////////////  IB Mode Start  /////////////////////////////////////
enum enumIB_ItemUseType
{
    IB_UseType_Unknown = -1,       // 未知类型
    IB_UseType_Unlimit = 0,        // 永久使用（没有保值期）
    IB_UseType_Any_Time,           // 在过期前可以任意使用
    IB_UseType_By_Time,            // 在过期前可以使用一次
};

// GUID不为0，且高16位为0，则此GUID由PaySystem产品，为IB商品
#define IB_IS_IB_ITEM(nItemGUID) \
    (((nItemGUID > 0) && (nItemGUID >> 48) == 0) ? TRUE : FALSE)


#define MAX_ITEM_COUNT_IN_PACKAGE_TO_PAYSYS 16

struct KIBAccountBuyItem : public KAccountUser
{
    int   nPlayerDataIndex;                           // 玩家在游戏世界的编号
    int   nGoodsIndex;                                // 商品在商品的编号

    int   nItemTypeID;                                // 物品类型ID
    int   nItemLevel;                                 // 物品级别(与物品类型ID一起唯一定位物品)
    int   nUseType;                                   // 使用类型(enumIB_ItemUseType)
    int   nPrice;                                     // 购买价格
    DWORD dwOverdueTime;                              // 保期期(差值)
};

#define MAX_SD_UNIQUEID_SIZE 33
struct KIBAccountBuyItemSD : public KIBAccountBuyItem
{
    char szSDUniqueId[MAX_SD_UNIQUEID_SIZE];
};

struct KIBAccountBuyMultiItem : public KAccountUser
{
    int   nPlayerDataIndex;                           // 玩家在游戏世界的编号
    int   nGoodsIndex;                                // 商品在商品的编号

    int   nItemTypeID;                                // 物品类型ID
    int   nItemLevel;                                 // 物品级别(与物品类型ID一起唯一定位物品)
    int   nUseType;                                   // 使用类型(enumIB_ItemUseType)
    int   nPrice;                                     // 购买价格
    DWORD dwOverdueTime;                              // 保期期(差值)

    int   nItemCount;                                 // 请求的物品数量
    BYTE  byUseItemNow;                               // 购买的同时使用掉物品
};

struct KIBAccountBuyMultiItemSD : public KIBAccountBuyMultiItem
{
    char szSDUniqueId[MAX_SD_UNIQUEID_SIZE];
};

struct KIBAccountUseItem : public KAccountUser
{
    int       nPlayerDataIndex;                           // 玩家在游戏世界的编号

    int       nItemTypeID;                                // 物品类型ID
    int       nItemLevel;                                 // 物品级别(与物品类型ID一起唯一定位物品)
    long long llItemGUID;                                 // 物品在数据库的唯一编号
};

struct KIBAccountUseMultiItem : public KAccountUser
{
    int       nPlayerDataIndex;                           // 玩家在游戏世界的编号

    int       nItemTypeID;                                // 物品类型ID
    int       nItemLevel;                                 // 物品级别(与物品类型ID一起唯一定位物品)
    int       nItemCount;                                 // 请求的物品数量
    long long llItemGUID[MAX_ITEM_COUNT_IN_PACKAGE_TO_PAYSYS];  // 物品在数据库的唯一编号
};

struct KIBAccountBuyItemRet : public KAccountUser
{
    int       nPlayerDataIndex;                            // 玩家在游戏世界的编号
    int       nGoodsIndex;                                 // 商品在商品的编号

    int       nItemTypeID;                                 // 物品类型ID
    int       nItemLevel;                                  // 物品级别(与物品类型ID一起唯一定位物品)
    int       nPrice;                                      // 购买价格
    long long llItemGUID;                                  // 物品在数据库的唯一编号
    
    int       nResult;                                     // 结果返回码
};

struct KIBAccountBuyItemRetSD : public KIBAccountBuyItemRet
{
    char      szSDUniqueId[MAX_SD_UNIQUEID_SIZE];
};

struct KIBAccountBuyMultiItemRet : public KAccountUser
{
    int       nPlayerDataIndex;                            // 玩家在游戏世界的编号
    int       nGoodsIndex;                                 // 商品在商品的编号

    int       nItemTypeID;                                 // 物品类型ID
    int       nItemLevel;                                  // 物品级别(与物品类型ID一起唯一定位物品)
    int       nPrice;                                      // 购买价格
    int       nItemCount;                                  // 请求的物品数量
    long long llItemGUID[MAX_ITEM_COUNT_IN_PACKAGE_TO_PAYSYS];   // 物品在数据库的唯一编号

    int       nResult;                                     // 结果返回码
};

struct KIBAccountBuyMultiItemRetSD : public KIBAccountBuyMultiItemRet
{
    char      szSDUniqueId[MAX_SD_UNIQUEID_SIZE];
};

struct KIBAccountUseItemRet : public KAccountUser
{
    int       nPlayerDataIndex;                             // 玩家在游戏世界的编号

    int       nItemTypeID;                                  // 物品类型ID
    int       nItemLevel;                                   // 物品级别(与物品类型ID一起唯一定位物品)
    long long llItemGUID;                                   // 物品在数据库的唯一编号

    int       nResult;                                      // 结果返回码
};

struct KIBAccountUseMultiItemRet : public KAccountUser
{
    int       nPlayerDataIndex;                             // 玩家在游戏世界的编号

    int       nItemTypeID;                                  // 物品类型ID
    int       nItemLevel;                                   // 物品级别(与物品类型ID一起唯一定位物品)
    int       nItemCount;                                   // 请求的物品数量
    long long llItemGUID[MAX_ITEM_COUNT_IN_PACKAGE_TO_PAYSYS];   // 物品在数据库的唯一编号

    int       nResult;                                      // 结果返回码
};

struct KAccountUserReturnExtIB : public KAccountUserReturn    // Paysys ==> Bishop, 专用于IB模式的扩展协议。
{
    union
    {
        struct
        {
            DWORD nExtPoint0;        //可用的附送点0
            DWORD nExtPoint1;        //可用的附送点1
            DWORD nExtPoint2;        //可用的附送点2
            DWORD nExtPoint3;        //可用的附送点3
            DWORD nExtPoint4;        //可用的附送点4
            DWORD nExtPoint5;        //可用的附送点5
            DWORD nExtPoint6;        //可用的附送点6
            DWORD nExtPoint7;        //可用的附送点7
        };
        DWORD nExtPointArray[ACCOUNT_MAX_EXT_POINT_COUNT];
    };

    // 玩家剩余时间分为包时和点数两部分传下来
    DWORD dwEndOfDayTime;            // 玩家包时(包天,包月等)的截止时间, time_t, 单位秒
    DWORD dwLeftTimeOfPoint;         // 剩余点数
    DWORD dwLastLoginTime;           // 玩家上次登陆的时间
    DWORD dwLastLoginIP;             // 玩家上次登陆的IP
    DWORD dwLeftMoney;               // 返回玩家的金币余额，通过此方式可以做到传统计费与IB模式兼容。
    DWORD dwOnlineSecond;            // 玩家累计在线时间

    union
    {
        struct
        {
            DWORD dwLimitPlayTimeFlag;   // byReserve[0]  .. Reserve[3]
            DWORD dwLimitOnlineSecond;   // byReserve[4]  .. Reserve[7] 
            DWORD dwLimitOfflineSecond;  // byReserve[8]  .. Reserve[11]
            int   nChargeFlag;           // byReserve[12] .. Reserve[15]
            unsigned int  uAccountState; // byReserve[16] .. Reserve[19] 
            char  szPhoneNumber[20];     // byReserve[20] .. byReserve[39]
            DWORD dwGatewayID;           // byReserve[40] .. byReserve[43]
            BYTE  byPasspodVersion;      // byReserve[44] .. byReserve[44]密宝版本
            BYTE  byPasspodMode;         // byReserve[45] .. byReserve[45]密宝认证方式
            char  szMatrixPosition[9];   // byReserve[46] .. byReserve[54]需要用户输入的矩阵密码的位置
        };
        BYTE  byReserve[64];
    };
};
//////////////////////////  IB Mode End  ///////////////////////////////////////

// 帐号状态改变通知协议
struct KChangeAccountState : public KAccountUser
{
    int nStateType;
    int nStateValue;
};
struct KChangeAccountStateRet : public KAccountUser
{
    int nResult;
};

//冻结，解冻计费标志
enum Freeze_Fee_Flag
{
    FREEZE   = 1,      //锁定
    UNFREEZE = 2       //解锁
};

//冻结，解冻计费类型
enum Freeze_Fee_Type
{
    FREEZE_SECOND   = 1, //计点
    FREEZE_COIN     = 2, //金币
    FREEZE_EXTPOINT = 3  //扩展点
};

//冻结，解冻协议
struct KAccountFreezeFee : public KAccountUser
{
    long long llFreezeGUID;
    DWORD  dwFreezeFlag;
    DWORD  dwFreezeType;
    DWORD  dwExtPoint;   //若是扩展点冻结，该字段为扩展索引（0～7）
    DWORD  dwFreezeAmount;
};
struct KAccountFreezeFeeRet : public KAccountUser
{
    long long llFreezeGUID;
    DWORD  dwFreezeFlag;
    DWORD  dwFreezeType;
    DWORD  dwExtPoint;   //若是扩展点冻结，该字段为扩展索引（0～7）
    DWORD  dwFreezeAmount;
    
    int    nResult;
};


//转帐标志
enum Transfer_Flag
{
    TRANSFER_FREEZE_FEE    = 1, //转帐冻结的金币
    TRANSFER_UNFREEZE_FEE  = 2  //转帐未冻结的金币
};

//转帐类型
enum Transfer_Type
{
    TRANSFER_SECOND   = 1, //计点
    TRANSFER_COIN     = 2, //金币
    TRANSFER_EXTPOINT = 3  //扩展点
};
// 玩家转帐协议
struct KAccountTransfer : public KAccountHead
{
    long long llTransferGUID; //交易操作的唯一编号,由游戏世界传给Paysys.丢包后查询的依据
    char      AccountDest[LOGIN_USER_ACCOUNT_MAX_LEN]; 
    char      AccountSrc[LOGIN_USER_ACCOUNT_MAX_LEN]; 
    DWORD     dwTransferFlag;
    DWORD     dwTransferType;
    DWORD     dwExtPoint;       //若是扩展点冻结，该字段为扩展索引（0～7）
    DWORD     dwTransferAmount;
};
struct KAccountTransferRet : public KAccountHead
{
    long long llTransferGUID; //交易操作的唯一编号,由游戏世界传给Paysys.丢包后查询的依据
    char      AccountDest[LOGIN_USER_ACCOUNT_MAX_LEN]; 
    char      AccountSrc[LOGIN_USER_ACCOUNT_MAX_LEN]; 
    DWORD     dwTransferFlag;
    DWORD     dwTransferType;
    DWORD     dwExtPoint;       //若是扩展点冻结，该字段为扩展索引（0～7）
    DWORD     dwTransferAmount;
   
    int       nResult;
};


//转帐查询协议
//请求协议不含Account
struct KAccountQueryTransfer : public KAccountHead
{
    long long llTransferGUID; //交易操作的唯一编号,由游戏世界传给Paysys
};
struct KAccountQueryTransferRet : public KAccountHead
{
    long long llTransferGUID; //交易操作的唯一编号,由游戏世界传给Paysys
    DWORD     dwTransferTime;
    char      AccountDest[LOGIN_USER_ACCOUNT_MAX_LEN]; 
    char      AccountSrc[LOGIN_USER_ACCOUNT_MAX_LEN]; 
    DWORD     dwTransferFlag;
    DWORD     dwTransferType;
    DWORD     dwExtPoint;        //若是扩展点冻结，该字段为扩展索引（0～7）
    DWORD     dwTransferAmount;
    DWORD     dwTransferResult;

    int       nResult;
};

//兑换类型
enum Exchange_Type
{
    COIN_EXCHANGE_SECOND  = 1, //金币兑换计点
    COIN_EXCHANGE_DATE    = 2  //金币兑换包时

};

//玩家兑换
struct KAccountExchange : public KAccountUser
{
    DWORD  dwExchangeType; 
    DWORD  dwDestAmount; //兑换成的数目
    DWORD  dwSrcAmount;  //被兑换的数目
};
struct KAccountExchangeRet : public KAccountUser
{
    DWORD  dwExchangeType; 
    DWORD  dwDestAmount; //兑换成的数目
    DWORD  dwSrcAmount;  //被兑换的数目
    
    int    nResult;
};

//获取帐号信息    
struct KAccountUserInfo : public KAccountHead
{
    char      Account[LOGIN_USER_ACCOUNT_MAX_LEN]; 
};

struct KAccountUserInfoRet : public KAccountUserReturn
{
    union
    {
        struct
        {
            DWORD nExtPoint0;        //可用的附送点0
            DWORD nExtPoint1;        //可用的附送点1
            DWORD nExtPoint2;        //可用的附送点2
            DWORD nExtPoint3;        //可用的附送点3
            DWORD nExtPoint4;        //可用的附送点4
            DWORD nExtPoint5;        //可用的附送点5
            DWORD nExtPoint6;        //可用的附送点6
            DWORD nExtPoint7;        //可用的附送点7
        };
        DWORD nExtPointArray[ACCOUNT_MAX_EXT_POINT_COUNT];
    };
    DWORD     dwEndDate;
    DWORD     dwLeftSecond;
    DWORD     dwLastLoginTime;
    DWORD     dwLastLoginIP;
    DWORD     dwLeftCoin;            //剩余金币
    DWORD     dwLastLogoutTime;
    DWORD     dwActiveIP;
    DWORD     dwActiveTime;
    DWORD     dwActiveType;
};

struct KAccountUserPasspodVerify : public KAccountUser // Bishop ==> Paysys
{
    BYTE byPasspodVersion;    // 密宝版本
    BYTE byPasspodMode;       // 密宝认证方式
    char szTokenPassword[10]; // 令牌密码
    char szMatrixPosition[9]; // 需要用户输入的矩阵密码的位置
    char szMatrixPassword[9]; // 对应矩阵位置的密码
};

struct KAccountUserPasspodVerifyRet : public KAccountUser // Paysys ==>Bishop
{
    BYTE byPasspodVersion;    // 密宝版本
    BYTE byPasspodMode;       // 密宝认证方式
    char szMatrixPosition[9]; // 需要用户输入的矩阵密码的位置
    
    int nReturn;
};

// 获取区收费标志
struct KGetZoneChargeFlag : public KAccountHead
{
    char  szGatewayName[32];    // 网关名称，如gateway01...
    BYTE  byReserve[128];
};

struct KGetZoneChargeFlagRet : public KAccountHead
{
    char  szGatewayName[32];    // 网关名称
    int   nZoneChargeFlag;      // 0:免费,1:收费
	union
	{
		struct  
		{
			int  nZoneID;        // byReserve[0] .. byReserve[3]  区ID
			char szZoneName[32]; // byReserve[4] .. byReserve[35] 区名称
		};
		BYTE byReserve[128];
	};
    int   nResult;
};


struct KGameworld2Paysys : public KAccountHead
{
    unsigned    uDataSize;
    BYTE        byData[0];
};

struct KAccountActivePresentCode : public tagProtocolHeader
{
	char		szAccount[32];
	char		szPresentCode[32];
	DWORD		dwActiveIP;
};

struct KPaysys2Gameworld : public KAccountHead
{
    unsigned    uDataSize;
    BYTE        byData[0];
};

struct KAccountActivePresentCodeRet : KAccountActivePresentCode
{
	DWORD		dwPresentType;
	int			nResult;
};

enum Exchange_Ex_Type
{
    COIN_EXCHANGE_DATE_EX   = 1,
    COIN_EXCHANGE_SECOND_EX = 2,

};

//寄售
struct KAccountExchangeEx : public KAccountHead
{
    char   szSrcAccount[LOGIN_USER_ACCOUNT_MAX_LEN];
    char   szDestAccount[LOGIN_USER_ACCOUNT_MAX_LEN];
    DWORD  dwExchangeType; 
    DWORD  dwDestAmount; //兑换成的数目
    DWORD  dwSrcAmount;  //被兑换的数目
};
struct KAccountExchangeExRet : public KAccountHead
{
    char   szSrcAccount[LOGIN_USER_ACCOUNT_MAX_LEN];
    char   szDestAccount[LOGIN_USER_ACCOUNT_MAX_LEN];
    DWORD  dwExchangeType; 
    DWORD  dwDestAmount; //兑换成的数目
    DWORD  dwSrcAmount;  //被兑换的数目

    int    nResult;
};

// 新增加登录反馈协议，支持计天
struct KAccountUserLoginInfoExt : public KAccountUserPassword  // Bishop ==> Paysys, 玩家身份验证!
{
    DWORD UserIP;
    DWORD UserPort;
    BYTE  byMachineID[16];      // 相同的MachineID的连接被认为是同一台电脑多开
    BYTE  nLogout;              // 1表示login时要先logout，0表示正常登录
    char  szActivateCode[LOGIN_USER_ACCOUNT_MAX_LEN];

    union
    {
        struct
        {
            BYTE  byPasspodVersion;     // 密宝版本
            BYTE  byPasspodMode;        // 密宝认证方式
            char  szTokenPassword[10];  // 令牌密码
            char  szMatrixPosition[9];  // 需要用户输入的矩阵密码的位置
            char  szMatrixPassword[9];  // 对应矩阵位置的密码
        };
        BYTE  byReserve[128];
    };
};
struct KAccountUserLoginReturnExt : public KAccountUserReturn    // Paysys ==> Bishop, 专用于IB模式的扩展协议。
{
    union
    {
        struct   
        {
            DWORD nExtPoint0;        //可用的附送点0
            DWORD nExtPoint1;        //可用的附送点1
            DWORD nExtPoint2;        //可用的附送点2
            DWORD nExtPoint3;        //可用的附送点3
            DWORD nExtPoint4;        //可用的附送点4
            DWORD nExtPoint5;        //可用的附送点5
            DWORD nExtPoint6;        //可用的附送点6
            DWORD nExtPoint7;        //可用的附送点7
        };
        DWORD nExtPointArray[ACCOUNT_MAX_EXT_POINT_COUNT];
    };

    // 玩家剩余时间分为包时和点数两部分传下来
    DWORD dwEndOfDayTime;            // 玩家包时(包天,包月等)的截止时间, time_t, 单位秒
    DWORD dwLeftTimeOfPoint;         // 剩余点数
    DWORD dwLastLoginTime;           // 玩家上次登陆的时间
    DWORD dwLastLoginIP;             // 玩家上次登陆的IP
    DWORD dwLeftMoney;               // 返回玩家的金币余额，通过此方式可以做到传统计费与IB模式兼容。
    DWORD dwOnlineSecond;            // 玩家累计在线时间

    union
    {
        struct
        {
            DWORD dwLimitPlayTimeFlag;   // byReserve[0]  .. Reserve[3]
            DWORD dwLimitOnlineSecond;   // byReserve[4]  .. Reserve[7] 
            DWORD dwLimitOfflineSecond;  // byReserve[8]  .. Reserve[11]
            int   nChargeFlag;           // byReserve[12] .. Reserve[15]
            unsigned int  uAccountState; // byReserve[16] .. Reserve[19] 
            char  szPhoneNumber[20];     // byReserve[20] .. byReserve[39]
            DWORD dwGatewayID;           // byReserve[40] .. byReserve[43]
            BYTE  byPasspodVersion;      // byReserve[44] .. byReserve[44]密宝版本
            BYTE  byPasspodMode;         // byReserve[45] .. byReserve[45]密宝认证方式
            char  szMatrixPosition[9];   // byReserve[46] .. byReserve[54]需要用户输入的矩阵密码的位置
            DWORD nLeftTimeOfDay;        // byReserve[55] .. byReserve[58]计天模式中剩余的秒数
            DWORD dwEndTimeOfFee;        // byReserve[59] .. byReserve[62]玩家收费的截止日期
            DWORD dwLoginTime;           // byReserve[63] .. byReserve[66]玩家本次登陆的时间
            DWORD dwLastLogoutTime;      // byReserve[67] .. byReserve[70]玩家上次登出的时间
            struct 
            {
                WORD wYear;
                BYTE byMonth;
                BYTE byDay;
            } Birthday;                           // byReserve[71] .. byReserve[74]玩家的出生日期，用于封神3生日卡
        };
        BYTE  byReserve[128];
    };
};

// 新增加用户信息查询的反馈协议，支持计天
struct KAccountUserInfoExt : public KAccountHead
{
    char      Account[LOGIN_USER_ACCOUNT_MAX_LEN]; 
    BYTE      byReserve[128];
};
struct KAccountUserInfoRetExt : public KAccountUserReturn
{
    union
    {
        struct
        {
            DWORD nExtPoint0;        //可用的附送点0
            DWORD nExtPoint1;        //可用的附送点1
            DWORD nExtPoint2;        //可用的附送点2
            DWORD nExtPoint3;        //可用的附送点3
            DWORD nExtPoint4;        //可用的附送点4
            DWORD nExtPoint5;        //可用的附送点5
            DWORD nExtPoint6;        //可用的附送点6
            DWORD nExtPoint7;        //可用的附送点7
        };
        DWORD nExtPointArray[ACCOUNT_MAX_EXT_POINT_COUNT];
    };
    DWORD     dwEndDate;
    DWORD     dwLeftSecond;
    DWORD     dwLastLoginTime;
    DWORD     dwLastLoginIP;
    DWORD     dwLeftCoin;            //剩余金币
    DWORD     dwLastLogoutTime;
    DWORD     dwActiveIP;
    DWORD     dwActiveTime;
    DWORD     dwActiveType;
    union
    {
        struct  
        {
            DWORD     nLeftTimeOfDay; // byReserve[0] .. byReserve[3]计天模式中的剩余秒数
            DWORD     dwEndTimeOfFee; // byReserve[4] .. byReserve[7]
        };
        BYTE byReserve[128];
    };
};

// 新增加密保的反馈协议，支持新的密保登录流程
struct KAccountUserPasspodVerifyExt : public KAccountUser // Bishop ==> Paysys
{
    BYTE byPasspodVersion;    // 密宝版本
    BYTE byPasspodMode;       // 密宝认证方式
    char szTokenPassword[10]; // 令牌密码
    char szMatrixPosition[9]; // 需要用户输入的矩阵密码的位置
    char szMatrixPassword[9]; // 对应矩阵位置的密码
    union
    {	
        struct
        {
            BYTE byLogoutIfFailed;    // 验证失败了是否登出
            BYTE byLogoutDeductFlag;  // 登出是否扣费
        };
        BYTE byReserve[128];
    };
};
struct KAccountUserPasspodVerifyRetExt : public KAccountUser // Paysys ==>Bishop
{
    BYTE byPasspodVersion;    // 密宝版本
    BYTE byPasspodMode;       // 密宝认证方式
    char szMatrixPosition[9]; // 需要用户输入的矩阵密码的位置
    BYTE byReserve[128];
    int nReturn;
};

#pragma    pack(pop)

#endif // __ACCOUNTLOGINDEF_H__
