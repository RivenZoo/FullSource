/*****************************************************************************************
//	包文件的伴侣文件
//	Copyright : Kingsoft 2005
//	Author	:   Wooy(Wu yue)
//	CreateTime:	2005-3-23
*****************************************************************************************/
#include "Precompile.h"
#include "PackDef.h"
#include "File.h"
#include "SmartPtr.h"
#include "KPackFilePartner.h"
#ifdef __linux
	#include <sys/time.h>
#else
	#include <time.h>
#endif

#define LINE_FORMAT_FIRST	"TotalFile:%d\tPakTime:%d-%d-%d %d:%d:%d\tPakTimeSave:%x\tCRC:%x\r\n"
#define LINE_FORMAT_SECOND	"Index\tID\tTime\tFileName\tSize\tInPakSize\tComprFlag\tCRC\r\n"
#define LINE_FORMAT_OTHERS	"%d\t%x\t%d-%d-%d %d:%d:%d\t%s\t%d\t%d\t%x\t%x\r\n"
#define LINE_FORMAT_OTHERS_HEAD			"%d\t%x\t%d-%d-%d %d:%d:%d"
#define LINE_FORMAT_OTHERS_TAIL			"%d\t%d\t%x\t%x\r\n"
#define VALUE_COUNT_IN_LINE_FIRST		9
#define VALUE_COUNT_IN_LINE_OTHERS_HEAD	8
#define VALUE_COUNT_IN_LINE_OTHERS_TAIL	4

KPackFilePartner::KPackFilePartner()
{
	m_pElemInfoList = NULL;
	m_nElemCount = 0;
	m_uPackTime = 0;
	m_uCRC = 0;
	m_pScanCallback = NULL;
}

KPackFilePartner::~KPackFilePartner()
{
	Clear();
}

//初始化
bool KPackFilePartner::Init()
{
	Clear();
	m_pElemInfoList = (PACKPARTNER_ELEM_INFO*)malloc(sizeof(PACKPARTNER_ELEM_INFO) * IPackFileShell::PACK_FILE_SHELL_MAX_SUPPORT_ELEM_FILE_NUM);
	return (m_pElemInfoList != NULL);
}

//清空数据
void KPackFilePartner::Clear()
{
	SAFE_FREE(m_pElemInfoList);
	m_nElemCount = 0;
	m_uPackTime = 0;
	m_uCRC = 0;
	m_pScanCallback = NULL;
}

//检查打包信息文件是否匹配特定信息
bool KPackFilePartner::IsPartnerMatch(int nElemCount, unsigned int uPackTime, unsigned int uCRC)
{
	return (m_pElemInfoList && m_uPackTime &&
		m_nElemCount == nElemCount && m_uPackTime == uPackTime && m_uCRC == uCRC);
}

//加载打包文件信息
bool KPackFilePartner::Load(const char* pFileName)
{
	if (!Init())
		return false;

	KSmartFile file;
	file = g_OpenFile(pFileName, true, false);
	if (!file)
		return false;
	char* pFileBuffer = (char*)file->GetBuffer();
	if (pFileBuffer == NULL)
		return false;

	int		nSize = file->Size();
	char*	pString = pFileBuffer;
	int		nPos = 0, nLineCount = 0, nTotalCount = 0;
	struct tm FormatTime;
	int		nTempFlag = 0;

	while(nPos < nSize)
	{
		int nLen, nRet;
		char* pEnd = (char*)memchr(pString, '\n', nSize - nPos);
		if (pEnd == NULL)
			pEnd = &pFileBuffer[nSize - 1];
		*pEnd = 0;
		nLen = pEnd - pString;
		if (nLineCount == 0)
		{
			nRet = sscanf(pString, LINE_FORMAT_FIRST, &nTotalCount,
				&FormatTime.tm_year, &FormatTime.tm_mon, &FormatTime.tm_mday,
				&FormatTime.tm_hour, &FormatTime.tm_min, &FormatTime.tm_sec,
				&m_uPackTime, &m_uCRC);
			if (nRet != VALUE_COUNT_IN_LINE_FIRST)	//上面读了9个数据
				break;
		}
		nLineCount++;
		if (nLineCount <= 2)
		{
			pString = pEnd + 1;
			nPos+= nLen + 1;
			continue;
		}

		PACKPARTNER_ELEM_INFO& info = m_pElemInfoList[nLineCount - 3];
		//以为文件名中可能包含空格，所以不能直接用LINE_FORMAT_OTHERS作为格式化字符串来读取！
		//读取文件名之前的数据
		nRet = sscanf(pString, LINE_FORMAT_OTHERS_HEAD,
			&info.nElemIndex, &info.uId, 
			&FormatTime.tm_year, &FormatTime.tm_mon, &FormatTime.tm_mday,
			&FormatTime.tm_hour, &FormatTime.tm_min, &FormatTime.tm_sec);
		if (nRet != VALUE_COUNT_IN_LINE_OTHERS_HEAD || info.nElemIndex != nLineCount - 3)
			break;
		char* pElemName = strchr(pString, '\\');
		if (pElemName)
		{
			char* pElemEnd = strchr(pElemName, '\t');
			if (!pElemEnd)
				break;
			//读取文件名
			memcpy(info.szFileName, pElemName, pElemEnd - pElemName);
			info.szFileName[pElemEnd - pElemName] = 0;
			pString = pElemEnd + 1;
		}
		else
		{
			info.szFileName[0] = 0;
			pString = strrchr(pString, ':');
			if (!pString)
				break;
			pString = strchr(pString + 1, '\t');
			if (!pString)
				break;
			pString = strchr(pString + 1, '\t');
			if (!pString)
				break;
			pString++;
		}
		//读取文件名之后的部分		
		nRet = sscanf(pString, LINE_FORMAT_OTHERS_TAIL,
            &info.uSize, &info.uStoreSizeAndCompressFlag,
			&nTempFlag, &info.uCRC);
		if (nRet != VALUE_COUNT_IN_LINE_OTHERS_TAIL)
			break;
		info.uStoreSizeAndCompressFlag |= (nTempFlag << XPACK_COMPRESS_SIZE_BIT);
		FormatTime.tm_year -= 1900;
		FormatTime.tm_mon--;
		info.uTime = (unsigned int)mktime(&FormatTime);
		if (info.uTime == (unsigned int)(-1))
			info.uTime = 0;
		pString = pEnd + 1;
		nPos+= nLen + 1;
		m_nElemCount++;
	}

	return (m_nElemCount == nTotalCount);
}

//保存打包文件信息
bool KPackFilePartner::Save(const char* pFileName, unsigned int uPackTime, unsigned int uPackCRC)
{
	int nResult  = false;

    m_uPackTime = uPackTime;
	m_uCRC = uPackCRC;

	KSmartFile	file;
	file = g_CreateFile(pFileName);
	if (!file)
		return false;

#define	MAX_BUFF_SIZE	10240
	int			nElemIndex;
	struct tm*	pFormatTime = NULL;
	struct tm	t = { 0 };
	char		line[MAX_BUFF_SIZE + 512];
	int			nPos = 0;

	pFormatTime = localtime((time_t *)&uPackTime);
	if (pFormatTime == NULL)
		pFormatTime = &t;

	nPos += sprintf((line + nPos), LINE_FORMAT_FIRST, m_nElemCount,
		pFormatTime->tm_year + 1900, pFormatTime->tm_mon + 1,	pFormatTime->tm_mday,
		pFormatTime->tm_hour, pFormatTime->tm_min, pFormatTime->tm_sec,
		m_uPackTime, m_uCRC);
	nPos += sprintf((line + nPos), LINE_FORMAT_SECOND);

	bool bResult = true;

	for (nElemIndex = 0; nElemIndex < m_nElemCount; ++nElemIndex)
	{
		PACKPARTNER_ELEM_INFO& info = m_pElemInfoList[nElemIndex];
        pFormatTime = localtime((time_t *)(&info.uTime));
		if (pFormatTime == NULL)
			pFormatTime = &t;
		nPos += sprintf((line + nPos), LINE_FORMAT_OTHERS,
			info.nElemIndex, info.uId, 
			pFormatTime->tm_year + 1900, pFormatTime->tm_mon + 1,	pFormatTime->tm_mday,
			pFormatTime->tm_hour, pFormatTime->tm_min, pFormatTime->tm_sec,
			info.szFileName,
			info.uSize, (info.uStoreSizeAndCompressFlag & XPACK_COMPRESS_SIZE_FILTER),
			(info.uStoreSizeAndCompressFlag >> XPACK_COMPRESS_SIZE_BIT), info.uCRC);
		if (nPos >= MAX_BUFF_SIZE)
		{
			if (file->Write(line, nPos) != nPos)
			{
				nPos = 0;
				bResult = false;
				break;
			}
			nPos = 0;
		}
	}

	if (nPos > 0)
	{
		if (file->Write(line, nPos) != nPos)
			bResult = false;
	}

	file->Close();
	return bResult;
}

//往打包文件中添加一个子文件
bool KPackFilePartner::AddElem(PACKPARTNER_ELEM_INFO& ElemInfo)
{
	if (m_pElemInfoList == NULL || m_nElemCount == IPackFileShell::PACK_FILE_SHELL_MAX_SUPPORT_ELEM_FILE_NUM ||
		ElemInfo.nElemIndex < 0 || ElemInfo.nElemIndex > m_nElemCount)
		return false;

	if (ElemInfo.nElemIndex > 0)	//检查前一个，防止意外
	{
		if (m_pElemInfoList[ElemInfo.nElemIndex - 1].uId >= ElemInfo.uId)
			return false;
	}
	if (ElemInfo.nElemIndex < m_nElemCount)	//检查后一个，防止意外
	{
		if (m_pElemInfoList[ElemInfo.nElemIndex].uId < ElemInfo.uId)
			return false;
		if (m_pElemInfoList[ElemInfo.nElemIndex].uId > ElemInfo.uId)
		{
			for (int i = m_nElemCount; i > ElemInfo.nElemIndex; --i)
			{
				m_pElemInfoList[i] = m_pElemInfoList[i - 1];
				m_pElemInfoList[i].nElemIndex = i;
			}
			++m_nElemCount;
		}
	}
	else
	{
		++m_nElemCount;
	}
	m_pElemInfoList[ElemInfo.nElemIndex] = ElemInfo;
	return true;
}

//删除打包文件中的一个子文件
bool KPackFilePartner::DeleteElemInPak(unsigned int uElemID)
{
	unsigned int uIndex;
	if (!FindElem(uElemID, uIndex))
		return false;

	--m_nElemCount;
	for (uIndex; uIndex < (unsigned int)m_nElemCount ; ++uIndex)
	{
		m_pElemInfoList[uIndex] = m_pElemInfoList[uIndex + 1];
	}

	return true;
}

//查找子文件项
bool KPackFilePartner::FindElem(unsigned int uElemId, unsigned int& uIndex)
{
	if (m_pElemInfoList == NULL)
		return false;
    int nBegin, nEnd, nMid;
    nBegin = 0;
    nEnd = m_nElemCount - 1;
    while (nBegin <= nEnd)
    {
        nMid = (nBegin + nEnd) / 2;
        if (uElemId < m_pElemInfoList[nMid].uId)
        {
            nEnd = nMid - 1;
        }
        else if (uElemId > m_pElemInfoList[nMid].uId)
        {
            nBegin = nMid + 1;
        }
        else
        {
            uIndex = nMid;
            return true;
        }
    }

    if (nBegin == nEnd)
        uIndex = (uElemId < m_pElemInfoList[nMid].uId) ? nMid : (nMid + 1);
    else
        uIndex = nBegin;
	return false;
}

//获取子文件信息
bool KPackFilePartner::GetElemInfo(unsigned int uElemId, PACKPARTNER_ELEM_INFO& info)
{
    unsigned int uIndex;
    if (!FindElem(uElemId, uIndex))
		return false;
	info = m_pElemInfoList[uIndex];
	return true;
}

//扫描整个包文件集合，对于每个子文件给出进行一次回调函数操作
//参数pFileNamePrefix表示遍历到的子文件名的前缀必须与此给定的字符串完全一致（不区分大小写），前缀不符的子文件将被略过，传入空指针表示无前缀限制。
//返回值表示多少个满足条件的子文件被扫描到
//int	 KPackFilePartner::ScanAllPack(IPackFileShell::fnScanPackCallback pCallback, const char* pFileNamePrefix)
//{
//	return false;
//}

