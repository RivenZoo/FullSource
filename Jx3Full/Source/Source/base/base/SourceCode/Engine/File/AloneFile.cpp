//---------------------------------------------------------------------------
// Sword3 Engine (c) 1999-2005 by Kingsoft
// File:	KAloneFile.cpp
// Date:	2000.08.08
// Code:	WangWei(Daphnis), Wooy
// Desc:	Win32 File Operation Class
//---------------------------------------------------------------------------
#include "Precompile.h"
#include "AloneFile.h"

KRecycleBin<KAloneFile, 4, RBAFM_NEW_DELETE>	KAloneFile::ms_Recycle;
#define CONTENT_BUFFER_NOT_SUPPORT	(m_nContentBufferSize = (unsigned long)(-1))     // 这里是赋值语句？和下面一个相比怎么觉得是比较==;看后面，而且没有IS
#define	IS_CONTENT_BUFFER_SUPPORT	(m_nContentBufferSize != (unsigned long)(-1))

//---------------------------------------------------------------------------
// 功能:	购造函数
//---------------------------------------------------------------------------
KAloneFile::KAloneFile()
{
	m_hFile	= NULL;
	m_pContentBuffer = NULL;
	m_nContentBufferSize = 0;
}

//---------------------------------------------------------------------------
// 功能:	析造函数
//---------------------------------------------------------------------------
KAloneFile::~KAloneFile()
{
	Close();
}

//---------------------------------------------------------------------------
// 功能:	打开一个文件，准备读取写
// 参数:	FileName	文件名
// 返回:	成功返回TRUE，失败返回FALSE。
//---------------------------------------------------------------------------
int	KAloneFile::Open(const char* FileName, int WriteSupport /*= false*/)
{
	//入口参数合法性判断有engine的对外接口函数负责，这里不再处理

	Close();

	char PathName[MAX_PATH];
	g_GetFullPath(PathName, FileName);

	#ifdef __linux
	{
		char *ptr = PathName;
        while(*ptr)
		{
			if (*ptr == '\\')
				*ptr = '/';
			ptr++;
        }
	}
	#endif	// #ifdef __linux

	const char*	pMode = "rb";
	if (WriteSupport)
	{
		if (g_IsFileExist(PathName))
			pMode = "r+b";
		else
			pMode = "a+b";
	}
	m_hFile = fopen(PathName, pMode);

	#ifdef __linux
	{
		if (m_hFile == NULL)
		{
			g_StrLower(PathName);
			m_hFile = fopen(PathName, pMode);
		}
	}
	#endif	// #ifdef __linux

	if (WriteSupport && m_hFile)
		CONTENT_BUFFER_NOT_SUPPORT;

	return (m_hFile != NULL);
}
//---------------------------------------------------------------------------
// 功能:	创建一个文件，准备写入。
// 参数:	FileName	文件名
// 返回:	成功返回TRUE，失败返回FALSE。
//---------------------------------------------------------------------------
int	KAloneFile::Create(const char*  FileName)
{
	//入口参数合法性判断有engine的对外接口函数负责，这里不再处理

	Close();

	char PathName[MAX_PATH];
	g_GetFullPath(PathName, FileName);
	m_hFile = fopen(PathName, "wb+");

	return (m_hFile != NULL);
}

//---------------------------------------------------------------------------
// 功能:	关闭打开的文件
//---------------------------------------------------------------------------
void KAloneFile::Close()
{
	m_nContentBufferSize = 0;
	SAFE_FREE(m_pContentBuffer);
	if (m_hFile)
	{
		fclose(m_hFile);
		m_hFile	= NULL;
	}
}

//---------------------------------------------------------------------------
// 功能:	读取文件数据
// 参数:	Buffer	读取数据存放的内存区域
//			ReadBytes	读取数据的字节数
// 返回:	成功返回读取的字节数，失败返回0。
//---------------------------------------------------------------------------
unsigned long KAloneFile::Read(void* Buffer, unsigned long ReadBytes)
{
	long BytesReaded;
	if (m_hFile)
		BytesReaded = (unsigned long)fread(Buffer, 1, ReadBytes, m_hFile);
	else
		BytesReaded = 0;
	return BytesReaded;
}

//---------------------------------------------------------------------------
// 功能:	写入文件数据
// 参数:	Buffer		写入数据存放的内存区域
//			WriteBytes	写入数据的字节数
// 返回:	成功返回写入的字节数，失败返回0。
//---------------------------------------------------------------------------
unsigned long KAloneFile::Write(const void* Buffer, unsigned long WriteBytes)
{
	unsigned long BytesWrited;
	if (m_hFile)
		BytesWrited = (unsigned long)fwrite(Buffer, 1, WriteBytes, m_hFile);
	else
		BytesWrited = 0;

	return BytesWrited;
}

// 获得文件内容Buffer
void* KAloneFile::GetBuffer()
{
	if (m_pContentBuffer == NULL && m_hFile && IS_CONTENT_BUFFER_SUPPORT == true)
	{
		m_nContentBufferSize = Size();
		if (m_nContentBufferSize)
		{
			m_pContentBuffer = malloc(m_nContentBufferSize);
			if (m_pContentBuffer)
			{
				Seek(0, SEEK_SET);
				if (Read(m_pContentBuffer, m_nContentBufferSize) != m_nContentBufferSize)
				{
					free(m_pContentBuffer);
					m_pContentBuffer = NULL;
				}
			}
		}
	}
	return m_pContentBuffer;
}

//---------------------------------------------------------------------------
// 功能:	移动文件指针位置
// 参数:	Offset		Number of bytes from origin. 
//			Origin		Initial position: SEEK_CUR SEEK_END SEEK_SET
// 返回:	成功返回指针位置，失败返回-1。
//---------------------------------------------------------------------------
long KAloneFile::Seek(long Offset, int Origin)
{
	if (m_hFile)
	{
		fseek(m_hFile, Offset, Origin);
		Offset = ftell(m_hFile);
	}
	else
	{
		Offset = -1;
	}

	return Offset;
}

//---------------------------------------------------------------------------
// 功能:	取得文件指针位置
// 返回:	成功返回指针位置，失败返回-1。
//---------------------------------------------------------------------------
long KAloneFile::Tell()
{
	long Offset;
	if (m_hFile)
		Offset = ftell(m_hFile);
	else
		Offset = -1;
	return Offset;
}

//---------------------------------------------------------------------------
// 功能:	取得文件长度
// 返回:	成功返回文件长度，失败返回0。
//---------------------------------------------------------------------------
unsigned long KAloneFile::Size()
{
	unsigned long Size;
	if (m_pContentBuffer)
	{
		Size = m_nContentBufferSize;
	}
	else if (m_hFile)
	{
		long Offset = ftell(m_hFile);
		fseek(m_hFile, 0, SEEK_END);
		Size = ftell(m_hFile);
		fseek(m_hFile, Offset, SEEK_SET);
//		if (Size == (unsigned long)(-1))
//			Size = 0;
	}
	else
	{
		Size = 0;
	}
	return Size;
}

// 判断打开的是否是包中的文件
int	KAloneFile::IsFileInPak()
{
	return false;
}

void KAloneFile::Release()
{
	Close();
	ms_Recycle.Delete(this);
}

//另外生成一个对象，剥夺走自己的全部数据
KAloneFile* KAloneFile::Deprive()
{
	KAloneFile* pClone = ms_Recycle.New();
	if (pClone)
	{
		*pClone = *this;
		m_hFile	= NULL;
	}
	return pClone;
}

//构造一个空的KAloneFile对象
KAloneFile*	KAloneFile::New()
{
	return ms_Recycle.New();
}

//---------------------------------------------------------------------------
// 功能:	判断是否分块压缩文件

// 返回:	非0值为分块压缩文件
//---------------------------------------------------------------------------
int	KAloneFile::IsPackedByFragment()
{
	return 0;
}

//获取文件分块的数目
int	KAloneFile::GetFragmentCount()
{
	return 0;
}

//获取分块的大小
unsigned int KAloneFile::GetFragmentSize(int nFragmentIndex)
{
	return 0;
}

//读取一个文件分块
unsigned long	KAloneFile::ReadFragment(int nFragmentIndex, void*& pBuffer)
{
	return 0;
}
