//---------------------------------------------------------------------------
//  Engine文件模块-源于打包文件的文件
//	Copyright : Kingsoft Season 2004
//	Author	:   Wooy(Wu yue)
//	CreateTime:	2004-5-18
//---------------------------------------------------------------------------
#ifndef _ENGINE_PAKFILE_H_
#define _ENGINE_PAKFILE_H_

#include "File.h"
#include "./XPackFile.h"


class KPackFile : public IFile
{
public:
	KPackFile();
	virtual ~KPackFile();

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

	// 判断打开的是否是包中的文件,返回布尔值
	int		IsFileInPak();
	//判断文件是否分块压缩的
	int		IsPackedByFragment();
	//获取文件分块的数目
	int		GetFragmentCount();
	//获取分块的大小
	unsigned int	GetFragmentSize(int nFragmentIndex);
	//读取一个文件分块，传入的pBuffer为目标缓冲区，如果传入的缓冲区指针为空，则内部会分配新的缓冲区，并传出指针，外部需要负责销毁。
	//缓冲区的大小需要能容纳下分块的内容，可以通过GetFragmentCount知道每个分块的数据大小，缓冲区必须至少要有这么大。
	//返回值表示实际读取出来的这个分块的数据大小
	unsigned long	ReadFragment(int nFragmentIndex, void*& pBuffer);
	// 关闭打开的文件
	void	Close();
	// 接口对象销毁
	void	Release();
//----IFile街口函数，结束----

public:
	// 打开一个文件，准备读取写,返回布尔值
	int		Open(const char* FileName);
	//另外生成一个对象，剥夺走自己的全部数据
	KPackFile*	Deprive();
	//构造一个空的KPackFile对象
	static KPackFile*	New();

private:
	XPackFile::XPackElemFileRef	m_Core;
	void*						m_pContentBuffer;		// 内容缓冲区
	static KRecycleBin<KPackFile, 4, RBAFM_NEW_DELETE>	ms_Recycle;
};

#endif //ifndef _ENGINE_PAKFILE_H_
