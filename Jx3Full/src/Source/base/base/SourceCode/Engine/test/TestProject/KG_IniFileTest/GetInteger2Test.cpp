#include "GetInteger2Test.h"
#include "KGT_IniFileTest.h"

void KGT_GetInteger2Test::setUp()
{

}
void KGT_GetInteger2Test::tearDown()
{

}

void KGT_GetInteger2Test::TestGetInteger2_01()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2",
        "--Database.name=mysql"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "";
    char *pszKey = "version";
    int  nValue1 = -1;
    int  nValue2 = -1;

    KG_CASE_INFO("输入的lpSection为空,其他参数不为空", "配置文件或命令行有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger2(pszSection, pszKey, &nValue1, &nValue2);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nValue1 == -1 && nValue2 == -1);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetInteger2Test::TestGetInteger2_02()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2",
        "--Database.name=mysql"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "Version";
    char *pszKey = "";
    int nValue1 = -1;
    int nValue2 = -1;

    KG_CASE_INFO("输入的lpKeyName为空,其他参数不为空", "配置文件或命令行有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger2(pszSection, pszKey, &nValue1, &nValue2);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nValue1 == -1 && nValue2 == -1);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetInteger2Test::TestGetInteger2_03()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2",
        "--Database.name=mysql"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "";
    char *pszKey = "";
    int nValue1 = -1;
    int nValue2 = -1;

    KG_CASE_INFO("输入的lpSection和lpKeyName为空,其他参数不为空", "配置文件或命令行有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger2(pszSection, pszKey, &nValue1, &nValue2);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nValue1 == -1 && nValue2 == -1);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetInteger2Test::TestGetInteger2_04()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2",
        "--Database.name=mysql"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "Version";
    char *pszKey = "name";
    int nValue1 = -1;
    int nValue2 = -1;

    KG_CASE_INFO("输入的lpSection存在,但输入的lpKeyName不存在", "配置文件或命令行有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger2(pszSection, pszKey, &nValue1, &nValue2);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nValue1 == -1 && nValue2 == -1);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetInteger2Test::TestGetInteger2_05()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2",
        "--Database.name=mysql"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "Server";
    char *pszKey = "name";
    int nValue1 = -1;
    int nValue2 = -1;

    KG_CASE_INFO("输入的lpSection不存在", "配置文件或命令行有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger2(pszSection, pszKey, &nValue1, &nValue2);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nValue1 == -1 && nValue2 == -1);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetInteger2Test::TestGetInteger2_06()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2",
        "--Database.name=mysql"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "Version";
    char *pszKey = "version";
    int nValue1 = -1;
    int nValue2 = -1;

    KG_CASE_INFO("输入的lpSection存在，且输入的lpKeyName存在,value不为空,且有1个值", "配置文件或命令行有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger2(pszSection, pszKey, &nValue1, &nValue2);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nValue1 == -1 && nValue2 == -1);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetInteger2Test::TestGetInteger2_07()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2,3",
        "--Database.name=mysql"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "Version";
    char *pszKey = "version";
    int nValue1 = -1;
    int nValue2 = -1;

    KG_CASE_INFO("输入的lpSection存在，且输入的lpKeyName存在,value不为空,且有2个正值", "配置文件或命令行有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger2(pszSection, pszKey, &nValue1, &nValue2);
    KG_PROCESS_ERROR(nRetCode);

    KG_PROCESS_ERROR(nValue1 == 2 && nValue2 == 3);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetInteger2Test::TestGetInteger2_08()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2,3,4",
        "--Database.name=mysql"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "Version";
    char *pszKey = "version";
    int nValue1 = -1;
    int nValue2 = -1;

    KG_CASE_INFO("输入的lpSection存在，且输入的lpKeyName存在,value不为空,且有3个值", "配置文件或命令行有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger2(pszSection, pszKey, &nValue1, &nValue2);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nValue1 == -1 && nValue2 == -1);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetInteger2Test::TestGetInteger2_09()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=-2,-3",
        "--Database.name=mysql"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "Version";
    char *pszKey = "version";
    int nValue1 = -1;
    int nValue2 = -1;

    KG_CASE_INFO("输入的lpSection存在，且输入的lpKeyName存在,value不为空,且有2个负值", "配置文件或命令行有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger2(pszSection, pszKey, &nValue1, &nValue2);
    KG_PROCESS_ERROR(nRetCode);

    KG_PROCESS_ERROR(nValue1 == -2 && nValue2 == -3);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetInteger2Test::TestGetInteger2_10()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=",
        "--Database.name=mysql"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "Version";
    char *pszKey = "version";
    int nValue1 = -1;
    int nValue2 = -1;

    KG_CASE_INFO("输入的lpSection存在,且输入的lpKeyName存在,value为空", "配置文件或命令行有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger2(pszSection, pszKey, &nValue1, &nValue2);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nValue1 == -1 && nValue2 == -1);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetInteger2Test::TestGetInteger2_11()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=ab,cd",
        "--Database.name=mysql"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "Version";
    char *pszKey = "version";
    int nValue1 = -1;
    int nValue2 = -1;

    KG_CASE_INFO("输入的lpSection存在,且输入的lpKeyName存在,value为非数字字符串", "配置文件或命令行有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger2(pszSection, pszKey, &nValue1, &nValue2);
    KG_PROCESS_ERROR(nRetCode);

    KG_PROCESS_ERROR(nValue1 == 0 && nValue2 == 0);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetInteger2Test::TestGetInteger2_12()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "";
    char *pszKey = "";
    int nValue1 = -1;
    int nValue2 = -1;

    KG_CASE_INFO("输入的lpSection和lpKeyName为空值", "配置文件或命令行没有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger2(pszSection, pszKey, &nValue1, &nValue2);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nValue1 == -1 && nValue2 == -1);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetInteger2Test::TestGetInteger2_13()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "Version";
    char *pszKey = "version";
    int nValue1 = -1;
    int nValue2 = -1;

    KG_CASE_INFO("输入的lpSection和lpKeyName为非空值", "配置文件或命令行没有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger2(pszSection, pszKey, &nValue1, &nValue2);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nValue1 == -1 && nValue2 == -1);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}