#ifndef _KSO_CLIENT_INTERFACE_H_
#define _KSO_CLIENT_INTERFACE_H_

typedef void (*ProtocolCallBackFunc)(BYTE* pbyData, size_t nDataSize);

struct IKConnector
{
    virtual BOOL Init(const char cszServerIP[], int nPort) = 0;
    virtual void UnInit() = 0;
    virtual void Activate() = 0;
    virtual void SetCallBackFunc(uint32_t uProtocolID, ProtocolCallBackFunc Func) = 0;
    virtual BOOL Send(void* pbyData, size_t nDataSize) = 0;
};

IKConnector* CreateConnector();

#endif // _KSO_CLIENT_INTERFACE_H_
