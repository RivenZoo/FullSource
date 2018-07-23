//////////////////////////////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
//
//  FileName    :   GetNextKeyTest.h    
//  Version     :   1.0
//  Creater     :   DengWenfeng
//  Date        :   2008-7-1 9:16
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef _GetNextKeyTest_h__
#define _GetNextKeyTest_h__

#include "cppunit/extensions/HelperMacros.h"

class KGT_GetNextKeyTest : public CppUnit::TestFixture 
{
    CPPUNIT_TEST_SUITE(KGT_GetNextKeyTest);

    CPPUNIT_TEST(TestGetNextKey_01);
    CPPUNIT_TEST(TestGetNextKey_02);
    CPPUNIT_TEST(TestGetNextKey_03);
    CPPUNIT_TEST(TestGetNextKey_04);
    CPPUNIT_TEST(TestGetNextKey_05);
    CPPUNIT_TEST(TestGetNextKey_06);
    CPPUNIT_TEST(TestGetNextKey_07);
    CPPUNIT_TEST(TestGetNextKey_08);
    CPPUNIT_TEST(TestGetNextKey_09);
    CPPUNIT_TEST(TestGetNextKey_10);
    CPPUNIT_TEST(TestGetNextKey_11);
    CPPUNIT_TEST(TestGetNextKey_12);
    CPPUNIT_TEST(TestGetNextKey_13);

    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
public:
    ///////////////////////////section存在，且有多个key////////////////////////////
    void TestGetNextKey_01();            //空值的下一个key
    void TestGetNextKey_02();            //第一条记录的下一个key
    void TestGetNextKey_03();            //中间一条记录的下一个key（不是最后一个key）
    void TestGetNextKey_04();            //倒数第二条记录的下一个key
    void TestGetNextKey_05();            //最后一条记录的下一个key
    void TestGetNextKey_06();            //不存在的记录的下一个key

    ///////////////////////////section存在，但只有一个key///////////////////////////
    void TestGetNextKey_07();            //空值的下一个key
    void TestGetNextKey_08();            //存在记录的下一个key
    void TestGetNextKey_09();            //不存在记录的下一个key

    ///////////////////////////section存在，但没有key///////////////////////////////
    void TestGetNextKey_10();            //空值的下一个key
    void TestGetNextKey_11();            //非空值的下一个key

    /////////////////////////section不存在////////////////////////////////////////
    void TestGetNextKey_12();            //空值的下一个key
    void TestGetNextKey_13();            //非空值的下一个key
};

#endif // GetNextKeyTest_h__