#include "stdafx.h"
#include "KNetworkMgr.h"

#define REGISTER_INTERNAL_FUNC(ProtocolID, FuncName, ProtocolSize)	\
{m_ProcessProtocolFuns[ProtocolID] = FuncName;					\
    m_uProtocolSize[ProtocolID] = ProtocolSize;}

KNetworkMgr::KNetworkMgr()
{
    m_nMaxConnection        = 0;
    m_pSocketEvent          = NULL;
    m_nNextCheckConnection  = 0;

    memset(m_ProcessProtocolFuns, 0, sizeof(m_ProcessProtocolFuns));
    memset(m_uProtocolSize, 0, sizeof(m_uProtocolSize));

    REGISTER_INTERNAL_FUNC(editor_to_server_handshake_request, &KNetworkMgr::OnHandshakeRequest, sizeof(EDITOR_TO_SERVER_HANDSHAKE_REQUEST));
    REGISTER_INTERNAL_FUNC(editor_to_server_send_message, &KNetworkMgr::OnSendMessage, sizeof(EDITOR_TO_SERVER_SEND_MESSAGE));
    REGISTER_INTERNAL_FUNC(editor_to_server_send_ping, &KNetworkMgr::OnSendPing, sizeof(EDITOR_TO_SERVER_SEND_PING));
    REGISTER_INTERNAL_FUNC(editor_to_server_send_jsonfilechange, &KNetworkMgr::OnSendJsonFileChange, sizeof(EDITOR_TO_SERVER_SEND_JSONFILECHANGE));
}

KNetworkMgr::~KNetworkMgr()
{
}

BOOL KNetworkMgr::Init(const char* szLocalIP, int nListenPort, int nMaxConnection)
{
    BOOL    bResult             = false;
    int     nRetCode            = 0;
    BOOL    bSocketServerInit   = false;
    
    m_nMaxConnection = nMaxConnection;
    m_ConnectionDataList = new KG_CONNECTION_DATA[m_nMaxConnection];
    KGLOG_PROCESS_ERROR(m_ConnectionDataList);

    m_nEventCount  = nMaxConnection + KG_MAX_ACCEPT_EACH_WAIT;
    m_pSocketEvent = new KG_SOCKET_EVENT[m_nEventCount];
    KGLOG_PROCESS_ERROR(m_pSocketEvent);

    nRetCode = m_SocketServerAcceptor.Init(
        szLocalIP, nListenPort, KG_MAX_ACCEPT_EACH_WAIT, 
        KG_RECV_BUFFER_SIZE, KG_SEND_BUFFER_SIZE, KSG_ENCODE_DECODE_NONE, NULL
    );
    KGLogPrintf(
        KGLOG_INFO, "Start service at %s:%d ... ... [%s]",
        szLocalIP, nListenPort, nRetCode ? "OK" : "Failed"
    );
    
    KGLOG_PROCESS_ERROR(nRetCode);
    bSocketServerInit = true;

    m_ConnectionDataListFreeVector.reserve(nMaxConnection);
    for (int i = 0; i < nMaxConnection; i++)
    {
        m_ConnectionDataListFreeVector.push_back(nMaxConnection - i - 1);
    }

    bResult = true;
Exit0:
    if (!bResult)
    {
        if (bSocketServerInit)
        {
            m_SocketServerAcceptor.UnInit(NULL);
            bSocketServerInit = false;
        }
        SAFE_DELETE(m_pSocketEvent);
        SAFE_DELETE(m_ConnectionDataList);
    }
    return bResult;
}

void KNetworkMgr::UnInit()
{
    m_SocketServerAcceptor.UnInit(NULL);
    SAFE_DELETE(m_pSocketEvent);
    SAFE_DELETE(m_ConnectionDataList);
}

KG_CONNECTION_DATA* KNetworkMgr::GetConnectionData(int nConnIndex)
{
    if (nConnIndex >= 0 && nConnIndex < m_nMaxConnection)
    {
        return &m_ConnectionDataList[nConnIndex];
    }

    return NULL;
}

void KNetworkMgr::Process()
{
    int                 nRetCode        = 0;
    int                 nWaitEventCount = 0;
    time_t              nTimeNow        = time(NULL);
    KG_SOCKET_EVENT*    pSocketEvent    = NULL;
    KG_SOCKET_EVENT*    pSocketEventEnd = NULL;

    while (true)
    {
        nRetCode = m_SocketServerAcceptor.Wait(m_nEventCount, m_pSocketEvent, &nWaitEventCount);
        KGLOG_PROCESS_ERROR(nRetCode);

        if (nWaitEventCount == 0)
            break;

        pSocketEventEnd = m_pSocketEvent + nWaitEventCount;
        for (pSocketEvent = m_pSocketEvent; pSocketEvent < pSocketEventEnd; pSocketEvent++)
        {
            if (pSocketEvent->uEventFlag & KG_SOCKET_EVENT_ACCEPT)
            {
                ProcessNewConnection(pSocketEvent->piSocket);
                KG_COM_RELEASE(pSocketEvent->piSocket);
                continue;
            }

            if (!(pSocketEvent->uEventFlag & KG_SOCKET_EVENT_IN))
            {
                KGLogPrintf(KGLOG_DEBUG, "Unexpected socket event: %u", pSocketEvent->uEventFlag);
                KG_COM_RELEASE(pSocketEvent->piSocket);
                continue;
            }

            ProcessPackage(pSocketEvent->piSocket);
            KG_COM_RELEASE(pSocketEvent->piSocket);
        }
    }

    for (int i = 0; i < 8; i++)
    {
        int                 nConnIndex  = m_nNextCheckConnection;
        KG_CONNECTION_DATA* pConnection = &m_ConnectionDataList[nConnIndex];

        m_nNextCheckConnection = (m_nNextCheckConnection + 1) % m_nMaxConnection;

        if (pConnection->piSocketStream == NULL)
            continue;

        if (nTimeNow > pConnection->nLastPingTime + PING_CYCLE)
        {
            KGLogPrintf(KGLOG_ERR, "Connection timeout: %d\n", nConnIndex);

            ShutDown(nConnIndex);
            continue;
        }

        if (pConnection->bSendError)
        {
            ShutDown(nConnIndex);
            pConnection->bSendError = false;
        }
    }

Exit0:
    return;
}

void KNetworkMgr::ProcessNewConnection(IKG_SocketStream* piSocket)
{
    int             nRetCode        = 0;
    int             nConnIndex      = -1;
    u_short         uRemotePort     = 0;
    const char*     pcszIP          = NULL;
    struct in_addr  RemoteIP;

    assert(piSocket);

    nRetCode = piSocket->GetRemoteAddress(&RemoteIP, &uRemotePort);
    KGLOG_PROCESS_ERROR(nRetCode);

    pcszIP = inet_ntoa(RemoteIP);
    KGLOG_PROCESS_ERROR(pcszIP);
    
    KGLOG_PROCESS_ERROR(!m_ConnectionDataListFreeVector.empty());
    nConnIndex = m_ConnectionDataListFreeVector.back();
    m_ConnectionDataListFreeVector.pop_back();

    KGLOG_PROCESS_ERROR(nConnIndex >= 0 && nConnIndex < m_nMaxConnection);
    KGLOG_PROCESS_ERROR(m_ConnectionDataList[nConnIndex].piSocketStream == NULL);
    KGLOG_PROCESS_ERROR(m_ConnectionDataList[nConnIndex].piJointBuffer == NULL);

    m_ConnectionDataList[nConnIndex].uJointOffset           = 0;
    m_ConnectionDataList[nConnIndex].nLastPingTime          = time(NULL);
    m_ConnectionDataList[nConnIndex].bSendError             = false;
    
    nRetCode = piSocket->SetUserData((void*)(ptrdiff_t)nConnIndex);
    KGLOG_PROCESS_ERROR(nRetCode);

    piSocket->AddRef();
    m_ConnectionDataList[nConnIndex].piSocketStream = piSocket;

    KGLogPrintf(KGLOG_INFO, "New Connection: %d", nConnIndex);

Exit0:
    return;
}

BOOL KNetworkMgr::ProcessPackage(IKG_SocketStream* piSocket)
{
    BOOL                    bResult         = false;
    int                     nRetCode        = 0;
    int                     nConnIndex      = -1;
    IKG_Buffer*             piBuffer        = NULL;
    BYTE*                   pbyData         = NULL;
    unsigned                uDataLen        = 0;
    int                     nPackCount      = 0;
    BOOL                    bShutDownFlag   = false;
    BOOL                    bKickout        = false;
    DWORD                   dwStartTime     = 0;
    DWORD                   dwEndTime       = 0;
    KG_CONNECTION_DATA*     pConn           = NULL;
    
    assert(piSocket);

    nConnIndex = (int)(ptrdiff_t)(piSocket->GetUserData());
    KGLOG_PROCESS_ERROR(nConnIndex >= 0 && nConnIndex < m_nMaxConnection);
    
    KG_PROCESS_ERROR(m_ConnectionDataList[nConnIndex].bSendError == false);

    while (true)
    {
        PROTOCOL_HEADER*    pHeader     = NULL;
        size_t              uDataSize   =   0;

        KG_COM_RELEASE(piBuffer);

        nRetCode = piSocket->Recv(&piBuffer);
        if (nRetCode == -2)
        {
            break;
        }

        if (nRetCode == -1)
        {
            bShutDownFlag = true;
            KGLogPrintf(KGLOG_INFO, "Connection lost: %d %d\n", nConnIndex, piSocket->GetLastError());
            break;
        }
        KGLOG_PROCESS_ERROR(piBuffer);
        
        m_ConnectionDataList[nConnIndex].nLastPingTime = time(NULL);
        pHeader = (PROTOCOL_HEADER*)piBuffer->GetData();
        KGLOG_PROCESS_ERROR(pHeader);

        uDataSize = piBuffer->GetSize();

        pConn = &m_ConnectionDataList[nConnIndex];
        KGLOG_PROCESS_ERROR(pConn);

        switch (pHeader->uPakFlag)
        {
        case ppfSinglePackage:
            ProcessSinglePackage(nConnIndex, pHeader, uDataSize);
            break;
        case ppfPackageHeader:
            ProcessLargePackageBegin(nConnIndex, pHeader, uDataSize);
            break;
        case ppfPackageBody:
            ProcessLargePackage(nConnIndex, pHeader, uDataSize);
            break;
        case ppfPackageTail:
            ProcessLargePackageEnd(nConnIndex, pHeader, uDataSize);
            break;
        }
    }

    bResult = true;
Exit0:
    if (bShutDownFlag)
    {
        ShutDown(nConnIndex);
    }

    KG_COM_RELEASE(piBuffer);
    return bResult;
}

void KNetworkMgr::ProcessSinglePackage(int nConnIndex, PROTOCOL_HEADER* pHeader, size_t uPakSize)
{
    PROCESS_PROTOCOL_FUNC   ProcessFunc;

    if (uPakSize < m_uProtocolSize[pHeader->uProtocolID])
    {
        KGLogPrintf(
            KGLOG_ERR, "[network] Protocol%d size error. pak size:%d, limit size:%d.",
            pHeader->uProtocolID, uPakSize, m_uProtocolSize[pHeader->uProtocolID]
        );
        goto Exit0;
    }
        
	ProcessFunc = m_ProcessProtocolFuns[pHeader->uProtocolID];
    KGLOG_PROCESS_ERROR(ProcessFunc);

    (this->*ProcessFunc)((BYTE*)(pHeader), uPakSize, nConnIndex);

Exit0:
    return;
}

void KNetworkMgr::ProcessLargePackageBegin(int nConnIndex, PROTOCOL_HEADER* pHeader, size_t uPakSize)
{
    void*               pData       = NULL;
    KG_CONNECTION_DATA* pConnData   = GetConnectionData(nConnIndex);

    KGLOG_PROCESS_ERROR(pConnData);
    KGLOG_PROCESS_ERROR(pConnData->piJointBuffer == NULL);
    KGLOG_PROCESS_ERROR(pHeader->uPakSize > SHRT_MAX);

    pConnData->piJointBuffer = KG_MemoryCreateBuffer(pHeader->uPakSize);
    KGLOG_PROCESS_ERROR(pConnData->piJointBuffer);

    pData = pConnData->piJointBuffer->GetData();
    KGLOG_PROCESS_ERROR(pData);

    memcpy(pData, pHeader, uPakSize);
    pConnData->uJointOffset += uPakSize;

Exit0:
    return;
}

void KNetworkMgr::ProcessLargePackage(int nConnIndex, PROTOCOL_HEADER* pHeader, size_t uPakSize)
{
    BYTE*                   pbyData     = NULL;
    BYTE*                   pbyAddData  = NULL;
    size_t                  uBufferSize = 0;
    size_t                  uAddSize    = uPakSize - sizeof(PROTOCOL_HEADER);
    KG_CONNECTION_DATA*     pConnData   = GetConnectionData(nConnIndex);


    KGLOG_PROCESS_ERROR(pConnData->piJointBuffer);

    pbyData = (BYTE*)pConnData->piJointBuffer->GetData();
    KGLOG_PROCESS_ERROR(pbyData);

    pbyAddData = (BYTE*)pHeader + sizeof(PROTOCOL_HEADER);

    uBufferSize = pConnData->piJointBuffer->GetSize();
    KGLOG_PROCESS_ERROR(pConnData->uJointOffset + uAddSize <= uBufferSize);

    memcpy(pbyData + pConnData->uJointOffset, pbyAddData, uAddSize);
    pConnData->uJointOffset += uAddSize;
    
Exit0:
    return;
}

void KNetworkMgr::ProcessLargePackageEnd(int nConnIndex, PROTOCOL_HEADER* pHeader, size_t uPakSize)
{
    BYTE*                   pbyData     = NULL;
    size_t                  uBufferSize = 0;
    KG_CONNECTION_DATA*     pConnData   = GetConnectionData(nConnIndex);
    PROCESS_PROTOCOL_FUNC   ProcessFunc;

    ProcessLargePackage(nConnIndex, pHeader, uPakSize);
    
    uBufferSize = pConnData->piJointBuffer->GetSize();
    KGLOG_PROCESS_ERROR(uBufferSize == pConnData->uJointOffset);

    pbyData = (BYTE*)pConnData->piJointBuffer->GetData();
    KGLOG_PROCESS_ERROR(pbyData);
    
    if (uPakSize < m_uProtocolSize[pHeader->uProtocolID])
    {
        KGLogPrintf(
            KGLOG_ERR, "[network] Protocol%d size error. pak size:%d, limit size:%d.",
            pHeader->uProtocolID, uPakSize, m_uProtocolSize[pHeader->uProtocolID]
        );
        goto Exit0;
    }
        
	ProcessFunc = m_ProcessProtocolFuns[pHeader->uProtocolID];
    KGLOG_PROCESS_ERROR(ProcessFunc);

    (this->*ProcessFunc)(pbyData, uBufferSize, nConnIndex);

Exit0:
    KG_COM_RELEASE(pConnData->piJointBuffer);
    pConnData->uJointOffset = 0;

    return;
}

BOOL KNetworkMgr::Send(int nConnIndex, void* pData, size_t nDataSize)
{
    BOOL                bResult         = false;
    BOOL                bRetCode        = false;
    KG_CONNECTION_DATA* pConnectionData = NULL;

    KGLOG_PROCESS_ERROR(nConnIndex >= 0 && nConnIndex < m_nMaxConnection);
    pConnectionData = &m_ConnectionDataList[nConnIndex];
    
    KGLOG_PROCESS_ERROR(pConnectionData->bSendError == false);
    KGLOG_PROCESS_ERROR(pConnectionData->piSocketStream);

    if (nDataSize < SHRT_MAX)
    {
        bRetCode = SendSinglePackage(pConnectionData, pData, nDataSize);
        KGLOG_PROCESS_ERROR(bRetCode);
    }
    else
    {
        bRetCode = SendLargePackage(pConnectionData, (BYTE*)pData, nDataSize);
        KGLOG_PROCESS_ERROR(bRetCode);
    }

    bResult = true;
Exit0:
    return bResult;
}

BOOL KNetworkMgr::SendBuffer(KG_CONNECTION_DATA* pConnData, IKG_Buffer* piBuffer)
{
    BOOL    bResult     = false;
    BOOL    bRetCode    = false;

    bRetCode = pConnData->piSocketStream->Send(piBuffer);
    if (!bRetCode)
    {
        pConnData->bSendError = true;
        goto Exit0;
    }

    bResult = true;
Exit0:
    return bResult;
}

BOOL KNetworkMgr::SendSinglePackage(KG_CONNECTION_DATA* pConnData, void* pData, size_t uDataSize)
{
    BOOL                bResult         = false;
    BOOL                bRetCode        = false;
    IKG_Buffer*         piBuffer        = NULL;
    BYTE*               pbyData         = NULL;
    PROTOCOL_HEADER*    pHeader         = (PROTOCOL_HEADER*)pData;

    pHeader->uPakFlag = ppfSinglePackage;

    piBuffer = KG_MemoryCreateBuffer((unsigned)uDataSize);
    KGLOG_PROCESS_ERROR(piBuffer);

    pbyData = (BYTE*)piBuffer->GetData();
    KGLOG_PROCESS_ERROR(pbyData);

    memcpy(pbyData, pData, uDataSize);
    bRetCode = SendBuffer(pConnData, piBuffer);
    KGLOG_PROCESS_ERROR(bRetCode);

    bResult = true;
Exit0:
    KG_COM_RELEASE(piBuffer);
    return bResult;
}

BOOL KNetworkMgr::SendLargePackage(KG_CONNECTION_DATA* pConnData, BYTE* pbyData, size_t uDataSize)
{
    BOOL                bResult         = false;
    BOOL                bRetCode        = false;
    IKG_Buffer*         piBuffer        = NULL;
    PROTOCOL_HEADER*    pHeader         = (PROTOCOL_HEADER*)pbyData;
    uint32_t            uProtocolID     = 0;
    BYTE*               pbyOffset       = pbyData + sizeof(PROTOCOL_HEADER);
    size_t              uLeftSize       = uDataSize - sizeof(PROTOCOL_HEADER);
    size_t              uPakSize        = 0;

    uProtocolID = pHeader->uProtocolID;
    
    // 先发一个开始的头 PakFlag = ppfPackageHeader
    uPakSize = min(SHRT_MAX, uLeftSize);
    bRetCode = SendBlockPackage(pConnData, uProtocolID, uDataSize, pbyOffset, uPakSize, ppfPackageHeader);
    KGLOG_PROCESS_ERROR(bRetCode);
    uLeftSize -= uPakSize;
    pbyOffset += uPakSize;

    while (uLeftSize > SHRT_MAX)
    {
        KG_COM_RELEASE(piBuffer);

        uPakSize = min(SHRT_MAX, uLeftSize);
        bRetCode = SendBlockPackage(pConnData, uProtocolID, uDataSize, pbyOffset, uPakSize, ppfPackageBody);
        KGLOG_PROCESS_ERROR(bRetCode);
        uLeftSize   -= uPakSize;
        pbyOffset   += uPakSize;
    }

    uPakSize = uLeftSize;
    bRetCode = SendBlockPackage(pConnData, uProtocolID, uDataSize, pbyOffset, uPakSize, ppfPackageTail);
    KGLOG_PROCESS_ERROR(bRetCode);
    uLeftSize   -= uPakSize;
    pbyOffset   += uPakSize;

    KGLOG_PROCESS_ERROR(uLeftSize == 0);

    bResult = true;
Exit0:
    KG_COM_RELEASE(piBuffer);
    return bResult;
}

BOOL KNetworkMgr::SendBlockPackage(
    KG_CONNECTION_DATA* pConnData, uint32_t uProtocolID,
    size_t nOrginSize, BYTE* pbyData, size_t uDataSize, uint8_t uPakFlag
)
{
    BOOL                bResult         = false;
    BOOL                bRetCode        = false;
    IKG_Buffer*         piBuffer        = NULL;
    BYTE*               pbyBufferData   = NULL;
    PROTOCOL_HEADER*    pHeader         = NULL;

    KGLOG_PROCESS_ERROR(uDataSize + sizeof(PROTOCOL_HEADER) < USHRT_MAX);

    piBuffer = KG_MemoryCreateBuffer((unsigned)uDataSize + sizeof(PROTOCOL_HEADER));
    KGLOG_PROCESS_ERROR(piBuffer);
        
    pbyBufferData = (BYTE*)piBuffer->GetData();
    KGLOG_PROCESS_ERROR(pbyBufferData);

    pHeader = (PROTOCOL_HEADER*)pbyBufferData;
    KGLOG_PROCESS_ERROR(pHeader);

    pHeader->uProtocolID = uProtocolID;
    pHeader->uPakSize    = nOrginSize;
    pHeader->uPakFlag    = uPakFlag;
    memcpy(
        pbyBufferData + sizeof(PROTOCOL_HEADER), pbyData, uDataSize
    );

    bRetCode = SendBuffer(pConnData, piBuffer);
    KGLOG_PROCESS_ERROR(bRetCode);

    bResult = true;
Exit0:
    return bResult;
}

void KNetworkMgr::Broadcast(void* pData, size_t nDataSize)
{
    for (int i = 0; i < m_nMaxConnection; i++)
    {
        if (m_ConnectionDataList[i].piSocketStream == NULL)
            continue;

        if (m_ConnectionDataList[i].bSendError)
            continue;

        Send(i, pData, nDataSize);
    }
}

//////////////////////////////////////////////////////////////////////////
BOOL KNetworkMgr::BroadcastMessage(const char* pszMessage)
{
    BOOL                            bResult         = false;
    IKG_Buffer*                     piBuffer        = NULL;
    SERVER_TO_EDITOR_SEND_MESSAGE*  pSendMessage    = NULL;
    size_t                          nPakSize        = 0;
    size_t                          nMessageLen     = 0;

    nMessageLen = strlen(pszMessage);
    nPakSize = (unsigned)sizeof(SERVER_TO_EDITOR_SEND_MESSAGE) + nMessageLen + 1;
    piBuffer = KG_MemoryCreateBuffer(nPakSize);
    KGLOG_PROCESS_ERROR(piBuffer);

    pSendMessage = (SERVER_TO_EDITOR_SEND_MESSAGE*)piBuffer->GetData();
    KGLOG_PROCESS_ERROR(pSendMessage);

    pSendMessage->uProtocolID = server_to_editor_send_message;
    strncpy(pSendMessage->szMessage, pszMessage, nMessageLen);
    pSendMessage->szMessage[nMessageLen] = 0;

    Broadcast(pSendMessage, nPakSize);

    bResult = true;
Exit0:
    KG_COM_RELEASE(piBuffer);
    return bResult;
}

//////////////////////////////////////////////////////////////////////////
BOOL KNetworkMgr::BroadcastJsonFileChange(EDITOR_TO_SERVER_SEND_JSONFILECHANGE* pRecived,BYTE* pbyData, size_t uDataLen)
{
    BOOL                                    bResult         = false;
    IKG_Buffer*                             piBuffer        = NULL;
    SERVER_TO_EDITOR_SEND_JSONFILECHANGE*   pSendMessage    = NULL;
    size_t                                  nPakSize        = 0;
	size_t                                  nJsonSize       = strlen(pRecived->szJsonFile);

    nPakSize = sizeof(SERVER_TO_EDITOR_SEND_JSONFILECHANGE) + nJsonSize + 1;
    piBuffer = KG_MemoryCreateBuffer(nPakSize);
    KGLOG_PROCESS_ERROR(piBuffer);

    pSendMessage = (SERVER_TO_EDITOR_SEND_JSONFILECHANGE*)piBuffer->GetData();
    KGLOG_PROCESS_ERROR(pSendMessage);

    pSendMessage->uProtocolID = server_to_editor_send_jsonfilechange;

    strncpy(pSendMessage->szFileName, pRecived->szFileName, sizeof(pSendMessage->szFileName));
    pSendMessage->szFileName[sizeof(pSendMessage->szFileName) - 1] = 0;

	strncpy(pSendMessage->szJsonFile, pRecived->szJsonFile, nJsonSize);
	pSendMessage->szJsonFile[nJsonSize] = 0;

    Broadcast(pSendMessage, nPakSize);

    bResult = true;
Exit0:
    KG_COM_RELEASE(piBuffer);
    return bResult;
}

//////////////////////////////////////////////////////////////////////////
void KNetworkMgr::ShutDown(int nConnIndex)
{
    BOOL        bRetCode    = false;
    
    assert(nConnIndex >= 0 && nConnIndex < m_nMaxConnection);

    assert(m_ConnectionDataList[nConnIndex].piSocketStream);

    m_ConnectionDataList[nConnIndex].piSocketStream->SetUserData((void*)(ptrdiff_t)-1);

    KG_COM_RELEASE(m_ConnectionDataList[nConnIndex].piSocketStream);
    KG_COM_RELEASE(m_ConnectionDataList[nConnIndex].piJointBuffer);
    m_ConnectionDataList[nConnIndex].uJointOffset   = 0;

    KGLogPrintf(KGLOG_INFO, "Shutdown connection: %d\n", nConnIndex);
    
    m_ConnectionDataListFreeVector.push_back(nConnIndex);
}

//////////////////////////////////////////////////////////////////////////
void KNetworkMgr::OnHandshakeRequest(BYTE* pbyData, size_t uDataLen, int nConnIndex)
{
    EDITOR_TO_SERVER_HANDSHAKE_REQUEST* pHandshakeRequest   = (EDITOR_TO_SERVER_HANDSHAKE_REQUEST*)pbyData;

    if (pHandshakeRequest->uVersion != PROTOCOL_CURRENT_VERSION)
    {
        KGLogPrintf(KGLOG_INFO, "[network] %d conntion version error.", nConnIndex);
        ShutDown(nConnIndex);
    }
}

void KNetworkMgr::OnSendMessage(BYTE* pbyData, size_t uDataLen, int nConnIndex)
{
    EDITOR_TO_SERVER_SEND_MESSAGE*  pSendMessage    = (EDITOR_TO_SERVER_SEND_MESSAGE*)pbyData;
    
    pSendMessage->szMessage[uDataLen - sizeof(EDITOR_TO_SERVER_SEND_MESSAGE)] = 0;

	KGLogPrintf(KGLOG_INFO, "File Change: %d %s\n", nConnIndex,pSendMessage->szMessage);

    BroadcastMessage(pSendMessage->szMessage);
}

void KNetworkMgr::OnSendPing(BYTE* pbyData, size_t uDataLen, int nConnIndex)
{
	EDITOR_TO_SERVER_SEND_PING*  pSendMessage    = (EDITOR_TO_SERVER_SEND_PING*)pbyData;

	pSendMessage->szMessage[uDataLen - sizeof(EDITOR_TO_SERVER_SEND_PING)] = 0;

	//KGLogPrintf(KGLOG_INFO, "Ping: %d\n", nConnIndex);

	//BroadcastMessage(pSendMessage->szMessage);
}

void KNetworkMgr::OnSendJsonFileChange(BYTE* pbyData, size_t uDataLen, int nConnIndex)
{
	EDITOR_TO_SERVER_SEND_JSONFILECHANGE*  pSendMessage    = (EDITOR_TO_SERVER_SEND_JSONFILECHANGE*)pbyData;

	pSendMessage->szJsonFile[uDataLen - sizeof(EDITOR_TO_SERVER_SEND_JSONFILECHANGE)] = 0;
    pSendMessage->szFileName[sizeof(pSendMessage->szFileName) - 1] = 0;
	KGLogPrintf(KGLOG_INFO, "Json Memory Change: %d %s %s\n", nConnIndex,pSendMessage->szFileName, pSendMessage->szJsonFile);
	//KGLogPrintf(KGLOG_INFO, "Recived Json File: %d %s\n", nConnIndex,pSendMessage->szJsonFile);

	BroadcastJsonFileChange(pSendMessage,pbyData,uDataLen);
}
