#ifndef IKSGSERVER_H
#define IKSGSERVER_H

enum enumClientConnectInfo {
	enumClientConnectCreate = 0x100,
	enumClientConnectClose
};

typedef void (*CALLBACK_SERVER_EVENT)(void* lpParam, unsigned long ulnID, enumClientConnectInfo ulnEventType);

class IKSGServer {
public:
	//启动初始化
	virtual bool Startup() = 0;

	//退出清理
	virtual bool Cleanup() = 0;

	//打开一个端口启动网络服务
	virtual bool OpenServer(unsigned long ulnAddressToListenOn, unsigned short usnPortToListenOn) = 0;

	//关闭网络服务
	virtual bool CloseServer() = 0;

	//注册事件回调函数
	virtual bool RegisterMsgFilter(void * lpParam, CALLBACK_SERVER_EVENT pfnEventNotify) = 0;

	//将数据加入某客户端的发送队列,数据不会即时发送到客户端
	virtual bool PackDataToClient(unsigned long ulnClientID, const void *pData, unsigned long datalength) = 0;

	//将发送队列中的数据强制即时发送到客户端, ulnClientID == -1 表示强制发送所有客户端缓冲区恿
	virtual bool SendPackToClient(unsigned long ulnClientID) = 0;

	//将数据即时发送到客户端
	virtual bool SendData(unsigned long ulnClientID, const void *pData, unsigned long datalength) = 0;

	//取得从某客户端发送来的一个数据包
	virtual const void *GetPackFromClient(unsigned long ulnClientID, unsigned long &datalength) = 0;

	//强制断开一个客户端连接
	virtual bool ShutdownClient(unsigned long ulnClientID) = 0;

	//取得当前的有效客户端连接总数
	virtual unsigned long GetClientCount() = 0;

	//取得一个客户端的信息(IP地址)
	virtual const char * GetClientInfo(unsigned long ulnClientID) = 0;
	
	//如果要保证 KSGServer 正常运行,必须在程序主线程不断调用此函数
	virtual void Breathe() = 0;
};

/************************************************************
//函数：CreateKSGServer()
//功能：创建一个 KSGServer 对象
//参数：unsigned long	ulMaxClient		: Server支持的最大连接数
		unsigned long	ulBufferParam1	: windows: 本KSGServer允许的空闲缓冲区最大个数, linux: 单个客户端连接的发送缓冲区大小
		unsigned long	ulBufferParam2	: windows: 单个缓冲区的大小, linux: 单个客户端连接的接受缓冲区大小
//返回：IKSGServer*	: 创建好的 KSGServer 对象指针
************************************************************/
IKSGServer* CreateKSGServer(unsigned long ulMaxClient,
							unsigned long ulBufferParam1,
							unsigned long ulBufferParam2);

//删除释放一个 KSGServer 对象
bool DeleteKSGServer(IKSGServer*);

#endif
