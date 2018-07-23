//---------------------------------------------------------------------------
// Sword3 Engine (c) 1999-2000 by Kingsoft
//
// File:	KPackList.cpp
// Date:	2000.08.08
// Code:	WangWei(Daphnis)
// Desc:	Pack Data List Class
//---------------------------------------------------------------------------
#include "Precompile.h"
#include "XPackList.h"
#include "FileType.h"
#include "SmartPtr.h"

//---------------------------------------------------------------------------
KPackList g_EnginePackList;

//---------------------------------------------------------------------------
// 功能:	购造函数
//---------------------------------------------------------------------------
KPackList::KPackList()
{
	m_PakNumber = 0;
}

//---------------------------------------------------------------------------
// 功能:	分造函数
//---------------------------------------------------------------------------
KPackList::~KPackList()
{
	Close();
}

//---------------------------------------------------------------------------
// 功能:	关闭所有文件
//---------------------------------------------------------------------------
void KPackList::Close()
{
	for (int i = 0; i < m_PakNumber; i++)
		delete m_PakFilePtrList[i];
	m_PakNumber = 0;

	XPackFile::Terminate();
}

//---------------------------------------------------------------------------
// 功能:	在所有包中扫描指定文件
// 参数:	uId			文件名ID
//			ElemRef		用于存放（传出）文件信息
// 返回:	是否成功找到
//---------------------------------------------------------------------------
int KPackList::FindElemFile(unsigned int uId, XPackFile::XPackElemFileRef& ElemRef)
{
	int nFounded = false;
	for (int i = 0; i < m_PakNumber; i++)
	{
		if (m_PakFilePtrList[i]->FindElemFile(uId, ElemRef))
		{
			nFounded = true;
			break;
		}
	}
	return nFounded;
}

//---------------------------------------------------------------------------
// 功能:	在所有包中扫描指定文件
// 参数:	pszFileName	文件名
//			ElemRef	用于存放（传出）文件信息
// 返回:	是否成功找到
//---------------------------------------------------------------------------
int KPackList::FindElemFile(const char* pszFileName, XPackFile::XPackElemFileRef& ElemRef)
{
	int nFounded = false;
	if (pszFileName && pszFileName[0])
	{
		char szPackName[256];
		#ifdef WIN32
			szPackName[0] = '\\';
		#else
			szPackName[0] = '/';
		#endif
		g_GetPackPath(szPackName + 1, pszFileName);
		unsigned int uId = g_FileNameHash(szPackName);
		nFounded = FindElemFile(uId, ElemRef);
	}
	return nFounded;
}

//--------------------------------------------------------------------
// 功能:	Open package ini file
// 参数:	char* filename
//--------------------------------------------------------------------
int KPackList::Open(const char* pPakListFile, const char* pSection)
{
	Close();

	if (!XPackFile::Initialize())
		return false;

	KSmartIniFile pIni;
	pIni = g_OpenIniFile(pPakListFile, true, false);
	if (pIni == NULL)
		return false;

	char	szBuffer[64], szKey[16], szFile[MAX_PATH];

	if (pIni->GetString(pSection, "Path", "", szBuffer, sizeof(szBuffer)))
		//g_GetFullPath(szFile, szBuffer);
		strcpy(szFile, szBuffer);
	else
		g_GetRootPath(szFile);
	int nNameStartPos = (int)strlen(szFile);

	if (szFile[nNameStartPos - 1] != '\\' || szFile[nNameStartPos - 1] != '/')
	{
		#ifdef WIN32
			szFile[nNameStartPos++] = '\\';
		#else
			szFile[nNameStartPos++] = '/';
		#endif
		szFile[nNameStartPos] = 0;
	}

	for (int i = 0; i < PAK_LIST_MAX_PAK; i++)
	{
		#ifdef WIN32
			itoa(i, szKey, 10);
		#else
			sprintf(szKey, "%d", i);
		#endif
		if (!pIni->GetString(pSection, szKey, "", szBuffer, sizeof(szBuffer)))
			break;
		if (szBuffer[0] == 0)
			break;
		strcpy(szFile + nNameStartPos, szBuffer);
		m_PakFilePtrList[m_PakNumber] = new XPackFile;
		if (m_PakFilePtrList[m_PakNumber])
		{
			if (m_PakFilePtrList[m_PakNumber]->Open(szFile, m_PakNumber))
			{
				m_PakNumber++;
			}
			else
			{
				delete (m_PakFilePtrList[m_PakNumber]);
			}
		}
	}

	return true;
}

//读取包内的子文件
unsigned long KPackList::ElemFileRead(XPackFile::XPackElemFileRef& ElemRef,
					void* pBuffer, unsigned long uSize)
{
	if (ElemRef.PakFileIndex >= 0 && ElemRef.PakFileIndex < m_PakNumber)
		return m_PakFilePtrList[ElemRef.PakFileIndex]->ElemFileRead(ElemRef, pBuffer, uSize);
	return 0;
}


//---------------------------------------------------------------------------
// 功能:	分块读取文件
// 参数:	ElemRef			在包中定位要读取文件的索引
//			Buffer			缓冲区指针
//			ReadBytes		要读取的长度
//			Offset			Number of bytes from origin. 
//			CompressSize	文件压缩的大小，0表示没有压缩，读取方式为直接读取，其他的表示为解压读取
// 返回:	读到的字节长度
//---------------------------------------------------------------------------
unsigned long KPackList::ElemReadFragment(XPackFile::XPackElemFileRef& ElemRef, int nFragmentIndex, void*& Buffer)
{
	return m_PakFilePtrList[ElemRef.PakFileIndex]->XElemReadFragment(ElemRef.ElemFileIndex, nFragmentIndex, Buffer);
}


//---------------------------------------------------------------------------
// 功能:	判断是否分块压缩文件

// 返回:	非0值为分块压缩文件
//---------------------------------------------------------------------------
int KPackList::ElemIsPackedByFragment(XPackFile::XPackElemFileRef& ElemRef)
{
	return m_PakFilePtrList[ElemRef.PakFileIndex]->XElemIsPackedByFragment(ElemRef.ElemFileIndex);
}

//获取文件分块的数目
int	KPackList::ElemGetFragmentCount(XPackFile::XPackElemFileRef& ElemRef)
{
	return m_PakFilePtrList[ElemRef.PakFileIndex]->XElemGetFragmentCount(ElemRef.ElemFileIndex);
}

//获取某个子文件某个分块的大小
unsigned int KPackList::ElemGetFragmentSize(XPackFile::XPackElemFileRef& ElemRef, int nFragmentIndex)
{
	return m_PakFilePtrList[ElemRef.PakFileIndex]->ElemGetFragmentSize(ElemRef.ElemFileIndex, nFragmentIndex);
}

//获得包含包内子文件完整内容的缓冲区
void* KPackList::GetElemFileBuffer(XPackFile::XPackElemFileRef& ElemRef)
{
	if (ElemRef.PakFileIndex >= 0 && ElemRef.PakFileIndex < m_PakNumber)
		return m_PakFilePtrList[ElemRef.PakFileIndex]->GetElemFileBuffer(ElemRef);
	return NULL;
}
