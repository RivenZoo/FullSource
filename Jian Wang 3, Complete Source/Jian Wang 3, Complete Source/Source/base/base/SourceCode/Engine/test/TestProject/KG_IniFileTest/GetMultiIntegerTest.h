//////////////////////////////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
//
//  FileName    :   GetMultiIntegerTest.h    
//  Version     :   1.0
//  Creater     :   DengWenfeng
//  Date        :   2008-7-2 15:54
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef _GetMultiIntegerTest_h__
#define _GetMultiIntegerTest_h__

#include "cppunit/extensions/HelperMacros.h"

class KGT_GetMultiIntegerTest : public CppUnit::TestFixture 
{
    CPPUNIT_TEST_SUITE(KGT_GetMultiIntegerTest);
    
    CPPUNIT_TEST(TestGetMultiInteger_01);
    CPPUNIT_TEST(TestGetMultiInteger_02);
    CPPUNIT_TEST(TestGetMultiInteger_03);
    CPPUNIT_TEST(TestGetMultiInteger_04);
    CPPUNIT_TEST(TestGetMultiInteger_05);
    CPPUNIT_TEST(TestGetMultiInteger_06);
    CPPUNIT_TEST(TestGetMultiInteger_07);
    CPPUNIT_TEST(TestGetMultiInteger_08);
    CPPUNIT_TEST(TestGetMultiInteger_09);
    CPPUNIT_TEST(TestGetMultiInteger_10);
    CPPUNIT_TEST(TestGetMultiInteger_11);
    CPPUNIT_TEST(TestGetMultiInteger_12);
    CPPUNIT_TEST(TestGetMultiInteger_13);


    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void teatDown();
public:
    /////////////////////////////配置文件或命令行有记录///////////////////////
    void TestGetMultiInteger_01();           //输入的lpSection为空，其他参数不为空
    void TestGetMultiInteger_02();           //输入的lpKeyName为空，其他参数不为空
    void TestGetMultiInteger_03();           //输入的lpSection和lpKeyName都为空，其他参数不为空
    void TestGetMultiInteger_04();           //输入的lpSection存在，但输入的lpKeyName不存在
    void TestGetMultiInteger_05();           //输入的lpSection不存在
    void TestGetMultiInteger_06();           //输入的nCount<=0或nCount>INI_MAX_SUPPORT_MULTI_VALUE_COUNT
    void TestGetMultiInteger_07();           //输入的lpSection存在，且输入的lpKeyName存在,value的个数小于输入的nCount
    void TestGetMultiInteger_08();           //输入的lpSection存在，且输入的lpKeyName存在,value的个数等于输入的nCount
    void TestGetMultiInteger_09();           //输入的lpSection存在，且输入的lpKeyName存在,value的个数大于输入的nCount
    void TestGetMultiInteger_10();           //输入的lpSection存在，且输入的lpKeyName存在,value为空值
    void TestGetMultiInteger_11();           //输入的lpSection存在，且输入的lpKeyName存在,value为非数字字符串

    /////////////////////////////配置文件或命令行没有记录///////////////////////
    void TestGetMultiInteger_12();           //输入的lpSection和lpKeyName为空值
    void TestGetMultiInteger_13();           //输入的lpSection和lpKeyName为非空值
};

#endif // GetMultiIntegerTest_h__