//////////////////////////////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
//
//  FileName    :   GetIntegerTest.h    
//  Version     :   1.0
//  Creater     :   DengWenfeng
//  Date        :   2008-7-2 11:09
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef _GetIntegerTest_h__
#define _GetIntegerTest_h__

#include "cppunit/extensions/HelperMacros.h"

class KGT_GetIntegerTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(KGT_GetIntegerTest);

    CPPUNIT_TEST(TestGetInteger_01);
    CPPUNIT_TEST(TestGetInteger_02);
    CPPUNIT_TEST(TestGetInteger_03);
    CPPUNIT_TEST(TestGetInteger_04);
    CPPUNIT_TEST(TestGetInteger_05);
    CPPUNIT_TEST(TestGetInteger_06);
    CPPUNIT_TEST(TestGetInteger_07);
    CPPUNIT_TEST(TestGetInteger_08);
    CPPUNIT_TEST(TestGetInteger_09);
    CPPUNIT_TEST(TestGetInteger_10);
    CPPUNIT_TEST(TestGetInteger_11);

    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
public:
    /////////////////////////////配置文件或命令行有记录///////////////////////
    void TestGetInteger_01();           //输入的lpSection为空，其他参数不为空
    void TestGetInteger_02();           //输入的lpKeyName为空，其他参数不为空
    void TestGetInteger_03();           //输入的lpSection和lpKeyName都为空，其他参数不为空
    void TestGetInteger_04();           //输入的lpSection存在，但输入的lpKeyName不存在
    void TestGetInteger_05();           //输入的lpSection不存在
    void TestGetInteger_06();           //输入的lpSection存在，且输入的lpKeyName存在,value为数字字符串，且为正数
    void TestGetInteger_07();           //输入的lpSection存在，且输入的lpKeyName存在,value为数字字符串，且为负数
    void TestGetInteger_08();           //输入的lpSection存在，且输入的lpKeyName存在,value为空值
    void TestGetInteger_09();           //输入的lpSection存在，且输入的lpKeyName存在,value为非数字字符串

    /////////////////////////////配置文件或命令行没有记录///////////////////////
    void TestGetInteger_10();           //输入的lpSection和lpKeyName为空值
    void TestGetInteger_11();           //输入的lpSection和lpKeyName为非空值
};

#endif // GetIntegerTest_h__