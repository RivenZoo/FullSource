//---------------------------------------------------------------------------
//	文字串处理
//	Copyright : Kingsoft 2002
//	Author	:   Wooy(Wu yue)
//	CreateTime:	2002-8-31
//	本文件默认字符集里单个字符的最大宽度为2（即一个字符最多有两个字符组成），
//	如果新加进来的字符集合不符合这个条件，需要更改相应的代码。
//---------------------------------------------------------------------------
#include "Precompile.h"
#include "Text.h"
#include "CharacterSetDepend.inl"

#define		MAX_ENCODED_CTRL_LEN	4	//单个控制符（控制标识+控制参数）的最大存储长度

#define	ADJUST_FONT_SIZE(size) ((size >= 4) ? ((size <= 64) ? size : 64) : 4)


LOCALIZATION_CHARACTER_SET g_LocalCharacterSet = LOCALIZATION_CHARACTER_SET_GBK; //本地字符集，默认为GBK

//得到一个字符的宽度（占几个字节）
int LOC_GetCharacterWide(unsigned char Character)
{
	switch(g_LocalCharacterSet)
	{
	case LOCALIZATION_CHARACTER_SET_GBK:
	case LOCALIZATION_CHARACTER_SET_BIG5:
		if (Character >= 0x80)
			return 2;
		break;
	case LOCALIZATION_CHARACTER_SET_ENGLISH:
	case LOCALIZATION_CHARACTER_SET_VIETNAM:
		break;
	}
	return 1;
}


C_ENGINE_API
void LOC_SetLocalCharacterSet(LOCALIZATION_CHARACTER_SET LocCharacterSet)
{
	g_LocalCharacterSet = LocCharacterSet;
}

C_ENGINE_API
LOCALIZATION_CHARACTER_SET LOC_GetLocalCharacterSet()
{
	return g_LocalCharacterSet;
}

IInlinePicEngineSink* g_pIInlinePicSink = NULL;	//嵌入式图片的处理接口[wxb 2003-6-19]
C_ENGINE_API
int TAdviseEngine(IInlinePicEngineSink* pSink)
{
	g_pIInlinePicSink = pSink;
	return 0;
}

C_ENGINE_API
int TUnAdviseEngine(IInlinePicEngineSink* pSink)
{
	if (pSink == g_pIInlinePicSink)
		g_pIInlinePicSink = NULL;
	return 0;
}


//检测某个字符是否为不许放置行首的字符，不是限制字符则返回0，否则返回字符占的子节数
C_ENGINE_API
int TIsCharacterNotAlowAtLineHead(const char* pCharacter)
{
	switch(g_LocalCharacterSet)
	{
	case LOCALIZATION_CHARACTER_SET_GBK:
		return GBK_IsCharacterNotAlowAtLineHead(pCharacter);

	case LOCALIZATION_CHARACTER_SET_BIG5:
		return BIG5_IsCharacterNotAlowAtLineHead(pCharacter);

	case LOCALIZATION_CHARACTER_SET_ENGLISH:
	case LOCALIZATION_CHARACTER_SET_VIETNAM:
		return ENGLISH_IsCharacterNotAlowAtLineHead(pCharacter);
	}

	return false;
}

//获取本行的下个显示字符
C_ENGINE_API
const char* TGetSecondVisibleCharacterThisLine(const char* pCharacter, int nPos, int nLen)
{
	if (pCharacter && nLen > 0)
	{
		int bFoundFirst = false;
		while(nPos < nLen)
		{
			unsigned char cChar = (unsigned char)(pCharacter[nPos]);
			if (cChar >= 0x20)
			{
				if (bFoundFirst)
					return (pCharacter + nPos);
				bFoundFirst = true;
				nPos += LOC_GetCharacterWide(cChar);
				continue;
			}
			if (cChar == KTC_COLOR || cChar == KTC_BORDER_COLOR)
				nPos += 4;
			else if (cChar == KTC_INLINE_PIC)
				nPos += 1 + sizeof(unsigned short);
			else if (cChar == KTC_COLOR_RESTORE || cChar == KTC_BORDER_RESTORE)
				nPos++;
			break;
		};
	}
	return NULL;
}

//--------------------------------------------------------------------------
//	功能：寻找分割字符串的合适位置
//	参数：pString    --> 想要分割的字符串
//		　nDesirePos --> 期望分割的位置（以字节为单位）
//		  bLess      --> 如果期望分割的位置处于一个字符编码的中间时，结果位置
//					为前靠还是后靠，0: 向后靠; 非0: 向前靠。
//	注释：Chinese GBK编码版本，此字符串中字符全部视为显示字符，不包含控制字符
//--------------------------------------------------------------------------
C_ENGINE_API
int TSplitString(const char* pString, int nDesirePos, int bLess)
{
	register int	nPos = 0;
	if (pString)
	{
		nDesirePos -= 2; //默认单个字符的最大宽度为2
		unsigned char cCharacter = 0;
		while(nPos < nDesirePos)
		{
			cCharacter = (unsigned char)pString[nPos];
			if (cCharacter)
				nPos += LOC_GetCharacterWide(cCharacter);
			else
				break;
		};
		nDesirePos += 2;
		while(nPos < nDesirePos)
		{
			cCharacter = (unsigned char)pString[nPos];
			int nWide = LOC_GetCharacterWide(cCharacter);
			if (nWide > 1)
			{
				if (bLess && (nPos + nWide > nDesirePos))
					break;
				if (pString[nPos + 1] == 0) //默认单个字符的最大宽度为2
				{//防止只出现多字节字符的部分
					nPos ++;
					break;
				}				
				nPos += nWide;
			}
			else if (cCharacter)
				nPos ++;
			else
				break;
		}
	}
	return nPos;
}

//--------------------------------------------------------------------------
//	功能：在编码字串寻找分割字符串的合适位置
//	参数：pString    --> 想要分割的字符串
//		  nCount	 -->字符串内容的长度（以字节为单位）
//		　nDesirePos --> 期望分割的位置（以缓冲驱存储字节为单位）
//		  bLess      --> 如果期望分割的位置处于一个中文字符编码的中间时，
//						结果位置为前靠还是后靠，0: 向后靠; 非0: 向前靠。
//	注释：Chinese GBK编码版本，此字符串中可包含已经编码的控制符
//--------------------------------------------------------------------------
C_ENGINE_API
int	TSplitEncodedString(const char* pString, int nCount, int nDesirePos, int bLess)
{
	int	nPos = 0;
	if (pString)
	{
		if (nDesirePos <= nCount)
		{
			register unsigned char cCharacter = 0;
			nDesirePos -= MAX_ENCODED_CTRL_LEN;
			while (nPos < nDesirePos)
			{
				cCharacter = (unsigned char)pString[nPos];
				if (cCharacter == KTC_COLOR || cCharacter == KTC_BORDER_COLOR)
					nPos += 4;
				else if (cCharacter == KTC_INLINE_PIC)
					nPos += 3;//1 + sizeof(WORD);
				else
					nPos += LOC_GetCharacterWide(cCharacter);
			}
			nPos += MAX_ENCODED_CTRL_LEN;
			while(nPos < nDesirePos)
			{
				cCharacter = (unsigned char)pString[nPos];
				if (cCharacter == KTC_INLINE_PIC)
				{
					if (bLess && nPos + 3 > nDesirePos)
						break;
					if (nPos + 3 >= nCount)
					{
						nPos = nCount;
						break;
					}
					nPos += 3;//1 + sizeof(WORD);
				}
				else if (cCharacter == KTC_COLOR || cCharacter == KTC_BORDER_COLOR)
				{
					if (bLess && (nPos + 4 > nDesirePos))
						break;
					if (nPos + 4 >= nCount)
					{
						nPos = nCount;
						break;
					}
					nPos += 4;
				}
				else
				{
					int nWide = LOC_GetCharacterWide(cCharacter);
					if (nPos + nWide > nCount)
					{//防止只出现多字节字符的部分
						nPos = nCount;
						break;
					}
					if (bLess && (nPos + nWide > nDesirePos))
						break;								
					nPos += nWide;
				}
			}

		}
		else
		{
			nPos = nCount;
		}
	}
	return nPos;
	
}


//字符换控制码的字符标记表示与内部编码的对应结构
#define	KTC_CTRL_CODE_MAX_LEN	7
typedef struct _KCtrlTable
{
	char    szCtrl[KTC_CTRL_CODE_MAX_LEN + 1];	//字符换控制码的字符表示
	short	nCtrlLen;							//字符换控制码的字符表示的长度
	short   nCtrl;								//字符换控制码的内部编码
}KCtrlTable;

//控制码列表
static	const KCtrlTable	s_CtrlTable[] =
{	
	{ "enter",	5, KTC_ENTER		},
	{ "color",	5, KTC_COLOR		},
	{ "bclr",	4, KTC_BORDER_COLOR	},
	{ "pic",	3, KTC_INLINE_PIC	},
};

//控制码的数目
static	const int	s_nCtrlCount = sizeof(s_CtrlTable)/sizeof(KCtrlTable);

//颜色结构
typedef struct _KColorTable
{
	char			Token[8];		//颜色的字符表示
	unsigned char	Red;			//颜色的R分量
	unsigned char	Green;			//颜色的G分量
	unsigned char	Blue;			//颜色的B分量
}KColorTable;

//颜色列表
static	const KColorTable	s_ColorTable[] =
{
	{ "Black",		0,		0,		0	},
	{ "White",		255,	255,	255	},
	{ "Gray",		192,	192,	192 },
	{ "Red",		255,	0,		0	},
	{ "Gray1",		207,	207, 	207	},
	{ "Gray2",		173,	173, 	173	},
	{ "Gray3",		150,	150, 	150	},
	{ "Gray4",		99,		99, 	99	},
	{ "Gray5",		69,		84, 	75	},
	{ "Gray6",		40,		40, 	40	},
	{ "Gray7",		38,		38, 	38	},
	{ "Yellow1",	255,	255,	187	},
	{ "Yellow2",	255,	255,	0	},
	{ "Yellow3",	163,	176,	106	},
	{ "Yellow4",	96,		96,		0	},
	{ "Yellow5",	150,	140,	0	},
	{ "Yellow6",	239,	255,	9	},
	{ "Yellow7",	120,	99,		3	},
	{ "Orange1",	255,	202,	126	},
	{ "Orange2",	255,	150,	0	},
	{ "Orange3",	169,	99,		0	},
	{ "Orange4",	230,	140,	0	},
	{ "Red1",		255,	126,	126	},
	{ "Red2",		255,	0,		0	},
	{ "Red3",		169,	0,		0	},
	{ "Red4",		139,	46,		28	},
	{ "Red5",		220,	30,		0	},
	{ "Red6",		239,	55,		12	},
	{ "Purple1",	202,	126,	255	},
	{ "Purple2",	185,	38,		210	},
	{ "Purple3",	94,		27,		160	},
	{ "Purple4",	223,	18,		201	},
	{ "Blue",		0,		0,		255 },
	{ "Blue1",		126,	126,	255 },
	{ "Blue2",		0,		126,	255 },
	{ "Blue3",		0,		0,		169 },
	{ "Blue4",		30,		54,		108 },
	{ "Blue5",		30,		104,	254 },
	{ "Green",		0,		255,	0	},
	{ "Green1",		126,	227,	163	},
	{ "Green2",		0,		200,	72	},
	{ "Green3",		0,		132,	47	},
	{ "Green4",		16,		88,		48	},
	{ "Green5",		76,		223,	21	},
	{ "Green6",		50,		205,	50	},
	{ "Yellow",		255,	255,	0	},
	{ "Pink",		255,	0,		255	},
	{ "Cyan",		0,		255,	255	},
	{ "Metal",		246,	255,	117	},
	{ "Wood",		0,		255,	120	},
	{ "Water",		78,		124,	255	},
	{ "Fire",		255,	90,		0	},
	{ "Earth",		254,	207,	179	},
	{ "DBlue",		120,	120,	120 },
	{ "HBlue",		100,	100,	255 },
	{ "BAttr",		72,		141,	255 },
	{ "SAttr",		102,	104,	215 },
	{ "Nor",		245,	245,	245 },
	{ "Sock",		225,	207,	226 },
	{ "Beset",		72,		141,	255 },
	{ "Series",		179,	254,	155 },
	{ "Gold",		249,	193,	21	},
	{ "Purple",		239,	79,		184	},
};

//颜色的数目
static	const int	s_nColorCount = sizeof(s_ColorTable)/sizeof(KColorTable);

//嵌入图片[wxb 2003-6-19]
#define MAXPICTOKENLEN	16


static int TEncodeCtrl(char* pBuffer, int nCount, int& nReadPos, int& nShortCount);
static int  TEncodeCtrl(int nCtrl, char* pParamBuffer, int nParamLen, char* pEncodedBuffer);

//--------------------------------------------------------------------------
//	功能：对文本串中的控制标记进行转换，去除无效字符，缩短文本串存储长度
//--------------------------------------------------------------------------
C_ENGINE_API
int	TEncodeText(char* pBuffer, int nCount)
{
	int nShortCount = 0;
	if (pBuffer)
	{
		unsigned char	cCharacter;
		int		nReadPos = 0;		
		while(nReadPos < nCount)
		{
			cCharacter = pBuffer[nReadPos];	
			if (cCharacter == 0x0d)	//换行
			{
				if (nReadPos + 1 < nCount && pBuffer[nReadPos + 1] == 0x0a)
					nReadPos += 2;
				else
					nReadPos ++;
				pBuffer[nShortCount++] = 0x0a;
			}
			else if (pBuffer[nReadPos] == '<')
				TEncodeCtrl(pBuffer, nCount, nReadPos, nShortCount);
			else if(cCharacter >= 0x20 || cCharacter == 0x0a || cCharacter == 0x09)
			{
				int nWide = LOC_GetCharacterWide(cCharacter);
				if (nReadPos + nWide > nCount)
					break;
				pBuffer[nShortCount++] = cCharacter;
				if (nWide > 1) //默认单个字符的最大宽度为2
					pBuffer[nShortCount++] = pBuffer[nReadPos + 1];
				nReadPos += nWide;
			}
			else
				nReadPos++;
				
		}
		if (nShortCount <nCount)
			pBuffer[nShortCount] = 0;
	}
	return nShortCount;
}

//--------------------------------------------------------------------------
//	功能：过滤去除已编码文本中的无效(非法)内容
//--------------------------------------------------------------------------
C_ENGINE_API
int TFilterEncodedText(char* pBuffer, int nCount)
{
	int nShortCount = 0;
	if (pBuffer)
	{
		unsigned char	cCharacter;
		int nReadPos = 0;
		while(nReadPos < nCount)
		{
			cCharacter = (unsigned char)pBuffer[nReadPos];
			if (cCharacter >= 0x20 || cCharacter == 0x0a || cCharacter == 0x09)
			{
				int nWide = LOC_GetCharacterWide(cCharacter);
				if (nReadPos + nWide > nCount)
					break;
				pBuffer[nShortCount++] = cCharacter;
				if (nWide > 1) //默认单个字符的最大宽度为2
					pBuffer[nShortCount++] = pBuffer[nReadPos + 1];

				nReadPos += nWide;
			}
			else if (cCharacter == KTC_COLOR || cCharacter == KTC_BORDER_COLOR)
			{
				if (nReadPos + 4 < nCount)
				{
					*(int*)(pBuffer + nShortCount) = *(int*)(pBuffer + nReadPos);
					nShortCount += 4;
					nReadPos += 4;
				}
				else
				{
					nReadPos++;
					break;
				}
			}
			else if (cCharacter == KTC_INLINE_PIC)
			{
				if ((int)(nReadPos + 1 + sizeof(unsigned short)) < nCount)
				{
					memcpy(pBuffer + nShortCount, pBuffer + nReadPos, 1 + sizeof(unsigned short));;
					nShortCount += 1 + sizeof(unsigned short);
					nReadPos += 1 + sizeof(unsigned short);
				}
				else
				{
					nReadPos++;
					break;
				}
			}
			else
				nReadPos ++;
		}
		if (nShortCount < nCount)
			pBuffer[nShortCount] = 0;
	}

	return nShortCount;
}

//--------------------------------------------------------------------------
//	功能：分析转换控制符
//--------------------------------------------------------------------------
static int TEncodeCtrl(char* pBuffer, int nCount, int& nReadPos, int& nShortCount)
{

	assert(pBuffer != NULL && nReadPos < nCount && nShortCount < nCount && nShortCount <= nReadPos);
	
	int nCtrlCodeSize, nEndPos, nCtrl;

	//寻找结束符号'='的位置或'>'的位置
	int nEqualPos = nReadPos + 1;
	for (; nEqualPos < nCount && nEqualPos <= nReadPos + KTC_CTRL_CODE_MAX_LEN; nEqualPos++)
		if (pBuffer[nEqualPos] == '>' || pBuffer[nEqualPos] == '=')
			break;	

	if(nEqualPos >= nCount || nEqualPos > nReadPos + KTC_CTRL_CODE_MAX_LEN)
		goto NO_MATCHING_CTRL;	//未找到'='或者'>'结束符号

	nCtrlCodeSize = nEqualPos - nReadPos - 1;	//控制命令符号的长度

	for (nCtrl = 0; nCtrl < s_nCtrlCount; nCtrl++)
	{
		if (nCtrlCodeSize ==  s_CtrlTable[nCtrl].nCtrlLen &&
			memcmp(pBuffer + nReadPos + 1, s_CtrlTable[nCtrl].szCtrl, nCtrlCodeSize) == 0)
			break;
	}
	if (nCtrl >= s_nCtrlCount)		//未找到匹配一致的控制命令
		goto NO_MATCHING_CTRL;
	nCtrl = s_CtrlTable[nCtrl].nCtrl;

	nEndPos = nEqualPos;
	if (pBuffer[nEqualPos] != '>')
	{
		for(nEndPos++; nEndPos < nCount; nEndPos++)
			if (pBuffer[nEndPos] == '>')
				break;
		if (nEndPos >= nCount)
			goto NO_MATCHING_CTRL;
		nShortCount += TEncodeCtrl(nCtrl, pBuffer + nEqualPos + 1,
			nEndPos - nEqualPos - 1, pBuffer + nShortCount);
	}
	else
		nShortCount += TEncodeCtrl(nCtrl, NULL, 0, pBuffer + nShortCount);
	nReadPos = nEndPos + 1;
	return true;

NO_MATCHING_CTRL:
	pBuffer[nShortCount++] = '<';
	nReadPos++;
	return false;
}

//--------------------------------------------------------------------------
//	功能：转换并存储控制命令及各控制参数
//--------------------------------------------------------------------------
static int TEncodeCtrl(int nCtrl, char* pParamBuffer, int nParamLen, char* pEncodedBuffer)
{
	assert(pEncodedBuffer && (nParamLen == 0 || pParamBuffer != NULL));

	int nEncodedSize = 0;
	static char	Color[8];
	static char	szPic[MAXPICTOKENLEN];

	switch(nCtrl)
	{
	case KTC_ENTER:
		pEncodedBuffer[nEncodedSize ++] = nCtrl;
		break;
	case KTC_INLINE_PIC:	//[wxb 2003-6-19]
		if (nParamLen == 0 && nParamLen >= MAXPICTOKENLEN)
			break;
		{
			memcpy(szPic, pParamBuffer, nParamLen);
			szPic[nParamLen] = 0;
			pEncodedBuffer[nEncodedSize] = KTC_INLINE_PIC;
			*((unsigned short*)(pEncodedBuffer + nEncodedSize + 1)) = atoi(szPic);
			nEncodedSize += 1 + sizeof(unsigned short);
		}		
		break;
	case KTC_COLOR:
		if (nParamLen == 0)
		{
			pEncodedBuffer[nEncodedSize ++] = KTC_COLOR_RESTORE;
		}
		else if (nParamLen < 8)
		{
			memcpy(Color, pParamBuffer, nParamLen);
			Color[nParamLen] = 0;
			for (int i = 0; i < s_nColorCount; i++)
			{
#ifndef __linux
				if (stricmp(Color,s_ColorTable[i].Token) == 0)
#else
				if(strcasecmp(Color,s_ColorTable[i].Token) == 0)
#endif
				{
					pEncodedBuffer[nEncodedSize] = KTC_COLOR;
					pEncodedBuffer[nEncodedSize + 1]= s_ColorTable[i].Red;
					pEncodedBuffer[nEncodedSize + 2]= s_ColorTable[i].Green;
					pEncodedBuffer[nEncodedSize + 3]= s_ColorTable[i].Blue;
					nEncodedSize += 4;
					break;
				}
			}
		}		
		break;
	case KTC_BORDER_COLOR:
		if (nParamLen == 0)
		{
			pEncodedBuffer[nEncodedSize ++] = KTC_BORDER_RESTORE;
		}
		else if (nParamLen < 8)
		{
			memcpy(Color, pParamBuffer, nParamLen);
			Color[nParamLen] = 0;
			for (int i = 0; i < s_nColorCount; i++)
			{
#ifndef __linux
				if (stricmp(Color,s_ColorTable[i].Token) == 0)
#else
				if(strcasecmp(Color,s_ColorTable[i].Token) == 0)
#endif
//				if (stricmp(Color,s_ColorTable[i].Token) == 0)
				{
					pEncodedBuffer[nEncodedSize] = KTC_BORDER_COLOR;
					pEncodedBuffer[nEncodedSize + 1]= s_ColorTable[i].Red;
					pEncodedBuffer[nEncodedSize + 2]= s_ColorTable[i].Green;
					pEncodedBuffer[nEncodedSize + 3]= s_ColorTable[i].Blue;
					nEncodedSize += 4;
					break;
				}
			}
		}
		break;
	}
	return nEncodedSize;
}

C_ENGINE_API
int	TRemoveCtrlInEncodedText(char* pBuffer, int nCount)
{
	int nLen = 0;
	nCount = TFilterEncodedText(pBuffer, nCount);
	for (int nPos = 0; nPos < nCount; nPos++)
	{
		char cCharacter = pBuffer[nPos];
		if (cCharacter == KTC_COLOR || cCharacter == KTC_BORDER_COLOR)
			nPos += 3;
		else if (cCharacter == KTC_INLINE_PIC)
			nPos += sizeof(unsigned short);
		else if (cCharacter != KTC_COLOR_RESTORE && cCharacter != KTC_BORDER_RESTORE)
		{
			pBuffer[nLen] = cCharacter;
			nLen ++;
		}
	}
	return nLen;
}

//获取编码文本的行数与最大行宽
//参数：pBuffer			文本缓冲区
//		nCount			文本数据的长度
//		nWrapCharaNum	限制每行不许超过的字符数目
//		nMaxLineLen		用于获取文本的实际最大行宽（字符数目）
//		nFontSize		采用字体的大小 [wxb 2003-6-19]
//		nSkipLine		跳过前面多少行的数据
//		nNumLineLimit	检测的文本的行数，超过限制行数目之后的内容被忽略。如果此值小于等于0则表示无此限制。
//返回：文本的行数
//C_ENGINE_API
//int	TGetEncodedTextLineCount(const char* pBuffer, int nCount, int nWrapCharaNum, int& nMaxLineLen, int nFontSize, int nSkipLine = 0, int nNumLineLimit = 0)
C_ENGINE_API
int	TGetEncodedTextLineCount(const char* pBuffer, int nCount, int nWrapCharaNum, int& nMaxLineLen, int nFontSize, int nSkipLine, int nNumLineLimit,
							 int bPicSingleLine/* = FALSE*/)
{
	nMaxLineLen = 0;

	//设一个极值免得出错 [wxb 2003-6-20]
	if (nFontSize < 4 || nFontSize >= 64)
	{
		assert(0);
		return 0;
	}

	nFontSize = ADJUST_FONT_SIZE(nFontSize);

	float fMaxLineLen = 0;
	if (pBuffer == 0)
		return 0;

	if (nCount < 0)
		nCount = (int)strlen(pBuffer);

	float fNumChars = 0;
	int nNumLine = 0;
	int nPos = 0;
	unsigned char	cCode;

	if (nWrapCharaNum <= 0)
		nWrapCharaNum = 0x7fffffff;
	if (nSkipLine < 0)
		nSkipLine = 0;
	if (nNumLineLimit <= 0)
		nNumLineLimit = 0x7fffffff;

	int bNextLine = false;
	float fNumNextLineChar = 0;
	int  nExtraLineForInlinePic = 0;
	while(nPos < nCount)
	{
		cCode = (unsigned char)pBuffer[nPos];
		if (cCode == KTC_COLOR || cCode == KTC_BORDER_COLOR)//颜色控制
			nPos += 4;
		else if (cCode == KTC_INLINE_PIC)
		{
			//嵌入式图片处理 [wxb 2003-6-19]
			unsigned short wPicIndex = *((unsigned short*)(pBuffer + nPos + 1));
			nPos += 1 + sizeof(unsigned short);
			if (g_pIInlinePicSink)
			{
				int nWidth, nHeight;
				if (g_pIInlinePicSink->GetPicSize(wPicIndex, nWidth, nHeight))
				{
					if (nHeight > nFontSize)
					{
						int nExtraLines = nHeight - nFontSize;
						nExtraLines = nExtraLines / nFontSize + ((nExtraLines % nFontSize) ? 1 : 0);
						if (nExtraLines > nExtraLineForInlinePic && !bPicSingleLine)
							nExtraLineForInlinePic = nExtraLines;
					}
					if (fNumChars + (((float)nWidth) * 2 / nFontSize) < nWrapCharaNum)
						fNumChars += ((float)nWidth) * 2 / nFontSize;
					else if (fNumChars + (((float)nWidth) * 2 / nFontSize) == nWrapCharaNum || fNumChars == 0)
					{
						bNextLine = true;
						fNumChars += ((float)nWidth) * 2 / nFontSize;
					}
					else
					{
						bNextLine = true;
						fNumNextLineChar = ((float)nWidth) * 2 / nFontSize;
					}
				}
			}
		}
		else if (cCode == KTC_ENTER)
		{
			nPos ++;
			bNextLine = true;
		}
		else if (cCode != KTC_COLOR_RESTORE && cCode != KTC_BORDER_RESTORE)
		{
			int nWide = LOC_GetCharacterWide(cCode);
			nPos += nWide;
			if (fNumChars + nWide < nWrapCharaNum)
				fNumChars += nWide;
			else if (fNumChars + nWide == nWrapCharaNum || fNumChars == 0)
			{
				fNumChars += nWide;
				bNextLine = true;
			}
			else
			{
				bNextLine = true;
				fNumNextLineChar = (float)nWide;
			}
		}
		else
		{
			nPos++;
		}

		if (bNextLine == false && fNumChars && fNumChars + 3 >= nWrapCharaNum)
		{
			const char* pNext = TGetSecondVisibleCharacterThisLine(pBuffer, nPos, nCount);
			if (pNext && TIsCharacterNotAlowAtLineHead(pNext))
				bNextLine = true;
		}
		if (bNextLine)
		{
			if (nSkipLine > 0)
			{
				nSkipLine -= 1 + nExtraLineForInlinePic;

				//处理图片占多行的情况 [wxb 2003-6-19]
				if (nSkipLine < 0)
				{
					if (fMaxLineLen < fNumChars)
						fMaxLineLen = fNumChars;
					nNumLine += (-nSkipLine);
					if (nNumLine >= nNumLineLimit)
						break;
				}
			}
			else
			{
				if (fMaxLineLen < fNumChars)
					fMaxLineLen = fNumChars;
				nNumLine += 1 + nExtraLineForInlinePic;
				if (nNumLine >= nNumLineLimit)
					break;
			}
			nExtraLineForInlinePic = 0;
			fNumChars = (float)fNumNextLineChar;
			fNumNextLineChar = 0;
			bNextLine = false;
		}
	}
	if (nNumLine < nNumLineLimit && fNumChars && nSkipLine == 0)
	{
		if (fMaxLineLen < fNumChars)
			fMaxLineLen = fNumChars;
		nNumLine += 1 + nExtraLineForInlinePic;
	}

	nMaxLineLen = (int)(fMaxLineLen + (float)0.9999);	//进1
	return nNumLine;
}

//获得指定行的开始位置
int TGetEncodeStringLineHeadPos(const char* pBuffer, int nCount, int nLine, int nWrapCharaNum, int nFontSize, int bPicSingleLine)
{
	//设一个极值免得出错 [wxb 2003-6-20]
	assert(nFontSize >= 4 && nFontSize <= 64);
	nFontSize = ADJUST_FONT_SIZE(nFontSize);

	float fMaxLineLen = 0;
	if (pBuffer == 0 || nLine <= 0)
		return 0;

	if (nCount < 0)
		nCount = (int)strlen(pBuffer);

	float fNumChars = 0;
	int  nExtraLineForInlinePic = 0;
	int nPos = 0;
	unsigned char	cCode;

	if (nWrapCharaNum <= 0)
		nWrapCharaNum = 0x7fffffff;

	int bNextLine = false;
	float fNumNextLineChar = 0;
	while(nPos < nCount)
	{
		cCode = pBuffer[nPos];
		if (cCode == KTC_COLOR || cCode == KTC_BORDER_COLOR)//颜色控制
			nPos += 4;
		else if (cCode == KTC_INLINE_PIC)
		{
			//嵌入式图片处理 [wxb 2003-6-19]
			unsigned short wPicIndex = *((unsigned short*)(pBuffer + nPos + 1));
			nPos += 1 + sizeof(unsigned short);
			if (g_pIInlinePicSink)
			{
				int nWidth, nHeight;
				if (g_pIInlinePicSink->GetPicSize(wPicIndex, nWidth, nHeight))
				{
					if (nHeight > nFontSize)
					{
						int nExtraLines = nHeight - nFontSize;
						nExtraLines = nExtraLines / nFontSize + ((nExtraLines % nFontSize) ? 1 : 0);
						if (nExtraLines > nExtraLineForInlinePic && !bPicSingleLine)
							nExtraLineForInlinePic = nExtraLines;
					}
					if (fNumChars + (((float)nWidth) * 2 / nFontSize) < nWrapCharaNum)
						fNumChars += ((float)nWidth) * 2 / nFontSize;
					else if (fNumChars + (((float)nWidth) * 2 / nFontSize) == nWrapCharaNum || fNumChars == 0)
					{
						bNextLine = true;
						fNumChars += ((float)nWidth) * 2 / nFontSize;
					}
					else
					{
						bNextLine = true;
						fNumNextLineChar = ((float)nWidth) * 2 / nFontSize;
					}
				}
			}
		}
		else if (cCode == KTC_ENTER)
		{
			nPos ++;
			bNextLine = true;
		}
		else if (cCode != KTC_COLOR_RESTORE && cCode != KTC_BORDER_RESTORE)
		{
			int nWide = LOC_GetCharacterWide(cCode);
			nPos += nWide;
			if (fNumChars + nWide < nWrapCharaNum)
				fNumChars += nWide;
			else if (fNumChars + nWide == nWrapCharaNum || fNumChars == 0)
			{
				fNumChars += nWide;
				bNextLine = true;
			}
			else
			{
				bNextLine = true;
				fNumNextLineChar = (float)nWide;
			}
		}
		else
		{
			nPos++;
		}

		if (bNextLine == false && fNumChars && fNumChars + 3 >= nWrapCharaNum)
		{
			const char* pNext = TGetSecondVisibleCharacterThisLine(pBuffer, nPos, nCount);
			if (pNext && TIsCharacterNotAlowAtLineHead(pNext))
				bNextLine = true;
		}
		if (bNextLine)
		{
//			if (nSkipLine > 0)
//			{
//				nSkipLine -= 1 + nExtraLineForInlinePic;
//
//				//处理图片占多行的情况 [wxb 2003-6-19]
//				if (nSkipLine < 0)
//				{
//					if (fMaxLineLen < fNumChars)
//						fMaxLineLen = fNumChars;
//					nNumLine += (-nSkipLine);
//					if (nNumLine >= nNumLineLimit)
//						break;
//				}
//			}
			if ((--nLine) == 0)
				break;
			fNumChars = (float)fNumNextLineChar;
			fNumNextLineChar = 0;
			bNextLine = false;
		}
	}

	return nPos;
}

C_ENGINE_API
//如果原(包含控制符)字符串长度（包括结尾符）超过限定的长度，则截短它并加上..后缀
const char* TGetLimitLenEncodedString(const char* pOrigString, int nOrigLen, int nFontSize,
	int nWrapCharaNum, char* pLimitLenString, int& nShortLen, int nLineLimit, int bPicPackInSingleLine/*=false*/)
{
	if (pOrigString == NULL || pLimitLenString == NULL ||
		nOrigLen <= 0 || nShortLen < 2 || nLineLimit < 1 || nWrapCharaNum < 2)
	{
		nShortLen = 0;
		return NULL;
	}

	int nPreLineEndPos = 0, nFinalLineEndPos;
	if (nLineLimit > 1)	//跳过前面几行
	{
		nPreLineEndPos = TGetEncodeStringLineHeadPos(pOrigString, nOrigLen, nLineLimit - 1, nWrapCharaNum, nFontSize, bPicPackInSingleLine);
		if (nPreLineEndPos > nShortLen)
		{
			nShortLen = TSplitEncodedString(pOrigString, nOrigLen, nShortLen - 2, true);
			memcpy(pLimitLenString, pOrigString, nShortLen);
			pLimitLenString[nShortLen] = '.';
			pLimitLenString[nShortLen + 1] = '.';
			nShortLen += 2;
			return pLimitLenString;
		}
	}

	if (nPreLineEndPos < nOrigLen)
	{
		nFinalLineEndPos = TGetEncodeStringLineHeadPos(pOrigString + nPreLineEndPos,
			nOrigLen - nPreLineEndPos, 1, nWrapCharaNum, nFontSize, bPicPackInSingleLine) + nPreLineEndPos;
	}
	else
		nFinalLineEndPos = nOrigLen;

	if (nFinalLineEndPos >= nOrigLen)
	{
		nShortLen = TSplitEncodedString(pOrigString, nOrigLen, nShortLen, true);
		memcpy(pLimitLenString, pOrigString, nShortLen);
		return pLimitLenString;
	}

	int nDesireLen = (nFinalLineEndPos <= nShortLen) ? nFinalLineEndPos - 2 : nShortLen - 2;

	const char* pFinalLineHead = pOrigString + nPreLineEndPos;
	int nRemainCount = nOrigLen - nPreLineEndPos;
	nDesireLen -= nPreLineEndPos;
	while(true)
	{
		nShortLen = TSplitEncodedString(pFinalLineHead, nRemainCount, nDesireLen, true);
		int nMaxLineLen;
		TGetEncodedTextLineCount(pFinalLineHead, nShortLen, 0, nMaxLineLen, nFontSize, 0, 1, false);
		if (nMaxLineLen <= nWrapCharaNum - 2)
			break;
		nDesireLen --;
	}
	nShortLen += nPreLineEndPos;

   	memcpy(pLimitLenString, pOrigString, nShortLen);
	pLimitLenString[nShortLen] = '.';
	pLimitLenString[nShortLen + 1] = '.';
	nShortLen += 2;
	return pLimitLenString;
}

//--------------------------------------------------------------------------
//	功能：如果原字符串长度（包括结尾符）超过限定的长度，则截短它并加上..后缀
//	参数：pOrigString     --> 原字符串，要求不为空指针
//		　nOrigLen		  --> 原字符串长度（不包括结尾符）
//		  pLimitLenString --> 如果原字符串超出限长，用来存储截短后的字符串的缓冲区，要求不为空指针
//		  nLimitLen		  --> 限定长度，此值要求大于等于3
//	返回：如原字符串不超过限长，则返回原缓冲区指针，否则返回用来存储截短后的字符串的缓冲区的指针
//	注释：Chinese GBK编码版本，此字符串中字符全部视为显示字符，不包含控制字符
//--------------------------------------------------------------------------
C_ENGINE_API
const char* TGetLimitLenString(const char* pOrigString, int nOrigLen, char* pLimitLenString, int nLimitLen)
{
	if (pOrigString && pLimitLenString && nLimitLen > 0)
	{
		if (nOrigLen < 0)
			nOrigLen = (int)strlen(pOrigString);
		if (nOrigLen < nLimitLen)
			return pOrigString;
		if (nLimitLen > 2)
		{
			nOrigLen = TSplitString(pOrigString, nLimitLen - 3, true);
			memcpy(pLimitLenString, pOrigString, nOrigLen);
			pLimitLenString[nOrigLen] = '.';
			pLimitLenString[nOrigLen + 1] = '.';
			pLimitLenString[nOrigLen + 2] = 0;
		}
		else if (nLimitLen == 2)
		{
			pLimitLenString[0] = '.';
			pLimitLenString[1] = 0;
		}
		return ((nLimitLen >= 2) ? pLimitLenString : NULL);
	}
	return NULL;
}


//对已经编码的文本，从指定位置开始查找指定的控制符号的位置，返回-1表示未找到
C_ENGINE_API
int	TFindSpecialCtrlInEncodedText(const char* pBuffer, int nCount, int nStartPos, char cControl)
{
	int nFindPos = -1;
	if (pBuffer)
	{
		while(nStartPos < nCount)
		{
			unsigned char cCharacter = (unsigned char)pBuffer[nStartPos];
			if ((unsigned char)cControl == cCharacter)
			{
				nFindPos = nStartPos;
				break;
			}
			if (cCharacter == KTC_COLOR || cCharacter == KTC_BORDER_COLOR)
				nStartPos += 4;
			else if (cCharacter == KTC_INLINE_PIC)
				nStartPos += 3;
			else
				nStartPos += LOC_GetCharacterWide(cCharacter);
		}
	}
	return nFindPos;
}

//对已经编码的文本，去除指定类型的控制符
C_ENGINE_API
int	TClearSpecialCtrlInEncodedText(char* pBuffer, int nCount, char cControl)
{
	int nFinalLen = 0;
	int nReadPos = 0;
	if (pBuffer)
	{
		if ((unsigned char)(cControl) <= 0x80)
		{
			int nMatchLen = 1;
			if (cControl == KTC_COLOR || cControl == KTC_BORDER_COLOR)
				nMatchLen = 4;
			else if (cControl == KTC_INLINE_PIC)
				nMatchLen = 3;
			while(nReadPos < nCount)
			{
				unsigned char cCharacter = (unsigned char)pBuffer[nReadPos];
				if ((unsigned char)cControl == cCharacter)
				{
					nReadPos += nMatchLen;
				}
				else if (cCharacter == KTC_COLOR || cCharacter == KTC_BORDER_COLOR)
				{
					int nTemp = *(int*)(pBuffer + nReadPos);
					*(int*)(pBuffer + nFinalLen) = nTemp;
					nFinalLen += 4;
					nReadPos += 4;
				}
				else if (cCharacter == KTC_INLINE_PIC)
				{
					memmove((pBuffer + nFinalLen), (pBuffer + nReadPos), 3);
					nFinalLen += 3;
					nReadPos += 3;
				}
				else
				{
					pBuffer[nFinalLen++] = pBuffer[nReadPos++];
					if (LOC_GetCharacterWide(cCharacter) > 1) //默认单个字符的最大宽度为2
						pBuffer[nFinalLen++] = pBuffer[nReadPos++];
				}
			}
		}
	}
	return nFinalLen;
}

//对已经编码的文本，指定输出长度的在缓冲区中位置
C_ENGINE_API
int TGetEncodedTextOutputLenPos(const char* pBuffer, int nCount, int& nLen, int bLess, int nFontSize)
{
	int nIndex = 0, nLenTemp = 0;

	if (nFontSize < 4)
	{
		assert(0);
		return 0;
	}

	nFontSize = ADJUST_FONT_SIZE(nFontSize);

    if (pBuffer)
	{
		int nWidth, nHeight;
		int nByteCount = 0, nCurCharLen = 0;
	    unsigned char cCharacter        = 0;

		while(nLenTemp < nLen)
		{
			cCharacter = (unsigned char)pBuffer[nIndex];
			//计算出当前元素的所占字节数nByteCount和在显示画面上所占宽度nCurCharLen
			if (cCharacter == KTC_COLOR || cCharacter == KTC_BORDER_COLOR)
			{
			    nByteCount  = 4;
				nCurCharLen = 0;
			}
			else if (cCharacter == KTC_COLOR_RESTORE && cCharacter == KTC_BORDER_RESTORE)
			{
				nByteCount  = 1;
				nCurCharLen = 0;
			}
			else if (cCharacter == KTC_INLINE_PIC)
			{
				nByteCount  = 3;
				if(g_pIInlinePicSink->GetPicSize(
					*((unsigned short *)(pBuffer + nIndex + 1)), nWidth, nHeight))
				{
					nCurCharLen = ((nWidth * 2 + nFontSize - 1) /  nFontSize);
				}
				else
					nCurCharLen = 0;
			}
			else
			{
				nByteCount  = LOC_GetCharacterWide(cCharacter);
				nCurCharLen = nByteCount;
			}

			//如果超出缓冲区，就停止吧
			if(nIndex + nByteCount > nCount)
				break;
			//如果宽度还没超过要求宽度
			if(nLenTemp + nCurCharLen < nLen)
			{
				nLenTemp += nCurCharLen;
		        nIndex   += nByteCount;
			}
			//如果宽度等于要求宽度了
			else if(nLenTemp + nCurCharLen == nLen)
			{
				nLenTemp += nCurCharLen;
				nIndex   += nByteCount;
				break;
			}
			//这里就是超过了
			else
			{
				nLenTemp = bLess ? nLenTemp : (nLenTemp + nCurCharLen);
				nIndex   = bLess ? nIndex   : (nIndex + nByteCount);
				break;
			}
		}
	}
	nLen = nLenTemp;
	return nIndex;
}

//对已经编码的文本，指定的前段缓冲区中控制符，对后面的输出产生效果影响
C_ENGINE_API
int TGetEncodedTextEffectCtrls(const char* pBuffer, int nSkipCount, KTP_CTRL& Ctrl0, KTP_CTRL& Ctrl1)
{
	int nIndex = 0;
	Ctrl0.cCtrl = Ctrl1.cCtrl = KTC_INVALID;
	if (pBuffer)
	{
		KTP_CTRL PreCtrl0, PreCtrl1;
		PreCtrl0.cCtrl = PreCtrl1.cCtrl = KTC_INVALID;

		while(nIndex < nSkipCount)
		{
			unsigned char cCharacter = pBuffer[nIndex];
			if (cCharacter == KTC_COLOR)
			{
				PreCtrl0  =  Ctrl0;
				*(int*)(&Ctrl0) = *(int*)(pBuffer + nIndex);
				nIndex += 4;				
			}
			else if (cCharacter == KTC_BORDER_COLOR)
			{
				PreCtrl1  =  Ctrl1;
				*(int*)(&Ctrl1) = *(int*)(pBuffer + nIndex);
				nIndex += 4;
			}
			else if(cCharacter == KTC_COLOR_RESTORE)
			{
				Ctrl0 = PreCtrl0;
				nIndex ++;
			}
			else if(cCharacter == KTC_BORDER_RESTORE)
			{
				Ctrl1 = PreCtrl1;
				nIndex ++;
			}
			else
				nIndex += LOC_GetCharacterWide(cCharacter);
		}
	}
	return nIndex;
}
