/*****************************************************************************************
                    ┏━━━━━━━━━━━━━━━━━━━━━━━━━┓
                    ┃　　　　　Ｐｅｅｐｅｒ常用接口与定义　　　　　　　┃
                    ┗━━━━━━━━━━━━━━━━━━━━━━━━━┛
Copyright : Kingsoft 2002
Author	:   Wooy(Wu yue)
CreateTime:	2002-3-6
------------------------------------------------------------------------------------------
*****************************************************************************************/
#ifndef __PEEPER_COMMINTERFACE_H__
#define __PEEPER_COMMINTERFACE_H__

//======================================
//	peeper可操作调度的功能操作的接口
//======================================
interface IFunction
{
	virtual void Release() = 0;		//释放接口
	virtual int  GetVersion() = 0;	//取得版本号
};

//======================================
//	观察者
//======================================
interface iKDetector
{
	virtual void	Notify(interface iKTargetObject* pObj) = 0;	//接受被观察对象发生了变化的通知
};

//======================================
//	被观察目标对象
//======================================
interface iKTargetObject
{
	virtual BOOL	Attach(iKDetector* pDetector) = 0;			//捆绑观察者
	virtual void	Detach(iKDetector* pDetector) = 0;			//解除观察者的捆绑
	virtual BOOL	GetStatus(void* pData1, void* pData2) = 0;	//获取对象状态
};

//======================================
//	资源包容器
//======================================
interface iKResHolder
{
	virtual BOOL	OpenResource(struct KResource* pResource) = 0;//打开资源
	virtual void	SaveResource() = 0;							//存储正被打开的资源
	virtual BOOL	CloseResource(int nFlag) = 0;				//关闭正被打开的资源
	virtual interface iKWndHolder* WndHolder() { return NULL; }	//获得资源包容器对象关联的窗口包容器对象的接口指针，如果无则返回NULL。
	virtual void	Release() = 0;								//释放接口对象
};

//======================================
//	窗口包容器
//======================================
interface iKWndHolder
{
	virtual BOOL	Create(HWND hParentWnd, RECT* prc) = 0;		//创建窗口界面
	virtual void	OnCmd(int nCmd) = 0;						//响应界面操作命令
	virtual void	OnWndMsg(UINT uMsg, WPARAM wParam, LPARAM lParam) {}; //响应窗口消息
	virtual HWND	Wnd() = 0;									//获得窗口的win32句柄
	virtual UINT	GetWndType() { return 0; }					//获得窗口包容器类型
	virtual iKResHolder* ResHolder() { return NULL;}		//获得窗口对象关联的资源包容器的接口指针，如果无则返回NULL。
	virtual void	Release() = 0;								//释放接口对象
};

//======================================
//	界面操作行为
//======================================
enum UI_OPERATION
{
	UIO_NONE		=	0,		//无操作
	UIO_SELECT		=	1,		//选中
	UIO_ACTIVE		=	2,		//激活（回车，双击）
	UIO_DRAG_BEGIN	=	3,		//开始拖动
	UIO_DRAG_END	=	4,		//拖动结束
};

//======================================
//	文件列表视图窗口
//======================================
//文件列表视图窗口回调函数原型定义
typedef int (*fnFlvCallback)(char* pFile, void* pData, int nParam);
interface iKFileListView : public iKWndHolder, iKDetector, iKTargetObject
{
	//设置界面布局情况，nLayout取值可为梅举FLV_LAYOUT中任意值的组合
	virtual void SetLayout(UINT nLayout) = 0;
	//设置回调函数，nCallback的取值为梅举FLV_CALLBACK_IDX中任意一值
	virtual void SetCallback(UINT nCallback, fnFlvCallback pCallback, int nParam) = 0;
	//列出给定文件夹的内容
	virtual void Browse(char* pFolder) = 0;
	//获取当前选择的文件名（单选模式）
	virtual BOOL GetFile(char* pFile) = 0;
	//获取选中的文件（多选模式）
	virtual BOOL GetFile(char* pFile, int* pnPos) = 0;
	//获取选中的文件的数目
	virtual UINT GetSelectedCount() = 0;
	//刷新
	virtual void Refresh() = 0;
};
//文件列表视图窗口布局选项
enum FLV_LAYOUT
{
	FLV_PATH_WND	= 0x0001,	//显示目录窗口
	FLV_SINGLE_SEL	= 0x0002,	//列表里只能同时选择一个文件/目录
	FLV_FILE_INFO	= 0x0004,	//显示文件特定信息
	FLV_FILE_TIME	= 0x0008,	//显示文件最后修改时间
	FLV_FILE_SIZE	= 0x0010,	//显示文件大小
	FLV_INC_FOLDER	= 0x0100,	//文件列表里包含文件夹
	FLV_INC_HIDDEN	= 0x0200,	//文件列表里包含隐藏文件(夹)

};
//文件列表视图窗口回调函数索引
enum FLV_CALLBACK_IDX
{
	FLV_CBI_FILTER	= 1,		//文件过滤
	FLV_CBI_GETINFO	= 2,		//文件信息描述
};

//======================================
//	文件夹视图窗口
//======================================
interface iKFolderView : public iKWndHolder, iKTargetObject
{
	virtual void	SelectFolder(char* pFolder) = 0;		//选定以目录名表示的文件夹
	virtual void	SelectFolder(LPITEMIDLIST pFolder) = 0;	//选定以itemlist表示的文件夹
	virtual void	Refresh() = 0;							//刷新
};

//======================================
//	图像显示窗口
//======================================
interface iKImageView : public iKWndHolder, iKTargetObject
{
	virtual void	SetWnd(HWND hWnd) = 0;					//设置绘制图形窗口Win32句柄
	virtual void	SetCanvasRect(RECT* prc) = 0;			//设置窗口画布的区域
	virtual void	SetInterval(int nInterval) = 0;			//设置换帧间隔
	virtual void*	SetImage(void* pImage) = 0;				//设置窗口要显示的图形
	virtual void	OnPaint() = 0;							//在窗口上完成绘制操作
};

//======================================
//	文件批处理接口
//======================================
interface iFileBatchProcess : IFunction
{
	enum FileBatchProcessOption
	{
		FBP_PROCESS_CALLBACK = 1,
		FBP_PROCESS_END_CALLBACK,
		FBP_CALLBACK_PARAM,
		FBP_SEARCH_FILE_FILTER,
		FBP_ROCESS_BTN_LABEL,

		FBP_SEARCH_FILE					= 0x0100,
		FBP_SEARCH_FOLDER				= 0x0200,
		FBP_SEARCH_RECURSIVE			= 0x0400,
		FBP_HIDE_PROCESS_BTN			= 0x0800,
		FBP_HIDE_RESULT_COLUMN			= 0x1000,
		FBP_REMOVE_ITEM_AFTER_PROCESSED = 0x2000,
	};

	typedef bool (*fnProcessFun)(void* Param, const char* pPath, const char* pFile, char* pResult);
	typedef void (*fnProcessEndFun)(void* Param, bool bOkForAll);

	virtual void	SetOption(FileBatchProcessOption eOption, void* OptionValue) = 0;
	virtual void	Process() = 0;
	virtual void	Process(const char* pPath) = 0;
	virtual bool	CreateUi(HWND hParentWnd, RECT* pRc) = 0;
	virtual void	AdjustLayout(RECT* pRc) = 0;			//调整窗口布局
	virtual void	ShowUi(bool bShow) = 0;
	virtual void	DestroyUi() = 0;
	virtual void	ClearResult() = 0;
};

#endif //__PEEPER_COMMINTERFACE_H__
