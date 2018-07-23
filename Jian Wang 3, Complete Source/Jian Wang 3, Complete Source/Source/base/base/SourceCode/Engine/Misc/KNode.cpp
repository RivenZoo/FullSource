#include "Precompile.h"
#include "KNode.h"
#include "KList.h"
//---------------------------------------------------------------------------
// 函数:	Knode
// 功能:	构造
//---------------------------------------------------------------------------
KNode::KNode()
{
	m_pNext = NULL;
	m_pPrev = NULL;
	m_pList = NULL;
}

//----------------------------------------------------------------------------
// 函数:	InsertBefore
// 功能:	在前面插入一个结点
// 参数:	KNode*
//---------------------------------------------------------------------------
void KNode::InsertBefore(KNode *pNode)
{
	KASSERT(pNode && !pNode->IsLinked());
	pNode->m_pList = m_pList;
	pNode->m_pPrev = m_pPrev;
	pNode->m_pNext = this;
	if (m_pPrev)
	{
		m_pPrev->m_pNext = pNode;
	}
	if (m_pList)
	{
		if (m_pList->m_pListHead == this)
			m_pList->m_pListHead = pNode;
		++m_pList->m_nodeCount;
	}
	m_pPrev = pNode;
}

//---------------------------------------------------------------------------
// 函数:	InsertAfter
// 功能:	在后面插入一个结点
// 参数:	KNode*
//---------------------------------------------------------------------------
void KNode::InsertAfter(KNode *pNode)
{
	KASSERT(pNode && !pNode->IsLinked());
	pNode->m_pList = m_pList;
	pNode->m_pPrev = this;
	pNode->m_pNext = m_pNext;
	if (m_pNext)
	{
		m_pNext->m_pPrev = pNode;
	}
	if (m_pList)
	{
		if (m_pList->m_pListTail == this)
			m_pList->m_pListTail = pNode;
		++m_pList->m_nodeCount;
	}
	m_pNext = pNode;
}

//---------------------------------------------------------------------------
// 函数:	Remove the node
// 功能:	删除这个结点
// 返回:	KNode*
//---------------------------------------------------------------------------
void KNode::Remove()
{
	if (m_pList && m_pList->m_pListHead == this)
	{
		m_pList->RemoveHead();
	}
	else if (m_pList && m_pList->m_pListTail == this)
	{
		m_pList->RemoveTail();
	}
	else
	{
		if (m_pList) --m_pList->m_nodeCount;
		if (m_pPrev) m_pPrev->m_pNext = m_pNext;
		if (m_pNext) m_pNext->m_pPrev = m_pPrev;
	}
	m_pPrev = NULL;
	m_pNext = NULL;
	m_pList = NULL;
}

//---------------------------------------------------------------------------
// 函数:	IsLinked
// 功能:	这个节点是否链接
// 返回:	bool
//---------------------------------------------------------------------------
int KNode::IsLinked()
{
	return (m_pList || m_pNext || m_pPrev);
}
//--------------------------------------------------------------------------------
