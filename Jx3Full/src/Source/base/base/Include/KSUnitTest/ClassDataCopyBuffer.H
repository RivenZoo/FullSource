
#ifndef KINGSOFT_UNITTEST_CLASSDATACOPYBUFFER_H
#define KINGSOFT_UINITEST_CLASSDATACOPYBUFFER_H

/***************************************************
Filename:ClassDataCopyBuffer.H
CreatedBy: WilsonWei
CreatedOn: 2005年7月29日 14:11:41.5954528
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

aaaaaaaaaaaa
aaaaaaaaaaaaaaa
***************************************************/


namespace KingsoftUnitTest
{
	/*
	类数据副本容器,本类只提供给测试函数使用.
	*/
    class ClassDataCopyBuffer
	{
	public:
		ClassDataCopyBuffer()
		{
			_FirstCopy = 0;
			_SecondCopy = 0;
		}
		~ClassDataCopyBuffer(){
            ReleaseAllCopy();
        }
	protected:
		void* _FirstCopy;
		void* _SecondCopy;
		
	public:
		/*
		// 设置第一个拷贝
		// @pvTestData 要拷贝的类数据指针(_TestData类)
		// @lMemSize 要拷贝的类数据内存大小
		// @Returns: void.
		// @注意: 如果之前已存在一份拷贝,则原来的拷贝会被自动释放.
        */
		void SetFirstCopy( const void* pvTestData, long lMemSize )
		{
			ASSERT( pvTestData );
			if( _FirstCopy )
			{
				free(_FirstCopy);
				_FirstCopy = NULL;
			}
			_FirstCopy = malloc( lMemSize );
			memcpy( _FirstCopy, (void*)pvTestData, lMemSize );
		}
		/*
		// 设置第二个拷贝
		// @pvTestData 要拷贝的类数据指针(_TestData类)
		// @lMemSize 要拷贝的类数据内存大小
		// @Returns: void.
		// @注意: 如果之前已存在一份拷贝,则原来的拷贝会被自动释放.
        */
		void SetSecondCopy( const void* pvTestData, long lMemSize)
		{
			ASSERT( pvTestData );
			if( _SecondCopy )
			{
				free(_SecondCopy);
				_SecondCopy = NULL;
			}
			_SecondCopy = malloc( lMemSize );
			memcpy( _SecondCopy , (void*)pvTestData, lMemSize );
		}
		/*
		// 获取第一个类拷贝
		// @Returns: void*
        */
		void* GetFirstCopy() const
		{
			return _FirstCopy;
		}
		/*
		// 获取第二个类拷贝
		// @Returns: void*
        */
		void* GetSecondCopy() const
		{
			return _SecondCopy;
		}
		/*
		// 释放副本内存资源
		// @Returns: void.
        */
		void ReleaseAllCopy()
		{
			free(_FirstCopy);
			_FirstCopy = NULL;
			free(_SecondCopy);
			_SecondCopy = NULL;
		}
    };
};
#endif