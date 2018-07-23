#ifndef ICLIENT_H
#define ICLIENT_H

//应该使用线程的方法,Startup启动线程等待信号,不同的IO模型使用不同的信号通知这些线程,处理的时候
//根据处理器数目的不同启动不同数目的线程和缓冲区,处理异常情况
#include "ZPort.h"
#include "XBuffer.h"
#include "Cipher.h"
#include "Cache.h"

enum enumServerConnectInfo {
	enumServerConnectCreate = 0x100,
	enumServerConnectClose
};

typedef void (*CALLBACK_CLIENT_EVENT )(void *lpParam, const unsigned long &ulnEventType);

class IClient
{
public:
	STDPROC Startup() = 0;						//启动一个线程发送
	STDPROC Cleanup() = 0;
	STDPROC Shutdown() = 0;
	virtual void Release() = 0;
	STDPROC ConnectTo(const char *pAddressToConnectServer, unsigned short usPortToConnectServer) = 0;
	STDPROC RegisterMsgFilter(void * lpParam, CALLBACK_CLIENT_EVENT pfnEventNotify) = 0;
	STDPROC SendPackToServer( const void * const pData, const unsigned long datalength) = 0;
	virtual void *GetPackFromServer(unsigned int &datalength) = 0;
	/*
	virtual void PushMessage(char *pMsg, size_t nMsgLen) = 0;
	virtual BOOL IsEmpty() = 0;
	*/
	virtual void PassPack() {}
};

#endif
