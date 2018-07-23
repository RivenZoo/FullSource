//---------------------------------------------------------------------------
// Sword3 Engine (c) 1999-2004 by Kingsoft
// Date:	2000.08.08
// Code:	WangWei(Daphnis), Wooy(Wu yue)
//---------------------------------------------------------------------------
#ifndef _ENGINE_INIFILE_H_
#define _ENGINE_INIFILE_H_

#include "FileType.h"
#include "RecycleBin.h"

class KIniFile : public IIniFile
{
public:	//IIniFile接口函数
	int		Save(const char* FileName);
	void	Clear();
	void	Release();

	int		GetNextSection(const char* pSection, char* pNextSection);
	int		GetNextKey(const char* pSection, const char* pKey, char* pNextKey);
	int		GetSectionCount();
	int		IsSectionExist(const char* lpSection);
	void	EraseSection(const char* lpSection);
	void	EraseKey(const char* lpSection, const char* lpKey);

	int		GetString(const char* lpSection, const char* lpKeyName,
						const char*	lpDefault, char* lpRString, unsigned int dwSize);
	int		GetInteger(const char* lpSection, const char* lpKeyName,
						int nDefault, int* pnValue);
	int		GetInteger2(const char*	lpSection, const char* lpKeyName,
						int *pnValue1, int *pnValue2);
	int		GetMultiInteger(const char*	lpSection, const char* lpKeyName,
						int *pValues, int nCount);
	int		GetMultiLong(const char* lpSection, const char*	lpKeyName,
						long *pValues, int nCount);
	int		GetFloat(const char* lpSection, const char*	lpKeyName,
						float fDefault, float *pfValue);
	int		GetFloat2(const char* lpSection, const char* lpKeyName,
						float* pfValue1, float* pfValue2);
	int		GetMultiFloat(const char* lpSection, const char* lpKeyName,
						float* pValues, int nCount);
	int		GetStruct(const char* lpSection, const char* lpKeyName,
						void* lpStruct, unsigned int dwSize);
	int		GetBool(const char*	lpSection, const char* lpKeyName, int*	pBool);
	int		WriteString(const char*	lpSection, const char* lpKeyName, const char* lpString);
	int		WriteInteger(const char* lpSection, const char*	lpKeyName, int Value);
	int		WriteInteger2(const char* lpSection, const char* lpKeyName,	int Value1, int Value2);
	int		WriteMultiInteger(const char* lpSection, const char* lpKeyName,	int	*pValues, int nCount);
	int		WriteMultiLong(const char* lpSection, const char* lpKeyName, long *pValues, int nCount);
	int		WriteFloat(const char* lpSection, const char* lpKeyName, float fValue);
	int		WriteFloat2(const char*	lpSection, const char* lpKeyName, float	fValue1, float fValue2);
	int		WriteMultiFloat(const char*	lpSection, const char* lpKeyName, float	*pValues, int nCount);
	int		WriteStruct(const char*	lpSection, const char* lpKeyName, void*	lpStruct, unsigned int dwSize);

public:
	KIniFile();
	virtual ~KIniFile();
	//构造一个空的KIniFile对象
	static KIniFile* New();
	int		LoadData(IFile* pFile);

private:
	struct KEYNODE
	{
		unsigned int	dwID;
		char*			pKey;
		char*			pValue;
		KEYNODE*		pNextNode;
	};
	
	struct SECNODE
	{
		unsigned int	dwID;
		char*			pSection;
		KEYNODE			RootNode;
		SECNODE*		pNextNode;
	};

	SECNODE		m_Header;
	long		m_Offset;
	static KRecycleBin<KIniFile, 4, RBAFM_NEW_DELETE>	ms_Recycle;

private:
	void		CreateIniLink(void* Buffer,long Size);
	void		ReleaseIniLink();
	unsigned int	String2Id(const char* pString);
	int			ReadLine(char* Buffer,long Size);
	int			IsKeyChar(char ch);
	char*		SplitKeyValue(char* pString);
	int			SetKeyValue(const char* pSection,const char* pKey,const char* pValue);
	int			GetKeyValue(const char* pSection,const char* pKey,char* pValue,unsigned int dwSize);
};

#endif //_ENGINE_INIFILE_H_
