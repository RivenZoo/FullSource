//////////////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   KSCppUnit_Helper.h 
//  Version     :   1.0
//  Creater     :   Cheng Zhaohui
//  Date        :   2005-12-05
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////

#ifndef _KS_CPP_UNIT_HELPER_H_
#define _KS_CPP_UNIT_HELPER_H_

#include <string>

#include "cppunit/extensions/HelperMacros.h"
#include "cppunit/TestFixture.h"

#include "KSCppUnit_TestResultCollector.h"
#include "Engine/KGLog.h"

extern KSCppUnit_TestResultCollector g_KS_CPPUNIT_result;

#define KS_CPPUNIT_DESCRIPTION(Description)                          \
        {                                                            \
            std::string strDescription;                              \
            strDescription = std::string(Description);               \
            if (strDescription.empty())                              \
                 strDescription = "[Œﬁ√Ë ˆ–≈œ¢]";                   \
            g_KS_CPPUNIT_result.SetCaseDescription(strDescription);  \
        }
       

#ifdef CPPUNIT_ASSERT
#undef CPPUNIT_ASSERT
#define CPPUNIT_ASSERT(condition)                                    \
        {                                                            \
            if (!(condition))                                        \
            {                                                        \
                KGLogPrintf(                                         \
                    KGLOG_DEBUG,                                     \
                    "CPPUNIT_ASSERT(%s) at line %d in %s\n", #condition, __LINE__, KG_FUNCTION  \
                );                                                   \
            }                                                        \
            CPPUNIT_NS::Asserter::failIf(                            \
                                            !(condition),            \
                                            CPPUNIT_NS::Message(""), \
                                            CPPUNIT_SOURCELINE()     \
                                        );                           \
        }
#endif //CPPUNIT_ASSERT

#endif //_KS_CPP_UNIT_HELPER_H_