//////////////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   PrintHTML.h
//  Version     :   1.0
//  Creater     :   Cheng Zhaohui
//  Date        :   2005-10-26
//  Comment     :   将cppunit测试结果以html网页格式输出，依赖css.css样式表文件，
//                  需要将css.css文件跟.html文件放到同级目录下
//
//////////////////////////////////////////////////////////////////////////////////////

#ifndef _KS_UNIT_HTML_H_
#define _KS_UNIT_HTML_H_

#include <string>
#include <fstream>
#include "def.h"
#include "KSCppUnit_TestResultCollector.h"

int Print_HTML(
    const KSCppUnit_TestResultCollector *pcResult, 
    const char cszTestName[], 
    const char cszResultPath[], 
    const char cszStartTime[], 
    const char cszEndTime[]
);

//将所有执行失败的案例信息输出至html文件
int _Print_Results(
    const KSCppUnit_TestResultCollector *pcResult, 
    std::ofstream &OStrm
);
int _Print_Result(const KSCppUnit_TestResult *pcResult, std::ofstream &OStrm);
int _Print_Header(std::ofstream &OStrm);
int _Print_Tail(std::ofstream &OStrm);

int Print_HTML(
    const KSCppUnit_TestResultCollector *pcResult, 
    const char cszTestName[],
    const char cszResultPath[], 
    const char cszStartTime[], 
    const char cszEndTime[]
)
{
    int nResult  = false;
    int nRetCode = false;

    char szFileName[MAX_PATH];
    char szDate[32];
    std::ofstream FileStrm;
    int nFileStrmFlag = false;

    KGLOG_PROCESS_ERROR(pcResult);
    KGLOG_PROCESS_ERROR(cszTestName);
    KGLOG_PROCESS_ERROR(cszResultPath);
    KGLOG_PROCESS_ERROR(cszStartTime);
    KGLOG_PROCESS_ERROR(cszEndTime);

    nRetCode = GetDate(szDate,32);
    KGLOG_PROCESS_ERROR(nRetCode);

    nRetCode = _snprintf(
        szFileName, 
        sizeof(szFileName) - 1,
        "%s\\%s_%s.html",
        cszResultPath, 
        cszTestName, 
        szDate
    );
    KGLOG_PROCESS_ERROR(nRetCode);
    szFileName[sizeof(szFileName) - 1] = '\0';

    FileStrm.open(szFileName, std::ios_base::out | std::ios_base::trunc);
    nRetCode = FileStrm.is_open();
    KGLOG_PROCESS_ERROR(nRetCode);
    nFileStrmFlag = true;
 
    FileStrm << "<LINK href=\"css.css\" type=\"text/css\" rel=\"stylesheet\">\n";
    FileStrm << "<HTML>\n";
    FileStrm << "<TABLE class=cs1_project border=1>\n";
    FileStrm << "  <TBODY>\n";
    FileStrm << "  <TR>\n";
    FileStrm << "    <TH colSpan=3>" << cszTestName << "单元测试报告</TH>\n";
    FileStrm << "  </TR>\n";
    FileStrm << "  <TR>\n";
    FileStrm << "    <TD colSpan=2>\n";
    FileStrm << "      <TABLE class=cs1_distribution border=1>\n";
    FileStrm << "        <TBODY>\n";
    FileStrm << "        <TR>\n";
    FileStrm << "          <TD class=cs1_category colSpan=2> 测试概况 </TD>\n";
    FileStrm << "        </TR>\n";
    FileStrm << "        <TR>\n";
    FileStrm << "          <TD class=cs1_count >[测试项目] </TD>\n";
    FileStrm << "          <TD class=cs1_description>" << cszTestName << "</TD></TR>\n";
    FileStrm << "        <TR>\n";
    FileStrm << "          <TD class=cs1_count>[测试时间] </TD>\n";
    FileStrm << "         <TD class=cs1_description>" << cszStartTime  << " 至 "<< cszEndTime << "</TD></TR>\n";
    FileStrm << "        <TR>\n";
    FileStrm << "          <TD class=cs1_count>[测试结果] </TD>\n";
    FileStrm << "          <TD class=cs1_description>运行 " << pcResult->RunTests()  << ", 成功 " << pcResult->Success() << ", 失败 " << pcResult->Failures() << ", 错误 " << pcResult->Errors() << "</TD>\n";
    FileStrm << "        </TR>\n";
    FileStrm << "        </TBODY>\n";
    FileStrm << "      </TABLE>\n";
    FileStrm << "    </TD>\n";
    FileStrm << "  </TR>\n";
    FileStrm << "  </TBODY>\n";
    FileStrm << "</TABLE>\n";

    nRetCode = _Print_Header(FileStrm);
    KGLOG_PROCESS_ERROR(nRetCode);

    nRetCode = _Print_Results(pcResult, FileStrm);
    KGLOG_PROCESS_ERROR(nRetCode);

    nRetCode = _Print_Tail(FileStrm);
    KGLOG_PROCESS_ERROR(nRetCode);

    nResult = true;
Exit0:
    if (nFileStrmFlag)
    {
        FileStrm.close();
        nFileStrmFlag = FALSE;
    }

    return nResult;
}

int _Print_Results(const KSCppUnit_TestResultCollector *pcResult, std::ofstream &OStrm)
{
    int nResult  = false;
    int nRetCode = false;

    const KSCppUnit_TestResult *pcTestResult = NULL;
    TEST_RESULT::const_iterator cit;

    KGLOG_PROCESS_ERROR(pcResult);
    
    cit = pcResult->GetResFailures().begin(); //失败案例
    while (cit != pcResult->GetResFailures().end()) 
    {   
        pcTestResult = (const KSCppUnit_TestResult *)(cit->second);
        _Print_Result(pcTestResult, OStrm);
        cit++;
    }

    cit = pcResult->GetResSuccess().begin(); //成功案例
    while (cit != pcResult->GetResSuccess().end()) 
    {   
        pcTestResult = (const KSCppUnit_TestResult *)(cit->second);
        _Print_Result(pcTestResult, OStrm);
        cit++;
    }

    nResult = true;
Exit0:
    return nResult;
}

int _Print_Result(const KSCppUnit_TestResult *pcResult, std::ofstream &OStrm)
{
    int nResult  = false;
    int nRetCode = false;

    static int nIndex = 0;

    KGLOG_PROCESS_ERROR(pcResult);

    nIndex++;
    
    OStrm << "        <TR>\n";
    
    OStrm << "          <TD class=cs1_row_data>" << nIndex << "</TD>\n";

    OStrm << "          <TD class=cs2_row_data>" << pcResult->FunctionName() << "</TD>\n";

    OStrm << "          <TD class=cs3_row_data>" << pcResult->Description() << "</TD>\n";

    if (pcResult->Result() == KSCPPUNIT_SUCCESS)
    {
        OStrm << "          <TD class=cs4_row_data>" << "-" << "</TD>\n";
    
        OStrm << "          <TD class=cs5_row_data>" << "-" << "</TD>\n";

        OStrm << "          <TD class=cs6_row_data>" << "<font color=#10A322>" << "OK" << "</font>" << "</TD>\n";
    }
    else
    {
        OStrm << "          <TD class=cs4_row_data>" << pcResult->Line() << "</TD>\n";

        OStrm << "          <TD class=cs5_row_data>" << pcResult->FileName() << "</TD>\n";

        OStrm << "          <TD class=cs6_row_data>" << "<font color=#ff0000>" << ((pcResult->Result() == KSCPPUNIT_ERROR) ? "Error" : "Failure") << "</font>" << "</TD>\n";
    }

    OStrm << "        </TR>\n";

    nResult = true;
Exit0:
    return nResult;
}

int  _Print_Header(std::ofstream &OStrm)
{
    int nResult  = false;
    int nRetCode = false;

    OStrm << "<TABLE class=cs1_project border=1>\n";
    OStrm << "  <TBODY>\n";
    OStrm << "    <TD>\n";
    OStrm << "      <TABLE class=cs1_index border=1>\n";
    OStrm << "        <TBODY>\n";
    OStrm << "        <TR>\n";
    OStrm << "          <TD class=cs1_header_data>编号</TD>\n";
    OStrm << "          <TD class=cs1_header_data>案例名称</TD>\n";
    OStrm << "          <TD class=cs1_header_data>案例描述</TD>\n";
    //OStrm << "          <TD class=cs1_header_data>详细描述</TD>\n";
    OStrm << "          <TD class=cs1_header_data>行号</TD>\n";
    OStrm << "          <TD class=cs1_header_data>文件名称</TD>\n";
    OStrm << "          <TD class=cs1_header_data>执行结果</TD>\n";
    OStrm << "        </TR>\n";

    nResult = true;
//Exit0:
    return nResult;
}

int  _Print_Tail(std::ofstream &OStrm)
{ 
    int nResult  = false;
    int nRetCode = false;

    OStrm << "        </TBODY>\n";
    OStrm << "      </TABLE>\n";
    OStrm << "   </TD>\n";
    OStrm << "  </TBODY>\n";
    OStrm << "</TABLE>\n";
    OStrm << "</HTML>\n";

    nResult = true;
//Exit0:
    return nResult;
}

#endif //_KS_UNIT_HTML_H_