//////////////////////////////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
//
//  FileName    :   GetStructTest.h    
//  Version     :   1.0
//  Creater     :   DengWenfeng
//  Date        :   2008-7-2 17:30
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef _GetStructTest_h__
#define _GetStructTest_h__

#include "cppunit/extensions/HelperMacros.h"
#include "time.h"

typedef struct MAN
{
    int nAge;
    char szName[32];
} MAN;
typedef struct PERSON    
{
    int nAge;
    char szName[32];
    long lMoney;
    bool bMan;
    float fScore;
    tm    dBirthday;
    MAN   man;
} TEST_STRUCT;

class KGT_GetStructTest : public CppUnit::TestFixture  
{
    CPPUNIT_TEST_SUITE(KGT_GetStructTest);

    CPPUNIT_TEST(TestGetStruct_01);
    CPPUNIT_TEST(TestGetStruct_02);
    CPPUNIT_TEST(TestGetStruct_03);
    CPPUNIT_TEST(TestGetStruct_04);
    CPPUNIT_TEST(TestGetStruct_05);
    CPPUNIT_TEST(TestGetStruct_06);
    CPPUNIT_TEST(TestGetStruct_07);
    CPPUNIT_TEST(TestGetStruct_08);
    CPPUNIT_TEST(TestGetStruct_09);
    CPPUNIT_TEST(TestGetStruct_10);
    CPPUNIT_TEST(TestGetStruct_11);

    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
public:
    /////////////////////////////配置文件或命令行有记录///////////////////////
    void TestGetStruct_01();        //输入的lpSection为空，其他参数不为空
    void TestGetStruct_02();        //输入的lpKeyName为空，其他参数不为空
    void TestGetStruct_03();        //输入的lpSection和lpKeyName为空，其他参数不为空
    void TestGetStruct_04();        //输入的lpSection存在，但输入的lpKeyName不存在
    void TestGetStruct_05();        //输入的lpSection不存在
    void TestGetStruct_06();        //struct的长度*2=value的长度,值正常
    void TestGetStruct_07();        //struct的长度*2=value的长度,但value的值含有0-f以外的字符串
    void TestGetStruct_08();        //struct的长度*2!=value的长度
    void TestGetStruct_09();        //struct的长度*2=value的长度,但value的值为空值

    /////////////////////////////配置文件或命令行没有记录///////////////////////
    void TestGetStruct_10();        //输入的lpSection和lpKeyName为空值
    void TestGetStruct_11();        //输入的lpSection和lpKeyName为非空值
private:
    TEST_STRUCT m_TestStruct;
};

#endif // GetStructTest_h__