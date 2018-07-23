// ClientTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "conio.h"
#include "KSOEditorProtocol.h"
#include "KSOClientInterface.h"
#include "Common/KG_Memory.h"

void OnSendMessage(BYTE* pbyData, size_t nDataSize)
{
    SERVER_TO_EDITOR_SEND_JSONFILECHANGE* pSendMessage = (SERVER_TO_EDITOR_SEND_JSONFILECHANGE*)pbyData;

    printf("%s:%s\n", pSendMessage->szFileName, pSendMessage->szJsonFile);
}

void DoSendMessage(IKConnector* piConnector, const char szMessage[])
{
    IKG_Buffer*                             piBuffer    = NULL;
    EDITOR_TO_SERVER_SEND_JSONFILECHANGE*   pSend       = NULL;
    size_t                                  uSize       = strlen(szMessage);
    size_t                                  uPakSize    = 0;

    uPakSize = sizeof(EDITOR_TO_SERVER_SEND_JSONFILECHANGE) + (64 * 1024) + 1;

    piBuffer = KG_MemoryCreateBuffer((unsigned)uPakSize);
    KGLOG_PROCESS_ERROR(piBuffer);

    pSend = (EDITOR_TO_SERVER_SEND_JSONFILECHANGE*)piBuffer->GetData();
    KGLOG_PROCESS_ERROR(pSend);

    pSend->uProtocolID = editor_to_server_send_jsonfilechange;
    strncpy(pSend->szFileName, "1234", sizeof(pSend->szFileName));
    pSend->szFileName[sizeof(pSend->szFileName) - 1] = 0;
    for (int i = 0; i < 64 * 1024; i++)
    {
        pSend->szJsonFile[i] = '1';
    }
    pSend->szJsonFile[64 * 1024] = 0;

    piConnector->Send(pSend, uPakSize);

Exit0:
    KG_COM_RELEASE(piBuffer);
    return;
}

void DoTransferFileData(IKConnector* piConnector, const char szFileBuffer, size_t uFileSize)
{

}

int _tmain(int argc, _TCHAR* argv[])
{
    IKConnector* piConnector     = CreateConnector();

    if (piConnector == NULL)
        return -1;

    piConnector->Init("127.0.0.1", 14811);
    piConnector->SetCallBackFunc(server_to_editor_send_jsonfilechange, OnSendMessage);
    while (true)
    {
        if (_kbhit())
        {
            char szMessage[128];
            gets(szMessage);
            DoSendMessage(piConnector, szMessage);
        }
        piConnector->Activate();
    }
    piConnector->UnInit();

	return 0;
}

