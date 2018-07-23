#ifndef IKSGCLIENT_H
#define IKSGCLIENT_H


enum enumServerConnectInfo {
	enumServerConnectCreate = 0x100,
	enumServerConnectClose
};

typedef void (*CALLBACK_CLIENT_EVENT)(void *lpParam, enumServerConnectInfo eEventType);

class IKSGClient {
public:
	//设定事件回调函数
	virtual bool RegisterMsgFilter(void * lpParam, CALLBACK_CLIENT_EVENT pfnEventNotify) = 0;

	//启动初始化
	virtual bool Startup() = 0;

	//退出清理
	virtual bool CleanUp() = 0;

	//连接指定IP地址
	virtual bool ConnectTo(const char * const &pAddressToConnectServer, unsigned short usPortToConnectServer) = 0;

	//断开连接
	virtual bool Shutdown() = 0;

	//向Server发送数据
	virtual bool SendPackToServer(const void * const pData, const unsigned long datalength) = 0;

	//获取从Server传送过来的数据
	virtual void *GetPackFromServer(unsigned int &datalength) = 0;
};

//创建KSGClient对象
//windows:	ulBufferParam1有效, 含义同原RainBowLib
//linux:	ulBufferParam1为发送缓冲区大小, ulBufferParam2为接受缓冲区大小
IKSGClient* CreateKSGClient(unsigned long ulBufferParam1, unsigned long ulBufferParam2);

//删除释放KSGClient对象
bool DeleteKSGClient(IKSGClient*);

#endif
