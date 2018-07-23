//////////////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   KSCppUnit_TestResult.h
//  Version     :   1.0
//  Creater     :   Cheng Zhaohui
//  Date        :   2005-12-05
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////


#ifndef _KS_CPP_UNIT_TESTRESULT_H_
#define _KS_CPP_UNIT_TESTRESULT_H_

#include <string>

typedef enum
{
    KSCPPUNIT_SUCCESS,
    KSCPPUNIT_FAILURE,
    KSCPPUNIT_ERROR
}RESULT_TYPE;

class KSCppUnit_TestResult
{
public:
    KSCppUnit_TestResult() {}

    KSCppUnit_TestResult(
                const std::string &strFunctionName,
                const std::string &strCaseDescription,
                RESULT_TYPE Result,
                const std::string strFileName = "",
                int nLine = -1
    )
    {
        m_strFunctionName = strFunctionName;
        m_strCaseDescription = strCaseDescription;
        m_Result = Result;
        m_strFileName = strFileName;
        m_nLine = nLine;
    }

    virtual ~KSCppUnit_TestResult() {}

public:
    const std::string &FunctionName() const {return m_strFunctionName;}
    
    const std::string &Description() const {return m_strCaseDescription;}
    
    RESULT_TYPE Result() const {return m_Result;}
    
    const std::string &FileName() const {return m_strFileName;}
    
    int Line() const {return m_nLine;}

private:
    std::string m_strFunctionName;
    std::string m_strCaseDescription;
    RESULT_TYPE m_Result;

    //以下是只有案例执行失败时才收集的信息
    std::string m_strFileName;
    int m_nLine;

private:
    KSCppUnit_TestResult(const KSCppUnit_TestResult &copy);
    KSCppUnit_TestResult operator =(const KSCppUnit_TestResult &copy);
};


#endif //_KS_CPP_UNIT_TESTRESULT_H_