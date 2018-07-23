//-------------------------------------------------------------------------
//	月影传说网络版	GMC_SDK
//	版权所有:			2010 金山软件(Kingsoft)
//	创建日期与作者:	2010-1 Golton Gao
//-------------------------------------------------------------------------
#ifndef __I_GMC_CLIENT_H__
#define __I_GMC_CLIENT_H__

// 游戏世界应当实现的接口
struct IGameSpaceLogicForGmc
{
	//
	// 发布公告
	// 输入参数	szNotice -- 公告内容
	//				szOption -- 公告选项，当前取值范围：
	//						 ""			 -- 空字符串，表示一般公告
	//						 "IMPORTANT" -- 表示重要公告
	//						 "NEWS"		 -- 表示新闻公告
	// 返回参数	true	-- 发布公告成功
	//				false	-- 发布公告失败
	virtual bool BroadcastNotice(const char* szNotice, const char* szOption) = 0;

	//
	// 密聊角色
	// 输入参数	szRole	-- 玩家角色名
	//				szMsg	-- 密聊的消息内容
	// 返回参数	true	-- 密聊成功 
	//				false	-- 密聊失败
	virtual bool ChatToPlayerByRole(const char* szRole, const char* szMsg) = 0;

	//
	// 密聊账号
	// 输入参数	szAcc	-- 玩家账户名
	//				szMsg	-- 密聊的消息内容
	// 返回参数	true	-- 密聊成功
	//				false	-- 密聊失败
	virtual bool ChatToPlayerByAccount(const char* szAcc, const char* szMsg) = 0;

	// 
	// 踢除玩家（根据角色）
	// 输入参数	szRole	-- 玩家角色名
	// 返回参数	true	-- 踢除成功
	//				false	-- 踢除失败
	virtual bool KickPlayerByRole(const char* szRole) = 0;

	// 
	// 踢除玩家（根据账号）
	// 输入参数	szAcc	-- 玩家账号名
	// 返回参数	true	-- 踢除成功
	//				false	-- 踢除失败
	virtual bool KickPlayerByAccount(const char* szAccount) = 0;

	//
	// 瞬移玩家
	// 输入参数	szRole	-- 玩家角色名
	//				nMapId	-- 目的地的地图ID
	//				nX		-- 目的地的X坐标
	//				nY		-- 目的地的Y坐标
	//				nZ		-- 目的地的Z坐标
	// 返回参数	true	-- 瞬移成功
	//				false	-- 瞬移失败
	virtual bool MovePlayerToLocationByRole(const char* szRole, int nMapId, int nX, int nY, int nZ) = 0;

	//
	// 瞬移玩家到目标角色身边
	// 输入参数	szRole			-- 玩家角色名
	//				szTargetRole	-- 目的角色
	// 返回参数	true			-- 瞬移成功
	//				false			-- 瞬移失败
	virtual bool MovePlayerToPlayerByRole(const char* szRole, const char* szTargetRole) = 0;

	//
	// 控制玩家发言行为
	// 输入参数	szRole	-- 玩家角色名
	//				bAllow	-- true则允许玩家发言; false则禁止玩家发言
	// 返回参数	true	-- 控制成功
	//				false	-- 控制失败
	virtual bool ControlTalkBehaviorByRole(const char* szRole, bool bAllow) = 0;
};

struct IGmcClient
{
	virtual void Release() = 0;

	virtual bool Initialize() = 0;
	virtual void Terminate() = 0;
	virtual void Tick() = 0;

	//
	// 发送与GM的聊天消息
	// 输入参数	szAcc		--	玩家账号
	//				szRole		--	玩家角色名
	//				szChatType	--	聊天类型，便于分类，以下是举例，不同的游戏可以做扩展
	//								"Accuse-trick"	不良信息
	//								"Accuse-treat"	外挂
	//								"Chock-none"	卡号
	//								"Helpme-none"	人工求助回复
	//				szMsg		--	聊天的具体内容
	virtual bool SendChatMsg(const char* szAcc, const char* szRole, const char* szChatType, const char* szMsg) = 0;

	virtual void SetGameSpaceLogicForGmc(IGameSpaceLogicForGmc* pGameSpaceLogic) = 0;
};

//=== 外部引用该头文件时，给出接口声明 ===//
#ifndef  GMC_CLIENT_INTERNAL_SIGNATURE 

extern "C" IGmcClient*	GmcClientCreate();
#define FUNC_NAME_GMC_CLIENT_CREATE "GmcClientCreate"
typedef IGmcClient* (*FUNC_GMC_CLIENT_CREATE)();

#endif // #ifndef  GMC_CLIENT_INTERNAL_SIGNATURE 

#endif
