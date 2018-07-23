#include "g_OpenIniFileFromArgumentsTest.h"
#include "KGT_IniFileTest.h"
#include <time.h>

const char *g_pcszErrorInputFileName = "ErrorInput.txt";
const char *g_pcszErrorMessage[] = {
    "section不存在"
    "section长度为0", 
    "key长度为0",
    "--号前后有空格",
    "section前后有空格",
    "key前后有空格",
    "=号前后有空格",
    "只有section部分，没有key",
    "=号前面含有2个点",
    "只有一个\"-\"号",
    "有3个\"-\"号",
    "两个\"-\"之间含有空格",
    "没有=号",
    "有2个=号"
};

void KGT_g_OpenIniFileFromArgumentsTest::setUp()
{

}
void KGT_g_OpenIniFileFromArgumentsTest::tearDown()
{

}

int KGT_g_OpenIniFileFromArgumentsTest::_LoadFile()
{
    int nResult = false;
    int nRetCode = false;
    long lFileLength = -1;

    FILE *pFile = NULL;
    ZeroMemory(m_szErrorInput, sizeof(m_szErrorInput) / sizeof(m_szErrorInput[0]));

    pFile = fopen(g_pcszErrorInputFileName, "r");
    KG_PROCESS_ERROR(pFile);

    nRetCode = fseek(pFile, 0, SEEK_END);
    KG_PROCESS_ERROR(nRetCode == 0);

    lFileLength = ftell(pFile);
    KG_PROCESS_ERROR(lFileLength != -1);
    ASSERT(lFileLength <= MAX_ERROR_INPUT_FILE);

    nRetCode = fseek(pFile, 0, SEEK_SET);
    KG_PROCESS_ERROR(nRetCode == 0);

    nRetCode = (int)fread(m_szErrorInput, sizeof(char), lFileLength, pFile);
    KG_PROCESS_ERROR(nRetCode <= lFileLength);

    m_szErrorInput[nRetCode] = '\0';

    nResult = true;
Exit0:
    if (pFile)
    {
        fclose(pFile);
        pFile = NULL;
    }
    return nResult;
}

int KGT_g_OpenIniFileFromArgumentsTest::_DataGenerator(int nSize, char szRetString[])
{
    int nResult = false;
    int nRetCode = false;
    int i = 0;
    int nData = 0;

    KG_PROCESS_ERROR(nSize > 0);
    KG_PROCESS_ERROR(szRetString);

    srand(time(NULL));

    for (i = 0; i < nSize; i++)
    {
        nData = rand() % (0x7e - 0x41) + 0x41; //保证nData为可显示的字符,且不为. =        
        szRetString[i] = nData;
    }
    szRetString[nSize - 1] = '\0';

    nResult = true;
Exit0:
    return nResult;
}

void KGT_g_OpenIniFileFromArgumentsTest::Test_g_OpenFileFromArguments_01()
{
    int nResult = false;
    int nRetCode = false;

    char *pszArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2",
        "--Version.version=8"
    };
    int nArgc = sizeof(pszArgv) / sizeof(pszArgv[0]);
    IIniFile *piIniFile = NULL;

    KG_CASE_INFO("相同的section相同的key", "");

    piIniFile = g_OpenIniFileFromArguments(nArgc, pszArgv);
    KG_PROCESS_ERROR(!piIniFile);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_g_OpenIniFileFromArgumentsTest::Test_g_OpenFileFromArguments_02()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *pszArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2",
        "--Version.name=sword3"
    };
    int nArgc = sizeof(pszArgv) / sizeof(pszArgv[0]);
    char szRetVersion[IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE];
    szRetVersion[0] = '\0';
    char szRetName[IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE];
    szRetName[0] = '\0';


    KG_CASE_INFO("相同的section不同的key", "");

    piIniFile = g_OpenIniFileFromArguments(nArgc, pszArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->IsSectionExist("Version");
    KG_PROCESS_ERROR(nRetCode);

    nRetCode = piIniFile->GetString("Version", "version", "", szRetVersion, sizeof(szRetVersion) / sizeof(szRetVersion[0]));
    KG_PROCESS_ERROR(nRetCode);
    szRetVersion[sizeof(szRetVersion) / sizeof(szRetVersion[0]) -1] = '\0';
    nRetCode = strncmp(szRetVersion, "2", sizeof(szRetVersion) / sizeof(szRetVersion[0]));
    KG_PROCESS_ERROR(nRetCode == 0);

    nRetCode = piIniFile->GetString("Version", "name", "", szRetName, sizeof(szRetName) / sizeof(szRetName[0]));
    KG_PROCESS_ERROR(nRetCode);
    szRetName[sizeof(szRetName) / sizeof(szRetName[0]) -1] = '\0';
    nRetCode = strncmp(szRetName, "sword3", sizeof(szRetName) / sizeof(szRetName[0]));
    KG_PROCESS_ERROR(nRetCode == 0);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_g_OpenIniFileFromArgumentsTest::Test_g_OpenFileFromArguments_03()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *pszArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2",
        "--Database.version=8"
    };
    int nArgc = sizeof(pszArgv) / sizeof(pszArgv[0]);
    char szRetVersion[IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE];
    szRetVersion[0] = '\0';


    KG_CASE_INFO("不同的section相同的key", "");

    piIniFile = g_OpenIniFileFromArguments(nArgc, pszArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->IsSectionExist("Version");
    KG_PROCESS_ERROR(nRetCode);

    nRetCode = piIniFile->IsSectionExist("Database");
    KG_PROCESS_ERROR(nRetCode);

    nRetCode = piIniFile->GetString("Version", "version", "", szRetVersion, sizeof(szRetVersion) / sizeof(szRetVersion[0]));
    KG_PROCESS_ERROR(nRetCode);
    szRetVersion[sizeof(szRetVersion) / sizeof(szRetVersion[0]) -1] = '\0';
    nRetCode = strncmp(szRetVersion, "2", sizeof(szRetVersion) / sizeof(szRetVersion[0]));
    KG_PROCESS_ERROR(nRetCode == 0);

    nRetCode = piIniFile->GetString("Database", "version", "", szRetVersion, sizeof(szRetVersion) / sizeof(szRetVersion[0]));
    KG_PROCESS_ERROR(nRetCode);
    szRetVersion[sizeof(szRetVersion) / sizeof(szRetVersion[0]) -1] = '\0';
    nRetCode = strncmp(szRetVersion, "8", sizeof(szRetVersion) / sizeof(szRetVersion[0]));
    KG_PROCESS_ERROR(nRetCode == 0);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_g_OpenIniFileFromArgumentsTest::Test_g_OpenFileFromArguments_04()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *pszArgv[] = {
        "KG_GoddessD.exe",
        "--Version.version=2",
        "--Database.name=mysql"
    };
    int nArgc = sizeof(pszArgv) / sizeof(pszArgv[0]);
    char szRetVersion[IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE];
    szRetVersion[0] = '\0';
    char szRetName[IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE];
    szRetName[0] = '\0';

    KG_CASE_INFO("不同的section不同的key", "");

    piIniFile = g_OpenIniFileFromArguments(nArgc, pszArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->IsSectionExist("Version");
    KG_PROCESS_ERROR(nRetCode);

    nRetCode = piIniFile->IsSectionExist("Database");
    KG_PROCESS_ERROR(nRetCode);

    nRetCode = piIniFile->GetString("Version", "version", "", szRetVersion, sizeof(szRetVersion) / sizeof(szRetVersion[0]));
    KG_PROCESS_ERROR(nRetCode);
    szRetVersion[sizeof(szRetVersion) / sizeof(szRetVersion[0]) -1] = '\0';
    nRetCode = strncmp(szRetVersion, "2", sizeof(szRetVersion) / sizeof(szRetVersion[0]));
    KG_PROCESS_ERROR(nRetCode == 0);

    nRetCode = piIniFile->GetString("Database", "name", "", szRetName, sizeof(szRetName) / sizeof(szRetName[0]));
    KG_PROCESS_ERROR(nRetCode);
    szRetName[sizeof(szRetName) / sizeof(szRetName[0]) -1] = '\0';
    nRetCode = strncmp(szRetName, "mysql", sizeof(szRetName) / sizeof(szRetName[0]));
    KG_PROCESS_ERROR(nRetCode == 0);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_g_OpenIniFileFromArgumentsTest::Test_g_OpenFileFromArguments_05()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    int nRetValue = 0;
    int nArgc = 0;
    char *pszArgv[2] = {0};
    char szArgv[2][IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE * 2] = {0};
    nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char szSection[IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE];
    szSection[0] = '\0';
    pszArgv[0] = szArgv[0];
    pszArgv[1] = szArgv[1];

    strncpy(szArgv[0], "KG_GoddessD.exe", sizeof(szArgv[0]));
    szArgv[0][IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE] = '\0';

    KG_CASE_INFO("section的长度为最大值", "");

    nRetCode = _DataGenerator(sizeof(szSection), szSection);
    KG_PROCESS_ERROR(nRetCode);

    nRetCode = _snprintf(
       szArgv[1],
       sizeof(szArgv[1]) / sizeof(szArgv[1][0]) - 1,
       "--%s.version=2",
       szSection
    );
    KG_PROCESS_ERROR(nRetCode > 0);

    piIniFile = g_OpenIniFileFromArguments(nArgc, pszArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger(szSection, "version", 0, &nRetValue);
    KG_PROCESS_ERROR(nRetCode);
    
    KG_PROCESS_ERROR(nRetValue == 2);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_g_OpenIniFileFromArgumentsTest::Test_g_OpenFileFromArguments_06()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    int nRetValue = 0;
    int nArgc = 0;
    char *pszArgv[2] = {0};
    char szArgv[2][IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE * 2] = {0};
    nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char szSection[IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE + 10];
    szSection[0] = '\0';
    pszArgv[0] = szArgv[0];
    pszArgv[1] = szArgv[1];

    strncpy(szArgv[0], "KG_GoddessD.exe", sizeof(szArgv[0]));
    szArgv[0][IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE] = '\0';

    KG_CASE_INFO("section的长度大于最大值", "");

    nRetCode = _DataGenerator(sizeof(szSection), szSection);
    KG_PROCESS_ERROR(nRetCode);

    nRetCode = _snprintf(
        szArgv[1],
        sizeof(szArgv[1]) / sizeof(szArgv[1][0]) - 1,
        "--%s.version=2",
        szSection
    );
    KG_PROCESS_ERROR(nRetCode > 0);

    piIniFile = g_OpenIniFileFromArguments(nArgc, pszArgv);
    KG_PROCESS_ERROR(!piIniFile);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_g_OpenIniFileFromArgumentsTest::Test_g_OpenFileFromArguments_07()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    int nRetValue = 0;
    int nArgc = 0;
    char *pszArgv[2] = {0};
    char szArgv[2][IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE * 2] = {0};
    nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char szKey[IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE];
    szKey[0] = '\0';
    pszArgv[0] = szArgv[0];
    pszArgv[1] = szArgv[1];

    strncpy(szArgv[0], "KG_GoddessD.exe", sizeof(szArgv[0]));
    szArgv[0][IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE] = '\0';

    KG_CASE_INFO("key的长度为最大值", "");

    nRetCode = _DataGenerator(sizeof(szKey), szKey);
    KG_PROCESS_ERROR(nRetCode);

    nRetCode = _snprintf(
        szArgv[1],
        sizeof(szArgv[1]) / sizeof(szArgv[1][0]) - 1,
        "--Version.%s=2",
        szKey
    );
    KG_PROCESS_ERROR(nRetCode > 0);

    piIniFile = g_OpenIniFileFromArguments(nArgc, pszArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetInteger("Version", szKey, 0, &nRetValue);
    KG_PROCESS_ERROR(nRetCode);

    KG_PROCESS_ERROR(nRetValue == 2);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_g_OpenIniFileFromArgumentsTest::Test_g_OpenFileFromArguments_08()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    int nRetValue = 0;
    int nArgc = 0;
    char *pszArgv[2] = {0};
    char szArgv[2][IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE * 2] = {0};
    nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char szKey[IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE + 10];
    szKey[0] = '\0';
    pszArgv[0] = szArgv[0];
    pszArgv[1] = szArgv[1];

    strncpy(szArgv[0], "KG_GoddessD.exe", sizeof(szArgv[0]));
    szArgv[0][IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE] = '\0';

    KG_CASE_INFO("key的长度大于最大值", "");

    nRetCode = _DataGenerator(sizeof(szKey), szKey);
    KG_PROCESS_ERROR(nRetCode);

    nRetCode = _snprintf(
        szArgv[1],
        sizeof(szArgv[1]) / sizeof(szArgv[1][0]) - 1,
        "--Version.%s=2",
        szKey
    );
    KG_PROCESS_ERROR(nRetCode > 0);

    piIniFile = g_OpenIniFileFromArguments(nArgc, pszArgv);
    KG_PROCESS_ERROR(!piIniFile);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_g_OpenIniFileFromArgumentsTest::Test_g_OpenFileFromArguments_09()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    char *szArgv[] = {
        "KG_GoddessD.exe",
        "--Database.password="
    };
    int nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char szRetValue[12];
    szRetValue[0] = '\0';

    KG_CASE_INFO("value的长度为0", "");

    piIniFile = g_OpenIniFileFromArguments(nArgc, szArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetSectionCount();
    KG_PROCESS_ERROR(nRetCode == 1);

    nRetCode = piIniFile->GetString("Database", "password", "root", szRetValue, sizeof(szRetValue) / sizeof(szRetValue[0]));
    KG_PROCESS_ERROR(nRetCode);

    KG_PROCESS_ERROR(szRetValue[0] == '\0');

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_g_OpenIniFileFromArgumentsTest::Test_g_OpenFileFromArguments_10()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    int nArgc = 0;
    char *pszArgv[2] = {0};
    char szArgv[2][IIniFile::INI_MAX_SUPPORT_VALUE_SIZE + 100] = {0};
    nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char szValue[IIniFile::INI_MAX_SUPPORT_VALUE_SIZE];
    szValue[0] = '\0';
    char szRetValue[IIniFile::INI_MAX_SUPPORT_VALUE_SIZE];
    szRetValue[0] = '\0';

    pszArgv[0] = szArgv[0];
    pszArgv[1] = szArgv[1];

    strncpy(szArgv[0], "KG_GoddessD.exe", sizeof(szArgv[0]));
    szArgv[0][IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE] = '\0';

    KG_CASE_INFO("value的长度为最大值", "");

    nRetCode = _DataGenerator(sizeof(szValue), szValue);
    KG_PROCESS_ERROR(nRetCode);

    nRetCode = _snprintf(
        szArgv[1],
        sizeof(szArgv[1]) / sizeof(szArgv[1][0]) - 1,
        "--Database.name=%s",
        szValue
    );
    KG_PROCESS_ERROR(nRetCode > 0);

    piIniFile = g_OpenIniFileFromArguments(nArgc, pszArgv);
    KG_PROCESS_ERROR(piIniFile);

    nRetCode = piIniFile->GetString("Database", "name", "", szRetValue, sizeof(szRetValue) / sizeof(szRetValue[0]));
    KG_PROCESS_ERROR(nRetCode);

    nRetCode = strcmp(szValue, szRetValue);
    KG_PROCESS_ERROR(nRetCode == 0);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_g_OpenIniFileFromArgumentsTest::Test_g_OpenFileFromArguments_11()
{
    int nResult = false;
    int nRetCode = false;

    IIniFile *piIniFile = NULL;
    int nArgc = 0;
    char *pszArgv[2] = {0};
    char szArgv[2][IIniFile::INI_MAX_SUPPORT_VALUE_SIZE + 100] = {0};
    nArgc = sizeof(szArgv) / sizeof(szArgv[0]);
    char szValue[IIniFile::INI_MAX_SUPPORT_VALUE_SIZE + 10];
    szValue[0] = '\0';

    pszArgv[0] = szArgv[0];
    pszArgv[1] = szArgv[1];

    strncpy(szArgv[0], "KG_GoddessD.exe", sizeof(szArgv[0]));
    szArgv[0][IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE] = '\0';

    KG_CASE_INFO("value的长度大于最大值", "");

    nRetCode = _DataGenerator(sizeof(szValue), szValue);
    KG_PROCESS_ERROR(nRetCode);

    nRetCode = _snprintf(
        szArgv[1],
        sizeof(szArgv[1]) / sizeof(szArgv[1][0]) - 1,
        "--Database.name=%s",
        szValue
    );
    KG_PROCESS_ERROR(nRetCode > 0);

    piIniFile = g_OpenIniFileFromArguments(nArgc, pszArgv);
    KG_PROCESS_ERROR(!piIniFile);

    nResult = true;
Exit0:
    KG_COM_RELEASE(piIniFile);
    CPPUNIT_ASSERT(nResult);
}

void KGT_g_OpenIniFileFromArgumentsTest::Test_ErrorInput()
{
    int nResult = true;
    int nRetCode = false;

    int i = 0;
    int j = 0;
    int nErrorIndex = 0;
    int nPrevSpace = 0;
    int nArgc = 0;
    char szArgv[10][IIniFile::INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE];
    IIniFile *piIniFile = NULL;
    char *pszArgv[10] = {0};

    nRetCode = _LoadFile();
    KG_PROCESS_ERROR(nRetCode);

    ASSERT(m_szErrorInput[0]);

    i = 0;
    while (m_szErrorInput[i] != '\0')
    {
        nArgc = 0;
        ZeroMemory(szArgv, sizeof(szArgv));
        nPrevSpace = i;
        while (m_szErrorInput[i] != '\n' && m_szErrorInput[i] != '\0')
        {
            if (m_szErrorInput[i] == ' ')
            {
                strncpy(szArgv[nArgc], m_szErrorInput + nPrevSpace, i - nPrevSpace);

                szArgv[nArgc][i - nPrevSpace] = '\0';
                pszArgv[nArgc] = szArgv[nArgc];
                nArgc++;
                nPrevSpace = i;
            }
            i++;
        }
        //最后一个空格到'\n'或'\0'
        strncpy(szArgv[nArgc], m_szErrorInput + nPrevSpace, i - nPrevSpace);
        szArgv[nArgc][i - nPrevSpace] = '\0';
        pszArgv[nArgc] = szArgv[nArgc];
        nArgc++;
        i++;
        nPrevSpace = i;

        if (nArgc == 0)
            continue;
        
        piIniFile = g_OpenIniFileFromArguments(nArgc, pszArgv);
        if (!piIniFile)
        {  
            ASSERT(nErrorIndex < sizeof(g_pcszErrorMessage) / sizeof(g_pcszErrorMessage[0]));
            printf("%s\n", g_pcszErrorMessage[nErrorIndex]);
            nResult = false;
        }
        nRetCode = piIniFile->GetSectionCount();
        if (nRetCode != 0)
        {
            ASSERT(nErrorIndex < sizeof(g_pcszErrorMessage) / sizeof(g_pcszErrorMessage[0]));
            printf("%s\n", g_pcszErrorMessage[nErrorIndex]);    
            nResult = false;
        }
        KG_COM_RELEASE(piIniFile);
        nErrorIndex++;
    }

/*    printf("%d\n", nErrorIndex);*/
Exit0:
    CPPUNIT_ASSERT(nResult);
}