//---------------------------------------------------------------------------
// Sword3 Engine (c) 1999-2004 by Kingsoft
//
// File:	KPackList.h
// Date:	2000.08.08
// Code:	WangWei(Daphnis),Wuyue(Wooy)
// Desc:	Header File
// Modify:	Wooy(2003-9-17)
//---------------------------------------------------------------------------
#ifndef _ENGINE_XPAKLIST_H_
#define _ENGINE_XPAKLIST_H_

#include "XPackFile.h"
//---------------------------------------------------------------------------

class KPackList
{
public:
	KPackList();
	~KPackList();
	//加载打包文件，返回布尔值
	int			Open(const char* pPakListFile, const char* pSection);
	void		Close();                                       
	//查找包内的子文件
	int			FindElemFile(unsigned int uId, XPackFile::XPackElemFileRef& ElemRef);
	//查找包内的子文件
	int			FindElemFile(const char* pszFileName, XPackFile::XPackElemFileRef& ElemRef);
	//读取包内的子文件
	unsigned long	ElemFileRead(XPackFile::XPackElemFileRef& ElemRef, void* pBuffer, unsigned long uSize);

	//读取分块文件包内的数据，CompressSize = 0表示不解压直接读取
	unsigned long	ElemReadFragment(XPackFile::XPackElemFileRef& ElemRef, int nFragmentIndex, void*& Buffer);
	//判断文件是否分块压缩的
	int				ElemIsPackedByFragment(XPackFile::XPackElemFileRef& ElemRef);
	//获取文件分块的数目
	int				ElemGetFragmentCount(XPackFile::XPackElemFileRef& ElemRef);
	//获取某个子文件某个分块的大小
	unsigned int	ElemGetFragmentSize(XPackFile::XPackElemFileRef& ElemRef, int nFragmentIndex);
	//获得包含包内子文件完整内容的缓冲区
	void*			GetElemFileBuffer(XPackFile::XPackElemFileRef& ElemRef);

private:
	enum	PACK_LIST_PARAM
	{
		PAK_LIST_MAX_PAK = 32,
	};
	XPackFile*			m_PakFilePtrList[PAK_LIST_MAX_PAK];
	long				m_PakNumber;

};

extern KPackList g_EnginePackList;

#endif //ifndef _ENGINE_XPAKLIST_H_
