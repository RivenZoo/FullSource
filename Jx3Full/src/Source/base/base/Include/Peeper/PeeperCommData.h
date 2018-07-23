/*****************************************************************************************
                    ┏━━━━━━━━━━━━━━━━━━━━━━━━━┓
                    ┃　　　　　Ｐｅｅｐｅｒ一些基本数据类型定义　　　　┃
                    ┗━━━━━━━━━━━━━━━━━━━━━━━━━┛
Copyright : Kingsoft 2001-2002
Author	:   Wooy(Wu yue)
CreateTime:	2001-11-8
------------------------------------------------------------------------------------------
*****************************************************************************************/
#ifndef __PEEPER_COMMONDATA_H__
#define __PEEPER_COMMONDATA_H__

//======================================
//	资源来源类型定义
//======================================
enum KResTypeSource
{
	RT_S_MEMORY			=	0x01,	//来自内存
	RT_S_FILE			=	0x02,	//来自文件
	RT_S_FILEPORTION	=	0x04,	//来自文件的部分
};

//======================================
//	资源类型定义
//======================================
struct KResTypeInfo
{
	int		nIdxInModule;				//类型在插件模块中的索引
	DWORD	Source;						//资源的来源，参看KResTypeSource的来源类型定义
	char	Description[STRING_MINI];	//资源类型的描述
	char	FileFilter[STRING_MINI];	//资源文件的扩展名构成的类型过滤字符串
};

//======================================
//	资源操作类型定义
//======================================
enum KResOperation
{
	RO_OPEN			=	0x01,		//打开
	RO_EDIT			=	0x02,		//编辑
	RO_SAVE			=	0x04,		//存储
	RO_CANCEL		=	0xa0000000,	//操作被取消
	RO_DONE			=	0xc0000000,	//操作完成
	RO_OVER			=	0x80000000	//操作结束
};

//======================================
//	资源描述
//======================================
struct KResource
{
	unsigned int	Source;						//资源的来源, 参看KResTypeSource
	unsigned int	Operation;					//对资源进行的操作，参看KResOperation的资源操作类型定义
	int				nFileType;					//第几个文件类型
	char			Description[STRING_MINI];	//资源类型描述
	char			szFileName[MAX_PATH];		//资源文件名
	void*			pData;						//资源存储块
    unsigned long	nPara1;						//参数一
	unsigned long	nPara2;						//参数贰
};

//======================================
//	功能调用请求描述
//======================================
struct KFuncRequest
{
	char			FuncName[64];	//功能名称
	int				Version;		//功能版本要求
	char			strParam[512];	//功能调用字符串参数
	unsigned long	nPara1;			//参数一
	long			nPara2;			//参数贰
};

#endif //__PEEPER_COMMONDATA_H__
