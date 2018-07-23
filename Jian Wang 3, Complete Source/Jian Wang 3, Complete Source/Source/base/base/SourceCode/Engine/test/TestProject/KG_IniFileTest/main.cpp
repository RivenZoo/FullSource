#include "KGT_IniFileTest.h "
#include "cppunit/KG_Cppunit.h"
#include "Engine/File.h"
#include <direct.h>

////////////////////////////////////////////////////////////////////////////////
// @brief :Set runtime environment 
// @param cszAppFullPathName : [in] Application full path name. 
// @return : true if successful, false if failed.
static int _SetRuntimeEnvironment(const char cszAppFullPathName[MAX_PATH])
{
    int nResult  = false;
    int nRetCode = false;
    char szProgramPath[MAX_PATH];

    setlocale(LC_ALL, "");

    ASSERT(cszAppFullPathName);

    // set working path to application path
    g_ExtractFilePath(szProgramPath, const_cast<char *>(cszAppFullPathName));

    if (szProgramPath[0] != '\0')
    {
        nRetCode = _chdir(szProgramPath);
        KG_PROCESS_ERROR(nRetCode == 0);
    }

    // set root path for config file
    g_SetRootPath(NULL);

    //Exit1:
    nResult = true;
Exit0:
    return nResult;
}

int main(int argc, char *argv[])
{
    int nResult = false;
    int nRetCode = false;

    CppUnit::KG_Cppunit TestSuit("KGT_IniFileTest");
    
    nRetCode = _SetRuntimeEnvironment(argv[0]);
    KG_PROCESS_ERROR(nRetCode);
    
    TestSuit.RunTest();

    TestSuit.Output();

    nResult = true;
Exit0:
    _getch();
    return nResult ? 0 : 1;
}