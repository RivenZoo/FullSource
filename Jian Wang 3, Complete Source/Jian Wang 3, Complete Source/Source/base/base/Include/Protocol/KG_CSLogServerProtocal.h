////////////////////////////////////////////////////////////////////////////////
//
//  FileName    : KG_LogServerProtocal.h
//  Version     : 1.0
//  Creator     : Wu Caizhong
//  Create Date : 2008-6-13 11:21:52
//  Comment     : 
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _INCLUDE_KG_LOGSERVERPROTOCAL_H_
#define _INCLUDE_KG_LOGSERVERPROTOCAL_H_

#include "ProtocolBasic.h"

#pragma	pack(push, 1)

////////////////////////////////////////////////////////////////////////////////
const unsigned KG_LOG_SERVER_MAX_PACKET_SIZE = 4096;

enum KG_LOG_SERVER_C2S_PROTOCAL_ID
{
    LOGC2S_PING = PROTOCOL_NORMAL_PACKAGE_BEGIN + 1,
    LOGC2S_LOG_LOGIN,              // must be first command, ref: KGCSLogServerLogin
    LOGC2S_LOG_ITEM_OPERATION,     // ref: KGItemLog
    LOGC2S_LOG_PLAYER_ACTION       // ref: KGPlayerActionLog
};

enum KG_LOG_SERVER_S2C_PROTOCAL_ID
{
    LOGS2C_PING_RESULT = PROTOCOL_NORMAL_PACKAGE_BEGIN + 1,
    LOGC2S_LOG_LOGIN_RESULT,            // ref: TProcessData 
                                        // TProcessData.pDataBuffer[0]:0 failed, TProcessData.pDataBuffer[0]:1 success
    LOGS2C_LOG_ITEM_OPERATION_RESULT,   // ref: TProcessData
                                        // TProcessData.pDataBuffer[0]:0 failed, TProcessData.pDataBuffer[0]:1 success
    LOGS2C_LOG_PLAYER_ACTION_RESULT     // ref: TProcessData
                                        // TProcessData.pDataBuffer[0]:0 failed, TProcessData.pDataBuffer[0]:1 success
};

////////////////////////////////////////////////////////////////////////////////
struct KGCSLogServerLogin : tagProtocolHeader2
{
    char szGatewayName[_NAME_LEN];
};

//////////////////////////////////////////////////////////////////////////
const unsigned LOG_ITEM_RESTORE_DATA_MAX_SIZE   = 1024;
const unsigned LOG_COMMENT_MAX_SIZE             = 2048;

enum LOG_RETURN_CODE
{
    LOG_RETURN_FAILED  = 0,
    LOG_RETURN_SUCCESS = 1,
    LOG_RETURN_FILTER  = 2
};

enum ITEM_OPERATION_TYPE
{
    ITEM_OPERATION_TYPE_IN  = 0, // 获得物品
    ITEM_OPERATION_TYPE_OUT = 1, // 失去物品

    ITEM_OPERATION_TYPE_COUNT
};

struct KGItemLog : tagProtocolHeader2
{
    ITEM_OPERATION_TYPE eOperationType;
    char                szAccountName[_NAME_LEN];
    char                szRoleName[_NAME_LEN];
    unsigned long long  ullItemID;               // 物品ID，用来唯一标识一个特定的物品
    char                szItemName[_NAME_LEN];
    unsigned            uItemValue;              // 物品价值量
    unsigned            uItemRestoreDataSize;    // include string's terminal '\0', max size is LOG_ITEM_RESTORE_DATA_MAX_SIZE
    unsigned            uCommentSize;            // include string's terminal '\0', max size is LOG_COMMENT_MAX_SIZE, set to 0 for none comment
    unsigned char       pbyData[1];       // following data size is :uItemRestoreDataSize + uCommentSize
};

//////////////////////////////////////////////////////////////////////////
enum PLAYER_ACTION_TYPE
{
    PLAYER_ACTION_PLAYER_LEVELUP        = 0,    // 玩家升级
    PLAYER_ACTION_PLAYER_LEVELDOWN      = 1,    // 玩家降级

    PLAYER_ACTION_JOIN_FACTION          = 2,    // 加入门派
    PLAYER_ACTION_LEAVE_FACTION         = 3,    // 退出门派

    PLAYER_ACTION_JOIN_TONG             = 4,    // 加入家族
    PLAYER_ACTION_LEAVE_TONG            = 5,    // 推出家族
    PLAYER_ACTION_KICK_TONG             = 6,    // 踢出家族
    PLAYER_ACTION_FIGURECHANGE_TONG     = 7,    // 职位变更

    PLAYER_ACTION_ACCEPT_TASK           = 8,    // 接受任务
    PLAYER_ACTION_FINISH_TASK           = 9,    // 完成任务
    PLAYER_ACTION_CANCEL_TASK           = 10,   // 取消任务

    PLAYER_ACTION_ACCEPT_AWARD          = 11,   // 领取奖励
    PLAYER_ACTION_ACCEPT_REPAIR         = 12,   // 获取补偿

    PLAYER_ACTION_LOGIN                 = 13,   // 登录
    PLAYER_ACTION_LOGOUT                = 14,   // 正常离线
    PLAYER_ACTION_BEGIN_OFFLIVE         = 15,   // 离线托管开始
    PLAYER_ACTION_END_OFFLIVE           = 16,   // 离线托管结束
    PLAYER_ACTION_KICK_OFFLIVE          = 17,   // 离线托管踢号

    PLAYER_ACTION_CHOOSE_SKILLROUTE     = 18,   // 选择技能路线
    PLAYER_ACTION_SKILL_LEVELUP         = 19,   // 技能升级
    PLAYER_ACTION_RESET_SKILL           = 20,   // 洗点

    PLAYER_ACTION_TRADE                 = 21,   // 交易

    PLAYER_ACTION_MARRY                 = 22,   // 结婚
    PLAYER_ACTION_UNMARRY               = 23,   // 离婚

    PLAYER_ACTION_JOIN_ACTIVITY         = 24,   // 参加活动
    PLAYER_ACTION_LEAVE_ACTIVITY        = 25,   // 结束活动

    PLAYER_ACTION_DELETE_ROLE           = 26,   // 删除角色
    PLAYER_ACTION_RESTORE_ROLE          = 27,   // 恢复角色
    PLAYER_ACTION_FREEZE_ROLE           = 28,   // 冻结角色
    PLAYER_ACTION_UNFREEZE_ROLE         = 29,   // 解除角色
    PLAYER_ACTION_RENAME_ROLE           = 30,   // 角色改名

    PLAYER_ACTION_SKILLPOINT_CHANGE     = 31,   // 技能点变化
    PLAYER_ACTION_PROPPOINT_CHANGE      = 32,   // 潜能点变化
    PLAYER_ACTION_GATHERPOINT_CHANGE    = 33,   // 活力值变化
    PLAYER_ACTION_MAKEPOINT_CHANGE      = 34,   // 精力值变化
    
    PLAYER_ACTION_TYPE_COUNT // must be the last one
};

struct KGPlayerActionLog : public tagProtocolHeader2
{
    unsigned            uActionLevel;   // 行为重要程度
    PLAYER_ACTION_TYPE  eActionType;
    char                szActionTarget[_NAME_LEN];  // 行为目标，如某个任务名，活动名等
    char                szAccountName[_NAME_LEN];
    char                szRoleName[_NAME_LEN]; 
    unsigned            uCommentSize;    // include string's terminal '\0', max size is LOG_COMMENT_MAX_SIZE, set to 0 for none comment
    unsigned char       pbyData[1]; // following data size is uCommentSize
};

#pragma	pack(pop)

#endif //_INCLUDE_KG_LOGSERVERPROTOCAL_H_
