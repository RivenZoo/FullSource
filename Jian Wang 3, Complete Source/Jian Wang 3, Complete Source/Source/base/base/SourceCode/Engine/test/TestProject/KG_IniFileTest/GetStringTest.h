//////////////////////////////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
//
//  FileName    :   GetStringTest.h    
//  Version     :   1.0
//  Creater     :   DengWenfeng
//  Date        :   2008-7-1 17:07
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef _GetStringTest_h__
#define _GetStringTest_h__

#include "cppunit/extensions/HelperMacros.h"

class KGT_GetStringTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(KGT_GetStringTest);

    CPPUNIT_TEST(TestGetString_01);
    CPPUNIT_TEST(TestGetString_02);
    CPPUNIT_TEST(TestGetString_03);
    CPPUNIT_TEST(TestGetString_04);
    CPPUNIT_TEST(TestGetString_05);
    CPPUNIT_TEST(TestGetString_06);
    CPPUNIT_TEST(TestGetString_07);
    CPPUNIT_TEST(TestGetString_08);
    CPPUNIT_TEST(TestGetString_09);
    CPPUNIT_TEST(TestGetString_10);

    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
public:
    void TestGetString_01();        //参数正确性，default=null
    /////////////////////////////////配置文件或命令行有记录/////////////////
    void TestGetString_02();        //输入的lpSection为空，其他参数不为空
    void TestGetString_03();        //输入的lpKeyName为空，其他参数不为空
    void TestGetString_04();        //输入的lpSection和lpKeyName都为空，其他参数不为空
    void TestGetString_05();        //输入的lpSection存在，但输入的lpKeyName不存在
    void TestGetString_06();        //输入的lpSection不存在
    void TestGetString_07();        //输入的lpSection存在，且输入的lpKeyName存在，value长度为0
    void TestGetString_08();        //输入的lpSection存在，且输入的lpKeyName存在，value长度不为0

    /////////////////////////////////配置文件和命令行没有记录/////////////////
    void TestGetString_09();        //输入的lpSection和lpKeyName为空值
    void TestGetString_10();        //输入的lpSection和lpKeyName为非空值
};

#endif // GetStringTest_h__