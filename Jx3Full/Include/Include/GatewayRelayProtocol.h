#ifndef _GATEWAY_RELAY_PROTOCOL_H_
#define _GATEWAY_RELAY_PROTOCOL_H_

#include "GatewayDef.h"

enum G2R_PROTOCOL
{
    g2r_protocol_begin,
    g2r_ping_signal,
    g2r_query_account_state,
    g2r_query_role_list,
    g2r_query_newbie_maps,
    g2r_kick_account_notify,
    g2r_create_role_request,
    g2r_delete_role_request,
    g2r_game_login_request,
    g2r_change_ext_point_respond,
    g2r_set_charge_flag_respond,
    g2r_get_zone_charge_flag_notify,
    g2r_active_present_code_respond,
    g2r_freeze_coin_respond,
    g2r_account_exchange_respond,
    g2r_rename_request,
    g2r_protocol_total
};

enum R2G_PROTOCOL
{
    r2g_protocol_begin,
    r2g_ping_signal,
    r2g_sync_account_state,
    r2g_sync_role_list,
    r2g_create_role_respond,    
    r2g_delete_role_respond,
    r2g_game_login_respond,
    r2g_ext_points_opt_request,
    r2g_set_game_world_version,
    r2g_sync_newbie_maps,
    r2g_player_leave_game,
    r2g_change_ext_point_request,
    r2g_set_charge_flag_request,
    r2g_active_present_code_request,
    r2g_freeze_coin_request,
    r2g_account_exchange_request,
    r2g_rename_respond,
    r2g_protocol_total
};

#pragma	pack(1)

struct KGR_PROTOCOL_HEADER 
{
    BYTE byProtocol;
};

// ------ Gateway ---> Relay ----------------------------

struct G2R_PING_SIGNAL : KGR_PROTOCOL_HEADER
{
    DWORD dwTime;
};

struct G2R_QUERY_ACCOUNT_STATE : KGR_PROTOCOL_HEADER
{
    int     nPlayerIndex;
    char    szAccount[_NAME_LEN];
};

struct G2R_QUERY_ROLE_LIST : KGR_PROTOCOL_HEADER
{
    int     nPlayerIndex;
    char    szAccount[_NAME_LEN];
};

struct G2R_QUERY_NEWBIE_MAPS : KGR_PROTOCOL_HEADER
{
    int     nPlayerIndex;
};

struct G2R_KICK_ACCOUNT_NOTIFY : KGR_PROTOCOL_HEADER
{
    char szAccount[_NAME_LEN];
};

struct G2R_CREATE_ROLE_REQUEST: KGR_PROTOCOL_HEADER
{
    int     nPlayerIndex;
    char    szAccount[_NAME_LEN];
    BYTE    byData[0];
};

struct G2R_DELETE_ROLE_REQUEST : KGR_PROTOCOL_HEADER
{
    int     nPlayerIndex;
    DWORD   dwRoleID;
};

struct G2R_GAME_LOGIN_REQUEST : KGR_PROTOCOL_HEADER
{
    int             nPlayerIndex;
    char            szAccountName[_NAME_LEN];
    DWORD           dwRoleID;
    DWORD           dwQueueID;
    int             nChargeFlag;
    tagExtPointInfo	ExtPointInfo;			    // 可用的附加点
    DWORD           dwEndTimeOfFee;             // 收费总截止时间
    DWORD           dwCoin;
    DWORD           dwLimitPlayTimeFlag;        // 防沉迷标志位
    DWORD           dwLimitOnlineSecond;        // 防沉迷累计在线时间
    DWORD           dwLimitOfflineSecond;       // 防沉迷累计离线时间
    BYTE            byData[0];
};

struct G2R_CHANGE_EXT_POINT_RESPOND : KGR_PROTOCOL_HEADER
{
    DWORD dwRoleID;
    BOOL  bSucceed;
};

struct G2R_SET_CHARGE_FLAG_RESPOND : KGR_PROTOCOL_HEADER 
{
    BOOL            bSucceed;
    DWORD           dwRoleID;
    int             nChargeFlag;
    tagExtPointInfo ExtPointInfo;
    DWORD           dwEndTimeOfFee;
};

struct G2R_GET_ZONE_CHARGE_FLAG_NOTIFY : KGR_PROTOCOL_HEADER 
{
    int     nZoneChargeFlag;
};

struct G2R_ACTIVE_PRESENT_CODE_RESPOND : KGR_PROTOCOL_HEADER 
{
    BOOL    bSucceed;
    DWORD   dwRoleID;
    char    szPresentCode[_NAME_LEN];
    DWORD   dwPresentType;
};

struct G2R_FREEZE_COIN_RESPOND : KGR_PROTOCOL_HEADER 
{
    BOOL    bSucceed;
    DWORD   dwRequestID;
    BOOL    bFreezeFlag;
    int     nCoin;
};

struct G2R_ACCOUNT_EXCHANGE_RESPOND : KGR_PROTOCOL_HEADER 
{
    BOOL    bSucceed;
    DWORD   dwRequestID;
};

struct G2R_RENAME_REQUEST : KGR_PROTOCOL_HEADER
{
    int     nPlayerIndex;
    DWORD   dwRoleID;
    char    szNewName[_NAME_LEN];
};

// ------ Relay ---> Gateway ----------------------------

struct R2G_PING_SIGNAL : KGR_PROTOCOL_HEADER
{
    DWORD dwTime;
};

struct R2G_SYNC_ACCOUNT_STATE : KGR_PROTOCOL_HEADER
{
    int     nPlayerIndex;
    BOOL    bOnline;
};

struct R2G_SYNC_ROLE_LIST : KGR_PROTOCOL_HEADER
{
    int    nPlayerIndex;
    int    nRoleIndex;
    int    nRoleCount;
    DWORD  dwRoleID;
    BYTE   byData[0];
};

struct R2G_CREATE_ROLE_RESPOND : KGR_PROTOCOL_HEADER
{
    int     nPlayerIndex;
    BYTE    byCode;
    DWORD   dwRoleID;
    BYTE    byData[0];
};

struct R2G_DELETE_ROLE_RESPOND : KGR_PROTOCOL_HEADER
{
    int     nPlayerIndex;
    BYTE    byCode;
    DWORD   dwRoleID;
    time_t  nDeleteTime;
};

struct R2G_GAME_LOGIN_RESPOND : KGR_PROTOCOL_HEADER
{
    int     nPlayerIndex;
    BYTE    byCode;
    DWORD   dwRoleID;
    DWORD   dwQueueID;
    DWORD   dwIP;
    int     nPort;
    GUID    guid;
};

struct R2G_EXT_POINTS_OPT_REQUEST : KGR_PROTOCOL_HEADER
{
};

struct R2G_SET_GAME_WORLD_VERSION : KGR_PROTOCOL_HEADER
{
    int     nLowerVersion;
    int     nUpperVersion;
};

struct R2G_SYNC_NEWBIE_MAPS : KGR_PROTOCOL_HEADER
{
    int                     nPlayerIndex;
    DWORD                   dwMapID;
    int                     nCopyCount;
    KNEWBIE_MAP_COPY_INFO   CopyInfo[0];
};

struct R2G_PLAYER_LEAVE_GAME : KGR_PROTOCOL_HEADER
{
    char szAccount[_NAME_LEN];
};

struct R2G_CHANGE_EXT_POINT_REQUEST : KGR_PROTOCOL_HEADER 
{
    char    szAccount[_NAME_LEN];
    DWORD   dwRoleID;
    WORD    wExtPointIndex;
    WORD    wChangeValue;
};

struct R2G_SET_CHARGE_FLAG_REQUEST : KGR_PROTOCOL_HEADER 
{
    char    szAccount[_NAME_LEN];
    DWORD   dwRoleID;
    DWORD   dwLastLoginIP;
    int     nChargeFlag;
};

struct R2G_ACTIVE_PRESENT_CODE_REQUEST : KGR_PROTOCOL_HEADER 
{
    char    szAccount[_NAME_LEN];
    DWORD   dwRoleID;
    char    szPresentCode[_NAME_LEN];
    DWORD   dwActiveIP;
};

struct R2G_FREEZE_COIN_REQUEST : KGR_PROTOCOL_HEADER 
{
    DWORD   dwRequestID;
    char    szAccount[_NAME_LEN];
    BOOL    bFreezeFlag;
    int     nCoin;
};

struct R2G_ACCOUNT_EXCHANGE_REQUEST : KGR_PROTOCOL_HEADER 
{
    DWORD   dwRequestID;
    char    szSrcAccount[_NAME_LEN];
    char    szDstAccount[_NAME_LEN];
    DWORD   dwExchangeType;
    DWORD   dwDstAmount;
    DWORD   dwSrcAmount;
};

struct R2G_RENAME_RESPOND : KGR_PROTOCOL_HEADER
{
    int     nPlayerIndex;
    BYTE    byCode;
    DWORD   dwRoleID;
    BYTE    byData[0];
};
#pragma pack()

#endif
