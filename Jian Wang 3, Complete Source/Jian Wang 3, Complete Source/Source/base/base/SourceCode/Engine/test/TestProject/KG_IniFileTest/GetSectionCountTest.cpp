#include "GetSectionCountTest.h"
#include "KGT_IniFileTest.h"

void KGT_GetSectionCountTest::setUp()
{

}
void KGT_GetSectionCountTest::tearDown()
{

}

void KGT_GetSectionCountTest::TestGetSectionCount_01()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    int nSectionCount = -1;

    KG_CASE_INFO("没有section记录", "");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nSectionCount = piIniFile->GetSectionCount();
    KG_PROCESS_ERROR(nSectionCount == 0);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetSectionCountTest::TestGetSectionCount_02()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2",
        "--Server.name=mysql"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    int nSectionCount = -1;

    KG_CASE_INFO("有section记录", "");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nSectionCount = piIniFile->GetSectionCount();
    KG_PROCESS_ERROR(nSectionCount == 2);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}