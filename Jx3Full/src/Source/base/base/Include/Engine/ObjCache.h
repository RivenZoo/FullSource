 /*****************************************************************************************
//  文件名/字符串关联资源对象cache形式管理
//	Copyright : Kingsoft 2002-2004
//	Author	:   Wooy(Wu yue)
//	CreateTime:	2002-11-11
//  Comment   : 源自 Represent2\ImageStore2
*****************************************************************************************/
#ifndef _ENGINE_OBJCACHE_H_
#define _ENGINE_OBJCACHE_H_

//## 每个文件名/字符串对应一个资源对象，文件名/字符串存在到id数值的映射，
//## 相同id的资源对象在cache中认为是同一个对象，只保留一个。

//KObjCache的加载对象回调函数
//参数：pszObjeName --> 对象资源文件名， ppObject 用于获取加载后对象的指针的缓冲区
//返回: 表示成功与否的布尔值
typedef int (*fnObjCacheLoadObjCallback)(const char* pszObjName, void** ppObject);
//KObjCache对已加载对象操作的回调函数
typedef int	(*fnObjCacheOperOnObjCallback)(void* pObject, void* pParam);

class ENGINE_API KObjCache
{
public:
    KObjCache();
    ~KObjCache();

	//## 初始化KObjCache对象,设置加载/卸载/停止对象的回调函数
    void Init(fnObjCacheLoadObjCallback fnLoad,
			fnObjCacheOperOnObjCallback fnFree,
			fnObjCacheOperOnObjCallback fnIsInsUsing);
    //## 清空释放全部的对象
    void FreeAllObj();
	//## 提供对全部的对象进行操作的接口
	void ActionForAllObj(fnObjCacheOperOnObjCallback fnActionForAll, void* pParam);
    //## 设置动态加载平衡参数。
    void SetBalanceParam(
        //## 加载对象的数目的平衡值。
        int nNumObj, 
        //## 每多少次引用对象后作一次平衡检查。
		unsigned int uCheckPoint = 10000);

    //## 获取资源对象
    void* GetObj(
        //## 资源文件名称
        const char* pszObj,
        //## id
        unsigned int& uObj,
        //## Object原来在Cache内的位置。
        int& nObjPosition);

	//## 指定释放资源对象。
    void FreeObj(
        //## 文件名。
        const char* pszObj);

private:

    //## 存储保存id以及对象指针的结构
    struct KObj
    {
        //## id
        unsigned int uId;
		//在本次引用循环中是否被引用到
		int nRef;
        //## 图形数据对象指针。
        void* pObject;
    };

private:

	//## 扩展m_pObjectList的空间，使得存储更多图资源引用表述对象。
    bool ExpandSpace();

	int	 CanBeFree(void *pObject)
		{ return	(!m_fnObjIsInUsing(pObject, 0)); }

	//## 检查图资源存储量的平衡状况。
    void CheckBalance();

    //## 获得给定id在纪录表中的位置。
    //## 返回值含义：
    //##  返回值 >= 0 --> 给定的id在纪录表中的位置（以0开始索引数值）
    //##  返回值 < 0  --> 表中没有给定的id，如果需要插入此id的话，插入位置应该为(-返回值-1)
    int FindObj(
        //##Documentation
        //## 图形的id
        unsigned int uObj, 
        //##Documentation
        //## 图形纪录在m_pObjectList中可能的位置。
        int nPossiblePosition);

private:

    enum IS_BALANCE_PARAM
	{
        //## 扩展m_pObjectList，每次操作增加的元素的数目
        ISBP_EXPAND_SPACE_STEP = 64,
        //## 每多少次引用对象后作一次平衡检查的默认值。
        ISBP_CHECK_POINT_DEF = 512,
        //## 对象数目平衡的默认值
		ISBP_BALANCE_NUM_DEF = 256,
        //## 靠近范围优先查找的范围大小。
        ISBP_TRY_RANGE_DEF = 8,
	};

private:
    //## 保存图形对象结构的线性表。内容依据图形的id按照升序排列。
	KObj* m_pObjectList;

    //## m_pObjectList向量中包含KObj元素的数目。暨当前向量做多可存储图形信息的数目。m_pObjectList空间大小改变时同时调整此值。
    int m_nNumReserved;

    //## 对象的数目。这些对象的信息紧挨着存储在m_pObjectList从头开始的位置，按照图形的id升序排列。
    int m_nNumObjs;

    //## 对对象访问总次数的累加纪录值。
    unsigned int m_uObjAccessCounter;

    //## 调整平衡的时刻设置。
    unsigned int m_uCheckPoint;

    //## 加载在内存中对象数目的平衡值
	int m_nBalanceNum;

	fnObjCacheLoadObjCallback		m_fnLoadObj;
	fnObjCacheOperOnObjCallback		m_fnFreeObj;
	fnObjCacheOperOnObjCallback		m_fnObjIsInUsing;
};


#endif //ifndef _ENGINE_OBJCACHE_H_
