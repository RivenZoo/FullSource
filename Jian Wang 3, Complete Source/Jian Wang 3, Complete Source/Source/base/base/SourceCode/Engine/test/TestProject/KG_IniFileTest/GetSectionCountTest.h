//////////////////////////////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
//
//  FileName    :   GetSectionCountTest.h    
//  Version     :   1.0
//  Creater     :   DengWenfeng
//  Date        :   2008-7-1 11:17
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef _GetSectionCountTest_h__
#define _GetSectionCountTest_h__

#include "cppunit/extensions/HelperMacros.h"

class KGT_GetSectionCountTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(KGT_GetSectionCountTest);

    CPPUNIT_TEST(TestGetSectionCount_01);
    CPPUNIT_TEST(TestGetSectionCount_02);

    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
public:
    void TestGetSectionCount_01();          //没有section记录
    void TestGetSectionCount_02();          //有section记录
};

#endif // GetSectionCountTest_h__