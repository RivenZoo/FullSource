#include "stdafx.h"
#include "KSOEditorNetClient.h"

#include "conio.h"
#include "KSOEditorProtocol.h"
#include "KSOClientInterface.h"
#include "KG3DFileSynchronizationCient.h"

extern KG3DFileSynchronizationCient* g_lpFileSync;


void OnSendMessage(BYTE* pbyData, size_t nDataSize)
{
	SERVER_TO_EDITOR_SEND_MESSAGE* pSendMessage = (SERVER_TO_EDITOR_SEND_MESSAGE*)pbyData;

	printf("%s\n", pSendMessage->szMessage);

	g_lpFileSync->OnJsonFileChange(pSendMessage->szMessage);
}

void OnSendJsonFileChange(BYTE* pbyData, size_t nDataSize)
{
	SERVER_TO_EDITOR_SEND_JSONFILECHANGE* pSendMessage = (SERVER_TO_EDITOR_SEND_JSONFILECHANGE*)pbyData;

	printf("%s\n", pSendMessage->szFileName);

	g_lpFileSync->OnJsonFileChangeInMemory(pSendMessage->szFileName,pSendMessage->szJsonFile);
}

void DoSendMessage(IKConnector* piConnector, const char szMessage[])
{
	char                                szBuffer[256];
	EDITOR_TO_SERVER_SEND_MESSAGE*      pSend       = (EDITOR_TO_SERVER_SEND_MESSAGE*)szBuffer;
	size_t                              uSize       = strlen(szMessage);
	size_t                              uPakSize    = 0;

	uPakSize = sizeof(EDITOR_TO_SERVER_SEND_MESSAGE) + uSize + 1;

	pSend->uProtocolID = editor_to_server_send_message;
	strncpy(pSend->szMessage, szMessage, uSize);
	pSend->szMessage[uSize] = 0;

	piConnector->Send(pSend, uPakSize);
}

void DoSendJsonFileChange(IKConnector* piConnector,KG3DJsonFileHelper* pHelper)
{
	char                                szBuffer[25600];
	EDITOR_TO_SERVER_SEND_JSONFILECHANGE*      pSend = (EDITOR_TO_SERVER_SEND_JSONFILECHANGE*)szBuffer;
	size_t                              uSize       = pHelper->m_szJsonFileName.length();
	size_t                              uPakSize    = 0;

	Json::StyledWriter writer;
	string rewrite = writer.write( pHelper->m_Json );

	size_t                              uSizeJson      = rewrite.length();



	pSend->uProtocolID = editor_to_server_send_jsonfilechange;

	strncpy(pSend->szFileName, pHelper->m_szJsonFileName.c_str(), uSize);
	pSend->szFileName[ uSize ] = 0;

	strncpy(pSend->szJsonFile, rewrite.c_str(), uSizeJson);
	pSend->szJsonFile[ uSizeJson ] = 0;

	uPakSize = sizeof(EDITOR_TO_SERVER_SEND_JSONFILECHANGE) + uSizeJson + 1;

	piConnector->Send(pSend, uPakSize);
}

void DoSendPing(IKConnector* piConnector)
{
	char                                szBuffer[256];
	EDITOR_TO_SERVER_SEND_PING*         pSend       = (EDITOR_TO_SERVER_SEND_PING*)szBuffer;
	size_t                              uPakSize    = 0;

	uPakSize = sizeof(EDITOR_TO_SERVER_SEND_PING) + 1;

	pSend->uProtocolID = editor_to_server_send_ping;
	pSend->szMessage[0] = 0;

	piConnector->Send(pSend, uPakSize);
}


KSOEditorNetClient::KSOEditorNetClient(void)
{
	m_piConnector = NULL;
	m_dwLastPingTime = 0;
}


KSOEditorNetClient::~KSOEditorNetClient(void)
{
	if(m_piConnector)
	{
		m_piConnector->UnInit();
		m_piConnector = NULL;
	}

}

HRESULT KSOEditorNetClient::Init()
{
	m_piConnector     = CreateConnector();

	if (m_piConnector == NULL)
		return E_FAIL;

	m_piConnector->Init("127.0.0.1", 14811);
	m_piConnector->SetCallBackFunc(server_to_editor_send_message, OnSendMessage);
	m_piConnector->SetCallBackFunc(server_to_editor_send_jsonfilechange, OnSendJsonFileChange);

	return S_OK;
}

HRESULT KSOEditorNetClient::SendFileChange(const char szMessage[])
{
	if(!m_piConnector)
		return E_FAIL;

	DoSendMessage(m_piConnector, szMessage);

	return S_OK;
}

HRESULT KSOEditorNetClient::SendJsonFileChange(KG3DJsonFileHelper* pHelper)
{
	if(!m_piConnector)
		return E_FAIL;

	if(!pHelper)
		return E_FAIL;

	DoSendJsonFileChange(m_piConnector, pHelper);

	return S_OK;
}


HRESULT KSOEditorNetClient::Activate()
{
	if(!m_piConnector)
		return E_FAIL;
	
	m_piConnector->Activate();

	DWORD dwTime = timeGetTime();
	if(dwTime - m_dwLastPingTime>=1000)
	{
		DoSendPing(m_piConnector);
		m_dwLastPingTime = dwTime;
	}

	return S_OK;
}

HRESULT KSOEditorNetClient::Uninit()
{
	if(!m_piConnector)
		return E_FAIL;

	if(m_piConnector)
	{
		m_piConnector->UnInit();
		m_piConnector = NULL;
	}
	return S_OK;
}