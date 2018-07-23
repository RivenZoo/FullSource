// Gateway <---> Client protocol defines
#ifndef _GATEWAY_CLIENT_PROTOCOL_H_
#define _GATEWAY_CLIENT_PROTOCOL_H_

#include "Protocol/AccountLoginDef.h"
#include "GatewayDef.h"

enum C2G_PROTOCOL
{
    c2g_protocol_begin,
    c2g_ping_signal,
    c2g_handshake_request,
    c2g_account_verify_request,
    c2g_snda_token_verify_request,
    c2g_mibao_verify_request,
    c2g_query_newbie_maps,
    c2g_create_role_request,
    c2g_delete_role_request,
    c2g_game_login_request,
    c2g_giveup_queue_request,
    c2g_rename_request,
    c2g_protocol_total
};


enum G2C_PROTOCOL
{
    g2c_protocol_begin,
    g2c_ping_respond,
    g2c_handshake_respond,
    g2c_account_locked_notify,
    g2c_account_verify_respond,
    g2c_mibao_verify_respond,
    g2c_kick_account_notify,
    g2c_sync_role_list,
    g2c_sync_newbie_maps,
    g2c_create_role_respond,
    g2c_delete_role_respond,
    g2c_game_login_prepare,
    g2c_sync_login_key,
    g2c_sync_queue_state,
    g2c_giveup_queue_respond,
    g2c_rename_respond,
    g2c_snda_verify_respond,
    g2c_protocol_total
};

#pragma	pack(1)

struct KGC_PROTOCOL_HEADER 
{
    BYTE byProtocol;
};

// -------------- Client --> Gateway ------------------------------

struct C2G_PING_SIGNAL : KGC_PROTOCOL_HEADER
{
    DWORD dwTime;
};

struct C2G_HANDSHAKE_REQUEST : KGC_PROTOCOL_HEADER
{
    int  nGatewayVersion;
    int  nGameWorldVersion;
};

struct C2G_ACCOUNT_VERIFY_REQUEST : KGC_PROTOCOL_HEADER
{
    char szAcc[_NAME_LEN];
    char szPsw[LOGIN_USER_PASSWORD_MAX_LEN];
    char szAct[LOGIN_USER_PASSWORD_MAX_LEN];
};

struct C2G_SNDA_TOKEN_VERIFY_REQUEST : KGC_PROTOCOL_HEADER 
{
    char szSndaID[SNDA_ID_LEN];
    char szToken[SNDA_TOKEN_LEN];
};

struct C2G_MIBAO_VERIFY_REQUEST : KGC_PROTOCOL_HEADER 
{
    char szMibaoPassword[10];
};

struct C2G_QUERY_NEWBIE_MAPS : KGC_PROTOCOL_HEADER
{
    DWORD dwReserved;
};

struct C2G_CREATE_ROLE_REQUEST : KGC_PROTOCOL_HEADER
{
    BYTE byData[0];
};

struct C2G_DELETE_ROLE_REQUEST : KGC_PROTOCOL_HEADER
{
    DWORD dwRoleID;
};

struct C2G_GAME_LOGIN_REQUEST : KGC_PROTOCOL_HEADER
{
    DWORD dwRoleID;
};

struct C2G_GIVEUP_QUEUE_REQUEST : KGC_PROTOCOL_HEADER
{
    BYTE byNothing;
};

struct C2G_RENAME_REQUEST : KGC_PROTOCOL_HEADER
{
    BYTE    byCancel;
    DWORD   dwRoleID;
    char    szNewName[_NAME_LEN];
};

// ---------------- Gateway --> Client -----------------------------

struct G2C_PING_RESPOND : KGC_PROTOCOL_HEADER
{
    DWORD dwTime;
};

struct G2C_HANDSHAKE_RESPOND : KGC_PROTOCOL_HEADER
{
    BYTE    byCode;
    BOOL    bZoneChargeFlag;
};

struct G2C_ACCOUNT_LOCKED_NOTIFY : KGC_PROTOCOL_HEADER
{
    BYTE byNothing;
};

struct G2C_ACCOUNT_VERIFY_RESPOND : KGC_PROTOCOL_HEADER
{
    int     nCode;
    BYTE    byMibaoMode;
    char    szMatrixPosition[9];
    BOOL    bChargeFlag;
    DWORD   dwEndOfDayTime;
    DWORD   dwLeftTimeOfPoint;
    DWORD   dwLeftTimeOfDay;
    DWORD   dwEndTimeOfFee;
    time_t  nLoginTime;
    time_t  nLastLoginTime;
    DWORD   dwLastLoginIP;
};

struct G2C_MIBAO_VERIFY_RESPOND : KGC_PROTOCOL_HEADER 
{
    int     nCode;
    char    szMatrixPosition[9];
};

struct G2C_KICK_ACCOUNT_NOTIFY : KGC_PROTOCOL_HEADER
{
    BYTE byNothing;
};

struct G2C_SYNC_ROLE_LIST : KGC_PROTOCOL_HEADER
{
    int    nRoleIndex;
    int    nRoleCount;
    BYTE   byData[0];
};

struct G2C_SYNC_NEWBIE_MAPS : KGC_PROTOCOL_HEADER
{
    DWORD                   dwMapID;
    int                     nCopyCount;
    KNEWBIE_MAP_COPY_INFO   CopyInfo[0];
};

struct G2C_CREATE_ROLE_RESPOND : KGC_PROTOCOL_HEADER
{
    BYTE  byCode;
    DWORD dwRoleID;
    BYTE  byData[0];
};

struct G2C_DELETE_ROLE_RESPOND : KGC_PROTOCOL_HEADER
{
    BYTE    byCode;
    DWORD   dwRoleID;
    time_t  nDeleteTime;
};

struct G2C_SYNC_LOGIN_KEY : KGC_PROTOCOL_HEADER
{
    BYTE  byCode;
    DWORD dwRoleID;
    DWORD dwIP;
    int   nPort;
    GUID  guid;
};

struct G2C_SYNC_QUEUE_STATE : KGC_PROTOCOL_HEADER
{
    int nPosition;
};

struct G2C_GIVEUP_QUEUE_RESPOND : KGC_PROTOCOL_HEADER
{
    BYTE byNothing;
};

struct G2C_RENAME_RESPOND : KGC_PROTOCOL_HEADER
{
    BYTE    byCode;
    DWORD   dwRoleID;
    BYTE    byData[0];
};

struct G2C_SNDA_VERIFY_RESPOND : KGC_PROTOCOL_HEADER 
{
    int nRespondCode;
};

#pragma pack()

#endif
