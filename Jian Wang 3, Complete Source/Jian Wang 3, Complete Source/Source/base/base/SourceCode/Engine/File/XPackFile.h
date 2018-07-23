/*****************************************************************************************
//	包文件读取
//	Copyright : Kingsoft 2003
//	Author	:   Wooy(Wu yue)
//	CreateTime:	2003-9-16
------------------------------------------------------------------------------------------
	XPackFile支持多线程的同时访问。
	XPackFile外部通过XPackElemFileRef来描述其获得的对包内子文件的引用。
	外部勿自行随意改动此描述结构内的内容，以获得正常的包访问功能。
*****************************************************************************************/
#ifndef _ENGINE_XPACKFILE_H_
#define _ENGINE_XPACKFILE_H_
#include "Mutex.h"
#include "PackDef.h"
#include "./AloneFile.h"

class XPackFile
{
public:
	//--------------------------------------------------
	//使用XPackFile对子文件进行访问操作所用到的辅助结构
	//--------------------------------------------------
	typedef struct 
	{
		unsigned int	NameId;

		//----这些数据对打包文件中的小文件有效----
		short			CacheIndex;		//缓冲索引
		short			PakFileIndex;	//所处的打包文件的索引
		int				ElemFileIndex;	//在打包文件中的索引(是打包文件的第几个小文件)
		long			Offset;			//当前子文件操作偏移位置
		unsigned long	Size;			//子文件大小
		//----endof: 这些数据对打包文件中的小文件有效----
	} XPackElemFileRef;

public:
	XPackFile();
	~XPackFile();
	//初始化包文件模块,返回布尔值
	static int	Initialize();
	//关闭包文件模块
	static void	Terminate();
	//打开包文件,返回布尔值
	int			Open(const char* pszPackFileName, int nSelfIndex);
	//关闭包文件
	void		Close();
	//查找包内的子文件,返回布尔值
	int			FindElemFile(unsigned int uId, XPackElemFileRef& ElemRef);
	//读取包内的子文件
	unsigned long	ElemFileRead(XPackElemFileRef& ElemRef, void* pBuffer, unsigned long ReadBytes);
	//读取分块文件包内的数据，CompressSize = 0表示不解压直接读取
	unsigned long	XElemReadFragment(int nElemIndex, int nFragmentIndex, void*& Buffer);
	//判断文件是否分块压缩的
	int				XElemIsPackedByFragment(int nElemIndex);
	//获取文件分块的数目
	int				XElemGetFragmentCount(int nElemIndex);
	//获取某个子文件某个分块的大小
	unsigned int	ElemGetFragmentSize(int nElemIndex, int nFragmentIndex);
	//获得包含包内子文件完整内容的缓冲区
	void*			GetElemFileBuffer(XPackElemFileRef& ElemRef);

private:

	//直接读取包文件数据中的数据到缓冲区,返回布尔值
	int			DirectRead(void* pBuffer, unsigned int uOffset, unsigned int uSize);
	//带解压地读取包文件到缓冲区,返回布尔值
	int			ExtractRead(void* pBuffer, unsigned int uExtractSize,
						long lCompressType, unsigned int uOffset, unsigned int uSize);
	//在索引表中查找子文件项
	int			FindElemFile(unsigned long ulId) const;
	//在cache里查找子文件
	int			FindElemFileInCache(unsigned int uId, int nDesireIndex);
	//把子文件数据添加到cache
	int			AddElemFileToCache(void* pBuffer, int nElemIndex);
	//分配一个缓冲区，并把指定的子文件数据读入其中
	void*		ReadElemFile(int nElemIndex);
	//释放一个cache结点的数据
	static void	FreeElemCache(int nCacheIndex);
	//加载分块打包文件的全部内容,成功返回非0值，失败返回0值
	int			EnsureElemFlieContent(int nCacheIndex, int nStartOffset, int nEndOffset);

private:
	KAloneFile				m_File;				//包文件
	unsigned long			m_uFileSize;		//包文件大小
	unsigned long			m_uElemFileCount;	//子文件的个数
	int						m_nSelfIndex;		//包文件自己在包序列中的索引
	struct XPackIndexInfo*	m_pIndexList;		//子文件索引列表

	//----子文件数据cache----
	struct XPackElemFileCache
	{
		void*			pBuffer;			//保存子文件数据的缓冲区
		unsigned long	uId;				//子文件id
		unsigned long	lSize;				//子文件大小
		int				nPackIndex;			//来自哪个包文件
		int				nElemIndex;			//子文件在索引列表中的位置
		unsigned int	uRefFlag;			//近期引用标记
		int				nNumFragment;		//分块数目，为0表示不分块
		XPackFileFragmentInfo*	pFragmentInfo;	//分块信息
	};

	static int			ms_HasInitialize;	//是否已经初始化过了
	static MUTEX_DECLARE(ms_ReadCritical);	//操作包文件时的临界区控制

	#define	MAX_XPACKFILE_CACHE			10
	//子文件的cache数据
	static	XPackElemFileCache	ms_ElemFileCache[MAX_XPACKFILE_CACHE];
	//子文件被cache的数目
	static	int					ms_nNumElemFileCache;
};


#endif //#ifndef _ENGINE_XPACKFILE_H_
