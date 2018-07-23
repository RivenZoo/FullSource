//---------------------------------------------------------------------------
// Sword3 Engine (c) 1999-2004 by Kingsoft
// File:	KPath.cpp
// Date:	2000.08.08
// Code:	WangWei(Daphnis)
// Desc:	File Path Utility
//---------------------------------------------------------------------------
#include "Precompile.h"
#ifdef WIN32
	#include <direct.h>
	#include <mbstring.h>
#else
	#include <unistd.h>
	#include <sys/stat.h>
#endif
#include "XPackList.h"

#ifdef LINUX
void strlwr(char* str)
{
	char c;
	for (int i = 0; 0 != (c = str[i]); i++)
	{
		if (c >= 'A' && c <= 'Z')
			str[i] = c + ('a' - 'A');
	}
}

#endif //#ifdef LINUX
//---------------------------------------------------------------------------
#ifdef WIN32
	static char s_szRootPath[MAX_PATH] = "C:";		// 启动路径
	static char s_szCurrPath[MAX_PATH] = "\\";		// 当前路径
	#define		PATH_SPLITTER		'\\'
	#define		PATH_SPLITTER_STR	"\\"
#else
	static char s_szRootPath[MAX_PATH] = "/";		// 启动路径
	static char s_szCurrPath[MAX_PATH] = "/";		// 当前路径
	#define		PATH_SPLITTER		'/'
	#define		PATH_SPLITTER_STR	"/"
#endif

int RemoveTwoPointPath(char* szPath, int nLength)
{
	int nRemove = 0;
	assert(szPath);

#ifdef WIN32
	const char* lpszOld = "\\..\\";
#else
	const char* lpszOld = "/../";
#endif

	char* lpszTarget = strstr(szPath, lpszOld);

	if (lpszTarget)
	{
		const char* lpszAfter = lpszTarget + 3;
		while(lpszTarget > szPath)
		{
			lpszTarget--;
			if ((*lpszTarget) == '\\' ||(*lpszTarget) == '/')
				break;
		}
		memmove(lpszTarget, lpszAfter, (nLength - (lpszAfter - szPath) + 1) * sizeof(char));
		nRemove = (int)(lpszAfter - lpszTarget);
		return RemoveTwoPointPath(szPath, nLength - nRemove);
	}

	return nLength - nRemove;
}

int RemoveOnePointPath(char* szPath, int nLength)
{
	int nRemove = 0;
	assert(szPath);
#ifdef WIN32
	const char* lpszOld = "\\.\\";
#else
	const char* lpszOld = "/./";
#endif
	char* lpszTarget = strstr(szPath, lpszOld);
	if (lpszTarget)
	{
		char* lpszAfter = lpszTarget + 2;
		memmove(lpszTarget, lpszAfter, (nLength - (lpszAfter - szPath) + 1) * sizeof(char));
		nRemove = (int)(lpszAfter - lpszTarget);
		return RemoveOnePointPath(szPath, nLength - nRemove);
	}

	return nLength - nRemove;
}

int RemoveAllPointPath(char* szPath, int nLength)
{
	return RemoveOnePointPath(szPath, RemoveTwoPointPath(szPath, nLength));
}

//---------------------------------------------------------------------------
// 功能:	设置程序的根路径
// 参数:	lpPathName	路径名
//---------------------------------------------------------------------------
C_ENGINE_API
void g_SetRootPath(const char* lpPathName)
{
	if (lpPathName)
		strcpy(s_szRootPath, lpPathName);
	else
		getcwd(s_szRootPath, MAX_PATH);

	// 去掉路径末尾的 '\'
	int len = (int)strlen(s_szRootPath);
	if (s_szRootPath[len - 1] == '\\' || s_szRootPath[len - 1] == '/')
		s_szRootPath[len - 1] = 0;
}

//---------------------------------------------------------------------------
// 函数:	GetRootPath
// 功能:	取得程序的根路径
// 参数:	lpPathName	路径名
//---------------------------------------------------------------------------
C_ENGINE_API
void g_GetRootPath(char* lpPathName)
{
	strcpy(lpPathName, s_szRootPath);
}
//---------------------------------------------------------------------------
// 函数:	SetFilePath
// 功能:	设置当前文件路径
// 参数:	lpPathName	路径名
// 返回:	void
//---------------------------------------------------------------------------
C_ENGINE_API
void g_SetFilePath(const char* lpPathName)
{
	// 去掉前面的 "\\"
	if (lpPathName[0] == '\\' ||lpPathName[0] == '/')
	{
		strcpy(s_szCurrPath, lpPathName + 1);
	}
	else
	{
		strcpy(s_szCurrPath, lpPathName);
	}

	// 末尾加上 "\\"
	int len = (int)strlen(s_szCurrPath);
	if (len > 0 && s_szCurrPath[len - 1] != '\\' && s_szCurrPath[len - 1] != '/')
	{
		s_szCurrPath[len] = PATH_SPLITTER;
		s_szCurrPath[len + 1] = 0;
	}
	RemoveAllPointPath(s_szCurrPath, len + 1);
#ifndef WIN32
	//'\\' -> '/' [wxb 2003-7-29]
	for (len = 0; s_szCurrPath[len]; len++)
	{
		if (s_szCurrPath[len] == '\\')
			s_szCurrPath[len] = '/';
	}
#endif
}

//---------------------------------------------------------------------------
// 函数:	GetFilePath
// 功能:	取得当前文件路径
// 参数:	lpPathName	路径名
// 返回:	void
//---------------------------------------------------------------------------
C_ENGINE_API
void g_GetFilePath(char* lpPathName)
{
	strcpy(lpPathName, s_szCurrPath);
}

//---------------------------------------------------------------------------
// 函数:	GetFullPath
// 功能:	取得文件的全路径名
// 参数:	lpPathName	路径名
//			lpFileName	文件名
// 返回:	void
//---------------------------------------------------------------------------
C_ENGINE_API
void g_GetFullPath(char* lpPathName, const char* lpFileName)
{
#ifdef WIN32
	if (lpFileName[1] == ':' ||	// 文件带有全路径
		(lpFileName[0] == '\\' && lpFileName[1] == '\\'))// 跳过有'\\'这种局域网路径
	{
		strcpy(lpPathName, lpFileName);
		return;
	}
#endif

	// 文件带有部分路径
	if (lpFileName[0] == '\\' || lpFileName[0] == '/')
	{
		strcpy(lpPathName, s_szRootPath);
		strcat(lpPathName, lpFileName);
		return;
	}

	// 当前路径为全路径
#ifdef WIN32
	if (s_szCurrPath[1] == ':')
	{
		strcpy(lpPathName, s_szCurrPath);
		strcat(lpPathName, lpFileName);
		return;
	}
#endif
	// 当前路径为部分路径
	strcpy(lpPathName, s_szRootPath);
	if(s_szCurrPath[0] != '\\' && s_szCurrPath[0] != '/')
	{
		strcat(lpPathName, PATH_SPLITTER_STR);
	}
	strcat(lpPathName, s_szCurrPath);

	if (lpFileName[0] == '.' && (lpFileName[1] == '\\'||lpFileName[1] == '/') )
		strcat(lpPathName, lpFileName + 2);
	else
		strcat(lpPathName, lpFileName);
}
//---------------------------------------------------------------------------
// 函数:	GetHalfPath
// 功能:	取得文件的半路径名，不带根路径
// 参数:	lpPathName	路径名
//			lpFileName	文件名
// 返回:	void
//---------------------------------------------------------------------------
C_ENGINE_API
void g_GetHalfPath(char* lpPathName, const char* lpFileName)
{
	// 文件带有部分路径
	if (lpFileName[0] == '\\' || lpFileName[0] == '/')
	{
		strcpy(lpPathName, lpFileName);
	}
	else
	{
		strcpy(lpPathName, PATH_SPLITTER_STR);
		strcat(lpPathName, s_szCurrPath);
		strcat(lpPathName, lpFileName);
	}
}

//---------------------------------------------------------------------------
// 函数:	GetPackPath
// 功能:	取得文件在压缩包中的路径名
// 参数:	lpPathName	路径名
//			lpFileName	文件名
// 返回:	void
//---------------------------------------------------------------------------
C_ENGINE_API
void g_GetPackPath(char* lpPathName, const char* lpFileName)
{
	// 文件带有部分路径
	if (lpFileName[0] == '\\' || lpFileName[0] == '/')
	{
		strcpy(lpPathName, lpFileName + 1);
	}
	else
	{
		strcpy(lpPathName, s_szCurrPath);
		strcat(lpPathName, lpFileName);
	}
	int len = (int)strlen(lpPathName);
	RemoveAllPointPath(lpPathName, len + 1);
	// 全部转换为小写字母
	strlwr(lpPathName);
}

//---------------------------------------------------------------------------
// 函数:	GetDiskPath
// 功能:	取得CDROM对应的文件路径名
// 参数:	lpPathName	路径名
//			lpFileName	文件名
// 返回:	void
//---------------------------------------------------------------------------
/*ENGINE_API void g_GetDiskPath(char* lpPathName, char* lpFileName)
{
	strcpy(lpPathName, "C:");
	for (int i = 0; i < 24; lpPathName[0]++, i++)
	{
//		if (GetDriveType(lpPathName) == DRIVE_CDROM)
//			break;
	}
	if (lpFileName[0] == '\\' || lpPathName[0] == '/')
	{
		strcat(lpPathName, lpFileName);
	}
	else
	{
#ifdef WIN32
		strcat(lpPathName, "\\");
#else
		strcat(lpPathName, "/");
#endif
		strcat(lpPathName, s_szCurrPath);
		strcat(lpPathName, lpFileName);
	}
}
*/
//---------------------------------------------------------------------------
// 函数:	CreatePath
// 功能:	在游戏根目录下建立一条路径
// 参数:	lpPathName	路径名
//---------------------------------------------------------------------------
C_ENGINE_API
int	g_CreatePath(const char* lpPathName)
{
	if (!lpPathName || !lpPathName[0])
		return false;

	char szTempPathName[MAX_PATH];
	memset(szTempPathName, 0, sizeof(szTempPathName));
	strncpy(szTempPathName, lpPathName, sizeof(szTempPathName));
	szTempPathName[sizeof(szTempPathName) - 1] = 0;

	char	szFullPath[MAX_PATH];
	int		i;
	if (szTempPathName[0] == '\\' || szTempPathName[0] == '/')    /// 这段是处理什么的？
	{
		szTempPathName[0] = PATH_SPLITTER;
		if (szTempPathName[1] != '\\')
		{
			strcpy(szFullPath, s_szRootPath);
			strcat(szFullPath, szTempPathName);
			i = (int)strlen(s_szRootPath) + 1;
			
		}
		else
		{
			strcpy(szFullPath, szTempPathName);
			i = 2;
		}
	}
#ifndef LINUX
	else if (szTempPathName[1] == ':')// 文件带有全路径
	{
		if (strlen(szTempPathName) < 4)
			return false;
		strcpy(szFullPath, szTempPathName);
		i = 4;
	}
#endif
	else
	{
		strcpy(szFullPath, s_szRootPath);
		strcat(szFullPath, PATH_SPLITTER_STR);
		strcat(szFullPath, szTempPathName);
		i = (int)strlen(s_szRootPath) + 1;
	}

	int nResult = true;
	for (; nResult && i < (int)strlen(szFullPath); i++)  /// 循环创建所有的目录
	{
		if (szFullPath[i] == '\\' || szFullPath[i] == '/')
		{
			szFullPath[i] = 0;
			#ifdef WIN32
				CreateDirectory(szFullPath, NULL);
			#else
				mkdir(szFullPath, 0777);
			#endif
			szFullPath[i] = PATH_SPLITTER;
		}
	}
	#ifdef WIN32
		CreateDirectory(szFullPath, NULL);
		DWORD dwAtt = GetFileAttributes(szFullPath);
		nResult = ((dwAtt != 0xFFFFFFFF)  && (dwAtt & FILE_ATTRIBUTE_DIRECTORY));
	#else
		mkdir(szFullPath, 0777);
	#endif

	return nResult;
}

//---------------------------------------------------------------------------
// 函数:	g_UnitePathAndName
// 功能:	一个路径和一个文件名，合并到lpGet中形成一个完整的路径文件名
// 参数:	pcszPath 传入路径名 pcszFile 传入文件名 pszFullName 获得的最终完整文件名
// 返回:	void
// 注意：   这里没有考虑字符串的长度，使用的时候要保证字符串的长度足够
//---------------------------------------------------------------------------
C_ENGINE_API
void	g_UnitePathAndName(const char *pcszPath, const char *pcszFile, char *pszRetFullName)
{
    if (pszRetFullName)
        pszRetFullName[0] = '\0';
  /**
   *  下面判断就没有采用 (pcszPath && pcszPath[0])的形式
   */  
	if (
        (!pcszPath) || 
        (!pcszFile) || 
        (!pszRetFullName)
    )
		return;

	strcpy(pszRetFullName, pcszPath);
	int	nSize = (int)strlen(pszRetFullName);
    if (nSize > 0)
    {
	    if (pszRetFullName[nSize - 1] != '\\')
	    {
		    pszRetFullName[nSize] = '\\';
            nSize++;
		    pszRetFullName[nSize] = '\0';
	    }
    }

	if (pcszFile[0] != '\\')
	{
		strcat(pszRetFullName + nSize, pcszFile);
	}
	else
	{
		strcat(pszRetFullName + nSize, &pcszFile[1]);
	}
}

//---------------------------------------------------------------------------
// 函数:	find if file exists in pak or in hard disk
// 功能:	返回指定的文件是否存在
// 参数:	lpPathName	路径名＋文件名
// 返回:	TRUE－成功，false－失败。
//---------------------------------------------------------------------------
C_ENGINE_API
int g_IsFileExist(const char* FileName)
{
	int	bExist = false;
	char	szFullName[MAX_PATH];
	if (FileName && FileName[0])	//这种判断方式：？？？
	{
		//先查是是否在打包文件中
		XPackFile::XPackElemFileRef	PackRef;
		bExist = g_EnginePackList.FindElemFile(FileName, PackRef);
		//在检查是否单独存在文件系统里
		if (bExist == false)
		{
			g_GetFullPath(szFullName, FileName);
			#ifdef	WIN32
				bExist = !(GetFileAttributes(szFullName) & FILE_ATTRIBUTE_DIRECTORY);// || dword == INVALID_FILE_ATTRIBUTES) ？如果不是文件夹？
			#else
//				bExist = _sopen(szFullName, _O_BINARY, _SH_DENYNO, 0);
//				if (bExist != -1)
//				{
//					_close(bExist);
//					bExist = true;
//				}
//				else
//				{
//					bExist = false;
//				}
			#endif
		}
	}
	return bExist;
}

//---------------------------------------------------------------------------
// 函数:	String to 32bit Id
// 功能:	文件名转换成 Hash 32bit ID
// 参数:	lpFileName	文件名
// 返回:	FileName Hash 32bit ID
// 注意:	游戏世界和主网关交互数据所用的哈希查找索引也是用
//			的这个函数，所以请修改这个函数时也对应修改主网关
//			中相对应的那个函数。这个函数存在于Common.lib工程的Utils.h
//			中，函数声明为 unsigned int HashStr2ID( const char * const pStr );
//---------------------------------------------------------------------------
C_ENGINE_API
unsigned int g_StringHash(const char* pString)
{
	unsigned int Id = 0;
	char c = 0;
	for (int i = 0; pString[i]; i++)
	{
		c = pString[i];
		Id = (Id + (i + 1) * c) % 0x8000000b * 0xffffffef;
	}
	return (Id ^ 0x12345678);
}

//把一个字符串小写化，再转为hash数值
C_ENGINE_API	unsigned int	g_StringLowerHash(const char* pString)
{
	unsigned int Id = 0;
	char c = 0;
	for (int i = 0; pString[i]; i++)
	{
		c = pString[i];
		if (c >= 'A' && c <= 'Z')
			c += 0x20;	//中文字符的后字节亦可能被转换，人为地加大了重码的概率■
		Id = (Id + (i + 1) * c) % 0x8000000b * 0xffffffef;
	}
	return (Id ^ 0x12345678);
}

//把一个字符串小写化，再转为hash数值
C_ENGINE_API	unsigned int	g_FileNameHash(const char* pString)
{
	unsigned int Id = 0;
	char c = 0;
	for (int i = 0; pString[i]; i++)
	{
		c = pString[i];
		if (c >= 'A' && c <= 'Z')
			c += 0x20;	//中文字符的后字节亦可能被转换，人为地加大了重码的概率■
		else if (c == '/')
			c = '\\';
		Id = (Id + (i + 1) * c) % 0x8000000b * 0xffffffef;
	}
	return (Id ^ 0x12345678);
}

//---------------------------------------------------------------------------
// 函数:	change file extention
// 功能:	改变文件的扩展名
// 参数:	lpFileName	文件名
//			lpNewExt	新扩展名，不能有'.'
// 返回:	void
//---------------------------------------------------------------------------
C_ENGINE_API
void g_ChangeFileExt(char* lpFileName, const char* lpNewExt)
{
	char* pDot = strrchr(lpFileName, '.');
	char* pPathSplit = strrchr(lpFileName, PATH_SPLITTER);

	if (pDot && pPathSplit < pDot)
	{
		strcpy(pDot + 1, lpNewExt);
	}
	else
	{          /// 这种情况？ xxx./yyy???
		strcat(lpFileName, ".");
		strcat(lpFileName, lpNewExt);
	}
}

//---------------------------------------------------------------------------
// 函数:	Extract File Name from path name
// 功能:	取得文件名（不包含路径）
// 参数:	lpFileName	文件名（不包含路径）
//			lpFilePath	文件名（包含路径）
// 返回:	void
//---------------------------------------------------------------------------
C_ENGINE_API
void g_ExtractFileName(char* lpFileName, const char* lpFilePath)
{
	int nPos = (int)strlen(lpFilePath);
//	if (nPos < 5)
//		return;
	while ((--nPos) >= 0)
	{
		if (lpFilePath[nPos] == '\\' || lpFilePath[nPos] == '/')
			break;
	}
	strcpy(lpFileName, &lpFilePath[nPos + 1]);
}

//---------------------------------------------------------------------------
// 函数:	Extract File Path from path name
// 功能:	取得路径名
// 参数:	lpFileName	路径名
//			lpFilePath	路径名＋文件名
// 返回:	void
//---------------------------------------------------------------------------
C_ENGINE_API
void g_ExtractFilePath(char* lpPathName, const char* lpFilePath)
{
	int nPos = (int)strlen(lpFilePath);
//	if (nLen < 5)
//		return;
//	int nPos = nLen;
	while ((--nPos) > 0)
	{
		if (lpFilePath[nPos] == '\\' ||lpFilePath[nPos] == '/')
			break;
	}
	if (nPos > 0)
	{
		memcpy(lpPathName, lpFilePath, nPos);
		lpPathName[nPos] = 0;
	}
	else
	{
		lpPathName[0] = 0;
	}
}
//---------------------------------------------------------------------------
// 函数:	Get File Path from full path name
// 功能:	从全路径中取得相对路径名
// 参数:	lpPathName		相对路径名
//			lpFullFilePath	全路径名
// 返回:	void
//---------------------------------------------------------------------------
C_ENGINE_API
BOOL g_GetFilePathFromFullPath(char* lpPathName, const char* lpFullFilePath)
{
	if (!lpPathName || !lpFullFilePath)
		return FALSE;

	int nRootSize = strlen(s_szRootPath);
	int nFullSize = strlen(lpFullFilePath);

	if (nFullSize <= nRootSize)
		return FALSE;

	memcpy(lpPathName, lpFullFilePath, nRootSize);
	lpPathName[nRootSize] = 0;

	if (stricmp(lpPathName, s_szRootPath))
		return FALSE;

	//再跳过路径后的"\\"
	memcpy(lpPathName, &lpFullFilePath[nRootSize + 1], nFullSize - nRootSize - 1);
	lpPathName[nFullSize - nRootSize - 1] = 0;

	return TRUE;
}

