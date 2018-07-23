//////////////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   BishopLoginQueueProtocol.h
//  Version     :   1.0
//  Creater     :   Zhu Chengmin
//  Date        :   2010-5-20
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////

#ifndef _BISHOP_LOGIN_QUEUE_PROTOCOL_H_
#define _BISHOP_LOGIN_QUEUE_PROTOCOL_H_ 1

#include "ProtocolBasic.h"

enum C2BL_PROTOCOL
{
    c2bl_protocol_invalid = 0,

    c2bl_request_queue,
    c2bl_giveup_queue,
    c2bl_ping,

    c2bl_protocol_total
};

enum BL2C_PROTOCOL
{
    bl2c_protocol_invalid = 0,

    bl2c_sync_request_queue_result,
    bl2c_sync_giveup_queue_result,
    bl2c_sync_queue_state,
    bl2c_sync_login_key,

    bl2c_protocol_total
};

#pragma	pack(push, 1)

struct C2BL_REQUEST_QUEUE : public tagProtocolHeader 
{
    char szAccountName[_NAME_LEN];
};

struct C2BL_GIVEUP_QUEUE : public tagProtocolHeader 
{
    unsigned char byReserve;
};

struct C2BL_PING : public tagProtocolHeader
{
    unsigned char byReserve;
};

//------------------------------------------------------------------------------------

struct BL2C_SYNC_REQUEST_QUEUE_RESULT : public tagProtocolHeader 
{
    unsigned uPlayerID;
    int      nResult;
};

struct BL2C_SYNC_GIVEUP_QUEUE_RESULT : public tagProtocolHeader 
{
    int nResult;
};

struct BL2C_SYNC_QUEUE_STATE : public tagProtocolHeader 
{
    int nPosition;
};

struct BL2C_SYNC_LOGIN_KEY : public tagProtocolHeader 
{
    GUID guid;
};

#pragma pack(pop)

#endif //_BISHOP_LOGIN_QUEUE_PROTOCOL_H_
