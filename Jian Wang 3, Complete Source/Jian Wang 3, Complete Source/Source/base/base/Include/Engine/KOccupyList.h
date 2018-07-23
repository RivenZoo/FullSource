//---------------------------------------------------------------------------
// Sword3 Engine (c) 2004 by Kingsoft
// File:	KOccupyList.h
// Date:	2004.08.29
// Code:	Wuyue(wooy)
// Desc:	占用情况表
//---------------------------------------------------------------------------
#ifndef __ENGINE_OCCUPYLIST_H__
#define	__ENGINE_OCCUPYLIST_H__

//该文件中名词含义：
//项：  占用表要管理的对象集合的一个个体
//节点：占用表的内部结构
//一个节点与一个项一一对应，由KOccupyListNode::nItemIndex指定前者到后者对应关系，
//由KOccupyListNode::nItemInListIndex指定后者到前者的对应关系。

//！！！对外函数传入传出的索引都是项索引！！！
//第0个项（节点）不参与使用不可被占用
//GetNext和GetPre用于遍历占用项
//KOccupyList::GetNext(0)调用用于取得第一个占用向索引。
class ENGINE_API KOccupyList
{
public:
	bool			Init(int nSize);
	void			UnInit();

	void			Occupy(int nIdx);	//占用某项
	void			Free(int nIdx);		//释放某项
	void			OccupyAll();		//全部项占用
	void			FreeAll();			//释放全部项

	int				IsOccupy(int nIdx);				//判断某项是否被占用
	int				GetFirstFree(int bOccupyIt);	//得到第一个未被占用的项的索引,传入参数表示是否要同时占用它
	int				GetOccupyCount() const { return m_nOccupyCount; }	//返回被占用的项的数目

	inline int		GetNext(int nIdx) const			//获取下一个占用项的索引
	{ 
		if (nIdx >= 0 && nIdx < m_nTotalCount)
		{
			int nIndexInList = m_pNodeList[nIdx].nItemInListIndex;
			if (nIndexInList < m_nOccupyCount)
				return m_pNodeList[nIndexInList + 1].nItemIndex;
		}
		return 0;
	}

	inline int		GetPrev(int nIdx) const			//获取前一个占用项的索引
	{
		if (nIdx >= 0 && nIdx < m_nTotalCount)
		{
			int nIndexInList = m_pNodeList[nIdx].nItemInListIndex;
			if (nIndexInList >= 1 && nIndexInList <= m_nOccupyCount)
				return m_pNodeList[nIndexInList - 1].nItemIndex;
		}
		return 0;
	}

	KOccupyList()		{ m_pNodeList = NULL; m_nTotalCount = 0; m_nOccupyCount = 0;}
	~KOccupyList()		{ UnInit(); }

private:
	struct		KOccupyListNode
	{
		int		nItemIndex;				//该节点对应的项的索引
		int		nItemInListIndex;		//与该节点相同索引的项在节点表中的位置
	};
	KOccupyListNode*	m_pNodeList;	//节点数组
	int					m_nTotalCount;	//节点总数目
	int					m_nOccupyCount;	//占用数目
};

#endif //__ENGINE_OCCUPYLIST_H__

