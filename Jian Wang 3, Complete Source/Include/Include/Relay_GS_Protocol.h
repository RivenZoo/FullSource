/************************************************************************/
/* Relay和GS之间的协议定义					                            */
/* Copyright : Kingsoft 2004										    */
/* Author	 : Zhu Jianqiu												*/
/* History	 :															*/
/*		2004.12.09	Create												*/
/************************************************************************/
#ifndef _RELAY_GS_PROTOCOL_H_
#define _RELAY_GS_PROTOCOL_H_

#include "SO3ProtocolBasic.h"
#include "KRoleDBDataDef.h"
#include "KTongDef.h"
#include "KStatDataDef.h"
#include "KGameCardDef.h"
#include "KMailDef.h"
#include "KAuctionDef.h"
#include "KMentorDef.h"

#define PQ_PARAM_SYNC_COUNT 8
#define MAX_ROLE_DATA_PAK_SIZE  (1024 * 32)

// 上行协议定义
enum KS2R_PROTOCOL
{
    s2r_protocol_begin,

	s2r_handshake_request,
    s2r_ping_signal,
    s2r_update_performance,

	s2r_create_map_respond,

    s2r_player_login_respond,
	s2r_search_map_request,
    s2r_transfer_player_request,
    s2r_transfer_player_respond,
    s2r_confirm_player_login_request,
	s2r_player_leave_gs,

	s2r_update_fellowship,

    // ------------- 组队相关协议 --------------------------------
	s2r_invite_player_join_team_request,
	s2r_invite_player_join_team_respond,
    s2r_apply_join_team_request,
    s2r_apply_join_team_respond,
    s2r_team_del_member_request,
    s2r_team_change_authority_request,
    s2r_team_set_loot_mode_request,
	s2r_team_set_roll_quality_request,
	s2r_team_set_formation_leader_request,
    s2r_team_disband_request,
    s2r_sync_team_member_max_lmr,
    s2r_sync_team_member_current_lmr,
    s2r_sync_team_member_misc,
    s2r_sync_team_member_position,
    s2r_team_set_mark_request,
    s2r_team_level_up_raid_request,
    s2r_team_change_member_group_request,

    // ---------------- 聊天相关 --------------------------------------
    s2r_talk_message, 
    s2r_player_talk_error, 

    // ---------------- 好友相关 --------------------------------------
    s2r_apply_fellowship_data_request, 
    s2r_update_fellowship_data, 
    s2r_add_fellowship_request, 
    s2r_get_fellowship_name_request, 
    s2r_apply_fellowship_player_level_and_forceid, 
    s2r_add_fellowship_notify, 

    // ---------------- 邮件系统 --------------------------------------
    s2r_send_mail_request,
    s2r_send_global_mail_request,
    s2r_get_maillist_request,
    s2r_query_mail_content,
    s2r_acquire_mail_money_request,
    s2r_acquire_mail_item_request,
    s2r_give_mail_money_to_player,
    s2r_give_mail_item_to_player,
    s2r_set_mail_read,
    s2r_delete_mail,
    s2r_return_mail,
	s2r_sync_mid_map_mark,
    
    // ---------------- 副本相关 --------------------------------------
    s2r_save_scene_player_list,
    s2r_save_scene_data,
    s2r_reset_map_copy_request,
    s2r_player_enter_scene_notify,

    // ---------------- 交通相关 --------------------------------------
    s2r_sync_road_track_force,
    
    // ---------------- 角色操作 --------------------------------------
    s2r_load_role_data_request,

    s2r_change_role_level_request,
    s2r_change_role_forceid_request,

    s2r_send_gm_message,
    s2r_send_gm_chn,

    s2r_send_gm_command_gs,
    s2r_send_gm_command_gc,

    s2r_join_battle_field_queue_request,
    s2r_leave_battle_field_queue_request,

    s2r_accept_join_battle_field,
    s2r_get_battle_field_list,

    s2r_leave_battle_field_request,

    s2r_apply_create_pq_request, 
    s2r_apply_delete_pq_request, 
    s2r_apply_change_pq_value_request, 
    
    s2r_add_camp_score,
    s2r_apply_set_camp_request,

    s2r_sync_role_data,
    s2r_save_role_data,

    // ---------------- 帮会相关 --------------------------------------
    s2r_apply_tong_roster_request,
    s2r_apply_tong_info_request,
    s2r_apply_tong_repertory_page_request,
    s2r_apply_create_tong_request,
    s2r_invite_player_join_tong_request,
    s2r_invite_player_join_tong_respond,
    s2r_apply_kick_out_tong_member_request,
    s2r_modify_tong_info_request,
    s2r_modify_tong_schema_request,
    s2r_apply_quit_tong_request,
    s2r_change_tong_member_group_request,
    s2r_change_tong_master_request,
    s2r_change_tong_member_remark_request,
    s2r_get_tong_description_request,
    s2r_save_money_in_tong_request,
    s2r_pay_tong_salary_request,
    s2r_get_tong_salary_request,
    s2r_get_tong_salary_fail_respond,
    s2r_change_tong_camp_request,

    s2r_apply_open_tong_repertory_request,

    s2r_take_tong_repertory_item_to_pos_request,
    s2r_take_tong_repertory_item_request,
    s2r_take_tong_repertory_item_respond,

    s2r_put_tong_repertory_item_to_pos_request,
    s2r_put_tong_repertory_item_request,
    s2r_put_tong_repertory_item_respond,

    s2r_unlock_tong_repertory_grid,
    s2r_exchange_tong_repertory_item_pos_request,

    s2r_apply_stack_tong_repertory_item_request,
    s2r_stack_tong_repertory_item_request,
    // ---------------- 寄卖行相关 --------------------------------------
    s2r_auction_lookup_request,
    s2r_auction_bid_request,
    s2r_auction_sell_request,
    s2r_auction_cancel_request,

    s2r_remote_lua_call,
    
    s2r_achievement_global_announce_request,

    s2r_designation_global_announce_request,

    // ---------------- 统计数据相关 ------------------------------------
    s2r_update_stat_data_request,
    s2r_query_stat_id_request,
    s2r_map_copy_keep_player,

    s2r_change_ext_point_request,
    s2r_set_charge_flag_request,
    s2r_active_present_code_request,

    s2r_apex_protocol,
    
    s2r_report_farmer_player_request,

    s2r_game_card_sell_request,
    s2r_game_card_buy_request,
    s2r_game_card_lookup_request,
    s2r_game_card_cancel_request,

    s2r_apply_mentor_data,
    s2r_update_max_apprentice_num,
    s2r_add_mentor_value_request,

    
    s2r_protocol_end
};

// 下行协议定义
enum KR2S_PROTOCOL
{
	r2s_protocol_begin = 0,

	r2s_handshake_respond,
    r2s_quit_notify,
	r2s_create_map_notify,
    r2s_finish_create_map_notify,
	r2s_delete_map_notify,
    
    r2s_player_login_request,
	r2s_search_map_respond,
    r2s_transfer_player_request,    
    r2s_transfer_player_respond,
    r2s_confirm_player_login_respond,

	r2s_kick_account_notify,

    // ------------- 组队相关协议 --------------------------------	
	r2s_invite_player_join_team_request,
    r2s_apply_join_team_request,
    r2s_team_create_notify,
    r2s_team_add_member_notify,
    r2s_team_del_member_notify,
    r2s_team_change_authority_notify,
    r2s_team_set_loot_mode_notify,
    r2s_team_disband_notify,
    r2s_sync_team_member_online_flag,
    r2s_sync_team_member_max_lmr,
    r2s_sync_team_member_current_lmr,
    r2s_sync_team_member_misc,
    r2s_sync_team_member_position,
    r2s_party_message_notify,
    r2s_team_set_formation_leader_notify,
    r2s_team_set_mark_respond,
    r2s_team_camp_change,
    r2s_team_level_up_raid_notify,
    r2s_team_change_member_group_notify,

    // ---------------- 聊天相关 --------------------------------------
    r2s_player_talk_error,
    r2s_player_talk_whisper_success_respond, 
    r2s_talk_message,

    // ---------------- 好友相关 --------------------------------------
    r2s_apply_fellowship_data_respond,
    r2s_add_fellowship_respond, 
    r2s_get_fellowship_name_respond, 
    r2s_sync_fellowship_mapid, 
    r2s_sync_fellowship_player_level, 
    r2s_sync_fellowship_player_forceid, 
    r2s_add_fellowship_notify,

    // ---------------- 邮件系统 --------------------------------------
    r2s_send_mail_respond,
    r2s_get_maillist_respond,
    r2s_sync_mail_content,
    r2s_give_mail_money_to_player,
    r2s_give_mail_item_to_player,
    r2s_new_mail_notify,
    r2s_mail_general_respond,
    // ----------------------------------------------------------------

	r2s_sync_mid_map_mark,
    
    // ---------------- 副本相关 ---------------------------------------
    r2s_map_copy_do_clear_player_prepare,
    r2s_map_copy_do_clear_player,
    r2s_set_map_copy_owner,

    // ---------------- 交通相关 ---------------------------------------
    r2s_sync_road_track_info,
    
    // --------------------- 角色操作相关 -----------------------------
    r2s_save_role_data_respond,
    
    r2s_sync_role_data,
    r2s_load_role_data,

    r2s_gm_command,

    r2s_join_battle_field_queue_respond,
    r2s_leave_battle_field_queue_respond,

    r2s_battle_field_notify,

    r2s_sync_battle_field_list,
    r2s_accept_join_battle_field_respond,

    r2s_leave_battle_field_respond,

    r2s_sync_pq,
    r2s_delete_pq,
    r2s_pq_value_change,
    r2s_pq_finish,
    
    r2s_sync_camp_info,
    r2s_apply_set_camp_respond,

    // ---------------------   帮会相关   -----------------------------
    r2s_sync_tong_member_info,
    r2s_delete_tong_member_notify,
    r2s_apply_tong_info_respond,
    r2s_update_tong_client_data_version,

    r2s_invite_player_join_tong_request,

    r2s_change_player_tong_notify,
    r2s_tong_broadcast_message,
    r2s_get_tong_description_respond,
    r2s_sync_tong_online_message,

    r2s_apply_open_tong_repertpry_respond,
    r2s_sync_tong_repertory_page_respond,

    r2s_take_tong_repertory_item_to_pos_respond,
    r2s_take_tong_repertory_item_respond,
    r2s_put_tong_repertory_item_respond,
    r2s_apply_stack_tong_repertory_item_respond,

    r2s_get_tong_salary_respond,

    r2s_sync_tong_history_respond,
    // ---------------------   寄卖行相关   -----------------------------
    r2s_auction_lookup_respond,
    r2s_auction_bid_respond,
    r2s_auction_sell_respond,
    r2s_auction_cancel_respond,
    r2s_auction_message_notify,

    r2s_remote_lua_call,

    r2s_achievement_global_announce_respond,

    r2s_designation_global_announce_respond,

    r2s_sync_global_system_value,

    r2s_query_stat_id_respond,
    
    r2s_change_ext_point_respond,
    r2s_set_charge_flag_respond,
    r2s_sync_zone_charge_flag,
    r2s_active_present_code_respond,

    r2s_apex_protocol,

    r2s_set_farmer_limit_flag_request,

    r2s_game_card_sell_respond,
    r2s_game_card_buy_respond,
    r2s_game_card_lookup_respond,
    r2s_game_card_cancel_respond,

    r2s_sync_mentor_data,
    r2s_delete_mentor_record,
    r2s_update_mentor_record,
    r2s_seek_mentor_yell,
    r2s_seek_apprentice_yell,

	r2s_protocol_end
};



#pragma	pack(1)

// 上行协议结构定义

struct S2R_HANDSHAKE_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    int     nGameWorldLowerVersion;
    int     nGameWorldUpperVersion;
    time_t  nServerTime;
};

struct S2R_PING_SIGNAL : INTERNAL_PROTOCOL_HEADER
{
	DWORD dwReserved;
};

struct S2R_UPDATE_PERFORMANCE : INTERNAL_PROTOCOL_HEADER
{
    int     nIdleFrame;
    size_t  uMemory;
    int     nPlayerCount;
    int     nConnectionCount;
    size_t  uNetworkFlux;
};

struct S2R_CREATE_MAP_RESPOND : INTERNAL_PROTOCOL_HEADER
{
	DWORD		dwMapID;			
	int		    nMapCopyIndex;		
	BOOL		bResult;			
};

// GameServer对登录请求的应答消息 
struct S2R_PLAYER_LOGIN_RESPOND : IDENTITY_HEADER
{
	DWORD		dwPlayerID;
	BOOL		bPermit;
	GUID		Guid;
	DWORD       dwGSAddr;
	int			nGSPort;
};

struct S2R_CONFIRM_PLAYER_LOGIN_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwPlayerID;
};

struct S2R_PLAYER_LEAVE_GS : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwPlayerID;
};

struct S2R_SEARCH_MAP_REQUEST : INTERNAL_PROTOCOL_HEADER
{
	DWORD		dwPlayerID;
	DWORD		dwMapID;
    int         nMapCopyIndex;
    int         nPosX;
    int         nPosY;
    int         nPosZ;
};

// 玩家跨服务器,源服务器发出跨服请求(附带角色基本数据)
struct S2R_TRANSFER_PLAYER_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD           dwRoleID;
    BOOL            bChargeFlag;
	tagExtPointInfo	ExtPointInfo;			// 可用的附送点
    BOOL            bExtPointLock;
    int             nLastExtPointIndex;
    short           nLastExtPointValue;
    time_t          nEndTimeOfFee;
    int             nCoin;
    KRoleBaseInfo   RoleBaseInfo;
    int             nBattleFieldSide;
};

// 玩家跨服时,目标服务器的响应消息
struct S2R_TRANSFER_PLAYER_RESPOND : INTERNAL_PROTOCOL_HEADER
{
	DWORD		dwPlayerID;
	BOOL		bSucceed;
	DWORD	    dwAddress;
	WORD		wPort;
	GUID		Guid;
};

// ------------------ 组队相关协议结构定义 ---------------------------

// 从GS转发过来的玩家组队邀请
struct S2R_INVITE_PLAYER_JOIN_TEAM_REQUEST : INTERNAL_PROTOCOL_HEADER
{
	DWORD dwInviteSrc;
	char  szInviteRole[_NAME_LEN];
};

// 被邀请玩家的应答消息GS==>Relay
struct S2R_INVITE_PLAYER_JOIN_TEAM_RESPOND : INTERNAL_PROTOCOL_HEADER
{
    char  szInviteSrc[_NAME_LEN];
    DWORD dwInviteDst;
    BOOL  bAgreeFlag;
};

// 转发玩家的入队申请到Relay
struct S2R_APPLY_JOIN_TEAM_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwApplySrc; // 发出入队申请的玩家
    char  szApplyDst[_NAME_LEN]; // 申请加入这个玩家的队伍
};

// 将队长对入队申请的应答转发到Relay
struct S2R_APPLY_JOIN_TEAM_RESPOND : INTERNAL_PROTOCOL_HEADER
{
    char  szApplySrc[_NAME_LEN];
    DWORD dwApplyDst;
    BOOL  bAgreeFlag;
};

// 队伍解散请求
struct S2R_TEAM_DISBAND_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwLeaderID;
    DWORD dwTeamID;
};

// 队伍删除成员请求
struct S2R_TEAM_DEL_MEMBER_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwTeamID;
    DWORD dwRequestSrc; // 请求发起者的ID
    DWORD dwMemberID;
};

// 设置队伍队长请求
struct S2R_TEAM_CHANGE_AUTHORITY_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwTeamID;
    DWORD dwRequestSrc; // 请求发起者的ID
    BYTE  byType;
    DWORD dwTargetID;
};

// 设置队伍物品分配方式
struct S2R_TEAM_SET_LOOT_MODE_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwTeamID;
    DWORD dwRequestSrc;
    int   nLootMode;
};

struct S2R_TEAM_SET_ROLL_QUALITY_REQUEST : INTERNAL_PROTOCOL_HEADER
{
	DWORD dwTeamID;
	DWORD dwRequestSrc;
	int   nRollQuality;
};

struct S2R_TEAM_SET_FORMATION_LEADER_REQUEST : INTERNAL_PROTOCOL_HEADER
{
	DWORD dwTeamID;
	DWORD dwRequestSrc;
	DWORD dwNewFormationLeader;
    int   nGroupIndex;
};

struct S2R_SYNC_TEAM_MEMBER_MAX_LMR : INTERNAL_PROTOCOL_HEADER
{
    DWORD 	dwTeamID;
    DWORD 	dwMemberID;
    int   	nMaxLife; 
    int   	nMaxMana; 
    int     nMaxRage;
};

struct S2R_SYNC_TEAM_MEMBER_CURRENT_LMR : INTERNAL_PROTOCOL_HEADER
{
    DWORD 	dwTeamID;
    DWORD 	dwMemberID;
    BYTE   	byLifePercent; 
    BYTE   	byManaPercent; 
    BYTE   	byRagePercent; 
};

struct S2R_SYNC_TEAM_MEMBER_MISC : INTERNAL_PROTOCOL_HEADER
{
    DWORD 	dwTeamID;
    DWORD 	dwMemberID;

    // 头像相关数据
    KPORTRAIT_INFO PortraitInfo;
    
    DWORD   dwForceID;
    BYTE    byLevel;
    BYTE    byCamp;
	BYTE    byRoleType;
    bool    bDeathFlag;
};

struct S2R_SYNC_TEAM_MEMBER_POSITION : INTERNAL_PROTOCOL_HEADER
{
    DWORD 	dwTeamID;
    DWORD 	dwMemberID;
    DWORD   dwMapID;
    int     nMapCopyIndex;
    int     nPosX;
    int     nPosY;
};

struct S2R_TEAM_SET_MARK_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwTeamID;
    DWORD   dwMemberID;
    int     nMarkType;
    DWORD   dwTargetID;
};

struct S2R_TEAM_LEVEL_UP_RAID_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwTeamID;
    DWORD dwRequestSrc;
};

struct S2R_TEAM_CHANGE_MEMBER_GROUP_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwTeamID;
    DWORD dwMemberID;
    int   nDstGroupIndex;
    DWORD dwDstMemberID;
    DWORD dwRequestSrc;
};

// -------------- 聊天相关协议结构定义 ------------------------

struct S2R_TALK_MESSAGE : INTERNAL_PROTOCOL_HEADER
{
    BYTE  byMsgType;
    DWORD dwTalkerID;
    char  szTalker[_NAME_LEN];
    DWORD dwReceiverID;
    char  szReceiver[_NAME_LEN];
    BYTE  byTalkData[0];
};

struct S2R_PLAYER_TALK_ERROR : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwReceiverID;
    int   nErrorCode;
};

// -------------- 好友相关协议结构定义 -------------------------

struct S2R_APPLY_FELLOWSHIP_DATA_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
};

struct S2R_UPDATE_FELLOWSHIP_DATA : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    BYTE    byData[0];
};

struct S2R_ADD_FELLOWSHIP_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    char    szAlliedPlayerName[_NAME_LEN];
    BYTE    byType;
};

struct S2R_GET_FELLOWSHIP_NAME_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    BYTE    byCount;
    DWORD   dwAlliedPlayerIDArray[0];
};

struct S2R_APPLY_FELLOWSHIP_PLAYER_LEVEL_AND_FORCEID : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
};

struct S2R_ADD_FELLOWSHIP_NOTIFY : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    DWORD   dwAlliedPlayerID;
    char    szAlliedPlayerName[_NAME_LEN];
    int     nType;
};

// -------------- 邮件系统相关　------------------------------->

struct S2R_SEND_MAIL_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    BYTE            byRequestID;
    char            szReceiverName[ROLE_NAME_LEN];
    BYTE            byData[0];                      // KMail
};

struct S2R_SEND_GLOBAL_MAIL_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    int             nLifeTime;
    BYTE            byData[0];                      // KMail
};

struct S2R_GET_MAILLIST_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD           dwPlayerID;
    DWORD           dwStartID;
};

struct S2R_QUERY_MAIL_CONTENT : INTERNAL_PROTOCOL_HEADER
{
    DWORD           dwPlayerID;
    DWORD           dwMailID;
    BYTE            byMailType;
};

struct S2R_ACQUIRE_MAIL_MONEY_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD           dwPlayerID;
    DWORD           dwMailID;
};

struct S2R_ACQUIRE_MAIL_ITEM_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD           dwPlayerID;
    DWORD           dwMailID;
    BYTE            byIndex;
};

struct S2R_GIVE_MAIL_MONEY_TO_PLAYER_RESPOND : INTERNAL_PROTOCOL_HEADER
{
    DWORD           dwPlayerID;
    DWORD           dwMailID;
    BYTE            byResult;
};

struct S2R_GIVE_MAIL_ITEM_TO_PLAYER_RESPOND : INTERNAL_PROTOCOL_HEADER
{
    DWORD           dwPlayerID;
    DWORD           dwMailID;
    BYTE            byIndex;
    BYTE            byResult;
};

struct S2R_SET_MAIL_READ : INTERNAL_PROTOCOL_HEADER
{
    DWORD           dwPlayerID;
    DWORD           dwMailID;
};

struct S2R_DELETE_MAIL : INTERNAL_PROTOCOL_HEADER
{
    DWORD           dwPlayerID;
    DWORD           dwMailID;
};

struct S2R_RETURN_MAIL : INTERNAL_PROTOCOL_HEADER
{
    DWORD           dwPlayerID;
    DWORD           dwMailID;
};

// <------------- 邮件系统相关　--------------------------------

struct S2R_SYNC_MID_MAP_MARK : INTERNAL_PROTOCOL_HEADER
{
	DWORD   dwTeamID;
	DWORD   dwSrcPlayerID;
	int     nMapID;
	int     nX;
	int     nY;
	int     nType;
	char    szComment[MAX_MIDMAP_MARK_COMMENT_LEN];
};

// <--------------------- 副本相关 ---------------------------------------
struct S2R_SAVE_SCENE_PLAYER_LIST : INTERNAL_PROTOCOL_HEADER
{
	DWORD    dwMapID;
    int      nMapCopyIndex;
    int      nPlayerCount;
    DWORD    dwPlayerList[0];
};

struct S2R_SAVE_SCENE_DATA : INTERNAL_PROTOCOL_HEADER
{
	DWORD    dwMapID;
    int      nMapCopyIndex;
    size_t   uDataLen;
    BYTE     byData[0];
};

struct S2R_PLAYER_ENTER_SCENE_NOTIFY : INTERNAL_PROTOCOL_HEADER
{
    DWORD    dwPlayerID;
    DWORD    dwMapID;
    int      nMapCopyIndex;
};

struct S2R_LOAD_ROLE_DATA_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
};

struct S2R_CHANGE_ROLE_LEVEL_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwPlayerID;
    BYTE  byLevel;
};

struct S2R_CHANGE_ROLE_FORCEID_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwPlayerID;
    BYTE  byForceID;
};

// ---------------------- 交通相关 ------------------------------------------
struct S2R_SYNC_ROAD_TRACK_INFO : INTERNAL_PROTOCOL_HEADER
{
    int     nNodeID;
    BYTE    byCamp;
    BYTE    byEnable;
};

struct S2R_SEND_GM_MESSAGE : INTERNAL_PROTOCOL_HEADER 
{
    char    szGmName[_NAME_LEN];
    char    szMessage[0];
};

struct S2R_SEND_GM_CHN : INTERNAL_PROTOCOL_HEADER 
{
    char    szAccount[_NAME_LEN];
    char    szRole[_NAME_LEN];
    char    szMessage[0];
};

struct S2R_SEND_GM_COMMAND_GS : INTERNAL_PROTOCOL_HEADER
{
    char    szRoleName[_NAME_LEN];
    char    szCommand[0];
};

struct S2R_SEND_GM_COMMAND_GC : INTERNAL_PROTOCOL_HEADER
{
    char    szCommand[0];
};

struct S2R_JOIN_BATTLE_FIELD_QUEUE_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD       dwMapID;
    int         nCopyIndex;
    DWORD       dwGroupID;
    BOOL        bTeamJoin;
    DWORD       dwRoleID;
    DWORD       dwJoinValue;
};

struct S2R_LEAVE_BATTLE_FIELD_QUEUE_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwMapID;
    DWORD dwRoleID;
};

struct S2R_ACCEPT_JOIN_BATTLE_FIELD : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwMapID;
    int     nCopyIndex;
    DWORD   dwRoleID;
};

struct S2R_GET_BATTLE_FIELD_LIST : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwPlayerID;
    DWORD dwMapID;
};

struct S2R_LEAVE_BATTLE_FIELD_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwPlayerID;
};

struct S2R_APPLY_CREATE_PQ_REQUEST : INTERNAL_PROTOCOL_HEADER 
{
    DWORD dwPQTemplateID;
};

struct S2R_APPLY_DELETE_PQ_REQUEST : INTERNAL_PROTOCOL_HEADER 
{
    DWORD dwPQID;
};

struct S2R_APPLY_CHANGE_PQ_VALUE_REQUEST : INTERNAL_PROTOCOL_HEADER 
{
    DWORD   dwPQID;
    int     nIndex;
    int     nAddValue;
};

struct S2R_ADD_CAMP_SCORE : INTERNAL_PROTOCOL_HEADER
{
    int     nAddCampScore;
};

struct S2R_APPLY_SET_CAMP_REQUEST : INTERNAL_PROTOCOL_HEADER 
{
    DWORD dwPlayerID;
    BYTE  byNewCamp;
};

// ---------------------- 帮会相关 ------------------------------------------
struct S2R_APPLY_TONG_ROSTER_REQUEST : INTERNAL_PROTOCOL_HEADER 
{
    DWORD   dwPlayerID;
    int     nLastUpdateFrame;
    int     nMemberCount;
    DWORD   dwMemberList[0];
};

struct S2R_APPLY_TONG_INFO_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    int     nLastUpdateFrame;
};

struct S2R_APPLY_TONG_REPERTORY_PAGE_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    BYTE    byPageIndex;
    int     nLastUpdateCounter;
};

struct S2R_APPLY_CREATE_TONG_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwPlayerID;
    char  szTongName[_NAME_LEN];
    BYTE  byTemplateIndex;
};

struct S2R_INVITE_PLAYER_JOIN_TONG_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwPlayerID;
    char  szNewMemberName[_NAME_LEN];
};

struct S2R_INVITE_PLAYER_JOIN_TONG_RESPOND : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwPlayerID;
    DWORD dwInviterID;
    DWORD dwTongID;
    BYTE  byAccept;
};

struct S2R_APPLY_KICK_OUT_TONG_MEMBER : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwPlayerID;
    DWORD dwMemberID;
};

struct S2R_MODIFY_TONG_INFO_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    BYTE    byInfoType;
    WORD    wDataLen;
    BYTE    byData[0];
};

struct S2R_MODIFY_TONG_SCHEMA_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    BYTE    byGroupIndex;
    BYTE    byModifyType;
    BYTE    byData[0];
};

struct S2R_APPLY_QUIT_TONG_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
};

struct S2R_CHANGE_TONG_MEMBER_GROUP_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwPlayerID;
    DWORD dwTargetMemberID;
    BYTE  byTargetGroup;
};

struct S2R_CHANGE_TONG_MASTER_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwPlayerID;
    DWORD dwNewMasterID;
};

struct S2R_CHANGE_TONG_MEMBER_REMARK_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwPlayerID;
    DWORD dwTargetMemberID;
    char  szRemark[_NAME_LEN];
};

struct S2R_GET_TONG_DESCRIPTION_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwPlayerID;
    DWORD dwTongID;
};

struct S2R_SAVE_MONEY_IN_TONG_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    int     nMoney;
};

struct S2R_PAY_TONG_SALARY_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    int     nTotalSalary;
};

struct S2R_GET_TONG_SALARY_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
};

struct S2R_GET_TONG_SALARY_FAIL_RESPOND : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    DWORD   dwTongID;
    int     nSilver;
};

struct S2R_CHANGE_TONG_CAMP_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwPlayerID;
    BYTE  byCamp;
};

struct S2R_APPLY_OPEN_TONG_REPERTORY_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwPlayerID;
};

struct S2R_TAKE_TONG_REPERTORY_ITEM_TO_POS_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    BYTE    byPageIndex;
    BYTE    byRepertoryPos;
    BYTE    byBoxIndex;
    BYTE    byBoxPos;
    int     nLastUpdateCounter;
};

struct S2R_TAKE_TONG_REPERTORY_ITEM_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    BYTE    byPageIndex;
    BYTE    byRepertoryPos;
    int     nLastUpdateCounter;
};

struct S2R_TAKE_TONG_REPERTORY_ITEM_RESPOND : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    DWORD   dwTongID;
    BYTE    byPageIndex;
    BYTE    byRepertoryPos;
    bool    bSuccess;
};

struct S2R_PUT_TONG_REPERTORY_ITEM_TO_POS_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    DWORD   dwServerItemID;
    BYTE    byBoxIndex;
    BYTE    byBoxPos;
    BYTE    byPageIndex;
    BYTE    byPagePos;
};

struct S2R_PUT_TONG_REPERTORY_ITEM_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    DWORD   dwServerItemID;
    BYTE    byBoxIndex;
    BYTE    byBoxPos;
    BYTE    byPageIndex;
};

struct S2R_PUT_TONG_REPERTORY_ITEM_RESPOND : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    DWORD   dwTongID;
    BYTE    byPageIndex;
    BYTE    byPagePos;
    BYTE    byDataSize;
    BYTE    byData[0];
};

struct S2R_UNLOCK_TONG_REPERTORY_GRID : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwTongID;
    BYTE    byPageIndex;
    BYTE    byPagePos;
};

struct S2R_EXCHANGE_TONG_REPERTORY_ITEM_POS_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    BYTE    bySrcPageIndex;
    BYTE    byDstPageIndex;
    BYTE    bySrcPagePos;
    BYTE    byDstPagePos;
    int     nSrcUpdateCounter;
    int     nDstUpdateCounter;
};

struct S2R_APPLY_STACK_TONG_REPERTORY_ITEM_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    DWORD   dwTongID;
    BYTE    byPageIndex;
    BYTE    byPagePos;
    BYTE    byBoxIndex;
    BYTE    byBoxPos;
    DWORD   dwItemID;
    BYTE    byTabType;
    WORD    wTabIndex;
    WORD    wStackNum;
    WORD    wMaxStackNum;
    int     nLastUpdateCounter;
};

struct S2R_STACK_TONG_REPERTORY_ITEM_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    DWORD   dwTongID;
    BYTE    byPageIndex;
    BYTE    byPagePos;
    BYTE    byTabType;
    WORD    wTabIndex;
    WORD    wStackNum;
    WORD    wMaxStackNum;
    int     nLastUpdateCounter;
};
// ---------------------- 寄卖行相关 ------------------------------------------
struct S2R_AUCTION_LOOKUP_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    BYTE                    byRequestID;
    DWORD                   dwPlayerID;
    KAUCTION_LOOKUP_PARAM   Param;
};

struct S2R_AUCTION_BID_REQUEST : INTERNAL_PROTOCOL_HEADER 
{
    DWORD   dwBidderID;
    DWORD   dwSaleID;
    DWORD   dwCRC;
    int     nPrice;
};

struct S2R_AUCTION_SELL_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwSellerID;
    char    szSaleName[SALE_NAME_LEN];
    int     nAucGenre;
    int     nAucSub;
    int     nRequireLevel;
    int     nQuality;
    int     nStartPrice;
    int     nBuyItNowPrice;
    int     nCustodyCharges;
    int     nLeftTime;
    size_t  uItemDataLen;
    BYTE    byItemData[0];
};

struct S2R_AUCTION_CANCEL_REQUEST : INTERNAL_PROTOCOL_HEADER 
{
    DWORD   dwPlayerID;
    DWORD   dwSaleID;
};

struct S2R_REMOTE_LUA_CALL :  INTERNAL_PROTOCOL_HEADER
{
    char   szFunction[_NAME_LEN];
    size_t uParamLen;
    BYTE   byParam[0];
};

struct S2R_ACHIEVEMENT_ANNOUNCE_REQUEST : INTERNAL_PROTOCOL_HEADER 
{
    DWORD   dwPlayerID;
    int     nAchievementID;
};

struct S2R_CHANGE_EXT_POINT_REQUEST : INTERNAL_PROTOCOL_HEADER 
{
    DWORD   dwPlayerID;
    WORD    wExtPointIndex;
    WORD    wChangeValue;
};

struct S2R_SET_CHARGE_FLAG_REQUEST : INTERNAL_PROTOCOL_HEADER 
{
    DWORD   dwPlayerID;
    DWORD   dwLastLoginIP;
    int     nChargeFlag;
};

struct S2R_DESIGNATION_GLOBAL_ANNOUNCE_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwPlayerID;
    int   nPrefix;
    int   nPostfix;
};

struct S2R_SYNC_ROLE_DATA : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwRoleID;
    size_t  uOffset;
    BYTE    byData[0];
};

struct S2R_SAVE_ROLE_DATA : INTERNAL_PROTOCOL_HEADER
{
    DWORD           dwRoleID;
    int             nUserValue;
    KRoleBaseInfo   BaseInfo;
    size_t          uRoleDataLen;
};

struct S2R_UPDATE_STAT_DATA_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    int               	nCount;
    KSTAT_DATA_MODIFY 	Values[0];
};

struct S2R_QUERY_STAT_ID_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    char            	szName[STAT_DATA_NAME_LEN];
};

struct S2R_MAP_COPY_KEEP_PLAYER : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwMapID;
    int   nCopyIndex;
    DWORD dwPlayerID;
};

struct S2R_ACTIVE_PRESENT_CODE_REQUEST : INTERNAL_PROTOCOL_HEADER 
{
    DWORD   dwPlayerID;
    char    szPresentCode[_NAME_LEN];
    DWORD   dwActiveIP;
};

struct S2R_APEX_PROTOCOL : INTERNAL_PROTOCOL_HEADER
{
    BYTE   byIsUserData;
    DWORD  dwRoleID;
    size_t nSize;
    BYTE   byData[0];
};

struct S2R_REPORT_FARMER_PLAYER_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    time_t  nPunishTime;
};

struct S2R_GAME_CARD_SELL_REQUEST : INTERNAL_PROTOCOL_HEADER 
{
    DWORD   dwPlayerID;
    int     nCoin;
    int     nGameTime;
    BYTE    byType;
    int     nPrice;
    int     nDurationTime;
};

struct S2R_GAME_CARD_BUY_REQUEST : INTERNAL_PROTOCOL_HEADER 
{
    DWORD   dwBuyerID;
    DWORD   dwID;
    int     nBuyPrice;
};

struct S2R_GAME_CARD_LOOKUP_REQUEST : INTERNAL_PROTOCOL_HEADER 
{
    DWORD   dwPlayerID;
    BYTE    byCardType;
    int     nStartIndex;
    BYTE    byOrderType;
    BOOL    bDesc;
};

struct S2R_GAME_CARD_CANCEL_REQUEST : INTERNAL_PROTOCOL_HEADER 
{
    DWORD   dwPlayerID;
    DWORD   dwID;
};

// ---------------------- 师徒相关 --------------------------------------------
struct S2R_APPLY_MENTOR_DATA : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwMentorID;
    DWORD dwApprenticeID;
};

struct S2R_UPDATE_MAX_APPRENTICE_NUM : INTERNAL_PROTOCOL_HEADER 
{
    DWORD   dwMentorID;
    int     nMaxApprenticeNum;
};

struct S2R_ADD_MENTOR_VALUE_REQUEST : INTERNAL_PROTOCOL_HEADER 
{
    DWORD   dwMentorID;
    DWORD   dwApprenticeID;
    int     nDeltaVlue;
};
// --------------------------------------------------------------------------

// ---------------------- 下行协议结构定义 ---------------------------------------

struct R2S_HANDSHAKE_RESPOND : INTERNAL_PROTOCOL_HEADER
{
	int     nWorldIndex;
    time_t  nBaseTime;
    int     nStartFrame;
};

struct R2S_QUIT_NOTIFY : INTERNAL_PROTOCOL_HEADER
{
    int nNothing;
};

// 地图管理相关协议结构
struct R2S_CREATE_MAP_NOTIFY : INTERNAL_PROTOCOL_HEADER
{
	DWORD		dwMapID;		
	int		    nMapCopyIndex;
    size_t      uDataLen;
    BYTE        byData[0];
};

struct R2S_FINISH_CREATE_MAP_NOTIFY : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwPlayerID;
};

struct R2S_DELETE_MAP_NOTIFY : INTERNAL_PROTOCOL_HEADER
{
	DWORD		dwMapID;				
	int		    nMapCopyIndex;
};

// 玩家登录请求
struct R2S_PLAYER_LOGIN_REQUEST : IDENTITY_HEADER
{
    DWORD           dwRoleID;
    char            szRoleName[_NAME_LEN];
    char            szAccount[_NAME_LEN];
    int             nChargeFlag;            // 收费状态
	tagExtPointInfo	ExtPointInfo;			// 可用的附送点
    time_t          nEndTimeOfFee;          // 收费总截止时间
    int             nCoin;                  // 金币数
    DWORD           dwSystemTeamID;
    DWORD           dwTeamID;
    KRoleBaseInfo   BaseInfo;
    int             nBattleSide;
    DWORD           dwTongID;
    BYTE            byFarmerLimit;
};

struct R2S_CONFIRM_PLAYER_LOGIN_RESPOND : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwPlayerID;
    BOOL  bPermit;
};

struct R2S_SEARCH_MAP_RESPOND : INTERNAL_PROTOCOL_HEADER
{
	DWORD		dwPlayerID;
	int         nResultCode;
    BOOL        bSwitchServer;
	DWORD		dwMapID;
	int		    nMapCopyIndex;
    int         nPosX;
    int         nPosY;
    int         nPosZ;
    int         nBattleFieldSide;
};

// 玩家跨服务器,GameCenter转发源服务器发出的跨服请求(附带角色基本数据)
struct R2S_TRANSFER_PLAYER_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD           dwRoleID;
    char            szRoleName[_NAME_LEN];
    char            szAccount[_NAME_LEN];
    BOOL            bChargeFlag;
	tagExtPointInfo	ExtPointInfo;
    BOOL            bExtPointLock;
    int             nLastExtPointIndex;
    short           nLastExtPointValue;
    time_t          nEndTimeOfFee;
    int             nCoin;
    DWORD           dwSystemTeamID;
    DWORD           dwTeamID;
    KRoleBaseInfo   BaseInfo;
    int             nBattleFieldSide;
    DWORD           dwTongID;
    BYTE            byFarmerLimit;
};

// 玩家跨服时,GameCenter转发目标服务器的响应消息
struct R2S_TRANSFER_PLAYER_RESPOND : INTERNAL_PROTOCOL_HEADER
{
	DWORD		dwPlayerID;
	BOOL		bSucceed;
	DWORD	    dwAddress;
	WORD		wPort;
	GUID		Guid;
};

struct R2S_KICK_ACCOUNT_NOTIFY : INTERNAL_PROTOCOL_HEADER
{
	DWORD       dwPlayerID;
};

// ------------------ 组队相关协议结构定义 ---------------------------

// Relay将组队邀请转发到被邀请者所在的服务器
struct R2S_INVITE_PLAYER_JOIN_TEAM_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwInviteSrc;
	char  szInviteSrc[_NAME_LEN];
	DWORD dwInviteDst;
    BYTE  bySrcCamp;
};

// Relay对入队申请稍加处理后，转发到目标玩家所在的服务器
struct R2S_APPLY_JOIN_TEAM_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwApplyDst;
    DWORD dwApplySrc;
    char  szApplySrc[_NAME_LEN];
    BYTE  bySrcLevel;
    BYTE  bySrcCamp;
    BYTE  bySrcForceID;
    DWORD dwSrcTongID;
    DWORD dwMapID;
};

// 队伍解散消息广播
struct R2S_TEAM_DISBAND_NOTIFY : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwTeamID;
};

// 队员上下线通知
struct R2S_SYNC_TEAM_MEMBER_ONLINE_FLAG : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwTeamID;
    DWORD dwMemberID;
    BOOL  bOnlineFlag;
};

struct R2S_PARTY_MESSAGE_NOTIFY : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwPlayerID;
    int   nCode;
    BYTE  byData[0];
};

struct R2S_TEAM_SET_FORMATION_LEADER_NOTIFY : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwTeamID;
    int   nGroupIndex;
    DWORD dwNewFormationLeader;
};

struct R2S_TEAM_SET_MARK_RESPOND : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwTeamID;
    int   nMarkType;
    DWORD dwTarget;
};

struct R2S_TEAM_CAMP_CHANGE : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwTeamID;
    BYTE  byCamp;
};

struct R2S_TEAM_LEVEL_UP_RAID_NOTIFY : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwTeamID;
    int   nGroupNum;
};

struct R2S_TEAM_CHANGE_MEMBER_GROUP_NOTIFY : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwTeamID;
    DWORD dwMemberID;
    int   nOldGroupIndex;
    DWORD dwDstMemberID;
    int   nNewGroupIndex;
};

struct R2S_TEAM_CREATE_NOTIFY : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwTeamID;
    BOOL  bSystem;
    BYTE  byCamp;
    int   nLootMode;
    int   nRollQuality;
    int   nGroupNum;
    DWORD dwAuthority[tatTotal];
    DWORD dwTeamMark[PARTY_MARK_COUNT];
    BYTE  byMemberCount;
    struct KMEMBER
    {
        int     nGroupIndex;
        DWORD   dwMemberID;
        char    szMemberName[_NAME_LEN];
        BYTE    byOnLineFlag;
        BYTE    byLevel;
    } Member[0];
};

// 队伍添加成员消息广播
struct R2S_TEAM_ADD_MEMBER_NOTIFY : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwTeamID;
    int   nGroupIndex;
    DWORD dwMemberID;
    char  szMemberName[_NAME_LEN];
};

// 队伍删除成员消息广播
struct R2S_TEAM_DEL_MEMBER_NOTIFY : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwTeamID;
    int   nGroupIndex;
    DWORD dwMemberID; 
};

// 队伍队长变更通知
struct R2S_TEAM_CHANGE_AUTHORITY_NOTIFY : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwTeamID;
    BYTE  byType;
    DWORD dwNewID;
};

// 物品分配模式变更通知
struct R2S_TEAM_SET_LOOT_MODE_NOTIFY : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwTeamID;
    int   nLootMode;
	int   nRollQuality;
};

struct R2S_SYNC_TEAM_MEMBER_MAX_LMR : INTERNAL_PROTOCOL_HEADER
{
    DWORD 	dwTeamID;
    DWORD 	dwMemberID;
    int   	nMaxLife; 
    int   	nMaxMana; 
    int     nMaxRage;
};

struct R2S_SYNC_TEAM_MEMBER_CURRENT_LMR : INTERNAL_PROTOCOL_HEADER
{
    DWORD 	dwTeamID;
    DWORD 	dwMemberID;
    BYTE   	byLifePercent; 
    BYTE   	byManaPercent; 
    BYTE    byRagePercent;
};

struct R2S_SYNC_TEAM_MEMBER_MISC : INTERNAL_PROTOCOL_HEADER
{
    DWORD 	dwTeamID;
    DWORD 	dwMemberID;
    
    // 头像相关数据
    KPORTRAIT_INFO PortraitInfo;

    DWORD   dwForceID;
    BYTE    byCamp;
    BYTE    byLevel;
	BYTE    byRoleType;
    bool    bDeathFlag;
};

struct R2S_SYNC_TEAM_MEMBER_POSITION : INTERNAL_PROTOCOL_HEADER
{
    DWORD 	dwTeamID;
    DWORD 	dwMemberID;
    DWORD   dwMapID;
    int     nMapCopyIndex;
    int     nPosX;
    int     nPosY;
};

// -------------- 聊天相关协议结构定义 ------------------------
struct R2S_PLAYER_TALK_ERROR : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwReceiverID;
    int   nErrorCode;
};

struct R2S_PLAYER_TALK_WHISPER_SUCCESS_RESPOND : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwTalkerID;
    DWORD dwReceiverID;
};

struct R2S_TALK_MESSAGE : INTERNAL_PROTOCOL_HEADER
{
    BYTE  byMsgType;
    DWORD dwTalkerID;
    char  szTalker[_NAME_LEN];
    DWORD dwReceiverID;
    char  szReceiver[_NAME_LEN];
    BYTE  byTalkData[0];
};

// -------------- 好友相关协议结构定义 -------------------------

struct R2S_APPLY_FELLOWSHIP_DATA_RESPOND : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    BYTE    byData[0];
};

struct R2S_ADD_FELLOWSHIP_RESPOND : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    DWORD   dwAlliedPlayerID;
    char    szAlliedPlayerName[_NAME_LEN];
    BYTE    byType; // 1: Friend, 2: Foe, 3: BlackList
};

struct R2S_GET_FELLOWSHIP_NAME_RESPOND : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    BYTE    byCount;
    struct _AlliedPlayer 
    {
        DWORD   dwID;
        DWORD   dwMapID;
        char    szName[_NAME_LEN];
    } AlliedPlayerInfo[0];
};

struct R2S_SYNC_FELLOWSHIP_MAPID : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    DWORD   dwMapID;
};

struct R2S_SYNC_FELLOWSHIP_PLAYER_LEVEL : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    BYTE    byLevel;
    BYTE    bNotifyClient;
};

struct R2S_SYNC_FELLOWSHIP_PLAYER_FORCEID : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    BYTE    byForceID;
};

struct R2S_ADD_FELLOWSHIP_NOTIFY : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    DWORD   dwAlliedPlayerID;
    char    szAlliedPlayerName[_NAME_LEN];
    int     nType;
};

// -------------- 邮件系统相关　------------------------------->
struct R2S_SYNC_MAIL_COUNT_INFO : INTERNAL_PROTOCOL_HEADER
{
    DWORD               dwPlayerID;
    int                 nReadCount;
    int                 nTotalCount;
};

struct R2S_SEND_MAIL_RESPOND : INTERNAL_PROTOCOL_HEADER
{
    BYTE                byRespondID;
    DWORD               dwSrcID;
    BYTE                byResult;
    char                szReceiver[ROLE_NAME_LEN];
    BYTE                byData[0];        // KMail
};

struct R2S_GET_MAILLIST_RESPOND : INTERNAL_PROTOCOL_HEADER
{
    DWORD               dwPlayerID;
    int                 nMailCount;
    KMailListInfo       MailList[0];
};

struct R2S_SYNC_MAIL_CONTENT : INTERNAL_PROTOCOL_HEADER
{
    DWORD               dwPlayerID;
    DWORD               dwMailID;
    BYTE                byResult;
    BYTE                byData[0];
};

struct R2S_GIVE_MAIL_MONEY_TO_PLAYER : INTERNAL_PROTOCOL_HEADER
{
    DWORD               dwPlayerID;
    DWORD               dwMailID;
    BYTE                byMailType;
    int                 nMoney;
    char                szSender[ROLE_NAME_LEN];
};

struct R2S_GIVE_MAIL_ITEM_TO_PLAYER : INTERNAL_PROTOCOL_HEADER
{
    DWORD               dwPlayerID;
    DWORD               dwMailID;
    BYTE                byMailType;
    BYTE                byResult;
    BYTE                byItemIndex;
    int                 nItemPrice;
    BYTE                byItemLen;
    char                szSender[ROLE_NAME_LEN];
    BYTE                byData[0];
};

struct R2S_NEW_MAIL_NOTIFY : INTERNAL_PROTOCOL_HEADER
{
    DWORD               dwPlayerID;
    KMailListInfo       NewMailListInfo;
};

struct R2S_MAIL_GENERAL_RESPOND : INTERNAL_PROTOCOL_HEADER
{
    DWORD               dwPlayerID;
    DWORD               dwMailID;
    BYTE                byRespond;
};

// <------------- 邮件系统相关　--------------------------------

struct R2S_SYNC_MID_MAP_MARK : INTERNAL_PROTOCOL_HEADER
{
	DWORD dwTeamID;
	DWORD dwSrcPlayerID;
	int nMapID;
	int nX;
	int nY;
	int nType;
	char szComment[MAX_MIDMAP_MARK_COMMENT_LEN];
};

// <--------------------- 副本相关 ---------------------------------------
struct R2S_MAP_COPY_DO_CLEAR_PLAYER_PREPARE : INTERNAL_PROTOCOL_HEADER
{
    DWORD    dwMapID;
    int      nMapCopyIndex;
    int      nType;
    int      nDelayTime;
};

struct R2S_MAP_COPY_DO_CLEAR_PLAYER : INTERNAL_PROTOCOL_HEADER
{
    DWORD    dwMapID;
    int      nMapCopyIndex;
};

struct R2S_SET_MAP_COPY_OWNER : INTERNAL_PROTOCOL_HEADER
{
    DWORD    dwMapID;
    int      nMapCopyIndex;
    DWORD    dwOwnerID;
};

// ---------------------- 交通相关 ------------------------------------

struct R2S_SYNC_ROAD_TRACK_INFO : INTERNAL_PROTOCOL_HEADER
{
    int     nNodeID;
    BYTE    byCamp;
    BYTE    byEnable;
};

// --------------------- 角色操作相关 -----------------------------

struct R2S_SAVE_ROLE_DATA_RESPOND : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwPlayerID;
    BOOL  bSucceed;
    int   nUserValue;
};

struct R2S_GM_COMMAND : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    char    szGmName[_NAME_LEN];
    char	szGmCommand[0];
};

// --------------------- 战场排队相关 -------------------------------

struct R2S_JOIN_BATTLE_FIELD_QUEUE_RESPOND : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    DWORD   dwMapID;
    int     nErrorCode;
};

struct R2S_LEAVE_BATTLE_FIELD_QUEUE_RESPOND : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    DWORD   dwMapID;
    int     nErrorCode;
};

struct R2S_BATTLE_FIELD_NOTIFY : INTERNAL_PROTOCOL_HEADER
{
    DWORD                       dwPlayerID;
    time_t                      nAvgQueueTime;
    int                         nPassTime;
    DWORD                       dwMapID;
    int                         nCopyIndex;
    BATTLE_FIELD_NOTIFY_TYPE    eType;
};

struct R2S_SYNC_BATTLE_FIELD_LIST : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    DWORD   dwMapID;
    int     nCopyIndex;
};

struct R2S_ACCEPT_JOIN_BATTLE_FIELD_RESPOND : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    DWORD   dwEnterMapID;
    int     nEnterCopyIndex;
    int     nEnterX;
    int     nEnterY;
    int     nEnterZ;
    DWORD   dwLeaveMapID;
    int     nLeaveCopyIndex;
    int     nLeaveX;
    int     nLeaveY;
    int     nLeaveZ;
};

struct R2S_LEAVE_BATTLE_FIELD_RESPOND : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwPlayerID;
};

// ---------------------   帮会相关   -------------------------------

struct R2S_SYNC_TONG_MEMBER_INFO : INTERNAL_PROTOCOL_HEADER
{
    DWORD           dwPlayerID;
    KTongMemberInfo MemberInfo;
};

struct R2S_DELETE_TONG_MEMBER_NOTIFY : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    DWORD   dwMemberID;
};

struct R2S_APPLY_TONG_INFO_RESPOND : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    BYTE    byInfoType;
    BYTE    byData[0];
};

struct R2S_UPDATE_TONG_CLIENT_DATA_VERSION : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    BYTE    byFrameType;
    int     nUpdateFrame;
};

struct R2S_INVITE_PLAYER_JOIN_TONG_REQUEST: INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    DWORD   dwInviterID;
    DWORD   dwTongID;
    char    szInviterName[_NAME_LEN];
    char    szTongName[_NAME_LEN];
};

struct R2S_CHANGE_PLAYER_TONG_NOTIFY : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    DWORD   dwTongID;
    BYTE    byReason;
    char    szTongName[_NAME_LEN];
};

struct R2S_TONG_BROADCAST_MESSAGE : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    BYTE    byCode;
    BYTE    byData[0];
};

struct R2S_GET_TONG_DESCRIPTION_RESPOND : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    DWORD   dwTongID;
    char    szTongName[_NAME_LEN];
};

struct R2S_SYNC_TONG_ONLINE_MESSAGE : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwPlayerID;
    BYTE  byDataLen;
    char  szOnlineMessage[0];
};

struct R2S_SYNC_TONG_REPERTORY_PAGE_RESPOND: INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    BYTE    byPageIndex;
    int     nServerCounter;
    BYTE    byGetRight;
    BYTE    byPutRight;
    BYTE    byUpdateItemCount;
    BYTE    byInvailedItemCount;
    BYTE    byData[0];
};

struct R2S_TAKE_TONG_REPERTORY_ITEM_TO_POS_RESPOND : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    DWORD   dwTongID;
    BYTE    byPageIndex;
    BYTE    byRepertoryPos;
    BYTE    byBoxIndex;
    BYTE    byBoxPos;
    BYTE    bySize;
    BYTE    byData[0];
};

struct R2S_TAKE_TONG_REPERTORY_ITEM_RESPOND : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    DWORD   dwTongID;
    BYTE    byPageIndex;
    BYTE    byRepertoryPos;
    BYTE    bySize;
    BYTE    byData[0];
};

struct R2S_PUT_TONG_REPERTORY_ITEM_RESPOND : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    DWORD   dwTongID;
    DWORD   dwServerItemID;  // server上的道具ID 用来在异步过程中验证是否是同一道具
    BYTE    byBoxIndex;
    BYTE    byBoxPos;
    BYTE    byPageIndex;
    BYTE    byPagePos;
};

struct R2S_APPLY_STACK_TONG_REPERTORY_ITEM_RESPOND : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    DWORD   dwTongID;
    BYTE    byPageIndex;
    BYTE    byPagePos;
    BYTE    byBoxIndex;
    BYTE    byBoxPos;
    DWORD   dwItemID;
    WORD    wStackNum;
};

struct R2S_APPLY_OPEN_TONG_REPERTPRY_RESPOND : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    char    szTongName[_NAME_LEN];
    BYTE    byRepertoryPageNum;
};

struct R2S_GET_TONG_SALARY_RESPOND : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    DWORD   dwTongID;
    int     nSilver;
};

struct R2S_SYNC_TONG_HISTORY_RESPOND : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    BYTE    byType;
    DWORD   dwStartIndex;
    BYTE    byCount;
    BYTE    byData[0];
};

// ---------------------   寄卖行相关   -------------------------------

struct R2S_AUCTION_LOOKUP_RESPOND : INTERNAL_PROTOCOL_HEADER
{
    BYTE                byRespondID;
    DWORD               dwPlayerID;
    BYTE                byCode;
    KAUCTION_PAGE_HEAD  Page;
};

struct R2S_AUCTION_BID_RESPOND : INTERNAL_PROTOCOL_HEADER 
{
    DWORD   dwPlayerID;
    BYTE    byCode;
    int     nBidPrice;
};

struct R2S_AUCTION_SELL_RESPOND : INTERNAL_PROTOCOL_HEADER 
{
    DWORD   dwPlayerID;
    BYTE    byCode;
    int     nStartPrice;
    int     nBuyItNowPrice;
    int     nCustodyCharges;
    size_t  uItemDataLen;
    BYTE    byItemData[0];
};

struct R2S_AUCTION_CANCEL_RESPOND : INTERNAL_PROTOCOL_HEADER 
{
    DWORD   dwPlayerID;
    BYTE    byCode;
};

struct R2S_AUCTION_MESSAGE_NOTIFY : INTERNAL_PROTOCOL_HEADER 
{
    DWORD   dwPlayerID;
    BYTE    byCode;
    char    szSaleName[SALE_NAME_LEN];
    int     nPrice;
};

// ------------------------------------------------------------------
struct R2S_SYNC_PQ : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPQID;
    DWORD   dwPQTemplateID;
    time_t  nBeginTime;
    int     nPQValue[PQ_PARAM_SYNC_COUNT];
    BYTE    bFinished;
    BYTE    byOnwerType;
    DWORD   dwOnwerID1;
    DWORD   dwOnwerID2;
    DWORD   dwOnwerID3;
};

struct R2S_DELETE_PQ : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPQID;
};

struct R2S_PQ_VALUE_CHANGE : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPQID;
    int     nIndex;
    int     nValue;
};

struct R2S_PQ_FINISH : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwPQID;
};

struct R2S_SYNC_CAMP_INFO : INTERNAL_PROTOCOL_HEADER
{
    int     nCampLevel;
    int     nCampScore;
    int     nActivePlayerCount[cTotal];
};

struct R2S_APPLY_SET_CAMP_RESPOND : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwPlayerID;
    BYTE  byCamp;
    BYTE  byResult;
};

struct R2S_REMOTE_LUA_CALL :  INTERNAL_PROTOCOL_HEADER
{
    char   szFunction[_NAME_LEN];
    size_t uParamLen;
    BYTE   byParam[0];
};

struct R2S_ACHIEVEMENT_GLOBAL_ANNOUNCE_RESPOND : INTERNAL_PROTOCOL_HEADER 
{
    char    szRoleName[ROLE_NAME_LEN];
    int     nAchievementID;
};

struct R2S_DESIGNATION_GLOBAL_ANNOUNCE_RESPOND : INTERNAL_PROTOCOL_HEADER
{
    char    szRoleName[ROLE_NAME_LEN];
    int     nPrefix;
    int     nPostfix;
};

struct R2S_SYNC_GLOBAL_SYSTEM_VALUE : INTERNAL_PROTOCOL_HEADER 
{
    int     nGameWorldStartTime;
    int     nMaxPlayerLevel;
    int     nGameWorldChargeTime;
};

struct R2S_SYNC_ROLE_DATA : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwRoleID;
    size_t  uOffset;
    BYTE    byData[0];
};

struct R2S_LOAD_ROLE_DATA : INTERNAL_PROTOCOL_HEADER
{
    DWORD   dwRoleID;
    BOOL    bSucceed;
    size_t  uRoleDataLen;
    BYTE    byRoleData[0];
};

struct R2S_QUERY_STAT_ID_RESPOND : INTERNAL_PROTOCOL_HEADER
{
    char    szName[STAT_DATA_NAME_LEN];
    int     nID;
};

struct R2S_CHANGE_EXT_POINT_RESPOND : INTERNAL_PROTOCOL_HEADER 
{
    DWORD   dwPlayerID;
    BOOL    bSucceed;
};

struct R2S_SET_CHARGE_FLAG_RESPOND : INTERNAL_PROTOCOL_HEADER
{
    DWORD           dwPlayerID;
    int             nChargeFlag;
    tagExtPointInfo ExtPointInfo;
    DWORD           dwEndTimeOfFee;
};

struct R2S_SYNC_ZONE_CHARGE_FLAG : INTERNAL_PROTOCOL_HEADER 
{
    int     nZoneChargeFlag;
};

struct R2S_ACTIVE_PRESENT_CODE_RESPOND : INTERNAL_PROTOCOL_HEADER 
{
    DWORD   dwPlayerID;
    BOOL    bSucceed;
    char    szPresentCode[_NAME_LEN];
    DWORD   dwPresentType;
};

struct R2S_APEX_PROTOCOL : INTERNAL_PROTOCOL_HEADER 
{
    DWORD   dwRoleID;
    size_t  nSize;
    BYTE    byData[0];
};

struct R2S_SET_FARMER_LIMIT_FLAG_REQUEST : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwRoleID;
    BOOL  bLimit;
};

struct R2S_GAME_CARD_SELL_RESPOND : INTERNAL_PROTOCOL_HEADER 
{
    DWORD   dwPlayerID;
    BYTE    byCode;
    int     nCoin;
};

struct R2S_GAME_CARD_BUY_RESPOND : INTERNAL_PROTOCOL_HEADER 
{
    DWORD   dwPlayerID;
    BYTE    byCode;
    int     nBuyPrice;
};

struct R2S_GAME_CARD_LOOKUP_RESPOND : INTERNAL_PROTOCOL_HEADER 
{
    DWORD       dwPlayerID;
    int         nTotalCount;
    int         nCount;
    KGAME_CARD  CardList[0];
};

struct R2S_GAME_CARD_CANCEL_RESPOND : INTERNAL_PROTOCOL_HEADER 
{
    DWORD   dwPlayerID;
    BYTE    byCode;
};

struct R2S_SYNC_MENTOR_DATA : INTERNAL_PROTOCOL_HEADER 
{
    int             nRecordCount;
    KMentorSyncInfo Data[0];
};

struct R2S_DELETE_MENTOR_RECORD : INTERNAL_PROTOCOL_HEADER 
{
    uint64_t uMKey;
};

struct R2S_UPDATE_MENTOR_RECORD : INTERNAL_PROTOCOL_HEADER
{
    DWORD dwMentor;
    DWORD dwApprentice;
    int   nValue;
    BYTE  byState;
};

struct R2S_SEEK_MENTOR_YELL : INTERNAL_PROTOCOL_HEADER
{
    char szRoleName[_NAME_LEN];
    char szTongName[_NAME_LEN];
    BYTE byForceID;
    BYTE byRoleLevel;
    BYTE byRoleType;
};

struct R2S_SEEK_APPRENTICE_YELL : INTERNAL_PROTOCOL_HEADER
{
    char szRoleName[_NAME_LEN];
    char szTongName[_NAME_LEN];
    BYTE byForceID;
    BYTE byRoleLevel;
    BYTE byRoleType;
};
#pragma pack()

#endif	//_RELAY_GS_PROTOCOL_H
