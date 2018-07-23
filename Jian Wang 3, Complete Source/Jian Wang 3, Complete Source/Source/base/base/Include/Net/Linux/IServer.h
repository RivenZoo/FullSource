#ifndef ISERVER_H
#define ISERVER_H

#include "XBuffer.h"

enum enumClientConnectInfo {
	enumClientConnectCreate = 0x100,
	enumClientConnectClose
};

typedef void (*CALLBACK_SERVER_EVENT)(void * lpParam, const unsigned long &ulnID, const unsigned long &ulnEventType);

class IServer
{
public:
//对外公开的接口
	STDPROC Startup() = 0;
	STDPROC Cleanup() = 0;
	virtual int Release() = 0;
	STDPROC Open(unsigned long ulnAddressToListenOn, unsigned short usnPortToListenOn) = 0;
	STDPROC OpenService(unsigned long ulnAddressToListenOn, unsigned short usnPortToListenOn) = 0;
	STDPROC CloseService() = 0;
	STDPROC RegisterMsgFilter(void * lpParam, CALLBACK_SERVER_EVENT pfnEventNotify) = 0;
	STDPROC PreparePackSink() = 0;
	STDPROC PackDataToClient(unsigned long ulnClientID, const void *pData, unsigned long datalength) = 0;
	STDPROC SendPackToClient() = 0;
	STDPROC SendPackToClient(int index) = 0;
	STDPROC SendData(unsigned long ulnClientID, const void *pData, unsigned long datalength) = 0;
	virtual const void *GetPackFromClient(unsigned long ulnClientID, unsigned int &datalength) = 0;
	STDPROC ShutdownClient(unsigned long ulnClientID) = 0;
	virtual const char * GetClientInfo(unsigned long ulnClientID) = 0;
	STDPROC PassPack(unsigned long ulnClientID) = 0;	// 放弃当前数据包
	virtual void DoEveryThing() = 0;
	/*
	virtual ZPerf *SendPerf() = 0;
	virtual ZPerf *RecvPerf() = 0;
	virtual void PushMessage(unsigned long nIndex, char *pMsg, size_t nMsgLen) = 0;
	virtual BOOL IsClientEmpty(unsigned long nIndex) = 0;
	*/
};

#endif
