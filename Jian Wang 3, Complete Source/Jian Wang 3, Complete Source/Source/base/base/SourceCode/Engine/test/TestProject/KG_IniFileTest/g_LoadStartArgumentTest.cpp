#include "g_LoadStartArgumentTest.h"
#include "KGT_IniFileTest.h"

void KGT_g_LoadStartArgumentTest::setUp()
{

}
void KGT_g_LoadStartArgumentTest::tearDown()
{

}

void KGT_g_LoadStartArgumentTest::Test_g_LoadStartArgument_01()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);

    KG_CASE_INFO("FileName指示的文件不存在", "命令行没有--section参数");

    piIniFile = g_LoadStartArgument(nArgc, szArgv, "djhjhgh.ini");
    KG_PROCESS_ERROR(!piIniFile);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_g_LoadStartArgumentTest::Test_g_LoadStartArgument_02()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);

    KG_CASE_INFO("FileName指示的文件存在,但是没有数据", "命令行没有--section参数");

    piIniFile = g_LoadStartArgument(nArgc, szArgv, "NoData.ini");
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetSectionCount();
    KG_PROCESS_ERROR(nRetCode == 0);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_g_LoadStartArgumentTest::Test_g_LoadStartArgument_03()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);

    KG_CASE_INFO("FileName指示的文件存在,且有数据", "命令行没有--section参数");

    piIniFile = g_LoadStartArgument(nArgc, szArgv, "HaveData.ini");
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetSectionCount();
    KG_PROCESS_ERROR(nRetCode > 0);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_g_LoadStartArgumentTest::Test_g_LoadStartArgument_04()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);

    KG_CASE_INFO("FileName指示的文件不存在", "命令行有--section参数");

    piIniFile = g_LoadStartArgument(nArgc, szArgv, "djhjhgh.ini");
    KG_PROCESS_ERROR(!piIniFile);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_g_LoadStartArgumentTest::Test_g_LoadStartArgument_05()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    IIniFile *piCmdArgument = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);

    KG_CASE_INFO("FileName指示的文件存在,但是没有数据", "命令行有--section参数");

    piIniFile = g_OpenIniFile("NoData.ini");
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetSectionCount();
    KG_PROCESS_ERROR(nRetCode == 0);

    piCmdArgument = g_LoadStartArgument(nArgc, szArgv, "NoData.ini");
    KG_PROCESS_ERROR(piCmdArgument);

    nRetCode = piCmdArgument->GetSectionCount();
    KG_PROCESS_ERROR(nRetCode == 1);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piCmdArgument);
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_g_LoadStartArgumentTest::Test_g_LoadStartArgument_06()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    IIniFile *piCmdArgument = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Version1.version=100"
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    int nRetValue = 0;

    KG_CASE_INFO("FileName指示的文件存在,且有数据", "命令行有--section参数");

    piIniFile = g_OpenIniFile("HaveData.ini");
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger("Version1", "version", 0, &nRetValue);
    KG_PROCESS_ERROR(nRetCode);
    KG_PROCESS_ERROR(nRetValue != 100);

    piCmdArgument = g_LoadStartArgument(nArgc, szArgv, "HaveData.ini");
    KG_PROCESS_ERROR(piCmdArgument);

    nRetCode = piCmdArgument->GetInteger("Version1", "version", 0, &nRetValue);
    KG_PROCESS_ERROR(nRetCode);
    KG_PROCESS_ERROR(nRetValue == 100);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piCmdArgument);
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}