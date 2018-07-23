//---------------------------------------------------------------------------
// Sword3 Engine (c) 1999-2000 by Kingsoft
// Date:	2000.08.08
// Code:	WangWei(Daphnis)
// Desc:	Header File
//---------------------------------------------------------------------------
#ifndef _ENGINE_MEMBASE_H_
#define _ENGINE_MEMBASE_H_

void	g_MemInfo(void);
void*	g_MemAlloc(unsigned int dwSize);
void	g_MemFree(void* lpMem);
void	g_MemCopy(void* lpDest, void* lpSrc, unsigned int dwLen);
void	g_MemCopyMmx(void* lpDest, void* lpSrc, unsigned int dwLen);
int		g_MemComp(void* lpDest, void* lpSrc, unsigned int dwLen);
void	g_MemFill(void* lpDest, unsigned int dwLen, unsigned char byFill);
void	g_MemFill(void* lpDest, unsigned int dwLen, unsigned short wFill);
void	g_MemFill(void* lpDest, unsigned int dwLen, unsigned int dwFill);
void	g_MemZero(void* lpDest, unsigned int dwLen);
void	g_MemXore(void* lpDest, unsigned int dwLen, unsigned int dwXor);

#endif //_ENGINE_MEMBASE_H_
