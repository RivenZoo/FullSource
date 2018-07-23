#ifndef _KCONNECTOR_H_
#define _KCONNECTOR_H_

#include <list>
#include "KSOClientInterface.h"
#include "KSOEditorProtocol.h"

#define RECONNECTION_CYCLE 10

class IKG_SocketStream;
class IKG_Buffer;
class KConnector : public IKConnector
{
public:
    KConnector();
    virtual ~KConnector();

    virtual BOOL Init(const char cszServerIP[], int nPort);
    virtual void UnInit();
    virtual void SetCallBackFunc(uint32_t uProtocolID, ProtocolCallBackFunc Func);

    virtual void Activate();

    virtual BOOL Send(void* pData, size_t uDataSize);
    BOOL SendBuffer(IKG_Buffer* piBuffer);
    BOOL SendSinglePackage(void* pData, size_t uDataSize);
    BOOL SendLargePackage(BYTE* pbyData, size_t uDataSize);
    BOOL SendBlockPackage(uint32_t uProtocolID, size_t nOrginSize, BYTE* pbyData, size_t uDataSize, uint8_t uPakFlag);

    void ProcessSinglePackage(PROTOCOL_HEADER* pHeader, size_t uPakSize);
    void ProcessLargePackageBegin(PROTOCOL_HEADER* pHeader, size_t uPakSize);
    void ProcessLargePackage(PROTOCOL_HEADER* pHeader, size_t uPakSize);
    void ProcessLargePackageEnd(PROTOCOL_HEADER* pHeader, size_t uPakSize);
    BOOL DoHandshakeRequest();

    typedef std::list<ProtocolCallBackFunc> CALLBACK_LIST;
    CALLBACK_LIST   m_CallBackList[server_to_editor_end];

private:
    BOOL Connect(const char cszServerIP[], int nPort);
private:
    char                m_szServerIP[32];
    int                 m_nPort;
    time_t              m_nLastReconnectTime;
    IKG_SocketStream*   m_piSocket;
    BOOL                m_bSendErrorFlag;
    IKG_Buffer*         m_piJointBuffer;
    uint32_t            m_uJointOffset;
};

#endif // _KCONNECTOR_H_
