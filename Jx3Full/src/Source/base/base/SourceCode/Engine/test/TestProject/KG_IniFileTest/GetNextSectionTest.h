//////////////////////////////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
//
//  FileName    :   GetNextSectionTest.h    
//  Version     :   1.0
//  Creater     :   DengWenfeng
//  Date        :   2008-6-30 14:36
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef _GetNextSectionTest_h__
#define _GetNextSectionTest_h__

#include "cppunit/extensions/HelperMacros.h"

class KGT_GetNextSectionTest : public CppUnit::TestFixture 
{
    CPPUNIT_TEST_SUITE(KGT_GetNextSectionTest);

    CPPUNIT_TEST(TestGetNextSection_01);
    CPPUNIT_TEST(TestGetNextSection_02);
    CPPUNIT_TEST(TestGetNextSection_03);
    CPPUNIT_TEST(TestGetNextSection_04);
    CPPUNIT_TEST(TestGetNextSection_05);
    CPPUNIT_TEST(TestGetNextSection_06);
    CPPUNIT_TEST(TestGetNextSection_07);
    CPPUNIT_TEST(TestGetNextSection_08);
    CPPUNIT_TEST(TestGetNextSection_09);
    CPPUNIT_TEST(TestGetNextSection_10);
    CPPUNIT_TEST(TestGetNextSection_11);
    
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
public:
    /////////////////////////////////KG_Ini_SectionMap有多条记录////////////////////////////
    void TestGetNextSection_01();           //空值的下一个section
    void TestGetNextSection_02();           //第一条记录的下一个section
    void TestGetNextSection_03();           //中间一条记录的下一个section(不是最后一个section)
    void TestGetNextSection_04();           //倒数第二条记录的下一个section
    void TestGetNextSection_05();           //最后一条记录的下一个section
    void TestGetNextSection_06();           //不存在的记录的下一个section
    
    /////////////////////////////KG_Ini_SectionMap只有1条记录///////////////////////////
    void TestGetNextSection_07();           //空值的下一个section
    void TestGetNextSection_08();           //存在的记录的下一个section
    void TestGetNextSection_09();           //不存在的记录的下一个section

    ////////////////////////////KG_Ini_SectionMap没有记录///////////////////////////////
    void TestGetNextSection_10();           //空值的下一个section
    void TestGetNextSection_11();           //非空值的下一个section
};

#endif // GetNextSectionTest_h__