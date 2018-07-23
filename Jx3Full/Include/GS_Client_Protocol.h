/************************************************************************/
/* GS和客户端之间协议定义					                            */
/* Copyright : Kingsoft 2005										    */
/* Author	 : Zhu Jianqiu												*/
/* Modify	 : Spe														*/
/* Remark	 : 不要随意修改分隔区块的注释，在自动生成代码的宏中需要使用 */
/* History	 :															*/
/*		2005.01.27	Create												*/
/************************************************************************/
#ifndef _GS_CLIENT_PROTOCOL_H_
#define _GS_CLIENT_PROTOCOL_H_

#include "Global.h"
#include "SO3ProtocolBasic.h"
#include "SO3GlobalDef.h"
#include "KTongDef.h"
#include "KGameCardDef.h"
#include "KMailDef.h"
#include "KAuctionDef.h"
#include "KMentorDef.h"

#define  GAME_WORLD_CURRENT_VERSION 138
#define  GAME_WORLD_LOWEST_VERSION  138

enum GS_CLIENT_PROTOCOL
{
    gs_client_connection_begin = 0,

    s2c_message_notify,			    // 通知消息
    s2c_frame_signal,				// 帧同步
    s2c_ping_signal,                // 下行ping信号

    // 登陆＆跨服＆踢号的相关协议
    s2c_sync_player_base_info,	    // 登录时同步玩家数据
    s2c_sync_quest_data,            // 登陆时同步任务

    s2c_account_kickout,            // 踢号通知
    s2c_switch_gs,			        // 跨服通知
    s2c_switch_map,                 // 换地图通知

    s2c_sync_new_player,	        // 通知客户端: 一个玩家进入Region了
    s2c_sync_new_npc,	            // 通知客户端: 一个npc进入Region了
    s2c_sync_new_doodad,            // 通知客户端: 一个新的Doodad进入Region

    s2c_move_character,				// 移动角色的位置
    s2c_remove_character,			// 从场景中移除角色
    s2c_remove_doodad,

    s2c_sync_doodad_state,			// Doodad状态同步

    s2c_player_display_data,		// 玩家显示数据

    s2c_sync_experience,            // 经验值同步
    s2c_player_level_up,            // 玩家升级时的广播消息
    s2c_common_health,              // 普通伤害或者增益,比如摔伤之类的

    // 角色移动同步
    s2c_sync_move_ctrl,
    s2c_sync_move_param,            // 参数同步,校正客户端玩家的移动参数,广播
    s2c_adjust_player_move,         // 同步校正,校正客户端玩家的移动状态与参数,仅客户端玩家
    s2c_sync_move_state,            // 客户端发出移动指令的时候,如果服务端发现坐标不对,则通知客户端修正
    s2c_character_action,			// 角色交互动作的同步数据包
    s2c_character_death,			// 角色死亡的同步数据包
    s2c_over_time_action,
    
    // ------------- skill about protocol -------------------
    s2c_sync_skill_data,			//登录或者学习新技能时同步技能数据
    s2c_sync_skill_recipe,
    s2c_skill_prepare,
    s2c_skill_cast,
    s2c_sync_common_skill_auto_cast_state, // 新手技能自动释放状态
    s2c_reset_cooldown,
    s2c_skill_chain_effect,
    s2c_skill_effect_result,
    s2c_sync_behit_represent,
    s2c_sync_buff_list,		
    s2c_sync_buff_single,		
    s2c_sync_represent_state,
    s2c_sync_kungfu_mount,
    s2c_skill_beat_back,
    s2c_sync_sheath_state,

    // ------------- 数值同步 -----------------------------

    s2c_sync_self_max_lmrs,
    s2c_sync_self_current_lmrs,
    s2c_sync_self_weak_info,
    s2c_sync_select_character_max_lmr,
    s2c_sync_select_character_current_lmr,
    s2c_sync_select_character_weak_info,
    s2c_sync_team_member_max_lmr,
    s2c_sync_team_member_current_lmr,
    s2c_sync_team_member_misc,
    s2c_sync_team_member_position,
    s2c_broadcast_character_life,

    // ------------- party about protocol -----------------
    s2c_sync_player_team_base_info,
    s2c_invite_join_team_request,     
    s2c_apply_join_team_request,
    s2c_team_add_member_notify,        // 通知队伍所有成员"某人加入了我们的队伍"
    s2c_team_del_member_notify,
    s2c_team_change_authority_notify,
    s2c_team_set_loot_mode_notify,
    s2c_team_set_formation_leader_notify,
    s2c_team_disband_notify,
    s2c_sync_team_member_online_flag,
    s2c_team_member_signpost_notify,   // 通知队友小地图上的标记
    s2c_team_set_mark_respond,
    s2c_team_camp_change,
    s2c_team_level_up_raid_notify,
    s2c_team_change_member_group_notify,

    // ------------- shop about protocol ------------->
    s2c_open_shop_notify,
    s2c_update_shop_item,
    
    // -------------- Trading about ------------------>
    s2c_trading_invite_request,
    s2c_open_trading_box_notify,
    s2c_sync_trading_confirm,
    s2c_sync_trading_item_data,    
    s2c_sync_trading_money,
    s2c_trading_complete,
    // <------------- Trading about ------------------

    s2c_sync_money,					//同步金钱数量
    s2c_sync_contribution,          //同步贡献值
    s2c_sync_item_data,				//同步道具数据
    s2c_sync_item_destroy,			//同步道具删除
    s2c_exchange_item,				//交换装备
    s2c_update_item_amount,			//更新物品数量或耐久
    s2c_sync_equip_represent,       //换装广播
	s2c_add_item_notify,

    s2c_learn_profession_notify,	//学习生活技能
	s2c_learn_branch_notify,		//学习生活技能分支
    s2c_forget_profession_notify,		//遗忘技能

    s2c_add_profession_proficiency,		//增加生活技能经验
    s2c_set_max_profession_level_notify,//设置生活技能最大等级
    s2c_sync_profession_adjust_level,   // 同步生活技能因其他因素改变的调整等级
    s2c_update_player_profession,		//同步更新玩家生活技能

	s2c_learn_recipe_notify,
	s2c_forget_recipe_notify,
	s2c_sync_recipe_state,

    s2c_open_window,				// 打开一个客户端窗口

    s2c_start_use_recipe,			// 同步配方的使用

    s2c_accept_quest,				// 通知客户端接受任务
    s2c_finish_quest,				// 通知客户端完成任务
    s2c_cancel_quest,				// 通知客户端取消任务
    s2c_clear_quest,                // 通知客户端清除任务状态
    s2c_share_quest,				// 共享任务
    s2c_sync_quest_value,			// 同步任务变量
	s2c_start_escort_quest,

    s2c_sync_loot_list,				// 同步拾取列表
    s2c_roll_item_message,			// 掷骰子信息
    s2c_open_loot_list,				// 打开拾取面板
	s2c_sync_fight_flag,			// 同步战斗开关
	s2c_sync_repute,				// 同步声望
	s2c_sync_fightflag_list,		// 同步所有势力战斗开关
	s2c_sync_repute_list,			// 同步所有的势力声望
	s2c_show_reputation,			
	s2c_sync_repute_update,
	s2c_character_open,				
    s2c_distribute_item_message,    // 分配者分配物品
	s2c_finish_loot,				// 结束拾取
	s2c_begin_roll_item,			// start roll
	s2c_custom_OTAction,			// 同步定制的用户消息

	s2c_modify_threat,				// 添加仇恨
	s2c_modify_threaten,			// 修改被仇恨
	s2c_clear_threat,				// 清除仇恨
	s2c_clear_threaten,				// 清除被仇恨
    s2c_talk_message,               //
	s2c_sync_self_current_st,	    // 同步精力
    
	s2c_doodad_loot_over,			//

    s2c_sync_fellowship_list, 
    s2c_sync_fellowship_group_name, 

	s2c_npc_talk_to_player,			//
	s2c_set_force,
    s2c_send_mail_respond,
    s2c_sync_mail_count_info,
    s2c_get_maillist_respond,
    s2c_new_mail_notify,
    s2c_sync_mail_content,
    s2c_mail_general_respond,
    
	s2c_sync_pk_state,

	s2c_win_duel_broadcast,
	
    s2c_sync_force_id,			
	s2c_sync_user_preferences,	
	s2c_sync_all_book_state,	
	s2c_sync_book_state,		
	s2c_character_change_model,	
	s2c_sync_npc_dialog_flag,	
	s2c_sync_role_data_over,
	s2c_sync_enable_bank_package,
	s2c_update_map_mark,			//地图标记
	s2c_sync_mid_map_mark,
	s2c_play_sound,
	s2c_play_mini_game,

    s2c_sync_horse_flag,            // 同步骑马标志
    s2c_road_track_force_respond,
    s2c_sync_route_node_open_list,
    s2c_sync_player_state_info,
    s2c_sync_player_train,
    s2c_broadcast_player_school_id,
    
    s2c_sync_prink_force,

    s2c_sync_visit_map_info,

    s2c_sync_accumulate_value,

    s2c_set_target,

    s2c_sync_kill_point,
    s2c_set_player_red_name,
    s2c_set_player_dialog_flag,
    s2c_set_only_revive_in_situ,

    s2c_sync_formation_coefficient,

    s2c_join_battle_field_queue_respond,
    s2c_leave_battle_field_queue_respond,
    s2c_battle_field_notify,
    s2c_sync_battle_field_list,
    s2c_sync_battle_field_side,
    s2c_battle_field_end,

    s2c_sync_camp_info,
    s2c_sync_current_prestige,

    // -------------- 帮会相关 ------------------>
    s2c_sync_tong_member_info,
    s2c_delete_tong_member_notify,
    s2c_apply_tong_info_respond,
    s2c_update_tong_client_data_version,
    
    s2c_sync_tong_repertory_page_respond,

    s2c_invite_player_join_tong_request,
    s2c_change_player_tong_notify,
    s2c_tong_broadcast_message,
    s2c_get_tong_description_respond,
    s2c_broadcast_player_change_tong,
    s2c_sync_tong_online_message,
    s2c_apply_open_tong_repertory_respond,
    s2c_sync_tong_history_respond,

    // -------------- 寄卖行相关 ------------------>
    s2c_auction_lookup_respond,
    s2c_auction_bid_respond,
    s2c_auction_sell_respond,
    s2c_auction_cancel_respond,
    s2c_auction_message_notify,
    
    s2c_set_camp,

    s2c_sync_battlefield_statistics, 
    s2c_sync_battlefield_objective, 
    s2c_sync_battlefield_pq_info, 

    s2c_sync_hero_flag,

    s2c_sync_npc_drop_target,

    s2c_remote_lua_call,

    s2c_sync_player_revive_ctrl, 

    // ------------ Achievement about -------------->
    s2c_sync_achievement_data,
    s2c_new_achievement_notify,
    s2c_achievement_announce_notify,
    s2c_sync_achievement_point,
    s2c_sync_achievement_count,

    s2c_sync_designation_data,
    s2c_set_generation,
    s2c_acquire_designation,
    s2c_designation_announce,
    s2c_remove_designation,
    s2c_sync_player_designation,

    s2c_sync_max_level,

    s2c_use_item_prepare,

    // ------------ ViewPoint ---------------------->
    s2c_create_view_point_respond,
    s2c_remove_view_point_respond,
    s2c_move_view_point_respond,

    s2c_account_end_of_day_time,
    s2c_sync_free_limit_flag_info,

    s2c_apex_protocol,

    s2c_game_card_sell_respond,
    s2c_game_card_buy_respond,
    s2c_game_card_lookup_respond,
    s2c_game_card_cancel_respond,

    s2c_sync_coin,

    s2c_seek_mentor_yell,
    s2c_seek_apprentice_yell,
    s2c_sync_mentor_data,
    s2c_delete_mentor_data,

    s2c_sync_camp_flag,

    s2c_character_threat_ranklist_respond, 

	gs_client_connection_end
};
//GS 2 Client Protocol End

// Client 2 GS Protocol Begin
enum CLIENT_GS_PROTOCOL
{
    client_gs_connection_begin = 0,

    c2s_handshake_request,			// 登录时请求玩家数据
    c2s_apply_enter_scene,			// 客户端加载资源完毕,请求进入场景
    c2s_player_logout,				// 玩家登出
    c2s_ping_signal,                // 上行ping信号

    c2s_move_ctrl,
    c2s_apply_move_adjust,
    c2s_character_stand,            // 角色站立的上传指令
    c2s_character_jump,				// 角色跳跃的上传指令
    c2s_character_sit,				// 角色坐下的上传指令
    c2s_sync_direction,             // 朝向/俯仰同步

    c2s_character_action,			// 角色交互动作的上传指令

    c2s_apply_player_display_data,	// 玩家显示数据

    c2s_stop_current_action,        // 中断玩家当前正在进行的行为

    // ------------ skill about protocol ------------->
    c2s_character_skill,			//角色攻击的上传指令
    c2s_mount_kungfu,
    c2s_cancel_buff,
    c2s_set_sheath_state,
    c2s_set_hide_hat_flag,
    c2s_apply_player_bufflist,

    // ------------- party about protocol ------------->
    c2s_invite_join_team_request, 
    c2s_invite_join_team_respond, 
    c2s_apply_join_team_request,
    c2s_apply_join_team_respond,
    c2s_team_del_member_request,
    c2s_team_change_authority_request,
    c2s_team_set_distribute_mode_request,
	c2s_team_set_roll_quality_request,
    c2s_team_set_formation_leader_request,
    c2s_team_member_notify_signpost_request,   // 向队友发送小地图上的标记
    c2s_team_set_mark_request,
    c2s_team_level_up_raid_request,
    c2s_team_change_member_group_request,

    //任务相关协议
    c2s_accept_quest,				//接受任务
    c2s_cancel_quest,				//取消任务
    c2s_finish_quest,				//完成任务
    c2s_share_quest,				//共享任务

	c2s_accept_escort_quest,		//接受护送任务

    //GM指令上传协议
    c2s_gm_command,

    // ------------- shop about protocol ------------->
    c2s_open_shop_request,
    c2s_query_shop_items,
    c2s_shop_buy_request,
    c2s_shop_sell_request,
    c2s_shop_repair_request,
    c2s_sold_list_buy_request,

    // ------------- Trading about ------------------->
    c2s_trading_invite_request,
    c2s_trading_invite_respond,
    c2s_trading_add_item,
    c2s_trading_delete_item,
    c2s_trading_set_money,
    c2s_trading_confirm,

    // ----------------------------------------------
    c2s_request_target,
    c2s_apply_exchange_item,		//申请交换装备
    c2s_apply_use_item,				//申请使用道具

    c2s_window_select,				//选择窗口选项

    c2s_cast_profession_skill,			//配方使用协议

    c2s_loot_item,			
    c2s_roll_item,			

    c2s_apply_loot_list,			//申请拾取列表
    c2s_character_open,				//打开

	c2s_apply_fight_flag,			//改变战斗开关

	c2s_finish_loot,				//结束拾取
	c2s_loot_money,					//拾取金钱
	c2s_change_pk_mode,				//改变PK状态
	c2s_distribute_item,		    //分配者分配物品

    c2s_talk_message,

    c2s_get_fellowship_list_request,
    c2s_add_fellowship_request,
    c2s_del_fellowship_request,
    c2s_add_fellowship_group_request,
    c2s_del_fellowship_group_request,
    c2s_rename_fellowship_group_request,
    c2s_set_fellowship_remark_request,
    c2s_set_fellowship_group_request,

    c2s_send_mail_request,
    c2s_get_maillist_request,
    c2s_query_mail_content,
    c2s_acquire_mail_money_request,
    c2s_acquire_mail_item_request,
    c2s_set_mail_read,
    c2s_delete_mail,
    c2s_return_mail,

	c2s_apply_pk_operate,

	c2s_sync_user_preferences,		//同步玩家角色界面配置信息的修改

	c2s_set_bank_opened_flag,
	c2s_enable_bank_package,

	c2s_sync_mid_map_mark,

    c2s_player_learn_skill, 
	c2s_player_learn_recipe,

    c2s_player_active_skill_recipe,

    c2s_peek_other_player_equip,
    c2s_peek_other_player_book,
    c2s_peek_other_player_quest,

    c2s_road_track_start_out,
    c2s_road_track_force_request,
    c2s_open_venation,

    c2s_send_gm_message, 

    c2s_join_battle_field_queue_request,
    c2s_leave_battle_field_queue_request,
    
    c2s_accept_join_battle_field,
    c2s_get_battle_field_list,
    c2s_leave_battle_field,

    // ------------- Tong about ------------------->
    c2s_update_tong_roster_request,
    c2s_apply_tong_info_request,
    c2s_apply_tong_repertory_page_request,
    c2s_invite_player_join_tong_request,
    c2s_invite_player_join_tong_respond,
    c2s_apply_kick_out_tong_member_request,
    c2s_modify_tong_info_request,
    c2s_modify_tong_schema_request,
    c2s_apply_quit_tong_request,

    c2s_change_tong_member_group_request,
    c2s_change_tong_master_request,
    c2s_change_tong_member_remark_request,

    c2s_get_tong_description_request,
    c2s_save_money_in_tong_request,
    c2s_pay_tong_salary_request,
    c2s_get_tong_salary_request,

    c2s_apply_open_tong_repertory_request,
    c2s_take_tong_repertory_item_to_pos_request,
    c2s_take_tong_repertory_item_request,
    c2s_put_tong_repertory_item_to_pos_request,
    c2s_put_tong_repertory_item_request,
    c2s_exchange_tong_repertory_item_pos_request,
    c2s_stack_tong_repertory_item_request,

    // -----------------------------------------------
    c2s_apply_battlefield_statistics,
    c2s_set_hero_flag,

    // ------------- Auction about ------------------->
    c2s_auction_lookup_request,
    c2s_auction_bid_request,
    c2s_auction_sell_request,
    c2s_auction_cancel_request,
    
    c2s_apply_set_camp_request,

    c2s_remote_lua_call,

    c2s_player_revive_request,
    c2s_query_product_identity,
    // ------------- Achievement about ------------------->
    c2s_apply_achievement_data_request,

    c2s_set_current_designation_request,

    // ------------- ViewPoint --------------------------->
    c2s_create_view_point_request,
    c2s_remove_view_point_request,
    c2s_move_view_point_request,

    c2s_apex_protocol,

    c2s_game_card_sell_request,
    c2s_game_card_buy_request,
    c2s_game_card_lookup_request,
    c2s_game_card_cancel_request,

    c2s_apply_character_threat_ranklist, 

    client_gs_connection_end
};
// Client 2 GS Protocol End

//协议结构定义
#pragma	pack(1)

//GS 2 Client Struct Begin

// 好感度信息结构，通过S2C_MESSAGE_NOTIFY下行至客户端
struct KMESSAGE_ATTRACTION
{
    char  szAlliedPlayerName[_NAME_LEN];
    int   nAttraction;
};

struct KSOLD_ITEM_INFO 
{
    DWORD dwBuyerID;
    DWORD dwItemPos;
    int   nPriceAfterTax;
};

// 消息通知
struct S2C_MESSAGE_NOTIFY : UNDEFINED_SIZE_DOWNWARDS_HEADER
{
    BYTE    byType;
    BYTE	byCode;
    BYTE    byData[0];
};

// 登录时同步玩家基本信息
struct S2C_SYNC_PLAYER_BASE_INFO : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD	dwPlayerID;
    char	szRoleName[_NAME_LEN];
    BYTE    byRoleType;
    DWORD	dwMapID;
    int     nMapCopyIndex;
    int		nX;
    int		nY;
    int		nZ;
    BYTE    byFaceDirection;
    BYTE    byLevel;
    BYTE    byCamp;
    BYTE    byForceID;
    WORD    wRepresentId[perRepresentCount];
    int     nFrame;
    time_t  nBaseTime;
    DWORD   dwTongID;
    int     nBattleFieldSide;
};

struct S2C_SYNC_QUEST_DATA : UNDEFINED_SIZE_DOWNWARDS_HEADER 
{
    DWORD	dwDestPlayerID;
    BYTE    byQuestDataType;
    BYTE    byData[0];
};

struct S2C_ACCOUNT_KICKOUT : DOWNWARDS_PROTOCOL_HEADER
{
};

struct S2C_SWITCH_GS : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD           dwPlayerID;
    GUID            Guid;
    DWORD           dwIPAddr;
    WORD	        wPort;	
};

struct S2C_SWITCH_MAP : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD   dwMapID;
    int     nCopyIndex;
    int     nX;
    int     nY;
    int     nZ;
    int     nBattleFieldSide;
};

// 同步新进入的玩家到客户端
struct S2C_SYNC_NEW_PLAYER : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD	    dwID;
    BYTE        byRepresentState[brpTotal];
    BYTE        byFaceDirection;
    BYTE        byPitchDirection;
    BYTE        byMoveFrameCount;
    BYTE        byLifePercent;

    uint64_t    uMoveState          : MAX_MOVE_STATE_BIT_NUM;       // 5 bits
    uint64_t    uPosX               : MAX_X_COORDINATE_BIT;	        // 17 bits
    uint64_t    uPosY               : MAX_Y_COORDINATE_BIT;         // 17 bits
    uint64_t    uPosZ               : MAX_Z_POINT_BIT_NUM;          // 22 bits
    uint64_t    uFightState         : 1;                            // 战斗状态
    uint64_t    uSheathFlag         : 1;                            // 拔剑状态
    uint64_t    uPK                 : 1;
    // <-- 64 bits ---

    uint64_t    uConvergenceSpeed   : MAX_VELOCITY_XY_BIT_NUM;      // 稳态速度 7 bits
    uint64_t    uDirectionXY        : DIRECTION_BIT_NUM;            // 8 bits
    int64_t     nVelocityZ          : MAX_VELOCITY_Z_BIT_NUM;       // 12 bits
    uint64_t    uDestX              : MAX_X_COORDINATE_BIT;	        // 17 bits, AutoMove模式下,表示TrackID
    uint64_t    uDestY              : MAX_Y_COORDINATE_BIT;	        // 17 bits, AutoMove模式下,表示Frame
    uint64_t    uOnHorse            : 1;                            // 是否在马上 
    uint64_t    uTryPathState       : 1;
    uint64_t    uTryPathSide        : 1;
    // <-- 64 bits ---

    uint32_t    uCurrentGravity     : MAX_GRAVITY_BIT_NUM;          // 5 bits
    uint32_t    uVelocityXY         : MAX_ZOOM_VELOCITY_BIT_NUM;    // 11  bits
    uint32_t    uRedName            : 1;
    uint32_t    uRunSpeed           : MAX_VELOCITY_XY_BIT_NUM;      // 7 bits
    uint32_t    uMoveCtrlDisable    : 1;
    uint32_t    uMoveCtrlMoving     : 1;
    uint32_t    uMoveCtrlWalk       : 1;
    uint32_t    uMoveCtrlDirection8 : 3;
    int32_t     nMoveCtrlTurn       : 2;
    // <-- 32 bits ---

    uint8_t     uSlipFlag           : 1;
    uint8_t     uWaterFlyAbility    : 1;  
    uint8_t     uCampFlag           : 1;  
};

// 同步新进入的NPC到客户端
struct S2C_SYNC_NEW_NPC : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD	    dwID;
    DWORD       dwTemplateID;
    BYTE        byRepresentState[brpTotal];
    BYTE        byFaceDirection;
    BYTE        byMoveFrameCount;
	BYTE        byLevel;
	WORD	    wModelID;
	BYTE	    byForceID;
    BYTE        byLifePercent;

    uint64_t    uMoveState          : MAX_MOVE_STATE_BIT_NUM;       // 5 bits
    uint64_t    uPosX               : MAX_X_COORDINATE_BIT;	        // 17 bits
    uint64_t    uPosY               : MAX_Y_COORDINATE_BIT;         // 17 bits
    uint64_t    uPosZ               : MAX_Z_POINT_BIT_NUM;          // 22 bits
    uint64_t    uFightState         : 1;                            // 战斗状态
    uint64_t    uSheathFlag         : 1;                            // 拔剑状态
    uint64_t    uTryPathState       : 1;
    // <-- 64 bits ---

    uint64_t    uVelocityXY         : MAX_ZOOM_VELOCITY_BIT_NUM;    // 11 bits
    uint64_t    uConvergenceSpeed   : MAX_VELOCITY_XY_BIT_NUM;      // 稳态速度 7 bits
    int64_t     nVelocityZ          : MAX_VELOCITY_Z_BIT_NUM;       // 12 bits
    uint64_t    uDestX              : MAX_X_COORDINATE_BIT;	        // 17 bits
    uint64_t    uDestY              : MAX_Y_COORDINATE_BIT;	        // 17 bits
    // <-- 64 bits ---

    uint16_t    uDirectionXY        : DIRECTION_BIT_NUM;            // 8 bits
    uint16_t    uTryPathSide        : 1;
    uint16_t    uCurrentGravity     : MAX_GRAVITY_BIT_NUM;          // 5 bits
    uint16_t    uSlipFlag           : 1;
    uint16_t    uDialogFlag         : 1;
    // <-- 16 bits ---
};

// 同步新进入的Doodad到客户端
struct S2C_SYNC_NEW_DOODAD : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD		dwID;
    DWORD		dwTemplateID;
    BYTE	    byFaceDirection;
    char	    cKind;
    char		cState;
    DWORD		dwNpcTemplateID;
    DWORD		dwNpcID;
    DWORD		dwRepresentID;
    bool		bLooted;
    int         nObstacleGroup;
    bool        bObstacleState;
    uint64_t    uPosX               : MAX_X_COORDINATE_BIT;	        // 17 bits
    uint64_t    uPosY               : MAX_Y_COORDINATE_BIT;         // 17 bits
    uint64_t    uPosZ               : MAX_Z_POINT_BIT_NUM;          // 22 bits
    uint64_t    uReserve            : 8;                            // 对齐
    // <-- 64 bits ---
};


// 从场景中移除角色
struct S2C_REMOVE_CHARACTER : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD   dwCharacterID;
	BOOL    bKilled;
};

// 从场景中移除Doodad
struct S2C_REMOVE_DOODAD : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD   dwID;
};

// Doodad状态同步
struct S2C_SYNC_DOODAD_STATE : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD   dwID;
	char    cState;
    bool    bObstacleState;
};

// 控制同步
struct S2C_SYNC_MOVE_CTRL : DOWNWARDS_PROTOCOL_HEADER 
{
    DWORD       dwID;
    BYTE        byMoveFrameCount;
    BYTE        byFaceDirection;
    BYTE        byPitchDirection;

    uint64_t    uMoveCtrlDisable        : 1;
    uint64_t    uMoveCtrlMoving         : 1;
    uint64_t    uMoveCtrlWalk           : 1;
    uint64_t    uMoveCtrlDirection8     : 3;
    int64_t     nMoveCtrlTurn           : 2;
    uint64_t    uPosX                   : MAX_X_COORDINATE_BIT;	     // 17 bits
    uint64_t    uPosY                   : MAX_Y_COORDINATE_BIT;      // 17 bits
    uint64_t    uPosZ                   : MAX_Z_POINT_BIT_NUM;       // 22 bits
    // <-- 64 bit --

    uint64_t    uMoveState              : MAX_MOVE_STATE_BIT_NUM;    // 5 bits
    uint64_t    uVelocityXY             : MAX_ZOOM_VELOCITY_BIT_NUM; // 11 bits
    int64_t     nVelocityZ              : MAX_VELOCITY_Z_BIT_NUM;    // 12 bits
    uint64_t    uDirectionXY            : DIRECTION_BIT_NUM;         // 8 bits
    uint64_t    uConvergenceSpeed       : MAX_VELOCITY_XY_BIT_NUM;   // 7 bits
    uint64_t    uCurrentGravity         : MAX_GRAVITY_BIT_NUM;       // 5 bits
    uint64_t    uTryPathState           : 1;
    uint64_t    uTryPathSide            : 1;
    uint64_t    uSlipFlag               : 1;
    uint64_t    uRunSpeed               : MAX_VELOCITY_XY_BIT_NUM;      // 7 bits
    // <-- 58 bits --
};

// 参数同步
struct S2C_SYNC_MOVE_PARAM : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD       dwID;
    BYTE        byFaceDirection;
    BYTE        byPitchDirection;
    BYTE        byMoveFrameCount;

    uint64_t    uMoveState          : MAX_MOVE_STATE_BIT_NUM;       // 5 bits
    uint64_t    uPosX               : MAX_X_COORDINATE_BIT;	        // 17 bits
    uint64_t    uPosY               : MAX_Y_COORDINATE_BIT;         // 17 bits
    uint64_t    uPosZ               : MAX_Z_POINT_BIT_NUM;          // 22 bits
    uint64_t    uTryPathState       : 1;
    uint64_t    uTryPathSide        : 1;
    uint64_t    uSlipFlag           : 1;
    // <-- 64 bits ---

    uint64_t    uVelocityXY         : MAX_ZOOM_VELOCITY_BIT_NUM;    // 11  bits
    uint64_t    uRunSpeed           : MAX_VELOCITY_XY_BIT_NUM;      // 7 bits
    int64_t     nVelocityZ          : MAX_VELOCITY_Z_BIT_NUM;       // 12 bits
    uint64_t    uDestX              : MAX_X_COORDINATE_BIT;	        // 17 bits, AutoMove模式下,表示TrackID
    uint64_t    uDestY              : MAX_Y_COORDINATE_BIT;	        // 17 bits, AutoMove模式下,表示Frame
    // <-- 64 bits ---

    uint32_t    uConvergenceSpeed   : MAX_VELOCITY_XY_BIT_NUM;      // 稳态速度 7 bits
    uint32_t    uDirectionXY        : DIRECTION_BIT_NUM;            // 8 bits
    uint32_t    uCurrentGravity     : MAX_GRAVITY_BIT_NUM;          // 5 bits
    // <-- 21 bits ---
};

// 同步修正
struct S2C_ADJUST_PLAYER_MOVE : DOWNWARDS_PROTOCOL_HEADER
{
    int         nMoveCount;
    int         nVirtualFrame;
    int         nJumpLimitFrame;
    BYTE        byFaceDirection;
    BYTE        byPitchDirection;
    BYTE        byMoveFrameCount;

    uint64_t    uMoveState          : MAX_MOVE_STATE_BIT_NUM;       // 5 bits
    uint64_t    uPosX               : MAX_X_COORDINATE_BIT;	        // 17 bits
    uint64_t    uPosY               : MAX_Y_COORDINATE_BIT;         // 17 bits
    uint64_t    uPosZ               : MAX_Z_POINT_BIT_NUM;          // 22 bits
    uint64_t    uTryPathState       : 1;
    uint64_t    uTryPathSide        : 1;
    uint64_t    uSlipFlag           : 1;
    // <-- 64 bits ---

    uint64_t    uVelocityXY         : MAX_ZOOM_VELOCITY_BIT_NUM;    // 11  bits
    uint64_t    uRunSpeed           : MAX_VELOCITY_XY_BIT_NUM;      // 7 bits
    int64_t     nVelocityZ          : MAX_VELOCITY_Z_BIT_NUM;       // 12 bits
    uint64_t    uDestX              : MAX_X_COORDINATE_BIT;	        // 17 bits, AutoMove模式下,表示TrackID
    uint64_t    uDestY              : MAX_Y_COORDINATE_BIT;	        // 17 bits, AutoMove模式下,表示Frame
    // <-- 64 bits ---

    uint32_t    uConvergenceSpeed   : MAX_VELOCITY_XY_BIT_NUM;      // 稳态速度 7 bits
    uint32_t    uDirectionXY        : DIRECTION_BIT_NUM;            // 8 bits
    uint32_t    uCurrentGravity     : MAX_GRAVITY_BIT_NUM;          // 5 bits
    // <-- 21 bits ---
};

// 状态同步
struct S2C_SYNC_MOVE_STATE : DOWNWARDS_PROTOCOL_HEADER 
{
    DWORD       dwID;
    BYTE        byFaceDirection;
    BYTE        byPitchDirection;
    BYTE        byMoveFrameCount;

    uint64_t    uMoveState              : MAX_MOVE_STATE_BIT_NUM;    // 5 bits
    uint64_t    uPosX                   : MAX_X_COORDINATE_BIT;	     // 17 bits
    uint64_t    uPosY                   : MAX_Y_COORDINATE_BIT;      // 17 bits
    uint64_t    uPosZ                   : MAX_Z_POINT_BIT_NUM;       // 22 bits
    uint64_t    uFightState             : 1;
    uint64_t    uTryPathState           : 1;
    uint64_t    uTryPathSide            : 1;
    // <-- 64 bit --

    uint64_t    uVelocityXY             : MAX_ZOOM_VELOCITY_BIT_NUM; // 11 bits
    int64_t     nVelocityZ              : MAX_VELOCITY_Z_BIT_NUM;    // 12 bits
    uint64_t    uConvergenceSpeed       : MAX_VELOCITY_XY_BIT_NUM;   // 7 bits
    uint64_t    uDestX                  : MAX_X_COORDINATE_BIT;	     // 17 bits
    uint64_t    uDestY                  : MAX_Y_COORDINATE_BIT;	     // 17 bits
    // <-- 64 bits --

    uint16_t    uDirectionXY            : DIRECTION_BIT_NUM;         // 8 bits
    uint16_t    uJumpCount              : MAX_JUMP_COUNT_BIT;        // 2 bits
    uint16_t    uSlipFlag               : 1;
    // <-- 11 bits --
};

// 角色死亡的同步数据包
struct S2C_CHARACTER_DEATH : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD	    dwCharacterID;
    DWORD	    dwKillerID;
    uint64_t    uSrcX              : MAX_X_COORDINATE_BIT;	  // 17 bits
    uint64_t    uSrcY              : MAX_Y_COORDINATE_BIT;    // 17 bits
    uint64_t    uSrcZ              : MAX_Z_POINT_BIT_NUM;     // 22 bits
    uint64_t    uFaceDirection     : DIRECTION_BIT_NUM;       // 8  bits
    // <-- 64 bit
};

// 移动角色位置
struct S2C_MOVE_CHARACTER : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD	    dwID;
    BYTE        byFaceDirection;
    int         nPosX;           
    int         nPosY;  
    int         nPosZ;
    BYTE        byDirectionXY;
    uint16_t    uVelocityXY;
    int16_t     nVelocityZ;
    uint16_t    uConvergenceSpeed;
    BYTE        byMoveState;
    BYTE        bIgnoreBlock;
};

// 角色交互动作的同步数据包
struct S2C_CHARACTER_ACTION : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD   dwSrcCharacterID;
    DWORD	dwDestCharacterID;
    DWORD	dwAction;
};

struct S2C_OVER_TIME_ACTION : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD   dwCharacterID;
    char    cActionType;
    WORD    wActionID;
    BYTE    byDirection;
    WORD    wDurationFrame;
};

// 玩家显示数据
struct S2C_PLAYER_DISPLAY_DATA : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD	    dwPlayerID;
    char	    szRoleName[_NAME_LEN];
    BYTE	    byRoleType;
    BYTE        byLevel;
    BYTE        byCamp;
	BYTE        byForceID;
    DWORD       dwTongID;
    WORD        wModelID;
    char        byBattleFieldSide;

    uint32_t    uDesignationPrefix  : 8;
    uint32_t    uDesignationPostfix : 8;
    uint32_t    uGenerationIndex    : 5;
    uint32_t    uBynameIndex        : 10;
    uint32_t    uDisplayFlag        : 1;
    // <---------- 32 bits ------

    uint64_t    uFaceStyle      : 5;
    uint64_t    uBangleColor    : 6;
    
    uint64_t    uHelmStyle      : 8;     
    uint64_t    uHelmColor      : 4;     
    uint64_t    uHelmEnchant    : 5;
    
    uint64_t    uChestStyle     : 8;
    uint64_t    uChestColor     : 6;
    uint64_t    uChestEnchant   : 5;
    
    uint64_t    uWaistStyle     : 8;    
    uint64_t    uWaistColor     : 4;    
    uint64_t    uWaistEnchant   : 5;
    // <---------- 64 bits
     
    uint64_t    uBangleStyle    : 8;
    uint64_t    uHairStyle      : 8;   
    uint64_t    uBangleEnchant  : 5; 
    
    uint64_t    uHorseStyle     : 5;   
    uint64_t    uBootsColor     : 4;
       
    uint64_t    uWeaponStyle    : 10;    
    uint64_t    uWeaponEnchant1 : 5;
    uint64_t    uWeaponEnchant2 : 5;
    
    uint64_t    uBackExtend     : 7;
    uint64_t    uWaistExtend    : 7;
    // <--- 64 bits--
    
    uint32_t    uBootsStyle         : 8;    
    uint32_t    uHorseAdornment1    : 5;
    uint32_t    uHorseAdornment2    : 5;
    uint32_t    uHorseAdornment3    : 5;
    uint32_t    uHorseAdornment4    : 5;
    uint32_t    uSchoolID           : 4;
    // <--- 32 bits--
};

// 获取经验值
struct S2C_SYNC_EXPERIENCE : DOWNWARDS_PROTOCOL_HEADER
{
    int nCurrentExp;
    int nDeltaExp;
};

struct S2C_PLAYER_LEVEL_UP : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD   dwID;
    int     nLevel;
};

struct S2C_COMMON_HEALTH :  DOWNWARDS_PROTOCOL_HEADER
{
    DWORD   dwCharacterID;
    int     nDeltaLife;
};

struct S2C_FRAME_SIGNAL : DOWNWARDS_PROTOCOL_HEADER
{
    int nFrame;
};

struct S2C_PING_SIGNAL : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD dwTime;
};

// ------------------ skill about protocol ----------------->

//同步技能数据,bySkillLevel为0意味着这个技能没有了(Forget)
struct S2C_SYNC_SKILL_DATA : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD	dwSkillID;
    BYTE	bySkillLevel;
    DWORD   dwSkillExp;
    BOOL    bNotifyPlayer;
};

struct S2C_SYNC_SKILL_RECIPE : UNDEFINED_SIZE_DOWNWARDS_HEADER 
{
    WORD    wCount;
    struct _RecipeNode 
    {
        DWORD   dwRecipeKey;
        BOOL    bActive;
    } RecipeArray[0];
};

struct S2C_SKILL_PREPARE : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD	dwCharacterID;
    DWORD	dwSkillID;
    BYTE	bySkillLevel;
    int     nPrepareFrame;
    BYTE    byTargetType;		    //TARGET_TYPE类型
    int	    nParam1;			    //如果TargetType不是坐标，则这里表示角色ID
    int	    nParam2;
    int	    nParam3;
};

struct S2C_SKILL_CAST : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD   dwCharacterID;
    DWORD   dwSkillID;
    BYTE    bySkillLevel;
    DWORD   dwBulletID;           //该技能所产生的子弹ID    
    bool    bSubCast;
    BYTE    byFaceDirection;
    BYTE    byTargetType;		    //TARGET_TYPE类型
    int     nParam1;			    //如果TargetType不是坐标，则这里表示角色ID
    int     nParam2;
    int	    nParam3;
};

struct S2C_SYNC_COMMON_SKILL_AUTO_CAST_STATE : DOWNWARDS_PROTOCOL_HEADER
{
    bool bStart;
    bool bMelee;
};

struct S2C_RESET_COOLDOWN :  DOWNWARDS_PROTOCOL_HEADER
{
    DWORD dwCoolDownID;
    int   nEndFrame;
    int   nInterval;
};

struct S2C_SKILL_CHAIN_EFFECT : UNDEFINED_SIZE_DOWNWARDS_HEADER
{
    DWORD   dwSkillID;
    DWORD   dwSkillLevel;
    DWORD   dwCasterID;
    size_t  uCount;
    DWORD   dwCharacterID[0];
};

// 技能打断,终止,包括吟唱的终止,通道技的终止
struct S2C_SKILL_BREAK :  DOWNWARDS_PROTOCOL_HEADER
{
    DWORD dwCharacterID;
};

// 吟唱打退
struct  S2C_PREPARE_BACK : DOWNWARDS_PROTOCOL_HEADER
{
};

struct S2C_SKILL_EFFECT_RESULT : UNDEFINED_SIZE_DOWNWARDS_HEADER
{
    DWORD dwSkillSrc;   // 技能发出者的ID
    DWORD dwSkillDst;
    DWORD dwBulletID;

	struct
    {
        BYTE    byType;
        DWORD   dwID;
        BYTE    byLevel;  
    } EffectSrc;
  
    BYTE  bShield               : 1;
    BYTE  bPhysicsBlock         : 1;
    BYTE  bSolarMagicBlock      : 1;
    BYTE  bNeutralMagicBlock    : 1;
    BYTE  bLunarMagicBlock      : 1;
    BYTE  bPoisonBlock          : 1;
    BYTE  bReact                : 1;
    BYTE  bHitTarget            : 1;
    // <--- 8 bits--

    BYTE  bSkillDodge           : 1;
    BYTE  bSkillImmunity        : 1;
    BYTE  bCriticalStrike       : 1;
    BYTE  bBuffResist           : 1;
    BYTE  bBuffImmunity         : 1;
    BYTE  bParry                : 1;
    BYTE  bInsight              : 1;

    BYTE  byReserve            : 1;    // 对齐
    // <--- 8 bits--

    DWORD dwBuffID;
    BYTE  byBuffLevel;

    char  cResultCount;
    struct KSKILL_RESULT 
    {
        char cEffectResultType;
        int  nValue;
    } SkillResult[0];
};

struct S2C_SYNC_BEHIT_REPRESENT: UNDEFINED_SIZE_DOWNWARDS_HEADER
{
    DWORD dwSkillSrc;
    DWORD dwSkillDst;
    DWORD dwBulletID;
    
    struct
    {
        BYTE    byType;
        DWORD   dwID;
        BYTE    byLevel;  
    } EffectSrc;

    int bReact              : 1;
    int bHitTarget          : 1;
    int bSkillDodge         : 1;
    int bCriticalStrike     : 1;    

    int bPhysicsBlock       : 1;
    int bSolarMagicBlock    : 1;
    int bNeutralMagicBlock  : 1;
    int bLunarMagicBlock    : 1;
    int bPoisonBlock        : 1;

    int bPhysicsDamage      : 1;
    int bSolarMagicDamage   : 1;
    int bNeutralMagicDamage : 1;
    int bLunarMagicDamage   : 1;
    int bPoisonDamage       : 1;
    int bReflectiedDamage   : 1;  

    int bTherapy            : 1;          
    int bStealLife          : 1;         
    int bAbsorbDamage       : 1;     
    int bShieldDamage       : 1;
    int bParry              : 1;
    int bInsight            : 1;

    int nReserve            : 11;   // 对齐
    // <-- 32 bits ---
};

struct S2C_SYNC_BUFF_LIST : UNDEFINED_SIZE_DOWNWARDS_HEADER
{
    DWORD dwCharacterID;
    WORD  wDataSize;
    BYTE  byData[0];
};

struct S2C_SYNC_BUFF_SINGLE : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD   dwCharacterID;
    int     nIndex;
    DWORD   dwBuffID;
    BYTE    byLevel;
    DWORD   dwRecipeKey;
    BYTE    byStackNum;
    int     nEndFrame;
};

struct S2C_SYNC_REPRESENT_STATE : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD dwCharacterID;
    BYTE  byRepresentState[brpTotal];
};

struct S2C_SYNC_KUNGFU_MOUNT :  DOWNWARDS_PROTOCOL_HEADER
{
    DWORD dwID;
    DWORD dwLevel;
};

struct S2C_SKILL_BEAT_BACK :  DOWNWARDS_PROTOCOL_HEADER
{
    DWORD dwCharacterID;
    int   nBeatBackFrame;
	BOOL  bBreak;
};

struct S2C_SYNC_SHEATH_STATE :  DOWNWARDS_PROTOCOL_HEADER
{
    DWORD dwCharacterID;
    bool  bSheathFlag;
};

// ------------------  人物数值同步 -----------------------------

struct S2C_SYNC_SELF_MAX_LMRS : DOWNWARDS_PROTOCOL_HEADER
{
    int nMaxLife;
    int nMaxMana;
    int nMaxRage;
};

struct S2C_SYNC_SELF_CURRENT_LMRS : DOWNWARDS_PROTOCOL_HEADER
{
    int nCurrentLife;
    int nCurrentMana;
    int nCurrentRage;
};

struct S2C_SYNC_SELF_WEAK_INFO : DOWNWARDS_PROTOCOL_HEADER
{
    BYTE byUpper    : 2;
    BYTE byMiddle   : 2;
    BYTE byLower    : 2;

    BYTE byReserve  : 2;    //对齐
    // <--- 8 bits--
};

struct S2C_SYNC_SELECT_CHARACTER_MAX_LMR : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD   dwCharacterID;
    int     nMaxLife;
    int     nMaxMana;
    int     nMaxRage;
};

struct S2C_SYNC_SELECT_CHARACTER_CURRENT_LMR : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD   dwCharacterID;
    BYTE    byLifePercent;
    BYTE    byManaPercent;
    BYTE    byRagePercent;
};

struct S2C_SYNC_SELECT_CHARACTER_WEAK_INFO : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD   dwCharacterID;
    BYTE    byUpper     : 2;
    BYTE    byMiddle    : 2;
    BYTE    byLower     : 2;

    BYTE    byReserve   : 2;    //对齐
    // <--- 8 bits--
};

struct S2C_SYNC_TEAM_MEMBER_MAX_LMR : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD   dwMemberID;
    int     nMaxLife;
    int     nMaxMana;
    int     nMaxRage;
};

struct S2C_SYNC_TEAM_MEMBER_CURRENT_LMR : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD   dwMemberID;
    BYTE    byLifePercent;
    BYTE    byManaPercent;
    BYTE    byRagePercent;
};

struct S2C_SYNC_TEAM_MEMBER_MISC : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD           dwMemberID;
    KPORTRAIT_INFO  PortraitInfo;
    DWORD           dwMapID;
    DWORD           dwForceID;
    BYTE            byCamp;
    BYTE            byLevel;  
	BYTE            byRoleType;
    bool            bDeathFlag;
};

struct S2C_SYNC_TEAM_MEMBER_POSITION : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD dwMemberID;
    DWORD dwMapID;
    int   nMapCopyIndex;
    int   nPosX;
    int   nPosY;
};

struct S2C_BROADCAST_CHARACTER_LIFE : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD		dwCharacterID;
    BYTE	    byLifePercent;
};

struct S2C_SYNC_PLAYER_TRAIN : DOWNWARDS_PROTOCOL_HEADER
{
    int         nCurrentTrainValue;
    int         nUsedTrainValue;
};

struct S2C_BROADCAST_PLAYER_SCHOOL_ID : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD       dwPlayerID;
    DWORD       dwSchoolID;
};

// ------------------ party about protocol ------------------>

// 玩家登陆服务器时同步队伍基本信息
struct S2C_SYNC_PLAYER_TEAM_BASE_INFO : UNDEFINED_SIZE_DOWNWARDS_HEADER
{
    BOOL  bSystem;
    DWORD dwTeamID;
    DWORD dwLeaderID;
    int   nGroupNum;
    int   nLootMode;
	int   nRollQuality;
    BYTE  byCamp;
    DWORD dwFormationLeader[MAX_TEAM_GROUP_NUM];
    DWORD dwDistributeMan;
    DWORD dwMarkMan;
    bool  bAddTeamMemberFlag;
    DWORD dwTeamMark[PARTY_MARK_COUNT];
    BYTE  byMemberCount;
    struct KMEMBER_INFO
    {
        DWORD dwMemberID;
        BYTE  byGroupIndex;
        char  szMemberName[_NAME_LEN];
        KPORTRAIT_INFO  PortraitInfo;
        DWORD dwMapID;
        int   nMapCopyIndex;
        BYTE  byForceID;
        BYTE  byLevel;
        BYTE  byOnLineFlag;
        int   nMaxLife;
        int   nMaxMana;
        int   nMaxRage;
        BYTE  byLifePercent;
        BYTE  byManaPercent;
        BYTE  byRagePercent;
        int   nPosX;
        int   nPosY;
        BYTE  byRoleType;
        BYTE  byDeathFlag;
    } MemberInfo[0];
};

// xxx邀请你组队
struct S2C_INVITE_JOIN_TEAM_REQUEST : DOWNWARDS_PROTOCOL_HEADER
{
    char  szInviteSrc[_NAME_LEN]; // 发出组队请求的玩家
};

// xxx申请加入xxx的队伍
struct S2C_APPLY_JOIN_TEAM_REQUEST : DOWNWARDS_PROTOCOL_HEADER
{
    char  szApplySrc[_NAME_LEN]; // 发出入队申请的玩家
};

// 如果A玩家刚刚加入某队伍,通知队伍里面的所有成员"A的加入了队伍"
struct S2C_TEAM_ADD_MEMBER_NOTIFY : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD           dwTeamID;
    int             nGroupIndex;
    DWORD           dwMemberID;
    char            szMemberName[_NAME_LEN];
};

// 通知客户端xxx离开xxx的队伍
struct S2C_TEAM_DEL_MEMBER_NOTIFY : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD dwTeamID;
    int   nGroupIndex;
    DWORD dwMemberID;
};

struct S2C_TEAM_CHANGE_AUTHORITY_NOTIFY : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD dwTeamID;
    BYTE  byType;
    DWORD dwNewID;
};

struct S2C_TEAM_SET_LOOT_MODE_NOTIFY : DOWNWARDS_PROTOCOL_HEADER
{
	DWORD dwTeamID;
	int   nLootMode;
	int   nRollQuality;
};

struct S2C_TEAM_SET_FORMATION_LEADER_NOTIFY : DOWNWARDS_PROTOCOL_HEADER
{
	DWORD dwTeamID;
    int   nGroupIndex;
    DWORD dwNewFormationLeader;
};

struct S2C_TEAM_DISBAND_NOTIFY : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD dwTeamID;
};

struct S2C_SYNC_TEAM_MEMBER_ONLINE_FLAG : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD dwTeamID;
    DWORD dwMemberID;
    bool  bOnlineFlag;
};

struct  S2C_TEAM_MEMBER_SIGNPOST_NOTIFY : DOWNWARDS_PROTOCOL_HEADER
{
    int   nX;
    int   nY;
};

struct S2C_TEAM_SET_MARK_RESPOND : DOWNWARDS_PROTOCOL_HEADER
{
    int     nMarkType;
    DWORD   dwTargetID;
};

struct S2C_TEAM_CAMP_CHANGE : DOWNWARDS_PROTOCOL_HEADER
{
    BYTE byCamp;
};

struct S2C_TEAM_LEVEL_UP_RAID_NOTIFY : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD dwTeamID;
    BYTE  byGroupNum;
};

struct S2C_TEAM_CHANGE_MEMBER_GROUP_NOTIFY : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD dwTeamID;
    BYTE  bySrcGroupIndex;
    BYTE  byDstGroupIndex;
    DWORD dwDstMemberID;
    DWORD dwMemberID;
};

// ------------------ shop about protocol ------------------>

struct S2C_OPEN_SHOP_NOTIFY : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD   dwShopID;
    char    cShopType;
    BYTE    byValidPage;
    bool    bCanRepair;
    DWORD   dwNpcID;
    DWORD   dwShopTemplateID;
};

// 同步商店格子信息
struct S2C_UPDATE_SHOP_ITEM : UNDEFINED_SIZE_DOWNWARDS_HEADER
{
    DWORD   dwShopID;
    BYTE    byPageIndex;
    BYTE    byPosIndex;
    BYTE    byItemTemplateIndex;
    DWORD   dwItemID;
    int     nCount;
    WORD    wItemDataLength;
    BYTE    byItemData[0];

};

// <------------------ shop about protocol ------------------

struct S2C_TRADING_INVITE_REQUEST : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD dwTradingInviteSrc;
};

struct S2C_OPEN_TRADING_BOX_NOTIFY : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD dwOtherPlayer;
};

struct S2C_SYNC_TRADING_CONFIRM : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD dwPlayerID;
    bool  bConfirm;
};

struct S2C_SYNC_TRADING_ITEM_DATA : UNDEFINED_SIZE_DOWNWARDS_HEADER
{
    DWORD   dwItemOwnerID;
    BYTE    byBoxIndex;
    BYTE    byPosIndex;
    BYTE    byGridIndex;
    BYTE    byStackNum;     // 物品叠加数量或耐久度
    int     nKey;
    char    szBuff[0];
};

struct S2C_SYNC_TRADING_MONEY : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD dwPlayerID;
    int   nMoney;
    int   nKey;
};

struct S2C_TRADING_COMPLETE : DOWNWARDS_PROTOCOL_HEADER
{
    bool bComplete;
};

// 同步金钱数量
struct S2C_SYNC_MONEY : DOWNWARDS_PROTOCOL_HEADER
{
    int						nMoney;
	BOOL					bShowMsg;
};

// 同步贡献值
struct S2C_SYNC_CONTRIBUTION : DOWNWARDS_PROTOCOL_HEADER
{   
    int                     nContribution;
};

// 同步道具数据
struct S2C_SYNC_ITEM_DATA : UNDEFINED_SIZE_DOWNWARDS_HEADER
{
    DWORD                   dwPlayerID;
    DWORD                   dwItemID;
    BYTE					byBox;
    BYTE					byX;
    BYTE					byBuff[0];
};

// 同步道具删除
struct S2C_SYNC_ITEM_DESTROY : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD                   dwOwnerID;
    BYTE					byBoX;
    BYTE					byX;
};


// 交换装备
struct S2C_EXCHANGE_ITEM : DOWNWARDS_PROTOCOL_HEADER
{
    BYTE					byBox1;
    BYTE					byX1;
    BYTE					byBox2;
    BYTE					byX2;
	WORD					wAmount;
};

// 换装广播
struct S2C_SYNC_EQUIP_REPRESENT : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD dwPlayerID;
    BYTE  byIndex;
    WORD  wRepresentID;
};

struct S2C_ADD_ITEM_NOTIFY : DOWNWARDS_PROTOCOL_HEADER
{
	DWORD dwPlayerID;
	DWORD dwItemID;
	DWORD dwCount;
};


// 更新物品数量或耐久
struct S2C_UPDATE_ITEM_AMOUNT : DOWNWARDS_PROTOCOL_HEADER
{
    BYTE byBox;
    BYTE byX;
    WORD wAmount;
};


// 学习生活技能
struct S2C_LEARN_PROFESSION_NOTIFY : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD dwProfessionID;
};

struct S2C_LEARN_BRANCH_NOTIFY : DOWNWARDS_PROTOCOL_HEADER
{
	DWORD dwProfessionID;
	DWORD dwBranchID;
};

// 遗忘技能
struct S2C_FORGET_PROFESSION_NOTIFY : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD dwProfessionID;
};

// 增加生活技能经验
struct S2C_ADD_PROFESSION_PROFICIENCY : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD dwProfessionID;
    DWORD dwExp;
};


// 设置生活技能等级
struct S2C_SET_MAX_PROFESSION_LEVEL_NOTIFY : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD dwProfessionID;
    DWORD dwLevel;
};

// 同步生活技能因其他因素修改的调整等级
struct S2C_SYNC_PROFESSION_ADJUST_LEVEL : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD dwProfessionID;
    DWORD dwAdjustLevel;
};

// 同步更新玩家生活技能
struct S2C_UPDATE_PLAYER_PROFESSION : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD dwProfessionID;
    DWORD dwMaxLevel;
    DWORD dwCurrentLevel; 
    DWORD dwCurrentProficiency;
	BYTE  byBranchID;
};

struct S2C_LEARN_RECIPE_NOTIFY : DOWNWARDS_PROTOCOL_HEADER
{
	DWORD dwCraftID;
	DWORD dwRecipeID;
};

struct S2C_FORGET_RECIPE_NOTIFY : DOWNWARDS_PROTOCOL_HEADER
{
	DWORD dwCraftID;
};

struct S2C_SYNC_RECIPE_STATE : UNDEFINED_SIZE_DOWNWARDS_HEADER
{
	BYTE  byVersion;
	BYTE  byData[0];
};

// 打开一个客户端窗口
struct S2C_OPEN_WINDOW : UNDEFINED_SIZE_DOWNWARDS_HEADER
{
    DWORD	dwIndex;			//流水号
	DWORD	dwTargetType;		//目标类型 Doodad? Npc?
	DWORD	dwTargetID;			//目标ID
    char	szText[0];
};


// 同步配方的使用
struct S2C_START_USE_RECIPE : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD	dwPlayerID;
	DWORD	dwCraftID;
    DWORD	dwRecipeID;
    BYTE	byTargetType;
    int		nParam1;
    int		nParam2;
};

// 通知客户端接受任务
struct S2C_ACCEPT_QUEST : DOWNWARDS_PROTOCOL_HEADER
{
    int     nQuestIndex;
    DWORD	dwQuestID;
    BYTE    byDailyQuest;
};

// 通知客户端完成任务
struct S2C_FINISH_QUEST : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD	dwQuestID;
	BOOL	bForce;
};

// 通知客户端取消任务
struct S2C_CANCEL_QUEST : DOWNWARDS_PROTOCOL_HEADER
{
    int		nQuestIndex;
};

// 通知客户端清除任务状态
struct S2C_CLEAR_QUEST : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD   dwQuestID;
};

// 共享任务
struct S2C_SHARE_QUEST : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD	dwSrcPlayerID;
    DWORD	dwQuestID;
};

// 同步任务变量
struct S2C_SYNC_QUEST_VALUE : DOWNWARDS_PROTOCOL_HEADER
{
    BYTE	byQuestIndex;
    DWORD	dwKillNpcCount[QUEST_PARAM_COUNT];
    int		nQuestValue[QUEST_PARAM_COUNT * 2];
	BOOL	bFailed;	
};


// 同步拾取列表
struct LOOT_ITEM 
{
    DWORD dwItemID;
    BYTE  byItemLootType;
    BYTE  byDisplay;
    BYTE  byItemDataSize;
};
struct S2C_SYNC_LOOT_LIST : UNDEFINED_SIZE_DOWNWARDS_HEADER
{
    DWORD	    dwDoodadID;
	int		    nMoney;
    BYTE        byLooterCount;
	DWORD       dwLooterIDList[0];
};

// 掷骰子信息
struct S2C_ROLL_ITEM_MESSAGE : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD	dwPlayerID;
    DWORD	dwDoodadID;
    DWORD	dwItemID;
    int		nRollPoint;
};

// 打开拾取面板
struct S2C_OPEN_LOOT_LIST : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD dwPlayerID;
    DWORD dwDoodadID;
};


// 同步战斗开关
struct S2C_SYNC_FIGHT_FLAG : DOWNWARDS_PROTOCOL_HEADER
{
	BYTE byForceID;
	BYTE byOpen;
};

// 同步声望
struct S2C_SYNC_REPUTE : DOWNWARDS_PROTOCOL_HEADER
{
	BYTE byForceID;
	BYTE byLevel;
	int	 nRepute;
	int	 nDiffValue;
};


// 同步所有势力战斗开关
struct S2C_SYNC_FIGHTFLAG_LIST : UNDEFINED_SIZE_DOWNWARDS_HEADER
{
	BYTE	byFightFlagCount;
	BYTE	byFightFlag[0];
};


// 同步所有的势力声望
struct S2C_SYNC_REPUTE_LIST : UNDEFINED_SIZE_DOWNWARDS_HEADER
{
	BYTE			byForceCount;

    struct KFORCE_REPUTE
    {
	    BYTE	byLevel;
	    short	shRepute;
    } Repute[0];	
};

struct S2C_SHOW_REPUTATION : DOWNWARDS_PROTOCOL_HEADER
{
	DWORD   dwForceID;
	BOOL    bShow;
    BOOL    bLoginLoading;
};
 
struct S2C_CHARACTER_OPEN : DOWNWARDS_PROTOCOL_HEADER
{
	DWORD dwCharacterID;
	DWORD dwDoodadID;
};


// 组队广播金钱的拾取
struct S2C_LOOT_MONEY_MESSAGE : DOWNWARDS_PROTOCOL_HEADER
{
	DWORD dwPlayerID;
	DWORD dwDoodadID;
	DWORD dwMoney;
};

struct S2C_DISTRIBUTE_ITEM_MESSAGE : DOWNWARDS_PROTOCOL_HEADER 
{
    DWORD dwDestPlayerID;
    DWORD dwItemID;
};

// 结束拾取
struct S2C_FINISH_LOOT : DOWNWARDS_PROTOCOL_HEADER
{
	DWORD dwPlayerID;
	DWORD dwDoodadID;
};

struct S2C_BEGIN_ROLL_ITEM : DOWNWARDS_PROTOCOL_HEADER
{
	DWORD dwItemID;
	DWORD dwDoodadID;
    WORD  wLeftRollFrame;
};

// 同步定制的用户消息
struct S2C_CUSTOM_OTACTION : DOWNWARDS_PROTOCOL_HEADER
{
	DWORD dwPlayerID;
	int nType;
	BOOL bIsBreakable;
	int nFrame;
	int nTargetType;
	int nTargetID;
	DWORD dwScriptID;
	char szActionName[CUSTOM_OTACTION_NAME_LEN];
};

// 同步开始小队任务
struct S2C_START_ESCORT_QUEST : DOWNWARDS_PROTOCOL_HEADER
{
	DWORD dwStartPlayerID;
	DWORD dwQuestID;
};

// 添加仇恨
struct S2C_MODIFY_THREAT : DOWNWARDS_PROTOCOL_HEADER
{
	DWORD dwCharacterID;
};


// 修改被仇恨
struct S2C_MODIFY_THREATEN : DOWNWARDS_PROTOCOL_HEADER
{
	DWORD dwCharacterID;
};


// 清除仇恨
struct S2C_CLEAR_THREAT : DOWNWARDS_PROTOCOL_HEADER
{
	DWORD dwCharacterID;
};


// 清除被仇恨
struct S2C_CLEAR_THREATEN : DOWNWARDS_PROTOCOL_HEADER
{
	DWORD dwCharacterID;
};

struct S2C_TALK_MESSAGE : UNDEFINED_SIZE_DOWNWARDS_HEADER
{
    BYTE    byMsgType;
    DWORD   dwTalkerID;
    // 注意,为了减少聊天的带宽占用,byTalkData里面还包括了变长的名字
    BYTE    byTalkData[0];
};

// 精力体力
struct S2C_SYNC_SELF_CURRENT_ST : DOWNWARDS_PROTOCOL_HEADER
{
	int nCurrentStamina;
    int nCurrentThew;
};

// 
struct S2C_DOODAD_LOOT_OVER : DOWNWARDS_PROTOCOL_HEADER
{
	DWORD dwDoodadID;
};
// 好友列表相关
struct S2C_SYNC_FELLOWSHIP_LIST : UNDEFINED_SIZE_DOWNWARDS_HEADER
{
    BYTE    byType;
    BYTE    nFellowshipCount;
    BYTE    byFellowshipList[0];
};

struct S2C_SYNC_FELLOWSHIP_GROUP_NAME : DOWNWARDS_PROTOCOL_HEADER
{
    char    szGroupName[KG_FELLOWSHIP_MAX_CUSTEM_GROUP][_NAME_LEN];
};

// 
struct S2C_NPC_TALK_TO_PLAYER : DOWNWARDS_PROTOCOL_HEADER
{
	DWORD dwDialogID;
	NPC_TALK_ACTION_TYPE eTalkActionType;
	DWORD dwTalkIndex;
	CHARACTER_TALK_TYPE eTalkType;
	DWORD dwTargetType;
	DWORD dwTargetID;
	DWORD dwNpcID;
};

struct S2C_SET_FORCE : DOWNWARDS_PROTOCOL_HEADER
{
	DWORD   dwCharacterID;
	BYTE    byForceID;
};

// - Mail --------------------------------------------------------------->
struct S2C_SEND_MAIL_RESPOND : DOWNWARDS_PROTOCOL_HEADER
{
    BYTE            byRespondID;
    BYTE            byResult;
};

struct S2C_GET_MAIL_LIST_RESPOND : UNDEFINED_SIZE_DOWNWARDS_HEADER
{
    BYTE            byMailCount;
    KMailListInfo   MailListInfo[0];
};

struct S2C_NEW_MAIL_NOTIFY : DOWNWARDS_PROTOCOL_HEADER
{
    KMailListInfo   NewMailListInfo;
};

struct S2C_SYNC_MAIL_CONTENT : UNDEFINED_SIZE_DOWNWARDS_HEADER
{
    DWORD           dwMailID;
    BOOL            byResult;   // Success, mail not found, data not ready.
    BYTE            byData[0];
};

struct S2C_MAIL_GENERAL_RESPOND : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD           dwMailID;
    BOOL            byResult;   // Success, mail not found, data not ready.
};

// <----------------------------------------------------------------------
struct S2C_SYNC_PK_STATE : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    BYTE    byPKState;
    DWORD   dwTargetID;
    BYTE    byRefuseDuel;
    int     nEndFrame;
};

struct S2C_SYNC_FORCE_ID : DOWNWARDS_PROTOCOL_HEADER
{
	DWORD dwForceID;
};

struct S2C_WIN_DUEL_BROADCAST : DOWNWARDS_PROTOCOL_HEADER
{
	DWORD dwWinnerID;
	DWORD dwLosserID;
};

struct S2C_SYNC_USER_PREFERENCES : UNDEFINED_SIZE_DOWNWARDS_HEADER
{
	int nOffset;
	int nLength;
	BYTE byData[0];
};

struct S2C_SYNC_ALL_BOOK_STATE : UNDEFINED_SIZE_DOWNWARDS_HEADER
{
    DWORD   dwPlayerID;
    size_t  uDataLen;
	BYTE    byData[0];
};

struct S2C_SYNC_BOOK_STATE : DOWNWARDS_PROTOCOL_HEADER
{
	DWORD dwBookID;
	BYTE byState;
};

struct S2C_CHARACTER_CHANGE_MODEL : DOWNWARDS_PROTOCOL_HEADER
{
	DWORD dwCharacterID;
	DWORD dwModelID;
};

struct S2C_SYNC_NPC_DIALOG_FLAG : DOWNWARDS_PROTOCOL_HEADER
{
	DWORD dwNpcID;
	BOOL bDialogFlag;
};

struct S2C_SYNC_ROLE_DATA_OVER : DOWNWARDS_PROTOCOL_HEADER
{
};

struct S2C_SYNC_ENABLE_BANK_PACKAGE : DOWNWARDS_PROTOCOL_HEADER
{
	int nEnabledCount;
};

struct S2C_UPDATE_MAP_MARK : DOWNWARDS_PROTOCOL_HEADER
{
	int nX;
	int nY;
	int nZ;
	int nType;
	char szComment[MAX_MAP_MARK_COMMENT_LEN];
};

struct S2C_SYNC_MID_MAP_MARK : DOWNWARDS_PROTOCOL_HEADER
{
	DWORD dwSrcPlayerID;
	int nMap;
	int nX;
	int nY;
	int nType;
	char szComment[MAX_MIDMAP_MARK_COMMENT_LEN];
};

struct S2C_PLAY_SOUND : DOWNWARDS_PROTOCOL_HEADER
{
	DWORD dwSoundID;
};

struct S2C_PLAY_MINI_GAME : DOWNWARDS_PROTOCOL_HEADER
{
	DWORD dwGameID;
};

struct S2C_ADD_ITEM_REF : DOWNWARDS_PROTOCOL_HEADER
{
	DWORD dwSrcBox;
	DWORD dwSrcX;
	DWORD dwX;
};

struct S2C_REMOVE_ITEM_REF : DOWNWARDS_PROTOCOL_HEADER
{
	DWORD dwX;
};

struct S2C_EXCHANGE_ITEM_REF : DOWNWARDS_PROTOCOL_HEADER
{	
	DWORD dwSrcX;
	DWORD dwDstX;
};

struct S2C_SET_ITEM_REF_PARAM : DOWNWARDS_PROTOCOL_HEADER
{
	DWORD dwX;
	DWORD dwIndex;
	int nNewValue;
};

struct S2C_SYNC_HORSE_FLAG : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD dwPlayerID;
    bool  bHorseFlag;
};

struct S2C_ROAD_TRACK_FORCE_RESPOND : UNDEFINED_SIZE_DOWNWARDS_HEADER
{
    BYTE byNodeCount;
    struct KNODE_FORCE
    {
        int     nNodeID;
        BYTE    byCamp;
        BYTE    byEnable;
    } NodeForce[0];
};

struct S2C_SYNC_ROUTE_NODE_OPEN_LIST : UNDEFINED_SIZE_DOWNWARDS_HEADER
{
    BYTE    byNodeCount;
    int     nNodeID[0];
};

struct S2C_SYNC_PLAYER_STATE_INFO : DOWNWARDS_PROTOCOL_HEADER
{
    BYTE    byMoveState;
    WORD    wCurrentTrack;
    int     nMoveFrameCounter;
    int     nFromNode;
    int     nTargetCity;

    int     nExperience;

    int     nCurrentTrainValue;
    int     nUsedTrainValue;

    int     nCurrentPrestige;

    int     nMaxLevel;
    BOOL    bHideHat;

    int     nContribution;
};

struct S2C_SYNC_PRINK_FORCE : DOWNWARDS_PROTOCOL_HEADER
{
    BYTE byPrinkForceID;
    BYTE byLevel;
};

struct S2C_SYNC_VISIT_MAP_INFO : DOWNWARDS_PROTOCOL_HEADER
{
    BYTE byVisitMap[MAX_MAP_ID_DATA_SIZE];
};

struct S2C_SYNC_ACCUMULATE_VALUE : DOWNWARDS_PROTOCOL_HEADER
{
    BYTE byAccumualtevalue;
};

struct S2C_SET_TARGET : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD   dwCharacterID;
    BYTE    byTargetType;
    DWORD   dwTargetID;
};

struct S2C_SYNC_KILL_POINT : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    WORD    wCurrentKillPoint;
};

struct S2C_SET_PLAYER_RED_NAME : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    BYTE    byRedName;
};

struct S2C_SET_PLAYER_DIALOG_FLAG : DOWNWARDS_PROTOCOL_HEADER 
{
    DWORD dwPlayerID;
    BYTE  byDialogFlag;
};

struct S2C_SET_ONLY_REVIVE_IN_SITU : DOWNWARDS_PROTOCOL_HEADER 
{
    DWORD dwPlayerID;
    BYTE  byOnlyReviveInSitu;
};

struct S2C_SYNC_FORMATION_COEFFICIENT : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD dwMemberID;
    int   nCoefficient;
};

struct S2C_JOIN_BATTLE_FIELD_QUEUE_RESPOND : DOWNWARDS_PROTOCOL_HEADER 
{
    DWORD   dwMapID;
    int     nErrorCode;
};

struct S2C_LEAVE_BATTLE_FIELD_QUEUE_RESPOND : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD   dwMapID;
    int     nErrorCode;
};

struct S2C_BATTLE_FIELD_NOTIFY : DOWNWARDS_PROTOCOL_HEADER
{
    time_t                      nAvgQueueTime;
    int                         nPassTime;
    DWORD                       dwMapID;
    int                         nCopyIndex;
    BATTLE_FIELD_NOTIFY_TYPE    eType;
};

struct S2C_SYNC_BATTLE_FIELD_LIST : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD   dwMapID;
    int     nCopyIndex;
};

struct S2C_SYNC_BATTLE_FIELD_SIDE : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    int     nSide;
};

struct S2C_BATTLE_FIELD_END : DOWNWARDS_PROTOCOL_HEADER
{
};

struct S2C_SYNC_CAMP_INFO : DOWNWARDS_PROTOCOL_HEADER
{
    BYTE    byCampLevel;
    int     nCampScore;
    time_t  nNextResetTime;
};

struct S2C_SYNC_CURRENT_PRESTIGE : DOWNWARDS_PROTOCOL_HEADER 
{
    int     nCurrentPrestige;
};

struct S2C_SYNC_TONG_MEMBER_INFO : DOWNWARDS_PROTOCOL_HEADER 
{
    KTongMemberInfo TongMemberInfo;
};

struct S2C_DELETE_TONG_MEMBER_NOTIFY : DOWNWARDS_PROTOCOL_HEADER 
{
    DWORD dwMemberID;
};

struct S2C_APPLY_TONG_INFO_RESPOND : UNDEFINED_SIZE_DOWNWARDS_HEADER
{
    BYTE    byRespondType;
    BYTE    byData[0];
};

struct S2C_UPDATE_TONG_CLIENT_DATA_VERSION : DOWNWARDS_PROTOCOL_HEADER 
{
    BYTE    byFrameType;
    int     nUpdateFrame;
};

struct S2C_SYNC_TONG_REPERTORY_PAGE_RESPOND : UNDEFINED_SIZE_DOWNWARDS_HEADER
{
    BYTE    byPageIndex;
    int     nServerCounter;
    BYTE    byGetRight;
    BYTE    byPutRight;
    BYTE    byUpdateItemCount;
    BYTE    byInvailedItemCount;
    BYTE    byData[0];
};

struct S2C_SYNC_TONG_REPERTORY_PAGE_FRAME : DOWNWARDS_PROTOCOL_HEADER
{
    BYTE    byPageIndex;
    int     nServerFrame;
};

struct S2C_INVITE_PLAYER_JOIN_TONG_REQUEST : DOWNWARDS_PROTOCOL_HEADER 
{
    DWORD dwPlayerID;
    DWORD dwInviterID;
    DWORD dwTongID;
    char  szInviterName[_NAME_LEN];
    char  szTongName[_NAME_LEN];
};

struct S2C_CHANGE_PLAYER_TONG_NOTIFY : DOWNWARDS_PROTOCOL_HEADER 
{
    DWORD   dwTongID;
    BYTE    byReason;
    char    szTongName[_NAME_LEN];
};

struct S2C_TONG_BROADCAST_MESSAGE : UNDEFINED_SIZE_DOWNWARDS_HEADER
{
    BYTE byCode;
    BYTE byData[0];
};

struct S2C_GET_TONG_DESCRIPTION_RESPOND : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD dwTongID;
    char  szTongName[_NAME_LEN];
};

struct S2C_BROADCAST_PLAYER_CHANGE_TONG : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD dwPlayerID;
    DWORD dwTongID;
};

struct S2C_SYNC_TONG_ONLINE_MESSAGE : UNDEFINED_SIZE_DOWNWARDS_HEADER 
{
    char    szOnlineMessage[0];
};

struct S2C_APPLY_OPEN_TONG_REPERTORY_RESPOND : DOWNWARDS_PROTOCOL_HEADER
{
    char    szTongName[_NAME_LEN];
    BYTE    byRepertoryPageNum;
};

struct S2C_SYNC_TONG_HISTORY_RESPOND : UNDEFINED_SIZE_DOWNWARDS_HEADER
{
    BYTE    byType;
    DWORD   dwStartIndex;
    BYTE    byCount;
    BYTE    byData[0];
};
// --------------------------------------------------------------------------
struct S2C_SET_CAMP : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
	BYTE    byCamp;
};

struct S2C_SYNC_BATTLEFIELD_STATISTICS : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    DWORD   dwPlayerForceID;
    int     nBattleFieldSide;
    char    szPlayerName[_NAME_LEN];
    int     nValueArray[psiTotal];
};

// Auction about
struct S2C_AUCTION_LOOKUP_RESPOND : UNDEFINED_SIZE_DOWNWARDS_HEADER 
{
    BYTE                byRespondID;
    BYTE                byCode;
    KAUCTION_PAGE_HEAD  Page;
};

struct S2C_AUCTION_BID_RESPOND : DOWNWARDS_PROTOCOL_HEADER
{
    BYTE byCode;
};

struct S2C_AUCTION_SELL_RESPOND : DOWNWARDS_PROTOCOL_HEADER 
{
    BYTE byCode;
};

struct S2C_AUCTION_CANCEL_RESPOND : DOWNWARDS_PROTOCOL_HEADER 
{
    BYTE byCode;
};

struct S2C_AUCTION_MESSAGE_NOTIFY : DOWNWARDS_PROTOCOL_HEADER 
{
    BYTE    byCode;
    char    szSaleName[SALE_NAME_LEN];
    int     nPrice;
};

struct S2C_SYNC_BATTLEFIELD_OBJECTIVE : DOWNWARDS_PROTOCOL_HEADER
{
    BYTE    byIndex;
    int     nCurrentValue;
    int     nTargetValue;
};

struct S2C_SYNC_BATTLEFIELD_PQ_INFO : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD   dwPQID;
    DWORD   dwPQTemplateID;
    int     nLapseTime;
    int     nLeftTime;
};

struct S2C_SYNC_HERO_FLAG : DOWNWARDS_PROTOCOL_HEADER
{
    BYTE byHeroFlag;
};

struct S2C_SYNC_NPC_DROP_TARGET : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD dwNpcID;
    DWORD dwDropTargetID;
};

struct S2C_REMOTE_LUA_CALL : UNDEFINED_SIZE_DOWNWARDS_HEADER
{
    char    szFunction[_NAME_LEN];
    BYTE    byData[0];
};

struct S2C_SYNC_PLAYER_REVIVE_CTRL : DOWNWARDS_PROTOCOL_HEADER 
{
    int     nReviveFrame;
    BOOL    bReviveInSitu;
    BOOL    bReviveInAltar;
    BOOL    bReviveByPlayer;
    DWORD   dwReviver;
    int     nMessageID;
};

struct S2C_SYNC_ACHIEVEMENT_DATA : UNDEFINED_SIZE_DOWNWARDS_HEADER 
{
    DWORD   dwPlayerID;
    size_t  uDataLen;
    BYTE    byData[0];
};

struct S2C_SYNC_DESIGNATION_DATA : UNDEFINED_SIZE_DOWNWARDS_HEADER
{
    size_t  uDataLen;
    BYTE    byData[0];
};

struct S2C_SET_GENERATION : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    BYTE    byGenerationIndex;
    int     nNameInForceIndex;
};

struct S2C_ACQUIRE_DESIGNATION : DOWNWARDS_PROTOCOL_HEADER
{
    BYTE    byPrefix;
    BYTE    byPostfix;
};

struct S2C_DESIGNATION_ANNOUNCE : DOWNWARDS_PROTOCOL_HEADER
{
    char    szRoleName[ROLE_NAME_LEN];
    BYTE    byType;
    BYTE    byPrefix;
    BYTE    byPostfix;
};

struct S2C_REMOVE_DESIGNATION : DOWNWARDS_PROTOCOL_HEADER
{
    BYTE    byPrefix;
    BYTE    byPostfix;
};

struct S2C_SYNC_PLAYER_DESIGNATION : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD   dwPlayerID;
    BYTE    byPrefix;
    BYTE    byPostfix;
    BYTE    byGenerationIndex;
    WORD    wByname;
    bool    bDisplayFlag;
};

struct S2C_NEW_ACHIEVEMENT_NOTIFY : DOWNWARDS_PROTOCOL_HEADER 
{
    int    nAchievementID;
};

struct S2C_ACHIEVEMENT_ANNOUNCE_NOTIFY : DOWNWARDS_PROTOCOL_HEADER 
{
    char    szRoleName[ROLE_NAME_LEN];
    BYTE    byType;
    int     nAchievementID;
};

struct S2C_SYNC_ACHIEVEMENT_POINT : DOWNWARDS_PROTOCOL_HEADER 
{
    int     nDeltaPoint;
};

struct S2C_SYNC_ACHIEVEMENT_COUNT : DOWNWARDS_PROTOCOL_HEADER 
{
    int     nID;
    int     nDeltaCount;
};

struct S2C_SYNC_MAX_LEVEL : DOWNWARDS_PROTOCOL_HEADER
{
    int     nMaxLevel;
};

struct S2C_USE_ITEM_PREPARE : DOWNWARDS_PROTOCOL_HEADER 
{
    DWORD   dwPlayerID;
    int     nFrames;
    DWORD   dwOTAniID;
    DWORD   dwEndAniID;
    char    szText[USE_ITEM_PROGRESS_NAME_LEN];
};

// 观察点相关
struct S2C_CREATE_VIEW_POINT_RESPOND : DOWNWARDS_PROTOCOL_HEADER
{
    int     nRegionX;
    int     nRegionY;
};

struct S2C_REMOVE_VIEW_POINT_RESPOND : DOWNWARDS_PROTOCOL_HEADER
{
};

struct S2C_MOVE_VIEW_POINT_RESPOND : DOWNWARDS_PROTOCOL_HEADER
{
    int     nRegionX;
    int     nRegionY;
};

struct S2C_ACCOUNT_END_OF_DAY_TIME : DOWNWARDS_PROTOCOL_HEADER 
{
    int     nLeftTime;
};

struct S2C_SYNC_FREE_LIMIT_FLAG_INFO : DOWNWARDS_PROTOCOL_HEADER
{
    BYTE byFreeLimitFlag;
};

struct S2C_APEX_PROTOCOL : UNDEFINED_SIZE_DOWNWARDS_HEADER
{
    size_t nSize;
    BYTE   byData[0];
};

struct S2C_GAME_CARD_SELL_RESPOND : DOWNWARDS_PROTOCOL_HEADER 
{
    BYTE    byCode;
};

struct S2C_GAME_CARD_BUY_RESPOND : DOWNWARDS_PROTOCOL_HEADER 
{
    BYTE    byCode;
};

struct S2C_GAME_CARD_LOOKUP_RESPOND : UNDEFINED_SIZE_DOWNWARDS_HEADER
{
    int         nTotalCount;
    int         nCount;
    KGAME_CARD  CardList[0];
};

struct S2C_GAME_CARD_CANCEL_RESPOND : DOWNWARDS_PROTOCOL_HEADER 
{
    BYTE    byCode;
};

struct S2C_SYNC_COIN : DOWNWARDS_PROTOCOL_HEADER 
{
    int nCoin;
};

struct S2C_SEEK_MENTOR_YELL : DOWNWARDS_PROTOCOL_HEADER 
{
    char szPlayerName[_NAME_LEN];
    char szTongName[_NAME_LEN];
    BYTE byForceID;
    BYTE byRoleLevel;
    BYTE byRoleType;
};

struct S2C_SEEK_APPRENTICE_YELL : DOWNWARDS_PROTOCOL_HEADER 
{
    char szPlayerName[_NAME_LEN];
    char szTongName[_NAME_LEN];
    BYTE byForceID;
    BYTE byRoleLevel;
    BYTE byRoleType;
};

struct S2C_SYNC_MENTOR_DATA : DOWNWARDS_PROTOCOL_HEADER 
{
    DWORD dwMentor;
    DWORD dwApprentice;
    int   nValue;
    BYTE  byState;
};

struct S2C_DELETE_MENTOR_DATA : DOWNWARDS_PROTOCOL_HEADER 
{
    DWORD dwMentor;
    DWORD dwApprentice;
};

struct S2C_SYNC_CAMP_FLAG : DOWNWARDS_PROTOCOL_HEADER
{
    DWORD dwPlayerID;
    BYTE  byCampFlag;
};

#define MAX_THREAT_RANKLIST_COUNT 32

struct S2C_CHARACTER_THREAT_RANKLIST : UNDEFINED_SIZE_DOWNWARDS_HEADER
{
    DWORD   dwThreatListOwnerID;
    WORD    wCount;
    struct _THREAT_RANK_LIST 
    {
        DWORD   dwCharacterID;
        WORD    wThreatRank;
    } RankList[0];
};

//AutoCode:GS 2 Client Struct End

/************************************************************************/
//Client 2 GS Struct Begin

struct C2S_HANDSHAKE_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    DWORD   dwRoleID; 
    GUID	Guid;
};

struct C2S_APPLY_ENTER_SCENE : UPWARDS_PROTOCOL_HEADER
{
    time_t nSceneTimeStamp;
};

// 玩家登出
struct C2S_PLAYER_LOGOUT : UPWARDS_PROTOCOL_HEADER
{
};

struct C2S_PING_SIGNAL : UPWARDS_PROTOCOL_HEADER
{
    DWORD dwTime;
};

struct C2S_MOVE_CTRL : UPWARDS_PROTOCOL_HEADER
{
    bool                    bMove;
    bool                    bWalk;
    BYTE                    byDirection8;
    int8_t                  nTurn;
    int                     nMoveCount;
    KMOVE_CRITICAL_PARAM    Param;
};

struct C2S_APPLY_MOVE_ADJUST : UPWARDS_PROTOCOL_HEADER
{
};

struct C2S_CHARACTER_STAND : UPWARDS_PROTOCOL_HEADER
{
    int                     nMoveCount;
    KMOVE_CRITICAL_PARAM    Param;
};

struct C2S_CHARACTER_JUMP : UPWARDS_PROTOCOL_HEADER
{
    bool                    bStandJump;
    BYTE                    byJumpDirection;
    BYTE	                byFaceDirection;
    int                     nMoveCount;
    KMOVE_CRITICAL_PARAM    Param;
};

struct C2S_CHARACTER_SIT :  UPWARDS_PROTOCOL_HEADER
{
    int                     nMoveCount;
    KMOVE_CRITICAL_PARAM    Param;
};

struct C2S_SYNC_DIRECTION : UPWARDS_PROTOCOL_HEADER
{
    BYTE	                byFaceDirection;
    BYTE                    byPitchDirection;
    int                     nMoveCount;
    KMOVE_CRITICAL_PARAM    Param;
};

// 玩家的交互动作上传指令
struct C2S_CHARACTER_ACTION : UPWARDS_PROTOCOL_HEADER
{
    DWORD	dwCharacterID;
    DWORD	dwAction;
};

// 玩家显示数据
struct C2S_APPLY_PLAYER_DISPLAY_DATA : UPWARDS_PROTOCOL_HEADER
{
    DWORD	dwPlayerID;
    DWORD	dwCheckSum;
};

struct C2S_STOP_CURRENT_ACTION : UPWARDS_PROTOCOL_HEADER
{

};

// ------------------ skill about protocol ----------------->

//角色攻击上传指令
struct C2S_CHARACTER_SKILL : UPWARDS_PROTOCOL_HEADER
{
    DWORD	dwSkillID;			//技能ID
    BYTE	bySkillLevel;		//技能等级
    BYTE	byTargetType;
    int		nParam1;	        //当TARGET_TYPE类型是坐标时,坐标值为(nParam1, nParam2, nParam3)
    int		nParam2;            //当类型为xxID时,nParam1为ID值,nParam2没意义
    int     nParam3;
};

struct C2S_MOUNT_KUNGFU :  UPWARDS_PROTOCOL_HEADER
{
    DWORD dwID;
    DWORD dwLevel;
};

struct C2S_CANCEL_BUFF : UPWARDS_PROTOCOL_HEADER
{
    int nIndex;
};

struct C2S_SET_SHEATH_STATE :  UPWARDS_PROTOCOL_HEADER
{
    bool bSheathFlag;
};

struct C2S_APPLY_PLAYER_BUFFLIST :  UPWARDS_PROTOCOL_HEADER
{
    DWORD dwPlayerID;
};

struct C2S_SET_HIDE_HAT_FLAG : UPWARDS_PROTOCOL_HEADER
{
    bool bHideHat;
};

// <------------------ skill about protocol -----------------


// ----------------- party about protocol ----------------->

// xxx邀请xxx组队
struct C2S_INVITE_JOIN_TEAM_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    char szInvitedPlayer[_NAME_LEN]; // 邀请该玩家组队
};

// xxx申请加入xxx的队伍
struct C2S_APPLY_JOIN_TEAM_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    char  szApplyDst[_NAME_LEN]; // 申请加入这个玩家的队伍
};

// 客户端收到组队邀请后的应答
struct C2S_INVITE_JOIN_TEAM_RESPOND : UPWARDS_PROTOCOL_HEADER
{
    char  szInviteSrc[_NAME_LEN]; // 发出组队请求的玩家    
    BOOL  bAgreeFlag;
};

// 客户端(队长)收到入队申请后的应答
struct C2S_APPLY_JOIN_TEAM_RESPOND : UPWARDS_PROTOCOL_HEADER
{
    char  szApplySrc[_NAME_LEN]; // 发出入队申请的玩家
    BOOL  bAgreeFlag;
};

struct C2S_TEAM_DEL_MEMBER_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    DWORD dwMemberID;
};

struct C2S_TEAM_CHANGE_AUTHORITY_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    BYTE  byType;
    DWORD dwNewLeaderID;
};

struct C2S_TEAM_SET_LOOT_MODE_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    int nLootMode;
};

struct C2S_TEAM_SET_ROLL_QUALITY_REQUEST : UPWARDS_PROTOCOL_HEADER
{
	int nRollQuality;
};

struct C2S_TEAM_SET_FORMATION_LEADER_REQUEST : UPWARDS_PROTOCOL_HEADER
{
	DWORD dwNewFormationLeaderID;
    int   nGroupIndex;
};

struct  C2S_TEAM_MEMBER_NOTIFY_SIGNPOST_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    int   nX;
    int   nY;
};

struct C2S_TEAM_SET_MARK_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    int     nMarkType;
    DWORD   dwTargetID;
};

struct C2S_TEAM_LEVEL_UP_RAID_REQUEST : UPWARDS_PROTOCOL_HEADER
{
};

struct C2S_TEAM_CHANGE_MEMBER_GROUP_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    DWORD dwMemberID;
    int   nDstGroupIndex;
    DWORD dwDstMemberID;
};

// <----------------- party about protocol -----------------

// 接受任务
struct C2S_ACCEPT_QUEST : UPWARDS_PROTOCOL_HEADER
{
    BYTE	byTargetType;
    DWORD	dwTargetID;
    DWORD	dwQuestID;
};

//完成任务
struct C2S_FINISH_QUEST : UPWARDS_PROTOCOL_HEADER
{
    DWORD	dwQuestID;
	DWORD	dwTargetType;
	DWORD	dwTargetID;
    int		nPresentChoice1;
    int		nPresentChoice2;
};

//取消任务
struct C2S_CANCEL_QUEST : UPWARDS_PROTOCOL_HEADER
{
    int		nQuestIndex;
};

// 共享任务
struct C2S_SHARE_QUEST : UPWARDS_PROTOCOL_HEADER
{
    int		nQuestIndex;
};

struct C2S_ACCEPT_ESCORT_QUEST : UPWARDS_PROTOCOL_HEADER
{
	DWORD dwStartPlayerID;
	DWORD dwQuestID;
};

//GM指令
struct C2S_GM_COMMAND : UNDEFINED_SIZE_UPWARDS_HEADER
{
    char	szGmCommand[0];
};

// ----------------- shop about protocol ----------------->


// 请求同步商店物品列表，注意，当服务端返回商店基本信息的时候，客户端就可以打开商店界面了，后面同步物品是
// 一件一件的同步的，并不存在一个标志说“物品同步完毕”

struct C2S_OPEN_SHOP_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    DWORD dwShopID;
};

struct C2S_QUERY_SHOP_ITEMS : UPWARDS_PROTOCOL_HEADER
{
    DWORD dwShopID;    
    BYTE  byPageIndex;
    struct SHOP_SYNC_ITEM
    {
        BYTE  byPosIndex;
        DWORD dwItemID;
        int   nCount;
    } ShopPageItems[MAX_SHOP_PAGE_ITEM_COUNT];
};

struct C2S_SHOP_BUY_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    DWORD dwShopID;
    DWORD dwItemID;
    int   nCount;
    int   nCost;
    BYTE  byPageIndex;
    BYTE  byPosIndex; 
};

struct C2S_SHOP_SELL_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    DWORD dwShopID;
    DWORD dwItemID;
    int   nCost;
    DWORD dwBoxIndex;
    DWORD dwPosIndex;
};

struct C2S_SHOP_REPAIR_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    DWORD dwShopID;
    DWORD dwItemID;     // 当该值为ERROR_ID(0)时,代表修理身上和包包里所有的装备
    int   nCost;
    DWORD dwBoxIndex;
    DWORD dwPosIndex;
};

struct C2S_SOLD_LIST_BUY_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    DWORD dwShopID;
    DWORD dwItemID;
    DWORD dwX;
};

// <----------------- shop about protocol -----------------

// ------------- Trading about ------------------->
struct C2S_TRADING_INVITE_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    DWORD dwInviteDst;
};

struct C2S_TRADING_INVITE_RESPOND : UPWARDS_PROTOCOL_HEADER
{
    bool bAccept;
};

struct C2S_TRADING_ADD_ITEM : UPWARDS_PROTOCOL_HEADER
{
    BYTE byBoxIndex;
    BYTE byPosIndex;
    BYTE byGridIndex;
};

struct C2S_TRADING_DELETE_ITEM : UPWARDS_PROTOCOL_HEADER
{
    BYTE byGridIndex;
};

struct C2S_TRADING_SET_MONEY : UPWARDS_PROTOCOL_HEADER
{
    int nMoney;
};

struct C2S_TRADING_CONFIRM : UPWARDS_PROTOCOL_HEADER
{
    bool bConfirm;
    int  nKey;
};

// <-------------Trading about --------------------

struct C2S_REQUEST_TARGET : UPWARDS_PROTOCOL_HEADER
{
    BYTE    byTargetType;
    DWORD   dwTargetID;   // Target只能是Player, NPC, Doodad.
};


// 申请交换装备
struct C2S_APPLY_EXCHANGE_ITEM : UPWARDS_PROTOCOL_HEADER
{
    BYTE	byBox1;
    BYTE	byX1;
    BYTE	byBox2;
    BYTE	byX2;
    WORD	wAmount;
};


// 选择窗口选项
struct C2S_WINDOW_SELECT : UPWARDS_PROTOCOL_HEADER
{
    DWORD	dwIndex;
    BYTE	bySelect;
};


// 配方使用协议
struct C2S_CAST_PROFESSION_SKILL : UPWARDS_PROTOCOL_HEADER
{
	DWORD	dwCraftID;
    DWORD	dwRecipeID;
    BYTE	byTargetType;
	DWORD	dwRBookItemID;
    int		nParam1;
    int		nParam2;
};

struct C2S_LOOT_ITEM : UPWARDS_PROTOCOL_HEADER
{
    DWORD	dwDoodadID;
    DWORD	dwItemID;
};

struct C2S_ROLL_ITEM : UPWARDS_PROTOCOL_HEADER
{
    DWORD	dwDoodadID;
    DWORD	dwItemID;
    BOOL	bCancel;
};

// 申请拾取列表
struct C2S_APPLY_LOOT_LIST : UPWARDS_PROTOCOL_HEADER
{
    DWORD	dwDoodadID;
};


// 打开
struct C2S_CHARACTER_OPEN : UPWARDS_PROTOCOL_HEADER
{
    DWORD	dwDoodadID;
};

// 申请使用道具
struct C2S_APPLY_USE_ITEM : UPWARDS_PROTOCOL_HEADER
{
    BYTE	byBox;
    BYTE	byX;
    BYTE	byTargetType;
    int	    nParam1;			    //如果TargetType不是坐标，则这里表示ID
    int	    nParam2;
    int		nParam3;
};


// 改变战斗开关
struct C2S_APPLY_FIGHT_FLAG : UPWARDS_PROTOCOL_HEADER
{
	BYTE	byForceID;
	BYTE	byOpen;
};


// 结束拾取
struct C2S_FINISH_LOOT : UPWARDS_PROTOCOL_HEADER
{
	DWORD dwDoodadID;
};


// 拾取金钱
struct C2S_LOOT_MONEY : UPWARDS_PROTOCOL_HEADER
{
	DWORD dwDoodadID;
};

// 改变PK状态
struct C2S_CHANGE_PK_MODE : UPWARDS_PROTOCOL_HEADER
{
	BYTE byPKMode;
};

// 分配物品
struct C2S_DISTRIBUTE_ITEM : UPWARDS_PROTOCOL_HEADER
{
	DWORD dwDoodadID;
	DWORD dwItemID;
	DWORD dwDstPlayerID;
};

struct C2S_TALK_MESSAGE : UNDEFINED_SIZE_UPWARDS_HEADER
{
    BYTE  byMsgType;
    char  szReceiver[_NAME_LEN];
    BYTE  byTalkData[0];
};

// 好友列表相关
struct C2S_GET_FELLOWSHIP_LIST_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    BYTE    byType; // 1: Friend, 2: Foe, 3: BlackList
};

struct C2S_ADD_FELLOWSHIP_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    char    szAlliedPlayerName[_NAME_LEN];
    BYTE    byType; // 1: Friend, 2: Foe, 3: BlackList
};

struct C2S_DEL_FELLOWSHIP_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    DWORD   dwAlliedPlayerID;
    BYTE    byType; // 1: Friend, 2: Foe, 3: BlackList
};

struct C2S_ADD_FELLOWSHIP_GROUP_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    char szGroupName[_NAME_LEN];
};

struct C2S_DEL_FELLOWSHIP_GROUP_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    DWORD dwGroupID;
};

struct C2S_RENAME_FELLOWSHIP_GROUP_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    DWORD dwGroupID;
    char szGroupName[_NAME_LEN];
};

struct C2S_SET_FELLOWSHIP_REMARK : UPWARDS_PROTOCOL_HEADER
{
    DWORD dwAlliedPlayerID;
    char szRemark[_NAME_LEN];
};

struct C2S_SET_FELLOWSHIP_GROUP : UPWARDS_PROTOCOL_HEADER
{
    DWORD dwAlliedPlayerID;
    DWORD dwGroupID;
};

struct C2S_SEND_MAIL_REQUEST : UNDEFINED_SIZE_UPWARDS_HEADER
{
    DWORD       dwNpcID;
    BYTE        byRequestID;
    char        szDstName[_NAME_LEN];
    char        szTitle[_NAME_LEN];
    int         nMoney;
    BYTE        byBox[KMAIL_MAX_ITEM_COUNT];        // 邮寄物品所在的包裹
    BYTE        byX[KMAIL_MAX_ITEM_COUNT];          // 邮寄物品所在包裹里的位置
    int         nItemPrice[KMAIL_MAX_ITEM_COUNT];   // 货到付款的价格
    WORD        wTextLen;     
    char        szText[0];                          // 信件文本内容
};

struct C2S_GET_MAILLIST_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    DWORD dwStartID;
};

struct C2S_QUERY_MAIL_CONTENT : UPWARDS_PROTOCOL_HEADER
{
    DWORD   dwNpcID;
    DWORD   dwMailID;
    BYTE    byMailType;
};

struct C2S_ACQUIRE_MAIL_MONEY_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    DWORD       dwMailID;
};

struct C2S_ACQUIRE_MAIL_ITEM_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    DWORD       dwMailID;
    BYTE        byIndex;
};

struct C2S_SET_MAIL_READ : UPWARDS_PROTOCOL_HEADER
{
    DWORD   dwMailID;
};

struct C2S_DELETE_MAIL : UPWARDS_PROTOCOL_HEADER
{
    DWORD   dwMailID;
};

struct C2S_RETURN_MAIL : UPWARDS_PROTOCOL_HEADER
{
    DWORD   dwMailID;
};

struct C2S_APPLY_PK_OPERATE : UPWARDS_PROTOCOL_HEADER
{
	BYTE  byPKOperate;
	DWORD dwParam1;
	DWORD dwParam2;
};

struct C2S_SYNC_USER_PREFERENCES : UNDEFINED_SIZE_UPWARDS_HEADER
{
	int     nOffset;
	WORD    wDataLen;
	BYTE    byData[0];
};

struct C2S_SET_BANK_OPENED_FLAG : UPWARDS_PROTOCOL_HEADER
{
    BYTE  byBankOpend;
	DWORD dwNpcID;
};

struct C2S_ENABLE_BANK_PACKAGE : UPWARDS_PROTOCOL_HEADER
{
};

struct C2S_SYNC_MID_MAP_MARK : UPWARDS_PROTOCOL_HEADER
{
	int  nMapID;
	int  nX;
	int  nY;
	int  nType;
	char szComment[MAX_MIDMAP_MARK_COMMENT_LEN];
};

struct C2S_PLAYER_LEARN_SKILL : UPWARDS_PROTOCOL_HEADER
{
	DWORD dwSkillID;
	DWORD dwNpcID;
};

struct C2S_PLAYER_LEARN_RECIPE : UPWARDS_PROTOCOL_HEADER
{
	DWORD dwCraftID;
	DWORD dwRecipeID;
	DWORD dwNpcID;
};

struct C2S_PLAYER_ACTIVE_SKILL_RECIPE : UPWARDS_PROTOCOL_HEADER
{
    DWORD dwRecipeKey;
    BOOL bActive;
};

struct C2S_PEEK_OTHER_PLAYER_EQUIP : UPWARDS_PROTOCOL_HEADER
{
    DWORD dwPlayerID;
};

struct C2S_PEEK_OTHER_PLAYER_BOOK : UPWARDS_PROTOCOL_HEADER
{
    DWORD dwPlayerID;
};

struct C2S_PEEK_OTHER_PLAYER_QUEST : UPWARDS_PROTOCOL_HEADER
{
    DWORD dwPlayerID;
};

struct C2S_ROAD_TRACK_START_OUT : UPWARDS_PROTOCOL_HEADER
{
    int     nFromNode;
    int     nTargetCityID;
    int     nCost;
};

struct C2S_ROAD_TRACK_FORCE_REQUEST : UPWARDS_PROTOCOL_HEADER
{
};

struct C2S_OPEN_VENATION : UPWARDS_PROTOCOL_HEADER
{
    int nVenationID;
};

struct C2S_SEND_GM_MESSAGE : UNDEFINED_SIZE_UPWARDS_HEADER
{
    char szMessage[0];
};

struct C2S_JOIN_BATTLE_FIELD_QUEUE_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    DWORD   dwNpcID;
    DWORD   dwMapID;
    int     nCopyIndex;
    DWORD   dwGroupID;
    BOOL    bTeamJoin;
};

struct C2S_LEAVE_BATTLE_FIELD_QUEUE_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    DWORD   dwMapID;
};

struct C2S_ACCEPT_JOIN_BATTLE_FIELD : UPWARDS_PROTOCOL_HEADER
{
    DWORD   dwMapID;
    int     nCopyIndex;
};

struct C2S_GET_BATTLE_FIELD_LIST : UPWARDS_PROTOCOL_HEADER
{
    DWORD dwMapID;
};

struct C2S_LEAVE_BATTLE_FIELD : UPWARDS_PROTOCOL_HEADER
{
};

// 帮会相关

struct C2S_APPLY_TONG_ROSTER_REQUEST : UNDEFINED_SIZE_UPWARDS_HEADER
{
    int     nLastUpdateFrame;
    int     nMemberCount;
    DWORD   dwMemberList[0];
};

struct C2S_APPLY_TONG_INFO_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    int     nLastUpdateFrame;
};

struct C2S_APPLY_TONG_REPERTORY_PAGE_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    BYTE    byPageIndex;
    int     nLastUpdateCounter;
};

struct C2S_INVITE_PLAYER_JOIN_TONG_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    char    szNewMemberName[_NAME_LEN];
};

struct C2S_INVITE_PLAYER_JOIN_TONG_RESPOND : UPWARDS_PROTOCOL_HEADER
{
    DWORD   dwInviterID;
    DWORD   dwTongID;
    BYTE    byAccept;
};

struct C2S_APPLY_KICK_OUT_TONG_MEMBER_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    DWORD dwMemberID;
};

struct C2S_MODIFY_TONG_INFO_REQUEST : UNDEFINED_SIZE_UPWARDS_HEADER
{
    BYTE byInfoType;
    WORD wDataLen;
    BYTE byData[0];
};

struct C2S_MODIFY_TONG_SCHEMA_REQUEST : UNDEFINED_SIZE_UPWARDS_HEADER
{
    BYTE byGroupIndex;
    BYTE byModifyType;
    BYTE byData[0];
};

struct C2S_APPLY_QUIT_TONG_REQUEST : UPWARDS_PROTOCOL_HEADER
{
};

struct C2S_CHANGE_TONG_MEMBER_GROUP_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    DWORD dwTargetMemberID;
    BYTE  byTargetGroup;
};

struct C2S_CHANGE_TONG_MASTER_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    DWORD dwNewMasterID;
};

struct C2S_CHANGE_TONG_MEMBER_REMARK_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    DWORD dwTargetMemberID;
    char  szRemark[_NAME_LEN];
};

struct C2S_GET_TONG_DESCRIPTION_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    DWORD dwTongID;
};

struct C2S_SAVE_MONEY_IN_TONG_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    int nMoney;
};

struct C2S_PAY_TONG_SALARY_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    int nTotalSalary;
};

struct C2S_GET_TONG_SALARY_REQUEST : UPWARDS_PROTOCOL_HEADER
{

};

struct C2S_APPLY_OPEN_TONG_REPERTORY_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    DWORD dwNpcID;
};

struct C2S_TAKE_TONG_REPERTORY_ITEM_TO_POS_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    BYTE    byPageIndex;
    BYTE    byPagePos;
    BYTE    byBoxIndex;
    BYTE    byBoxPos;
    int     nLastUpdateCounter;
};

struct C2S_TAKE_TONG_REPERTORY_ITEM_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    BYTE    byPageIndex;
    BYTE    byPagePos;
    int     nLastUpdateCounter;
};

struct C2S_PUT_TONG_REPERTORY_ITEM_TO_POS_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    BYTE    byBoxIndex;
    BYTE    byBoxPos;
    BYTE    byPageIndex;
    BYTE    byPagePos;
};

struct C2S_PUT_TONG_REPERTORY_ITEM_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    BYTE    byBoxIndex;
    BYTE    byBoxPos;
    BYTE    byPageIndex;
};

struct C2S_EXCHANGE_TONG_REPERTORY_ITEM_POS_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    BYTE    bySrcPageIndex;
    BYTE    byDstPageIndex;
    BYTE    bySrcPagePos;
    BYTE    byDstPagePos;
    int     nSrcPageLastUpdateCounter;
    int     nDstPageLastUpdateCounter;
};

struct C2S_STACK_TONG_REPERTORY_ITEM_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    BYTE    byPageIndex;
    BYTE    byPagePos;
    BYTE    byBoxIndex;
    BYTE    byBoxPos;
    WORD    wStackNum;
    int     nLastUpdateCounter;
};

//
struct C2S_APPLY_BATTLEFIELD_STATISTICS : UPWARDS_PROTOCOL_HEADER 
{
};

struct C2S_SET_HERO_FLAG : UPWARDS_PROTOCOL_HEADER
{
    BYTE byHeroFlag;
};

// 寄卖行相关
struct C2S_AUCTION_LOOKUP_REQUEST : UPWARDS_PROTOCOL_HEADER 
{
    DWORD                   dwNpcID;
    BYTE                    byRequestID;
    KAUCTION_LOOKUP_PARAM   Param;
};

struct C2S_AUCTION_BID_REQUEST : UPWARDS_PROTOCOL_HEADER 
{
    DWORD   dwNpcID;
    DWORD   dwSaleID;
    DWORD   dwCRC;
    int     nPrice;
};

struct C2S_AUCTION_SELL_REQUEST : UPWARDS_PROTOCOL_HEADER 
{
    DWORD   dwNpcID;
    BYTE    byBox;
    BYTE    byX;
    int     nStartPrice;
    int     nBuyItNowPrice;
    BYTE    byLeftHour;
};

struct C2S_AUCTION_CANCEL_REQUEST : UPWARDS_PROTOCOL_HEADER 
{
    DWORD   dwNpcID;
    DWORD   dwSaleID;
};

struct C2S_APPLY_ACHIEVEMENT_DATA_REQUEST : UPWARDS_PROTOCOL_HEADER 
{
    DWORD   dwPlayerID;
};

struct C2S_APPLY_SET_CAMP_REQUEST : UPWARDS_PROTOCOL_HEADER 
{
    BYTE byCamp;
};

struct C2S_REMOTE_LUA_CALL : UNDEFINED_SIZE_UPWARDS_HEADER
{
    char    szFunction[_NAME_LEN];
    size_t  uDataLen;
    BYTE    byData[0];
};

struct C2S_PLAYER_REVIVE_REQUEST : UPWARDS_PROTOCOL_HEADER 
{
    int nReviveCode;
};

struct C2S_QUERY_PRODUCT_IDENTITY : UPWARDS_PROTOCOL_HEADER 
{
    int nMagic;
};

struct C2S_SET_CURRENT_DESIGNATION_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    BYTE byPrefix;
    BYTE byPostfix;
    BYTE byDisplayFlag;
};

// 观察点相关
struct C2S_CREATE_VIEW_POINT_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    int nX;
    int nY;
    int nLifeFrame;
};

struct C2S_REMOVE_VIEW_POINT_REQUEST : UPWARDS_PROTOCOL_HEADER
{
};

struct C2S_MOVE_VIEW_POINT_REQUEST : UPWARDS_PROTOCOL_HEADER
{
    int nX;
    int nY;
};

struct C2S_APEX_PROTOCOL : UNDEFINED_SIZE_UPWARDS_HEADER
{
    size_t  nSize;
    BYTE    byIsUserData;
    BYTE    byData[0];
};

struct C2S_GAME_CARD_SELL_REQUEST : UPWARDS_PROTOCOL_HEADER 
{
    DWORD   dwNpcID;
    int     nTypeIndex;
    int     nPrice;
    int     nDurationTime;
};

struct C2S_GAME_CARD_BUY_REQUEST : UPWARDS_PROTOCOL_HEADER 
{
    DWORD   dwNpcID;
    DWORD   dwID;
    int     nBuyPrice;
};

struct C2S_GAME_CARD_LOOKUP_REQUEST : UPWARDS_PROTOCOL_HEADER 
{
    DWORD   dwNpcID;
    BYTE    byCardType;
    int     nStartIndex;
    BYTE    byOrderType;
    BOOL    bDesc;
};

struct C2S_GAME_CARD_CANCEL_REQUEST : UPWARDS_PROTOCOL_HEADER 
{
    DWORD   dwNpcID;
    DWORD   dwID;
};

struct C2S_APPLY_CHARACTER_THREAT_RANKLIST : UPWARDS_PROTOCOL_HEADER
{
    DWORD   dwCharacterID;
};

//AutoCode:Client 2 GS Struct End
#pragma pack()

#endif	//_GS_CLIENT_PROTOCOL_H_
