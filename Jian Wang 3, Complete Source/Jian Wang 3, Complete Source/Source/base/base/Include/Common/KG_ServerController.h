////////////////////////////////////////////////////////////////////////////////
//
//  FileName    : KG_ServerController.h
//  Version     : 1.0
//  Creator     : Wu Caizhong
//  Create Date : 2008-5-26 15:04:24
//  Comment     :
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _INCLUDE_KG_SERVERCONTROLLER_H_
#define _INCLUDE_KG_SERVERCONTROLLER_H_

#include "Common/KG_Socket.h"
#include <string>

////////////////////////////////////////////////////////////////////////////////
// if is windows, should link psapi.lib; ws2_2.lib
enum KG_EMPTY_COMMAND_LINE_PROCESS
{
    EMPTY_ARG_FAILED,           // return fail
    EMPTY_ARG_AS_START_COMMAND, // treat as start command
};
class KG_ServerController
{
public:
    KG_ServerController(void);
    ~KG_ServerController(void);

    int Run(
        int argc, char *argv[],
        const char cszStartCommand[], // command to start server, normally is "start"
        const char cszDaemonOption[], // option of start server to run as daemon, normally is "--daemon"
        KG_EMPTY_COMMAND_LINE_PROCESS eEmptyCommandProcess,
        int *pnRetRunAsServerFlag
    );

    // get command line of the client instance, the argv[0] always module name
    // if no new command, the *pnRetArgc be set to 0, and *pnRetArgv set to null
    int GetCommand(int *pnRetArgc, char ***pnRetArgv);

    // return result to client instance
    int Printf(const char cszFormat[], ...);

private:
    int _GetProcessFullPathName(int nProcessID, unsigned uNameBufferSize, char *pszRetName);
    int _GetFlagFileName(std::string *psRetFileName);
    int _CreateFlagFile(int nListenPort);
    int _RemoveFlagFile();
    // (*pnRetServerListenPort) just valid when *pnRetServerExistFlag is true;
    int _IsServerExist(int *pnRetServerExistFlag, int *pnRetListenPort);

    int _ListenOnUnusedPort();
    int _Accept(int *pnRetClientSocket); // non block
    int _StopListen();

    int _IsRunAsDaemonServer();

    int _CreateDaemonServer(int argc, char * argv[]);
    int _RunServer();
    int _RunClient(int argc, char * argv[], int nStartCommandFlag, int nListenPort);
    int _Clear();

private:
    KG_SocketAcceptor   m_Acceptor;
    int                 m_nListenFlag;

    IKG_SocketStream   *m_piSocketStream;
    IKG_Buffer         *m_piArgumentBuf;
    enum CLIENT_STATUS
    {
        CLIENT_NOT_CONNECT,
        CLIENT_WAIT_FOR_COMMAND,
        CLIENT_SEND_RESULT,
        CLIENT_NOTIFY_CLOSE,
    };
    CLIENT_STATUS    m_eClientStatus;
};

#endif //_INCLUDE_KG_SERVERCONTROLLER_H_
