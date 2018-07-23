#ifndef _BISHOP_PAYSYS_H_
#define _BISHOP_PAYSYS_H_

#include "../ProtocolBasic.h"
#include "AccountLoginDef.h"

enum B2P_PROTOCOL_ID // Bishop ==> Paysys
{
    B2P_PROTOCOL_BEGIN = PROTOCOL_NORMAL_PACKAGE_BEGIN,
    B2P_BISHOP_IDENTITY_VERIFY = 36,           // Bishop启动后首次登陆身份验证, ref : KServerAccountUserLoginInfo，注意，北京Paysys是：KServerAccountUserLoginInfo2
    B2P_BISHOP_RECONNECT_IDENTITY_VERIFY = 37, // Bishop断线重连身份验证, ref : 同B2P_BISHOP_IDENTITY_VERIFY
    B2P_BISHOP_LOGOUT = 39,                    // Bishop退出， ref : KServerAccountUserLoginInfo
    B2P_PLAYER_IDENTITY_VERIFY = 33,           // 玩家身份验证, ref : KAccountUserLoginInfo
    B2P_PLAYER_ENTER_GAME = 34,                // 玩家进入游戏, ref : KAccountUser
    B2P_PLAYER_LEAVE_GAME = 35,                // 玩家离开游戏, ref : KAccountUserLogout
    B2P_EXT_POINTS_OPERATION = 40,             // 附加点操作, ref : KAccountUserChangeExtPoint
    B2P_CLEANUP_ACCOUNT_FREE_TIME = 42,        // 清除新手免费时间, ref : TRYOUT_TIMEOUT_ASK
    B2P_PING = 112,                            // ping包, ref : PING_COMMAND
    B2P_USE_SPREADER_CDKEY = 50,               // 玩家使用推广员cdkey, ref : TAccountCDKEY

    // IB Mode.
    B2P_IB_PLAYER_BUY_ITEM = 60,               // 玩家在IB模式下购买物品。
    B2P_IB_PLAYER_USE_ITEM = 61,               // 玩家在IB模式下使用物品。
    B2P_IB_PLAYER_IDENTITY_VERIFY = 62,        // 玩家在IB模式下的登入验证。
    B2P_PLAYER_SET_CHARGE_FLAG    = 63,        // 玩家设置ChargeFlag
    B2P_PLAYER_EXCHANGE = 65,                  // 玩家兑换
    B2P_PLAYER_TRANSFER = 66,                  // 玩家转帐
    B2P_PLAYER_QUERY_TRANSFER = 67,            // 玩家转帐查询
    B2P_PLAYER_FREEZE_FEE = 68,                // 玩家冻结费用
    B2P_GAMEWORLD_2_PAYSYS = 69,               // 通用协议: 游戏世界到Paysys的请求 
    
    B2P_CHANGE_ACCOUNT_STATE = 70,
  
    B2P_IB_PLAYER_BUY_MULTI_ITEM = 71,         // 玩家在IB模式下购买多个物品
    B2P_IB_PLAYER_USE_MULTI_ITEM = 72,         // 玩家在IB模式下使用多个物品
    
    B2P_PLAYER_INFO    = 73,
    
    B2P_PLAYER_PASSPOD_VERIFY = 74,            // 密宝认证  
    
    B2P_IB_PLAYER_BUY_ITEM_SD = 75,            // 玩家在IB模式下购买物品。
    B2P_IB_PLAYER_BUY_MULTI_ITEM_SD = 76,      // 玩家在IB模式下购买多个物品

    B2P_PLAYER_IDENTITY_VERIFY_SD = 77,        // 盛大玩家专有的登入验证, 返回包依然使用P2B_PLAYER_IDENTITY_VERIFY_RESULT
    B2P_IB_PLAYER_IDENTITY_VERIFY_SD = 78,     // 盛大玩家在IB模式下的登入验证, 返回包使用P2B_IB_PLAYER_IDENTITY_VERIFY_RESULT
    B2P_GET_ZONE_CHARGE_FLAG = 79,             // 获取网关所在区的收费标志

    B2P_PLAYER_EXCHANGE_EX = 80,               // 玩家寄售协议

    B2P_PLAYER_PASSPOD_VERIFY_EX = 81,         // 密保认证扩展，支持新的密保认证

    B2P_IB_PLAYER_IDENTITY_VERIFY_EX = 82,     // 新增加IB上行，支持计天
    B2P_PLAYER_INFO_EX = 85,                   // 新增加上行，支持计天

	B2P_IB_PLAYER_IDENTITY_VERIFY_SD_EX = 86   // 盛大新上行，反馈新下行
};



enum P2B_PROTOCOL_ID // Paysys ==> Bishop
{
    P2B_PROTOCOL_BEGIN = PROTOCOL_NORMAL_PACKAGE_BEGIN,
    P2B_BISHOP_IDENTITY_VERIFY_RESULT = 36,     // Bishop登陆Paysys的校验结果, ref : KAccountUserReturnVerify
    P2B_PLAYER_IDENTITY_VERIFY_RESULT = 33,     // 玩家验证结果, ref : KAccountUserReturnExt
    P2B_EXT_POINTS_OPERATION_RESULT = 40,       // 修改附加点的结果返回, ref : KAccountUserReturnExt2
    P2B_LEAVE_GAME_RESPOND = 35,                // B2P_PLAYER_LEAVE_GAME协议的响应结果, 目前忽略
    P2B_ACCOUNT_FREE_TIME_CLEANING_RESULT = 64, // 清除新手免费时间的操作结果, ref : TRYOUT_TIMEOUT_ANS
    P2B_PING = 130,                             // 回ping, ref : PING_COMMAND
    P2B_USE_SPREADER_CDKEY_RESULT = 50,         // 玩家使用推广员cdkey的返回结果, ref : TAccountCDKEYRet

    // IB Mode.
    P2B_IB_PLAYER_BUY_ITEM_RESULT = 60,         // 玩家在IB模式下购买物品的回应包。
    P2B_IB_PLAYER_USE_ITEM_RESULT = 61,         // 玩家在IB模式下使用物品的回应包。
    P2B_IB_PLAYER_IDENTITY_VERIFY_RESULT = 62,  // 玩家在IB模式下登入验证的回应包。
    P2B_PLAYER_SET_CHARGE_FLAG_RESULT    = 63,  // 玩家设置ChargeFlag
    P2B_PLAYER_EXCHANGE = 65,                   // 玩家兑换
    P2B_PLAYER_TRANSFER = 66,                   // 玩家转帐
    P2B_PLAYER_QUERY_TRANSFER = 67,             // 玩家转帐查询
    P2B_PLAYER_FREEZE_FEE = 68,                 // 玩家冻结费用
    P2B_PAYSYS_2_GAMEWORLD = 69,                // 通用协议: Paysys到游戏世界的回应包

    P2B_CHANGE_ACCOUNT_STATE = 70,

    P2B_IB_PLAYER_BUY_MULTI_ITEM_RESULT = 71,   // 玩家在IB模式下购买多个物品的回应包
    P2B_IB_PLAYER_USE_MULTI_ITEM_RESULT = 72,   // 玩家在IB模式下使用多个物品的回应包
    
    P2B_PLAYER_INFO_RESULT    = 73,
    
    P2B_PLAYER_PASSPOD_VERIFY = 74,              // 密宝认证 

    P2B_IB_PLAYER_BUY_ITEM_RESULT_SD = 75,       // 盛大玩家在IB模式下购买物品的回应包
    P2B_IB_PLAYER_BUY_MULTI_ITEM_RESULT_SD = 76, // 盛大玩家在IB模式下购买多个物品的回应包

    P2B_GET_ZONE_CHARGE_FLAG = 79,               // 获取网关所在区的收费标志的回应包
    P2B_PLAYER_EXCHANGE_EX = 80,                 // 玩家寄售协议回应包
    P2B_PLAYER_PASSPOD_VERIFY_EX = 81,           // 密保认证新协议
    P2B_IB_PLAYER_IDENTITY_VERIFY_RESULT_EX = 82,// 玩家在IB模式下登入验证的回应包，ref : KAccountUserReturnExtIB2
 
    P2B_PLAYER_INFO_RESULT_EX = 85               // 获取玩家信息反馈包，扩展，ref ：KAccountUserInfoRetExt
};

#endif

