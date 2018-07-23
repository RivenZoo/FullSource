//---------------------------------------------------------------------------
//  回收站
//	Copyright : Kingsoft Season 2004
//	Author	:   Wooy(Wu yue)
//	CreateTime:	2004-5-19
//---------------------------------------------------------------------------
#ifndef _ENGINE_RECYCLE_BIN_H_
#define _ENGINE_RECYCLE_BIN_H_

#include "Mutex.h"

enum	RECYCLEBIN_ALLOCFREE_MANA
{
	RBAFM_MALLOC_FREE = 0,
	RBAFM_NEW_DELETE,
	RBAFM_NEW_RELEASE,
};

template <class RecycleType, int MaxCapacity, RECYCLEBIN_ALLOCFREE_MANA  Mana>
class KRecycleBin
{
public:
	RecycleType*	New();
	void			Delete(RecycleType* item);

	KRecycleBin();
	~KRecycleBin();

private:
	RecycleType*				m_RecyclePool[MaxCapacity];
	RECYCLEBIN_ALLOCFREE_MANA	m_RecycleMana;
};

//构造函数
template <class RecycleType, int MaxCapacity, enum RECYCLEBIN_ALLOCFREE_MANA  Mana>
KRecycleBin<RecycleType, MaxCapacity, Mana>::KRecycleBin()
{
	m_RecycleMana = Mana;
	for (int i = 0; i < MaxCapacity; i++)
	{
		m_RecyclePool[i] = NULL;
	}
}

//释放内存池中的对象
template <class RecycleType, int MaxCapacity, enum RECYCLEBIN_ALLOCFREE_MANA  Mana>
KRecycleBin<RecycleType, MaxCapacity, Mana>::~KRecycleBin()
{
	for (int i = 0; i < MaxCapacity; i++)
	{
		if (m_RecyclePool[i])
		{
			switch(m_RecycleMana)
			{
			case RBAFM_MALLOC_FREE:			
				free(m_RecyclePool[i]);
				m_RecyclePool[i] = NULL;
				break;
			case RBAFM_NEW_DELETE:
				delete (m_RecyclePool[i]);
				m_RecyclePool[i] = NULL;
				break;
			case RBAFM_NEW_RELEASE:
				m_RecyclePool[i]->Release();
				m_RecyclePool[i] = NULL;
				break;
			}
		}
	}
}

//分配对象
template <class RecycleType, int MaxCapacity, enum RECYCLEBIN_ALLOCFREE_MANA  Mana>
RecycleType* KRecycleBin<RecycleType, MaxCapacity, Mana>::New()
{
	RecycleType*	pNewItem = NULL;
	for (int i = 0; i < MaxCapacity; i++)
	{
		if (m_RecyclePool[i])
		{
			pNewItem = (RecycleType*)EngineInterlockedExchange((long*)&m_RecyclePool[i], (long)NULL);
			if (pNewItem)
				break;
		}
	}
	if (pNewItem == NULL)
	{
		if (m_RecycleMana == RBAFM_MALLOC_FREE)
			pNewItem = (RecycleType*)malloc(sizeof(RecycleType));
		else
			pNewItem = new RecycleType;
	}
	return pNewItem;
}

//回收对象
template <class RecycleType, int MaxCapacity, enum RECYCLEBIN_ALLOCFREE_MANA  Mana>
void KRecycleBin<RecycleType, MaxCapacity, Mana>::Delete(RecycleType* item)
{
	if (item == NULL)
		return;
	for (int i = 0; i < MaxCapacity; i++)
	{
		if (m_RecyclePool[i] == NULL)
		{
			item = (RecycleType*)EngineInterlockedExchange((long*)&m_RecyclePool[i], (long)item);
			if (item == NULL)
				break;
		}
	}
	if (item)
	{
		switch(m_RecycleMana)
		{
		case RBAFM_MALLOC_FREE:
			free(item);
			break;
		case RBAFM_NEW_DELETE:
			delete (item);
			break;
		case RBAFM_NEW_RELEASE:
			item->Release();
			break;
		}
	}
}


#endif //ifndef _ENGINE_RECYCLE_BIN_H_

