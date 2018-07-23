//---------------------------------------------------------------------------
// Sword3 Engine (c) 1999-2004 by Kingsoft
// File:	KTabFile.h
// Date:	2002.02.18
// Code:	Spe, wooy
// Desc:	Header File
//---------------------------------------------------------------------------
#ifndef _ENGINE_TABFILE_H_
#define _ENGINE_TABFILE_H_

#include "FileType.h"
#include "RecycleBin.h"

#define	_NOT_IMPL_	{ return 0; }

class KTabFile: public ITabFile
{
public:	//ITabFile接口函数
	void	Clear();
	void	Release();

    void    SetErrorLog(BOOL bEnable);

	int		FindRow(const char* szRow);
	int		FindColumn(const char* szColumn);
	int		GetWidth();
	int		GetHeight();
	int		GetString(int nRow, const char* szColumn, const char* lpDefault,
						char* lpRString, unsigned int dwSize, int bColumnLab = true);
	int		GetString(int nRow, int nColumn, const char* lpDefault,
						char* lpRString, unsigned int dwSize);
	int		GetString(const char* szRow, const char* szColumn, const char* lpDefault,
						char* lpRString, unsigned int dwSize);
	int		GetInteger(int nRow, const char* szColumn, int nDefault,
						int *pnValue, int bColumnLab = true);
	int		GetInteger(int nRow, int nColumn, int nDefault, int *pnValue);
	int		GetInteger(const char* szRow, const char* szColumn,
						int nDefault, int *pnValue);
	int		GetFloat(int nRow, const char* szColumn, float fDefault,
						float *pfValue, int bColumnLab = true);
	int		GetFloat(int nRow, int nColumn, float fDefault, float *pfValue);
	int		GetFloat(const char* szRow, const char* szColumn,
						float fDefault, float *pfValue);

	//下列函数在KTabFile中不支持，都直接返回失败(false/0)
	int			Save(const char* FileName) _NOT_IMPL_;//保存文件,返回布尔值
	const char*	GetRowName(int nRow) _NOT_IMPL_;
	const char*	GetColName(int nCol) _NOT_IMPL_;
	int			InsertNewCol(const char* strNewCol) _NOT_IMPL_;//返回新生成的Col编号，错误则返回-1
	int			InsertAfter(int nRow) _NOT_IMPL_;
	int			InsertAfter(char* szRow, int bColumnLab = true) _NOT_IMPL_;
	int			InsertBefore(int nRow) _NOT_IMPL_;
	int			InsertBefore(char* szRow, int bColumnLab = true) _NOT_IMPL_;
	int			WriteString(int nRow, int nColumn, const char* lpString,  unsigned int dwSize = 0) _NOT_IMPL_;
	int			WriteString(int nRow, const char* szColumn, const char* lpString,  int bColumnLab = true) _NOT_IMPL_;
	int			WriteString(const char* szRow, const char* szColumn,  const char* lpRString) _NOT_IMPL_;
	int			WriteInteger(int nRow, int nColumn, int nValue) _NOT_IMPL_;
	int			WriteInteger(int nRow, const char* szColumn, int nValue, int bColumnLab = true) _NOT_IMPL_;
	int			WriteInteger(const char* szRow, const char* szColumn, int nValue) _NOT_IMPL_;
	int			WriteFloat(int nRow, int nColumn,float fValue) _NOT_IMPL_;
	int			WriteFloat(int nRow, const char* szColumn, float fValue, int bColumnLab = true) _NOT_IMPL_;
	int			WriteFloat(const char* szRow, const char* szColumn, float fValue) _NOT_IMPL_;
	int			Remove(int nRow) _NOT_IMPL_;
	int			Remove(const char* szRow, int bColumnLab = true) _NOT_IMPL_;

public:
	KTabFile();
	virtual ~KTabFile();
	//构造一个空的KTabFile对象
	static	KTabFile* New();
	int		LoadData(IFile* pFile);

private:
	struct TABOFFSET
	{
		unsigned int		dwOffset;
		unsigned int		dwLength;
	};
private:
	int				m_Width;
	int				m_Height;
	unsigned char*	m_pMemory;
	unsigned int	m_uMemorySize;
	TABOFFSET*		m_pOffsetTable;
	static KRecycleBin<KTabFile, 2, RBAFM_NEW_DELETE>	ms_Recycle;

    BOOL            m_bErrorLogEnable;

private:
	int		CreateTabOffset();
	int		Str2Col(const char* szColumn);
	int		GetValue(int nRow, int nColumn, char* lpRString, unsigned int dwSize);
	void	Col2Str(int nCol, char* szColumn);
};

#endif	//_ENGINE_TABFILE_H_
