//---------------------------------------------------------------------------
// Sword3 Engine (c) 1999-2004 by Kingsoft
// File:	KAloneFile.h
// Date:	2000.08.08
// Code:	wooy
// Desc:	Header File
//---------------------------------------------------------------------------
#ifndef _ENGINE_ALONE_FILE_H_
#define _ENGINE_ALONE_FILE_H_

#include "File.h"
#include "RecycleBin.h"

class KAloneFile : public IFile
{
public:
	KAloneFile();
	virtual ~KAloneFile();
//----IFile街口函数，开始----
	// 读取文件数据
	unsigned long	Read(void* Buffer, unsigned long ReadBytes);
	// 写入文件数据
	unsigned long	Write(const void* Buffer, unsigned long WriteBytes);
	// 获得文件内容Buffer
	void*			GetBuffer();
	// 移动文件指针位置，Origin	-> Initial position: SEEK_CUR SEEK_END SEEK_SET
	long	Seek(long Offset, int Origin);
	// 取得文件指针位置,失败返回-1。
	long	Tell();
	// 取得文件长度,失败返回0。
	unsigned long	Size();

	// 判断打开的是否是包中的文件
	int		IsFileInPak();
	//判断文件是否分块压缩的
	int		IsPackedByFragment();
	//获取文件分块的数目
	int		GetFragmentCount();
	//获取分块的大小
	unsigned int	GetFragmentSize(int nFragmentIndex);
	//读取一个文件分块
	unsigned long	ReadFragment(int nFragmentIndex, void*& pBuffer);

	// 关闭打开的文件
	void	Close();
	// 接口对象销毁
	void	Release();
//----IFile街口函数，结束----

public:
	// 打开一个文件，准备读取写
	int		Open(const char* FileName, int WriteSupport = false);
	// 创建一个文件，准备写入。
	int		Create(const char*  FileName);
	//另外生成一个对象，剥夺走自己的全部数据
	KAloneFile*	Deprive();
	//构造一个空的KAloneFile对象
	static KAloneFile*	New();

private:
	FILE*			m_hFile;				// 文件对象句柄
	void*			m_pContentBuffer;		// 内容缓冲区
	unsigned long	m_nContentBufferSize;	// 内容缓冲区大小
	static KRecycleBin<KAloneFile, 4, RBAFM_NEW_DELETE>	ms_Recycle;
};


#endif //#ifndef _ENGINE_ALONE_FILE_H_

