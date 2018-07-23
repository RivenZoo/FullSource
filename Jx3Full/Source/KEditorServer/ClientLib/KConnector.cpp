#include "stdafx.h"
#include "KConnector.h"
#include "Common/KG_Socket.h"

KConnector::KConnector()
{
    m_szServerIP[0]         = 0;
    m_nPort                 = 0;
    m_piSocket              = NULL;
    m_bSendErrorFlag        = false;
    m_nLastReconnectTime    = 0;
    m_piJointBuffer         = NULL;
    m_uJointOffset          = 0;
}

KConnector::~KConnector()
{
}

BOOL KConnector::Init(const char cszServerIP[], int nPort)
{
    BOOL                bResult     = false;
    BOOL                bRetCode    = false;
    IKG_SocketStream*   piSocket    = NULL;

    strncpy(m_szServerIP, cszServerIP, sizeof(m_szServerIP));
    m_szServerIP[sizeof(m_szServerIP) - 1] = 0;
    m_nPort = nPort;

    bRetCode = Connect(m_szServerIP, m_nPort);
    KGLOG_PROCESS_ERROR(bRetCode);

    bResult = true;
Exit0:
    KG_COM_RELEASE(piSocket);
    return bResult;
}

void KConnector::UnInit()
{
    KG_COM_RELEASE(m_piSocket);
}

void KConnector::SetCallBackFunc(uint32_t uProtocolID, ProtocolCallBackFunc Func)
{
    KGLOG_PROCESS_ERROR(uProtocolID > server_to_editor_begin && uProtocolID < server_to_editor_end);

    for (CALLBACK_LIST::iterator it = m_CallBackList[uProtocolID].begin(); it != m_CallBackList[uProtocolID].end(); ++it)
    {
        KGLOG_PROCESS_ERROR(*it != Func);
    }

    m_CallBackList[uProtocolID].push_back(Func);

Exit0:
    return;
}

void KConnector::Activate()
{
    BOOL    bResult     = false;
    int     nRetCode    = 0;
    time_t  nTimeNow    = time(NULL);

    if (m_piSocket == NULL && nTimeNow - m_nLastReconnectTime > RECONNECTION_CYCLE)
    {
        m_nLastReconnectTime = nTimeNow;
        KGLogPrintf(KGLOG_INFO, "[client] try reconnect ... ... [%s:%d]", m_szServerIP, m_nPort);
        nRetCode = Connect(m_szServerIP, m_nPort);
        KGLOG_PROCESS_ERROR(nRetCode);
    }
    KGLOG_PROCESS_ERROR(m_piSocket);

    while (true)
    {
        IKG_Buffer*         piBuffer        = NULL;
        BYTE*               pbyData         = NULL;
        size_t              nDataSize       = 0;
        PROTOCOL_HEADER*    pHeader         = NULL;
        timeval             TimeoutValue    = {0, 0};

        if (!m_piSocket)
            break;

        KGLOG_PROCESS_ERROR(!m_bSendErrorFlag);

        nRetCode = m_piSocket->CheckCanRecv(&TimeoutValue);
        if (nRetCode == -1)
        {
            m_bSendErrorFlag = true;
            break;
        }
        if (nRetCode == 0)
            break;  // if no data arrive

        nRetCode = m_piSocket->Recv(&piBuffer);
        if (nRetCode == -1)
        {
            m_bSendErrorFlag = true;
            break;
        }
        if (nRetCode == -2)
        {
            break;
        }
        if (nRetCode != 1)  // if timeout or error then error
        {
            m_bSendErrorFlag = true;
            break;
        }

        KGLOG_PROCESS_ERROR(piBuffer);
        pbyData = (BYTE*)piBuffer->GetData();
        KGLOG_PROCESS_ERROR(pbyData);
        nDataSize = piBuffer->GetSize();

        pHeader = (PROTOCOL_HEADER*)pbyData;
        KGLOG_PROCESS_ERROR(pHeader);
        KGLOG_PROCESS_ERROR(pHeader->uProtocolID > server_to_editor_begin && pHeader->uProtocolID < server_to_editor_end);

        switch (pHeader->uPakFlag)
        {
        case ppfSinglePackage:
            ProcessSinglePackage(pHeader, nDataSize);
            break;
        case ppfPackageHeader:
            ProcessLargePackageBegin(pHeader, nDataSize);
            break;
        case ppfPackageBody:
            ProcessLargePackage(pHeader, nDataSize);
            break;
        case ppfPackageTail:
            ProcessLargePackageEnd(pHeader, nDataSize);
            break;
        }
    }
    bResult = true;
Exit0:
    if (!bResult)
    {
        KG_COM_RELEASE(m_piSocket);
    }
    return;
}

BOOL KConnector::Send(void* pData, size_t nDataSize)
{
    BOOL        bResult     = false;
    BOOL        bRetCode    = false;

    if (nDataSize <= SHRT_MAX)
    {
        bRetCode = SendSinglePackage(pData, nDataSize);
        KGLOG_PROCESS_ERROR(bRetCode);
    }
    else
    {
        bRetCode = SendLargePackage((BYTE*)pData, nDataSize);
        KGLOG_PROCESS_ERROR(bRetCode);
    }

    bResult = true;
Exit0:
    return bResult;
}

BOOL KConnector::SendBuffer(IKG_Buffer* piBuffer)
{
    BOOL    bResult     = false;
    BOOL    bRetCode    = false;

    KGLOG_PROCESS_ERROR(!m_bSendErrorFlag);

    bRetCode = m_piSocket->Send(piBuffer);
    if (!bRetCode)
    {
        m_bSendErrorFlag = true;
        goto Exit0;
    }

    bResult = true;
Exit0:
    return bResult;
}

BOOL KConnector::SendSinglePackage(void* pData, size_t nDataSize)
{
    BOOL                bResult     = false;
    BOOL                bRetCode    = false;
    IKG_Buffer*         piBuffer    = NULL;
    void*               pDstData    = NULL;
    PROTOCOL_HEADER*    pHeader     = (PROTOCOL_HEADER*)pData;

    KGLOG_PROCESS_ERROR(m_piSocket);

    pHeader->uPakFlag = ppfSinglePackage;
    pHeader->uPakSize = nDataSize;

    piBuffer = KG_MemoryCreateBuffer((unsigned)nDataSize);
    KGLOG_PROCESS_ERROR(piBuffer);

    pDstData = piBuffer->GetData();
    KGLOG_PROCESS_ERROR(pDstData);

    memcpy(pDstData, pData, nDataSize);

    bRetCode = SendBuffer(piBuffer);
    KGLOG_PROCESS_ERROR(bRetCode);

    bResult = true;
Exit0:
    KG_COM_RELEASE(piBuffer);
    return bResult;
}

BOOL KConnector::SendLargePackage(BYTE* pbyData, size_t uDataSize)
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
    bRetCode = SendBlockPackage(uProtocolID, uDataSize, pbyOffset, uPakSize, ppfPackageHeader);
    KGLOG_PROCESS_ERROR(bRetCode);
    uLeftSize -= uPakSize;
    pbyOffset += uPakSize;

    while (uLeftSize > SHRT_MAX)
    {
        KG_COM_RELEASE(piBuffer);

        uPakSize = min(SHRT_MAX, uLeftSize);
        bRetCode = SendBlockPackage(uProtocolID, uDataSize, pbyOffset, uPakSize, ppfPackageBody);
        KGLOG_PROCESS_ERROR(bRetCode);
        uLeftSize   -= uPakSize;
        pbyOffset   += uPakSize;
    }

    uPakSize = uLeftSize;
    bRetCode = SendBlockPackage(uProtocolID, uDataSize, pbyOffset, uPakSize, ppfPackageTail);
    KGLOG_PROCESS_ERROR(bRetCode);
    uLeftSize   -= uPakSize;
    pbyOffset   += uPakSize;

    KGLOG_PROCESS_ERROR(uLeftSize == 0);

    bResult = true;
Exit0:
    KG_COM_RELEASE(piBuffer);
    return bResult;
}

BOOL KConnector::SendBlockPackage(uint32_t uProtocolID, size_t nOrginSize, BYTE* pbyData, size_t uDataSize, uint8_t uPakFlag)
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

    bRetCode = SendBuffer(piBuffer);
    KGLOG_PROCESS_ERROR(bRetCode);

    printf("%d\n", uDataSize);

    bResult = true;
Exit0:
    return bResult;
}

void KConnector::ProcessSinglePackage(PROTOCOL_HEADER* pHeader, size_t uPakSize)
{
    for (
        CALLBACK_LIST::iterator it = m_CallBackList[pHeader->uProtocolID].begin();
        it != m_CallBackList[pHeader->uProtocolID].end(); ++it
    )
    {
        ProtocolCallBackFunc Func = *it;
        (*Func)((BYTE*)pHeader, uPakSize);
    }
}

void KConnector::ProcessLargePackageBegin(PROTOCOL_HEADER* pHeader, size_t uPakSize)
{
    void*   pData    = NULL;

    KGLOG_PROCESS_ERROR(m_piJointBuffer == NULL);
    KGLOG_PROCESS_ERROR(pHeader->uPakSize > SHRT_MAX);

    m_piJointBuffer = KG_MemoryCreateBuffer(pHeader->uPakSize);
    KGLOG_PROCESS_ERROR(m_piJointBuffer);

    pData = m_piJointBuffer->GetData();
    KGLOG_PROCESS_ERROR(pData);

    memcpy(pData, pHeader, uPakSize);
    m_uJointOffset += uPakSize;

Exit0:
    return;
}

void KConnector::ProcessLargePackage(PROTOCOL_HEADER* pHeader, size_t uPakSize)
{
    BYTE*       pbyData     = NULL;
    BYTE*       pbyAddData  = NULL;
    size_t      uBufferSize = 0;
    size_t      uAddSize    = uPakSize - sizeof(PROTOCOL_HEADER);

    KGLOG_PROCESS_ERROR(m_piJointBuffer);

    pbyData = (BYTE*)m_piJointBuffer->GetData();
    KGLOG_PROCESS_ERROR(pbyData);

    pbyAddData = (BYTE*)pHeader + sizeof(PROTOCOL_HEADER);

    uBufferSize = m_piJointBuffer->GetSize();
    KGLOG_PROCESS_ERROR(m_uJointOffset + uAddSize <= uBufferSize);

    memcpy(pbyData + m_uJointOffset, pbyAddData, uAddSize);
    m_uJointOffset += uAddSize;

Exit0:
    return;
}

void KConnector::ProcessLargePackageEnd(PROTOCOL_HEADER* pHeader, size_t uPakSize)
{
    BYTE*       pbyData     = NULL;
    size_t      uBufferSize = 0;

    ProcessLargePackage(pHeader, uPakSize);
    
    uBufferSize = m_piJointBuffer->GetSize();
    KGLOG_PROCESS_ERROR(uBufferSize == m_uJointOffset);

    pbyData = (BYTE*)m_piJointBuffer->GetData();
    KGLOG_PROCESS_ERROR(pbyData);

    for (
        CALLBACK_LIST::iterator it = m_CallBackList[pHeader->uProtocolID].begin();
        it != m_CallBackList[pHeader->uProtocolID].end(); ++it
    )
    {
        ProtocolCallBackFunc Func = *it;
        (*Func)(pbyData, uBufferSize);
    }

Exit0:
    KG_COM_RELEASE(m_piJointBuffer);
    m_uJointOffset = 0;

    return;
}

//////////////////////////////////////////////////////////////////////////
BOOL KConnector::DoHandshakeRequest()
{
    BOOL                                bResult     = false;
    BOOL                                bRetCode    = false;
    EDITOR_TO_SERVER_HANDSHAKE_REQUEST  HandshakeRequest;

    HandshakeRequest.uProtocolID = editor_to_server_handshake_request;
    HandshakeRequest.uVersion    = PROTOCOL_CURRENT_VERSION;

    bRetCode = Send(&HandshakeRequest, sizeof(HandshakeRequest));
    KGLOG_PROCESS_ERROR(bRetCode);

    bResult = true;
Exit0:
    return bResult;
}
//////////////////////////////////////////////////////////////////////////

BOOL KConnector::Connect(const char cszServerIP[], int nPort)
{
    BOOL                bResult     = false;
    BOOL                bRetCode    = false;
    IKG_SocketStream*   piSocket    = NULL;
    KG_SocketConnector  Connector;

    piSocket = Connector.Connect(cszServerIP, nPort);
    KGLOG_PROCESS_ERROR(piSocket);
    
    piSocket->AddRef();
    m_piSocket = piSocket;
    
    m_bSendErrorFlag = false;

    bRetCode = DoHandshakeRequest();
    KGLOG_PROCESS_ERROR(bRetCode);

    bResult = true;
Exit0:
    KG_COM_RELEASE(piSocket);
    return bResult;
}

IKConnector* CreateConnector()
{
    return new KConnector();
}