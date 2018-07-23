/*****************************************************************************************
//	读取打包文件
//	Copyright : Kingsoft 2003
//	Author	:   Wooy(Wu yue)
//	CreateTime:	2003-9-16
*****************************************************************************************/
#include "Precompile.h"
#include "XPackFile.h"
#include "../Ucl/ucl.h"

XPackFile::XPackElemFileCache	XPackFile::ms_ElemFileCache[MAX_XPACKFILE_CACHE];
int								XPackFile::ms_nNumElemFileCache = 0;
int								XPackFile::ms_HasInitialize = false;
MUTEX_TYPEDEF					XPackFile::ms_ReadCritical;

int	XPackFile::Initialize()
{
	if (ms_HasInitialize == false)
	{
		MUTEX_INIT(ms_ReadCritical);
		ms_HasInitialize = true;
	}
	return ms_HasInitialize;
}

void	XPackFile::Terminate()
{
	if (ms_HasInitialize)
	{
		MUTEX_LOCK(ms_ReadCritical);
		for (int i = 0; i < ms_nNumElemFileCache; i++)
			FreeElemCache(i);
		ms_nNumElemFileCache = 0;
		MUTEX_UNLOCK(ms_ReadCritical);
		MUTEX_DELETE(ms_ReadCritical);
		ms_HasInitialize = false;
	}
}

XPackFile::XPackFile()
{
	m_uFileSize = 0;
	m_pIndexList = NULL;
	m_uElemFileCount = 0;
	m_nSelfIndex = -1;
}

XPackFile::~XPackFile()
{
	Close();
}

//-------------------------------------------------
//功能：打开包文件
//返回：成功与否
//-------------------------------------------------
int XPackFile::Open(const char* pszPackFileName, int nSelfIndex)
{
	if (ms_HasInitialize == false)
		return false;

	bool bResult = false;
	Close();
	MUTEX_LOCK(ms_ReadCritical);
	m_nSelfIndex = nSelfIndex;
	while (m_File.Open(pszPackFileName, false))
	{
		m_uFileSize = m_File.Size();
		if (m_uFileSize <= sizeof(XPackFileHeader))
			break;

		XPackFileHeader	Header;
		unsigned long uListSize;
		//--读取包文件头--
		if (m_File.Read(&Header, sizeof(Header)) != sizeof(Header))
			break;
		//--包文件标记与内容的合法性判断--
		if (*(int*)(&Header.cSignature) != XPACKFILE_SIGNATURE_FLAG ||
			Header.uCount == 0 ||
			Header.uIndexTableOffset < sizeof(XPackFileHeader) ||
			Header.uIndexTableOffset >= m_uFileSize ||
			Header.uDataOffset < sizeof(XPackFileHeader) ||
			Header.uDataOffset >= m_uFileSize)
		{
			break;
		}

		//--读取索引信息表--
		uListSize = sizeof(XPackIndexInfo) * Header.uCount;
		m_pIndexList = (XPackIndexInfo*)malloc(uListSize);
		if (m_pIndexList == NULL ||
			m_File.Seek(Header.uIndexTableOffset, SEEK_SET) != (long)Header.uIndexTableOffset)
		{
			break;
		}
		if (m_File.Read(m_pIndexList, uListSize) != uListSize)
			break;
		m_uElemFileCount = Header.uCount;
		bResult = true;
		break;
	};
	MUTEX_UNLOCK(ms_ReadCritical);
	if (bResult == false)
		Close();
	return bResult;
}

//-------------------------------------------------
//功能：关闭包文件
//-------------------------------------------------
void XPackFile::Close()
{
	if (ms_HasInitialize == false)
		return;

	MUTEX_LOCK(ms_ReadCritical);

	if (m_pIndexList)
	{
		//----清除cache中缓存到的（可能）是此包中的子文件----
		for (int i = ms_nNumElemFileCache - 1; i >=0; i--)
		{
			if (ms_ElemFileCache[i].nPackIndex == m_nSelfIndex)
			{
				FreeElemCache(i);
				ms_nNumElemFileCache --;
				if (i < ms_nNumElemFileCache)
					ms_ElemFileCache[i] = ms_ElemFileCache[ms_nNumElemFileCache];
			}
		}
		free (m_pIndexList);
		m_pIndexList = NULL;
	}
	m_uElemFileCount = 0;
	m_File.Close();
	m_uFileSize = 0;
	m_nSelfIndex = -1;
	MUTEX_UNLOCK(ms_ReadCritical);
}

//-------------------------------------------------
//功能：释放一个cache结点的内容
//返回：成功与否
//-------------------------------------------------
void XPackFile::FreeElemCache(int nCacheIndex)
{
	assert(nCacheIndex >= 0 && nCacheIndex < ms_nNumElemFileCache);
	SAFE_FREE(ms_ElemFileCache[nCacheIndex].pBuffer);
	SAFE_FREE(ms_ElemFileCache[nCacheIndex].pFragmentInfo);
	ms_ElemFileCache[nCacheIndex].uId = 0;
	ms_ElemFileCache[nCacheIndex].lSize = 0;
	ms_ElemFileCache[nCacheIndex].uRefFlag = 0;
	ms_ElemFileCache[nCacheIndex].nPackIndex = -1;
	ms_ElemFileCache[nCacheIndex].nNumFragment = 0;
}

//-------------------------------------------------
//功能：直接读取包文件数据中的数据到缓冲区
//返回：成功与否
//-------------------------------------------------
int	XPackFile::DirectRead(void* pBuffer, unsigned int uOffset, unsigned int uSize)
{
	int bResult = false;
	assert(pBuffer);
	if (uOffset + uSize <= m_uFileSize &&
		m_File.Seek(uOffset, SEEK_SET) == (long)uOffset)
	{
		bResult =  (m_File.Read(pBuffer, uSize) == uSize);
	}
	return bResult;
}

//-------------------------------------------------
//功能：带解压地读取包文件到缓冲区
//参数：pBuffer --> 缓冲区指针
//		uExtractSize  --> 数据（期望）解压后的大小，pBuffer缓冲区的大小不小于此数
//		lCompressType --> 直接从包中度取得原始（/压缩）大小
//		uOffset  --> 从包中的此偏移位置开始读取
//		uSize    --> 从包中直接读取得（压缩）数据的大小
//返回：成功与否
//-------------------------------------------------
int	XPackFile::ExtractRead(void* pBuffer, unsigned int uExtractSize,
						long lCompressType, unsigned int uOffset, unsigned int uSize)
{
	assert(pBuffer);
	int bResult = false;
	if (lCompressType == XPACK_METHOD_NONE)
	{
		if (uExtractSize == uSize)
			bResult = DirectRead(pBuffer, uOffset, uSize);
	}
	else
	{
		void*	pReadBuffer = malloc(uSize);
		if (pReadBuffer)
		{
		    if (lCompressType == XPACK_METHOD_UCL && DirectRead(pReadBuffer, uOffset, uSize))
			{
				unsigned int uDestLength = uExtractSize;
				ucl_nrv2b_decompress_safe_8((unsigned char*)pReadBuffer, uSize, (unsigned char*)pBuffer, &uDestLength, NULL);
				bResult =  (uDestLength == uExtractSize);
			}
			free (pReadBuffer);
		}
	}
	return bResult;
}


//---------------------------------------------------------------------------
// 功能:	分块读取文件
// 参数:	nElemIndex		在包中定位要读取文件的索引
//			Buffer			缓冲区指针
//			ReadBytes		要读取的长度
//			Offset			传进去的值是相对于块文件中的偏移量，之后还要加上块文件相对于包文件头的偏移量 
//			CompressSize	文件压缩的大小，0表示没有压缩，读取方式为直接读取，其他的表示为解压读取
// 返回:	读到的字节长度
//---------------------------------------------------------------------------
unsigned long XPackFile::XElemReadFragment(int nElemIndex, int nFragmentIndex, void*& Buffer)
{
	MUTEX_LOCK(ms_ReadCritical);
	XPackFileFragmentElemHeader	header;
	if (!(m_pIndexList[nElemIndex].uCompressSizeFlag & XPACK_FLAG_FRAGMENT) ||		//不是分块压缩的，不能用XElemReadFragment来读取
		!DirectRead(&header, m_pIndexList[nElemIndex].uOffset, sizeof(header)) ||	//读取头结构
		nFragmentIndex >= header.nNumFragment)	
	{
		MUTEX_UNLOCK(ms_ReadCritical);
		return 0;
	}

	//读取指定数据块的分块信息
	XPackFileFragmentInfo	fragment;
	unsigned int			uOffset = m_pIndexList[nElemIndex].uOffset + header.nFragmentInfoOffest + sizeof(XPackFileFragmentInfo) * nFragmentIndex;
	if (!DirectRead(&fragment,  uOffset, sizeof(XPackFileFragmentInfo)))
	{
		MUTEX_UNLOCK(ms_ReadCritical);
		return 0;
	}
	uOffset = m_pIndexList[nElemIndex].uOffset + fragment.uOffset;

	//如果传入buffer为空，则分配buffer
	if (Buffer == NULL)
	{
		Buffer = malloc(fragment.uSize);
		if (Buffer == NULL)
		{
			MUTEX_UNLOCK(ms_ReadCritical);
			return 0;
		}
	}

	int bOk;
	if ((fragment.uCompressSizeFlag & XPACK_METHOD_FILTER) != XPACK_METHOD_NONE)
	{
		bOk = ExtractRead(Buffer, fragment.uSize, (fragment.uCompressSizeFlag & XPACK_METHOD_FILTER),
					uOffset, (fragment.uCompressSizeFlag & XPACK_COMPRESS_SIZE_FILTER));
	}
	else
	{
		bOk = DirectRead(Buffer, uOffset, fragment.uSize);
	}

	MUTEX_UNLOCK(ms_ReadCritical);
	return (bOk ? fragment.uSize : 0);
}

//---------------------------------------------------------------------------
// 功能:	判断是否分块压缩文件

// 返回:	非0值为分块压缩文件
//---------------------------------------------------------------------------
int	XPackFile::XElemIsPackedByFragment(int nElemIndex)
{
	return ((m_pIndexList[nElemIndex].uCompressSizeFlag & XPACK_FLAG_FRAGMENT) != 0);
}

//获取文件分块的数目
int	XPackFile::XElemGetFragmentCount(int nElemIndex)
{
	if ((m_pIndexList[nElemIndex].uCompressSizeFlag & XPACK_FLAG_FRAGMENT) != 0)
	{
		XPackFileFragmentElemHeader	header;
		if (DirectRead(&header, m_pIndexList[nElemIndex].uOffset, sizeof(header)))
		{
			return header.nNumFragment;
		}
	}
	return 0;
}

//获取某个子文件某个分块的大小
unsigned int XPackFile::ElemGetFragmentSize(int nElemIndex, int nFragmentIndex)
{
	if ((m_pIndexList[nElemIndex].uCompressSizeFlag & XPACK_FLAG_FRAGMENT) != 0)
	{
		MUTEX_LOCK(ms_ReadCritical);
		XPackFileFragmentElemHeader	header;
		XPackFileFragmentInfo		fragment;
		if (DirectRead(&header, m_pIndexList[nElemIndex].uOffset, sizeof(header)) && nFragmentIndex < header.nNumFragment)
		{
			unsigned int uOffset = m_pIndexList[nElemIndex].uOffset + header.nFragmentInfoOffest + sizeof(XPackFileFragmentInfo) * nFragmentIndex;
			//读取指定数据块的分块信息
			if (DirectRead(&fragment,  uOffset, sizeof(XPackFileFragmentInfo)))
			{
				MUTEX_UNLOCK(ms_ReadCritical);
				return fragment.uSize;
			}
		}
		MUTEX_UNLOCK(ms_ReadCritical);
	}
	return 0;
}

//-------------------------------------------------
//功能：在索引表中查找子文件项(二分法找)
//返回：如找到返回在索引表中的位置(>=0)，如未找到返回-1
//-------------------------------------------------
int XPackFile::FindElemFile(unsigned long ulId) const
{
	int nBegin, nEnd, nMid;
	nBegin = 0;
	nEnd = m_uElemFileCount - 1;
	while (nBegin <= nEnd)
	{
		nMid = (nBegin + nEnd) / 2;
		if (ulId < m_pIndexList[nMid].uId)
			nEnd = nMid - 1;
		else if (ulId > m_pIndexList[nMid].uId)
			nBegin = nMid + 1;
		else
			break;
	}
	return ((nBegin <= nEnd) ? nMid : -1);
}

//-------------------------------------------------
//功能：查找包内的子文件
//参数：uId --> 子文件的id
//		ElemRef -->如果找到则在此结构里填上子文件的相关信息
//返回：是否找到
//-------------------------------------------------
int XPackFile::FindElemFile(unsigned int uId, XPackElemFileRef& ElemRef)
{
	int nFound = false;
	if (uId)
	{
		MUTEX_LOCK(ms_ReadCritical);
		ElemRef.CacheIndex = FindElemFileInCache(uId, -1);
		if (ElemRef.CacheIndex >= 0)
		{
			ElemRef.NameId = uId;
			ElemRef.PakFileIndex = ms_ElemFileCache[ElemRef.CacheIndex].nPackIndex;
			ElemRef.ElemFileIndex = ms_ElemFileCache[ElemRef.CacheIndex].nElemIndex;
			ElemRef.Size = ms_ElemFileCache[ElemRef.CacheIndex].lSize;
			ElemRef.Offset = 0;
			nFound = true;
		}
		else
		{
			int nIndex = FindElemFile(uId);
			if (nIndex >= 0)
			{
				nFound = true;
				ElemRef.ElemFileIndex = nIndex;
				ElemRef.NameId = uId;
				ElemRef.PakFileIndex = m_nSelfIndex;
				ElemRef.Size = m_pIndexList[ElemRef.ElemFileIndex].uSize;
				ElemRef.Offset = 0;
			}
		}
		MUTEX_UNLOCK(ms_ReadCritical);
	}
	return nFound;
}

//-------------------------------------------------
//功能：分配缓冲区，并读包内的子文件的内容到其中；对于分块存储文件不立刻读取文件内容
//参数：子文件在包内的索引
//返回：成功则返回缓冲区的指针，否则返回空指针
//-------------------------------------------------
void* XPackFile::ReadElemFile(int nElemIndex)
{
	assert(nElemIndex >= 0 && (unsigned long)nElemIndex < m_uElemFileCount);
	XPackIndexInfo&	info = m_pIndexList[nElemIndex];
	void*	pDataBuffer = malloc(info.uSize);
	if (pDataBuffer)
	{
		if ((info.uCompressSizeFlag & XPACK_FLAG_FRAGMENT) == 0)
		{
			if (ExtractRead(pDataBuffer,
				m_pIndexList[nElemIndex].uSize,
				(m_pIndexList[nElemIndex].uCompressSizeFlag & XPACK_METHOD_FILTER),
				m_pIndexList[nElemIndex].uOffset,
				(m_pIndexList[nElemIndex].uCompressSizeFlag & XPACK_COMPRESS_SIZE_FILTER)) == false)
			{
				free (pDataBuffer);
				pDataBuffer = NULL;
			}
		}
	}
	return pDataBuffer;
}

//-------------------------------------------------
//功能：在cache里查找子文件
//参数：uId --> 子文件id
//		nDesireIndex --> 在cache中的可能位置
//返回：成功则返回cache节点索引(>=0),失败则返回-1
//-------------------------------------------------
int XPackFile::FindElemFileInCache(unsigned int uId, int nDesireIndex)
{
	if (nDesireIndex >= 0 && nDesireIndex < ms_nNumElemFileCache &&
		uId == ms_ElemFileCache[nDesireIndex].uId)
	{
		ms_ElemFileCache[nDesireIndex].uRefFlag = 0xffffffff;
		return nDesireIndex;
	}

	nDesireIndex = -1;
	for (int i = 0; i < ms_nNumElemFileCache; i++)
	{
		if (uId == ms_ElemFileCache[i].uId)
		{
			ms_ElemFileCache[i].uRefFlag = 0xffffffff;
			nDesireIndex = i;
			break;
		}
	}
	return nDesireIndex;
}

//-------------------------------------------------
//功能：把子文件数据添加到cache
//参数：pBuffer --> 存有子文件数据的缓冲区
//		nElemIndex --> 子文件在包中的索引
//返回：添加到cache的索引位置
//-------------------------------------------------
int XPackFile::AddElemFileToCache(void* pBuffer, int nElemIndex)
{
	assert(pBuffer && nElemIndex >= 0 && (unsigned long)nElemIndex < m_uElemFileCount);
	int nCacheIndex;
	if (ms_nNumElemFileCache < MAX_XPACKFILE_CACHE)
	{	//找到一个空位置
		nCacheIndex = ms_nNumElemFileCache++;
	}
	else
	{	//释放一个旧的cache节点
		nCacheIndex = 0;
		if (ms_ElemFileCache[0].uRefFlag)
			ms_ElemFileCache[0].uRefFlag --;
		for (int i = 1; i < MAX_XPACKFILE_CACHE; i++)
		{
			if (ms_ElemFileCache[i].uRefFlag)
				ms_ElemFileCache[i].uRefFlag --;
			if (ms_ElemFileCache[i].uRefFlag < ms_ElemFileCache[nCacheIndex].uRefFlag)
				nCacheIndex = i;

		}
		FreeElemCache(nCacheIndex);
	}

	ms_ElemFileCache[nCacheIndex].pBuffer = pBuffer;
	ms_ElemFileCache[nCacheIndex].uId = m_pIndexList[nElemIndex].uId;
	ms_ElemFileCache[nCacheIndex].lSize = m_pIndexList[nElemIndex].uSize;
	ms_ElemFileCache[nCacheIndex].nPackIndex = m_nSelfIndex;
	ms_ElemFileCache[nCacheIndex].nElemIndex = nElemIndex;
	ms_ElemFileCache[nCacheIndex].uRefFlag = 0xffffffff;
	ms_ElemFileCache[nCacheIndex].nNumFragment = 0;
	ms_ElemFileCache[nCacheIndex].pFragmentInfo = NULL;
	if ((m_pIndexList[nElemIndex].uCompressSizeFlag & XPACK_FLAG_FRAGMENT) == 0)
	{
		return nCacheIndex;
	}

	XPackFileFragmentElemHeader	header;
	if (DirectRead(&header, m_pIndexList[nElemIndex].uOffset, sizeof(header)))
	{
		int nInfoSize = sizeof(XPackFileFragmentInfo) * header.nNumFragment;
		ms_ElemFileCache[nCacheIndex].pFragmentInfo = (XPackFileFragmentInfo*)malloc(nInfoSize);
		if (ms_ElemFileCache[nCacheIndex].pFragmentInfo)
		{
			//读取指定数据块的分块信息
			if (DirectRead(ms_ElemFileCache[nCacheIndex].pFragmentInfo,  m_pIndexList[nElemIndex].uOffset + header.nFragmentInfoOffest, nInfoSize))
			{
				ms_ElemFileCache[nCacheIndex].nNumFragment = header.nNumFragment;
				return nCacheIndex;
			}
		}
	}

	ms_nNumElemFileCache --;
	if (nCacheIndex < ms_nNumElemFileCache)
		ms_ElemFileCache[nCacheIndex] = ms_ElemFileCache[ms_nNumElemFileCache];
	return -1;
}

//-------------------------------------------------
//功能：读取子文件一定长度的数据到缓冲区
//参数：pBuffer --> 用来读取数据的缓冲区
//		uSize --> 要读取的数据的长度
//返回：成功读取得字节数
//-------------------------------------------------
unsigned long XPackFile::ElemFileRead(XPackElemFileRef& ElemRef, void* pBuffer, unsigned long ReadBytes)
{
	unsigned int nResult = 0;
	if (pBuffer && ElemRef.NameId)
	{
		MUTEX_LOCK(ms_ReadCritical);

		//--先看是否已经在cache里了---
		ElemRef.CacheIndex = FindElemFileInCache(ElemRef.NameId, ElemRef.CacheIndex);

		if (ElemRef.CacheIndex < 0 &&								//在cache里未找到
			(unsigned int)ElemRef.ElemFileIndex < m_uElemFileCount &&
			m_pIndexList[ElemRef.ElemFileIndex].uId == ElemRef.NameId)
		{
			void*	pDataBuffer = ReadElemFile(ElemRef.ElemFileIndex);
			if (pDataBuffer)
				ElemRef.CacheIndex = AddElemFileToCache(pDataBuffer, ElemRef.ElemFileIndex);
		}

		if (ElemRef.CacheIndex >= 0 &&
			//此下面三项应该展开检查，防止被模块外部改变，引起错误。
			//为效率可考虑省略，但需外部按照规则不可随便改变ElemRef的内容。
			ElemRef.PakFileIndex == ms_ElemFileCache[ElemRef.CacheIndex].nPackIndex &&
			ElemRef.ElemFileIndex == ms_ElemFileCache[ElemRef.CacheIndex].nElemIndex &&
			ElemRef.Size == ms_ElemFileCache[ElemRef.CacheIndex].lSize
			)
		{
			if (ElemRef.Offset < 0)
				ElemRef.Offset = 0;
			if ((unsigned long)ElemRef.Offset < ElemRef.Size)
			{
				if ((unsigned long)(ElemRef.Offset + ReadBytes) <= ElemRef.Size)
					nResult = ReadBytes;
				else
					nResult = ElemRef.Size - ElemRef.Offset;

				if (ms_ElemFileCache[ElemRef.CacheIndex].nNumFragment == 0)
				{
					memcpy(pBuffer, (char*)ms_ElemFileCache[ElemRef.CacheIndex].pBuffer + ElemRef.Offset, nResult);
					ElemRef.Offset += nResult;
				}
				else if (EnsureElemFlieContent(ElemRef.CacheIndex, ElemRef.Offset, ElemRef.Offset + nResult))
				{
					memcpy(pBuffer, (char*)ms_ElemFileCache[ElemRef.CacheIndex].pBuffer + ElemRef.Offset, nResult);
					ElemRef.Offset += nResult;
				}
				else
				{
					nResult = 0;
				}
			}
			else
			{
				ElemRef.Offset = ElemRef.Size;
			}
		}
		MUTEX_UNLOCK(ms_ReadCritical);
	}
	return nResult;
}

//获得包含包内子文件完整内容的缓冲区
void* XPackFile::GetElemFileBuffer(XPackElemFileRef& ElemRef)
{
	void* pBuffer = NULL;
	if (ElemRef.NameId)
	{
		MUTEX_LOCK(ms_ReadCritical);

		//--先看是否已经在cache里了---
		ElemRef.CacheIndex = FindElemFileInCache(ElemRef.NameId, ElemRef.CacheIndex);

		if (ElemRef.CacheIndex < 0 &&								//在cache里未找到
			(unsigned int)ElemRef.ElemFileIndex < m_uElemFileCount &&
			m_pIndexList[ElemRef.ElemFileIndex].uId == ElemRef.NameId)
		{
			void*	pDataBuffer = ReadElemFile(ElemRef.ElemFileIndex);
			if (pDataBuffer)
				ElemRef.CacheIndex = AddElemFileToCache(pDataBuffer, ElemRef.ElemFileIndex);
		}

		if (ElemRef.CacheIndex >= 0 &&
			//此下面三项应该展开检查，防止被模块外部改变，引起错误。
			//为效率可考虑省略，但需外部按照规则随便改变ElemRef的内容。
			ElemRef.PakFileIndex == ms_ElemFileCache[ElemRef.CacheIndex].nPackIndex &&
			ElemRef.ElemFileIndex == ms_ElemFileCache[ElemRef.CacheIndex].nElemIndex &&
			ElemRef.Size == ms_ElemFileCache[ElemRef.CacheIndex].lSize
			)
		{
			if (ms_ElemFileCache[ElemRef.CacheIndex].nNumFragment == 0)
			{
				pBuffer = ms_ElemFileCache[ElemRef.CacheIndex].pBuffer;
				ms_ElemFileCache[ElemRef.CacheIndex].pBuffer = NULL;
			}
			else if (EnsureElemFlieContent(ElemRef.CacheIndex, 0, ElemRef.Size))
			{
				pBuffer = ms_ElemFileCache[ElemRef.CacheIndex].pBuffer;
				ms_ElemFileCache[ElemRef.CacheIndex].pBuffer = NULL;
			}
			if (ms_ElemFileCache[ElemRef.CacheIndex].pBuffer == NULL)
			{
				FreeElemCache(ElemRef.CacheIndex);
				ms_nNumElemFileCache --;
				if (ElemRef.CacheIndex < ms_nNumElemFileCache)
					ms_ElemFileCache[ElemRef.CacheIndex] = ms_ElemFileCache[ms_nNumElemFileCache];
			}
		}
		MUTEX_UNLOCK(ms_ReadCritical);
	}
	return pBuffer;
}

//加载分块打包文件的全部内容,成功返回非0值，失败返回0值
int	XPackFile::EnsureElemFlieContent(int nCacheIndex, int nStartOffset, int nEndOffset)
{
	assert(nCacheIndex >= 0 && nCacheIndex < MAX_XPACKFILE_CACHE);
	assert(nStartOffset <= nEndOffset);
	XPackElemFileCache&	cache = ms_ElemFileCache[nCacheIndex];
	assert(cache.pBuffer && cache.nNumFragment && cache.pFragmentInfo);
	int	nSize = 0;
	int nResult = true;
	bool bAllFragmentLoaded = true;
	for (int nFragment = 0; nFragment < cache.nNumFragment; nFragment++)
	{
		XPackFileFragmentInfo& frag = cache.pFragmentInfo[nFragment];
		if (frag.uCompressSizeFlag)
		{
			if (nEndOffset > nSize && nStartOffset < (int)(nSize + frag.uSize))
			{
				if (!ExtractRead(((char*)cache.pBuffer) + nSize, frag.uSize,
					(frag.uCompressSizeFlag & XPACK_METHOD_FILTER),
					m_pIndexList[cache.nElemIndex].uOffset + frag.uOffset,
					(frag.uCompressSizeFlag & XPACK_COMPRESS_SIZE_FILTER)))
				{
					nResult = false;
					break;
				}
				cache.pFragmentInfo[nFragment].uCompressSizeFlag = 0;
			}
			else
			{
				bAllFragmentLoaded = false;
				if (nEndOffset <= nSize)
					break;
			}
		}
		nSize += frag.uSize;
	}
	if (nResult && bAllFragmentLoaded)
	{
		SAFE_FREE(cache.pFragmentInfo);
		cache.nNumFragment = 0;
	}
	return nResult;
}
