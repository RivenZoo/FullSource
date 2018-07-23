//////////////////////////////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
//
//  FileName    :   IsSectionExistTest.h    
//  Version     :   1.0
//  Creater     :   DengWenfeng
//  Date        :   2008-7-1 11:55
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef _IsSectionExistTest_h__
#define _IsSectionExistTest_h__

#include "cppunit/extensions/HelperMacros.h"

class KGT_IsSectionExistTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(KGT_IsSectionExistTest);
    
    CPPUNIT_TEST(TestIsSectionExist_01);
    CPPUNIT_TEST(TestIsSectionExist_02);
    CPPUNIT_TEST(TestIsSectionExist_03);
    CPPUNIT_TEST(TestIsSectionExist_04);
    CPPUNIT_TEST(TestIsSectionExist_05);

    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
public:
    /////////////////////////////存在section记录//////////////////////
    void TestIsSectionExist_01();           //空值
    void TestIsSectionExist_02();           //非空值，且存在的section
    void TestIsSectionExist_03();           //非空值，且不存在的section

    /////////////////////////////不存在section记录//////////////////////
    void TestIsSectionExist_04();           //空值
    void TestIsSectionExist_05();           //非空值
};

#endif // IsSectionExistTest_h__