/*****************************************************************************************
//	包文件的生成、展开、修改、合并等操作的接口
//	Copyright : Kingsoft 2005
//	Author	:   Wooy(Wu yue)
//	CreateTime:	2005-3-23
------------------------------------------------------------------------------------------
*****************************************************************************************/

#ifndef   __IPACKILESHELL_H_HEADER__
#define   __IPACKILESHELL_H_HEADER__

struct IPackFileShell
{
public:
	enum IPACK_FILE_SHELL_PARAM
	{
		PACK_FILE_SHELL_MAX_SUPPORT_PAK_NUM = 24,			//最多同时支持的打包文件的数目
		PACK_FILE_SHELL_MAX_SUPPORT_ELEM_FILE_NUM = 200000,	//一个打包文件中最多可以包含子文件的个数
		IPACK_FILE_SHELL_OPTION_SPR_SPLIT_FRAME_BALANCE_MIN = 100,
		IPACK_FILE_SHELL_OPTION_SPR_SPLIT_FRAME_BALANCE_MAX = 1000,
		IPACK_FILE_SIGNATURE_FLAG = 0x4b434150,				//'PACK'，打包文件符。
		IPACK_FILE_SHELL_OPTION_SPR_SPLIT_FRAME_BALANCE_DEF = 131072,		//128K，默认为spr文件大于128K则分帧压缩
								//通过SetOption(IPACK_FILE_SHELL_OPTION_SPR_SPLIT_FRAME_BALANCE..)调整此设定
		
	};
	enum IPACK_FILE_SHELL_OPTION
	{
		IPACK_FILE_SHELL_OPTION_SPR_SPLIT_FRAME_BALANCE = 0,
		IPACK_FILE_SHELL_OPTION_RETRENCH = 1,					//紧缩打包文件,去除不必要的空间。在打包文件之后删除子文件、合并等操作之后
																//nValue == 0 表示不做紧缩处理， nValue == 非0 表示要做紧缩处理
	};
	typedef int		(*fnAddFolderToPakCallback)(const char* pFileName);
	struct ELEM_FILE_INFO
	{
		int				nPakIndex;		//在哪个包中
		int				nElemIndex;		//在包中的第几个子文件
		unsigned int	uId;			//子文件ID
		unsigned int	uSize;			//子文件原始大小
		unsigned int	uStoreSize;		//子文件在包中的存储大小
		unsigned int	uCompressFlag;	//子文件的压缩标记 = (XPackIndexInfo::uCompressSizeFlag & 0xff000000)
		unsigned int	uTime;			//子文件的时间
		unsigned int	uCRC;			//校验和
		char			szFileName[128];//子文件的文件名（相对于游戏根目录）
	};
	//扫描包文件的回调函数，传入参数表示扫描到的子文件
	//返回值如果为非0，则继续扫描，返回值为0则终止扫描。
	//参看IPackFileShell::ScanAllPack
	typedef int		(*fnScanPackCallback)(ELEM_FILE_INFO& ElemInfo, void* pParam);

public:
	//销毁接口对象
	virtual void	Release() = 0;
	//设置子文件的根目录
	virtual void	SetElemFileRootPath(const char* pPath) = 0;
	//创建/打开的一个打包文件，返回打包文件索引，返回负值表示操作失败。
	virtual int		CreatePack(const char* pszFile, int bOpenExist, int bExcludeOfCheckId) = 0;
	//关闭打包文件
	virtual void	ClosePack(int nPakIndex) = 0;
	//往打包文件中添加一个目录
	virtual bool	AddFolderToPak(int nPakIndex, const char* pFolder, fnAddFolderToPakCallback pCallback) = 0;
	//往打包文件中添加一个子文件
	virtual bool	AddElemToPak(int nPakIndex, const char* pElemFile) = 0;
	//删除打包文件中的一个子文件
	virtual int		DeleteElemInPak(int nPakIndex, const char* pElemFile) = 0;
	//获取子文件信息
	virtual bool	GetElemInfo(const char* pElemName, ELEM_FILE_INFO& info) = 0;
	//获取子文件信息
	virtual bool	GetElemInfo(unsigned int uElemId, ELEM_FILE_INFO& info) = 0;
	//从包中解出某个文件
	virtual bool	UnpackElem(int nPakIndex, const char* pElemName, const char* pDestName) = 0;
	//从包中解出某个文件
	virtual bool	UnpackElemByID(int nPakIndex, unsigned int uElemId, const char* pDestName) = 0;
	//从包中解出某个文件
	virtual bool	UnpackElemByIndex(int nPakIndex, unsigned int uElemIndex, const char* pDestName) = 0;
	//从包中解出全部文件
	//参数nUnpackCount用于传出结果解了多少个文件
	//参数pFileNamePrefix表示子文件名的前缀必须与此给定的字符串完全一致（不区分大小写），传入空指针表示无前缀限制
	virtual bool	UnpackAll(int nPakIndex, int& nUnpackCount, const char* pDestPath, const char* pFileNamePrefix = 0) = 0;
	//得到包中子文件的数目
	virtual int		GetElemCountInPak(int nPakIndex) = 0;
	//设置接口操作参数
	virtual void	SetOption(IPACK_FILE_SHELL_OPTION eOption, int nValue) = 0;
	//扫描整个包文件集合，对于每个子文件给出进行一次回调函数操作
	//参数pParam 为传给回调函数pCallback的参数
	//参数nCount 用于传出被扫描到到的（匹配要求）子文件的数目
	//参数pFileNamePrefix表示遍历到的子文件名的前缀必须与此给定的字符串完全一致（不区分大小写），前缀不符的子文件将被略过，传入空指针表示无前缀限制。
	//返回值表示扫描过程是否执行完毕未被打断
	virtual bool	ScanAllPack(fnScanPackCallback pCallback, void* pCallbackParam, int& nCount, const char* pFileNamePrefix = NULL) = 0;
	//获得包内某个子文件的存储数据
	virtual unsigned int	GetElemStoreDataInPak(int nPakIndex, int nElemIndex, void* pBuffer, unsigned int uBufferSize) = 0;
	//往打包文件中添加一个子文件（已经压缩好的）
	//传入参数ElemInfo::nPakIndex表示要加入哪个Pak文件
	//传入参数ElemInfo::nElemIndex无意义被忽略
	virtual bool	AddElemToPak(ELEM_FILE_INFO& ElemInfo, void* pBuffer) = 0;
};

//------模块的接口函数的原型的定义------
typedef IPackFileShell*					(*fnCreatePackFileShell)();

//------接口函数的函数名字符串----------
#define	FN_CREATE_PACKFILE_SHELL			"CreatePackFileShell"


C_ENGINE_API IPackFileShell* CreatePackFileShell();

#endif //__IPACKILESHELL_H_HEADER__