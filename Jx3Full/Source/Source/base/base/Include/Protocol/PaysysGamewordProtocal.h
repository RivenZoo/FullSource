#ifndef _PAYSYS_GAMEWORLD_PROTOCAL_H_
#define _PAYSYS_GAMEWORLD_PROTOCAL_H_

#include "AccountLoginDef.h"

#pragma    pack(push, 1)

enum G2P_PROTOCOL_ID
{
    G2P_PROTOCOL_BEGIN = 0,
    G2P_PLAYER_ACTIVE_PRESENT_CODE = 50
};

enum P2G_PROTOCOL_ID
{
    P2G_PROTOCOL_BEGIN = 0,
    P2G_PLAYER_ACTIVE_PRESENT_CODE = 50
};

//礼品卡激活
struct KAccountActivePresentCode : public tagProtocolHeader
{
    char        Account[LOGIN_USER_ACCOUNT_MAX_LEN];
    char        PresentCode[LOGIN_USER_ACCOUNT_MAX_LEN]; //礼品卡号
    DWORD       dwActiveIP;                              //激活IP
};
struct KAccountActivePresentCodeRet : public tagProtocolHeader
{
    char        Account[LOGIN_USER_ACCOUNT_MAX_LEN];
    char        PresentCode[LOGIN_USER_ACCOUNT_MAX_LEN]; //礼品卡号
    DWORD       dwActiveIP;                              //激活IP
    DWORD       dwPresentType;                           //礼品卡类型，用于游戏世界决定用的礼品
    
    int         nResult;
};

#pragma    pack(pop)

#endif // _PAYSYS_GAMEWORLD_PROTOCAL_H_