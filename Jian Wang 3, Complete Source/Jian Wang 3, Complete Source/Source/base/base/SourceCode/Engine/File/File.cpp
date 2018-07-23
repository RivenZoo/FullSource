//---------------------------------------------------------------------------
//  Engine文件模块接口函数实现
//	Copyright : Kingsoft Season 2004
//	Author	:   Wooy(Wu yue)
//	CreateTime:	2004-5-18
//---------------------------------------------------------------------------
#include "Precompile.h"
#include "./AloneFile.h"
#include "./PackFile.h"
#include "./XPackList.h"
#include "../Ucl/ucl.h"
#include "KGLog.h"
#include "Debug.h"

//---------------------------------------------------------------------------
// 文件读取模式 0 = 优先从磁盘读取 !0 = 优先从文件包读取
static int s_nEngineFindFilePackFirst = 1;

//设置查找文件的优先次序(是否先查找打包文件)
C_ENGINE_API void
g_SetFindFileMode(int FindPakFirst)
{
	s_nEngineFindFilePackFirst = FindPakFirst;
}

//加载打包文件
C_ENGINE_API int
g_LoadPackageFiles(const char* pListFile, const char* pSection)
{
	if (pListFile && pSection && pListFile[0] && pSection[0])
		return g_EnginePackList.Open(pListFile, pSection);
	return false;
}

//卸载打包文件
C_ENGINE_API void g_ClearPackageFiles()
{
	g_EnginePackList.Close();
}

//初始化UCL压缩算法模块
C_ENGINE_API int CD_LCU_I()
{
	return (!ucl_init());
}

//UCL压缩算法-压缩函数
C_ENGINE_API int CD_LCU_C(const unsigned char* pSrcBuffer, unsigned int nSrcLen,
					unsigned char* pDestBuffer, unsigned int* pDestLen, int nCompressLevel)
{
	return (!ucl_nrv2b_99_compress(pSrcBuffer, nSrcLen, pDestBuffer, pDestLen, NULL, nCompressLevel, NULL, NULL));
}

//UCL压缩算法-解压函数
C_ENGINE_API int CD_LCU_D(const unsigned char* pSrcBuffer, unsigned nSrcLen, unsigned char* pDestBuffer, unsigned int uExtractSize)
{
	unsigned int uDestLen = 0;
	ucl_nrv2b_decompress_8(pSrcBuffer, nSrcLen, pDestBuffer, &uDestLen, NULL);
	return (uDestLen == uExtractSize);
}

C_ENGINE_API IFile*
g_OpenFile(const char* FileName, int ForceSingleFile/* = false*/, int ForWrite/* = false*/)
{
	if (FileName == NULL || FileName[0] == 0)
		return 0;

	int	TryTurn[2] = { 0, 0 };	//0-不尝试，1-读取独立文件，2-读取打包文件 --- ？为何如此分？
	if (ForceSingleFile || ForWrite)
	{
		TryTurn[0] = 1;
	}
	else if (s_nEngineFindFilePackFirst)
	{
		TryTurn[0] = 2;
		TryTurn[1] = 1;
	}
	else
	{
		TryTurn[0] = 1;
		TryTurn[1] = 2;
	}

	IFile*		pFile = NULL;
	for (int nTry = 0; nTry < 2; nTry++)
	{
		if (TryTurn[nTry] == 2)
		{
			KPackFile	pak;
			if (pak.Open(FileName))
			{
				pFile = pak.Deprive();
				break;
			}
		}
		else if (TryTurn[nTry] == 1)
		{
			KAloneFile	alone;
			if (alone.Open(FileName, ForWrite))
			{
				pFile = alone.Deprive();
				break;
			}
		}
	}
	return pFile;
}

C_ENGINE_API
IFile*	g_CreateFile(const char* FileName)
{
	KAloneFile	alone;
	if (alone.Create(FileName))
		return alone.Deprive();

	#ifdef _DEBUG
	if (FileName)
		g_DebugLog("ERROR: failed to create file[%s]!", FileName);
	#endif

	return NULL;
}

//#define	PAK_INDEX_STORE_IN_RESERVED	0
/*
//----modify by Wooy to add Adjust color palette and to get rid of #@$%^& ----2003.8.19
SPRHEAD* SprGetHeader(const char* pszFileName, SPROFFS*& pOffsetTable)
{
	pOffsetTable = NULL;

	if(pszFileName == NULL || pszFileName[0] == 0)
		return NULL;

	KPakFile	File;
	if (!File.Open(pszFileName))
		return NULL;

	SPRHEAD*		pSpr = NULL;
	if (File.IsFileInPak())
	{
		//====到文件包内寻找读取图文件=====
		XPackElemFileRef	PakRef;
		//_ASSERT(g_pPakList);
		if (g_pPakList->FindElemFile(pszFileName, PakRef))
		{
			pSpr = g_pPakList->GetSprHeader(PakRef, pOffsetTable);
			if (pSpr)
				pSpr->Reserved[PAK_INDEX_STORE_IN_RESERVED] = (WORD)(short)PakRef.nPackIndex;
		}
	}
	else
	{
		bool			bOk = false;
		SPRHEAD			Header;
		//---读文件头，并判断是否为合法的spr图文件---
		while(File.Read(&Header, sizeof(SPRHEAD)) == sizeof(SPRHEAD))
		{
			if (*(int*)&Header.Comment[0] != SPR_COMMENT_FLAG || Header.Colors > 256)
				break;
			//---为输出缓冲区分配空间---
			unsigned int uEntireSize = File.Size();
			pSpr = (SPRHEAD*)malloc(uEntireSize);
			if (pSpr == NULL)
				break;

			uEntireSize -= sizeof(SPRHEAD);
			//---读取spr剩下的数据---
			if (File.Read(&pSpr[1], uEntireSize) == uEntireSize)
			{
				//----获得图形帧索引表的开始位置---
				pOffsetTable = (SPROFFS*)(((char*)(pSpr)) + sizeof(SPRHEAD) + Header.Colors * 3);
				Header.Reserved[PAK_INDEX_STORE_IN_RESERVED] = (WORD)(-1);
				memcpy(pSpr, &Header, sizeof(SPRHEAD));
				bOk = true;
			}
			break;
		};

		if (bOk == false && pSpr)
		{
			free (pSpr);
			pSpr = NULL;
		}
	}
	File.Close();
	return pSpr;
}
*/
/*void SprReleaseHeader(SPRHEAD* pSprHeader)
{
    if (pSprHeader)
		free(pSprHeader);
}
*/
/*SPRFRAME* SprGetFrame(SPRHEAD* pSprHeader, int nFrame)
{
	SPRFRAME*	pFrame = NULL;
	if (pSprHeader && g_pPakList)
	{
		int nPakIndex = (short)pSprHeader->Reserved[PAK_INDEX_STORE_IN_RESERVED];
		if (nPakIndex >= 0)
			pFrame = g_pPakList->GetSprFrame(nPakIndex, pSprHeader, nFrame);
	}
	return pFrame;
}

void SprReleaseFrame(SPRFRAME* pFrame)
{
    if (pFrame)
		free(pFrame);
}

//#include "JpgLib.h"

KSGImageContent*	get_jpg_image(const char cszName[], unsigned uRGBMask16)
{
	KPakFile	File;
	unsigned char *pbyFileData = NULL;

	if (File.Open(cszName))
	{
		unsigned int uSize = File.Size();
		pbyFileData = (unsigned char *)malloc(uSize);
		if (pbyFileData)
		{
			if (File.Read(pbyFileData, uSize) != uSize)
			{
				free (pbyFileData);
				pbyFileData = NULL;
			}
		}
	}

	if (!pbyFileData)
        return NULL;

	int nResult = false;
    int nRetCode = false;
    KSGImageContent *pImageResult = NULL;

	BOOL		bRGB555;
	JPEG_INFO	JpegInfo;

    if (uRGBMask16 == ((unsigned)-1))
    {
    	bRGB555 = (g_pDirectDraw->GetRGBBitMask16() == RGB_555) ? TRUE : FALSE;
    }
    else
    {
        bRGB555 = (uRGBMask16 == RGB_555) ? TRUE : FALSE;
    }

    nRetCode = jpeg_decode_init(bRGB555, TRUE);
	if(!nRetCode)
        goto Exit0;
         
	nRetCode = jpeg_decode_info(pbyFileData, &JpegInfo);
    if (!nRetCode)
        goto Exit0;

	pImageResult = (KSGImageContent *)malloc(KSG_IMAGE_CONTENT_SIZE(JpegInfo.width, JpegInfo.height));
    if (!pImageResult)
        goto Exit0;

    pImageResult->nWidth = JpegInfo.width;
    pImageResult->nHeight = JpegInfo.height;

	nRetCode = jpeg_decode_data(pImageResult->Data, &JpegInfo);
    if (!nRetCode)
        goto Exit0;

    nResult = true;

Exit0:
	free (pbyFileData);
    if (!nResult && pImageResult)
	{
		free (pImageResult);
		pImageResult = NULL;
    }

	return pImageResult;
}


void release_image(KSGImageContent *pImage)
{
    if (pImage)
        free (pImage);
}
*/

