//////////////////////////////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
//
//  FileName    :   g_OpenCombinatorialIniFileTest.h    
//  Version     :   1.0
//  Creater     :   DengWenfeng
//  Date        :   2008-7-16 11:38
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef _g_OpenCombinatorialIniFileTest_H__
#define _g_OpenCombinatorialIniFileTest_H__

#include "cppunit/extensions/HelperMacros.h"

class KGT_g_OpenCombinatorialIniFileTest : public CppUnit::TestFixture
{ 
    CPPUNIT_TEST_SUITE(KGT_g_OpenCombinatorialIniFileTest);

    CPPUNIT_TEST(Test_g_OpenCombinatorialIniFile_01);
    CPPUNIT_TEST(Test_g_OpenCombinatorialIniFile_02);
    CPPUNIT_TEST(Test_g_OpenCombinatorialIniFile_03);
    CPPUNIT_TEST(Test_g_OpenCombinatorialIniFile_04);
    CPPUNIT_TEST(Test_g_OpenCombinatorialIniFile_05);
    CPPUNIT_TEST(Test_g_OpenCombinatorialIniFile_06);
    CPPUNIT_TEST(Test_g_OpenCombinatorialIniFile_07);
    CPPUNIT_TEST(Test_g_OpenCombinatorialIniFile_08);
    CPPUNIT_TEST(Test_g_OpenCombinatorialIniFile_09);
    CPPUNIT_TEST(Test_g_OpenCombinatorialIniFile_10);
    CPPUNIT_TEST(Test_g_OpenCombinatorialIniFile_11);
    CPPUNIT_TEST(Test_g_OpenCombinatorialIniFile_12);
    CPPUNIT_TEST(Test_g_OpenCombinatorialIniFile_13);

    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
public:
    void Test_g_OpenCombinatorialIniFile_01();          //命令行文件没有记录，ini文件有数据
    void Test_g_OpenCombinatorialIniFile_02();          //命令行文件有记录，ini文件没有数据
    void Test_g_OpenCombinatorialIniFile_03();          //命令行文件没有记录，ini文件没有数据
    void Test_g_OpenCombinatorialIniFile_04();          //命令行文件和ini文件都有数据，2者有相同的section
    void Test_g_OpenCombinatorialIniFile_05();          //命令行文件和ini文件都有数据，2者有相同的section,ini文件中只有section，没有key
    void Test_g_OpenCombinatorialIniFile_06();          //命令行文件和ini文件都有数据，2者有不同的section
    void Test_g_OpenCombinatorialIniFile_07();          //命令行文件和ini文件都有数据，2者有不同的section,ini文件中只有section,没有key
    void Test_g_OpenCombinatorialIniFile_08();          //命令行文件和ini文件都有数据，2者有相同的section，相同的key
    void Test_g_OpenCombinatorialIniFile_09();          //命令行文件和ini文件都有数据，2者有相同的section，不同的key
    void Test_g_OpenCombinatorialIniFile_10();          //命令行文件和ini文件都有数据，2者有相同的section，相同的key,相同的value
    void Test_g_OpenCombinatorialIniFile_11();          //命令行文件和ini文件都有数据，2者有相同的section，相同的key,不同的value
    void Test_g_OpenCombinatorialIniFile_12();          //命令行文件和ini文件都有数据，2者有相同的section，相同的key,不同的value,命令行的value=""
    void Test_g_OpenCombinatorialIniFile_13();          //命令行文件和ini文件都有数据，2者有相同的section，相同的key,不同的value,ini文件的value=""
private:

};

#endif //_g_OpenCombinatorialIniFileTest_H__