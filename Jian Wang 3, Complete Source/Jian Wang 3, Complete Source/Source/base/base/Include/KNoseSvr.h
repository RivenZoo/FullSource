#ifndef __KNOSE_SERVER__
#define __KNOSE_SERVER__

#include "Engine/FileType.h"
#include "Common/KG_Socket.h"

//新的kingeyes系统的KNose通信模块

typedef int (* GetDataFunc)(int nDataType, unsigned long uParam);

enum K2SProtocolIdx
{
	K2S_GET_PLAYER_CNT = 1,
	K2S_GET_SVR_VER,
	K2S_PING,
	K2S_STOP,
	K2S_RELOAD,
};

enum NoseServerType
{
	ST_BEGIN,
	ST_GODDESS,
	ST_BISHOP,
	ST_RELAY,
	ST_GAMESERVER,
	ST_END,
};

#pragma	pack(push, 1)
struct K2SProtocolHeader
{
	int			nProtocol;
	int			nSubProtocol;
	long long	llCID;
};

struct S2KNOTIFY_VER: K2SProtocolHeader
{
	char szVersion[20];
};

struct S2KNOTIFY_PLAYRE_CNT: K2SProtocolHeader
{
	unsigned short   wPlayerOnline;
	unsigned short	 wPlayerOffline;
};
#pragma pack(pop)

enum NOSE_GET_DATA_TYPE{
	GET_TOTAL_PLAYER_CNT_IN_GS,			//gamesvr上总的在线人数
	GET_OFFLINE_PLAYER_CNT_IN_GS,		//gamesvr上的离线托管玩家人数
	GET_ONLINE_PLAYER_CNT_IN_BISHOP,	//bishop上的在线人数
	GET_OFFLINE_PLAYER_CNT_IN_BISHOP,	//bishop上的离线人数
	GAMESERVER_RELOAD,					//gmaesvr上reload指定脚本
};

class KNoseSvr
{
public:
	KNoseSvr()
	{
		m_pSocket				= NULL;
		m_bRunning				= false;
		m_pSocketEventsArray	= NULL;
		m_bEnable				= false;
		m_eSvrType				= ST_BEGIN;
		m_GetDataFunc			= NULL;
		m_nPort					= 0;
		m_nSocketEventArrayCount= 0;
		memset(m_szGameVer, 0, sizeof(m_szGameVer));
		memset(m_szLocalAddr, 0, sizeof(m_szLocalAddr));
	};

	int Initialize(const char* cpCfgFile, GetDataFunc func, NoseServerType eType)
	{
		int nRetCode = false;
		int nRetsult = false;
		int nServerInit = false;
		int nArrayNew = false;

		nRetCode = LoadNoseConfig(cpCfgFile);
		KGLOG_PROCESS_ERROR(nRetCode);

		KG_PROCESS_SUCCESS(!m_bEnable);

		KGLOG_PROCESS_ERROR(eType > ST_BEGIN && eType < ST_END);
		m_eSvrType = eType;

		nRetCode = m_Server.Init(m_szLocalAddr, m_nPort, 2, 8192, 102400, KSG_ENCODE_DECODE_NONE, NULL);
		KGLOG_PROCESS_ERROR(nRetCode);
		nServerInit = true;
		m_nSocketEventArrayCount = 2;

		m_pSocketEventsArray = new KG_SOCKET_EVENT[m_nSocketEventArrayCount];
		KGLOG_PROCESS_ERROR(m_pSocketEventsArray);
		nArrayNew = true;

		nRetCode = LoadVersion();
		m_bRunning = true;
		m_GetDataFunc = func;
		KGLogPrintf(KGLOG_INFO, "Nose init ok!~");

Exit1:
		nRetsult = true;
Exit0:
		if (!nRetsult)
		{
			if (nServerInit)
			{
				m_Server.UnInit(NULL);
			}
			if (nArrayNew)
			{
				KG_DELETE_ARRAY(m_pSocketEventsArray);
			}
		}
		return nRetsult;
	}
	void UnInitialize()
	{
		if (!m_bEnable)
		{
			return;
		}
		m_bRunning = false;
		KG_COM_RELEASE(m_pSocket);
		m_Server.UnInit(NULL);
		KG_DELETE_ARRAY(m_pSocketEventsArray);
	}

	bool Breathe()
	{
		IKG_Buffer*	piBuffer = NULL;
		int	nRetSocketEventCount = 0;

		if (!m_bEnable)
			return true;

		if (!m_bRunning)
			return false;

		int nRetCode = m_Server.Wait(m_nSocketEventArrayCount, m_pSocketEventsArray, &nRetSocketEventCount);
		if (!nRetCode || nRetSocketEventCount == 0)
			return true;

		KG_SOCKET_EVENT* pSocketEvent = m_pSocketEventsArray;
		KG_SOCKET_EVENT* pSocketEventEnd = m_pSocketEventsArray + nRetSocketEventCount;
		for (; pSocketEvent < pSocketEventEnd; pSocketEvent++)
		{
			if (pSocketEvent->uEventFlag & KG_SOCKET_EVENT_ACCEPT)
			{
				if (m_pSocket){
					KGLogPrintf(KGLOG_WARNING, "there is a old Knose client connected yet!");
				}else{
					KGLogPrintf(KGLOG_INFO, "Knose client connected now!");
				}
				KG_COM_RELEASE(m_pSocket);
				m_pSocket = pSocketEvent->piSocket;
			}

			if ((pSocketEvent->uEventFlag & KG_SOCKET_EVENT_IN) == 0)
				continue;

			while (true)
			{
				KG_COM_RELEASE(piBuffer);
				if (pSocketEvent == NULL || pSocketEvent->piSocket == NULL)
					break;

				nRetCode = pSocketEvent->piSocket->Recv(&piBuffer);

				if (nRetCode == -2)
					break;

				if (nRetCode == -1)
				{
					KGLogPrintf(KGLOG_INFO, "Knose client disconnected now!");
					KG_COM_RELEASE(m_pSocket);
					break;
				}

				ProcessMessage(piBuffer);
			}
			KG_COM_RELEASE(piBuffer);
		}
		return true;
	}

private:
	int LoadNoseConfig(const char* pConfigFile)
	{
		int nResult = false;
		int nRetCode = false;
		int nEnable = 0;
		char szLoaclAddr[16];
		int nPort = 0;
		IIniFile* pFile = NULL;

		pFile = g_OpenIniFile(pConfigFile);
		KGLOG_PROCESS_ERROR(pFile);

		pFile->GetInteger("Nose", "Enable", 0, &nEnable);
		m_bEnable = (nEnable > 0);
		KG_PROCESS_SUCCESS(!m_bEnable);

		pFile->GetString("Nose", "LocalIPAddress", "0.0.0.0", szLoaclAddr, sizeof(szLoaclAddr));
		nRetCode = pFile->GetInteger("Nose", "ListenPort", 0, &nPort);
		KGLOG_PROCESS_ERROR(nRetCode && (nPort>0));

		memcpy(m_szLocalAddr, szLoaclAddr, sizeof(m_szLocalAddr));
		m_nPort = nPort;
Exit1:
		nResult = true;
Exit0:
		KG_COM_RELEASE(pFile);
		return nResult;
	}

	int LoadVersion()
	{
		int nResult = false;
		int nRetCode = false;
		char szVersion[32];
		char* pTemp = NULL;
		int nCount = 0;
		IIniFile* pFile = NULL;

		memset(m_szGameVer, 0, sizeof(m_szGameVer));

		pFile = g_OpenIniFile("version.ini");
		KG_PROCESS_ERROR(pFile);

		memset(m_szGameVer, 0, sizeof(m_szGameVer));
		nRetCode = pFile->GetString("Version", "Version", "", szVersion, sizeof(szVersion));
		KG_PROCESS_ERROR(nRetCode);

		memcpy(m_szGameVer, szVersion, sizeof(m_szGameVer)-1);
		m_szGameVer[sizeof(m_szGameVer)-1] = '\0';

		nResult = true;
Exit0:
		KG_COM_RELEASE(pFile);
		return nResult;
	}

	int ProcessMessage(IKG_Buffer* piRecvBuffer)
	{
		int nResult = false;
		IKG_Buffer* piSendBuffer = NULL;
		S2KNOTIFY_VER* pNotifyVer = NULL;
		S2KNOTIFY_PLAYRE_CNT* pNotifyCnt = NULL;
		void *pBuffer = piRecvBuffer->GetData();
		short nPlayerOnline, nPlayerOffline;
		nPlayerOnline =	nPlayerOffline = 0;
		K2SProtocolHeader *pHeader = (K2SProtocolHeader *)piRecvBuffer->GetData();
		KGLOG_PROCESS_ERROR(pHeader->nProtocol == 1);//暂时主协议号只有1

		switch (pHeader->nSubProtocol)
		{
		case K2S_PING:
			m_pSocket->Send(piRecvBuffer);
			break;
		case K2S_STOP:
			m_bRunning = false;
			m_pSocket->Send(piRecvBuffer);
			break;
		case K2S_GET_SVR_VER:
			piSendBuffer = KG_MemoryCreateBuffer(sizeof(S2KNOTIFY_VER));
			pNotifyVer = (S2KNOTIFY_VER*)piSendBuffer->GetData();
			memcpy((void*)pNotifyVer, piRecvBuffer->GetData(), piRecvBuffer->GetSize());
			memcpy(pNotifyVer->szVersion, m_szGameVer, sizeof(m_szGameVer));
			m_pSocket->Send(piSendBuffer);
			break;
		case K2S_GET_PLAYER_CNT:
			piSendBuffer = KG_MemoryCreateBuffer(sizeof(S2KNOTIFY_PLAYRE_CNT));
			pNotifyCnt = (S2KNOTIFY_PLAYRE_CNT*)piSendBuffer->GetData();
			memcpy((void*)pNotifyCnt, piRecvBuffer->GetData(), piRecvBuffer->GetSize());
			if (m_eSvrType == ST_GAMESERVER)
			{
				nPlayerOnline  = m_GetDataFunc(GET_TOTAL_PLAYER_CNT_IN_GS, 0);
				nPlayerOffline = m_GetDataFunc(GET_OFFLINE_PLAYER_CNT_IN_GS, 0);
				nPlayerOnline -= nPlayerOffline;
			}
			else if(m_eSvrType == ST_BISHOP)
			{
				nPlayerOnline  = m_GetDataFunc(GET_ONLINE_PLAYER_CNT_IN_BISHOP, 0);
				nPlayerOffline = m_GetDataFunc(GET_OFFLINE_PLAYER_CNT_IN_BISHOP, 0);
			}
			pNotifyCnt->wPlayerOnline  = nPlayerOnline;
			pNotifyCnt->wPlayerOffline = nPlayerOffline;

			m_pSocket->Send(piSendBuffer);
			break;
		case K2S_RELOAD:
			if (m_eSvrType == ST_GAMESERVER)
			{
				m_GetDataFunc(GAMESERVER_RELOAD, 0);
				m_pSocket->Send(piRecvBuffer);
			}
			break;
		}

		nResult = true;
Exit0:
		KG_COM_RELEASE(piSendBuffer);
		return nResult;
	}

private:
	KG_SocketServerAcceptor 	m_Server;
	IKG_SocketStream*			m_pSocket;
	KG_SOCKET_EVENT*			m_pSocketEventsArray;
	int							m_nSocketEventArrayCount;
	bool						m_bRunning;
	char						m_szGameVer[20];
	GetDataFunc					m_GetDataFunc;
	bool						m_bEnable;
	NoseServerType				m_eSvrType;
	char						m_szLocalAddr[16];
	int							m_nPort;
};

#endif //__KNOSE_SERVER__
