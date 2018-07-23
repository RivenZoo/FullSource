//---------------------------------------------------------------------------
// Sword Engine (c) 1999-2004 by Kingsoft
// Date:	2000.08.08
// Code:	wooy
// Desc:	Header File
//---------------------------------------------------------------------------
#ifndef _ENGINE_FILE_H_
#define _ENGINE_FILE_H_

class IFile
{
public:
	// 读取文件数据
	virtual unsigned long	Read(void* Buffer, unsigned long ReadBytes) = 0;
	// 写入文件数据
	virtual unsigned long	Write(const void* Buffer, unsigned long WriteBytes) = 0;
	// 获得文件内容Buffer,由iFile接口负责释放这个缓冲区，外部应用不可自行释放它。
	virtual void*			GetBuffer() = 0;
	// 移动文件指针位置，Origin	-> Initial position: SEEK_CUR SEEK_END SEEK_SET
	virtual long	Seek(long Offset, int Origin) = 0;
	// 取得文件指针位置,失败返回-1。
	virtual long	Tell() = 0;
	// 取得文件长度,失败返回0。
	virtual unsigned long	Size() = 0;
	// 判断打开的是否是包中的文件,返回布尔值
	virtual int		IsFileInPak() = 0;

	//判断文件是否分块压缩的
	virtual int		IsPackedByFragment() = 0;
	//获取文件分块的数目
	virtual int		GetFragmentCount() = 0;
	//获取分块的大小
	virtual unsigned int	GetFragmentSize(int nFragmentIndex) = 0;
	//读取一个文件分块，传入的pBuffer为目标缓冲区，如果传入的缓冲区指针为空，则内部会分配新的缓冲区，并传出指针，外部需要负责销毁。
	//缓冲区的大小需要能容纳下分块的内容，可以通过GetFragmentCount知道每个分块的数据大小，缓冲区必须至少要有这么大。
	//返回值表示实际读取出来的这个分块的数据大小,如果操作失败(包括分块不存在,子文件不是按分块方式存储等等)返回0。
	virtual unsigned long	ReadFragment(int nFragmentIndex, void*& pBuffer) = 0;

	// 关闭打开的文件
	virtual void	Close() = 0;
	// 接口对象销毁
	virtual void	Release() = 0;

	virtual ~IFile() {};
};


extern "C"
{
ENGINE_API	IFile*	g_OpenFile(const char* FileName, int ForceUnpakFile = false, int ForWrite = false);
ENGINE_API	IFile*	g_CreateFile(const char* FileName);

//设置查找文件的优先次序(是否先查找打包文件)
ENGINE_API	void	g_SetFindFileMode(int FindPakFirst);
//加载打包文件，返回布尔值
ENGINE_API	int		g_LoadPackageFiles(const char* pListFile, const char* pSection);
//卸载打包文件
ENGINE_API	void	g_ClearPackageFiles();
//设置文件操作根目录
ENGINE_API	void	g_SetRootPath(const char* lpPathName = 0);
//获取文件操作根目录
ENGINE_API	void	g_GetRootPath(char* lpPathName);

//多线程访问engine的文件模块时，勿使用如下两个函数，访问时，请使用相对与root目录的完整路径
ENGINE_API	void	g_SetFilePath(const char* lpPathName);
ENGINE_API	void	g_GetFilePath(char* lpPathName);

ENGINE_API	void	g_GetFullPath(char* lpPathName, const char* lpFileName);
ENGINE_API	void	g_GetHalfPath(char* lpPathName, const char* lpFileName);
ENGINE_API	void	g_GetPackPath(char* lpPathName, const char* lpFileName);
ENGINE_API	BOOL	g_GetFilePathFromFullPath(char* lpPathName,
											  const char* lpFullFilePath);
//ENGINE_API	void	g_GetDiskPath(char* lpPathName, const char* lpFileName);
ENGINE_API	int		g_CreatePath(const char* lpPathName);
ENGINE_API	int		g_IsFileExist(const char* lpPathName);
//把一个字符串转为hash数值
ENGINE_API	unsigned int	g_StringHash(const char* pString);
//把一个字符串小写化，再转为hash数值(对于非西文字符如中文字符会非正常转发,增加碰撞击率，但与语言编码平台无关)
ENGINE_API	unsigned int	g_StringLowerHash(const char* pString);
//把一个文件名字符串小写化，再转为hash数值
//a. 对于 / 字符都会转为 \
//b. 对对于非西文字符如中文字符会非正常转发,增加碰撞击率，但与语言编码平台无关
ENGINE_API	unsigned int	g_FileNameHash(const char* pString);

// 一个路径和一个文件名，合并到lpGet中形成一个完整的路径文件名
ENGINE_API	void	g_UnitePathAndName(const char *lpPath, const char *lpFile, char *lpGet);
ENGINE_API	void	g_ChangeFileExt(char* lpFileName, const char* lpNewExt);
ENGINE_API	void	g_ExtractFileName(char* lpFileName, const char* lpFilePath);
ENGINE_API	void	g_ExtractFilePath(char* lpPathName, const char* lpFilePath);
}

//====UCL压缩算法函数====
extern "C"
{
	ENGINE_API int CD_LCU_I();
	ENGINE_API int CD_LCU_C(const unsigned char* pSrcBuffer, unsigned int nSrcLen,
						unsigned char* pDestBuffer, unsigned int* pDestLen, int nCompressLevel);
	ENGINE_API int CD_LCU_D(const unsigned char* pSrcBuffer, unsigned nSrcLen,
						unsigned char* pDestBuffer, unsigned int uExtractSize);
}

#endif //#ifndef _ENGINE_FILE_H_
