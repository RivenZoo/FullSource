/*****************************************************************************************
                    ┏━━━━━━━━━━━━━━━━━━━━━━━━━┓
                    ┃　　　Ｐｅｅｐｅｒ编辑器功能模块插件的规范　　　　┃
                    ┗━━━━━━━━━━━━━━━━━━━━━━━━━┛
Copyright : Kingsoft 2001-2002
Author	:   Wooy(Wu yue)
CreateTime:	2001-11-9
------------------------------------------------------------------------------------------
	此文件给出了Peeper编辑器功能模块插件的规范。

	Peeper编辑器编辑(模块)插件

		编辑模块插件的插件包容器为编辑器(Peeper)。
		插件程序必须导出下列两个函数：
		FPluginQuerryInfo
			用于查询插件的信息，函数原型见下面的fnFPluginQuerryInfo。
		FPluginGetShell
			用于获取插件的Shell接口对象，函数原型见下面的fnFPluginGetShell。
			插件的对外操作接口为KPluginShell。插件通过FPluginGetShell向客户提供此接口对象。
			调用此函数时会传入IPeeperShell接口实例的指针，插件保存此接口指针，运行时可以通过
			此接口的方法给Peeper发消息，请求Peeper完成指定的操作。

		IFPluginShell接口
			IFPluginShell为Peeper操纵插件的接口，Peeper通过插件的函数FPluginGetShell
		获得此接口实例的指针。
			IFPluginShell提供了下列操作函数：
		CreateResourceHolder
			创建一个资源操作接口。资源操作接口可以用于执行资源的打开、显示、编辑、存储等
			操作。
		OnCmd
			响应对此插件自定的菜单、工具栏等界面的操作。
			在不需要在使用IFPluginShell接口的时候，调用Release函数释放它。
*****************************************************************************************/
#pragma once

struct KFuncInfo
{
	char			Name[64];	//功能名称
	int				Version;	//功能版本要求
};

//======================================
//	功能模块插件信息结构
//======================================
struct KFPluginInfo
{
	int		Size;					//结构大小
	char	Title[STRING_SHORT];	//插件名称
	char	Intro[1024];			//插件说明
	int		NumResType;				//可处理操作的资源类型的个数
	KResTypeInfo*	pResTypeInfo;	//可处理操作的资源类型的信息
	int		NumFunc;				//可处理操作的资源类型的个数
	KFuncInfo*		pFuncInfo;		//可执行的功能的信息
};

enum PEEPER_PLUGIN_MSG
{
	PEEPER_ACTIVE = 1,
	//wparam = bActive
	PEEPER_CONFIGURABLE = 2,
	//return = bCofigurable

	PEEPER_CONFIG = 3,
};

//======================================
//	插件模块接口
//======================================
interface iKFPluginShell
{
	virtual int		   PeeperMsg(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
	//创建一个资源操作接口对象
	virtual void*	   CreateResourceHolder(HWND hParentWnd, RECT* prc, int nResType) = 0;
	//创建一个功能调用接口
	virtual IFunction*  CreateFunctionInstance(int nFuncIndex) = 0;
	virtual void	   OnCmd(int nCmd) = 0;					//响应界面命令
	virtual void	   Release() = 0;						//释放接口
};

//--------------------------------------------------------------------------
//	FPluginQuerryInfo函数原型，用于获取插件的信息。
//	参数：pInfo 指向一个插件信息结构的指针，被填写插件信息后返回。
//--------------------------------------------------------------------------
//******************************************************************************
typedef void (*fnFPluginQuerryInfo)(KFPluginInfo* pInfo);

//--------------------------------------------------------------------------
//	FPluginGetShell函数原型，用于获取插件的接口Shell对象。
//	参数：pInfo 指向一个插件信息结构的指针，被填写插件信息后返回。
//--------------------------------------------------------------------------
typedef iKFPluginShell* (*fnFPluginGetShell)(iKPeeperShell* pPeeper, int nUiCmdBase);

//======================================
//	插件的界面命令范围
//======================================
#define	FPLUGIN_COMMAND_RANGE	0x200
