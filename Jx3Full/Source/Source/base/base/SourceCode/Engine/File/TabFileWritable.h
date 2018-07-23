#ifndef _ENGINE_TABFILECTRL_H_
#define _ENGINE_TABFILECTRL_H_

#include "File.h"
#include "FileType.h"
#include "KList.h"
#include "RecycleBin.h"

class TTabColNode: public KNode
{
public :
	char * m_Str;
	~TTabColNode(){ free(m_Str); }
};

class TTabLineNode: public KNode
{
public:
	KList * pList;
	~TTabLineNode()
	{
		if (pList)
		{
			while(pList->GetHead())	
			{
				TTabColNode * pDelNode = (TTabColNode*) pList->GetHead();
				pList->RemoveHead();
				delete pDelNode;
			}
			delete pList;
			pList = NULL;
		}
	};
};

class KTabFileWritable: public ITabFile
{
public:	//ITabFile接口函数
	void	Clear();
	void	Release();

    void    SetErrorLog(BOOL bEnable);

	int		FindRow(const char* szRow);			//返回以1为起点的值
	int		FindColumn(const char* szColumn);	//返回以1为起点的值
	int		GetWidth();
	int		GetHeight();

	//--读取数据---
	int		GetString(int nRow, int nColumn, const char* lpDefault,
						char* lpRString, unsigned int dwSize);
	int		GetString(int nRow, const char* szColumn, const char* lpDefault,
						char* lpRString, unsigned int dwSize, int bColumnLab = true);
	int		GetString(const char* szRow, const char* szColumn, const char* lpDefault,
						char* lpRString, unsigned int dwSize);
	int		GetInteger(int nRow, int nColumn, int nDefault, int *pnValue);
	int		GetInteger(int nRow, const char* szColumn, int nDefault,
						int *pnValue, int bColumnLab = true);
	int		GetInteger(const char* szRow, const char* szColumn,
						int nDefault, int *pnValue);
	int		GetFloat(int nRow, int nColumn, float fDefault, float *pfValue);
	int		GetFloat(int nRow, const char* szColumn, float fDefault,
						float *pfValue, int bColumnLab = true);
	int		GetFloat(const char* szRow, const char* szColumn,
						float fDefault, float *pfValue);

	//--写入数据--
	int			Save(const char* FileName);//保存文件,返回布尔值
	const char*	GetRowName(int nRow);
	const char*	GetColName(int nCol);
	int			InsertNewCol(const char* strNewCol);//返回新生成的Col编号，错误则返回-1
	int			InsertAfter(int nRow);
	int			InsertAfter(char* szRow, int bColumnLab = true);
	int			InsertBefore(int nRow);
	int			InsertBefore(char* szRow, int bColumnLab = true);
	int			WriteString(int nRow, int nColumn, const char* lpString,  unsigned int dwSize = 0);
	int			WriteString(int nRow, const char* szColumn, const char* lpString,  int bColumnLab = true);
	int			WriteString(const char* szRow, const char* szColumn, const char* lpRString);
	int			WriteInteger(int nRow, int nColumn, int nValue);
	int			WriteInteger(int nRow, const char* szColumn, int nValue, int bColumnLab = true);
	int			WriteInteger(const char* szRow, const char* szColumn, int nValue);
	int			WriteFloat(int nRow, int nColumn,float fValue);
	int			WriteFloat(int nRow, const char* szColumn, float fValue, int bColumnLab = true);
	int			WriteFloat(const char* szRow, const char* szColumn, float fValue);
	int			Remove(int nRow);
	int			Remove(const char* szRow, int bColumnLab = true);

public:
	KTabFileWritable();
	virtual ~KTabFileWritable();
	//构造一个空的KTabFile对象
	static	KTabFileWritable* New();
	int		LoadData(IFile* pFile);

private:
	int	SetValue(int nRow, int nColumn, const char* lpRString, unsigned int dwSize, int bCanCreateNew = true);
	int	GetValue(int nRow, int nColumn, char*& lpRString, unsigned int dwSize);
	int	GetValue(const char* RowName, const char* ColumnName, char* szValue, unsigned int dwSize)
	{
		return GetValue(FindRow(RowName),FindColumn(ColumnName), szValue, dwSize);
	}
	int	Str2Col(const char* szColumn);

	int	GetStringRaw(int nRow, int nColumn, const char* lpDefault, char* lpRString, unsigned int dwSize);
    int	GetIntegerRaw(int nRow, int nColumn, int nDefault, int *pnValue);
    int	GetFloatRaw(int nRow, int nColumn, float fDefault, float *pfValue);

private:
	KList		m_RowList;
	static KRecycleBin<KTabFileWritable, 2, RBAFM_NEW_DELETE>	ms_Recycle;
    BOOL        m_bErrorLogEnable;
};

#endif //_ENGINE_TABFILECTRL_H_

