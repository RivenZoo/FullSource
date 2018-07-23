//---------------------------------------------------------------------------
// Sword3 Engine (c) 1999-2000 by Kingsoft
// File:	KIniFile.h
// Date:	2000.08.08
// Code:	WangWei(Daphnis)
// Desc:	Header File
//---------------------------------------------------------------------------
#ifndef _ENGINE_FILE_TYPE_H_
#define _ENGINE_FILE_TYPE_H_
#include "EngineBase.h"
#include "CommonDefine.h"

// ***关于IIniFile的数据读取:***
//		有的读取接口不能传入默认值,对于这种接口，如果不存在数据可供
//读取,则保持原传入空间中的值不变(即传入前可以先给变量赋予默认值).
// ***关于多个并列值得读取与写入***
//   通过GetMulti*,WriteMulti*函数读取写入并列数据时，并列数据的个数是受限的，
//限制个数为枚举值INI_MAX_SUPPORT_MULTI_VALUE_COUNT，如果操作时并列数据的数目
//操出限制返回失败
class IIniFile
{
public:
	enum	INIFILE_PARAM
	{
		INI_MAX_SUPPORT_MULTI_VALUE_COUNT   = 16,	//通过GetMulti*,WriteMulti*函数操作的值的上限数目，操出限制返回失败
        
        INI_MAX_SUPPORT_SECTION_AND_KEY_SIZE = 64,
    
        INI_MAX_SUPPORT_VALUE_SIZE           = 4096,
	};

	virtual int		Save(const char* FileName) = 0;
	virtual void	Clear() = 0;
	virtual void	Release() = 0;

    // Set pSection as empty string to get the first section
	virtual int		GetNextSection(const char* pSection, char* pNextSection) = 0;
    // Set pKey as empty string to get the first key
	virtual int		GetNextKey(const char* pSection, const char* pKey, char* pNextKey) = 0;	
	virtual int		GetSectionCount() = 0;
	virtual int		IsSectionExist(const char* lpSection) = 0;
	virtual void	EraseSection(const char* lpSection) = 0;
	virtual void	EraseKey(const char* lpSection, const char* lpKey) = 0;

	virtual int		GetString(
				const char*	lpSection,		// points to section name
				const char*	lpKeyName,		// points to key name
				const char*	lpDefault,		// points to default string
				char*	lpRString,			// points to destination buffer
				unsigned int	dwSize		// size of string buffer
				) = 0;
	virtual int		GetInteger(
				const char*	lpSection,		// points to section name
				const char*	lpKeyName,		// points to key name
				int		nDefault,			// default value
				int*	pnValue				// return value
				) = 0;
	virtual int		GetInteger2(
				const char*	lpSection,		// points to section name
				const char*	lpKeyName,		// points to key name
				int		*pnValue1,			// value 1
				int		*pnValue2			// value 2
				) = 0;
	virtual int		GetMultiInteger(
				const char*	lpSection,		// points to section name
				const char*	lpKeyName,		// points to key name
				int		*pValues,			// value array
				int		nCount				// [in]  the count of integers want to get
                                            // [out] the count of integers actually got
				) = 0;
	virtual int		GetMultiLong(
				const char*	lpSection,		// points to section name
				const char*	lpKeyName,		// points to key name
				long	*pValues,			// value array
				int		nCount				// [in]  the count of long integers want to get
                                            // [out] the count of long integers actually got 
				) = 0;
	virtual int		GetFloat(
				const char*	lpSection,		// points to section name
				const char*	lpKeyName,		// points to key name
				float	fDefault,			// default value
				float	*pfValue			// return value
				) = 0;
	virtual int		GetFloat2(
				const char*	lpSection,		// points to section name
				const char*	lpKeyName,		// points to key name
				float	*pfValue1,			// value 1
				float	*pfValue2			// value 2
				) = 0;
	virtual int		GetMultiFloat(
				const char*	lpSection,		// points to section name
				const char*	lpKeyName,		// points to key name
				float	*pValues,			// value array
				int		nCount				// [in]  the count of float numbers want to get
                                            // [out] the count of float numbers actually got 
				) = 0;
	virtual int		GetStruct(
				const char*	lpSection,		// pointer to section name
				const char*	lpKeyName,		// pointer to key name
				void*	lpStruct,			// pointer to buffer that contains data to add
				unsigned int dwSize			// size, in bytes, of the buffer
				) = 0;
	virtual int		GetBool(
				const char*	lpSection,
				const char*	lpKeyName,
				int*		pBool
				) = 0;

	virtual int		WriteString(
				const char*	lpSection,		// pointer to section name
				const char*	lpKeyName,		// pointer to key name
				const char*	lpString		// pointer to string to add
				) = 0;
	virtual int		WriteInteger(
				const char*	lpSection,		// pointer to section name
				const char*	lpKeyName,		// pointer to key name
				int	    Value				// value to write
				) = 0;
	virtual int		WriteInteger2(
				const char*	lpSection,		// pointer to section name
				const char*	lpKeyName,		// pointer to key name
				int	    Value1,				// value 1 to write
				int		Value2				// value 2 to write
				) = 0;
	virtual int		WriteMultiInteger(
				const char*	lpSection,		// pointer to section name
				const char*	lpKeyName,		// pointer to key name
				int		*pValues,			// value array
				int		nCount				// 要写入的整数值的数目
				) = 0;
	virtual int		WriteMultiLong(
				const char*	lpSection,		// pointer to section name
				const char*	lpKeyName,		// pointer to key name
				long	*pValues,			// value array
				int		nCount				// 要写入的整数值的数目
				) = 0;
	virtual int		WriteFloat(
				const char*	lpSection,		// pointer to section name
				const char*	lpKeyName,		// pointer to key name
				float	fValue				// value to write
				) = 0;
	virtual int		WriteFloat2(
				const char*	lpSection,		// pointer to section name
				const char*	lpKeyName,		// pointer to key name
				float	fValue1,			// value 1 to write
				float	fValue2				// value 2 to write
				) = 0;
	virtual int		WriteMultiFloat(
				const char*	lpSection,		// pointer to section name
				const char*	lpKeyName,		// pointer to key name
				float	*pValues,			// value array
				int		nCount				// 要写入的浮点数值的数目
				) = 0;
	virtual int		WriteStruct(
				const char*	lpSection,		// pointer to section name
				const char*	lpKeyName,		// pointer to key name
				void*	lpStruct,			// pointer to buffer that contains data to add
				unsigned int dwSize			// size, in bytes, of the buffer
	 			) = 0;

	virtual ~IIniFile() {};
};

class ITabFile
{
public:
	virtual void	Clear() = 0;
	virtual void	Release() = 0;

    virtual void    SetErrorLog(BOOL bEnable) = 0;

	virtual int		FindRow(const char* szRow) = 0;			//返回以1为起点的值
	virtual int		FindColumn(const char* szColumn) = 0;	//返回以1为起点的值
	virtual int		GetWidth() 	= 0;
	virtual int		GetHeight() = 0;

	//--读取数据---
	virtual int		GetString(int nRow, const char* szColumn, const char* lpDefault,
						char* lpRString, unsigned int dwSize, int bColumnLab = true)	= 0;
	virtual int		GetString(int nRow, int nColumn, const char* lpDefault,
						char* lpRString, unsigned int dwSize) = 0;
	virtual int		GetString(const char* szRow, const char* szColumn, const char* lpDefault,
						char* lpRString, unsigned int dwSize) = 0;
	virtual int		GetInteger(int nRow, const char* szColumn, int nDefault,
						int *pnValue, int bColumnLab = true) = 0;
	virtual int		GetInteger(int nRow, int nColumn, int nDefault, int *pnValue) = 0;
	virtual int		GetInteger(const char* szRow, const char* szColumn,
						int nDefault, int *pnValue) = 0;
	virtual int		GetFloat(int nRow, const char* szColumn, float fDefault,
						float *pfValue, int bColumnLab = true) = 0;
	virtual int		GetFloat(int nRow, int nColumn, float fDefault, float *pfValue)	= 0;
	virtual int		GetFloat(const char* szRow, const char* szColumn,
						float fDefault, float *pfValue) = 0;

	//--写入数据--
	virtual int			Save(const char* FileName) = 0;//保存文件,返回布尔值
	virtual const char*	GetRowName(int nRow) = 0;
	virtual const char*	GetColName(int nCol) = 0;
	virtual int			InsertNewCol(const char* strNewCol) = 0;//返回新生成的Col编号，错误则返回-1
	virtual int			InsertAfter(int nRow) = 0;
	virtual int			InsertAfter(char* szRow, int bColumnLab = true) = 0;
	virtual int			InsertBefore(int nRow) = 0;
	virtual int			InsertBefore(char* szRow, int bColumnLab = true) = 0;
	virtual int			WriteString(int nRow, int nColumn, const char* lpString,  unsigned int dwSize = 0) = 0;
	virtual int			WriteString(int nRow, const char* szColumn, const char* lpString,  int bColumnLab = true) = 0;
	virtual int			WriteString(const char* szRow, const char* szColumn,  const char* lpRString) = 0;
	virtual int			WriteInteger(int nRow, int nColumn, int nValue) = 0;
	virtual int			WriteInteger(int nRow, const char* szColumn, int nValue, int bColumnLab = true) = 0;
	virtual int			WriteInteger(const char* szRow, const char* szColumn, int nValue) = 0;
	virtual int			WriteFloat(int nRow, int nColumn,float fValue) = 0;
	virtual int			WriteFloat(int nRow, const char* szColumn, float fValue, int bColumnLab = true) = 0;
	virtual int			WriteFloat(const char* szRow, const char* szColumn, float fValue) = 0;
	virtual int			Remove(int nRow) = 0;
	virtual int			Remove(const char* szRow, int bColumnLab = true) = 0;

	virtual ~ITabFile() {};
};


C_ENGINE_API	IIniFile*	g_CreateIniFile();
C_ENGINE_API	ITabFile*	g_CreateTabFile();
C_ENGINE_API	IIniFile*	g_OpenIniFile(const char* FileName, int ForceUnpakFile = false, int ForWrite = false);
C_ENGINE_API	ITabFile*	g_OpenTabFile(const char* FileName, int ForceUnpakFile = false, int ForWrite = false);
ENGINE_API bool	g_OpenFile(IIniFile** ppIniFile, const char* FileName, int ForceUnpakFile = false, int ForWrite = false);
ENGINE_API bool	g_OpenFile(ITabFile** ppTabFile, const char* FileName, int ForceUnpakFile = false, int ForWrite = false);

////////////////////////////////////////////////////////////////////////////////
// The argument string in argv should have the format as "--Section.Key=Value",
// such as "--Database.username=root". If no prefix "--", ignore it.
// Return a read only ini file interface
ENGINE_API IIniFile *g_OpenIniFileFromArguments(int argc, char* argv[]);

////////////////////////////////////////////////////////////////////////////////
// Combine two ini file to one, If there is repeated key in one section from 
// two IIniFile,  set its value as which from piHighPriority.
// Return a read only ini file interface
ENGINE_API IIniFile *g_OpenCombinatorialIniFile(IIniFile* piHighPriority, IIniFile* piLowPriority);

////////////////////////////////////////////////////////////////////////////////
// Load start arguments from command line and an ini file, and command arguments
// have high priority
// Return a read only ini file interface
ENGINE_API IIniFile *g_LoadStartArgument(int argc, char *argv[], const char *FileName);

#endif //ifndef _ENGINE_FILE_TYPE_H_
