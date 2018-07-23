//---------------------------------------------------------------------------
//  Engine文件模块-源于打包文件的文件
//	Copyright : Kingsoft Season 2004
//	Author	:   Wooy(Wu yue)
//	CreateTime:	2004-5-18
//---------------------------------------------------------------------------
#include "Precompile.h"
#include "PackFile.h"
#include "XPackList.h"

KRecycleBin<KPackFile, 4, RBAFM_NEW_DELETE>	KPackFile::ms_Recycle;

//---------------------------------------------------------------------------
// 功能:	购造函数
//---------------------------------------------------------------------------
KPackFile::KPackFile()
{
	m_Core.NameId = 0;
	m_Core.CacheIndex = 0;
	m_Core.ElemFileIndex = 0;
	m_Core.PakFileIndex = -1;
	m_Core.Offset = 0;
	m_Core.Size = 0;
	m_pContentBuffer = NULL;
}

//---------------------------------------------------------------------------
// 功能:	析造函数
//---------------------------------------------------------------------------
KPackFile::~KPackFile()
{
	Close();
}

//---------------------------------------------------------------------------
// 功能:	判断此文件是否从包中打开的
//---------------------------------------------------------------------------
// 判断打开的是否是包中的文件
int	KPackFile::IsFileInPak()
{
	return true;
}

//---------------------------------------------------------------------------
// 功能:	打开一个文件, 先寻找当前目录下是否有同名的单独文件,
// 参数:	FileName	文件名
// 返回:	TRUE		成功
//			FALSE		失败
//---------------------------------------------------------------------------
int KPackFile::Open(const char* FileName)
{
	//参数的合法性检查在更外一层做
	Close();
	if (g_EnginePackList.FindElemFile(FileName, m_Core))
		return true;
	Close();
	return false;
}

//---------------------------------------------------------------------------
// 功能:	从文件中读取数据
// 参数:	pBuffer		缓冲区指针
//			dwSize		要读取的长度
// 返回:	读到的字节长度
//---------------------------------------------------------------------------
unsigned long KPackFile::Read(void* Buffer, unsigned long ReadBytes)
{
	if (m_pContentBuffer)
	{
		if (m_Core.Offset < 0)
			m_Core.Offset = 0;
		if ((unsigned long)m_Core.Offset < m_Core.Size)
		{
			if ((unsigned long)(m_Core.Offset + ReadBytes) > m_Core.Size)
				ReadBytes = m_Core.Size - m_Core.Offset;
			memcpy(Buffer, (char*)m_pContentBuffer + m_Core.Offset, ReadBytes);
			m_Core.Offset += ReadBytes;
		}
		else
		{
			m_Core.Offset = m_Core.Size;
		}
		return ReadBytes;
	}

	if (m_Core.NameId)
		return g_EnginePackList.ElemFileRead(m_Core, Buffer, ReadBytes);
	return 0;
}

// 写入文件数据
unsigned long KPackFile::Write(const void* Buffer, unsigned long WriteBytes)
{
	return 0;
}

// 获得文件内容Buffer
void* KPackFile::GetBuffer()
{
	if (m_Core.NameId && m_pContentBuffer == NULL)
		m_pContentBuffer = g_EnginePackList.GetElemFileBuffer(m_Core);
	return m_pContentBuffer;
}

//---------------------------------------------------------------------------
// 功能:	分块读取文件(读取一整块)
// 参数:	pBuffer			目标缓冲区指针
//							如果传入的缓冲区指针为空，则内部会分配新的缓冲区，并传出指针，外部需要负责销毁。
// 返回:	读到的字节长度
//		缓冲区的大小需要能容纳下分块的内容，可以通过GetFragmentCount知道每个分块的数据大小，缓冲区必须至少要有这么大。
//		返回值表示实际读取出来的这个分块的数据大小
//---------------------------------------------------------------------------
unsigned long KPackFile::ReadFragment(int nFragmentIndex, void*& pBuffer)
{
	if (m_Core.NameId && nFragmentIndex >= 0)
		return g_EnginePackList.ElemReadFragment(m_Core, nFragmentIndex, pBuffer);
	return 0;
}

//---------------------------------------------------------------------------
// 功能:	判断是否分块压缩文件

// 返回:	非0值为分块压缩文件
//---------------------------------------------------------------------------
int	KPackFile::IsPackedByFragment()
{
	if (m_Core.NameId)
		return g_EnginePackList.ElemIsPackedByFragment(m_Core);
	return 0;
}

//获取文件分块的数目
int	KPackFile::GetFragmentCount()
{
	if (m_Core.NameId)
		return g_EnginePackList.ElemGetFragmentCount(m_Core);
	return 0;
}

//获取分块的大小
unsigned int KPackFile::GetFragmentSize(int nFragmentIndex)
{
	if (m_Core.NameId && nFragmentIndex >= 0)
		return g_EnginePackList.ElemGetFragmentSize(m_Core, nFragmentIndex);
	return 0;
}

//---------------------------------------------------------------------------
// 功能:	文件读指针定位
// 参数:	Offset		Number of bytes from origin. 
//			Origin		Initial position: SEEK_CUR SEEK_END SEEK_SET
// 返回:	文件的指针
//---------------------------------------------------------------------------
long KPackFile::Seek(long Offset, int Origin)
{
	if (m_Core.NameId)
	{
		if (Origin == SEEK_CUR)
			m_Core.Offset += Offset;
		else if (Origin == SEEK_SET)
			m_Core.Offset = Offset;
		else if (Origin == SEEK_END)
			m_Core.Offset = m_Core.Size + Offset;
		if (m_Core.Offset < 0)
			m_Core.Offset = 0;
		else if ((unsigned long)m_Core.Offset > m_Core.Size)
			m_Core.Offset =  m_Core.Size;
	}
	return m_Core.Offset;
}

//---------------------------------------------------------------------------
// 功能:	返回文件的指针
// 返回:	文件的指针
//---------------------------------------------------------------------------
long KPackFile::Tell()
{
	return m_Core.Offset;
}

//---------------------------------------------------------------------------
// 功能:	返回文件大小
// 返回:	文件的大小 in bytes
//---------------------------------------------------------------------------
unsigned long KPackFile::Size()
{
	return m_Core.Size;
}

//---------------------------------------------------------------------------
// 功能:	关闭一个文件
//---------------------------------------------------------------------------
void KPackFile::Close()
{
	SAFE_FREE(m_pContentBuffer);
	m_Core.NameId = 0;
	m_Core.PakFileIndex = -1;
	m_Core.Offset = 0;
	m_Core.Size = 0;
}

// 接口对象销毁
void KPackFile::Release()
{
	Close();
	ms_Recycle.Delete(this);
}

//另外生成一个对象，剥夺走自己的全部数据
KPackFile*	KPackFile::Deprive()
{
	KPackFile* pClone = ms_Recycle.New();
	if (pClone)
	{
		*pClone = *this;
		m_Core.NameId = 0;
		m_Core.CacheIndex = 0;
		m_Core.ElemFileIndex = 0;
		m_Core.PakFileIndex = -1;
		m_Core.Offset = 0;
		m_Core.Size = 0;
		m_pContentBuffer = NULL;
	}
	return pClone;
}

//构造一个空的KPackFile对象
KPackFile*	KPackFile::New()
{
	return ms_Recycle.New();
}
