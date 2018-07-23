#ifndef _KNETWORK_MGR_H_
#define _KNETWORK_MGR_H_

#include <vector>
#include "Common/KG_Socket.h"
#include "KSOEditorProtocol.h"

#define KG_MAX_ACCEPT_EACH_WAIT 64
#define KG_RECV_BUFFER_SIZE     (128 * 1024 * 10)
#define KG_SEND_BUFFER_SIZE     (128 * 1024 * 10)
#define PING_CYCLE              60

struct KG_CONNECTION_DATA
{
    KG_CONNECTION_DATA()
    {
        piSocketStream      = NULL;
        nLastPingTime       = 0;
        bSendError          = false;
        piJointBuffer       = NULL;
        uJointOffset        = 0;
    }
    IKG_SocketStream*   piSocketStream;
    IKG_Buffer*         piJointBuffer;
    uint32_t            uJointOffset;
    time_t              nLastPingTime;
    BOOL                bSendError;
};

class KNetworkMgr
{
public:
    KNetworkMgr();
    virtual ~KNetworkMgr();

    BOOL Init(const char* szLocalIP, int nListenPort, int nMaxConnection);
    void UnInit();

    KG_CONNECTION_DATA* GetConnectionData(int nConnIndex);

    void Process();
    void ProcessNewConnection(IKG_SocketStream* piSocket);
    BOOL ProcessPackage(IKG_SocketStream* piSocket);
    
    void ProcessSinglePackage(int nConnIndex, PROTOCOL_HEADER* pHeader, size_t uPakSize);
    void ProcessLargePackageBegin(int nConnIndex, PROTOCOL_HEADER* pHeader, size_t uPakSize);
    void ProcessLargePackage(int nConnIndex, PROTOCOL_HEADER* pHeader, size_t uPakSize);
    void ProcessLargePackageEnd(int nConnIndex, PROTOCOL_HEADER* pHeader, size_t uPakSize);

    BOOL Send(int nConnIndex, void* pData, size_t nDataSize);
    BOOL SendBuffer(KG_CONNECTION_DATA* pConnData, IKG_Buffer* piBuffer);
    BOOL SendSinglePackage(KG_CONNECTION_DATA* pConnData, void* pData, size_t uDataSize);
    BOOL SendLargePackage(KG_CONNECTION_DATA* pConnData, BYTE* pbyData, size_t uDataSize);
    BOOL SendBlockPackage(KG_CONNECTION_DATA* pConnData, uint32_t uProtocolID, size_t nOrginSize, BYTE* pbyData, size_t uDataSize, uint8_t uPakFlag);

    void Broadcast(void* pData, size_t nDataSize);

    BOOL BroadcastMessage(const char* pszMessage);

	BOOL BroadcastJsonFileChange(EDITOR_TO_SERVER_SEND_JSONFILECHANGE* pRecived,BYTE* pbyData, size_t uDataLen);

private:
    void ShutDown(int nConnIndex);
    
	typedef void (KNetworkMgr::*PROCESS_PROTOCOL_FUNC)(BYTE* pbyData, size_t uDataLen, int nConnIndex);
	PROCESS_PROTOCOL_FUNC	m_ProcessProtocolFuns[editor_to_server_end];    
    size_t                  m_uProtocolSize[editor_to_server_end];

    void    OnHandshakeRequest(BYTE* pbyData, size_t uDataLen, int nConnIndex);
    void    OnSendMessage(BYTE* pbyData, size_t uDataLen, int nConnIndex);
	void    OnSendPing(BYTE* pbyData, size_t uDataLen, int nConnIndex);
	void    OnSendJsonFileChange(BYTE* pbyData, size_t uDataLen, int nConnIndex);

private:
    int                     m_nMaxConnection;
    int                     m_nEventCount;
    int                     m_nNextCheckConnection;
    KG_SocketServerAcceptor m_SocketServerAcceptor;
    KG_SOCKET_EVENT*        m_pSocketEvent;
    
    typedef vector<unsigned>                KG_CONNECTION_DATA_LIST_FREE_VECTOR;
    KG_CONNECTION_DATA_LIST_FREE_VECTOR     m_ConnectionDataListFreeVector;

    KG_CONNECTION_DATA*     m_ConnectionDataList;

};

#endif // _KNETWORK_MGR_H_