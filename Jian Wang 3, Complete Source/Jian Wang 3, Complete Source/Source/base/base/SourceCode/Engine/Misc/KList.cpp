#include "Precompile.h"
#include "KList.h"
//---------------------------------------------------------------------------
// 函数:	KList
// 功能:	构造
KList::KList()
{
	m_nodeCount = 0;
	m_pListHead = NULL;
	m_pListTail = NULL;
}

//-------------------------------------------------------------------------
// 函数:	IsEmpty
// 功能:	是否为空
// 返回:	int
int KList::IsEmpty()
{
	return m_pListHead == NULL;
}

//-------------------------------------------------------------------------
// 函数:	AddHead
// 功能:	在头部增加一个节点
// 参数:	KNode*
// 返回:	int
//---------------------------------------------------------------------------
void KList::AddHead(KNode *pNode)
{
	KASSERT(pNode && !pNode->IsLinked());
	if (m_pListHead)
	{
		m_pListHead->m_pPrev = pNode;
	}
	pNode->m_pList = this;
	pNode->m_pPrev = NULL;
	pNode->m_pNext = m_pListHead;
	m_pListHead = pNode;

	if (!m_pListTail)
	{
		m_pListTail = pNode;
	}
	++m_nodeCount;
}

//-------------------------------------------------------------------------
// 函数:	AddTail
// 功能:	在末尾增加一个节点
// 参数:	KNode*
//---------------------------------------------------------------------------
void KList::AddTail(KNode *pNode)
{
	KASSERT(pNode && !pNode->IsLinked());
	if (m_pListTail)
	{
		m_pListTail->m_pNext = pNode;
	}
	pNode->m_pList = this;
	pNode->m_pPrev = m_pListTail;
	pNode->m_pNext = NULL;
	m_pListTail = pNode;

	if (!m_pListHead)
	{
		m_pListHead = pNode;
	}
	++m_nodeCount;
}

//-------------------------------------------------------------------------
// 函数:	RemoveHead
// 功能:	删除第一个节点
// 返回:	KNode*
//---------------------------------------------------------------------------
KNode* KList::RemoveHead()
{
	KNode* pRetNode = m_pListHead;
	if (m_pListHead && (m_pListHead == m_pListTail))
	{
		m_pListHead = m_pListTail = NULL;
		--m_nodeCount;
	}
	else if (m_pListHead)
	{
		m_pListHead = m_pListHead->GetNext();
		m_pListHead->m_pPrev = NULL;
		--m_nodeCount;
	}
	if (pRetNode)
	{
		pRetNode->m_pList = NULL;
		pRetNode->m_pNext = NULL;
		pRetNode->m_pPrev = NULL;
	}
	return pRetNode;
}

//-------------------------------------------------------------------------
// 函数:	RemoveTail
// 功能:	删除最后一个节点
// 返回:	KNode*
//---------------------------------------------------------------------------
KNode* KList::RemoveTail()
{
	KNode* pRetNode = m_pListTail;
	if (m_pListTail && (m_pListHead == m_pListTail))
	{
		m_pListHead = m_pListTail = NULL;
		--m_nodeCount;
	}
	else if (m_pListTail)
	{
		m_pListTail = m_pListTail->GetPrev();
		m_pListTail->m_pNext = NULL;
		--m_nodeCount;
	}
	if (pRetNode)
	{
		pRetNode->m_pList = NULL;
		pRetNode->m_pNext = NULL;
		pRetNode->m_pPrev = NULL;
	}
	return pRetNode;
}

//-------------------------------------------------------------------------
// 函数:	GetNodeCount
// 功能:	取得节点个数
// 返回:	long
//---------------------------------------------------------------------------
long KList::GetNodeCount()
{
	return m_nodeCount;
}
//-------------------------------------------------------------------------
