#include "stdafx.h"
#include "KSOEditor.h"
#include "KNetworkMgr.h"

KSOEditor* g_pSOEditor = NULL;

KSOEditor::KSOEditor()
{
    m_bRunFlag = true;
}

KSOEditor::~KSOEditor()
{
}

BOOL KSOEditor::Init()
{
    BOOL        bResult             = false;
    int         nRetCode            = 0;
    BOOL        bNetWorkInitFlag    = false;
    IIniFile*   piFile              = NULL;
    int         nPort               = 0;
    int         nMaxConnection      = 0;
    char        szLocalIP[32];

    g_SetRootPath(NULL);

    piFile = g_OpenIniFile("KSOEditorServer.ini");
    KGLOG_PROCESS_ERROR(piFile);

    piFile->GetString("Server", "IP", "127.0.0.1", szLocalIP, sizeof(szLocalIP));
    piFile->GetInteger("Server", "Port", 0, &nPort);
    piFile->GetInteger("Server", "MaxConnection", 100, &nMaxConnection);

    m_pNetworkMgr = new KNetworkMgr;
    KGLOG_PROCESS_ERROR(m_pNetworkMgr);
    
    nRetCode = m_pNetworkMgr->Init(szLocalIP, nPort, nMaxConnection);
    KGLOG_PROCESS_ERROR(nRetCode);
    bNetWorkInitFlag = true;

    bResult = true;
Exit0:
    if (!bResult)
    {
        if (bNetWorkInitFlag)
        {
            m_pNetworkMgr->UnInit();
            bNetWorkInitFlag = false;
        }
        SAFE_DELETE(m_pNetworkMgr);
    }

    KG_COM_RELEASE(piFile);
    return bResult;
}

void KSOEditor::UnInit()
{
    if (m_pNetworkMgr)
    {
        m_pNetworkMgr->UnInit();
    }
    SAFE_DELETE(m_pNetworkMgr);

    return;
}

void KSOEditor::Run()
{
    KGLOG_PROCESS_ERROR(m_pNetworkMgr);

    while (m_bRunFlag)
    {
        m_pNetworkMgr->Process();
        KGThread_Sleep(100);
    }
Exit0:
    return;
}

void KSOEditor::Quit()
{
    m_bRunFlag = false;
}

