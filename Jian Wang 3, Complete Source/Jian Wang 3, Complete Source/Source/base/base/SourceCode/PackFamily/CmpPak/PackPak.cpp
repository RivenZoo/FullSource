#include "PackFile.h"

static IPackFileShell*	s_pAddShell = NULL;

int	AddFileToPakFilter(const char* pFileName)
{
	if (pFileName)
	{
		const char* pExt = strrchr(pFileName, '.');
		return (strcmp(pExt + 1, "scc"));	//过滤SourceSafe信息文件
	}
	return false;
}

bool PackOperation()
{
	g_PackFileShell->SetElemFileRootPath(g_StringTable[OPER_PACK_ELEM_ROOT_PATH]);
	g_nPackIndex = g_PackFileShell->CreatePack(g_StringTable[OPER_PACK_PACKFILE_NAME], false, false);
	if (g_nPackIndex < 0)
	{
		printf("ERROR : Create package [%s] failed!\n", g_StringTable[OPER_PACK_PACKFILE_NAME]);
		return false;
	}

	if (g_StringTable[OPER_PACK_FOLDER_TO_ADD][0])
	{	//====把此整个目录内容都加入打包文件====
		if (!g_PackFileShell->AddFolderToPak(g_nPackIndex, g_StringTable[OPER_PACK_FOLDER_TO_ADD], AddFileToPakFilter))
		{
			printf("ERROR : Add folder to package failed!\n");
			return false;
		}
		printf("SUCCESS : Pack [%s] Folder to [%s] finished, Total %d files.\n",
			g_StringTable[OPER_PACK_FOLDER_TO_ADD], g_StringTable[OPER_PACK_PACKFILE_NAME], g_PackFileShell->GetElemCountInPak(g_nPackIndex));
	}
	else if (g_StringTable[OPER_PACK_BATCH_FILE][0])
	{	//====把此批处理文件中列出的内容都加入打包文件====
	}

	g_PackFileShell->ClosePack(g_nPackIndex);
	g_nPackIndex = -1;
	return true;
}


//扫描包文件的回调函数，传入参数表示扫描到的子文件
//返回值如果为非0，则继续扫描，返回值为0则终止扫描。
//参看IPackFileShell::ScanAllPack  IPackFileShell::fnScanPackCallback
int	CombinPackCallback(IPackFileShell::ELEM_FILE_INFO& ElemInfo, void* pParam)
{
	IPackFileShell::ELEM_FILE_INFO	OldInfo;
	if (g_PackFileShell->GetElemInfo(ElemInfo.uId, OldInfo))
	{
		if (ElemInfo.uSize == OldInfo.uSize && ElemInfo.uCRC == OldInfo.uCRC)
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
	if (s_pAddShell->GetElemStoreDataInPak(ElemInfo.nPakIndex, ElemInfo.nElemIndex, pBuffer, ElemInfo.uStoreSize) != ElemInfo.uStoreSize)
		goto ERROR_EXIT;
	int nPreIndex = ElemInfo.nPakIndex;
	ElemInfo.nPakIndex = g_nPackIndex;
	if (!g_PackFileShell->AddElemToPak(ElemInfo, pBuffer))
	{
		ElemInfo.nPakIndex = nPreIndex;
		goto ERROR_EXIT;
	}
	ElemInfo.nPakIndex = nPreIndex;
	free(pBuffer);
	return true;

ERROR_EXIT:
	free (pBuffer);
	return false;
}

IPackFileShell* LoadPackFile(const char* pPackFile);

bool CombinOperation()
{
	bool bResult = false;
	s_pAddShell = LoadPackFile(g_StringTable[OPER_COMBIN_ADDED_PACKFILE_NAME]);
	if (!s_pAddShell)
		goto ERROR_EXIT;

	g_nPackIndex = g_PackFileShell->CreatePack(g_StringTable[OPER_COMBIN_PACKFILE_NAME], true, false);
	if (g_nPackIndex < 0)
	{
		printf("ERROR : Open package [%s] failed!\n", g_StringTable[OPER_COMBIN_PACKFILE_NAME]);
		goto ERROR_EXIT;
	}

	int nScanCount = 0;
	int nCount = g_PackFileShell->GetElemCountInPak(g_nPackIndex);
	if (!s_pAddShell->ScanAllPack(CombinPackCallback, 0, nScanCount))
	{
		printf("ERROR : combin [%s] to [%s] has been interrupt!\n",
			g_StringTable[OPER_COMBIN_ADDED_PACKFILE_NAME],
			g_StringTable[OPER_COMBIN_PACKFILE_NAME]);
	}

	printf("SUCCESS : %d elems from [%s] have been added to [%s].\n",
		(g_PackFileShell->GetElemCountInPak(g_nPackIndex) - nCount),
		g_StringTable[OPER_COMBIN_ADDED_PACKFILE_NAME],
		g_StringTable[OPER_COMBIN_PACKFILE_NAME]);

	bResult = true;

ERROR_EXIT:
	SAFE_RELEASE(s_pAddShell);
	g_PackFileShell->ClosePack(g_nPackIndex);
	g_nPackIndex = -1;
	return bResult;
}

