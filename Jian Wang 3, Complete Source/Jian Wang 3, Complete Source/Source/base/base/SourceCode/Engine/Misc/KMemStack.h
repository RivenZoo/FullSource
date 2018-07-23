//---------------------------------------------------------------------------
// Sword3 Engine (c) 1999-2004 by Kingsoft
// File:	KMemStack.h
// Date:	2000.08.08
// Code:	WangWei(Daphnis)
//---------------------------------------------------------------------------
#ifndef _ENGINE_MEMSTACK_H_
#define _ENGINE_MEMSTACK_H_

class KMemStack
{
private:
	#define MAX_CHUNK	10
	unsigned char*		m_pStack[MAX_CHUNK];
	int			m_nStackTop;
	int 		m_nStackEnd;
	int			m_nChunkTop;
	int			m_nChunkSize;
public:
	KMemStack();
	~KMemStack();
	void		Init(int nChunkSize = 65536);
	void*		Push(int nSize);
	void		Free(void* pMem);
	int			AllocNewChunk();//·µ»Ø²¼¶ûÖµ
	void		FreeAllChunks();
	int			GetChunkSize();
	int			GetStackSize();
};

#endif	//_ENGINE_MEMSTACK_H_
