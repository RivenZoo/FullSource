//---------------------------------------------------------------------------
// Sword3 Engine (c) 1999-2004 by Kingsoft
// File:	KMemBase.cpp
// Date:	2000.08.08
// Code:	WangWei(Daphnis)
// Desc:	Memory base functions
//---------------------------------------------------------------------------
#include "Precompile.h"
#include "KNode.h"
#include "KList.h"
#include <new>

//---------------------------------------------------------------------------
class KMemNode : public KNode
{
public:
	unsigned int	m_dwMemSize;//内存大小
	unsigned int	m_dwMemSign;//内存标志
};
//---------------------------------------------------------------------------
class KMemList : public KList
{
public:
	~KMemList()
	{
		KMemNode* pNode = (KMemNode*)GetHead();
		while (pNode)
		{
			g_DebugLog("KMemList::Leak Detected, Size = %d", pNode->m_dwMemSize);
			pNode = (KMemNode*)pNode->GetNext();
		}
	};
	void ShowUsage()
	{
		KMemNode* pNode = (KMemNode*)GetHead();
		unsigned int dwMemSize = 0;
		while (pNode)
		{
			dwMemSize += pNode->m_dwMemSize;
			pNode = (KMemNode*)pNode->GetNext();
		}
		g_DebugLog("Memory Usage Size = %d KB", dwMemSize / 1024);
	}
};
static KMemList m_MemList;
//---------------------------------------------------------------------------
#define MEMSIGN 1234567890
//---------------------------------------------------------------------------
// 函数:	g_MemInfo
// 功能:	Memory Infomation
// 参数:	void
// 返回:	void
//---------------------------------------------------------------------------
void g_MemInfo()
{
//	MEMORYSTATUS stat;
	
//	GlobalMemoryStatus(&stat);
	
//	g_DebugLog("Total Physical Memory = %d MB", stat.dwTotalPhys >> 20);
//	g_DebugLog("Total Virtual Memory = %d MB", stat.dwTotalVirtual >> 20);
//	g_DebugLog("%d percent of memory is in use.", stat.dwMemoryLoad);
}
//---------------------------------------------------------------------------
// 函数:	g_MemAlloc
// 功能:	分配内存
// 参数:	dwSize		内存块大小
// 返回:	lpMem (lpMem = NULL 表示分配失败)
//---------------------------------------------------------------------------
void* g_MemAlloc(unsigned int dwSize)
{
//	HANDLE hHeap = GetProcessHeap();
	unsigned char*  lpMem = NULL;
	unsigned int  dwHeapSize = dwSize + sizeof(KMemNode);

//	lpMem = (unsigned char*)HeapAlloc(hHeap, 0, dwHeapSize);
	lpMem = (unsigned char*)malloc(dwHeapSize);
	if (NULL == lpMem)
	{
		g_MessageBox("g_MemAlloc() Failed, Size = %d", dwSize);
		return NULL;
	}

	KMemNode* pNode = (KMemNode*)lpMem;
	new (pNode) KMemNode();
	pNode->m_dwMemSize = dwSize;
	pNode->m_dwMemSign = MEMSIGN;
	m_MemList.AddHead(pNode);
	
	return (lpMem + sizeof(KMemNode));
}
//---------------------------------------------------------------------------
// 函数:	g_MemFree
// 功能:	释放内存
// 参数:	lpMem		要释放的内存指针
// 返回:	void
//---------------------------------------------------------------------------
void g_MemFree(void* lpMem)
{
//	HANDLE hHeap = GetProcessHeap();
	if (lpMem == NULL)
		return;
	lpMem = (unsigned char*)lpMem - sizeof(KMemNode);
	KMemNode* pNode = (KMemNode *)lpMem;
	if (pNode->m_dwMemSign != MEMSIGN)
	{
		g_MessageBox("g_MemFree() Failed, Size = %d", pNode->m_dwMemSize);
		return;
	}
	pNode->Remove();
//	HeapFree(hHeap, 0, lpMem);
	free(lpMem);
}
//---------------------------------------------------------------------------
// 函数:	MemoryCopy
// 功能:	内存拷贝
// 参数:	lpDest	:	目标内存块
//			lpSrc	:	源内存块
//			dwLen	:	拷贝长度
// 返回:	void
//---------------------------------------------------------------------------
void g_MemCopy(void* lpDest, void* lpSrc, unsigned int dwLen)
{	
#ifdef WIN32
	__asm
	{
		mov		edi, lpDest
		mov		esi, lpSrc
		mov		ecx, dwLen
		mov     ebx, ecx
		shr     ecx, 2
		rep     movsd
		mov     ecx, ebx
		and     ecx, 3
		rep     movsb
	}
#else
     memcpy(lpDest, lpSrc, dwLen);
#endif
}
//---------------------------------------------------------------------------
// 函数:	MemoryCopyMmx
// 功能:	内存拷贝（MMX版本）
// 参数:	lpDest	:	目标内存块
//			lpSrc	:	源内存块
//			dwLen	:	拷贝长度
// 返回:	void
//---------------------------------------------------------------------------
void g_MemCopyMmx(void* lpDest, void* lpSrc, unsigned int dwLen)
{
#ifdef WIN32
	__asm
	{
		mov		edi, lpDest
		mov		esi, lpSrc
		mov		ecx, dwLen
		mov     ebx, ecx
		shr     ecx, 3
		jcxz	loc_copy_mmx2

loc_copy_mmx1:

		movq	mm0, [esi]
		add		esi, 8
		movq	[edi], mm0
		add		edi, 8
		dec		ecx
		jnz		loc_copy_mmx1

loc_copy_mmx2:

		mov     ecx, ebx
		and     ecx, 7
		rep     movsb
		emms
	}
#else
     memcpy(lpDest, lpSrc, dwLen);
#endif
}
//---------------------------------------------------------------------------
// 函数:	MemoryComp
// 功能:	内存比较
// 参数:	lpDest	:	内存块1
//			lpSrc	:	内存块2
//			dwLen	:	比较长度
// 返回:	true	:	相同
//			false	:	不同	
//---------------------------------------------------------------------------
int g_MemComp(void* lpDest, void* lpSrc, unsigned int dwLen)
{	
#ifdef WIN32
	__asm
	{
		mov		edi, lpDest
		mov		esi, lpSrc
		mov		ecx, dwLen
		mov     ebx, ecx
		shr     ecx, 2
		rep     cmpsd
		jne		loc_not_equal
		mov     ecx, ebx
		and     ecx, 3
		rep     cmpsb
		jne		loc_not_equal
	};
	return true;

loc_not_equal:

	return false;
#else
     return (0 == memcmp(lpDest, lpSrc, dwLen));
#endif
}
//---------------------------------------------------------------------------
// 函数:	MemoryFill
// 功能:	内存填充
// 参数:	lpDest	:	内存地址
//			dwLen	:	内存长度
//			byFill	:	填充字节
// 返回:	void
//---------------------------------------------------------------------------
void g_MemFill(void* lpDest, unsigned int dwLen, unsigned char byFill)
{
#ifdef WIN32
	__asm
	{
		mov		edi, lpDest
		mov		ecx, dwLen
		mov		al, byFill
		mov		ah, al
		mov		bx, ax
		shl		eax, 16
		mov		ax, bx
		mov		ebx, ecx
		shr		ecx, 2
		rep     stosd
		mov     ecx, ebx
		and		ecx, 3
		rep     stosb
	}
#else
     memset(lpDest, byFill, dwLen);
#endif
}
//---------------------------------------------------------------------------
// 函数:	MemoryFill
// 功能:	内存填充
// 参数:	lpDest	:	内存地址
//			dwLen	:	内存长度
//			wFill	:	填充字
// 返回:	void
//---------------------------------------------------------------------------
void g_MemFill(void* lpDest, unsigned int dwLen, unsigned short wFill)
{	
#ifdef WIN32
	__asm
	{
		mov		edi, lpDest
		mov		ecx, dwLen
		mov		ax, wFill
		mov		bx, ax
		shl		eax, 16
		mov		ax, bx
		mov		ebx, ecx
		shr		ecx, 1
		rep     stosd
		mov     ecx, ebx
		and		ecx, 1
		rep     stosw
	}
#else
     memset(lpDest, wFill & 0xff, dwLen);
#endif
}
//---------------------------------------------------------------------------
// 函数:	MemoryFill
// 功能:	内存填充
// 参数:	lpDest	:	内存地址
//			dwLen	:	内存长度
//			dwFill	:	填充字
// 返回:	void
//---------------------------------------------------------------------------
void g_MemFill(void* lpDest, unsigned int dwLen, unsigned int dwFill)
{	
#ifdef WIN32
	__asm
	{
		mov		edi, lpDest
		mov		ecx, dwLen
		mov		eax, dwFill
		rep     stosd
	}
#else
     memset(lpDest, dwFill & 0xff, dwLen);
#endif
}
//---------------------------------------------------------------------------
// 函数:	MemoryZero
// 功能:	内存清零
// 参数:	lpDest	:	内存地址
//			dwLen	:	内存长度
// 返回:	void
//---------------------------------------------------------------------------
void g_MemZero(void* lpDest, unsigned int dwLen)
{
#ifdef WIN32
	__asm
	{
		mov		ecx, dwLen
		mov		edi, lpDest
		xor     eax, eax
		mov		ebx, ecx
		shr		ecx, 2
		rep     stosd
		mov     ecx, ebx
		and		ecx, 3
		rep     stosb
	}
#else
     memset(lpDest, 0, dwLen);
#endif
}
//---------------------------------------------------------------------------
// 函数:	MemoryXore
// 功能:	内存异或
// 参数:	lpDest	:	内存地址
//			dwLen	:	内存长度
//			dwXor	:	异或字节
// 返回:	void
//---------------------------------------------------------------------------
void g_MemXore(void* lpDest, unsigned int dwLen, unsigned int dwXor)
{
#ifdef WIN32
	__asm
	{
		mov		edi, lpDest
		mov		ecx, dwLen
		mov		eax, dwXor
		shr		ecx, 2
		cmp		ecx, 0
		jle		loc_xor_exit
loc_xor_loop:
		xor		[edi], eax
		add		edi, 4
		dec		ecx
		jnz		loc_xor_loop
loc_xor_exit:
	}
#else
     unsigned long *ptr = (unsigned long *)lpDest;
     while((long)dwLen > 0) {
       *ptr++ ^= dwXor;
       dwLen -= sizeof(unsigned long);
     }
#endif
}

