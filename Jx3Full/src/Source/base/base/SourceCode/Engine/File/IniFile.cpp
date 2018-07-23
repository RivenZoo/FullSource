//---------------------------------------------------------------------------
// Sword3 Engine (c) 1999-2004 by Kingsoft
// Date:	2000.08.08
// Code:	WangWei(Daphnis), Wuyue(Wooy)
// Desc:	Ini File Operation Class

// 注意:   对于数据读取,有的接口上不能传入默认值,则如果不存在数据可供读取,
//			则保持原传入空间中的值不变.

//---------------------------------------------------------------------------
#include "Precompile.h"
#include "KGPublic.h"
#include "KGCRT.h"
#include "File.h"
#include "IniFile.h"
#include "KSG_StringProcess.h"

extern int kg_atoi (const char *str);

#define COPY_SECTION_AND_ADD_BOUND(d, s)	\
{											\
	if (s[0] != '[')						\
	{										\
		d[0] = '[';							\
		strcpy(&d[1], s);					\
		strcat(&d[1], "]");					\
	}										\
	else									\
	{										\
		strcpy(d, s);						\
	}										\
}

#define COPY_SECTION_AND_REMOVE_BOUND(d, s)	\
{											\
	int nSecLen = strlen(s);				\
	if (s[0] == '[' && s[nSecLen-1] == ']')	\
	{										\
		strncpy(d, &s[1], nSecLen-2);		\
		d[nSecLen-2] = 0;					\
	}										\
	else									\
	{										\
		strcpy(d, s);						\
	}										\
}

KRecycleBin<KIniFile, 4, RBAFM_NEW_DELETE>	KIniFile::ms_Recycle;     /// 类模板中的静态成员变量

C_ENGINE_API IIniFile*
g_OpenIniFile(const char* FileName, int ForceUnpakFile/* = false*/, int ForWrite/* = false*/)
{
	KIniFile*	pIni = NULL;
	IFile*		pFile = g_OpenFile(FileName, ForceUnpakFile, ForWrite);

	if (pFile)
	{
		pIni = KIniFile::New();
		if (pIni)
		{
			if (!pIni->LoadData(pFile))
			{
				pIni->Release();
				pIni = NULL;
			}
		}
		pFile->Release();
		pFile = NULL;
	}

	if (pIni == NULL && ForWrite)
		pIni = KIniFile::New();
	return pIni;
}

ENGINE_API bool g_OpenFile(IIniFile** ppIniFile, const char* FileName, int ForceUnpakFile /* = false */, int ForWrite /* = false */)
{
	*ppIniFile = g_OpenIniFile(FileName, ForceUnpakFile, ForWrite);
	return (*ppIniFile != NULL);
}

C_ENGINE_API IIniFile* g_CreateIniFile()
{
	return KIniFile::New();
}

//---------------------------------------------------------------------------
// 函数:	KIniFile
// 功能:	购造函数
//---------------------------------------------------------------------------
KIniFile::KIniFile()
{
	ZeroMemory(&m_Header, sizeof(SECNODE));
	m_Offset = 0;
}

//---------------------------------------------------------------------------
// 函数:	~KIniFile
// 功能:	析造函数
//---------------------------------------------------------------------------
KIniFile::~KIniFile()
{
	Clear();
}

//构造一个空的KIniFile对象
KIniFile* KIniFile::New()
{
    return ms_Recycle.New();
}

//---------------------------------------------------------------------------
// 功能:	加载一个INI文件
// 返回:	1 成功,  0	失败
//---------------------------------------------------------------------------
int KIniFile::LoadData(IFile* pFile)
{
	assert(pFile);
	Clear();

	int				nResult = false;
	BYTE*			pBuffer = NULL;
	unsigned long	uSize = pFile->Size();

	pBuffer = new BYTE[uSize + 4];	//文件有可能要补0之类的，如果是文件原大小有可能会越界
	memset(pBuffer, 0, sizeof(uSize + 4));
	if (pBuffer)
	{
		if (pFile->Read(pBuffer, uSize) == uSize)
		{
			CreateIniLink(pBuffer, uSize);
			nResult = true;
		}
	}
	SAFE_DELETE_ARRAY(pBuffer);
	return nResult;
}

//---------------------------------------------------------------------------
// 函数:	Save
// 功能:	保存当前的INI文件
// 返回:	1 成功, 0失败
//---------------------------------------------------------------------------
int KIniFile::Save(const char* FileName)
{
	int			nResult         = false;
	IFile*		piFile          = NULL;
	SECNODE*	SecNode         = m_Header.pNextNode;
	KEYNODE*	KeyNode         = NULL;
    DWORD       dwStringLen     = 0;
    DWORD       dwWriteSize     = 0;
    const char  cszNewLine[3]   = "\r\n";

    piFile = g_CreateFile(FileName);
    KG_PROCESS_ERROR(piFile);

	while (SecNode != NULL)
	{
		dwStringLen = (DWORD)strlen(SecNode->pSection);
		dwWriteSize = piFile->Write(SecNode->pSection, dwStringLen);
		KG_PROCESS_ERROR(dwWriteSize == dwStringLen);
		dwWriteSize = piFile->Write(cszNewLine, 2);
		KG_PROCESS_ERROR(dwWriteSize == 2);

		KeyNode = SecNode->RootNode.pNextNode;
		while (KeyNode != NULL)
		{
			dwStringLen = (DWORD)strlen(KeyNode->pKey);
			dwWriteSize = piFile->Write(KeyNode->pKey, dwStringLen);
			KG_PROCESS_ERROR(dwWriteSize == dwStringLen);
			dwWriteSize = piFile->Write("=", 1);
			KG_PROCESS_ERROR(dwWriteSize == 1);
			dwStringLen = (DWORD)strlen(KeyNode->pValue);
			dwWriteSize = piFile->Write(KeyNode->pValue, dwStringLen);
			KG_PROCESS_ERROR(dwWriteSize == dwStringLen);
			dwWriteSize = piFile->Write(cszNewLine, 2);
			KG_PROCESS_ERROR(dwWriteSize == 2);
			KeyNode = KeyNode->pNextNode;
		}
		dwWriteSize = piFile->Write(cszNewLine, 2);
		KG_PROCESS_ERROR(dwWriteSize == 2);
		SecNode = SecNode->pNextNode;
	}
	nResult = true;
Exit0:
	KG_COM_RELEASE(piFile);
	return nResult;
}

//---------------------------------------------------------------------------
// 函数:	Clear
// 功能:	清除INI文件的内容
//---------------------------------------------------------------------------
void KIniFile::Clear()
{
	ReleaseIniLink();
}

//---------------------------------------------------------------------------
// 函数:	ReadLine
// 功能:	读取INI文件的一行
// 参数:	Buffer	缓存
//			Szie	长度
// 返回:	true		成功
//			false		失败
//---------------------------------------------------------------------------
int KIniFile::ReadLine(char* Buffer,long Size)
{
	if (m_Offset >= Size)
	{
		return false;
	}
	while (Buffer[m_Offset] != 0x0D && Buffer[m_Offset] != 0x0A)
	{
		m_Offset++;
		if (m_Offset >= Size)
			break;
	}
	Buffer[m_Offset] = 0;
  /// 保证Buffer指向下一行的开始
	if (Buffer[m_Offset] == 0x0D && Buffer[m_Offset + 1] == 0x0A)
		m_Offset += 2;
	else
		m_Offset += 1;	//linux [wxb 2003-7-29]
	return true;
}

//---------------------------------------------------------------------------
// 函数:	IsKeyChar
// 功能:	判断一个字符是否为字母
// 参数:	ch		要判断的字符	
// 返回:	true	是字母
//			false	不是字母
// 注释：	不支持中文作Key名，但是可以做Section名
//---------------------------------------------------------------------------
int KIniFile::IsKeyChar(char ch)
{
	if (((ch >= 'A') && (ch <= 'Z')) ||
		((ch >= 'a') && (ch <= 'z')) ||
		((ch >= '0') && (ch <= '9')) ||
		(ch == '$') || (ch == '.') ||
		(ch == '_') || (ch == '-'))
	{
		return true;
	}
	return false;
}

//---------------------------------------------------------------------------
// 函数:	CreateIniLink
// 功能:	创建Ini链表
// 参数:	pBuffer		缓存
//			nBufLen		长度
//---------------------------------------------------------------------------
void KIniFile::CreateIniLink(void* pBuffer, long nBufLen)
{
	char* lpBuffer = (char*)pBuffer;
	char* lpString = NULL;
	char* lpValue  = NULL;
	char  szSection[64] = "[MAIN]";

	m_Offset = 0;
	while (m_Offset < nBufLen)
	{
		lpString = &lpBuffer[m_Offset];
		if (!ReadLine(lpBuffer, nBufLen))
			break;
		if (IsKeyChar(*lpString))
		{
			lpValue = SplitKeyValue(lpString);
			if (lpValue)
				SetKeyValue(szSection, lpString, lpValue);
		}
		else if (*lpString == '[')
		{
			g_StrCpyLen(szSection, lpString, sizeof(szSection));
		}
	}
}

//---------------------------------------------------------------------------
// 函数:	ReleaseIniLink()
// 功能:	释放Ini链表
//---------------------------------------------------------------------------
void KIniFile::ReleaseIniLink()
{
	SECNODE* pThisSec = &m_Header;
	SECNODE* pNextSec = pThisSec->pNextNode;
	KEYNODE* pThisKey = NULL;
	KEYNODE* pNextKey = NULL;

	while (pNextSec != NULL)
	{
		pThisSec = pNextSec->pNextNode;
		pThisKey = &pNextSec->RootNode;
		pNextKey = pThisKey->pNextNode;
		while (pNextKey != NULL)
		{
			pThisKey = pNextKey->pNextNode;
			SAFE_DELETE_ARRAY(pNextKey->pKey);
			SAFE_DELETE_ARRAY(pNextKey->pValue);
			SAFE_DELETE(pNextKey);
			pNextKey = pThisKey;
		}
		SAFE_DELETE_ARRAY(pNextSec->pSection);
		SAFE_DELETE_ARRAY(pNextSec);
		pNextSec = pThisSec;
	}
	m_Header.pNextNode = NULL;
}

//---------------------------------------------------------------------------
// 函数:	SplitKeyValue
// 功能:	分割Key和Value
// 参数:	pString		Key=Value
// 返回:	指向Value
//---------------------------------------------------------------------------
char* KIniFile::SplitKeyValue(char* pString)
{
	char* pValue = pString;
	while (*pValue)
	{
		if (*pValue == '=')
		{
			*pValue = 0;
			return pValue + 1;    /// = 后面没有空格
		}
		pValue++;
	}
	return NULL;
}

//---------------------------------------------------------------------------
// 函数:	String2Id
// 功能:	字符串转成32 bits ID
// 参数:	pString		字符串
// 返回:	32 bits ID
//---------------------------------------------------------------------------
unsigned int KIniFile::String2Id(const char* pString)
{
	unsigned int Id = 0;
	for (int i=0; pString[i]; i++)
	{
		Id = (Id + (i+1) * pString[i]) % 0x8000000b * 0xffffffef;
	}
	return Id ^ 0x12345678;
}

//---------------------------------------------------------------------------
// 函数:	IsSectionExist
// 功能:	Section是否存在
// 参数:	pSection	节的名字
// 返回:	int
//---------------------------------------------------------------------------
int KIniFile::IsSectionExist(const char* pSection)
{
	// setup section name
	char szSection[64];
	COPY_SECTION_AND_ADD_BOUND(szSection, pSection);
	
	// search for the matched section
	SECNODE* pSecNode = m_Header.pNextNode;
	unsigned int dwID = String2Id(szSection);
	while (pSecNode != NULL)
	{
		if (dwID == pSecNode->dwID)
			return true;
		pSecNode = pSecNode->pNextNode;
	}
	
	return false;
}

//---------------------------------------------------------------------------
// 函数:	EraseSection
// 功能:	清除一个Section的内容
// 参数:	pSection	节的名字
//---------------------------------------------------------------------------
void KIniFile::EraseSection(const char* pSection)
{
	// setup section name
	char szSection[64];
	COPY_SECTION_AND_ADD_BOUND(szSection, pSection);

	// search for the matched section
	unsigned int dwID = String2Id(szSection);
	SECNODE* pPreSec = &m_Header;
	SECNODE* pSecNode;
	while((pSecNode = pPreSec->pNextNode) != NULL)
	{
		if (dwID == pSecNode->dwID)
			break;
		pPreSec = pSecNode;
	}

	// if no such section found
	if (pSecNode == NULL)
		return;
	pPreSec->pNextNode = pSecNode->pNextNode;

	// erase all key in the section
	KEYNODE* pThisKey = &pSecNode->RootNode;
	KEYNODE* pNextKey = pThisKey->pNextNode;
	while (pNextKey != NULL)
	{
		pThisKey = pNextKey->pNextNode;
		SAFE_DELETE_ARRAY(pNextKey->pKey);
		SAFE_DELETE_ARRAY(pNextKey->pValue);
		SAFE_DELETE(pNextKey);
		pNextKey = pThisKey;
	}
	pSecNode->RootNode.pNextNode = NULL;
	SAFE_DELETE_ARRAY(pSecNode->pSection);
	SAFE_DELETE(pSecNode);
}

//---------------------------------------------------------------------------
// 函数:	EraseKey
// 功能:	清除Section的下一个Key的内容
// 参数:	pSection	节的名字
//---------------------------------------------------------------------------
void	KIniFile::EraseKey(const char* lpSection, const char* lpKey)
{
	// setup section name
	char szSection[64];
	COPY_SECTION_AND_ADD_BOUND(szSection, lpSection);

	// search for the matched section
	SECNODE* pSecNode = m_Header.pNextNode;
	unsigned int dwID = String2Id(szSection);
	while (pSecNode != NULL)
	{
		if (dwID == pSecNode->dwID)
		{
			break;
		}
		pSecNode = pSecNode->pNextNode;
	}

	// if no such section found
	if (pSecNode == NULL)
	{
		return;
	}

	KEYNODE* pThisKey = &pSecNode->RootNode;
	KEYNODE* pNextKey = pThisKey->pNextNode;
	dwID = String2Id(lpKey);
	while (pNextKey != NULL)
	{
		if (pNextKey->dwID == dwID)
		{
			pThisKey->pNextNode = pNextKey->pNextNode;
			SAFE_DELETE_ARRAY(pNextKey->pKey);
			SAFE_DELETE_ARRAY(pNextKey->pValue);
			SAFE_DELETE(pNextKey);
			if (pSecNode->RootNode.pNextNode == NULL)
				EraseSection(szSection);
			return;
		}
		pThisKey = pNextKey;
		pNextKey = pNextKey->pNextNode;
	}
}

//---------------------------------------------------------------------------
// 函数:	SetKeyValue
// 功能:	设置Key的Value
// 参数:	pSection	节名
//			pKey		建名
//			pValue		建值
// 返回:	true－成功 false－失败
//---------------------------------------------------------------------------
int KIniFile::SetKeyValue(
	const char*	pSection,
	const char*	pKey,
	const char*	pValue)
{
	int		nLen;
	unsigned int	dwID;

	// setup section name
	char szSection[64];
	COPY_SECTION_AND_ADD_BOUND(szSection, pSection);

	// search for the matched section
	SECNODE* pThisSecNode = &m_Header;
	SECNODE* pNextSecNode = pThisSecNode->pNextNode;
	dwID = String2Id(szSection);
	while (pNextSecNode != NULL)
	{
		if (dwID == pNextSecNode->dwID)
		{
			break;
		}
		pThisSecNode = pNextSecNode;
		pNextSecNode = pThisSecNode->pNextNode;
	}

	// if no such section found create a new section
	if (pNextSecNode == NULL)
	{
		nLen = strlen(szSection) + 1;
		pNextSecNode = new SECNODE;
		pNextSecNode->pSection = new char[nLen];
		memcpy(pNextSecNode->pSection, szSection, nLen);
		pNextSecNode->dwID = dwID;
		pNextSecNode->RootNode.pNextNode = NULL;
		pNextSecNode->pNextNode = NULL;
		pThisSecNode->pNextNode = pNextSecNode;
	}

	// search for the same key
	KEYNODE* pThisKeyNode = &pNextSecNode->RootNode;
	KEYNODE* pNextKeyNode = pThisKeyNode->pNextNode;
	dwID = String2Id(pKey);
	while (pNextKeyNode != NULL)
	{
		if (dwID == pNextKeyNode->dwID)
		{
			break;
		}
		pThisKeyNode = pNextKeyNode;
		pNextKeyNode = pThisKeyNode->pNextNode;
	}

	// if no such key found create a new key
	if (pNextKeyNode == NULL)
	{
		pNextKeyNode = new KEYNODE;

		nLen = strlen(pKey) + 1;
		pNextKeyNode->pKey = new char[nLen];
		memcpy(pNextKeyNode->pKey, (void*)pKey, nLen);

		nLen = strlen(pValue) + 1;
		pNextKeyNode->pValue = new char[nLen];
		memcpy(pNextKeyNode->pValue, (void*)pValue, nLen);

		pNextKeyNode->dwID = dwID;
		pNextKeyNode->pNextNode = NULL;
		pThisKeyNode->pNextNode = pNextKeyNode;
	}
	// replace the old value with new
	else
	{
		SAFE_DELETE_ARRAY(pNextKeyNode->pValue);
		nLen = strlen(pValue) + 1;
		pNextKeyNode->pValue = new char[nLen];
		memcpy(pNextKeyNode->pValue, (void*)pValue, nLen);
	}
	return true;
}

//---------------------------------------------------------------------------
// 函数:	GetKeyValue
// 功能:	取得Key的Value
// 参数:	pSection	节名
//			pKey		建名
//			pValue		建值
// 返回:	true－成功 false－失败
//---------------------------------------------------------------------------
int	KIniFile::GetKeyValue(const char* pSection,const char* pKey,char* pValue,unsigned int dwSize)
{
	unsigned int	dwID;

	// setup section name
	char szSection[64];
	COPY_SECTION_AND_ADD_BOUND(szSection, pSection);

	// search for the matched section
	SECNODE* pSecNode = m_Header.pNextNode;
	dwID = String2Id(szSection);
	while (pSecNode != NULL)
	{
		if (dwID == pSecNode->dwID)
		{
			break;
		}
		pSecNode = pSecNode->pNextNode;
	}

	// if no such section founded
	if (pSecNode == NULL)
	{
		return false;
	}

	// search for the same key
	KEYNODE* pKeyNode = pSecNode->RootNode.pNextNode;
	dwID = String2Id(pKey);
	while (pKeyNode != NULL)
	{
		if (dwID == pKeyNode->dwID)
		{
			break;
		}
		pKeyNode = pKeyNode->pNextNode;
	}

	// if no such key found
	if (pKeyNode == NULL)
	{
		return false;
	}

	// copy the value of the key
	g_StrCpyLen(pValue, pKeyNode->pValue, dwSize);
	return true;
}

//---------------------------------------------------------------------------
// 函数:	GetString
// 功能:	读取一个字符串
// 参数:	lpSection		节名
//			lpKeyName		建名
//			lpDefault		缺省值
//			lpRString		返回值
//			dwSize			返回字符串的最大长度
//---------------------------------------------------------------------------
int KIniFile::GetString(
	const char* lpSection,		// points to section name
	const char* lpKeyName,		// points to key name
	const char* lpDefault,		// points to default string
	char* lpRString,		// points to destination buffer
	unsigned int dwSize			// size of string buffer
	)
{
	if (GetKeyValue(lpSection, lpKeyName, lpRString, dwSize))
		return true;
	g_StrCpyLen(lpRString, lpDefault, dwSize);
	return false;
}

//---------------------------------------------------------------------------
// 函数:	GetInteger
// 功能:	读取一个整数
// 参数:	lpSection		节名
//			lpKeyName		建名
//			nDefault		缺省值
//			pnValue			返回值
//---------------------------------------------------------------------------
int KIniFile::GetInteger(
	const char* lpSection,		// points to section name
	const char* lpKeyName,		// points to key name
	int   nDefault,			// default value
	int   *pnValue          // points to value
	)
{
	char Buffer[32];
	if (GetKeyValue(lpSection, lpKeyName, Buffer, sizeof(Buffer)))
	{
		*pnValue = kg_atoi(Buffer);
		return true;
	}
	else
	{
		*pnValue = nDefault;
		return false;
	}
}
//---------------------------------------------------------------------------
// 函数:	GetInteger2
// 功能:	读取2个整数，整数之间用逗号分割。
// 参数:	lpSection		节名
//			lpKeyName		建名
//			pnValue1		返回值1
//			pnValue2		返回值2
// 返回:	void
//---------------------------------------------------------------------------
int KIniFile::GetInteger2(
	const char* lpSection,		// points to section name
	const char* lpKeyName,		// points to key name
	int   *pnValue1,		// value 1
	int   *pnValue2			// value 2
	)
{
	char  Buffer[64];
	if (GetKeyValue(lpSection, lpKeyName, Buffer, sizeof(Buffer)))
	{
		char* pSplit = strchr(Buffer, ',');
		if (pSplit)
		{
			*pSplit = '\0';
			*pnValue2 = kg_atoi(pSplit + 1);
		}
		*pnValue1 = kg_atoi(Buffer);
		return (pSplit != NULL);
	}
	return false;
}

//---------------------------------------------------------------------------
// 函数:	GetFloat
// 功能:	读取1个浮点数
// 参数:	lpSection		节名
//			lpKeyName		建名
//			fDefault		缺省值
//			pfValue			返回值
// 返回:	
//---------------------------------------------------------------------------
int KIniFile::GetFloat(
	const char*	lpSection,		// points to section name
	const char*	lpKeyName,		// points to key name
	float	fDefault,		// default value
	float	*pfValue        // return value
	)
{
	char Buffer[32];
	if (GetKeyValue(lpSection, lpKeyName, Buffer, sizeof(Buffer)))
	{
		*pfValue = (float)atof(Buffer);
		return true;
	}
	else
	{
		*pfValue = fDefault;
		return false;
	}
}
//---------------------------------------------------------------------------
// 函数:	GetFloat2
// 功能:	读取2个浮点数，之间用逗号分割。
// 参数:	lpSection		节名
//			lpKeyName		建名
//			pfValue1		返回值1
//			pfValue2		返回值2
// 返回:	
//---------------------------------------------------------------------------
int KIniFile::GetFloat2(
	const char* lpSection,		// points to section name
	const char* lpKeyName,		// points to key name
	float *pfValue1,		// value 1
	float *pfValue2			// value 2
	)
{
	char  Buffer[64];
	if (GetKeyValue(lpSection, lpKeyName, Buffer, sizeof(Buffer)))
	{
		char* pSplit = strchr(Buffer, ',');
		if (pSplit)
		{
			*pSplit = '\0';
			*pfValue2 = (float)atof(pSplit + 1);
		}
		*pfValue1 = (float)atof(Buffer);
		return (pSplit != NULL);
	}
	return false;
}

//---------------------------------------------------------------------------
// 函数:	GetStruct
// 功能:	读取一个结构
// 参数:	lpSection		节名
//			lpKeyName		建名
//			lpStruct		缓存
//			dwSize			缓存大小
// 返回:	void
//---------------------------------------------------------------------------
int KIniFile::GetStruct(
	const char*	lpSection,	// pointer to section name
	const char*	lpKeyName,	// pointer to key name
	void*	lpStruct,		// pointer to buffer that contains data to add
	unsigned int	dwSize	// size, in bytes, of the buffer
	)
{
	char    Buffer[2048 * 2];
	unsigned char*	lpByte;
	unsigned char	ah,al;

	if (!GetKeyValue(lpSection, lpKeyName, Buffer, sizeof(Buffer)))
		return false;
	lpByte = (unsigned char*)lpStruct;
	int len = strlen(Buffer);
	if (len != (int)dwSize * 2)
		return false;
	for (int i = 0; i < len; i += 2)
	{
		// get byte high
		ah = Buffer[i];
		if ((ah >= 48) && (ah <= 57))
			ah = (unsigned char)(ah - 48);
		else
			ah = (unsigned char)(ah - 65 + 10);
		// get byte low
		al = Buffer[i+1];
		if ((al >= 48) && (al <= 57))
			al = (unsigned char)(al - 48);
		else
			al = (unsigned char)(al - 65 + 10);
		// set struct bye
		*lpByte++ = (unsigned char)(ah * 16 + al);    /// 将0xFFFFFFFF转换成十进制的？ eg：“A302B1” ->13 2 12
	}
	return true;
}

//---------------------------------------------------------------------------
// 函数:	WriteString
// 功能:	写入一个字符串
// 参数:	lpSection		节名
//			lpKeyName		建名
//			lpString		字符串
//---------------------------------------------------------------------------
int KIniFile::WriteString(
	const char*	lpSection,		// pointer to section name
	const char*	lpKeyName,		// pointer to key name
	const char*	lpString		// pointer to string to add
	)
{
	return SetKeyValue(lpSection, lpKeyName, lpString);
}

//---------------------------------------------------------------------------
// 函数:	WriteInteger
// 功能:	写入一个整数
// 参数:	lpSection		节名
//			lpKeyName		建名
//			nValue			整数
//---------------------------------------------------------------------------
int KIniFile::WriteInteger(
	const char*	lpSection,		// pointer to section name
	const char*	lpKeyName,		// pointer to key name
	int 	nValue			// Integer to write
	)
{
	char Buffer[32];
	sprintf(Buffer, "%d", nValue);
	return SetKeyValue(lpSection, lpKeyName, Buffer);
}
//---------------------------------------------------------------------------
// 函数:	WriteInteger2
// 功能:	写入2个整数
// 参数:	lpSection		节名
//			lpKeyName		建名
//			nValue1			整数1
//			nValue2			整数2
//---------------------------------------------------------------------------
int KIniFile::WriteInteger2(
	const char*	lpSection,		// pointer to section name
	const char*	lpKeyName,		// pointer to key name
	int 	Value1,			// value 1 to write
	int		Value2			// value 2 to write
	)
{
	char Buffer[64];
	sprintf(Buffer, "%d,%d", Value1, Value2);
	return SetKeyValue(lpSection, lpKeyName, Buffer);
}

//---------------------------------------------------------------------------
// 函数:	WriteFloat
// 功能:	写入1个浮点数
// 参数:	lpSection		节名
//			lpKeyName		建名
//			fValue			浮点数
//---------------------------------------------------------------------------
int KIniFile::WriteFloat(
	const char*	lpSection,		// pointer to section name
	const char*	lpKeyName,		// pointer to key name
	float	fValue			// Integer to write
	)
{
	char Buffer[32];
	sprintf(Buffer,"%f",fValue);
	return SetKeyValue(lpSection, lpKeyName, Buffer);
}
//---------------------------------------------------------------------------
// 函数:	WriteFloat2
// 功能:	写入2个浮点数
// 参数:	lpSection		节名
//			lpKeyName		建名
//			fValue1			浮点数1
//			fValue2			浮点数2
// 返回:	void
//---------------------------------------------------------------------------
int KIniFile::WriteFloat2(
	const char*	lpSection,		// pointer to section name
	const char*	lpKeyName,		// pointer to key name
	float 	fValue1,		// value 1 to write
	float	fValue2			// value 2 to write
	)
{
	char Buffer[64];
	sprintf(Buffer, "%f,%f", fValue1, fValue2);
	return SetKeyValue(lpSection, lpKeyName, Buffer);
}

//---------------------------------------------------------------------------
// 函数:	WriteFloat2
// 功能:	写入一个结构
// 参数:	lpSection		节名
//			lpKeyName		建名
//			lpStruct		结构
//			dwSize			结构大小
//---------------------------------------------------------------------------
int KIniFile::WriteStruct(
	const char*	lpSection,		// pointer to section name
	const char*	lpKeyName,		// pointer to key name
	void*	lpStruct,		// pointer to buffer that contains data to add
	unsigned int 	dwSize			// size, in bytes, of the buffer
	)
{
	char    Buffer[2048 * 2];
	char*	lpBuff = Buffer;
	unsigned char*	lpByte;

	if (dwSize >= 2048)
		return false;

	lpByte = (unsigned char*) lpStruct;
	for (unsigned int i=0; i<dwSize; i++)
	{
		sprintf(lpBuff,"%02X",*lpByte);
		lpBuff++;
		lpBuff++;
		lpByte++;
	}
	return SetKeyValue(lpSection, lpKeyName, Buffer);
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
int KIniFile::GetNextSection(const char* pSection, char* pNextSection)
{
	
	if (!pSection[0])	//	传入参数为""时就是取第一个Section
	{
		if (!m_Header.pNextNode)
			return false;
		else
		{
			COPY_SECTION_AND_REMOVE_BOUND(pNextSection, m_Header.pNextNode->pSection);
			return true;
		}
	}
	else
	{
		char szSection[64];
		COPY_SECTION_AND_ADD_BOUND(szSection, pSection);

		//	查找参数给定的Section
		SECNODE* pThisSecNode = &m_Header;
		SECNODE* pNextSecNode = pThisSecNode->pNextNode;
		unsigned int dwID = String2Id(szSection);
		while (pNextSecNode != NULL)
		{
			if (dwID == pNextSecNode->dwID)
			{
				break;
			}
			pThisSecNode = pNextSecNode;
			pNextSecNode = pThisSecNode->pNextNode;
		}
		//	没有这个Section，无所谓下一个
		if (!pNextSecNode)
		{
			return false;
		}
		else
		{
			//	参数给定的Section已经是最后一个了
			if (!pNextSecNode->pNextNode)
			{
				return false;
			}
			else	
			{
				COPY_SECTION_AND_REMOVE_BOUND(pNextSection, pNextSecNode->pNextNode->pSection);
				return true;
			}
		}
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
int KIniFile::GetNextKey(const char* pSection, const char* pKey, char* pNextKey)
{
	char szSection[64];
	COPY_SECTION_AND_ADD_BOUND(szSection, pSection);

	//	查找参数给定的Section
	SECNODE* pThisSecNode = &m_Header;
	SECNODE* pNextSecNode = pThisSecNode->pNextNode;
	unsigned int dwID = String2Id(szSection);
	while (pNextSecNode != NULL)
	{
		if (dwID == pNextSecNode->dwID)
		{
			break;
		}
		pThisSecNode = pNextSecNode;
		pNextSecNode = pThisSecNode->pNextNode;
	}
	//	没有这个Section，无所谓取Key
	if (!pNextSecNode)
	{
		return false;
	}

	KEYNODE* pThisKeyNode = &pNextSecNode->RootNode;
	KEYNODE* pNextKeyNode = pThisKeyNode->pNextNode;

	//	Key给的参数为""的话，取第一个Key
	if (!pKey[0])
	{
		//	没有Key，返回失败
		if (!pNextKeyNode->pKey)
		{
			return false;
		}
		else
		{
			strcpy(pNextKey, pNextKeyNode->pKey);
			return true;
		}
	}

	dwID = String2Id(pKey);
	while(pNextKeyNode != NULL)
	{
		if (dwID == pNextKeyNode->dwID)
		{
			break;
		}
		pThisKeyNode = pNextKeyNode;
		pNextKeyNode = pThisKeyNode->pNextNode;
	}
	//	找不到所给的Key，无所谓下一个
	if (!pNextKeyNode)
	{
		return false;
	}
	//	参数给定的Key已经是最后一个了
	if (!pNextKeyNode->pNextNode)
	{
		return false;
	}
	else
	{
		strcpy(pNextKey, pNextKeyNode->pNextNode->pKey);
		return true;
	}
}

int	KIniFile::GetSectionCount()
{
	int			nCount = 0;
	SECNODE*	pNextSecNode = m_Header.pNextNode;
	while (pNextSecNode)
	{
		nCount++;
		pNextSecNode = pNextSecNode->pNextNode;		
	}
	return nCount;
}

//获取多个int值
int KIniFile::GetMultiInteger(const char*	lpSection,
					const char* lpKeyName, int *pValues, int nCount)
{
	int	nReadCount = 0;
	if (nCount > 0 && nCount <= INI_MAX_SUPPORT_MULTI_VALUE_COUNT)
	{
		char  Buffer[256];
		if (GetKeyValue(lpSection, lpKeyName, Buffer, sizeof(Buffer)))
		{
			const char *pcszTemp = Buffer;
			do
			{
				pValues[nReadCount++] = KSG_StringGetInt(&pcszTemp, 0);
			}while((nReadCount < nCount) && KSG_StringSkipSymbol(&pcszTemp, ','));
		}
	}
	return nReadCount;
}

//获取多个long值
int KIniFile::GetMultiLong(const char* lpSection,
					const char*	lpKeyName, long *pValues, int nCount)
{
	int	nReadCount = 0;
	if (nCount > 0 && nCount <= INI_MAX_SUPPORT_MULTI_VALUE_COUNT)
	{
		char  Buffer[384];
		if (GetKeyValue(lpSection, lpKeyName, Buffer, sizeof(Buffer)))
		{
			char* pcszTemp = Buffer;
			do
			{
				char* pSplit = strchr(pcszTemp, ',');
				if (pSplit)
					*pSplit = '\0';
				pValues[nReadCount++] = atol(pcszTemp);
				pcszTemp = pSplit ? (pSplit + 1) : NULL;
			}while((nReadCount < nCount) && pcszTemp);
		}
	}
	return nReadCount;
}

int	KIniFile::GetMultiFloat(const char*	lpSection,
					const char*	lpKeyName, float *pValues, int nCount)
{
	int	nReadCount = 0;
	if (nCount > 0 && nCount <= INI_MAX_SUPPORT_MULTI_VALUE_COUNT)
	{
		char  Buffer[384];
		if (GetKeyValue(lpSection, lpKeyName, Buffer, sizeof(Buffer)))
		{
			char* pcszTemp = Buffer;
			do
			{
				char* pSplit = strchr(pcszTemp, ',');
				if (pSplit)
					*pSplit = '\0';
				pValues[nReadCount++] = (float)atof(pcszTemp);
				pcszTemp = pSplit ? (pSplit + 1) : NULL;
			}while((nReadCount < nCount) && pcszTemp);
		}
	}
	return nReadCount;
}

int	KIniFile::WriteMultiInteger(const char* lpSection,
					const char* lpKeyName, int *pValues, int nCount)
{
	if (nCount > 0 && nCount <= INI_MAX_SUPPORT_MULTI_VALUE_COUNT)
	{
		char Buffer[256];
		int	 nPos = sprintf(Buffer, "%d", *pValues);
		while(--nCount)
		{
			pValues++;
			Buffer[nPos++] = ',';
			nPos += sprintf(Buffer + nPos, "%d", *pValues);
		}
		return SetKeyValue(lpSection, lpKeyName, Buffer);
	}
	return false;
}

int	KIniFile::WriteMultiLong(const char* lpSection,
					const char* lpKeyName, long *pValues, int nCount)
{
	if (nCount > 0 && nCount <= INI_MAX_SUPPORT_MULTI_VALUE_COUNT)
	{
		char	Buffer[384];
		const char*	pFormat = (sizeof(long) == 8) ? "%I64d" : "%d";
		int	 nPos = sprintf(Buffer, pFormat, *pValues);
		while(--nCount)
		{
			pValues++;
			Buffer[nPos++] = ',';
			nPos += sprintf(Buffer + nPos, pFormat, *pValues);
		}
		return SetKeyValue(lpSection, lpKeyName, Buffer);
	}
	return false;
}

int	KIniFile::WriteMultiFloat(const char* lpSection,
					const char* lpKeyName, float *pValues, int nCount)
{
	if (nCount > 0 && nCount <= INI_MAX_SUPPORT_MULTI_VALUE_COUNT)
	{
		char Buffer[384];
		int	 nPos = sprintf(Buffer, "%f", *pValues);
		while(--nCount)
		{
			pValues++;
			Buffer[nPos++] = ',';
			nPos += sprintf(Buffer + nPos, "%f", *pValues);
		}
		return SetKeyValue(lpSection, lpKeyName, Buffer);
	}
	return false;
}

int KIniFile::GetBool(const char* lpSection, const char* lpKeyName, int* pBool)
{
	char	Buffer[16];
	const char*	Value[]=
	{
		"true",	"false",
		"1",	"0",
		"yes",	"no"
	};

	int		nResult = false;
	if (GetKeyValue(lpSection, lpKeyName, Buffer, sizeof(Buffer)))
	{
		for (int i = 0; i < sizeof(Value) / sizeof(const char*); i++)
		{
#ifdef __linux
			if (!strcasecmp(Buffer, Value[i]))
#else
			if (!stricmp(Buffer, Value[i]))
#endif
			{
				*pBool = ((i % 2) == 0);
				nResult = true;
				break;
			}
		}
	}
	return nResult;
}

void KIniFile::Release()
{
	Clear();
	ms_Recycle.Delete(this);
}
