#include "GetStringTest.h"
#include "KGT_IniFileTest.h"

void KGT_GetStringTest::setUp()
{

}
void KGT_GetStringTest::tearDown()
{

}

void KGT_GetStringTest::TestGetString_01()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szAgrv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2"
    };
    int nArgc = sizeof(szAgrv) / sizeof(szAgrv[0]);
    char *pszSection = "";
    char *pszKey = "";
    char *pszDefault = NULL;
    char szRetValue[IIniFile::INI_MAX_SUPPORT_VALUE_SIZE];
    szRetValue[0] = '\0';

    KG_CASE_INFO("参数正确性，default=null", "配置文件或命令行有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szAgrv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetString(
        pszSection, 
        pszKey, 
        pszDefault, 
        szRetValue, 
        sizeof(szRetValue) / sizeof(szRetValue[0])
    );
    KG_PROCESS_ERROR(!nRetCode);
    szRetValue[sizeof(szRetValue) / sizeof(szRetValue[0]) - 1] = '\0';

    KG_PROCESS_ERROR(szRetValue[0] == '\0');

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetStringTest::TestGetString_02()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szAgrv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2"
    };
    int nArgc = sizeof(szAgrv) / sizeof(szAgrv[0]);
    char *pszSection = "";
    char *pszKey = "version";
    char *pszDefault = "root";
    char szRetValue[IIniFile::INI_MAX_SUPPORT_VALUE_SIZE];
    szRetValue[0] = '\0';

    KG_CASE_INFO("输入的lpSection为空,其他参数不为空", "配置文件或命令行有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szAgrv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetString(
        pszSection, 
        pszKey, 
        pszDefault, 
        szRetValue, 
        sizeof(szRetValue) / sizeof(szRetValue[0])
    );
    KG_PROCESS_ERROR(!nRetCode);
    szRetValue[sizeof(szRetValue) / sizeof(szRetValue[0]) - 1] = '\0';
    
    nRetCode = strcmp(szRetValue, pszDefault);
    KG_PROCESS_ERROR(nRetCode == 0);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetStringTest::TestGetString_03()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szAgrv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2"
    };
    int nArgc = sizeof(szAgrv) / sizeof(szAgrv[0]);
    char *pszSection = "Version";
    char *pszKey = "";
    char *pszDefault = "root";
    char szRetValue[IIniFile::INI_MAX_SUPPORT_VALUE_SIZE];
    szRetValue[0] = '\0';

    KG_CASE_INFO("输入的lpKeyName为空,其他参数不为空", "配置文件或命令行有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szAgrv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetString(
        pszSection, 
        pszKey, 
        pszDefault, 
        szRetValue, 
        sizeof(szRetValue) / sizeof(szRetValue[0])
    );
    KG_PROCESS_ERROR(!nRetCode);
    szRetValue[sizeof(szRetValue) / sizeof(szRetValue[0]) - 1] = '\0';

    nRetCode = strcmp(szRetValue, pszDefault);
    KG_PROCESS_ERROR(nRetCode == 0);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetStringTest::TestGetString_04()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szAgrv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2"
    };
    int nArgc = sizeof(szAgrv) / sizeof(szAgrv[0]);
    char *pszSection = "";
    char *pszKey = "";
    char *pszDefault = "root";
    char szRetValue[IIniFile::INI_MAX_SUPPORT_VALUE_SIZE];
    szRetValue[0] = '\0';

    KG_CASE_INFO("输入的lpSection和lpKeyName为空,其他参数不为空", "配置文件或命令行有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szAgrv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetString(
        pszSection, 
        pszKey, 
        pszDefault, 
        szRetValue, 
        sizeof(szRetValue) / sizeof(szRetValue[0])
    );
    KG_PROCESS_ERROR(!nRetCode);
    szRetValue[sizeof(szRetValue) / sizeof(szRetValue[0]) - 1] = '\0';

    nRetCode = strcmp(szRetValue, pszDefault);
    KG_PROCESS_ERROR(nRetCode == 0);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetStringTest::TestGetString_05()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szAgrv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2"
    };
    int nArgc = sizeof(szAgrv) / sizeof(szAgrv[0]);
    char *pszSection = "Version";
    char *pszKey = "name";
    char *pszDefault = "root";
    char szRetValue[IIniFile::INI_MAX_SUPPORT_VALUE_SIZE];
    szRetValue[0] = '\0';

    KG_CASE_INFO("输入的lpSection存在，但输入的lpKeyName不存在", "配置文件或命令行有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szAgrv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetString(
        pszSection, 
        pszKey, 
        pszDefault, 
        szRetValue, 
        sizeof(szRetValue) / sizeof(szRetValue[0])
    );
    KG_PROCESS_ERROR(!nRetCode);
    szRetValue[sizeof(szRetValue) / sizeof(szRetValue[0]) - 1] = '\0';

    nRetCode = strcmp(szRetValue, pszDefault);
    KG_PROCESS_ERROR(nRetCode == 0);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetStringTest::TestGetString_06()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szAgrv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2"
    };
    int nArgc = sizeof(szAgrv) / sizeof(szAgrv[0]);
    char *pszSection = "Database";
    char *pszKey = "version";
    char *pszDefault = "root";
    char szRetValue[IIniFile::INI_MAX_SUPPORT_VALUE_SIZE];
    szRetValue[0] = '\0';

    KG_CASE_INFO("输入的lpSection不存在", "配置文件或命令行有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szAgrv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetString(
        pszSection, 
        pszKey, 
        pszDefault, 
        szRetValue, 
        sizeof(szRetValue) / sizeof(szRetValue[0])
    );
    KG_PROCESS_ERROR(!nRetCode);
    szRetValue[sizeof(szRetValue) / sizeof(szRetValue[0]) - 1] = '\0';

    nRetCode = strcmp(szRetValue, pszDefault);
    KG_PROCESS_ERROR(nRetCode == 0);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetStringTest::TestGetString_07()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szAgrv[] = {
        "KG_GoddessD.exe",
        "--Version.version="
    };
    int nArgc = sizeof(szAgrv) / sizeof(szAgrv[0]);
    char *pszSection = "Version";
    char *pszKey = "version";
    char *pszDefault = "root";
    char szRetValue[IIniFile::INI_MAX_SUPPORT_VALUE_SIZE];
    szRetValue[0] = '\0';

    KG_CASE_INFO("输入的lpSection存在，且输入的lpKeyName存在，value长度为0", "配置文件或命令行有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szAgrv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetString(
        pszSection, 
        pszKey, 
        pszDefault, 
        szRetValue, 
        sizeof(szRetValue) / sizeof(szRetValue[0])
    );
    KG_PROCESS_ERROR(nRetCode);
    szRetValue[sizeof(szRetValue) / sizeof(szRetValue[0]) - 1] = '\0';

    KG_PROCESS_ERROR(szRetValue[0] == '\0');

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetStringTest::TestGetString_08()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szAgrv[] = {
        "KG_GoddessD.exe",
        "--Version.version=mysql"
    };
    int nArgc = sizeof(szAgrv) / sizeof(szAgrv[0]);
    char *pszSection = "Version";
    char *pszKey = "version";
    char *pszDefault = "root";
    char szRetValue[IIniFile::INI_MAX_SUPPORT_VALUE_SIZE];
    szRetValue[0] = '\0';

    KG_CASE_INFO("输入的lpSection存在，且输入的lpKeyName存在，value长度不为0", "配置文件或命令行有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szAgrv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetString(
        pszSection, 
        pszKey, 
        pszDefault, 
        szRetValue, 
        sizeof(szRetValue) / sizeof(szRetValue[0])
    );
    KG_PROCESS_ERROR(nRetCode);
    szRetValue[sizeof(szRetValue) / sizeof(szRetValue[0]) - 1] = '\0';

    nRetCode = strcmp(szRetValue, "mysql");
    KG_PROCESS_ERROR(nRetCode == 0);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetStringTest::TestGetString_09()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szAgrv[] = {
        "KG_GoddessD.exe"
    };
    int nArgc = sizeof(szAgrv) / sizeof(szAgrv[0]);
    char *pszSection = "";
    char *pszKey = "";
    char *pszDefault = "root";
    char szRetValue[IIniFile::INI_MAX_SUPPORT_VALUE_SIZE];
    szRetValue[0] = '\0';

    KG_CASE_INFO("输入的lpSection和lpKeyName为空值", "配置文件或命令行没有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szAgrv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetString(
        pszSection, 
        pszKey, 
        pszDefault, 
        szRetValue, 
        sizeof(szRetValue) / sizeof(szRetValue[0])
    );
    KG_PROCESS_ERROR(!nRetCode);
    szRetValue[sizeof(szRetValue) / sizeof(szRetValue[0]) - 1] = '\0';

    nRetCode = strcmp(szRetValue, pszDefault);
    KG_PROCESS_ERROR(nRetCode == 0);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetStringTest::TestGetString_10()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szAgrv[] = {
        "KG_GoddessD.exe"
    };
    int nArgc = sizeof(szAgrv) / sizeof(szAgrv[0]);
    char *pszSection = "Version";
    char *pszKey = "version";
    char *pszDefault = "root";
    char szRetValue[IIniFile::INI_MAX_SUPPORT_VALUE_SIZE];
    szRetValue[0] = '\0';

    KG_CASE_INFO("输入的lpSection和lpKeyName非为空值", "配置文件或命令行没有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szAgrv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetString(
        pszSection, 
        pszKey, 
        pszDefault, 
        szRetValue, 
        sizeof(szRetValue) / sizeof(szRetValue[0])
    );
    KG_PROCESS_ERROR(!nRetCode);
    szRetValue[sizeof(szRetValue) / sizeof(szRetValue[0]) - 1] = '\0';

    nRetCode = strcmp(szRetValue, pszDefault);
    KG_PROCESS_ERROR(nRetCode == 0);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}