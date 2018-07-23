//---------------------------------------------------------------------------
// Sword3 Engine (c) 1999-2004 by Kingsoft
// File:	KNode.h
// Date:	2000.08.08
// Code:	WangWei(Daphnis)
// Desc:	Header File
//---------------------------------------------------------------------------
#ifndef	_ENGINE_KNODE_H_
#define	_ENGINE_KNODE_H_
//---------------------------------------------------------------------------

#include "Debug.h"

#pragma warning(disable: 4275)
#pragma warning(disable: 4251)

class KList;

class ENGINE_API KNode
{
	friend class KList;
public:
	KNode();
	virtual ~KNode(){};
	KNode*	GetNext() { return m_pNext; }
	KNode*	GetPrev() { return m_pPrev; }
	void	SetNext(KNode* pNext) { m_pNext = pNext; }
	void	SetPrev(KNode* pPre) { m_pPrev = pPre; }
	void	InsertBefore(KNode* pNode);
	void	InsertAfter(KNode* pNode);
	void	Remove();
	int		IsLinked();
private:
	KNode*  m_pNext;
	KNode*  m_pPrev;
	KList*	m_pList;
};

#endif	//_ENGINE_KNODE_H_
