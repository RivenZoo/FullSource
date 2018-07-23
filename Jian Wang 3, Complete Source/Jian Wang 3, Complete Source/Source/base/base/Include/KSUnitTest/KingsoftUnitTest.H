#ifndef KINGSOFT_UNITTEST_ICLASSUNITTEST_H
#define KINGSOFT_UINITEST_ICLASSUNITTEST_H

/***************************************************
Filename:KingsoftUnitTest.H
CreatedBy: WilsonWei
CreatedOn: 2005年7月29日 14:21:34.6882784
Description:
这个类是专门为单元测试服务的,鉴于采用以"类"为最小单位
进行单元测试的方案.类的成员数据变量的访问是非常频繁且
必须的.如果每个类的测试函数都对被测试类的数据成员进行
访问来达到数据比较的目的,会有缺漏,因为我们并不能保证
一个类的方法不会修改到其它的类数据成员.所以我们采用类
数据成员全匹配/比较的方法.即在进行一个操作(测试)之前,
先把该类的所有必要的成员变量保存一个副本,当做完操作(测试)
之后,再保存一个副本,把这两次副本进行全比较,可以达到检
验的目的.

至于为什么要使用这个方案,可以参与这个方案的讨论稿:
http://192.168.27.31/qcweb/pmwiki.php?n=XSJQC.XSJ-QC-SPEC-UnitTestWorkflow

**************************************************/


namespace KingsoftUnitTest
{
    // -------------------------------------------------------------------------
	// 功能		: 在类代码中使用的测试接口
	// 附注		: 
	// -------------------------------------------------------------------------
    #ifdef _UNIT_TEST
    #define EXPORT_TEST(classname) friend class classname##_Test
    #else // #ifdef _UNIT_TEST
    #define EXPORT_TEST(classname)
    #endif
	
	// -------------------------------------------------------------------------
	// 宏		: _UT_CLS_HEAD_BEGIN
	// 功能		: 这个宏写在测试类的头文件开头处
	// 附注		: 
	// -------------------------------------------------------------------------
	#define _UT_CLS_HEAD_INCLUDE()						    					\
			#include "cppunit/extensions/HelperMacros.h" 	    				\
			#include "cppunit/TestFixture.h" 									\
			#include "KSUnitTest/ClassDataCopyBuffer.H"
	
	// -------------------------------------------------------------------------
	// 宏		: _UT_CLS_HEAD_END
	// 功能		: 这个宏写在测试类的代码文件的开头处
	// 附注		: 
	// -------------------------------------------------------------------------
	#define _UT_CLS_IMP_NEEDED(ClassName) 										\
		CPPUNIT_TEST_SUITE_REGISTRATION(ClassName##_Test);
				
	//-------------------------------------------------------------------------
    /*存放类数据成员,这些数据成员是用来作"全比较"的,一般对应于
    //被测试类的数据成员(不含类方法).
    */
    struct _TestData;
	/*
	生成类成员数据测试的接口
	*/
	class IClassUnitTest
	{
	public:
  		/*将类的内存变量复制到第一份拷贝(_TestData类)*/
		virtual void DummyClassForFirstCopy(void* pvClassBeingTest)     = 0;
        /*将类的内存变量复制到第二份拷贝(_TestData类)*/
        virtual void DummyClassForSecondCopy(void* pvClassBeingTest)    = 0;
		/*将类的内存变量保存到指定的文件*/
		virtual void DummyClassToFile( LPCSTR szFilename)               = 0;
        /*比较两份拷贝,可指定在比较完成之后,是否自动释放内存数据拷贝*/
        virtual void CompareCopy(bool bAutoReleaseCopy)                 = 0;
	};
}

#endif