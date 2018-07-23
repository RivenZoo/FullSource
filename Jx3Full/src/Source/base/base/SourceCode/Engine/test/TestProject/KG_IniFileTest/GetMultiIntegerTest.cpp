#include "GetMultiIntegerTest.h"
#include "KGT_IniFileTest.h"

void KGT_GetMultiIntegerTest::setUp()
{

}
void KGT_GetMultiIntegerTest::teatDown()
{

}

void KGT_GetMultiIntegerTest::TestGetMultiInteger_01()
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
    int nArrayValues[IIniFile::INI_MAX_SUPPORT_MULTI_VALUE_COUNT - 2] = {-1, -2};
    int nCount = sizeof(nArrayValues) / sizeof(nArrayValues[0]);

    KG_CASE_INFO("输入的lpSection为空,其他参数不为空", "配置文件或命令行有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetMultiInteger(pszSection, pszKey, nArrayValues, nCount);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nArrayValues[0] == -1 && nArrayValues[1] == -2);    

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetMultiIntegerTest::TestGetMultiInteger_02()
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
    int nArrayValues[IIniFile::INI_MAX_SUPPORT_MULTI_VALUE_COUNT - 2] = {-1, -2};
    int nCount = sizeof(nArrayValues) / sizeof(nArrayValues[0]);

    KG_CASE_INFO("输入的lpKeyName为空,其他参数不为空", "配置文件或命令行有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetMultiInteger(pszSection, pszKey, nArrayValues, nCount);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nArrayValues[0] == -1 && nArrayValues[1] == -2);    

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetMultiIntegerTest::TestGetMultiInteger_03()
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
    int nArrayValues[IIniFile::INI_MAX_SUPPORT_MULTI_VALUE_COUNT - 2] = {-1, -2};
    int nCount = sizeof(nArrayValues) / sizeof(nArrayValues[0]);

    KG_CASE_INFO("输入的lpSection和lpKeyName为空,其他参数不为空", "配置文件或命令行有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetMultiInteger(pszSection, pszKey, nArrayValues, nCount);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nArrayValues[0] == -1 && nArrayValues[1] == -2);    

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetMultiIntegerTest::TestGetMultiInteger_04()
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
    int nArrayValues[IIniFile::INI_MAX_SUPPORT_MULTI_VALUE_COUNT - 2] = {-1, -2};
    int nCount = sizeof(nArrayValues) / sizeof(nArrayValues[0]);

    KG_CASE_INFO("输入的lpSection存在，但输入的lpKeyName不存在", "配置文件或命令行有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetMultiInteger(pszSection, pszKey, nArrayValues, nCount);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nArrayValues[0] == -1 && nArrayValues[1] == -2);    

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetMultiIntegerTest::TestGetMultiInteger_05()
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
    int nArrayValues[IIniFile::INI_MAX_SUPPORT_MULTI_VALUE_COUNT - 2] = {-1, -2};
    int nCount = sizeof(nArrayValues) / sizeof(nArrayValues[0]);

    KG_CASE_INFO("输入的lpSection不存在", "配置文件或命令行有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetMultiInteger(pszSection, pszKey, nArrayValues, nCount);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nArrayValues[0] == -1 && nArrayValues[1] == -2);    

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetMultiIntegerTest::TestGetMultiInteger_06()
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
    int nArrayValues[IIniFile::INI_MAX_SUPPORT_MULTI_VALUE_COUNT - 2] = {-1, -2};
    int nCount = sizeof(nArrayValues) / sizeof(nArrayValues[0]);

    KG_CASE_INFO("输入的nCount<=0或nCount>INI_MAX_SUPPORT_MULTI_VALUE_COUNT", "配置文件或命令行有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    //nCount = 0
    nCount = 0;
    nRetCode = piIniFile->GetMultiInteger(pszSection, pszKey, nArrayValues, nCount);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nArrayValues[0] == -1 && nArrayValues[1] == -2);

    //nCount > INI_MAX_SUPPORT_MULTI_VALUE_COUNT
    nCount = IIniFile::INI_MAX_SUPPORT_MULTI_VALUE_COUNT + 10;
    nRetCode = piIniFile->GetMultiInteger(pszSection, pszKey, nArrayValues, nCount);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nArrayValues[0] == -1 && nArrayValues[1] == -2);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetMultiIntegerTest::TestGetMultiInteger_07()
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
    int nArrayValues[5] = {-1, -2};
    int nCount = sizeof(nArrayValues) / sizeof(nArrayValues[0]);

    KG_CASE_INFO("输入的lpSection存在，且输入的lpKeyName存在,value的个数小于输入的nCount", "配置文件或命令行有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetMultiInteger(pszSection, pszKey, nArrayValues, nCount);
    KG_PROCESS_ERROR(nRetCode);

    KG_PROCESS_ERROR(nArrayValues[0] == 2 && nArrayValues[1] == 3);    

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetMultiIntegerTest::TestGetMultiInteger_08()
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
    int nArrayValues[2] = {-1, -2};
    int nCount = sizeof(nArrayValues) / sizeof(nArrayValues[0]);

    KG_CASE_INFO("输入的lpSection存在，且输入的lpKeyName存在,value的个数等于输入的nCount", "配置文件或命令行有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetMultiInteger(pszSection, pszKey, nArrayValues, nCount);
    KG_PROCESS_ERROR(nRetCode);

    KG_PROCESS_ERROR(nArrayValues[0] == 2 && nArrayValues[1] == 3);    

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetMultiIntegerTest::TestGetMultiInteger_09()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2,3,4,5,6",
        "--Database.name=mysql"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "Version";
    char *pszKey = "version";
    int nArrayValues[2] = {-1, -2};
    int nCount = sizeof(nArrayValues) / sizeof(nArrayValues[0]);

    KG_CASE_INFO("输入的lpSection存在，且输入的lpKeyName存在,value的个数大于输入的nCount", "配置文件或命令行有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetMultiInteger(pszSection, pszKey, nArrayValues, nCount);
    KG_PROCESS_ERROR(nRetCode);

    KG_PROCESS_ERROR(nArrayValues[0] == 2 && nArrayValues[1] == 3);    

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetMultiIntegerTest::TestGetMultiInteger_10()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version="
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "Version";
    char *pszKey = "version";
    int nArrayValues[2] = {-1, -2};
    int nCount = sizeof(nArrayValues) / sizeof(nArrayValues[0]);

    KG_CASE_INFO("输入的lpSection存在，且输入的lpKeyName存在,value为空值", "配置文件或命令行有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetMultiInteger(pszSection, pszKey, nArrayValues, nCount);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nArrayValues[0] == -1 && nArrayValues[1] == -2);    

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetMultiIntegerTest::TestGetMultiInteger_11()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=a,cd,ef"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char *pszSection = "Version";
    char *pszKey = "version";
    int nArrayValues[2] = {-1, -2};
    int nCount = sizeof(nArrayValues) / sizeof(nArrayValues[0]);

    KG_CASE_INFO("输入的lpSection存在，且输入的lpKeyName存在,value为非数字字符串", "配置文件或命令行有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetMultiInteger(pszSection, pszKey, nArrayValues, nCount);
    KG_PROCESS_ERROR(nRetCode);

    KG_PROCESS_ERROR(nArrayValues[0] == 0 && nArrayValues[1] == 0);    

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetMultiIntegerTest::TestGetMultiInteger_12()
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
    int nArrayValues[2] = {-1, -2};
    int nCount = sizeof(nArrayValues) / sizeof(nArrayValues[0]);

    KG_CASE_INFO("输入的lpSection和lpKeyName为空值", "配置文件或命令行没有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetMultiInteger(pszSection, pszKey, nArrayValues, nCount);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nArrayValues[0] == -1 && nArrayValues[1] == -2);    

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_GetMultiIntegerTest::TestGetMultiInteger_13()
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
    int nArrayValues[2] = {-1, -2};
    int nCount = sizeof(nArrayValues) / sizeof(nArrayValues[0]);

    KG_CASE_INFO("输入的lpSection和lpKeyName为非空值", "配置文件或命令行没有记录");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetMultiInteger(pszSection, pszKey, nArrayValues, nCount);
    KG_PROCESS_ERROR(!nRetCode);

    KG_PROCESS_ERROR(nArrayValues[0] == -1 && nArrayValues[1] == -2);    

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}