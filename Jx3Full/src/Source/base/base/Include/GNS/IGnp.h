//--------------------------------------------------------------
// 月影传说网络版  GmcNetworkProtocol(GNP)
// 版权所有:        2010 金山软件(Kingsoft)
// 创建日期与作者: 2010-3-16 Golton Gao
//--------------------------------------------------------------
#ifndef __I_GMC_NETWORK_PROTOCOL_H__
#define __I_GMC_NETWORK_PROTOCOL_H__

#include "GnsDef.h"

// === 身份验证相关 ===//
#pragma pack(1)

// == 身份验证模式 ==//
enum GNP_AUTHENTICATION_MODE	
{
	GAM_NONE = 0,	// 不进行身份验证
	GAM_IP,			// IP身份验证模式
};

// == 身份验证信息 ==//
#define GNP_AUTHENTICATION_MAX_LEN 512	// 身份验证信息的最大长度

#pragma pack()

// GNP的监控流
struct IGnpMonitor
{
	virtual void Print(const char* pFormat, ...) = 0;
};

// GNP_CLIENT的配置信息
struct GNP_CLIENT_CONFIG
{
	char			LocalIP[16];			// GNP客户端的IP，对于客户端有多个IP的情况尤需注意
	GNE_ADDR		LocalAddr;				// GNP客户端在GNS中的地址
	char			ServerIP[16];			// GNP服务端的IP
	unsigned int	ServerPort;				// GNP服务端的监听端口
	GNE_ADDR		ServerAddr;				// GNP服务端在GNS中的地址
	int				ServerEncryptionType;	// 通信加密方式
};

// GnpClient事件处理器
struct IGnpClientEventHandler
{
	// 消息接收事件
	// 输入参数：	Head		--	GNM消息的头部
	//				pLoadData	--	GNM消息载荷数据
	//				uLoadLen	--	GNM消息载荷长度
	virtual void OnClientRecv(const GNM_HEAD& Head, const char* pLoadData, unsigned int uLoadLen) = 0;
};

// GnpClient
struct IGnpClient
{
	// 销毁接口对象
	virtual void Release() = 0;

	// 设置身份验证的相关信息
	// 输入参数：	uAuthenticationMode -- 身份验证模式，参看GNP_AUTHENTICATION_MODE
	//				pAuthenticationInfo	-- 特定模式的身份验证信息
	//				uInfoSize			-- 特定模式的身份验证信息的长度，务必<=GNP_AUTHENTICATION_MAX_LEN
	// 注意：在Initialize之前调用
	// 例子：IP身份验证方式	--	SetAuthentication(GAM_IP, NULL, 0);
	virtual void SetAuthenticationInfo(unsigned int uAuthenticationMode, void* pAuhtenticationInfo, unsigned int uInfoSize) = 0;

	// 初始化
	virtual bool Initialize(const GNP_CLIENT_CONFIG& Config) = 0;
	
	// 反初始化
	virtual void Terminate() = 0;
	
	// 调度
	virtual void Tick() = 0;

	// 发送GNM消息
	virtual bool Send(const GNM_HEAD& Head, const void* pLoadData, unsigned int uLoadLen) = 0;

	// 连接状态是否正常
	virtual bool IsOk() = 0;

	// 获取GNP协议版本
	virtual void GetVersion(unsigned int& uMajor, unsigned int& uMinor) = 0;

	// 设置依赖的监控流
	// 输入参数：pMonitor	-- NULL, 关闭监控流
	//						-- 非NULL，监控流重定向到pMonitor
	virtual void SetMonitor(IGnpMonitor* pMonitor) = 0;

	// 设置事件处理器
	// 输入参数：pEventHandler	-- 事件处理器指针，不能为NULL
	// 注意：在Initialize之间调用
	virtual void SetEventHandler(IGnpClientEventHandler* pEventHandler) = 0;
};

// GNP_SERVER配置信息
struct GNP_SERVER_CONFIG
{
	char			ServerIP[16];			// GNP服务端IP
	unsigned int	ServerPort;				// GNP服务端监听端口
	GNE_ADDR		ServerAddr;				// GNP服务端在GNS中的地址
	unsigned int	ServerMaxConn;			// GNP服务端支持的最大连接数
	int				ServerEncryptionType;	// 通信加密方式
};

// GNP_SERVER事件处理器
struct IGnpServerEventHandler
{
	virtual void OnLogin(const GNE_ADDR& GneAddr) = 0;
	virtual void OnLogout(const GNE_ADDR& GneAddr) = 0;
	virtual void OnServerRecv(const GNM_HEAD& Head, const char* pLoadData, unsigned int uLoadLen) = 0;
};

// GNP_SERVER身份验证器
struct IGnpServerAuthentication
{
	// 判断是否通过身份验证
	// 输入参数：	ClientAddr	--	需要验证的客户端的GNE地址（希望持有的身份）
	//				uIp			--	客户端登陆的IP
	//				uMode		--	身份验证模式，参考GNP_AUTHENTICATION_MODE
	//				pInfo		--	身份验证信息，与具体的身份验证模式有关
	//				uInfoSize	--	身份验证信息的长度，最大不超过GNP_AUTHENTICATION_MAX_LEN
	// 返回值：	true		--	通过身份验证
	//				false		--	未通过身份验证
	virtual bool IsAuthenticated(const GNE_ADDR& ClientAddr, unsigned int uIp, unsigned int uMode, const void* pInfo, unsigned int uInfoSize) = 0;
};

struct GNE_INFO
{
	GNE_ADDR				Addr;		// GNE地址
	unsigned int			uIp;		// GNE所用的IP
	unsigned int			uPort;		// GNE所用的端口
};

struct IGnpServer
{
	// 销毁接口对象
	virtual void Release() = 0;

	// 初始化
	virtual bool Initialize(const GNP_SERVER_CONFIG& Config) = 0;

	// 反初始化
	virtual void Terminate() = 0;

	// 调度
	virtual void Tick() = 0;

	// 发送GNM消息
	// 输入参数：	Head		--	GNM消息头部
	//				pLoadData	--	GNM消息载荷数据
	//				uLoadLen	--	GNM消息载荷长度
	// 返回值:		true		--	发送成功
	//				false		--	发送失败
	virtual bool Send(const GNM_HEAD& Head, const void* pLoadData, unsigned int uLoadLen) = 0;

	// 遍历在线GNE
	// 例子：
	/*
		IGnpServer*	pServer;
		for (unsigned int uPos = pServer->GetBeginPos(); uPos != pServer->GetEndPos(); pServer->GetNextPos(uPos))
		{
			GNE_INFO Info = pServer->GetGneInfo(uPos);
		}
	*/
	virtual unsigned int GetBeginPos() = 0;
	virtual unsigned int GetEndPos() = 0;
	virtual void GetNextPos(unsigned int& uPos) = 0;
	virtual GNE_INFO GetGneInfo(unsigned int uPos) = 0;

	// 获取在线GNE数量
	virtual unsigned int GetGneCount() = 0;

	// 查询GNE是否已登录
	virtual bool IsGneLogined(const GNE_ADDR& GneAddr) = 0;

	// 断开GNE连接
	virtual void Disconnect(const GNE_ADDR& GneAddr) = 0;

	// 获取GNP协议的版本(可以写入初始化日志中，便于查证分析)
	virtual void GetVersion(unsigned int& uMajor, unsigned int& uMinor) = 0;

	// 设置依赖的监控流
	// 输入参数：pMonitor	-- NULL, 关闭监控流
	//						-- 非NULL，监控流重定向到pMonitor
	virtual void SetMonitor(IGnpMonitor* pMonitor) = 0;

	// 设置事件处理器
	// 输入参数：pEventHandler	-- 事件处理器指针，不能为NULL
	// 注意：在Initialize之间调用
	virtual void SetEventHandler(IGnpServerEventHandler* pEventHandler) = 0;

	// 设置身份验证器
	// 输入参数：pAuthentication	-- 身份验证器指针，不能为NULL
	// 注意：在Initialize之间调用
	virtual void SetAuthentication(IGnpServerAuthentication* pAuthentication) = 0;
};

//=== 外部引用该头文件时，给出接口声明 ===//
#ifndef  GNP_INTERNAL_SIGNATURE 

//== 隐式加载DLL所用的接口 ==
extern "C" IGnpClient* GnpClientCreate();
extern "C" IGnpServer* GnpServerCreate();

//== 显示加载DLL所用的接口 ==

//= 创建接口函数名定义 =
#define FUNC_NAME_GNP_CLIENT_CREATE "GnpClientCreate"
#define FUNC_NAME_GNP_SERVER_CREATE "GnpServerCreate"

//= 创建接口函数原型定义
typedef IGnpClient* (*FUNC_GNP_CLIENT_CREATE)();
typedef IGnpServer* (*FUNC_GNP_SERVER_CREATE)();

#endif // #ifndef  GNP_INTERNAL_SIGNATURE 

#endif // #ifndef __I_GMC_NETWORK_PROTOCOL_H__ 
