//////////////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   KG_Socket.h
//  Version     :   1.0
//  Creater     :   Freeway Chen, ZhaoChunFeng
//  Date        :   2004-11-11 18:32:21
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////

#ifndef _KG_SOCKET_H_
#define _KG_SOCKET_H_

#ifdef WIN32
	#include <winsock2.h>
	#include <windows.h>
#else
    #include <netdb.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <string.h>
    #include <ctype.h>
    #include <time.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <sys/time.h>
    #include <sys/socket.h>
    #include <sys/file.h>
    #include <sys/ioctl.h>
    #include <sys/select.h>
    #include <sys/types.h>
    #include <sys/param.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <errno.h>

    #include <time.h>
    #include <sys/epoll.h>

#endif	//WIN32

#include <vector>
using namespace std;

#include "KSUnknown.h"
#include "KG_Memory.h"
#include "Engine/KMutex.h"


/************************************************************************/
/*     you should call WSAStartup(...) and WSACleanup(...) in win32     */                                                                     
/************************************************************************/

enum ENCODE_DECODE_MODE
{
    KSG_ENCODE_DECODE_NONE = -1,
    KSG_ENCODE_DECODE = 0,
    EASYCRYPT_ENCODE_DECODE,
    KSG_ENCODE_DECODE_SIMPLE,
    KSG_ENCODE_DECODE_DYNAMIC
};

struct IKG_SocketStream : IUnknown
{

    virtual int SetTimeout(const timeval *pTimeout)  = 0;

    // return -1: error, 0: timeout, 1: success
    virtual int CheckCanSend(const timeval *pTimeout) = 0;
    
    // return -1: error, 0: timeout, 1: success, don't send a package > 65500 bytes
    virtual int Send(IKG_Buffer *piBuffer) = 0;

    // return -1: error, 0: timeout, 1: success
    virtual int CheckCanRecv(const timeval *pTimeout) = 0;

    // return -2: again, -1: error, 0: timeout, 1: success
    virtual int Recv(IKG_Buffer **piRetBuffer)  = 0;
    
    virtual int IsAlive() = 0;
    
    virtual int GetRemoteAddress(struct in_addr *pRemoteIP, u_short *pusRemotePort) = 0;

    virtual int SetUserData(void *pvUserData)      = 0;

    virtual void *GetUserData() = 0;
};


class KG_SocketConnector
{
public:
    KG_SocketConnector();

    virtual IKG_SocketStream *Connect(
        const char cszIPAddress[],     int nPort
    );

    virtual IKG_SocketStream *ProxyConnect(
        const char cszProxyAddress[],  int nProxyPort, 
        const char cszProxyUsername[], const char cszProxyPassword[], 
        const char cszIPAddress[],     int nPort
    );

    virtual IKG_SocketStream *ConnectSecurity(
        const char cszIPAddress[],     int nPort, 
        ENCODE_DECODE_MODE EncodeDecodeMode
    );

    virtual IKG_SocketStream *ProxyConnectSecurity(
        const char cszProxyAddress[],  int nProxyPort, 
        const char cszProxyUsername[], const char cszProxyPassword[], 
        const char cszIPAddress[],     int nPort, 
        ENCODE_DECODE_MODE EncodeDecodeMode
    );

    // Bind a local IP to use one Network Interface Card. 
    // if cszLocalIPAddress is NULL(or "") then is bind in INADDR_ANY address.
    // Bind must call before connect, or it takes no effect. 
    // If you never call Bind, it means bind all. 
    // Binding to a specific port number other than port 0 is discouraged for client applications, 
    // since there is a danger of conflicting with another socket already using that port number.
    virtual int Bind(
        const char cszLocalIPAddress[], int nPort = 0
    );

protected:
    struct sockaddr_in m_BindLoaclAddr;
};

class KG_BufferedSocketConnector : public KG_SocketConnector
{
public:
    virtual IKG_SocketStream *Connect(
        const char cszIPAddress[],     int nPort
    );

    virtual IKG_SocketStream *ProxyConnect(
        const char cszProxyAddress[],  int nProxyPort, 
        const char cszProxyUsername[], const char cszProxyPassword[], 
        const char cszIPAddress[],     int nPort
    );
};

class KG_SocketAcceptor
{
public:
    KG_SocketAcceptor();
    ~KG_SocketAcceptor();

    // cszIPAddress: local ip. if cszIPAddress is NULL(or "") then is bind in INADDR_ANY address
    virtual int Open(const char cszIPAddress[], int nPort);    //when succeed, return true,otherwise return false;
                                                      //ulAddress default is INADDR_ANY
    virtual int SetTimeout(const timeval *pTimeout);

    virtual IKG_SocketStream *Accept();

    virtual IKG_SocketStream *AcceptSecurity(ENCODE_DECODE_MODE EncodeDecodeMode);

    virtual int Close();

private:
    int     m_nListenSocket;
    timeval m_Timeout;

	KMutex m_AcceptLock;
};


#ifdef EPOLLIN
#define KG_SOCKET_EVENT_IN      EPOLLIN
#else
#define KG_SOCKET_EVENT_IN      0x001
#endif

#define KG_SOCKET_EVENT_ACCEPT  (1 << 23)   

struct KG_SOCKET_EVENT
{
    unsigned          uEventFlag;
    IKG_SocketStream *piSocket;
};


class IKG_SocketServerAcceptor
{
public:
    // cszIPAddress: local ip. if cszIPAddress is NULL(or "") then is bind in INADDR_ANY address
    virtual int Init(
        const char cszIPAddress[], int nPort,
        int nMaxAcceptEachWait,
        int nMaxRecvBufSizePerSocket,
        int nMaxSendBufSizePerSocket,
        ENCODE_DECODE_MODE EncodeDecodeMode, 
        void *pvContext
    ) = 0;    //when succeed, return true,otherwise return false;
                                                      
    //when succeed, return true,otherwise return false;
    virtual int UnInit(void *pvContext) = 0;    

    //when succeed, return true,otherwise return false;
    virtual int Wait(int nEventCount, KG_SOCKET_EVENT *pEvent, int *pnRetEventCount) = 0;
};


#ifdef WIN32
typedef vector<IKG_SocketStream *>    KG_SOCKET_VECTOR;
#else
// linux
typedef vector<struct epoll_event>  KG_SOCKET_EVENT_VECTOR;
#endif

class KG_SocketServerAcceptor : public IKG_SocketServerAcceptor
{
public:
    virtual int Init(
        const char cszIPAddress[], int nPort,
        int nMaxAcceptEachWait,
        int nMaxRecvBufSizePerSocket,
        int nMaxSendBufSizePerSocket,
        ENCODE_DECODE_MODE EncodeDecodeMode, 
        void *pvContext
    );

    virtual int UnInit(void *pvContext);

    virtual int Wait(int nEventCount, KG_SOCKET_EVENT *pEvent, int *pnRetEventCount);

private:
    int             _WaitProcessAccept(int nEventCount, KG_SOCKET_EVENT *pEvent, int *pnRetEventCount);
    #ifdef WIN32
    int             _WaitProcessRecvOrDestory(int nEventCount, KG_SOCKET_EVENT *pEvent, int *pnRetEventCount);
    int             _ProcessSocketVectorDestory();
    #else
    // linux
    int             _WaitProcessRecv(int nEventCount, KG_SOCKET_EVENT *pEvent, int *pnRetEventCount);
    #endif


private:
    int                     m_nMaxAcceptEachWait;
    int                     m_nMaxRecvBufSizePerSocket;
    int                     m_nMaxSendBufSizePerSocket;

    int                     m_nListenSocket;
    ENCODE_DECODE_MODE      m_EncodeDecodeMode;

    #ifdef WIN32
    int                     m_nLastWaitPos;
    KG_SOCKET_VECTOR        m_SocketVector;
    #else
    // linux
    int                     m_nEpollHandle;
    KG_SOCKET_EVENT_VECTOR  m_SocketEventVector;
    #endif
};

#endif	//_KG_SOCKET_H_
