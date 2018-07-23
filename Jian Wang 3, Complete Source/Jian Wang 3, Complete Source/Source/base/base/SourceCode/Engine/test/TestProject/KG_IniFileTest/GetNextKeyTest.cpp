#include "GetNextKeyTest.h"
#include "KGT_IniFileTest.h"

const char *g_cszFileName = "OnlySection.ini";
const char *g_cszSection  = "Server";

void KGT_GetNextKeyTest::setUp()
{

}
void KGT_GetNextKeyTest::tearDown()
{

}

void KGT_GetNextKeyTest::TestGetNextKey_01()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.Aversion=2",
        "--Version.Bname=sword3",
        "--Version.Cdate=2008",
        "--Version.DId=10"
    };    
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszKey = "";
    char szNextKey[IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE];
    szNextKey[0] = '\0';

    KG_CASE_INFO("空值的下一个key", "section存在，且有多个key");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetNextKey("Version", pszKey, szNextKey);
    KG_PROCESS_ERROR(nRetCode);

    nRetCode = strcmp(szNextKey, "Aversion");
    KG_PROCESS_ERROR(nRetCode == 0);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetNextKeyTest::TestGetNextKey_02()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.Aversion=2",
        "--Version.Bname=sword3",
        "--Version.Cdate=2008",
        "--Version.DId=10"
    };    
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszKey = "Aversion";
    char szNextKey[IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE];
    szNextKey[0] = '\0';

    KG_CASE_INFO("第一条记录的下一个key", "section存在，且有多个key");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetNextKey("Version", pszKey, szNextKey);
    KG_PROCESS_ERROR(nRetCode);

    nRetCode = strcmp(szNextKey, "Bname");
    KG_PROCESS_ERROR(nRetCode == 0);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetNextKeyTest::TestGetNextKey_03()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.Aversion=2",
        "--Version.Bname=sword3",
        "--Version.Cdate=2008",
        "--Version.DId=10"
    };    
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszKey = "Bname";
    char szNextKey[IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE];
    szNextKey[0] = '\0';

    KG_CASE_INFO("中间一条记录的下一个key(不是最后一个key)", "section存在，且有多个key");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetNextKey("Version", pszKey, szNextKey);
    KG_PROCESS_ERROR(nRetCode);

    nRetCode = strcmp(szNextKey, "Cdate");
    KG_PROCESS_ERROR(nRetCode == 0);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetNextKeyTest::TestGetNextKey_04()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.Aversion=2",
        "--Version.Bname=sword3",
        "--Version.Cdate=2008",
        "--Version.DId=10"
    };    
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszKey = "Cdate";
    char szNextKey[IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE];
    szNextKey[0] = '\0';

    KG_CASE_INFO("倒数第二条记录的下一个key", "section存在，且有多个key");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetNextKey("Version", pszKey, szNextKey);
    KG_PROCESS_ERROR(nRetCode);

    nRetCode = strcmp(szNextKey, "DId");
    KG_PROCESS_ERROR(nRetCode == 0);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetNextKeyTest::TestGetNextKey_05()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.Aversion=2",
        "--Version.Bname=sword3",
        "--Version.Cdate=2008",
        "--Version.DId=10"
    };    
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszKey = "DId";
    char szNextKey[IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE];
    szNextKey[0] = '\0';

    KG_CASE_INFO("最后一条记录的下一个key", "section存在，且有多个key");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetNextKey("Version", pszKey, szNextKey);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(szNextKey[0] == '\0');

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetNextKeyTest::TestGetNextKey_06()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.Aversion=2",
        "--Version.Bname=sword3",
        "--Version.Cdate=2008",
        "--Version.DId=10"
    };    
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszKey = "EAge";
    char szNextKey[IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE];
    szNextKey[0] = '\0';

    KG_CASE_INFO("不存在的记录的下一个key", "section存在，且有多个key");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetNextKey("Version", pszKey, szNextKey);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(szNextKey[0] == '\0');

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetNextKeyTest::TestGetNextKey_07()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.Aversion=2"
    };    
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszKey = "";
    char szNextKey[IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE];
    szNextKey[0] = '\0';

    KG_CASE_INFO("空值下一个key", "section存在，但只有一个key");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetNextKey("Version", pszKey, szNextKey);
    KG_PROCESS_ERROR(nRetCode);

    nRetCode = strcmp(szNextKey, "Aversion");
    KG_PROCESS_ERROR(nRetCode == 0);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetNextKeyTest::TestGetNextKey_08()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.Aversion=2"
    };    
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszKey = "Aversion";
    char szNextKey[IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE];
    szNextKey[0] = '\0';

    KG_CASE_INFO("存在记录下一个key", "section存在，但只有一个key");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetNextKey("Version", pszKey, szNextKey);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(szNextKey[0] == '\0');

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetNextKeyTest::TestGetNextKey_09()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.Aversion=2"
    };    
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszKey = "Bname";
    char szNextKey[IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE];
    szNextKey[0] = '\0';

    KG_CASE_INFO("不存在记录下一个key", "section存在，但只有一个key");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetNextKey("Version", pszKey, szNextKey);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(szNextKey[0] == '\0');

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetNextKeyTest::TestGetNextKey_10()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.Aversion=2"
    };    
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszKey = "";
    char szNextKey[IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE];
    szNextKey[0] = '\0';

    KG_CASE_INFO("空值的下一个key", "section存在，但没有key");

    piIniFile = g_LoadStartArgument(nArgc, szArgv, g_cszFileName);
    KG_PROCESS_ERROR(piIniFile);

    //OnlySection.ini文件中只有一个section[Server]，没有key
    nRetCode = piIniFile->GetNextKey(g_cszSection, pszKey, szNextKey);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(szNextKey[0] == '\0');

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetNextKeyTest::TestGetNextKey_11()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.Aversion=2"
    };    
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszKey = "Name";
    char szNextKey[IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE];
    szNextKey[0] = '\0';
    
    KG_CASE_INFO("非空值的下一个key", "section存在，但没有key");

    piIniFile = g_LoadStartArgument(nArgc, szArgv, g_cszFileName);
    KG_PROCESS_ERROR(piIniFile);

    //OnlySection.ini文件中只有一个section[Server]，没有key
    nRetCode = piIniFile->GetNextKey(g_cszSection, pszKey, szNextKey);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(szNextKey[0] == '\0');

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetNextKeyTest::TestGetNextKey_12()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe"
    };    
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszKey = "";
    char szNextKey[IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE];
    szNextKey[0] = '\0';

    KG_CASE_INFO("空值的下一个key", "section不存在");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetNextKey("Version", pszKey, szNextKey);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(szNextKey[0] == '\0');

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetNextKeyTest::TestGetNextKey_13()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe"
    };    
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszKey = "version";
    char szNextKey[IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE];
    szNextKey[0] = '\0';

    KG_CASE_INFO("非空值的下一个key", "section不存在");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetNextKey("Version", pszKey, szNextKey);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(szNextKey[0] == '\0');

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}