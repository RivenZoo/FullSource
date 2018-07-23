//---------------------------------------------------------------------------
// Sword3 Engine (c) 1999-2004 by Kingsoft
// File:	KList.h
// Date:	2000.08.08
// Code:	WangWei(Daphnis)
// Desc:	Header File
//---------------------------------------------------------------------------
#ifndef	_ENGINE_KLLIST_H_
#define	_ENGINE_KLLIST_H_

//---------------------------------------------------------------------------
#include "KNode.h"
//---------------------------------------------------------------------------

class ENGINE_API KList
{
public:
	KList();
	KNode*	GetHead()	{ return m_pListHead; }
	KNode*	GetTail()	{ return m_pListTail; }
	void	AddHead(KNode *pNode); // 在最前面增加一个节点
	void	AddTail(KNode *pNode); // 在最后面增加一个节点
	KNode*	RemoveHead();	// 删除第一个节点
	KNode*	RemoveTail();	// 删除最后一个节点
	int		IsEmpty();		// 是否是个空的链表
	long	GetNodeCount();
private:
	friend class KNode;

	KNode*	m_pListHead;	// 头节点
	KNode*	m_pListTail;
	int		m_nodeCount;
};

#endif	//_ENGINE_KLLIST_H_
