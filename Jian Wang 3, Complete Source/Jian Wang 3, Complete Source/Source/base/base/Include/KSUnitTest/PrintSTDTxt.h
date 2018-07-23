//////////////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   PrintSTDTxt.h
//  Version     :   1.0
//  Creater     :   Cheng Zhaohui
//  Date        :   2005-10-26
//  Comment     :   将cppunit测试结果输出到屏幕或文本文件
//
//////////////////////////////////////////////////////////////////////////////////////

#ifndef _KS_UNIT_STD_TXT_H_
#define _KS_UNIT_STD_TXT_H_

#include <iostream>
#include <string>
#include <fstream>
#include "def.h"
#include "KSCppUnit_TestResultCollector.h"

int Print_STD(
    const KSCppUnit_TestResultCollector *pcResult, 
    const char cszTestName[], 
    const char cszStartTime[],
    const char cszEndTime[]
);
int Print_TXT(
    const KSCppUnit_TestResultCollector *pcResult,
    const char cszTestName[], 
    const char cszResultPath[],
    const char cszStartTime[], 
    const char cszEndTime[]
);

int _GetHead(
     const KSCppUnit_TestResultCollector *pcResult, 
     const char cszTestName[],
     const char cszStartTime[],
     const char cszEndTime[],
     std::string &strHead
);
int _GetSuccessfulResults(
    const TEST_RESULT &cSuccess, 
    int &nTotal, 
    std::string &strResults
);
int _GetFailedResults(
    const TEST_RESULT &cFailure, 
    int &nTotal,
    std::string &strResults
);
int _GetResult(const KSCppUnit_TestResult *pcResult,std::string &strResult);

//输出到屏幕
int Print_STD(
    const KSCppUnit_TestResultCollector *pcResult, 
    const char cszTestName[],
    const char cszStartTime[], 
    const char cszEndTime[]
)
{
    int nResult  = false;
    int nRetCode = false;

    std::string strResult;
    std::string strHead;
    TEST_RESULT Failures;    ///注意
    int nTotal = 0;

    KGLOG_PROCESS_ERROR(pcResult);
    KGLOG_PROCESS_ERROR(cszTestName);
    KGLOG_PROCESS_ERROR(cszStartTime);
    KGLOG_PROCESS_ERROR(cszEndTime);

    nRetCode = _GetHead(pcResult, cszTestName, cszStartTime, cszEndTime, strHead);
    KGLOG_PROCESS_ERROR(nRetCode);

    Failures = pcResult->GetResFailures();
    nRetCode = _GetFailedResults(Failures, nTotal, strResult);
    KGLOG_PROCESS_ERROR(nRetCode);

    std::cout << std::endl << strHead << std::endl;
    std::cout << strResult;

    nResult = true;
Exit0:
    return nResult;
}

//文本文件
int Print_TXT(
    const KSCppUnit_TestResultCollector *pcResult, 
    const char cszTestName[],
    const char cszResultPath[],
    const char cszStartTime[], 
    const char cszEndTime[]
)
{
    int nResult  = false;
    int nRetCode = false;

    char szFileName[_MAX_PATH];
    std::string strResult;
    std::string strHead;
    std::string strS;
    std::ofstream FileStrm;
    int nFileStrmFlag = false;
    int nTotal = 0;
    char szDate[32];
    TEST_RESULT Failures;
    TEST_RESULT Sussess;

    KGLOG_PROCESS_ERROR(pcResult);
    KGLOG_PROCESS_ERROR(cszTestName);
    KGLOG_PROCESS_ERROR(cszResultPath);
    KGLOG_PROCESS_ERROR(cszStartTime);
    KGLOG_PROCESS_ERROR(cszEndTime);

    nRetCode = _GetHead(pcResult, cszTestName, cszStartTime, cszEndTime, strHead);    
    KGLOG_PROCESS_ERROR(nRetCode);

    Failures = pcResult->GetResFailures();
    nRetCode = _GetFailedResults(Failures, nTotal, strResult);
    KGLOG_PROCESS_ERROR(nRetCode);

    Sussess  = pcResult->GetResSuccess();

    nRetCode = _GetSuccessfulResults(Sussess, nTotal, strS);
    KGLOG_PROCESS_ERROR(nRetCode);
    strResult += strS;

    nRetCode = GetDate(szDate,32);
    KGLOG_PROCESS_ERROR(nRetCode);

    nRetCode = _snprintf(
        szFileName, 
        _MAX_PATH - 1,
        "%s\\%s_%s.txt", 
        cszResultPath, 
        cszTestName, 
        szDate
    );
    KGLOG_PROCESS_ERROR(nRetCode);
    szFileName[_MAX_PATH - 1] = '\0';

    FileStrm.open(szFileName, std::ios_base::out | std::ios_base::trunc);
    nRetCode = FileStrm.is_open();
    KGLOG_PROCESS_ERROR(nRetCode);
    nFileStrmFlag = true;

    FileStrm << std::endl << strHead << std::endl;
    FileStrm << strResult;

    nResult = true;
Exit0:
    if (nFileStrmFlag)
    {
        FileStrm.close();
    }

    return nResult;
}

int _GetHead(
    const KSCppUnit_TestResultCollector *pcResult, 
    const char cszTestName[],
    const char cszStartTime[], 
    const char cszEndTime[],
    std::string &strHead
)
{
    int nResult  = false;
    int nRetCode = false;

    char szBuffer[16];
    std::string strRun;
    std::string strSuccess;
    std::string strFail;
    std::string strError;
    char *pString = NULL;

    KGLOG_PROCESS_ERROR(pcResult);
    KGLOG_PROCESS_ERROR(cszTestName);
    KGLOG_PROCESS_ERROR(cszStartTime);
    KGLOG_PROCESS_ERROR(cszEndTime);

    pString = itoa(pcResult->RunTests(), szBuffer, 10);
    KGLOG_PROCESS_ERROR(pString);
    strRun = (std::string)pString;

    pString = itoa(pcResult->Success(), szBuffer, 10);
    KGLOG_PROCESS_ERROR(pString);
    strSuccess = (std::string)pString;

    pString = itoa(pcResult->Failures(), szBuffer, 10);
    KGLOG_PROCESS_ERROR(pString);
    strError = (std::string)pString;

    pString = itoa(pcResult->Errors(), szBuffer, 10);
    KGLOG_PROCESS_ERROR(pString);
    strFail = (std::string)pString;

    strHead = "测试项目: " + (std::string)cszTestName +
              "\n测试时间: " + (std::string)cszStartTime + " 至 " + (std::string)cszEndTime +
              "\n测试结果: " + "运行 " + strRun + 
              ", 成功 " + strSuccess +
              ", 失败 " + strFail +
              ", 错误 " + strError +
              "\n详细信息: \n\n";

    nResult = true;
Exit0:
    return nResult;
}

int _GetSuccessfulResults(
    const TEST_RESULT &cSuccess, 
    int &nTotal, 
    std::string &strResults
)
{
    int nResult  = false;
    int nRetCode = false;

    char szBuf[32];
    std::string strTotal;
    std::string strS;
    char *pString = NULL;
    KSCppUnit_TestResult *pTestResult = NULL;

    //遍历所有执行失败的案例信息
    TEST_RESULT::const_iterator cit = cSuccess.begin();  

    while (cit != cSuccess.end()) 
    {   
        nTotal++;
        pString = itoa(nTotal, szBuf, 10);
        KGLOG_PROCESS_ERROR(pString);
        strTotal = (std::string)pString;

        pTestResult = (KSCppUnit_TestResult *)(cit->second);

        strResults += "   " + strTotal + ".  ";

        nRetCode = _GetResult(pTestResult, strS);
        KGLOG_PROCESS_ERROR(nRetCode);

        strResults += strS;

        strResults += "\n\n";

        cit++;
    }

    nResult = true;
Exit0:
    return nResult;
}

int _GetFailedResults(
    const TEST_RESULT &cFailure, 
    int &nTotal,
    std::string &strResults
)
{
    int nResult  = false;
    int nRetCode = false;

    char szBuf[32];
    std::string strTotal;
    std::string strS;
    char *pString = NULL;
    KSCppUnit_TestResult *pTestResult = NULL;

    //遍历所有执行失败的案例信息
    TEST_RESULT::const_iterator cit = cFailure.begin();   

    while (cit != cFailure.end())
    {
        nTotal++;
        pString = itoa(nTotal, szBuf, 10);
        KGLOG_PROCESS_ERROR(pString);
        strTotal = (std::string)pString;

        pTestResult = (KSCppUnit_TestResult *)(cit->second);

        strResults += "   " + strTotal + ".  ";

        nRetCode = _GetResult(pTestResult, strS);
        KGLOG_PROCESS_ERROR(nRetCode);

        strResults += strS;

        strResults += "\n\n";

        cit++;
    }

    nResult = true;
Exit0:
    return nResult;
}

int _GetResult(const KSCppUnit_TestResult *pcResult,std::string &strResult)
{
    int nResult  = false;
    int nRetCode = false;

    char szBuf[32];
    std::string strS;
    char *pString = NULL;

    KGLOG_PROCESS_ERROR(pcResult);

    pString = itoa(pcResult->Line(), szBuf, 10);
    KGLOG_PROCESS_ERROR(pString);
    strS = (std::string)pString;

    switch(pcResult->Result())
    {
    case KSCPPUNIT_ERROR:
        strResult = "[Error]  ";
        break;
    case KSCPPUNIT_FAILURE:
        strResult = "[Failure]  ";
        break;
    case KSCPPUNIT_SUCCESS:
        strResult = "[OK]  ";
        break;
    default:
        break;
    }    
    strResult += pcResult->FunctionName() + "  ";
    strResult += pcResult->Description()  + "   \n";
    
    if (pcResult->Result() != KSCPPUNIT_SUCCESS)
    {
        strResult += "       Line:" + strS + "   ";
        strResult += "File: " + pcResult->FileName();
    }

    nResult = true;
Exit0:
    return nResult;
}

#endif //_KS_UNIT_STD_TXT_H_