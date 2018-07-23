//////////////////////////////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
//
//  FileName    :   GetInteger2Test.h    
//  Version     :   1.0
//  Creater     :   DengWenfeng
//  Date        :   2008-7-2 14:40
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef _GetInteger2Test_h__
#define _GetInteger2Test_h__

#include "cppunit/extensions/HelperMacros.h"

class KGT_GetInteger2Test : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(KGT_GetInteger2Test);

    CPPUNIT_TEST(TestGetInteger2_01);
    CPPUNIT_TEST(TestGetInteger2_02);
    CPPUNIT_TEST(TestGetInteger2_03);
    CPPUNIT_TEST(TestGetInteger2_04);
    CPPUNIT_TEST(TestGetInteger2_05);
    CPPUNIT_TEST(TestGetInteger2_06);
    CPPUNIT_TEST(TestGetInteger2_07);
    CPPUNIT_TEST(TestGetInteger2_08);
    CPPUNIT_TEST(TestGetInteger2_09);
    CPPUNIT_TEST(TestGetInteger2_10);
    CPPUNIT_TEST(TestGetInteger2_11);
    CPPUNIT_TEST(TestGetInteger2_12);
    CPPUNIT_TEST(TestGetInteger2_13);

    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
public:
    /////////////////////////////配置文件或命令行有记录///////////////////////
    void TestGetInteger2_01();           //输入的lpSection为空，其他参数不为空
    void TestGetInteger2_02();           //输入的lpKeyName为空，其他参数不为空
    void TestGetInteger2_03();           //输入的lpSection和lpKeyName都为空，其他参数不为空
    void TestGetInteger2_04();           //输入的lpSection存在，但输入的lpKeyName不存在
    void TestGetInteger2_05();           //输入的lpSection不存在
    void TestGetInteger2_06();           //输入的lpSection存在，且输入的lpKeyName存在,value不为空,且有1个值
    void TestGetInteger2_07();           //输入的lpSection存在，且输入的lpKeyName存在,value不为空,且有2正个值
    void TestGetInteger2_08();           //输入的lpSection存在，且输入的lpKeyName存在,value不为空,且有3个值
    void TestGetInteger2_09();           //输入的lpSection存在，且输入的lpKeyName存在,value不为空,且有2个负值
    void TestGetInteger2_10();           //输入的lpSection存在，且输入的lpKeyName存在,value为空
    void TestGetInteger2_11();           //输入的lpSection存在，且输入的lpKeyName存在,value为非数字字符串

    /////////////////////////////配置文件或命令行没有记录///////////////////////
    void TestGetInteger2_12();           //输入的lpSection和lpKeyName为空值
    void TestGetInteger2_13();           //输入的lpSection和lpKeyName为非空值
};

#endif // GetInteger2Test_h__