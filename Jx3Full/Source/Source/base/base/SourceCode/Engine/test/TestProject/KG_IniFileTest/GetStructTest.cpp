#include "GetStructTest.h"
#include "KGT_IniFileTest.h"

const char *g_cpszFileName = "Struct.ini";
const char *g_cpszSection  = "Person";
const char *g_cpszKeyName  = "man";

void KGT_GetStructTest::setUp()
{
    tm dBirthday;
    dBirthday.tm_year = 1984;
    dBirthday.tm_mon = 5;
    dBirthday.tm_mday = 9;

    ZeroMemory(&m_TestStruct, sizeof(m_TestStruct));
    m_TestStruct.nAge = 20;
    m_TestStruct.bMan = true;
    m_TestStruct.lMoney = 100000;
    m_TestStruct.fScore = 90.5;
    m_TestStruct.dBirthday = dBirthday;
    memcpy(m_TestStruct.szName, "xiaofeng", sizeof(m_TestStruct.szName));
    m_TestStruct.man.nAge = 30;
    memcpy(m_TestStruct.man.szName, "xiaofeng", sizeof(m_TestStruct.man.szName));
}
void KGT_GetStructTest::tearDown()
{

}

int _WriteStruct(
     const char*	lpSection,		// pointer to section name
     const char*	lpKeyName,		// pointer to key name
     void*	lpStruct,		        // pointer to buffer that contains data to add
     unsigned int 	dwSize			// size, in bytes, of the buffer
 )
{
    int nResult = false;
    int nRetCode = false;

    KG_PROCESS_ERROR(lpSection);
    KG_PROCESS_ERROR(lpKeyName);
    KG_PROCESS_ERROR(dwSize < 2048);

    IIniFile *piIniFile = NULL;

    piIniFile = g_OpenIniFile(g_cpszFileName);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->WriteStruct(lpSection, lpKeyName, lpStruct, dwSize);
    KG_PROCESS_ERROR(nRetCode);

    nRetCode = piIniFile->IsSectionExist(lpSection);
    KG_PROCESS_ERROR(nRetCode);

    nRetCode = piIniFile->Save(g_cpszFileName);
    KG_PROCESS_ERROR(nRetCode);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    return nResult;
}

void KGT_GetStructTest::TestGetStruct_01()
{
    int nResult = false;
    int nRetCode = false;

    TEST_STRUCT RetStruct;
    ZeroMemory(&RetStruct, sizeof(TEST_STRUCT));
    RetStruct.nAge = 10000;
    RetStruct.bMan = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "";
    char *pszKeyName = "man";
    unsigned uSize = sizeof(TEST_STRUCT);

    KG_CASE_INFO("输入的lpSection为空，其他参数不为空", "配置文件或命令行有记录");

    nRetCode = _WriteStruct(g_cpszSection, g_cpszKeyName, (TEST_STRUCT *)&m_TestStruct, sizeof(TEST_STRUCT));
    KG_PROCESS_ERROR(nRetCode);

    piIniFile = g_LoadStartArgument(nArgc, szArgv, g_cpszFileName);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetSectionCount();
    KG_PROCESS_ERROR(nRetCode == 2);

    nRetCode = piIniFile->GetStruct(pszSection, pszKeyName, (TEST_STRUCT *)&RetStruct, uSize);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR((RetStruct.nAge == 10000) && (RetStruct.bMan == false));

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetStructTest::TestGetStruct_02()
{
    int nResult = false;
    int nRetCode = false;

    TEST_STRUCT RetStruct;
    ZeroMemory(&RetStruct, sizeof(TEST_STRUCT));
    RetStruct.nAge = 10000;
    RetStruct.bMan = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "Person";
    char *pszKeyName = "";
    unsigned uSize = sizeof(TEST_STRUCT);

    KG_CASE_INFO("输入的lpKeyName为空，其他参数不为空", "配置文件或命令行有记录");

    nRetCode = _WriteStruct(g_cpszSection, g_cpszKeyName, (TEST_STRUCT *)&m_TestStruct, sizeof(TEST_STRUCT));
    KG_PROCESS_ERROR(nRetCode);

    piIniFile = g_LoadStartArgument(nArgc, szArgv, g_cpszFileName);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetSectionCount();
    KG_PROCESS_ERROR(nRetCode == 2);

    nRetCode = piIniFile->GetStruct(pszSection, pszKeyName, (TEST_STRUCT *)&RetStruct, uSize);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR((RetStruct.nAge == 10000) && (RetStruct.bMan == false));

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetStructTest::TestGetStruct_03()
{
    int nResult = false;
    int nRetCode = false;

    TEST_STRUCT RetStruct;
    ZeroMemory(&RetStruct, sizeof(TEST_STRUCT));
    RetStruct.nAge = 10000;
    RetStruct.bMan = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "";
    char *pszKeyName = "";
    unsigned uSize = sizeof(TEST_STRUCT);

    KG_CASE_INFO("输入的lpSection和lpKeyName为空，其他参数不为空", "配置文件或命令行有记录");

    nRetCode = _WriteStruct(g_cpszSection, g_cpszKeyName, (TEST_STRUCT *)&m_TestStruct, sizeof(TEST_STRUCT));
    KG_PROCESS_ERROR(nRetCode);

    piIniFile = g_LoadStartArgument(nArgc, szArgv, g_cpszFileName);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetSectionCount();
    KG_PROCESS_ERROR(nRetCode == 2);

    nRetCode = piIniFile->GetStruct(pszSection, pszKeyName, (TEST_STRUCT *)&RetStruct, uSize);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR((RetStruct.nAge == 10000) && (RetStruct.bMan == false));

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetStructTest::TestGetStruct_04()
{
    int nResult = false;
    int nRetCode = false;

    TEST_STRUCT RetStruct;
    ZeroMemory(&RetStruct, sizeof(TEST_STRUCT));
    RetStruct.nAge = 10000;
    RetStruct.bMan = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "Person";
    char *pszKeyName = "woman";
    unsigned uSize = sizeof(TEST_STRUCT);

    KG_CASE_INFO("输入的lpSection存在，但输入的lpKeyName不存在", "配置文件或命令行有记录");

    nRetCode = _WriteStruct(g_cpszSection, g_cpszKeyName, (TEST_STRUCT *)&m_TestStruct, sizeof(TEST_STRUCT));
    KG_PROCESS_ERROR(nRetCode);

    piIniFile = g_LoadStartArgument(nArgc, szArgv, g_cpszFileName);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetSectionCount();
    KG_PROCESS_ERROR(nRetCode == 2);

    nRetCode = piIniFile->GetStruct(pszSection, pszKeyName, (TEST_STRUCT *)&RetStruct, uSize);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR((RetStruct.nAge == 10000) && (RetStruct.bMan == false));

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetStructTest::TestGetStruct_05()
{
    int nResult = false;
    int nRetCode = false;

    TEST_STRUCT RetStruct;
    ZeroMemory(&RetStruct, sizeof(TEST_STRUCT));
    RetStruct.nAge = 10000;
    RetStruct.bMan = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "Server";
    char *pszKeyName = "man";
    unsigned uSize = sizeof(TEST_STRUCT);

    KG_CASE_INFO("输入的lpSection不存在", "配置文件或命令行有记录");

    nRetCode = _WriteStruct(g_cpszSection, g_cpszKeyName, (TEST_STRUCT *)&m_TestStruct, sizeof(TEST_STRUCT));
    KG_PROCESS_ERROR(nRetCode);

    piIniFile = g_LoadStartArgument(nArgc, szArgv, g_cpszFileName);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetSectionCount();
    KG_PROCESS_ERROR(nRetCode == 2);

    nRetCode = piIniFile->GetStruct(pszSection, pszKeyName, (TEST_STRUCT *)&RetStruct, uSize);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR((RetStruct.nAge == 10000) && (RetStruct.bMan == false));

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetStructTest::TestGetStruct_06()
{
    int nResult = false;
    int nRetCode = false;

    TEST_STRUCT RetStruct;
    ZeroMemory(&RetStruct, sizeof(TEST_STRUCT));
    RetStruct.nAge = 10000;
    RetStruct.bMan = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    const char *pszSection = g_cpszSection;
    const char *pszKeyName = g_cpszKeyName;
    unsigned uSize = sizeof(TEST_STRUCT);

    KG_CASE_INFO("struct的长度*2=value的长度，值正常", "配置文件或命令行有记录");

    nRetCode = _WriteStruct(g_cpszSection, g_cpszKeyName, (TEST_STRUCT *)&m_TestStruct, sizeof(TEST_STRUCT));
    KG_PROCESS_ERROR(nRetCode);

    piIniFile = g_LoadStartArgument(nArgc, szArgv, g_cpszFileName);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetSectionCount();
    KG_PROCESS_ERROR(nRetCode == 2);

    nRetCode = piIniFile->GetStruct(pszSection, pszKeyName, (TEST_STRUCT *)&RetStruct, uSize);
    KG_PROCESS_ERROR(nRetCode);

    nRetCode = memcmp((TEST_STRUCT *)&RetStruct, (TEST_STRUCT *)&m_TestStruct, sizeof(TEST_STRUCT));
    KG_PROCESS_ERROR(nRetCode == 0);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetStructTest::TestGetStruct_07()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=6m"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    const char *pszSection = "Version";
    const char *pszKeyName = "version";
    unsigned uSize = sizeof(char);
    char cRetValue = '0';

    KG_CASE_INFO("struct的长度*2=value的长度,但value的值含有0-f以外的字符串", "配置文件或命令行有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetSectionCount();
    KG_PROCESS_ERROR(nRetCode == 1);

    nRetCode = piIniFile->GetStruct(pszSection, pszKeyName, (char *)&cRetValue, uSize);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(cRetValue == '0');

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetStructTest::TestGetStruct_08()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=6143"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    const char *pszSection = "Version";
    const char *pszKeyName = "version";
    unsigned uSize = sizeof(char);
    char cRetValue = '0';

    KG_CASE_INFO("struct的长度*2!=value的长度", "配置文件或命令行有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetSectionCount();
    KG_PROCESS_ERROR(nRetCode == 1);

    nRetCode = piIniFile->GetStruct(pszSection, pszKeyName, (char *)&cRetValue, uSize);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(cRetValue == '0');

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetStructTest::TestGetStruct_09()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version="
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    const char *pszSection = "Version";
    const char *pszKeyName = "version";
    unsigned uSize = sizeof(char);
    char cRetValue = '0';

    KG_CASE_INFO("struct的长度*2=value的长度,但value为空值", "配置文件或命令行有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetSectionCount();
    KG_PROCESS_ERROR(nRetCode == 1);

    nRetCode = piIniFile->GetStruct(pszSection, pszKeyName, (char *)&cRetValue, uSize);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(cRetValue == '0');

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetStructTest::TestGetStruct_10()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    const char *pszSection = "";
    const char *pszKeyName = "";
    unsigned uSize = sizeof(char);
    char cRetValue = '0';

    KG_CASE_INFO("输入的lpSection和lpKeyName为空值", "配置文件或命令行没有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetSectionCount();
    KG_PROCESS_ERROR(nRetCode == 0);

    nRetCode = piIniFile->GetStruct(pszSection, pszKeyName, (char *)&cRetValue, uSize);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(cRetValue == '0');

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetStructTest::TestGetStruct_11()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    const char *pszSection = "Version";
    const char *pszKeyName = "version";
    unsigned uSize = sizeof(char);
    char cRetValue = '0';

    KG_CASE_INFO("输入的lpSection和lpKeyName为非空值", "配置文件或命令行没有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetSectionCount();
    KG_PROCESS_ERROR(nRetCode == 0);

    nRetCode = piIniFile->GetStruct(pszSection, pszKeyName, (char *)&cRetValue, uSize);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(cRetValue == '0');

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}