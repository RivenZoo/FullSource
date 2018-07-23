//////////////////////////////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
//
//  FileName    :   GetBoolTest.h    
//  Version     :   1.0
//  Creater     :   DengWenfeng
//  Date        :   2008-7-3 14:37
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef _GetBoolTest_h__
#define _GetBoolTest_h__

#include "cppunit/extensions/HelperMacros.h"

#pragma warning(disable:4996)

class KGT_GetBoolTest : public CppUnit::TestFixture   
{
    CPPUNIT_TEST_SUITE(KGT_GetBoolTest);

    CPPUNIT_TEST(TestGetBool_01);
    CPPUNIT_TEST(TestGetBool_02);
    CPPUNIT_TEST(TestGetBool_03);
    CPPUNIT_TEST(TestGetBool_04);
    CPPUNIT_TEST(TestGetBool_05);
    CPPUNIT_TEST(TestGetBool_06);
    CPPUNIT_TEST(TestGetBool_07);
    CPPUNIT_TEST(TestGetBool_08);
    CPPUNIT_TEST(TestGetBool_09);
    CPPUNIT_TEST(TestGetBool_10);
    CPPUNIT_TEST(TestGetBool_11);
    CPPUNIT_TEST(TestGetBool_12);

    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
public:
    /////////////////////////////配置文件或命令行有记录///////////////////////
    void TestGetBool_01();        //输入的lpSection为空，其他参数不为空
    void TestGetBool_02();        //输入的lpKeyName为空，其他参数不为空
    void TestGetBool_03();        //输入的lpSection和lpKeyName为空，其他参数不为空
    void TestGetBool_04();        //输入的lpSection存在，但输入的lpKeyName不存在
    void TestGetBool_05();        //输入的lpSection不存在
    void TestGetBool_06();        //value值为全大写的"YES",或"TRUE"(或"NO","FALSE")
    void TestGetBool_07();        //value值为全小写的"yes",或"true"(或"no","false")
    void TestGetBool_08();        //value值为大小写混合的"yEs",或"True"(或"No","False")
    void TestGetBool_09();        //value值不是有效关键字
    void TestGetBool_10();        //value值为空值

    /////////////////////////////配置文件或命令行没有记录///////////////////////
    void TestGetBool_11();        //输入的lpSection和lpKeyName为空值
    void TestGetBool_12();        //输入的lpSection和lpKeyName为非空值
};

#endif // GetBoolTest_h__