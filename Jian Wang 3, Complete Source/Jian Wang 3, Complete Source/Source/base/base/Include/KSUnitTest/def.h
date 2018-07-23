//////////////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   Def.h
//  Version     :   1.0
//  Creater     :   Cheng Zhaohui
//  Date        :   2005-10-26
//  Comment     :   头文件，基本宏定义，及公共函数实现
//
//////////////////////////////////////////////////////////////////////////////////////

#ifndef _KS_UNIT_DEF_H_
#define _KS_UNIT_DEF_H_

#include "../cppunit/extensions/TestFactoryRegistry.h"
#include "../cppunit/TestResultCollector.h"
#include "../cppunit/TextOutputter.h"
#include "../cppunit/XmlOutputter.h"
#include "../cppunit/TestResult.h"
#include "../cppunit/TestFailure.h"
#include "../cppunit/TestRunner.h"
#include "../cppunit/TextTestProgressListener.h"
#include "../cppunit/extensions/HelperMacros.h"
#include "../cppunit/TestFixture.h"

#include <assert.h>

#include <time.h>
#include <string>
#include "../Engine/KGLog.h"


enum OUTPUT_TYPE
{
    STD_OUTPUT  = 0x01,
    TXT_OUTPUT  = 0x02,
    HTML_OUTPUT = 0x04,
    //XML_OUTPUT  = 0x08,
    //DB_OUTPUT   = 0x10
};


inline int GetTime(char szTime[], int nTimeSize);
inline int GetDate(char szDate[], int nDateSize);
inline int string_replace(
    std::string &SourceStr, 
    const std::string &FindStr, 
    const std::string &ReplaceStr
);

inline int GetTime(char szTime[], int nTimeSize)
{
    int nResult  = false;
    int nRetCode = false;

    struct tm *curtime = NULL;
    time_t ltime = -1;

    KGLOG_PROCESS_ERROR(szTime);
    KGLOG_PROCESS_ERROR(nTimeSize > 0);

    time(&ltime);
    KGLOG_PROCESS_ERROR(ltime != -1);

    curtime = localtime(&ltime);
    KGLOG_PROCESS_ERROR(curtime);

    nRetCode = _snprintf(
        szTime,
        nTimeSize - 1,
        "%04d年%02d月%02d日 %02d点%02d分%02d秒", 
        curtime->tm_year + 1900,
        curtime->tm_mon + 1, 
        curtime->tm_mday,
        curtime->tm_hour,
        curtime->tm_min,
        curtime->tm_sec
    );
    KGLOG_PROCESS_ERROR(nRetCode);
    szTime[nTimeSize - 1] = '\0';

    nResult = true;
Exit0:
    return nResult;
}

inline int GetDate(char szDate[], int nDateSize)
{
    int nResult  = false;
    int nRetCode = false;

    struct tm *curtime = NULL;
    time_t ltime = -1;

    KGLOG_PROCESS_ERROR(szDate);
    KGLOG_PROCESS_ERROR(nDateSize > 0);

    time(&ltime);
    KGLOG_PROCESS_ERROR(ltime != -1);

    curtime = localtime(&ltime);
    KGLOG_PROCESS_ERROR(curtime);

    nRetCode = _snprintf(
        szDate,
        nDateSize - 1,
        "%04d%02d%02d%02d%02d%02d",
        curtime->tm_year + 1900,
        curtime->tm_mon + 1, 
        curtime->tm_mday,
        curtime->tm_hour,
        curtime->tm_min,
        curtime->tm_sec
    );
    KGLOG_PROCESS_ERROR(nRetCode);
    szDate[nDateSize - 1] = '\0';

    nResult = true;
Exit0:
    return nResult;
}

inline int string_replace(
    std::string &SourceStr, 
    const std::string &FindStr, 
    const std::string &ReplaceStr
)
{
    int nResult  = false;
    int nRetCode = false;

    std::string::size_type Pos = 0;
    std::string::size_type SrcLen = FindStr.size();
    std::string::size_type DesLen = ReplaceStr.size();

    while((Pos = SourceStr.find(FindStr)) != std::string::npos)
    {
        SourceStr.replace(Pos, SrcLen, ReplaceStr);
    }

    nResult = true;
//Exit0:
    return nResult;
}

#endif  //_KS_UNIT_DEF_H_