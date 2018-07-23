/*****************************************************************************************
                    ┏━━━━━━━━━━━━━━━━━━━━━━━━━┓
                    ┃　　　　　外部访问Ｐｅｅｐｅｒ的接口　　　　　　　┃
                    ┗━━━━━━━━━━━━━━━━━━━━━━━━━┛
Copyright : Kingsoft 2001-2002
Author	:   Wooy(Wu yue)
CreateTime:	2001-11-11
------------------------------------------------------------------------------------------
		Peeper在获取外部插件的接口实例时会传送IPeeperShell实例的指针给插件。
	插件保存此接口指针，运行时可以通过此接口的方法给Peeper发消息，请求Peeper
	完成指定的操作。
		枚举结构KP_MESSAGE列出了所有IPeeperShell可以接受处理的消息，其中
	消息PM_COMMAND，是由Peeper内部产生的，外部不发此消息给Peeper。
*****************************************************************************************/
#ifndef __PEEPERSHELL_H__
#define __PEEPERSHELL_H__

//======================================
//		Peeper对外接口
//======================================
interface iKPeeperShell
{
	virtual int	SendMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0) = 0;
	virtual int	PostMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0) = 0;
	virtual IFunction* CreateFunctionInstance(LPSTR szFunctionName) = 0;	//创建功能包容器
};

//----设置当前目录----
#define PEEPER_SET_CUR_PATH		0x04
//----相对目录----
#define PEEPER_RELATE_PATH		0x08

//======================================
//	Peeper的消息
//======================================
enum	KP_MESSAGE
{
//----传送来自界面的命令----
	PM_COMMAND	= 1,
	//传送来自界面的命令，插件不会发送此消息给Peeper
	//wParam  = 菜单、控件或者是键盘快捷键的ID

	PM_SPECIAL_CMD,
	//
	//wParam = nCmdBase
	//lParam = nSpecialCmd

//----获取信息与数据----

	PM_INSTANCE,
	//获取Peeper程序模块句柄
	//返回   = Peeeper程序实例句柄（HINSTANCE）

	PM_MAIN_WND,
	//获取Peeper主窗口句柄
	//返回   = Peeper主窗口的句柄（HWND）

	PM_GET_WORK_PATH,
	//获得Peeper运行（工作）目录。
	//lParam = 指向一个Buffer，用于接受获取到的目录字符串，缓冲区的大小要求不小于MAX_PATH。

	PM_GET_FPLUGIN_PATH,
	//获得Peeper的插件目录。
	//lParam = 指向一个Buffer，用于接受获取到的目录字符串，缓冲区的大小要求不小于MAX_PATH。

	PM_GET_REF_PATH,
	//获取Peeper关联目录
	//wParam = 第几个关联目录
	//lParam = 指向一个Buffer，当关联目录生效时候，用于接受获取到的关联目录字符串，缓冲区的大小要求不小于MAX_PATH。
	//Return = 此关联目录是否有效。

	PM_SET_REF_PATH,
	//设置Peeper关联目录，并使它有效
	//wParam = 第几个关联目录
	//lParam = 指向一个字符串Buffer，字符串为要设置的目录。

	PM_GET_PEEPER_CONFIG_FILE_NAME,
	//获取Peeper设置文件的文件名
	//lParam = 指向一个Buffer，用于填写文件名

//----操作命令----

	PM_EXIT,
	//请求退出Peeper
	
	PM_RELOAD_FPLUGIN,
	//重新加载功能插件

	PM_REGISTER_SPECIAL_CMD,
	//注册特殊函数
	//wParam = Plugin初始化时收到的nCmdbase
	//lParam = 提示文字
	//返回   = CMD id

	PM_UNREGISTER_SPECIAL_CMD,
	//取消注册特殊函数
	//lParam = 函数id

//----窗口操作相关----

	PM_CREATE_CHILD_WND,
	//要求创建子窗口
	//wParam = 指向子窗口类名称的字符串，可以传入NULL，则Peeper采用默认类型的窗口。(char*)
	//lParam = 指向包容这个新建窗口的iKWndHolder接口实例的指针(iKWndHolder)
	//返回   = 新创建的子窗口的句柄（HWND）

	PM_DESTROY_CHILD_WND,
	//要求关闭子窗口
	//wParam = 要关闭的字窗口的句柄(HWND)

	PM_CREATE_FILELIST_VIEW,
	//要求创建文件列表窗口
	//wParam = 父窗口句柄(HWND)
	//lParam = 窗口矩形区域(RECT*)
	//返回   = 新创建的窗口的包容器的指针(HWND)

	PM_CREATE_FOLDER_VIEW,
	//要求创建文件夹浏览窗口
	//wParam = 父窗口句柄(HWND)
	//lParam = 窗口矩形区域(RECT*)
	//返回   = 新创建的窗口的包容器的指针(HWND)

	PM_CREATE_IMG_VIEW,
	//创建图形显示窗口
	//返回   = 所创建的图形显示窗口的接口指针（KImageView*）

//----拖动相关----

	PM_DRAG_BEGIN,
	//进入拖动资源状态
	//lParam = 被拖动的资源结构指针（KResource*）

	PM_QUERY_DRAG,
	//查询拖动的资源的信息
	//lParam = 接收被拖动资源的信息的结构的指针（KResource*）
	//返回   = 是否成功取得拖动资源的信息（bool）

//----界面相关----
	PM_INSERT_MENU,
	//插入菜单项
	//lParam = 菜单的句柄(HMENU)
	//wParam = 菜单命令id的调节基值(int)

	PM_REMOVE_MENU,
	//移除一个菜单项
	//lParam = 菜单的句柄(HMENU)

	PM_GET_REBAR,
	//获得rebar的窗口句柄
	//返回   = rebar的窗口句柄（HWND）

	PM_INSERT_TOOLBAR,
	//添加新的工具栏
	//lParam = 工具栏的窗口句柄(HWND)

	PM_SHOW_TOOLBAR,
	//显示或者隐藏一个工具栏
	//lParam = 工具栏的窗口句柄(HWND)
	//wParam = (bool) true --> 显示, false --> 隐藏

	PM_DOCK_WND,
	//停靠一个窗口在主窗口的侧边内
	//lParam = 要停靠的窗口的句柄
	//wParam = 停靠的位置(0-3)

	PM_UNDOCK_WND,
	//取消窗口在主窗口的侧边内的停靠
	//lParam = 取消停靠窗口的句柄
	//wParam = 原来停靠的位置(0-3)

	PM_REMOVE_TOOLBAR,
	//删除一个工具栏
	//lParam = 工具栏的窗口句柄(HWND)

//----资源操作----
	PM_RESOURCE_OPEN,
	//wParam = lParam所指的资源结构需要被是否释放(BOOL)
	//lParam = 资源结构指针(KResource*)
};

//======================================
//Peeper的界面发送命令的基值，其范围为基值至0xFFFF
//======================================
#define	PEEPER_COMMAND_BASE		0xF000
#define PEEPER_SPECIAL_CMD_BASE (PEEPER_COMMAND_BASE - 0x200)

//======================================
//	窗口位置
//======================================
enum POSITION_RELATE
{
	POSITION_LEFT	= 0,
	POSITION_TOP	= 1,
	POSITION_RIGHT	= 2,
	POSITION_BOTTOM	= 3,
};

//======================================
//	Peeper窗口的消息
//======================================
enum	KPW_MESSAGE
{
	PWM_DROP_ITEM		= WM_USER + 1,
	PWM_OPEN_RESOURCE,
};

#endif //__PEEPERSHELL_H__
