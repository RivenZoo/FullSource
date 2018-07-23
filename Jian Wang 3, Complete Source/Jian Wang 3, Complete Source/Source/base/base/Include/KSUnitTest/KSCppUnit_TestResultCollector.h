//////////////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   KSCppUnit_TestResultCollector.h
//  Version     :   1.0
//  Creater     :   Cheng Zhaohui
//  Date        :   2005-12-05
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////

#ifndef _KS_CPP_UNIT_TESTRESULTCOLLECTOR_H_
#define _KS_CPP_UNIT_TESTRESULTCOLLECTOR_H_

#include "cppunit/Portability.h"
#include "cppunit/SynchronizedObject.h"
#include "cppunit/TestListener.h"

#include "Def.h"
#include "KSCppUnit_TestResult.h"

typedef std::map<CPPUNIT_NS::Test *, KSCppUnit_TestResult *> TEST_RESULT;

class KSCppUnit_TestResultCollector : public CPPUNIT_NS::TestListener, 
                                      public CPPUNIT_NS::SynchronizedObject
{
public:
    KSCppUnit_TestResultCollector()
    {
        reset();
    }
    virtual ~KSCppUnit_TestResultCollector();

public:
    void startTest(CPPUNIT_NS::Test *pTest);
    void endTest(CPPUNIT_NS::Test *pTest);
    void addFailure(const CPPUNIT_NS::TestFailure &failure);
    
    void SetCaseDescription(const std::string &strDescription)
    {   
        ExclusiveZone zone(m_syncObject); 
        m_strDescription = strDescription;
    }

    int RunTests() const {
        ExclusiveZone zone(m_syncObject);
        return (m_nSuccess + m_nFailures + m_nErrors);
    }
    int Success()  const {ExclusiveZone zone(m_syncObject); return m_nSuccess;}
    int Failures() const {ExclusiveZone zone(m_syncObject); return m_nFailures;}
    int Errors()   const {ExclusiveZone zone(m_syncObject); return m_nErrors;}

    const TEST_RESULT &GetResFailures() const {
        ExclusiveZone zone(m_syncObject); 
        return m_TestFailures;
    }
    const TEST_RESULT &GetResSuccess()  const {
        ExclusiveZone zone(m_syncObject); 
        return m_TestSuccess;
    }

    int WasSuccessful() const {
        ExclusiveZone zone(m_syncObject);
        return ((m_nFailures > 0 || m_nErrors > 0) ? 0 : 1);
    }

private:
    void reset()
    {
        ExclusiveZone zone(m_syncObject); 
        m_TestSuccess.clear();
        m_TestFailures.clear();        
        m_nSuccess  = 0;
        m_nFailures = 0;
        m_nErrors   = 0;
    }

protected:
    TEST_RESULT m_TestSuccess;
    TEST_RESULT m_TestFailures;
    int m_nSuccess;
    int m_nFailures;
    int m_nErrors;

    std::string m_strDescription;

private:
    KSCppUnit_TestResultCollector(const KSCppUnit_TestResultCollector &copy);
    KSCppUnit_TestResultCollector &operator=(const KSCppUnit_TestResultCollector &copy);
};

inline KSCppUnit_TestResultCollector::~KSCppUnit_TestResultCollector()
{
    TEST_RESULT::iterator it;
    for (it = m_TestFailures.begin(); it != m_TestFailures.end(); ++it)
    {
        KSCppUnit_TestResult *pResult = (KSCppUnit_TestResult *)(it->second);
        if (pResult)
        {
            delete pResult;
            pResult = NULL;
        }
    }
    m_TestFailures.clear();

    for (it = m_TestSuccess.begin(); it != m_TestSuccess.end(); ++it)
    {
        KSCppUnit_TestResult *pResult = (KSCppUnit_TestResult *)(it->second);
        if (pResult)
        {
            delete pResult;
            pResult = NULL;
        }
    }
    m_TestSuccess.clear();
}

inline void KSCppUnit_TestResultCollector::startTest(CPPUNIT_NS::Test *pTest)
{
    ExclusiveZone zone(m_syncObject);
    assert(pTest);
    m_strDescription.clear();
}

inline void KSCppUnit_TestResultCollector::endTest(CPPUNIT_NS::Test *pTest)
{
    assert(pTest);

    ExclusiveZone zone(m_syncObject);
    
    std::string &strFunction = pTest->getName();

    std::string strDescription = m_strDescription;
    if (strDescription.empty())
        strDescription = "[无描述信息]";

    TEST_RESULT::iterator it = m_TestFailures.find(pTest);
    if (it == m_TestFailures.end())//执行成功的案例
    {
        m_nSuccess++;

        KSCppUnit_TestResult *pResult = NULL;
        pResult = new KSCppUnit_TestResult(strFunction, strDescription, KSCPPUNIT_SUCCESS);
        if (pResult)
        {
            m_TestSuccess.insert(TEST_RESULT::value_type(pTest, pResult));
        }
    }
}

inline void KSCppUnit_TestResultCollector::addFailure(const CPPUNIT_NS::TestFailure &failure)
{
    CPPUNIT_NS::Test *pTest = NULL;

    ExclusiveZone zone(m_syncObject); 

    std::string &strFunction = failure.failedTestName();

    std::string strDescription = m_strDescription;
    if (strDescription.empty())
    {
        strDescription = "[无描述信息]";

        //查找是否是setUp()执行失败
        std::string strShortMsg = failure.thrownException()->message().shortDescription();
        std::string::size_type nFindPos = strShortMsg.find("setUp");
        if (nFindPos != std::string::npos)
        {
            strDescription = "[setUp() 执行失败]";
        }
    }
    
    std::string &strFileName = failure.sourceLine().fileName();
    std::string::size_type Pos = strFileName.rfind("\\");
    strFileName.erase(0, Pos + 1);

    int nLine = failure.sourceLine().lineNumber();

    RESULT_TYPE Type;    
    if (failure.isError())
    {
        m_nErrors++;
        Type = KSCPPUNIT_ERROR;
    }
    else
    {
        m_nFailures++;
        Type = KSCPPUNIT_FAILURE;
    }

    KSCppUnit_TestResult *pResult = NULL;
    pResult = new KSCppUnit_TestResult(strFunction, strDescription, Type, strFileName, nLine);
    if (pResult)
    {        
        pTest = failure.failedTest();
        m_TestFailures.insert(TEST_RESULT::value_type(pTest, pResult));
    }
}

#endif  //_KS_CPP_UNIT_TESTRESULTCOLLECTOR_H_
