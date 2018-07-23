//#include <iostream>
//#include <string>
#include "DiffPak.h"

//using namespace std;


/**
 *@brief
 *@param
 */
int g_ReadIni(const char* filename, char * packages, int &nCount)
{
	/// 之前需要检查filename
	/// 处理 对于Linux

	FILE *fp;
	char *buffer;	/// buffer for content
	long len;		/// file lenth
	//
	if( (fp = fopen(filename, "r")) == NULL)
	{
		printf("Read file error!\n");
		return -1;
	}

	long Offset = ftell(fp);
	fseek(fp, 0, SEEK_END);
	len = ftell(fp);
	fseek(fp, Offset, SEEK_SET); 
	printf("File len = %d\n", len); /// for tesst

	/// 一次性读取数据
	buffer = (char *)malloc(len + 1);
	if(NULL == buffer)
	{
		printf("Mallco error\n");
		return -1;
	}
	fread(buffer, 1, len, fp);
	fclose(fp);
//	printf("\n%s", buffer);	/// for test

	/// 数据的处理
	char str[1024];	///
	char *pStr = buffer;
	int i = 0, j = 0;
	while(i < len)
	{
		///
		if(*pStr == '\r' && *(pStr++) == '\n')
		{
			pStr += 2;
			i += 2;
			j = 0;
			nCount++;
			printf("%d: %s\n", nCount, str);
		}
		else if(*pStr == '\n')
		{
			pStr += 1;
			i += 1;
			j = 0;
			nCount++;
			printf("%d: %s\n", nCount, str);
		}
		else
			str[j++] = *pStr++;
	}
	
	if(buffer != NULL)
	{
		delete buffer;
		buffer = NULL;
	}
	return 0;
}


static IPackFileShell*	s_pOldShell = NULL;
static IPackFileShell*	s_pNewShell = NULL;

IPackFileShell* LoadPackFile(const char* pPackFile)
{
	IPackFileShell* pShell = CreatePackFileShell();
	if (pShell)
	{
		if (pShell->CreatePack(pPackFile, true, false) < 0)
		{
			pShell->Release();
			pShell = NULL;
		}
	}
	return pShell;
}

/**
 * @brief 
 * @param pList
 * @param pSection
 * @return 
 */
IPackFileShell* LoadPackFileList(const char* pList, const char* pSection)
{
	if (!pList || !pList[0] || !pSection || !pSection[0])
		return NULL;

	KSmartIniFile	list;
	char			szBuffer[64], szKey[16], szFile[MAX_PATH];
	char*			pPakName = NULL;
	strcpy(szFile, pList);
	pPakName = strrchr(szFile, '\\');
	list = g_OpenIniFile(pList, true);
	if (!list || !pPakName)
		return NULL;

	*(++pPakName) = 0;

	IPackFileShell* pShell = CreatePackFileShell();
	if (!pShell)
		return NULL;

	list->GetString(pSection, "Path", "", szBuffer, sizeof(szBuffer));
	if (szBuffer[0])
	{
		strcpy(pPakName, ((szBuffer[0] == '\\') ? (szBuffer + 1) : szBuffer));
		int nLen = (int)strlen(pPakName);
		if (pPakName[nLen - 1] != '\\')
		{
			pPakName[nLen++] = '\\';
			pPakName[nLen] = 0;
		}		
		pPakName += nLen;		
	}
	
	for (int i = 0; ; i++)
	{
		sprintf(szKey, "%d", i);
		if (!list->GetString(pSection, szKey, "", szBuffer, sizeof(szBuffer)))
			break;
		if (szBuffer[0] == 0)
			break;
		strcpy(pPakName, szBuffer);
		if (pShell->CreatePack(szFile, true, false) < 0)
		{
			printf("ERROR : Can't Open pack file [%s]!\n", szFile);
		}
	}
	return pShell;
}

//扫描包文件的回调函数，传入参数表示扫描到的子文件
//返回值如果为非0，则继续扫描，返回值为0则终止扫描。
//参看IPackFileShell::ScanAllPack  IPackFileShell::fnScanPackCallback
int	ScanPackCallback(IPackFileShell::ELEM_FILE_INFO& ElemInfo, void* pParam)
{
	IPackFileShell::ELEM_FILE_INFO	OldInfo;
	if (s_pOldShell->GetElemInfo(ElemInfo.uId, OldInfo))
	{
		if (ElemInfo.uSize == OldInfo.uSize && ElemInfo.uCRC == OldInfo.uCRC && ElemInfo.uCRC)
		{
			return true;		//两子文件相同
		}
	}

	void* pBuffer = malloc(ElemInfo.uStoreSize);
	if (pBuffer == NULL)
	{
		printf("ERROR : Failed to alloc buffer for elem [%s] of size %d!\n", ElemInfo.szFileName, ElemInfo.uStoreSize);
		return false;
	}

	unsigned int uOldPakCRC = 0;
	if (ElemInfo.uSize == OldInfo.uSize &&
		ElemInfo.uStoreSize == OldInfo.uStoreSize &&
		ElemInfo.uCompressFlag == OldInfo.uCompressFlag &&
		(OldInfo.uCRC == 0 || ElemInfo.uCRC == 0))
	{
		if (s_pOldShell->GetElemStoreDataInPak(OldInfo.nPakIndex, OldInfo.nElemIndex, pBuffer, OldInfo.uStoreSize) != OldInfo.uStoreSize)
			goto ERROR_EXIT;
		uOldPakCRC = Misc_CRC32(0, pBuffer, OldInfo.uStoreSize);
	}

	if (s_pNewShell->GetElemStoreDataInPak(ElemInfo.nPakIndex, ElemInfo.nElemIndex, pBuffer, ElemInfo.uStoreSize) != ElemInfo.uStoreSize)
		goto ERROR_EXIT;

	if (ElemInfo.uSize == OldInfo.uSize &&
		ElemInfo.uStoreSize == OldInfo.uStoreSize &&
		ElemInfo.uCompressFlag == OldInfo.uCompressFlag &&
		(OldInfo.uCRC == 0 || ElemInfo.uCRC == 0))
	{
		if (uOldPakCRC == Misc_CRC32(0, pBuffer, OldInfo.uStoreSize))	//打包方式一致，打包后的数据的CRC计算数值一致，被认为两文件内容一致
			goto MATCH_EXIT;
	}

	int nPreIndex = ElemInfo.nPakIndex;
	ElemInfo.nPakIndex = g_nPackIndex;
	if (!g_PackFileShell->AddElemToPak(ElemInfo, pBuffer))
	{
		ElemInfo.nPakIndex = nPreIndex;
		goto ERROR_EXIT;
	}
	ElemInfo.nPakIndex = nPreIndex;

MATCH_EXIT:
	free(pBuffer);
	return true;

ERROR_EXIT:
	free (pBuffer);
	return false;
}

bool DiffOperation(bool bUpdate)
{
	bool bResult = false;
	if (bUpdate)
	{
		s_pOldShell = LoadPackFileList(g_StringTable[OPER_UPDATE_OLD_PACK_LIST], "Package");
		s_pNewShell = LoadPackFileList(g_StringTable[OPER_UPDATE_NEW_PACK_LIST], "Package");
	}
	else
	{
		s_pOldShell = LoadPackFile(g_StringTable[OPER_DIFF_OLD_PACK]);
		s_pNewShell = LoadPackFile(g_StringTable[OPER_DIFF_NEW_PACK]);
	}
	if (!s_pOldShell || !s_pNewShell)
		goto ERROR_EXIT;

	char* pPackName = bUpdate ? g_StringTable[OPER_UPDATE_DIFF_PACK_FILE] : g_StringTable[OPER_DIFF_DIFF_PACK];
	g_nPackIndex = g_PackFileShell->CreatePack(pPackName, false, false);
	if (g_nPackIndex < 0)
	{
		printf("ERROR : Create package [%s] failed!\n", pPackName);
		goto ERROR_EXIT;
	}

	int nCount = 0;
	if (!s_pNewShell->ScanAllPack(ScanPackCallback, 0, nCount))
	{
		printf("ERROR : scanpack has been interrupt!\n");
	}

	printf("SUCCESS : Scaned %d elem-files and packed %d into package [%s].\n", nCount,
		g_PackFileShell->GetElemCountInPak(g_nPackIndex), pPackName);

	bResult = true;

ERROR_EXIT:
	SAFE_RELEASE(s_pOldShell);
	SAFE_RELEASE(s_pNewShell);
	g_PackFileShell->ClosePack(g_nPackIndex);
	g_nPackIndex = -1;
	return bResult;
}
