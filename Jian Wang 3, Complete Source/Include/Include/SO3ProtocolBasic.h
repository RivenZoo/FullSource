/************************************************************************/
/* 剑三协议基础结构定义						                            */
/* Copyright : Kingsoft 2005										    */
/* Author	 : Zhu Jianqiu												*/
/* History	 :															*/
/*		2005.11.30	Create												*/
/************************************************************************/
#ifndef _SO3_PROTOCOL_BASIC_
#define _SO3_PROTOCOL_BASIC_

#include "ProtocolBasic.h"
#include "SO3GlobalDef.h"

#define UNUSED_PROTOCOL_ID			-1
#define UNDEFINED_PROTOCOL_SIZE		-1

#pragma	pack(1)

/************************************************************************/
/* 常用协议中常用的共用结构												*/

#define QUEST_PARAM_COUNT		4		//任务参数个数

// 道具结构
enum ITEM_SYNC_STRUCT_TYPE
{
	isst_Common = 0,
	isst_CustomEquip,
	isst_Equip,
	isst_Train,
	isst_Total,
};

// 战场信息类型

enum BATTLE_FIELD_NOTIFY_TYPE
{
    bfntInvalid = 0,
    bfntQueueInfo,
    bfntJoinBattleField,
    bfntLeaveBattleField,
    bfntInBlackList,
    bfntLeaveBlackList,
    bfntTotle
};

/************************************************************************/
/* 外网基础协议头定义						                            */

struct EXTERNAL_PROTOCOL_HEADER
{
	BYTE	byProtocolID;			//协议号
};

struct UPWARDS_PROTOCOL_HEADER : EXTERNAL_PROTOCOL_HEADER
{
	int		nFrame;				//当前帧数	
};

struct DOWNWARDS_PROTOCOL_HEADER : EXTERNAL_PROTOCOL_HEADER
{

};

struct UNDEFINED_SIZE_UPWARDS_HEADER : UPWARDS_PROTOCOL_HEADER
{
};

struct UNDEFINED_SIZE_DOWNWARDS_HEADER : DOWNWARDS_PROTOCOL_HEADER
{
	WORD	wSize;
};

#pragma pack()

#define REGISTER_EXTERNAL_FUNC(ProtocolID, FuncName, ProtocolSize)	\
{m_ProcessProtocolFuns[ProtocolID] = FuncName;					\
	m_nProtocolSize[ProtocolID] = ProtocolSize;}						

/************************************************************************/
/* 内网基础协议头定义						                            */
//
//1.协议号名称命名规则
//		["发送端名称缩写"2"接收端名称缩写"_]["功能模块名称缩写"_]"功能描述"
//		字母全小写
//		功能描述的英文单词之间用_分割
//		e.g.	b2r_player_login			（Bishop通知Relay玩家登陆的协议）
//				g2r_dml_apply_mapcopy		（GS向Relay申请地图副本的协议，属于动态地图功能模块）
//2.协议结构名称的命名规则
//		将协议号名称变成全大写即可
//		e.g.	B2R_PLAYER_LOGIN
//3.相关协议处理函数的命名规则
//		On"功能描述"
//		功能描述中英文单词的首字母大写
//		e.g		OnPlayerLogin


#pragma	pack(1)

typedef struct _INTERNAL_PROTOCOL_HEADER
{
	WORD	wProtocolID;			//协议号
    BYTE	bReserved;
}INTERNAL_PROTOCOL_HEADER;

typedef struct _IDENTITY_HEADER : INTERNAL_PROTOCOL_HEADER
{
	DWORD		dwPacketIdentity;		//数据包的唯一标记，供验证返回路由使用
}IDENTITY_HEADER;

#pragma pack()

#define REGISTER_INTERNAL_FUNC(ProtocolID, FuncName, ProtocolSize)	\
{m_ProcessProtocolFuns[ProtocolID] = FuncName;					\
    m_uProtocolSize[ProtocolID] = ProtocolSize;}

#endif	//_SO3_PROTOCOL_BASIC_
